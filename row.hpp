#ifndef  ROW_HPP_
#define  ROW_HPP_

#include <vector>
#include <memory>
#include "abstract_cell.hpp"
#include "polysort_exception.hpp"

namespace polysort {
	
	class row {
		
		using val_ptr = std::unique_ptr<abstract_cell>;

	public:
		row() = default;

		// Explicit copy constructor, handles vector of unique_ptrs
		row(const row& other) {
			clone(other);
		}

		// Explicit copy assignment, handles vector of unique_ptrs
		row& operator=(const row& other) {

			if (this == &other) return *this;
			row_.clear();
			clone(other);
			return *this;
		}

		void push_back(val_ptr ptr) {
			row_.push_back(move(ptr));
		}
		
		abstract_cell& at(const size_t index) {
			if (index >= row_.size()) throw polysort_exception("Index out of range");
			return *row_[index];
		}
		const abstract_cell& at(const size_t index) const {
			if (index >= row_.size()) throw polysort_exception("Index out of range");
			return *row_[index];
		}

		auto begin() { return row_.begin(); }
		auto end() { return row_.end(); }
		auto begin() const { return row_.cbegin(); }
		auto end() const { return row_.cend(); }

	private:
		std::vector<val_ptr> row_;

		void clone(const row& r) {
			
			for (auto&& cell : r.row_) {
				row_.push_back(cell->clone());
			}
		}

	};
}

#endif