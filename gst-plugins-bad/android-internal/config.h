/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* Default audio sink */
#define DEFAULT_AUDIOSINK "autoaudiosink"

/* Default audio source */
#define DEFAULT_AUDIOSRC "alsasrc"

/* Default video sink */
#define DEFAULT_VIDEOSINK "autovideosink"

/* Default video source */
#define DEFAULT_VIDEOSRC "v4l2src"

/* Default visualizer */
#define DEFAULT_VISUALIZER "goom"

/* Disable Orc */
/* #undef DISABLE_ORC */

/* Define if an old libdts is used */
/* #undef DTS_OLD */

/* Define to 1 if translation of program messages to the user's native
   language is requested. */
/* #undef ENABLE_NLS */

/* The x in 2.x */
#define FAAD2_MINOR_VERSION  7

/* Define if AAC is using new api prefix */
/*add by Tony for faad2  */

#define FAAD_IS_NEAAC 1

/* gettext package name */
#define GETTEXT_PACKAGE "NULL"

/* Define if GSM header in gsm/ subdir */
/* #undef GSM_HEADER_IN_SUBDIR */

/* Extra platform specific plugin suffix */
/* #undef GST_EXTRA_MODULE_SUFFIX */

/* Defined if gcov is enabled to force a rebuild due to config.h changing */
/* #undef GST_GCOV_ENABLED */

/* Defined when registry scanning through fork is unsafe */
/* #undef GST_HAVE_UNSAFE_FORK */

/* Default errorlevel to use */
#define GST_LEVEL_DEFAULT GST_LEVEL_ERROR

/* GStreamer license */
#define GST_LICENSE "LGPL"

/* mjpegtools API evolution */
#define GST_MJPEGTOOLS_API 0

/* package name in plugins */
#define GST_PACKAGE_NAME "GStreamer Bad Plug-ins git"

/* package origin */
#define GST_PACKAGE_ORIGIN "Unknown package origin"

/* GStreamer package release date/time for plugins as YYYY-MM-DD */
#define GST_PACKAGE_RELEASE_DATETIME "2011-08-16T02:39Z"

/* Define to enable Windows ACM library (used by acm). */
/* #undef HAVE_ACM */

/* Define to enable AirPort Express Wireless sink (used by apexsink). */
#define HAVE_APEXSINK /**/

/* Define to enable Apple video (used by applemedia). */
/* #undef HAVE_APPLE_MEDIA */

/* Define to enable ASS/SSA renderer (used by assrender). */
/* #undef HAVE_ASSRENDER */

/* Define to enable AVC Video Services (used by avcsrc). */
/* #undef HAVE_AVC */

/* Define to enable bz2 library (used by bz2). */
/* #undef HAVE_BZ2 */

/* Define to enable cdaudio (used by cdaudio). */
/* #undef HAVE_CDAUDIO */

/* Define to enable celt (used by celt). */
/* #undef HAVE_CELT */

/* Define if libcelt 0.11 is installed */
/* #undef HAVE_CELT_0_11 */

/* Define if libcelt 0.7 is installed */
/* #undef HAVE_CELT_0_7 */

/* Define if libcelt 0.8 is installed */
/* #undef HAVE_CELT_0_8 */

/* Define to 1 if you have the MacOS X function CFLocaleCopyCurrent in the
   CoreFoundation framework. */
/* #undef HAVE_CFLOCALECOPYCURRENT */

/* Define to 1 if you have the MacOS X function CFPreferencesCopyAppValue in
   the CoreFoundation framework. */
/* #undef HAVE_CFPREFERENCESCOPYAPPVALUE */

/* Define to enable Cog plugin (used by cog). */
#define HAVE_COG /**/

/* Define if the host CPU is an Alpha */
/* #undef HAVE_CPU_ALPHA */

/* Define if the host CPU is an ARM */
#define HAVE_CPU_ARM 1

/* Define if the host CPU is a CRIS */
/* #undef HAVE_CPU_CRIS */

/* Define if the host CPU is a CRISv32 */
/* #undef HAVE_CPU_CRISV32 */

/* Define if the host CPU is a HPPA */
/* #undef HAVE_CPU_HPPA */

/* Define if the host CPU is an x86 */
/* #undef HAVE_CPU_I386 */

/* Define if the host CPU is a IA64 */
/* #undef HAVE_CPU_IA64 */

