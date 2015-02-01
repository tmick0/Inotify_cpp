#include "InotifyEvent.h"
#include "InotifyException.h"

#include <sys/inotify.h>

InotifyEvent::InotifyEvent(InotifyManager* man)
	: manager(man),
	  watch(0)
{

}

InotifyWatch *InotifyEvent::getWatch(){
	return watch;
}

InotifyManager *InotifyEvent::getManager(){
	return manager;
}

bool InotifyEvent::trigger(){
	bool ret = false;
	if(!watch){
		throw new InotifyException("an InotifyEvent has been orphaned by its Watch");
	}
	else{
		ret = watch->event(*this);
	}
	return ret;
}

uint32_t InotifyEvent::getFlags(){
	struct inotify_event *e = (struct inotify_event *) buf;
	return e->mask;
}

std::string InotifyEvent::getName(){
	struct inotify_event *e = (struct inotify_event *) buf;
	if(e->len){
		return std::string(e->name);
	}
	else{
		return std::string("");
	}
}
