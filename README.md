# Inotify_cpp
A set of C++ classes encapsulating the functionality of the C-language inotify library

Inotify_cpp creates an event-driven interface to the Linux inotify API, allowing a developer to hook into filesystem events without the hassle of implementing a read-handle loop or directly manipulating file descriptors.

Instead, monitoring a filesystem is as easy as writing an event handler and attaching it to a watch.

## Current features:
Inotify_cpp currently implements all functionality provided by the standard C API with the following exceptions:

* Cookie handling for move/rename events is not yet present
* Watches cannot yet be removed or modified

The primary advantage of of Inotify_cpp over the standard inotify API is its event-driven interface.

## Planned features:
Inotify_cpp will provide all the functionality of inotify, with several additions:

* Simple event checking without manipulating flags
* Abstraction of the IN_MOVED_FROM/IN_MOVED_TO events' cookie
* Inherent support for recursive watches
* Warning events when approaching limit for number of watches

## Usage:
This repository contains both the Inotify_cpp library and an example application. For ease of reference, this is the implementation of the example application:

    #include <iostream>
    #include <thread>
    #include "InotifyManager.h"
    using namespace std;

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
    
The application provided in this repository will soon be extended to provide a simple configurable interface to inotify, allowing arbitrary commands to be run when filesystem events occur.