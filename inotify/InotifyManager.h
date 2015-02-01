#ifndef InotifyManager_h
#define InotifyManager_h

class InotifyManager;

#include "InotifyWatch.h"
#include <set>

class InotifyManager {

	friend class InotifyWatch;
	
	private:
		int                     fd;
		std::set<InotifyWatch*> watchSet;
		
	public:
		InotifyManager();
		~InotifyManager();
		InotifyWatch* addWatch(std::string path, uint32_t flags);
};

#endif
