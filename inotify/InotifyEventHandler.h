#ifndef InotifyEventHandler_h
#define InotifyEventHandler_h

#include "InotifyEvent.h"

/** Interface for event handlers */
class InotifyEventHandler {
	public:
		/** This function will be called by the InotifyWatch when an event
			occurs.
			@param e A reference to the event that occurred
			@return  True if you request that the InotifyManager stop listening
					 for events
		*/
		virtual bool handle(InotifyEvent &e) = 0;
};

#endif
