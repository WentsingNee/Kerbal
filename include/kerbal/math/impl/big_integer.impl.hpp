/**
 * @file       big_integer.impl.hpp
 * @brief
 * @date       2020-07-05
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MATH_IMPL_BIG_INTEGER_IMPL_HPP
#define KERBAL_MATH_IMPL_BIG_INTEGER_IMPL_HPP

#include <kerbal/math/big_integer.hpp>

namespace kerbal
{

	namespace math
	{

		template <typename Unit>
		void basic_big_integer<Unit>::absolute_add_with(basic_big_integer & lhs, const basic_big_integer & rhs)
		{
			typename storage_t::iterator lhs_it(lhs.storage.begin());
			typename storage_t::const_iterator rhs_it(rhs.storage.begin());

			bool carry = false;
			size_t n = std::min(lhs.storage.size(), rhs.storage.size());
			for (size_t i = 0; i < n; ++i) {
				unit rhs_unit = *rhs_it; // specially: &lhs == &rhs
				unit t = *lhs_it + carry;
				if (t < carry) { // overflow
					carry = true;
					*lhs_it = rhs_unit;
				} else {
					*lhs_it = t + rhs_unit;
					carry = (*lhs_it < rhs_unit); // overflow
				}

				++lhs_it;
				++rhs_it;
			}

			if (lhs.storage.size() < rhs.storage.size()) {
				//         *****
				//      ********
				lhs.storage.insert(lhs_it, rhs_it, rhs.storage.end());
				lhs_it = lhs.storage.begin() + n; // because lhs_it maybe invalid after insert
			}

			//   ******* *****
			//         ^ carry
			while (lhs_it != lhs.storage.end()) {
				*lhs_it += carry;
				if (*lhs_it >= carry) {
					carry = false;
					break;
				}
				++lhs_it;
			}
			if (carry) {
				lhs.storage.push_back(1);
			}
		}

		template <typename Unit>
		void basic_big_integer<Unit>::absolute_add_with(basic_big_integer & lhs, unit rhs)
		{
			typename storage_t::iterator lhs_it(lhs.storage.begin());

			*lhs_it = *lhs_it + rhs;
			bool carry = (*lhs_it < rhs); // overflow

			++lhs_it;

			//   ******* *
			//         ^ carry
			while (lhs_it != lhs.storage.end()) {
				*lhs_it += carry;
				if (*lhs_it >= carry) {
					carry = false;
					break;
				}
				++lhs_it;
			}
			if (carry) {
				lhs.storage.push_back(1);
			}
		}

		template <typename Unit>
		std::pair<typename basic_big_integer<Unit>::unit, typename basic_big_integer<Unit>::unit>
		basic_big_integer<Unit>::unit_muliply(unit a, unit b)
		{
			unit ah = unit_high(a);
			unit al = unit_low(a);
			unit bh = unit_high(b);
			unit bl = unit_low(b);

			unit m = al * bl;
			unit n = ah * bl;

			unit p = al * bh;
			unit q = ah * bh;

			unit rl = m + (n << HALF_BIT_WIDTH::value);
			int carry = rl < m;
			unit t = p << HALF_BIT_WIDTH::value;
			rl += t;
			carry += rl < t;

			unit rh = unit_high(n) + unit_high(p) + q + carry;
			return std::make_pair(rh, rl);
		}

		template <typename Unit>
		basic_big_integer<Unit>
		basic_big_integer<Unit>::operator*(const basic_big_integer& rhs) const
		{
			basic_big_integer r;

			return r;
		}

	} // namespace math

} // namespace kerbal

#endif // KERBAL_MATH_IMPL_BIG_INTEGER_IMPL_HPP
