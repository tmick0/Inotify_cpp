#include "InotifyManager.h"
#include "InotifyException.h"
#include "InotifyCommon.h"

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
	std::set<InotifyWatch*>::iterator it;
	for(it = watchSet.begin(); it != watchSet.end(); it++){
		delete *it;
	}
	watchSet.clear();

	/* Close inotify fd */
	if(fd != -1 && close(this->fd)){
		char errstr[INOTIFY_ERR_LEN];
		INOTIFY_ERR_MSG("close", errstr, INOTIFY_ERR_LEN);
		throw InotifyException(errstr);
	}
	fd = -1;
}

InotifyWatch* InotifyManager::addWatch(std::string path, uint32_t flags){
	InotifyWatch* w = new InotifyWatch(*this, path, flags);
	watchSet.insert(w);
	return w;
}