/* Define if the host CPU is a M68K */
/* #undef HAVE_CPU_M68K */

/* Define if the host CPU is a MIPS */
/* #undef HAVE_CPU_MIPS */

/* Define if the host CPU is a PowerPC */
/* #undef HAVE_CPU_PPC */

/* Define if the host CPU is a 64 bit PowerPC */
/* #undef HAVE_CPU_PPC64 */

/* Define if the host CPU is a S390 */
/* #undef HAVE_CPU_S390 */

/* Define if the host CPU is a SPARC */
/* #undef HAVE_CPU_SPARC */

/* Define if the host CPU is a x86_64 */
/* #undef HAVE_CPU_X86_64 */

/* Define to enable Curl plugin (used by curl). */
/* #undef HAVE_CURL */

/* Define to enable libdc1394 (used by dc1394). */
/* #undef HAVE_DC1394 */

/* Define if the GNU dcgettext() function is already present or preinstalled.
   */
/* #undef HAVE_DCGETTEXT */

/* Define to enable decklink (used by decklink). */
/* #undef HAVE_DECKLINK */

/* Define to enable dirac (used by dirac). */
/* #undef HAVE_DIRAC */

/* Define to enable Direct3D plug-in (used by direct3dsink). */
/* #undef HAVE_DIRECT3D */

/* Define to enable DirectDraw plug-in (used by directdrawsink). */
/* #undef HAVE_DIRECTDRAW */

/* Define to enable directfb (used by dfbvideosink ). */
/*#define HAVE_DIRECTFB */

/* Define to enable DirectSound (used by directsoundsrc). */
/* #undef HAVE_DIRECTSOUND */

/* Define to enable divx plugins (used by divx). */
/* #undef HAVE_DIVX */

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* define for working do while(0) macros */
#define HAVE_DOWHILE_MACROS 1

/* Define to enable dts library (used by dtsdec). */
/* #undef HAVE_DTS */

/* Define to enable DVB Source (used by dvb). */
/* #undef HAVE_DVB */

/* Define to enable building of experimental plug-ins. */
/* #undef HAVE_EXPERIMENTAL */

/* Define to enable building of plug-ins with external deps. */
#define HAVE_EXTERNAL /**/

/* Define to enable AAC encoder plug-in (used by faac). */
/* #undef HAVE_FAAC */
#define HAVE_FAAC 1

/* Define to enable AAC decoder plug-in (used by faad). */
/* #undef HAVE_FAAD */
#define HAVE_FAAD 1
/* Define to enable linux framebuffer (used by fbdevsink). */
#define HAVE_FBDEV /**/

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* FIONREAD ioctl found in sys/filio.h */
/* #undef HAVE_FIONREAD_IN_SYS_FILIO */

/* FIONREAD ioctl found in sys/ioclt.h */
#define HAVE_FIONREAD_IN_SYS_IOCTL 1

/* Define to enable Flite plugin (used by flite). */
/* #undef HAVE_FLITE */

/* Define to 1 if you have the `getpagesize' function. */
#define HAVE_GETPAGESIZE 1

/* Define if the GNU gettext() function is already present or preinstalled. */
/* #undef HAVE_GETTEXT */

/* Define to enable gme decoder (used by gme). */
/* #undef HAVE_GME */

/* Define to 1 if you have the `gmtime_r' function. */
#define HAVE_GMTIME_R 1

/* Define to enable GSettings plugin (used by gsettings). */
/* #undef HAVE_GSETTINGS */

/* Define to enable GSM library (used by gsmenc gsmdec). */
/* #undef HAVE_GSM */

/* Define if you have the iconv() function and it works. */
#define HAVE_ICONV 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define if building for Apple iOS */
/* #undef HAVE_IOS */

/* Define to enable jp2k (used by jp2kdec jp2kenc). */
/* #undef HAVE_JP2K */

/* Define to enable Kate (used by kate). */
/* #undef HAVE_KATE */

/* Define to enable ladspa (used by ladspa). */
/* #undef HAVE_LADSPA */

/* Define to 1 if you have the `divxdecore' library (-ldivxdecore). */
/* #undef HAVE_LIBDIVXDECORE */

/* Define to 1 if you have the `divxencore' library (-ldivxencore). */
/* #undef HAVE_LIBDIVXENCORE */

