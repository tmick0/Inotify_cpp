CXX=g++
CXXFLAGS=-g -Wall -Wpedantic -Werror -std=c++11 -I../inotify
LDFLAGS=-lpthread

SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
OUTPUT=../inotifier
INOTIFY=../inotify_cpp.a

all: $(OUTPUT)

$(OUTPUT): $(INOTIFY) $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(INOTIFY) $(LDFLAGS)
	
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
$(INOTIFY): ../inotify/Makefile
	$(MAKE) -C ../inotify $(INOTIFY)
	
clean:
	rm -f $(OUTPUT) $(OBJECTS)
