#include "grid.hpp"
#include "string_type.hpp"
#include "numeric.hpp"
#include <sstream>
#include <iostream>

namespace polysort {

	grid::grid(const column_constraints& constraints, const char delimiter)
		: constraints_(constraints)
		, delimiter_(delimiter)
		, max_column_index_(0)
	 {

		add_type<string_type, 'S'>();
		add_type<numeric, 'N'>();

		for (const auto& constraint : constraints) {
			restrict_column_type(constraint.first, constraint.second);
			if (max_column_index_ < constraint.second) max_column_index_ = constraint.second;
		}
	}

	void grid::create(std::istream& input) {

		std::string line;
		while (getline(input, line)) {

			grid_.push_back(parse_line(line));
		}
	}

	row grid::parse_line(const std::string& line) {

		row row;
		size_t current_column = 0;

		std::string cell;
		std::stringstream ss(line);

		if (line.empty()) {
			row.push_back(get_cell(++current_column, line));
		}
		else {

			while (getline(ss, cell, delimiter_)) {
				
				row.push_back(get_cell(++current_column, cell));
			}
			// situation, when delimiter is last character, insert empty string behind as last column
			if (line[line.size() - 1] == delimiter_) {

				row.push_back(get_cell(++current_column, ""));
			}
		}

		if (current_column < max_column_index_) throw polysort_exception("All required cells were not initialized by parsed input.");
		return row;
	}

	std::unique_ptr<abstract_cell> grid::get_cell(const size_t column_index, const std::string& content) {

		// find type for column
		const auto ptr = restricted_columns_.find(column_index);
		if (ptr == restricted_columns_.end()) return types_['S'](content);
		const char symbol = (*ptr).second;
		// get function returning unique_ptr for the type
		const auto func = types_.find(symbol);
		if (func == types_.end()) throw polysort_exception("Type for symbol not provided.");
		return (*func).second(content);
	}

	void grid::print(std::ostream& output) const {

		for (const auto& row : grid_) {

			bool is_first_column = true;

			for (const auto& cell : row) {
				
				if (is_first_column) {
					output << *cell;
					is_first_column = false;
				}
				else {
					output << delimiter_ << *cell;
				}
			}

			output << std::endl;
		}
	}
}
