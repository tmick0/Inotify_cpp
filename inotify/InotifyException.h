#ifndef InotifyException_h
#define InotifyException_h

#include <stdexcept>

class InotifyException : public std::runtime_error {
	public:
		InotifyException(std::string m) : std::runtime_error(m) { }
		
};

#endif
