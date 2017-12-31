#ifndef  GRID_HPP_
#define  GRID_HPP_

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include "abstract_cell.hpp"
#include "polysort_exception.hpp"
#include "row.hpp"
#include "polysort.hpp"

namespace polysort {

	/// @brief Pair of char symbol for type and column index for the type.
	using column_constraints = std::vector<std::pair<char, size_t>>;

	///
	/// Class representing table containing columns with specific types.
	///
	class grid {

		/// @brief Callable target returning instance of type derived from abstract_cell initialized from string.
		using type_creator = std::function<std::unique_ptr<abstract_cell>(const std::string&)>;

	public:
		grid(const column_constraints& constraints, const char column_delimiter = ' ');

		void print(std::ostream& output) const;
		void create(std::istream& input);

		/// @brief Allows adding new derived class from abstract_cell to the table.
		/// @tparam T Class derived from polysort::abstract_cell having constructor with string argument.
		/// @tparam C Character symbol for this type, {'N', 'S'} already in use.
		template<class T, char C>
		void add_type() {

			if (types_.find(C) != types_.cend()) throw polysort_exception("Type can't be added, character symbol already used!");
			types_[C] = [](const std::string& content) { return std::make_unique<T>(content); };
			// if user has not implemented constructor with string argument -> compile time error
		}

		/*
		 * Wrapping sorting function added instead of direct STL sort because std::sort requires iterators 
		 * which means that grid_ is !MODIFIABLE! for every possible user function -> user could break restrictions. 
		 */
		void sort() { std::sort(grid_.begin(), grid_.end(), polysort(constraints_)); }
		void sort(const polysort& functor) { std::sort(grid_.begin(), grid_.end(), functor); }

		~grid() = default;

	private:
		row parse_line(const std::string& line);
		std::unique_ptr<abstract_cell> get_cell(const size_t column_index, const std::string& content);
		
		void restrict_column_type(const char c, const size_t index) {

			if (restricted_columns_.find(index) != restricted_columns_.end()) 
				throw polysort_exception("Column already constrained by type.");
			restricted_columns_[index] = c;
		}

		std::unordered_map<size_t, char> restricted_columns_;
		std::unordered_map<char, type_creator> types_;
		std::vector<row> grid_;
		column_constraints constraints_;
		char delimiter_;
		size_t max_column_index_;
	};
}
#endif
