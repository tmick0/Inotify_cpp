#ifndef InotifyWatch_h
#define InotifyWatch_h

#include <string>
#include <cstdint>
#include <set>

class InotifyWatch;

#include "InotifyManager.h"
#include "InotifyEventHandler.h"

/** An InotifyWatch monitors a specified file or directory for changes and
	manages the handlers for those events
*/
class InotifyWatch {

	friend class InotifyManager;
	friend class InotifyEvent;

	private:
		InotifyManager& man;
		std::string path;
		uint32_t flags;
		int wd;
		std::set<InotifyEventHandler*> handlers;
		
		/** Standard constructor: should only be called by InotifyManager
			@param m Reference to the InotifyManager which manages this watch
			@param p The path of the file or directory to monitor
			@param f The mask of events to listen for
		*/
		InotifyWatch(InotifyManager& m, std::string p, uint32_t f);
		
		/** Calls the underlying inotify_add_watch method in order for us to
			start receiving events.
		*/
		void init();
		
		/** Handles the incoming event related to this watch and calls any
			associated handlers.
			@param Reference to the InotifyEvent detected by the InotifyManager
			@return True if one of the InotifyEventHandlers requested for the
					InotifyManager to terminate.
		*/
		bool event(InotifyEvent& e);
	
	public:
		
		/** Destructor: Removes this watch from the underlying inotify API */
		~InotifyWatch();
		
		/** Adds the specified event handler to the list of callbacks to
			execute when this watch is triggered.
			@param h Reference to an object implementing the 
					 InotifyEventHandler interface.
		*/
		void addEventHandler(InotifyEventHandler &h);
		
};

#endif
