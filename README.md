gstreamer-ducati
================

This is a gstreamer project for android (include the ducati plugin).


1) How to build 

I:  Copy the source code into android/external dir.
II: build with Android.mk by use mm command. 

2) How to use the ducati plugin.

I:   adb push ducati-img/dce_app_m3.xem3 /data/
II:  adb push ducati-img/Notify_MPUSYS_reroute_Test_Core0.xem3 /data/
III: modify init.omap4430.rc 

#Load IVA firmware
#service baseimage /system/bin/syslink_daemon.out -f /data/base_image_sys_m3.xem3 /data/base_image_app_m3.xem3
service baseimage /system/bin/syslink_daemon.out -f /data/Notify_MPUSYS_reroute_Test_Core0.xem3 /data/dce_app_m3.xem3
    #critical
    user media
    group media





lib version:

libiconv                1.13.1
glib                    2.28
libid3tag               0.15.1
faad                    2.7
libmms                  0.6.2
libsoup                 2.29.3
libmad                  0.15.1
libogg                  1.2.0
orc                     0.4.14
gstreamer               0.10.35
gst-plugins-base        0.10.35
gst-plugins-good        0.10.30
gst-plugins-bad         0.10.22
gst-plugins-ugly        0.10.18
gst-ffmpeg              0.10.12