/* Define if gme 0.5.6 or newer is available */
/* #undef HAVE_LIBGME_ACCURACY */

/* Define to enable mms protocol library (used by libmms). */
#define HAVE_LIBMMS 1

/* Define to 1 if you have the `nsl' library (-lnsl). */
/* #undef HAVE_LIBNSL */

/* Define to 1 if you have the `socket' library (-lsocket). */
/* #undef HAVE_LIBSOCKET */

/* Define to enable Linear Systems SDI plugin (used by linsys). */
/* #undef HAVE_LINSYS */

/* Define if we have liblrdf */
/* #undef HAVE_LRDF */

/* Define to enable lv2 (used by lv2). */
/* #undef HAVE_LV2 */

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to enable libmimic library (used by mimic). */
/* #undef HAVE_MIMIC */

/* Define to 1 if you have a working `mmap' system call. */
#define HAVE_MMAP 1

/* Define to enable modplug (used by modplug). */
/* #undef HAVE_MODPLUG */

/* Define to enable mpeg2enc (used by mpeg2enc). */
/* #undef HAVE_MPEG2ENC */

/* Define to enable mplex (used by mplex). */
/* #undef HAVE_MPLEX */

/* Define to 1 if you have the <msacm.h> header file. */
/* #undef HAVE_MSACM_H */

/* Define to enable musepackdec (used by musepack). */
/* #undef HAVE_MUSEPACK */

/* Define to enable musicbrainz tag generation (used by musicbrainz). */
/* #undef HAVE_MUSICBRAINZ */

/* Define to enable MythTV client plugins (used by mythtvsrc). */
/* #undef HAVE_MYTHTV */

/* Define to enable nas plug-in (used by nassink). */
/* #undef HAVE_NAS */

/* Define to enable neon http client plugins (used by neonhttpsrc). */
#define HAVE_NEON 1

/* Define to 1 if you have the <netinet/in.h> header file. */
#define HAVE_NETINET_IN_H 1

/* Define to 1 if you have the <netinet/ip.h> header file. */
#define HAVE_NETINET_IP_H 1

/* Define to 1 if you have the <netinet/tcp.h> header file. */
#define HAVE_NETINET_TCP_H 1

/* Define to enable ofa plugins (used by ofa). */
/* #undef HAVE_OFA */

/* Define to enable OpenAL plugin (used by openal). */
/* #undef HAVE_OPENAL */

/* Define to enable opencv plugins (used by opencv). */
/* #undef HAVE_OPENCV */

/* Define to enable opus (used by opus). */
/* #undef HAVE_OPUS */

/* Use Orc */
#define HAVE_ORC 1

/* Defined if compiling for OSX */
/* #undef HAVE_OSX */

/* Define to enable OSX video (used by osxvideosrc). */
/* #undef HAVE_OSX_VIDEO */

/* Define to 1 if you have the <pthread.h> header file. */
#define HAVE_PTHREAD_H 1

/* Define to enable QuickTime wrapper (used by qtwrapper). */
/* #undef HAVE_QUICKTIME */

/* Define if RDTSC is available */
#define HAVE_RDTSC 1

/* Define to enable resindvd plugin (used by resindvd). */
/* #undef HAVE_RESINDVD */

/* Define to enable rsvg decoder (used by rsvg). */
/* #undef HAVE_RSVG */

/* Define to enable rtmp library (used by rtmp). */
#define HAVE_RTMP 1

/* Define to enable Schroedinger video codec (used by schro). */
/* #undef HAVE_SCHRO */

/* Define to enable SDL plug-in (used by sdlvideosink sdlaudiosink). */

/* #undef HAVE_SDL */

/* Define to enable POSIX shared memory source and sink (used by shm). */
/* #undef HAVE_SHM */

/* Define to enable sndfile plug-in (used by sfsrc sfsink). */
/* #undef HAVE_SNDFILE */

/* Define to enable soundtouch plug-in (used by soundtouch). */
/* #undef HAVE_SOUNDTOUCH */

/* Defined if the available libSoundTouch is >= 1.4 */
/* #undef HAVE_SOUNDTOUCH_1_4 */

/* Define to enable spc decoder (used by spc). */
/* #undef HAVE_SPC */

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to enable swfdec plug-in (used by swfdec). */
/* #undef HAVE_SWFDEC */

