#ifndef InotifyEvent_h
#define InotifyEvent_h

#include <cstdint>
#include <cstring>
#include <string>

class InotifyEvent;

#include "InotifyCommon.h"
#include "InotifyWatch.h"
#include "InotifyManager.h"

/** Represents an event detected by the inotify API */
class InotifyEvent {
	friend class InotifyManager;

	private:
		InotifyManager* manager;
		InotifyWatch* watch;
		uint8_t buf[INOTIFY_MAX_SIZE];
		
		/** Notifies the relevant InotifyWatch that this event has occurred
			@return True if the event handler requests for the InotifyManager to
					stop listening for events
		*/
		bool trigger();
		
	public:
		/** Constructs an InotifyEvent with a reference to its parent
			InotifyManager object.
			@param man The InotifyManager which maintains this InotifyEvent
		*/
		InotifyEvent(InotifyManager* man);
		
		/** Retrieves a pointer to the InotifyWatch which generated this
			InotifyEvent.
			@return Pointer to an InotifyWatch
		*/
		InotifyWatch* getWatch();
		
		/** Retrieves a pointer to the InotifyManager which mainains this
			InotifyEvent.
			@return Pointer to an InotifyManager
		*/
		InotifyManager* getManager();
		
		/** Returns the mask field of the underlying inotify_event structure 
			@return A bitmask indicating the type of event which occurred
		*/
		uint32_t getFlags();
		
		/** Returns the name of the file for which an event occurred
			@return The name of the file which this event pertains to
		*/
		std::string getName();
};

#endif
