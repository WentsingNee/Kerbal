#ifndef _ARRAY_SERVE_HPP_
#define _ARRAY_SERVE_HPP_

#include <kerbal/type_traits/type_traits_details/integral_constant.hpp>
#include <iostream>
#include <string>

namespace kerbal
{
	namespace utility
	{
		namespace array_serve
		{
			template <typename Type, size_t N>
			const Type* begin(const Type (&arr)[N])
			{
				return arr;
			}

			template <typename Type, size_t N>
			Type* begin(Type (&arr)[N])
			{
				return arr;
			}

			template <typename Type, size_t N>
			const Type* end(const Type (&arr)[N])
			{
				return arr + N;
			}

			template <typename Type, size_t N>
			Type* end(Type (&arr)[N])
			{
				return arr + N;
			}

			template <class Type, size_t N>
			KERBAL_CONSTEXPR inline size_t arraylen(const Type (&array)[N])
			{
				return N;
			}

			template <typename InputIterator>
			std::ostream & print_array(InputIterator begin, InputIterator end, const std::string & separator, bool if_output_number, std::ostream & out =
					std::cout)
			{
				if(begin == end)
				{
					return out;
				}

				if (if_output_number == true) {
					out << 0 << " : " << *begin;
					size_t i = 1;
					for (++begin; begin != end; ++begin, ++i) {
						out << separator << i << " : " << *begin;
					}
				} else {
					out << *begin;
					for (++begin; begin != end; ++begin) {
						out << separator << *begin;
					}
				}
				return out;
			}

			// rank
			template <typename >
			struct rank: public kerbal::type_traits::integral_constant<size_t, 0>
			{
			};

			template <typename Type, size_t Size>
			struct rank<Type[Size]> : public kerbal::type_traits::integral_constant<size_t, 1 + rank<Type>::value>
			{
			};

			template <typename Type>
			struct rank<Type[]> : public kerbal::type_traits::integral_constant<size_t, 1 + rank<Type>::value>
			{
			};

			template <typename Type>
			KERBAL_CONSTEXPR size_t array_dimension(const Type &)
			{
				return rank<Type>::value;
			}

		} /* Namespace array_serve */

	} /* namespace utility */

} /* namespace kerbal */

#endif	/* End _ARRAY_SERVE_HPP_ */
