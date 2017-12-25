#ifndef  POLYSORT_HPP_
#define  POLYSORT_HPP_

#include <vector>
#include "row.hpp"

namespace polysort {

	///
	/// Sorting functor class for polysort::grid.
	///
	class polysort {

	public:
		polysort(const std::vector<size_t>& indices) : priority_(indices) {
		}
		polysort(const std::vector<std::pair<char, size_t>>& constraints) {
			
			for(const auto& constraint : constraints) {
				priority_.push_back(constraint.second);
			}
		}
		polysort(const std::initializer_list<size_t> indices) : priority_(indices) {
		}
		bool operator() (const row& r1, const row& r2) {
			
			for(const auto index : priority_) {
				
				if (r1.at(index - 1) < r2.at(index - 1)) return true;
				if (r2.at(index - 1) < r1.at(index - 1)) return false;
			}   // if equal, move to next column in priority_
			return false; // both rows equal by priority_ indices
		}
	private:
		std::vector<size_t> priority_;
	};
}

#endif