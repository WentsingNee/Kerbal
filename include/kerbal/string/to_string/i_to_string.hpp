/**
 * @file       i_to_string.hpp
 * @brief
 * @date       2024-01-27
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_STRING_TO_STRING_I_TO_STRING_HPP
#define KERBAL_STRING_TO_STRING_I_TO_STRING_HPP

#include <kerbal/algorithm/modifier/reverse.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>

#include <string>


namespace kerbal
{

	namespace string
	{

		namespace detail
		{

			template <typename Integer, typename String>
			String k_i_to_string(Integer integer, kerbal::type_traits::false_type)
			{
				String s;
				do {
					int digit = integer % 10;
					s.push_back(digit + '0');
					integer /= 10;
				} while (integer != 0);
				kerbal::algorithm::reverse(s.begin(), s.end());
				return s;
			}

			template <typename Integer, typename String>
			String k_i_to_string(Integer integer, kerbal::type_traits::true_type)
			{
				String s;
				if (integer < 0) {
					s.push_back('-');
					integer = -integer;
					do {
						int digit = integer % 10;
						s.push_back(digit + '0');
						integer /= 10;
					} while (integer != 0);
					kerbal::algorithm::reverse(s.begin() + 1, s.end());
				} else {
					do {
						int digit = integer % 10;
						s.push_back(digit + '0');
						integer /= 10;
					} while (integer != 0);
					kerbal::algorithm::reverse(s.begin(), s.end());
				}
				return s;
			}

		} // namespace detail


		template <typename Integer, typename String = std::string>
		String i_to_string(const Integer & integer)
		{
			return kerbal::string::detail::k_i_to_string<Integer, String>(integer, kerbal::type_traits::is_signed<Integer>());
		}

	} // namespace string

} // namespace kerbal

#endif // KERBAL_STRING_TO_STRING_I_TO_STRING_HPP
