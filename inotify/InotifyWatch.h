#ifndef InotifyWatch_h
#define InotifyWatch_h

#include <string>
#include <cstdint>
#include <set>

class InotifyWatch;

#include "InotifyManager.h"
#include "InotifyEventHandler.h"

class InotifyWatch {

	friend class InotifyManager;

	private:
		InotifyManager& man;
		std::string path;
		uint32_t flags;
		int wd;
		std::set<InotifyEventHandler*> handlers;
		
		void init();
		void event(InotifyEvent& e);
	
	public:
		/* constructors */
		InotifyWatch(InotifyManager& m, std::string p, uint32_t f);
		
		/* destructor */
		~InotifyWatch();
		
		/* modifiers */
		void addEventHandler(InotifyEventHandler &h);
		
};

#endif
