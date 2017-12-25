#ifndef  POLYSORT_EXCEPTION_HPP_
#define  POLYSORT_EXCEPTION_HPP_

#include <exception>
#include <string>

class polysort_exception : std::exception {

public:
	polysort_exception(const std::string& message) : message_(message) {
	}

	const char* what() const noexcept override {
		
		return message_.c_str();
	};

private:
	const std::string message_;
};

#endif