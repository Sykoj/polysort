#ifndef  NUMERIC_HPP_
#define  NUMERIC_HPP_


#include "cell_type.hpp"
#include "polysort_exception.hpp"
#include <ostream>
#include <string>

class numeric final : public polysort::cell_type {

public:
	explicit numeric(const std::string& value) : value_(parse(value)){
	}
	explicit numeric(std::string&& value) : value_(std::stoi(value)) {}

	std::unique_ptr<cell_type> clone() const override {

		return std::make_unique<numeric>(*this);
	}
	bool operator<(const cell_type& other) const override {

		return dynamic_cast<const numeric&>(other).value_ > value_;
	}
private:
	void print(std::ostream& output) const override {

		output << value_;
	}

	static int parse(const std::string& value) {

		if (value.size() == 0) throw polysort_exception("Numeric type: unable to parse empty string to int");
		int x;

		// stoi is simply ignoring bad non-digit characters after number, self-implementation:
		try {
			x = stoi(value);
		}
		catch (...) { throw polysort_exception("Numeric type: int overflow or string contains non-digit characters"); }

		if (x < 0) {
			auto it = value.begin();
			++it;
			for (++it; it != value.end(); ++it) if (!isdigit(*it)) throw polysort_exception("Numeric type: string contains non-digit characters");
		}
		else if (x >= 0)
			for (auto c : value)
				if (!isdigit(c)) throw polysort_exception("Numeric type: string contains non-digit characters");
		return x;
	}

	int value_;
};

#endif
