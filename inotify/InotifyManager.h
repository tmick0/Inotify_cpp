#ifndef InotifyManager_h
#define InotifyManager_h

class InotifyManager;

#include "InotifyWatch.h"
#include <map>

class InotifyManager {

	friend class InotifyWatch;
	
	private:
		int fd;
		std::map<int, InotifyWatch*> watchSet;
		
	public:
		InotifyManager();
		~InotifyManager();
		InotifyWatch* addWatch(std::string path, uint32_t flags);
		InotifyWatch  startWatching();
};

#endif