/* Define to 1 if you have the <sys/param.h> header file. */
#define HAVE_SYS_PARAM_H 1

/* Define to 1 if you have the <sys/socket.h> header file. */
#define HAVE_SYS_SOCKET_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/time.h> header file. */
#define HAVE_SYS_TIME_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/utsname.h> header file. */
#define HAVE_SYS_UTSNAME_H 1

/* Define to enable Teletext decoder (used by teletextdec). */
/* #undef HAVE_TELETEXTDEC */

/* Define if libtiger is available */
/* #undef HAVE_TIGER */

/* Define to enable timidity midi soft synth plugin (used by timidity). */
/* #undef HAVE_TIMIDITY */

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define if valgrind should be used */
/* #undef HAVE_VALGRIND */

/* Define to enable Video CD (used by vcdsrc). */
#define HAVE_VCD /**/

/* Define to enable VDPAU (used by vdpau). */
/* #undef HAVE_VDPAU */

/* Define to enable vo-aacenc library (used by vo-aacenc). */
/* #undef HAVE_VOAACENC */

/* Define to enable vo-amrwbenc library (used by vo-amrwbenc). */
/* #undef HAVE_VOAMRWBENC */

/* Define to enable VP8 decoder (used by vp8). */
/* #undef HAVE_VP8 */

/* Defined if the VP8 decoder is available */
/* #undef HAVE_VP8_DECODER */

/* Defined if the VP8 encoder is available */
/* #undef HAVE_VP8_ENCODER */

/* Define to enable wildmidi midi soft synth plugin (used by wildmidi). */
/* #undef HAVE_WILDMIDI */

/* Have WildMidi 0.2.2 or earlier library */
/* #undef HAVE_WILDMIDI_0_2_2 */

/* Defined if compiling for Windows */
/* #undef HAVE_WIN32 */

/* Define to 1 if you have the <windows.h> header file. */
/* #undef HAVE_WINDOWS_H */

/* Define to enable Windows internet library (used by wininet). */
/* #undef HAVE_WININET */

/* Define to 1 if you have the <wininet.h> header file. */
/* #undef HAVE_WININET_H */

/* Define to 1 if you have the <winsock2.h> header file. */
/* #undef HAVE_WINSOCK2_H */

/* Define if you have X11 library */
/* #undef HAVE_X11 */
/* Define to enable xvid plugins (used by xvid). */
/* #undef HAVE_XVID */

/* Define to enable ZBar barcode detector (used by zbar). */
#define HAVE_ZLIB /**/

/* the host CPU */
#define HOST_CPU "arm"

/* library dir */
#define LIBDIR "/system/lib"

/* gettext locale dir */
#define LOCALEDIR "/system/share/locale"

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Define if the old MusePack API is used */
/* #undef MPC_IS_OLD_API */

/* Define to 1 if your C compiler doesn't accept -c and -o together. */
/* #undef NO_MINUS_C_MINUS_O */

/* Name of package */
#define PACKAGE "gst-plugins-bad"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "http://bugzilla.gnome.org/enter_bug.cgi?product=GStreamer"

/* Define to the full name of this package. */
#define PACKAGE_NAME "GStreamer Bad Plug-ins"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "GStreamer Bad Plug-ins 0.10.22.1"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "gst-plugins-bad"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "0.10.22.1"

/* directory where plugins are located */
#define PLUGINDIR "/usr/local/lib/gstreamer-0.10"

/* The size of `char', as computed by sizeof. */
/* #undef SIZEOF_CHAR */

/* The size of `int', as computed by sizeof. */
/* #undef SIZEOF_INT */

/* The size of `long', as computed by sizeof. */
/* #undef SIZEOF_LONG */

/* The size of `short', as computed by sizeof. */
/* #undef SIZEOF_SHORT */

/* The size of `void*', as computed by sizeof. */
/* #undef SIZEOF_VOIDP */

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define location of timidity.cfg */
/* #undef TIMIDITY_CFG */

/* Version number of package */
#define VERSION "0.10.22.1"

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
/* #  undef WORDS_BIGENDIAN */
# endif
#endif

/* Define to 1 if the X Window System is missing or not being used. */
/* #undef X_DISPLAY_MISSING */

/* We need at least WinXP SP2 for __stat64 */
/* #undef __MSVCRT_VERSION__ */
