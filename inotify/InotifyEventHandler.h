#ifndef InotifyEventHandler_h
#define InotifyEventHandler_h

#include "InotifyEvent.h"

class InotifyEventHandler {

	public:
		virtual bool handle(InotifyEvent &e) = 0;
};

#endif
