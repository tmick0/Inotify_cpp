#include "InotifyWatch.h"
#include "InotifyException.h"
#include <sys/inotify.h>

InotifyWatch::InotifyWatch(InotifyManager& m, std::string p, uint32_t f)
	: man  (m),
	  path (p),
	  flags(f)
{
	init();
}

InotifyWatch::~InotifyWatch(){
	int r;
	r = inotify_rm_watch(man.fd, wd);
	if(r == -1){
		char errstr[INOTIFY_ERR_LEN];
		INOTIFY_ERR_MSG("inotify_rm_watch", errstr, INOTIFY_ERR_LEN);
		throw InotifyException(errstr);
	}
}

void InotifyWatch::init(){
	wd = inotify_add_watch(man.fd, path.c_str(), flags);
	if(wd == -1){
		char errstr[INOTIFY_ERR_LEN];
		INOTIFY_ERR_MSG("inotify_add_watch", errstr, INOTIFY_ERR_LEN);
		throw InotifyException(errstr);
	}
}

bool InotifyWatch::event(InotifyEvent& e){
	std::set<InotifyEventHandler *>::iterator it;
	bool term = false;
	for(it = handlers.begin(); it != handlers.end(); it++){
		bool r = (*it)->handle(e);
		term = term ? term : r;
	}
	return term;
}

void InotifyWatch::addEventHandler(InotifyEventHandler &h){
	handlers.insert(&h);
}

