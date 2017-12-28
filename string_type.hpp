#ifndef  STRING_TYPE_HPP_
#define  STRING_TYPE_HPP_

#include "abstract_cell.hpp"
#include <string>
#include <memory>

class string_type final : public polysort::abstract_cell {

public:
	explicit string_type(const std::string& content) : value_(content) {}
	
	bool operator<(const abstract_cell& oper) const override {

		const string_type op = dynamic_cast<const string_type&>(oper);
		return value_ < op.value_;
	}

	std::unique_ptr<abstract_cell> clone() const override {

		return std::make_unique<string_type>(*this);
	}

private:
	void print(std::ostream& out) const override { out << value_; }
	std::string value_;
};

#endif