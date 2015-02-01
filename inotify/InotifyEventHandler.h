#ifndef InotifyEventHandler_h
#define InotifyEventHandler_h

#include "InotifyEvent.h"

class InotifyEventHandler {

	public:
		virtual void handle(InotifyEvent &e) = 0;
};

#endif
