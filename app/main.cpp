#include <iostream>
#include <thread>

#include "InotifyManager.h"

using namespace std;

/** A simple implementation of the InotifyEventHandler interface for the demo
	application. It will print the name and type of each event it receives, then
	ask the InotifyManager to terminate after the 5th event.
*/
class MyEventHandler : public InotifyEventHandler {
private:
	int eventCount = 0;
public:
	bool handle(InotifyEvent &e){
		string t;
		
		if(e.getFlags() & IN_CREATE)
			t = string("creation");
		else if(e.getFlags() & IN_DELETE)
			t = string("deletion");
		else
			t = string("unknown");
			
		cout << "An event occurred!" << endl;
		cout << " * Name : " << e.getName() << endl;
		cout << " * Type : " << t << endl;
		cout << endl;
		
		if(++eventCount == 5)
			return true;
		return false;
	}
};

/**	The directory specified in the first command line argument will be watched
	for creation and deletion events. Each event will be handled by the
	MyEventHandler class.
*/
int main(int argc, char *argv[]){

	if(argc != 2){
		cerr << "Please specify a directory to watch." << endl;
		cerr << "usage: " << argv[0] << " <directory_path>" << endl;
		return 1;
	}
	
	InotifyManager m;
	MyEventHandler h;
	InotifyWatch  *w = m.addWatch(argv[1], IN_CREATE | IN_DELETE);

	w->addEventHandler(h);
	
	thread t = m.startWatching();
	t.join();
	
	return 0;
}
