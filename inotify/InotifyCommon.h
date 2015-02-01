#ifndef InotifyCommon_h
#define InotifyCommon_h

#include <cstring>
#include <climits>
#include <sys/inotify.h>

/** Size of a simple inotify_event structure */
#define INOTIFY_MIN_SIZE sizeof(struct inotify_event)

/** Size of an inotify_event structure with the maximum possible length of the
	name field.
*/
#define INOTIFY_MAX_SIZE (INOTIFY_MIN_SIZE + NAME_MAX + 1)

/** Size of buffer allocated when preparing an error message */
#define INOTIFY_ERR_LEN 128

/** Macro to concatenate a context message and appropriate description of the
	current errno into a specified character buffer.
*/
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
