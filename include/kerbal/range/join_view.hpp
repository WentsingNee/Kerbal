/*
 * join_view.hpp
 *
 *  Created on: 2018年9月3日
 *      Author: peter
 */

#ifndef KERBAL_JOIN_VIEW_HPP
#define KERBAL_JOIN_VIEW_HPP

#include <string>

#if __cplusplus >= 201103L
#   include <initializer_list>
#endif

namespace kerbal
{
	namespace range
	{
		template <typename InputIterator>
		class Join_view
		{
			protected:
				std::string joint;
				InputIterator start, finish;

			public:
				Join_view(const std::string & joint, InputIterator start, InputIterator finish) :
						joint(joint), start(start), finish(finish)
				{
				}

				operator std::string() const
				{
					std::string res;
					InputIterator it = start;
					if (it == finish) {
						return res;
					}
					res += *it;
					++it;
					while (it != finish) {
						res += joint + *it;
						++it;
					}
					return res;
				}

				friend std::ostream & operator<<(std::ostream & out, const Join_view & src)
				{
					InputIterator it = src.start;
					if (it == src.finish) {
						return out;
					}
					out << *it;
					++it;
					while (it != src.finish) {
						out << src.joint << *it;
						++it;
					}
					return out;
				}
		};

		template <typename InputIterator>
		Join_view<InputIterator> make_join_view(const std::string & joint, InputIterator start, InputIterator finish)
		{
			return Join_view<InputIterator>(joint, start, finish);
		}

		template <typename IterableType>
		Join_view<typename IterableType::iterator>
		make_join_view(const std::string & joint, const IterableType & src)
		{
			return Join_view<typename IterableType::iterator>(joint, src.begin(), src.end());
		}
        
#   if __cplusplus >= 201103L
        template <typename Type>
        Join_view<typename std::initializer_list<Type>::iterator>
        make_join_view(const std::string & joint, std::initializer_list<Type> src)
        {
            return Join_view<typename std::initializer_list<Type>::iterator>(joint, src.begin(), src.end());
        }

#   endif

#	if __cplusplus >= 201103L
		class Join_literals_helper
		{
			protected:
				std::string joint;

			public:
				Join_literals_helper(const std::string joint) :
						joint(joint)
				{
				}

				template <typename InputIterator>
				Join_view<InputIterator> operator()(InputIterator start, InputIterator finish)
				{
					return Join_view<InputIterator>(joint, start, finish);
				}

                template <typename IterableType>
                Join_view<typename IterableType::iterator> operator()(const IterableType & src)
                {
                    return Join_view<typename IterableType::iterator>(joint, src.begin(), src.end());
                }
            
                template <typename Type>
                Join_view<typename std::initializer_list<Type>::iterator> operator()(std::initializer_list<Type> src)
                {
                    return Join_view<typename std::initializer_list<Type>::iterator>(joint, src.begin(), src.end());
                }
		};

		Join_literals_helper operator "" _join(const char s[], long unsigned int)
		{
			return Join_literals_helper(s);
		}

#	endif

	} /* namespace range */

} /* namespace kerbal */

#endif //KERBAL_JOIN_VIEW_HPP
