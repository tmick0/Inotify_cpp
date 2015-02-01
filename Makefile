NOTIFY_LIB=inotify_cpp.a
NOTIFY_APP=inotifier

all: $(NOTIFY_LIB) $(NOTIFY_APP)

$(NOTIFY_LIB): inotify/Makefile
	$(MAKE) -C inotify
	
$(NOTIFY_APP): app/Makefile
	$(MAKE) -C app
	
clean: 
	$(MAKE) -C inotify clean
	$(MAKE) -C app clean
