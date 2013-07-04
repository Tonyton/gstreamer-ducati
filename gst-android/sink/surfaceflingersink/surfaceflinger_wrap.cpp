#define ENABLE_GST_PLAYER_LOG
#include <surfaceflinger/ISurface.h>
#include <surfaceflinger/Surface.h>
#include <binder/MemoryHeapBase.h>
#include <binder/MemoryBase.h>
#include <surfaceflinger/ISurfaceComposer.h>
#include <surfaceflinger/SurfaceComposerClient.h>
#include <cutils/log.h>
#include "surfaceflinger_wrap.h"
#include <GstLog.h>
#include "gstsurfaceflingersink.h"

#include <utils/Vector.h>
#include <utils/RefBase.h>
#include <ui/Overlay.h>
#include <v4l2_utils.h>

using namespace android;

typedef struct 
{
    int32_t decoded_width;
    int32_t decoded_height;
    uint32_t display_width;
    uint32_t display_height;
    size_t buf_index; 
    int nOverlayBuffersQueued;
    int buffers_queued_to_dss[NUM_OVERLAY_BUFFERS_MAX];
    PixelFormat format;
    sp<Overlay> overlay;
    sp<ISurface> isurface;
    sp<SurfaceControl> surface;
    Vector< sp<IMemory> > overlay_addresses;
    sp<MemoryHeapBase> mVideoHeaps[NUM_OVERLAY_BUFFERS_MAX];
    release_rendered_overlaybuffer_callback release_frame_cb;
    void * cookie;
    size_t num_buffers;
        
} VideoFlingerDevice;

#define NUM_QUEUED_BUFFERS_OPTIMAL     (NUM_OVERLAY_BUFFERS_REQUESTED)

#define LITERAL_TO_STRING_INTERNAL(x)    #x
#define LITERAL_TO_STRING(x) LITERAL_TO_STRING_INTERNAL(x)

