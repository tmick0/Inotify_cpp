#ifndef InotifyEvent_h
#define InotifyEvent_h

#include <cstdint>
#include <cstring>
#include <string>

class InotifyEvent;

#include "InotifyCommon.h"
#include "InotifyWatch.h"
#include "InotifyManager.h"

class InotifyEvent {
	friend class InotifyManager;

	private:
		InotifyManager* manager;
		InotifyWatch* watch;
		uint8_t buf[INOTIFY_MAX_SIZE];
		bool trigger();
		
	public:
		InotifyEvent(InotifyManager* man);
		InotifyWatch* getWatch();
		InotifyManager* getManager();
		uint32_t getFlags();
		std::string getName();
};

#endif
