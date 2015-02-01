#include "InotifyManager.h"
#include "InotifyException.h"
#include "InotifyCommon.h"
#include "InotifyEvent.h"

#include <sys/inotify.h>
#include <unistd.h>

InotifyManager::InotifyManager(){
	fd = inotify_init();
	if(fd == -1){
		throw InotifyException("Could not create inotify file descriptor");
	}
}

InotifyManager::~InotifyManager(){
	/* Delete our InotifyWatches */
	std::map<int,InotifyWatch*>::iterator it;
	for(it = watchSet.begin(); it != watchSet.end(); it++){
		delete it->second;
	}
	watchSet.clear();

	/* Close inotify fd */
	if(fd != -1 && close(this->fd)){
		char errstr[INOTIFY_ERR_LEN];
		INOTIFY_ERR_MSG("close", errstr, INOTIFY_ERR_LEN);
		throw InotifyException(errstr);
	}
}

InotifyWatch* InotifyManager::addWatch(std::string path, uint32_t flags){
	InotifyWatch* w = new InotifyWatch(*this, path, flags);
	watchSet.insert(std::pair<int,InotifyWatch*>(w->wd, w));
	return w;
}

void InotifyManager::readLoop(InotifyManager *m){
	uint32_t n;
	InotifyEvent *e = new InotifyEvent(m);
	
	while(e && (n = read(m->fd, e->buf, INOTIFY_MAX_SIZE)) > 0){
		struct inotify_event *es = (struct inotify_event *) e->buf;
		bool term = false;
		
		e->watch = m->watchSet[es->wd];
		term = e->trigger();
		
		delete e;
		
		if(!term)
			e = new InotifyEvent(m);
		else
			e = 0;
	}
}

std::thread InotifyManager::startWatching(){
	std::thread t(readLoop, this);
	return t;
}
