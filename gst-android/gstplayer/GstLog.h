/* Remove the full path before file name. All android code build from top
 * folder, like .../external/gst-plugin-android/player/GstPlayer.cpp, which
 * make log too long. 
 */
#define  GST_PLAYER_GET_SHORT_FILENAME(longfilename)   \
    ( (strrchr(longfilename, '/')==NULL) ? \
        longfilename: ((char*)(strrchr(longfilename, '/')+1)))

#ifdef ENABLE_GST_PLAYER_LOG

/* TODO: remove GST_PLAYER_TEMP_LOG later */
#ifdef GST_PLAYER_TEMP_LOG

/* redirect log to stdio */
#define TRACE(fmt, args... )  \
    printf("TRACE: %s:%d, %s(): "fmt, \
        GST_PLAYER_GET_SHORT_FILENAME(__FILE__), __LINE__, __FUNCTION__, ##args)

#define GST_PLAYER_ERROR(fmt, args...)      TRACE(fmt,##args)
#define GST_PLAYER_WARNING(fmt, args...)    TRACE(fmt,##args)
#define GST_PLAYER_INFO(fmt, args...)       TRACE(fmt,##args)
#define GST_PLAYER_DEBUG(fmt, args...)      TRACE(fmt,##args)
#define GST_PLAYER_LOG(fmt, args...)        TRACE(fmt,##args)

#define GST_ERROR_ANDROID(fmt, args...)     printf(fmt,##args)                         
#define GST_WARNING_ANDROID(fmt, args...)   printf(fmt,##args)                         
#define GST_INFO_ANDROID(fmt, args...)      printf(fmt,##args)                         
#define GST_DEBUG_ANDROID(fmt, args...)     printf(fmt,##args)                         
#define GST_LOG_ANDROID(fmt, args...)       printf(fmt,##args)                         

#else /* GST_PLAYER_TEMP_LOG */
#define LOG_TAG "GstPlayer"

#define GST_PLAYER_ERROR(fmt, args...)      \
    LOGE("[%d], ERROR   %s:%d, %s(): "fmt,           \
        gettid(), GST_PLAYER_GET_SHORT_FILENAME(__FILE__), __LINE__, __FUNCTION__, ##args)                         
#define GST_PLAYER_WARNING(fmt, args...)    \
    LOGW("[%d], WARNING   %s:%d, %s(): "fmt,           \
        gettid(), GST_PLAYER_GET_SHORT_FILENAME(__FILE__), __LINE__, __FUNCTION__, ##args)                             
#define GST_PLAYER_INFO(fmt, args...)       \
    LOGI("[%d], INFO   %s:%d, %s(): "fmt,           \
        gettid(), GST_PLAYER_GET_SHORT_FILENAME(__FILE__), __LINE__, __FUNCTION__, ##args)                              
#define GST_PLAYER_DEBUG(fmt, args...)      \
    LOGD("[%d], DEBUG   %s:%d, %s(): "fmt,           \
        gettid(), GST_PLAYER_GET_SHORT_FILENAME(__FILE__), __LINE__, __FUNCTION__, ##args)                              
#define GST_PLAYER_LOG(fmt, args...)        \
    LOGV("[%d], LOG   %s:%d, %s(): "fmt,           \
        gettid(), GST_PLAYER_GET_SHORT_FILENAME(__FILE__), __LINE__, __FUNCTION__, ##args)                         

#define GST_ERROR_ANDROID(fmt, args...)      LOGE(fmt,##args)                         
#define GST_WARNING_ANDROID(fmt, args...)    LOGW(fmt,##args)                         
#define GST_INFO_ANDROID(fmt, args...)       LOGI(fmt,##args)                         
#define GST_DEBUG_ANDROID(fmt, args...)      LOGD(fmt,##args)                         
#define GST_LOG_ANDROID(fmt, args...)        LOGV(fmt,##args) 
#endif

#else /* ENABLE_GST_PLAYER_LOG */

#define GST_PLAYER_ERROR(fmt, args...) 
#define GST_PLAYER_WARNING(fmt, args...) 
#define GST_PLAYER_INFO(fmt, args...)
#define GST_PLAYER_DEBUG(fmt, args...) 
#define GST_PLAYER_LOG(fmt, args...) 

#endif /* ENABLE_GST_PLAYER_LOG */


