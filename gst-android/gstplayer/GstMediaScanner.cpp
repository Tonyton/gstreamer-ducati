#ifndef GSTMEDIASCANNER
#define GSTMEDIASCANNER

//#define LOG_NDEBUG 0

#undef LOG_TAG
#define LOG_TAG "GstMediaScanner"

#include <utils/Log.h>
#include <media/mediascanner.h>
#include <media/mediametadataretriever.h>
#include <private/media/VideoFrame.h>
#include <utils/StringArray.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>

#include <binder/IMemory.h>
#include "GstMediaScanner.h"

#define UNUSED(x) (void)x

// flags used for native encoding detection
enum {
    kEncodingNone               = 0,
    kEncodingShiftJIS           = (1 << 0),
    kEncodingGBK                = (1 << 1),
    kEncodingBig5               = (1 << 2),
    kEncodingEUCKR              = (1 << 3),
    kEncodingAll                = (kEncodingShiftJIS | kEncodingGBK | kEncodingBig5 | kEncodingEUCKR),
};

namespace android {
GstMediaScanner::GstMediaScanner()  {}

GstMediaScanner::~GstMediaScanner() {}

status_t GstMediaScanner::processFile(const char *path, const char* mimeType, MediaScannerClient& client)
{
	const char* extension = strrchr(path, '.');
	
	UNUSED(mimeType);

	LOGV("MediaScanner processFile %s", path);

	//first check if extension is supported 
	if( !extension) {
		return -1; 
	}

	if( 
		//audio file
		!strcasecmp(extension, ".mp3") ||
		!strcasecmp(extension, ".ogg") ||
		!strcasecmp(extension, ".oga") ||
		!strcasecmp(extension, ".mid") || 
		!strcasecmp(extension, ".midi") ||		
		!strcasecmp(extension, ".smf") ||
		!strcasecmp(extension, ".xmf") ||
		!strcasecmp(extension, ".rtttl") ||
		!strcasecmp(extension, ".imy") ||
		!strcasecmp(extension, ".rtx") ||
		!strcasecmp(extension, ".ota") ||
		!strcasecmp(extension, ".wma") ||
		!strcasecmp(extension, ".m4a") ||
		!strcasecmp(extension, ".amr") ||
		!strcasecmp(extension, ".awb") ||
		!strcasecmp(extension, ".wav") ||
		!strcasecmp(extension, ".aac") ||
		//video file
		!strcasecmp(extension, ".mp4") ||
		!strcasecmp(extension, ".m4v") ||
		!strcasecmp(extension, ".3gp") || 
		!strcasecmp(extension, ".3gpp") || 
		!strcasecmp(extension, ".3gp2") || 
		!strcasecmp(extension, ".3gpp2") ||		
		!strcasecmp(extension, ".3g2") ||
		!strcasecmp(extension, ".avi") || 
		!strcasecmp(extension, ".mov") ||
		!strcasecmp(extension, ".wmv") ||
		!strcasecmp(extension, ".asf") ||		
		!strcasecmp(extension, ".divx") 
		){
		// extension of multimedia file supported
	}
	else{
		LOGV("MediaScanner processFile extension %s not supported", extension);
		return -1;
	}

	sp<MediaMetadataRetriever> retriever = new MediaMetadataRetriever();
	retriever->setMode(METADATA_MODE_METADATA_RETRIEVAL_ONLY);
	status_t status = retriever->setDataSource(path);

	if (status != NO_ERROR) {
		LOGE("MediaScanner setDataSource failed (%d)", status);
		retriever->disconnect();
		return status;
	}
	
	// init client
	client.setLocale(locale());
	client.beginFile();

	const char* value;

	// extract metadata from the file
	value = retriever->extractMetadata(METADATA_KEY_IS_DRM_CRIPPLED);
	if (value && strcmp(value, "true") == 0) {
		// we don't support WMDRM currently
		// setting this invalid mimetype will make the java side ignore this file
		client.setMimeType("audio/x-wma-drm");
	}
	value = retriever->extractMetadata(METADATA_KEY_CODEC);
	if (value && strcmp(value, "Windows Media Audio 10 Professional") == 0) {
		// we don't support WM 10 Professional currently
		// setting this invalid mimetype will make the java side ignore this file
		client.setMimeType("audio/x-wma-10-professional");
	}

	value = retriever->extractMetadata(METADATA_KEY_ALBUM);
	if (value)
		client.addStringTag("album", value);

		// Look for "author" tag first, if it is not found, try "artist" tag
	value = retriever->extractMetadata(METADATA_KEY_AUTHOR);
	if (!value) {
		value = retriever->extractMetadata(METADATA_KEY_ARTIST);
	}
	if (value)
		client.addStringTag("artist", value);
	value = retriever->extractMetadata(METADATA_KEY_COMPOSER);
	if (value)
		client.addStringTag("composer", value);
	value = retriever->extractMetadata(METADATA_KEY_GENRE);
	if (value)
		client.addStringTag("genre", value);
	value = retriever->extractMetadata(METADATA_KEY_TITLE);
	if (value)
		client.addStringTag("title", value);
	value = retriever->extractMetadata(METADATA_KEY_YEAR);
	if (value)
		client.addStringTag("year", value);
	value = retriever->extractMetadata(METADATA_KEY_CD_TRACK_NUMBER);
	if (value)
		client.addStringTag("tracknumber", value);

	retriever->disconnect();
	// send info to java layer
	client.endFile();
	return status;
}
    
// extracts album art as a block of data
// output: is a jpeg + 4 bytes of header to give jpeg size
char* GstMediaScanner::extractAlbumArt(int fd)
{
	LOGV("MediaScanner extractAlbumArt %d", fd);
	struct stat statbuf;
	char *data = NULL;

	sp<MediaMetadataRetriever> retriever = new MediaMetadataRetriever();
	retriever->setMode(METADATA_MODE_METADATA_RETRIEVAL_ONLY);
	// make stat to get fd size
	fstat(fd, &statbuf);
	retriever->setDataSource(fd, 0, statbuf.st_size);
	
	sp<IMemory> albumArt = retriever->extractAlbumArt();

	if(albumArt != NULL) {
		MediaAlbumArt *albumArtCopy = static_cast<MediaAlbumArt *>(albumArt->pointer());
	
		data = (char*)malloc(albumArtCopy->mSize + 4);		
		if (data) {
			long *len = (long*)data;
			*len =  albumArtCopy->mSize;
			memcpy(data + 4,  (char*) albumArtCopy + sizeof(MediaAlbumArt), *len);
		}
	}
	retriever->disconnect();
	return data; 
}
    
void GstMediaScannerClient::setLocale(const char* locale) 
{
	LOGV("GstMediaScannerClient set locale %s", locale);
	MediaScannerClient::setLocale (locale);
}

void GstMediaScannerClient::beginFile()
{
	LOGV("GstMediaScannerClient beginFile");
	MediaScannerClient::beginFile();
}

bool GstMediaScannerClient::addStringTag(const char* name, const char* value)
{
	LOGV("GstMediaScannerClient addStringTag %s : %s", name, value);
	return MediaScannerClient::addStringTag (name, value);
}

void GstMediaScannerClient::endFile()
{	
	LOGV("GstMediaScannerClient endFile");
	MediaScannerClient::endFile();
}
	
void GstMediaScannerClient::convertValues(uint32_t encoding)
{
	LOGV("GstMediaScannerClient convertValues %d", encoding);
	MediaScannerClient::convertValues (encoding);
}

/*
 * place holder for functions
 */
bool GstMediaScannerClient::scanFile(const char* path, long long lastModified, long long fileSize) {
	LOGV("GstMediaScannerClient scanFile");
	return false;
}

bool GstMediaScannerClient::handleStringTag(const char* name, const char* value) {
	LOGV("GstMediaScannerClient handleStringTag");
	return false;
}

bool GstMediaScannerClient::setMimeType(const char* mimeType) {
	LOGV("GstMediaScannerClient setMimeType");
	return false;
}

bool GstMediaScannerClient::addNoMediaFolder(const char* path) {
	LOGV("GstMediaScannerClient addNoMediaFolder");
	return false;
}

}; //namespace android

#endif // GSTMEDIASCANNER
