/**
 * @file       big_integer.hpp
 * @brief
 * @date       2020-07-05
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MATH_BIG_INTEGER_HPP
#define KERBAL_MATH_BIG_INTEGER_HPP

#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/iterator/reverse_iterator.hpp>
#include <kerbal/numeric/bit.hpp>
#include <kerbal/type_traits/cv_deduction.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_same.hpp>

#include <climits>
#include <cstddef>
#include <vector>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif

namespace kerbal
{

	namespace math
	{

		template <typename Unit>
		class basic_big_integer
		{
			public:
				typedef Unit unit;
				typedef kerbal::type_traits::integral_constant<size_t, sizeof(unit) * CHAR_BIT> UNIT_BIT_WIDTH;
				typedef kerbal::type_traits::integral_constant<size_t, UNIT_BIT_WIDTH::value / 2> HALF_BIT_WIDTH;

				typedef std::vector<unit> storage_t;

			private:
				storage_t storage;
				bool sign;

			public:
				basic_big_integer() :
						storage(1, 0), sign(false)
				{
				}

				explicit basic_big_integer(unit x) :
						storage(1, x), sign(false)
				{
				}

				template <typename BidirectionalIterator>
				basic_big_integer(BidirectionalIterator first, BidirectionalIterator last) :
						storage(kerbal::iterator::make_reverse_iterator(last),
								kerbal::iterator::make_reverse_iterator(first)),
						sign(false)
				{
					typedef BidirectionalIterator iterator;
					typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
					typedef typename kerbal::type_traits::remove_cv<value_type>::type remove_cv_type;
					KERBAL_STATIC_ASSERT((kerbal::type_traits::is_same<remove_cv_type, unit>::value),
										 "BidirectionalIterator must refers to unit type");
				}

#			if __cplusplus >= 201103L

				basic_big_integer(std::initializer_list<unit> list) :
						basic_big_integer(list.begin(), list.end())
				{
				}

#			endif

			private:
				inline static
				void absolute_add_with(basic_big_integer & lhs, const basic_big_integer & rhs);

				inline static
				void absolute_add_with(basic_big_integer & lhs, unit rhs);

				inline static
				void absolute_minus_with(basic_big_integer & lhs, const basic_big_integer & rhs);

				inline static
				void absolute_minus_with(basic_big_integer & lhs, unit rhs);

			public:
				basic_big_integer& operator+=(const basic_big_integer & rhs)
				{
					if (this->sign == rhs.sign) {
						absolute_add_with(*this, rhs);
					}
					return *this;
				}

				basic_big_integer& operator+=(unit rhs)
				{
					if (this->sign == false) {
						absolute_add_with(*this, rhs);
					}
					return *this;
				}

				basic_big_integer& operator++()
				{
					if (this->sign == false) {
						absolute_add_with(*this, static_cast<unit>(1));
					}
					return *this;
				}

			private:
				static
				unit unit_high(unit x)
				{
					return x >> HALF_BIT_WIDTH::value;;
				}

				static
				unit unit_low(unit x)
				{
					return x & kerbal::numeric::mask<unit>(HALF_BIT_WIDTH::value);
				}

				inline static
				std::pair<unit, unit> unit_muliply(unit a, unit b);

			public:
				inline
				basic_big_integer operator*(const basic_big_integer & rhs) const;

				std::vector<kerbal::container::array<char, kerbal::numeric::hexarray_result_len<unit>::value> >
				hex_group() const
				{
					typename storage_t::const_reverse_iterator rit(this->storage.rbegin());
					typename storage_t::const_reverse_iterator rend(this->storage.rend());

					std::vector<kerbal::container::array<char, kerbal::numeric::hexarray_result_len<unit>::value> > r;
					r.reserve(this->storage.size());
					while (rit != rend) {
						r.push_back(kerbal::numeric::hexarray(*rit));
						++rit;
					}
					return r;
				}

		};

		typedef basic_big_integer<unsigned long long> big_integer;

	} // namespace math

} // namespace kerbal

#include <kerbal/math/impl/big_integer.impl.hpp>

#endif // KERBAL_MATH_BIG_INTEGER_HPP
