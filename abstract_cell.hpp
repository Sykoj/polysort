#ifndef  ABSTRACT_CELL_HPP_
#define  ABSTRACT_CELL_HPP_

#include <memory>

namespace polysort {

	/**
	* Abstract class for types sorted by polysort.
	*/
	class abstract_cell {

	public:
		virtual ~abstract_cell() = default;
		virtual bool operator<(const abstract_cell& other) const = 0;
		virtual std::unique_ptr<abstract_cell> clone() const = 0;

		/*
		 * Wrapper friend for '<<' operator, otherwise all derived must implement it, which is not possible
		 * User must implement print function which is called by this wrapper.
		 */
		friend std::ostream& operator<<(std::ostream& out, const abstract_cell& type) {
			
			type.print(out);
			return out;
		}

	private:
		virtual void print(std::ostream& out) const = 0;
	};
}
#endif