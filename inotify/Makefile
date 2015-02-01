CXX=g++
CXXFLAGS=-g -Wall -Wpedantic -Werror -std=c++11

SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
OUTPUT=../inotify_cpp.a

all: $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	ar cr $@ $(OBJECTS)
	
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
clean:
	rm -f $(OUTPUT) $(OBJECTS)
