NOTIFY_LIB=inotify_cpp.a
NOTIFY_APP=inotifier

LIB_SRC=$(wildcard inotify/*.cpp)
APP_SRC=$(wildcard app/*.cpp)

all: $(NOTIFY_LIB) $(NOTIFY_APP)

$(NOTIFY_LIB): inotify/Makefile $(LIB_SRC)
	$(MAKE) -C inotify
	
$(NOTIFY_APP): app/Makefile $(NOTIFY_LIB) $(APP_SRC)
	$(MAKE) -C app
	
clean: 
	$(MAKE) -C inotify clean
	$(MAKE) -C app clean
