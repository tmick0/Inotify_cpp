#ifndef InotifyManager_h
#define InotifyManager_h

class InotifyManager;

#include "InotifyWatch.h"
#include <thread>
#include <map>

/** InotifyManager is the main interface to the inotify API. It handles the
	creation of watches and handling of events.
*/
class InotifyManager {

	friend class InotifyWatch;
	
	private:
		int fd;
		std::map<int, InotifyWatch*> watchSet;
		
		/**	This function, which should be started in its own thread, will
			wait for events to be registered on the underlying inotify file
			descriptor and create corresponding InotifyEvent objects for them.
			It is also responsible for triggering the event handlers for those
			events.
			@param m A reference to the InotifyManager to handle events for
		*/
		static void readLoop(InotifyManager *m);
		
	public:
		/** Default constructor. Intializes the inotify file descriptor. */
		InotifyManager();
		
		/** Destructor. Cleans up all of our InotifyWatches and closes the
			inotify file desctiptor.
		*/
		~InotifyManager();
		
		/** Creates an InotifyWatch on the specified path, for events specified
			in the flags mask.
			@param path File or directory to watch for events
			@param flags Bit mask specifying which events to watch for
			@return Pointer to the created InotifyWatch object
		*/
		InotifyWatch* addWatch(std::string path, uint32_t flags);
		
		/** Starts the thread which waits for events to occur and handles them.
			@return The descriptor of the thread running the readLoop
		*/
		std::thread startWatching();
};

#endif
