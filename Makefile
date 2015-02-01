NOTIFY_LIB=inotify_cpp.a
NOTIFY_APP=inotifier

DOXYGEN=doxygen
LIB_SRC=$(wildcard inotify/*.cpp)
APP_SRC=$(wildcard app/*.cpp)

all: $(NOTIFY_LIB) $(NOTIFY_APP)

$(NOTIFY_LIB): inotify/Makefile $(LIB_SRC)
	$(MAKE) -C inotify
	
$(NOTIFY_APP): app/Makefile $(NOTIFY_LIB) $(APP_SRC)
	$(MAKE) -C app
	
docs: Doxyfile
	mkdir -p docs
	$(DOXYGEN)
	
clean: 
	$(MAKE) -C inotify clean
	$(MAKE) -C app clean
	rm -rf docs
