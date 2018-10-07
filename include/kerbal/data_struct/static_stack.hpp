/**
 * @file		static_stack.hpp
 * @brief
 * @date		2018年5月2日
 * @author		Peter
 * @copyright	Peter
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 */

#ifndef INCLUDE_KERBAL_DATA_STRUCT_STATIC_STACK_HPP_
#define INCLUDE_KERBAL_DATA_STRUCT_STATIC_STACK_HPP_

#include <kerbal/data_struct/static_array.hpp>

namespace kerbal
{
	namespace data_struct
	{
		/**
		 * @brief Stack with flexible length that stored on automatic storage duration
		 * @details The class is an encapsulation class of stack that could be stored on
		 *          automatic storage duration. It is more effective than std::stack because
		 *          std::stack store elements on heap storage duration (that's required memory
		 *          allocate and deallocate).
		 * @tparam Tp Type of the elements.
		 * @tparam N The maximum number of elements that the stack can hold.
		 */
		template <typename Tp, size_t N>
		class static_stack
		{
			public:
				typedef Tp value_type;
				typedef const Tp const_type;
				typedef Tp& reference;
				typedef const Tp& const_reference;
				typedef Tp* pointer;
				typedef const Tp* const_pointer;

			private:
				kerbal::data_struct::static_array<Tp, N> p;

			public:
				static_stack() :
						p()
				{
				}

#if __cplusplus >= 201103L
				static_stack(std::initializer_list<value_type> src) :
						p(src)
				{
				}
#endif
				static_stack& operator=(const static_stack& src)
				{
					this->p = src.p;
					return *this;
				}

				void push(const value_type & val)
				{
					p.push_back(val);
				}

				void pop()
				{
					p.pop_back();
				}

				void clear()
				{
					p.clear();
				}

				size_t size() const
				{
					return p.size();
				}

				bool empty() const
				{
					return p.empty();
				}

				bool full() const
				{
					return p.full();
				}

				reference top()
				{
					return p.back();
				}

				const_reference top() const
				{
					return p.back();
				}

				void swap(static_stack & with)
				{
					p.swap(with.p);
				}

				/**
				 * @addtogroup compare
				 * @{
				 */

				/**
				 * Judge whether the stack is equal to the other one.
				 * @param with another stack
				 */
				bool operator==(const static_stack & with) const
				{
					return p == with.p;
				}

				bool operator!=(const static_stack & with) const
				{
					return p != with.p;
				}

				bool operator<(const static_stack & with) const
				{
					return p < with.p;
				}
				bool operator<=(const static_stack & with) const
				{
					return p <= with.p;
				}
				bool operator>(const static_stack & with) const
				{
					return p > with.p;
				}
				bool operator>=(const static_stack & with) const
				{
					return p >= with.p;
				}

				// @} group compare
		};
	}
}

#endif /* INCLUDE_KERBAL_DATA_STRUCT_STATIC_STACK_HPP_ */
