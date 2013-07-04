#ifndef GST_METADATARETRIEVER_H
#define GST_METADATARETRIEVER_H

#include <utils/Errors.h>
#include <media/MediaMetadataRetrieverInterface.h>
#include "GstMetadataRetrieverDriver.h"

namespace android {

class GstMetadataRetriever : public MediaMetadataRetrieverInterface
{
public:
	GstMetadataRetriever();
	virtual             ~GstMetadataRetriever();

	virtual status_t    	setDataSource(const char *url);
	virtual status_t    	setDataSource(int fd, int64_t offset, int64_t length);
	virtual status_t    	setMode(int mode);
	virtual status_t    	getMode(int* mode) const;
	virtual VideoFrame* 	captureFrame();
	virtual MediaAlbumArt* 	extractAlbumArt();
	virtual const char* 	extractMetadata(int keyCode);

private:
	static void  do_nothing(status_t s, void *cookie, bool cancelled) { 
		if(s) { /* warning removal*/ } 
		if(cookie) { /* warning removal*/ }  
		if(cancelled) { /* warning removal*/ }  
	}

	GstMetadataRetrieverDriver*	mGstDriver;
	int				mMode;
	int				mLocked ;
	
};

}; // namespace android

#endif // GST_METADATARETRIEVER_H
