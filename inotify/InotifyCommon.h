#ifndef InotifyCommon_h
#define InotifyCommon_h

#include <cstring>
#include <climits>
#include <sys/inotify.h>

#define INOTIFY_MIN_SIZE sizeof(struct inotify_event)
#define INOTIFY_MAX_SIZE (INOTIFY_MIN_SIZE + NAME_MAX + 1)

#define INOTIFY_ERR_LEN 128
#define INOTIFY_ERR_MSG(ctx, buf, buflen) { 								\
					int    e = errno;										\
					size_t l = strlen(ctx);									\
					strncpy(buf, ctx, buflen);								\
					if(l < buflen) {										\
						strncpy(buf + l, ": ", buflen - l);					\
						strncpy(buf + l + 2, strerror(e), buflen - l - 2);	\
					}														\
		 }

#endif
