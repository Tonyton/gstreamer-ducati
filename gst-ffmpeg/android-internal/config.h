/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* Disable Orc */
/* #undef DISABLE_ORC */

/* Describes where the Libav libraries come from. */
#define FFMPEG_SOURCE "local snapshot"

/* Default errorlevel to use */
#define GST_LEVEL_DEFAULT GST_LEVEL_NONE

/* package name in plugins */
#define GST_PACKAGE_NAME "GStreamer FFMpeg source release"

/* package origin */
#define GST_PACKAGE_ORIGIN "Unknown package origin"

/* Define to 1 if you have the <avi.h> header file. */
#define HAVE_AVI_H 1

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

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Defined if building against uninstalled Libav source */
#define HAVE_FFMPEG_UNINSTALLED /**/

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Use Orc */
#define HAVE_ORC 1

/* Define if RDTSC is available */
/* #undef HAVE_RDTSC */

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define if valgrind should be used */
/* #undef HAVE_VALGRIND */

/* the host CPU */
#define HOST_CPU "arm"

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Define to 1 if your C compiler doesn't accept -c and -o together. */
/* #undef NO_MINUS_C_MINUS_O */

/* Name of package */
#define PACKAGE "gst-ffmpeg"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "http://bugzilla.gnome.org/enter_bug.cgi?product=GStreamer"

/* Define to the full name of this package. */
#define PACKAGE_NAME "GStreamer FFMpeg"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "GStreamer Libav 0.10.12"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "gst-ffmpeg"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "0.10.12"

/* directory where plugins are located */
#define PLUGINDIR "/system/plugins"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Version number of package */
#define VERSION "0.10.12"


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

/* Define if we build this package in Android */
#define BUILD_WITH_ANDROID 1 

