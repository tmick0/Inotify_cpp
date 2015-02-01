#ifndef InotifyEvent_h
#define InotifyEvent_h

#include "InotifyCommon.h"
#include "InotifyWatch.h"
#include "InotifyManager.h"

#include <cstdint>
#include <string>

class InotifyEvent {
	private:
		InotifyManager& manager;
		InotifyWatch& watch;
		uint8_t buf[INOTIFY_MAX_SIZE];
	public:
		InotifyEvent(InotifyManager& man, InotifyWatch& watch);
		InotifyWatch& getWatch();
		InotifyManager& getManager();
		uint32_t getFlags();
		std::string getName();
};

#endif
