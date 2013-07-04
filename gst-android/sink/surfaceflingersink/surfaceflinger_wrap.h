/*
 * This file defines APIs to convert C++ ISurface 
 * interface to C interface
 */
#ifndef __SURFACE_FLINGER_WRAP_H__
#define  __SURFACE_FLINGER_WRAP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <grp.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

#include "overlay_common.h"

typedef void (*release_rendered_overlaybuffer_callback)(const void *buf, void *cookie);

typedef void* VideoFlingerDeviceHandle;


typedef enum
{
	VIDEO_FLINGER_RGB_565 = 1,
	VIDEO_FLINGER_RGB_888 = 2,
	VIDEO_FLINGER_I420    = 3,
	VIDEO_FLINGER_NV12    = 4,
} VIDEO_FLINGER_PIXEL_FORMAT;

VideoFlingerDeviceHandle videoflinger_device_create(void *isurface);

int videoflinger_device_release(VideoFlingerDeviceHandle handle);
int videoflinger_device_register_framebuffers(VideoFlingerDeviceHandle handle, int w, int h, VIDEO_FLINGER_PIXEL_FORMAT format,int numbuf);
void videoflinger_device_unregister_framebuffers(VideoFlingerDeviceHandle handle);
void videoflinger_device_post(VideoFlingerDeviceHandle handle, void * buf, int bufsize);
void *videoflinger_device_get_overlay_address(VideoFlingerDeviceHandle handle, int index);
unsigned int videoflinger_device_get_overlay_buf_length(VideoFlingerDeviceHandle handle);
void videoflinger_device_set_callback(VideoFlingerDeviceHandle handle, release_rendered_overlaybuffer_callback cb, void *c);
int videoflinger_device_get_overlay_buf_count(VideoFlingerDeviceHandle handle);
void videoflinger_device_overlay_setcrop(VideoFlingerDeviceHandle handle,
                        int cropx,int cropy,int width,int height);

#ifdef __cplusplus
}
#endif

#endif /*__SURFACE_FLINGER_WRAP_H__*/
