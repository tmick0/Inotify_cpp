#ifndef InotifyManager_h
#define InotifyManager_h

class InotifyManager;

#include "InotifyWatch.h"
#include <thread>
#include <map>

class InotifyManager {

	friend class InotifyWatch;
	
	private:
		int fd;
		std::map<int, InotifyWatch*> watchSet;
		static void readLoop(InotifyManager *m);
		
	public:
		InotifyManager();
		~InotifyManager();
		InotifyWatch* addWatch(std::string path, uint32_t flags);
		std::thread startWatching();
};

#endif