#define CHECK_EQ(x,y)                                                   \
    LOG_ALWAYS_FATAL_IF(                                                \
            (x) != (y),                                                 \
            __FILE__ ":" LITERAL_TO_STRING(__LINE__) " " #x " != " #y)

#define CHECK(x)                                                        \
    LOG_ALWAYS_FATAL_IF(                                                \
            !(x),                                                       \
            __FILE__ ":" LITERAL_TO_STRING(__LINE__) " " #x)

/* 
 * The only purpose of class "MediaPlayer" is to call Surface::getISurface()
 * in frameworks/base/include/ui/Surface.h, which is private function and accessed
 * by friend class MediaPlayer.
 *
 * We define a fake one to cheat compiler
 */
namespace android {
class Test {
public:
    static const sp<ISurface>& getISurface(const sp<Surface>& s) {
        return s->getISurface();
    }
};
};

////////////////////////////////////////////////////////////////////////////////
static int Calculate_TotalRefFrames(int nWidth, int nHeight) {
    LOGD("Calculate_TotalRefFrames");
    uint32_t ref_frames = 0;
    uint32_t MaxDpbMbs;
    uint32_t PicWidthInMbs;
    uint32_t FrameHeightInMbs;

    MaxDpbMbs = 32768; //Maximum value for upto level 4.1

    PicWidthInMbs = nWidth / 16;

    FrameHeightInMbs = nHeight / 16;

    ref_frames =  (uint32_t)(MaxDpbMbs / (PicWidthInMbs * FrameHeightInMbs));

    LOGD("nWidth [%d] PicWidthInMbs [%d] nHeight [%d] FrameHeightInMbs [%d] ref_frames [%d]",
        nWidth, PicWidthInMbs, nHeight, FrameHeightInMbs, ref_frames);

    ref_frames = (ref_frames > 16) ? 16 : ref_frames;

    LOGD("Final ref_frames [%d]", ref_frames);

    return (ref_frames + 3 + 2*NUM_BUFFERS_TO_BE_QUEUED_FOR_OPTIMAL_PERFORMANCE);
}


VideoFlingerDeviceHandle videoflinger_device_create(void *isurface)
{
    VideoFlingerDevice *videodev=NULL;

    videodev = new VideoFlingerDevice;
    if (videodev == NULL) {
	return NULL;
    }
    videodev->isurface = (ISurface*)isurface;
    videodev->surface.clear();
    videodev->format = -1;
    videodev->decoded_width = 0;
    videodev->decoded_height = 0;
    videodev->display_width = 0;
    videodev->display_width = 0;
    videodev->buf_index = 0;
    videodev->num_buffers = -1;
    videodev->nOverlayBuffersQueued = 0;
    videodev->release_frame_cb = NULL;

    GST_PLAYER_INFO("Leave\n");

    return (VideoFlingerDeviceHandle)videodev;    
}

/*xuzhi.Tony.the fuc only for test on command. */
static int videoflinger_device_create_new_surface(VideoFlingerDevice* videodev)
{
    sp < SurfaceComposerClient > videoClient = new SurfaceComposerClient;
    if (videoClient.get () == NULL) {
    	LOGE ("Fail to create SurfaceComposerClient\n");
    	return -1;
    }
    /* release privious surface */
    videodev->surface.clear ();
    videodev->isurface.clear ();
    int width =  videodev->decoded_width;
    int height = videodev->decoded_height;
    videodev->surface = videoClient->createSurface (getpid(),
      		0,
      		width,
      		height,
      		PIXEL_FORMAT_RGB_565,
      		ISurfaceComposer::eFXSurfaceNormal | ISurfaceComposer::ePushBuffers);
    if (videodev->surface.get () == NULL) {
    	LOGE ("Fail to create Surface\n");
    	return -1;
    }
    videoClient->openTransaction ();
    /* set Surface toppest z-order, this will bypass all isurface created 
     * in java side and make sure this surface displaied in toppest */
    videodev->surface->setLayer (INT_MAX);
    /* show surface */
    videodev->surface->show ();
    /* get ISurface interface */
    videodev->isurface = Test::getISurface(videodev->surface->getSurface());
    videoClient->closeTransaction ();

    GST_PLAYER_INFO("Leave\n");
    return 0;
}

int videoflinger_device_release(VideoFlingerDeviceHandle handle)
{
    GST_PLAYER_INFO("Enter");
    if (handle == NULL) {
	return -1;
    }
    /* unregister frame buffer */
    videoflinger_device_unregister_framebuffers(handle); 

    /* release ISurface & Surface */
    VideoFlingerDevice *videodev = (VideoFlingerDevice*)handle;

    sp<IMemory> mem;
    for (size_t i = 0; i < videodev->num_buffers; ++i) {
        mem = videodev->overlay_addresses[i];
        mem.clear();
        //dispose the memory allocated on heap explicitly
        (videodev->mVideoHeaps[i].get())->dispose();
        videodev->mVideoHeaps[i].clear();
    }
    videodev->overlay->destroy();
    videodev->overlay.clear();
    videodev->overlay = NULL;
    // XXX apparently destroying an overlay is an asynchronous process...
    sleep(1);

    videodev->overlay_addresses.clear();

    videodev->isurface.clear();
    videodev->surface.clear();

    /* delete device */
    delete videodev;
    GST_PLAYER_INFO("Leave");
    return 0;
}

int videoflinger_device_register_framebuffers(VideoFlingerDeviceHandle handle, 
    int w, int h, VIDEO_FLINGER_PIXEL_FORMAT format,int numbuf)
{
    GST_PLAYER_INFO("Enter");
    /* Disable 3d */
    int isS3D = 0; 
    mapping_data_t *data;
    sp<IMemory> mem;

    if (handle == NULL) {
	GST_PLAYER_ERROR("videodev is NULL");
	return -1;
    }
    /* If playbin2 choose ffmpeg decoder,format is I420.
     * choose gst-ducati, format is NV12. Tony
     */
    if ((format !=  VIDEO_FLINGER_I420) && (format !=  VIDEO_FLINGER_NV12) ) {
	GST_PLAYER_ERROR("Unsupport format: %d", format);
	return -1;
    }

    VideoFlingerDevice *videodev = (VideoFlingerDevice*)handle;

    /* unregister previous buffers */
    if (videodev->overlay.get() != NULL ) {
	videoflinger_device_unregister_framebuffers(handle);
    }

    videodev->num_buffers = numbuf;
    /* reset framebuffers */
    videodev->format = format;
    videodev->decoded_width = (w + 1) & -2;
    videodev->decoded_height = (h + 1) & -2;

    /* create isurface internally, if no ISurface interface input */
    if (videodev->isurface.get() == NULL) {
	videoflinger_device_create_new_surface(videodev);
    }

    LOGD( 
	"format=%d, decoded_width=%d, decoded_height=%d, display_width=%d, display_height=%d",
	videodev->format,
	videodev->decoded_width,
	videodev->decoded_height,
	videodev->display_width,
	videodev->display_height);

    if(videodev->isurface.get() == NULL) {
	GST_PLAYER_ERROR("xuzhi.Tony :Error create android surface");
	return -1;
    }
    /* create overlay..Xuzhi.Tony */
    if(videodev->overlay == NULL){
	sp<OverlayRef> ref = videodev->isurface->createOverlay(
	    videodev->decoded_width, videodev->decoded_height, OVERLAY_FORMAT_YCbCr_420_SP,ISurface::BufferHeap::ROT_0, isS3D);
	if (ref.get() == NULL) {
	    GST_PLAYER_ERROR("Unable to create the overlay!");
	    return -1;
	}
        videodev->overlay = new Overlay(ref);
    }
    /* FIXME: under code come frome TIHardwareRenderer.cpp. Tony
     */
    if(videodev->num_buffers > NUM_OVERLAY_BUFFERS_MAX) {
        /* Calculate the number of overlay buffers required, based on the video resolution
         * and resize the overlay for the new number of buffers. 
	 * FIXME: You must set the display_width and display_height first. xuzhi.Tony
         */
        	
        int overlaybuffcnt = Calculate_TotalRefFrames(videodev->display_width, videodev->display_width);
        int initialcnt = videodev->overlay->getBufferCount();
        if (overlaybuffcnt != initialcnt) {
            videodev->overlay->setParameter(OVERLAY_NUM_BUFFERS, overlaybuffcnt);
            videodev->overlay->resizeInput(videodev->decoded_width, videodev->decoded_height);
        }
        videodev->overlay->setParameter(OPTIMAL_QBUF_CNT, 2*NUM_BUFFERS_TO_BE_QUEUED_FOR_OPTIMAL_PERFORMANCE);
    } else {
       	/* Number of buffers will be set as recommended by user or codec */
       	LOGI("Overlay Buffer Count [as recommneded] %d",videodev->num_buffers);
       	videodev->overlay->setParameter(OVERLAY_NUM_BUFFERS, videodev->num_buffers);
       	videodev->overlay->resizeInput(videodev->decoded_width, videodev->decoded_height);
       	videodev->overlay->setParameter(OPTIMAL_QBUF_CNT, NUM_BUFFERS_TO_BE_QUEUED_FOR_OPTIMAL_PERFORMANCE*2);
    }
    for (size_t i = 0; i < (size_t)videodev->overlay->getBufferCount(); ++i) {
        data = (mapping_data_t *)videodev->overlay->getBufferAddress((void *)i);
        CHECK(data != NULL);
        videodev->mVideoHeaps[i] = new MemoryHeapBase(data->fd,data->length, 0, data->offset);		
        mem = new MemoryBase(videodev->mVideoHeaps[i], 0, data->length);				
        CHECK(mem.get() != NULL);								
        LOGV("mem->pointer[%d] = %p\n", i, mem->pointer());
        videodev->overlay_addresses.push(mem);
        videodev->buffers_queued_to_dss[i] = 0;								

    }
    GST_PLAYER_INFO("Leave");
    return 0;
}

void videoflinger_device_overlay_setcrop(VideoFlingerDeviceHandle handle,
			int cropx,int cropy,int width,int height)
{
    LOGV("int cropx %d,int cropy %d,width %d, height %d =============",cropx,cropy,width,height);
    /* NOTE: this fuction is called when crop evnet appent which is latter than
     * the overlay create. So if you want use Calculate_TotalRefFrames fuc,
     * you must find a way to get the display_width and display_height 
     * first. xuzhi.Tony 
     */
    VideoFlingerDevice* videodev = (VideoFlingerDevice*)handle;
    assert( videodev != NULL );
    videodev->display_width = width;
    videodev->display_height = height;
    videodev->overlay->setCrop((uint32_t)cropx,(uint32_t)cropy,width,height);
}

void *videoflinger_device_get_overlay_address(VideoFlingerDeviceHandle handle,int index) 
{
    VideoFlingerDevice* videodev = (VideoFlingerDevice*)handle;
    assert( videodev != NULL );
    return videodev->overlay_addresses[index]->pointer();
}

unsigned int videoflinger_device_get_overlay_buf_length(VideoFlingerDeviceHandle handle) 
{
    VideoFlingerDevice* videodev = (VideoFlingerDevice*)handle;
    assert( videodev != NULL);
    LOGV("overlay buffer alloc size is %d\n",videodev->overlay_addresses[0]->size());
    /* All the buffer size are the same. 
     * So give any index. xuzhi.Tony
     */
    return videodev->overlay_addresses[0]->size();
}

int videoflinger_device_get_overlay_buf_count(VideoFlingerDeviceHandle handle)
{
    VideoFlingerDevice* videodev = (VideoFlingerDevice*)handle;
    if (videodev->overlay == NULL )
	return 0;
    return videodev->overlay->getBufferCount();
}

void videoflinger_device_unregister_framebuffers(VideoFlingerDeviceHandle handle)
{
    GST_PLAYER_INFO("Enter");
    if (handle == NULL) {
	return;
    }

    VideoFlingerDevice* videodev = (VideoFlingerDevice*)handle;
    if (videodev->overlay.get()) {
	GST_PLAYER_INFO("Unregister frame buffers.  videodev->isurface = %p", videodev->isurface.get());

	/* release ISurface */
	videodev->isurface->unregisterBuffers();

	videodev->format = -1;
	videodev->decoded_width = 0;
	videodev->decoded_height = 0;
	videodev->display_width = 0;
	videodev->display_width = 0;
	videodev->buf_index = 0;
	videodev->num_buffers = -1;
	videodev->nOverlayBuffersQueued = 0;
	videodev->release_frame_cb = NULL;
    }
    GST_PLAYER_INFO("Leave");
}

static void convertYuv420ToNV12(
        int width, int height, const void *src, void *dst) {
    //LOGI("Coverting YUV420 to NV-12 height %d and Width %d", height, width);
   uint32_t stride = 4096;
    //copy y-buffer, almost bytewise copy, except for stride jumps.
    {
        uint8_t* p1y = (uint8_t*) src;
        uint8_t* p2y = (uint8_t*) dst;
        for(int i=0;i<height;i++)
        {
            //copy whole row of Y pixels. source and desination will point to new row each time.
            memcpy(p2y+i*stride, p1y+i*width,width);
        }
    }

//copy uv buffers
//rearrange from  planar [uuu][vvvv] to packed planar [uvuvuv]  packages pixel wise
    {
        uint8_t* p2uv  = NULL;
        p2uv  = (uint8_t*) dst;
        p2uv  += stride * height;

        uint8_t* p1u = ((uint8_t*) src + (width*height));
        uint8_t* p1v = ((uint8_t*) p1u + ((width/2)*(height/2)));

        for(int i=0;(i<height/2);i++)
        {
            for(int j=0,j1=0;(j<width/2);j++,j1+=2)
            {
                p2uv[j1] = p1u[j];
                p2uv[j1+1] = p1v[j];
            }
            p2uv+=stride;
            p1u+=width/2;
            p1v+=width/2;
        }
    }
}

void videoflinger_device_post(VideoFlingerDeviceHandle handle, void * data, int size)
{
    GST_PLAYER_INFO("Enter");

    if (handle == NULL) {
		return;
    }

    VideoFlingerDevice* videodev = (VideoFlingerDevice*)handle;

    /* replace surfaceflinger with overlay */
    if (videodev->overlay.get() == NULL) {
	GST_PLAYER_ERROR("XuZhi.Tony :Get overlay Error");
	return;
    }
    overlay_buffer_t overlay_buffer;
    size_t i = 0;
    if (videodev->format == VIDEO_FLINGER_I420) {
	convertYuv420ToNV12(videodev->decoded_width, videodev->decoded_height, data, videodev->overlay_addresses[videodev->buf_index]->pointer());
    } else if (videodev->format == VIDEO_FLINGER_NV12) {
        for (; i < videodev->num_buffers; ++i) {
            /**
            *In order to support the offset from the decoded buffers, we have to check for
            * the range of offset with in the buffer. Here we can't check for the base address
            * and also, the offset should be used for crop window position calculation
            * we are getting the Baseaddress + offset
            **/
            unsigned int offsetinPixels = (char*)data - (char*)videodev->overlay_addresses[i]->pointer();
            if(offsetinPixels < size){
                LOGV("offsetinPixels is %u,size is %d, i is [ %d ] data address is [%p]\nvideodev->overlay_addresses[i]->pointer()is [%p] \n",
			offsetinPixels,size,i,data,videodev->overlay_addresses[i]->pointer());
                break;
            }
        }

        if (i == videodev->overlay_addresses.size()) {
            LOGE("Doing a memcpy. Report this issue.");
            memcpy(videodev->overlay_addresses[videodev->buf_index]->pointer(), data, size);
        }
        else{
            videodev->buf_index = i;
        }

    }

    LOGV("mIndex is %d\n",videodev->buf_index);
    int nBuffers_queued_to_dss = videodev->overlay->queueBuffer((void *)videodev->buf_index);

    if (videodev->release_frame_cb) {
        if (nBuffers_queued_to_dss < 0){
            videodev->release_frame_cb(videodev->overlay_addresses[videodev->buf_index]->pointer(),videodev->cookie);
        }
        else
        {
            videodev->nOverlayBuffersQueued++;
            videodev->buffers_queued_to_dss[videodev->buf_index] = 1;
            if (nBuffers_queued_to_dss != videodev->nOverlayBuffersQueued) // STREAM OFF occurred
            {
                LOGE("nBuffers_queued_to_dss = %d, nOverlayBuffersQueued = %d", nBuffers_queued_to_dss, videodev->nOverlayBuffersQueued);
                LOGE("buffers in DSS \n %d %d %d  %d %d %d", videodev->buffers_queued_to_dss[0], videodev->buffers_queued_to_dss[1],
                videodev->buffers_queued_to_dss[2], videodev->buffers_queued_to_dss[3], videodev->buffers_queued_to_dss[4], 
		videodev->buffers_queued_to_dss[5]);
                //Release all the buffers that were discarded by DSS upon STREAM OFF.
                for(unsigned int k = 0; k < (unsigned int)videodev->overlay->getBufferCount(); k++)
                {
                    if ((videodev->buffers_queued_to_dss[k] == 1) && (k != videodev->buf_index))
                    {
                        videodev->buffers_queued_to_dss[k] = 0;
                        videodev->nOverlayBuffersQueued--;
                        videodev->release_frame_cb(videodev->overlay_addresses[k]->pointer(),videodev->cookie);
                        LOGE("Reclaiming the buffer [%d] from Overlay", k);
                    }
                }
            }
        }
    }

    int err = videodev->overlay->dequeueBuffer(&overlay_buffer);
    if (err == 0) {
        videodev->nOverlayBuffersQueued--;
        videodev->buffers_queued_to_dss[(int)overlay_buffer] = 0;
        if (videodev->release_frame_cb) {
            videodev->release_frame_cb(videodev->overlay_addresses[(int)overlay_buffer]->pointer(),videodev->cookie);
        }
    }

    if (++videodev->buf_index == videodev->overlay_addresses.size()) videodev->buf_index = 0;

    LOGV("Leave");
}

/* TODO:gstreamer release buffer by itself. Then what can we do 
 *  in the release frame call back fuc? I just give a empty fuc 
 *  in the gstsurfaceflingersink.c. xuzhi.Tony
 */

void videoflinger_device_set_callback(VideoFlingerDeviceHandle handle,release_rendered_overlaybuffer_callback cb, void *c)
{
    VideoFlingerDevice* videodev = (VideoFlingerDevice*)handle;
    assert(videodev != NULL);

    videodev->release_frame_cb = cb;
    videodev->cookie = c;
}
