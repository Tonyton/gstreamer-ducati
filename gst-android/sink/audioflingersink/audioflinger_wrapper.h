/*
 * This file defines APIs to convert C++ AudioFlinder/AudioTrack
 * interface to C interface
 */
#ifndef __AUDIOFLINGER_WRAPPER_H__
#define __AUDIOFLINGER_WRAPPER_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef void* AudioFlingerDeviceHandle;

AudioFlingerDeviceHandle audioflinger_device_create();

AudioFlingerDeviceHandle audioflinger_device_open(void* audio_sink);

int audioflinger_device_set (AudioFlingerDeviceHandle handle, 
  int streamType, int channelCount, uint32_t sampleRate, int bufferCount);

void audioflinger_device_release(AudioFlingerDeviceHandle handle);

void audioflinger_device_start(AudioFlingerDeviceHandle handle);

void audioflinger_device_stop(AudioFlingerDeviceHandle handle);

ssize_t  audioflinger_device_write(AudioFlingerDeviceHandle handle, 
    const void* buffer, size_t size);

void audioflinger_device_flush(AudioFlingerDeviceHandle handle);

void audioflinger_device_pause(AudioFlingerDeviceHandle handle);

void audioflinger_device_mute(AudioFlingerDeviceHandle handle, int mute);

int  audioflinger_device_muted(AudioFlingerDeviceHandle handle);

void audioflinger_device_set_volume(AudioFlingerDeviceHandle handle, 
    float left, float right);

int audioflinger_device_frameCount(AudioFlingerDeviceHandle handle);

int audioflinger_device_frameSize(AudioFlingerDeviceHandle handle);

int64_t audioflinger_device_latency(AudioFlingerDeviceHandle handle);

int audioflinger_device_format(AudioFlingerDeviceHandle handle);

int audioflinger_device_channelCount(AudioFlingerDeviceHandle handle);

uint32_t  audioflinger_device_sampleRate(AudioFlingerDeviceHandle handle);

#ifdef __cplusplus
}
#endif

#endif /* __AUDIOFLINGER_WRAPPER_H__ */
