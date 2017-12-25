#ifndef  TYPE_HPP_
#define  TYPE_HPP_

#include <memory>

namespace polysort {

	/**
	* Abstract class for types sorted by polysort.
	*/
	class cell_type {

	public:
		virtual ~cell_type() = default;
		virtual bool operator<(const cell_type& other) const = 0;
		virtual std::unique_ptr<cell_type> clone() const = 0;

		/*
		 * Wrapper friend for '<<' operator, otherwise all derived must implement it, which is not possible
		 * User must implement print function which is called by this wrapper.
		 */
		friend std::ostream& operator<<(std::ostream& out, const cell_type& type) {
			
			type.print(out);
			return out;
		}

	private:
		virtual void print(std::ostream& out) const = 0;
	};
}
#endif