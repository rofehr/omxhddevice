#ifndef tools_h
#define tools_h

#define ELOG(a...) esyslog("omxhddevice: " a)
#define ILOG(a...) isyslog("omxhddevice: " a)
#define DLOG(a...) dsyslog("omxhddevice: " a)


#ifdef DEBUG
#define DBG(a...)  dsyslog("omxhddevice: " a)
#else
#define DBG(a...)  void()
#endif


#define loge(fmt, arg...) 
#define logw(fmt, arg...) 
#define logi(fmt, arg...)
#define logd(fmt, arg...)
#define logv(fmt, arg...)


#endif
/* File EOF */

