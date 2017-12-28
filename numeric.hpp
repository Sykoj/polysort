#ifndef  NUMERIC_HPP_
#define  NUMERIC_HPP_


#include "abstract_cell.hpp"
#include "polysort_exception.hpp"
#include <ostream>
#include <string>

class numeric final : public polysort::abstract_cell {

public:
	explicit numeric(const std::string& value) : value_(parse(value)){
	}
	explicit numeric(std::string&& value) : value_(std::stoi(value)) {}

	std::unique_ptr<abstract_cell> clone() const override {

		return std::make_unique<numeric>(*this);
	}
	bool operator<(const abstract_cell& other) const override {

		return dynamic_cast<const numeric&>(other).value_ > value_;
	}
private:
	void print(std::ostream& output) const override {

		output << value_;
	}

	static int parse(const std::string& parsed) {

		int value;
		size_t pos;
		try {
			value = stoi(parsed, &pos);
		}
		catch (...) {
			throw polysort_exception("Numeric type: unable to parse string to int");
		}
		if (pos != parsed.size()) throw polysort_exception("Numeric type: unable to parse string to int");

		return value;
	}

	int value_;
};

#endif
