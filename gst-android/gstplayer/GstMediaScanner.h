#ifndef GSTMEDIASCANNER_H
#define GSTMEDIASCANNER_H

#include <media/mediascanner.h>

namespace android {

struct GstMediaScanner : public MediaScanner {
	GstMediaScanner();
	virtual ~GstMediaScanner();

	virtual status_t processFile(
			const char *path, const char *mimeType,
			MediaScannerClient &client);

	virtual char *extractAlbumArt(int fd);
};

struct GstMediaScannerClient : public MediaScannerClient {
	GstMediaScannerClient() {  // call MediaScannerClient::MediaScannerClient
		LOGV("GstMediaScannerClient construtor");
	}

	~GstMediaScannerClient() { // call MediaScanner::~MediaScanner
		LOGV("GstMediaScannerClient destructor");
	}
	// non-virtual functions
	void setLocale(const char* locale);
	void beginFile();
	bool addStringTag(const char* name, const char* value);
	void endFile();
	void convertValues(uint32_t encoding);

	// pure virtual functions
	bool scanFile(const char* path, long long lastModified, long long fileSize);
	bool handleStringTag(const char* name, const char* value);
	bool setMimeType(const char* mimeType);
	bool addNoMediaFolder(const char* path);
};

}  // namespace android

#endif // GSTMEDIASCANNER_H
