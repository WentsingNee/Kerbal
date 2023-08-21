/**
 * @file       chrono_suffix.cxx11.part.hpp
 * @brief
 * @date       2018-7-24
 * @author     Peter
 * @remark     move from kerbal/compatibility/chrono_suffix.hpp, 2023-08-25
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COMPATIBILITY_CHRONO_SUFFIX_DETAIL_CHRONO_SUFFIX_CXX11_PART_HPP
#define KERBAL_COMPATIBILITY_CHRONO_SUFFIX_DETAIL_CHRONO_SUFFIX_CXX11_PART_HPP

#if __cplusplus < 201103L
#	error This file requires compiler and library support for the ISO C++ 2011 standard.
#endif

#include <kerbal/compatibility/constexpr.hpp>

#include <chrono>


namespace kerbal
{

	namespace compatibility
	{

		namespace chrono_suffix
		{

			KERBAL_CONSTEXPR
			std::chrono::duration<long double, std::ratio<3600, 1>> operator""_h(long double hours)
			{
				return std::chrono::duration<long double, std::ratio<3600, 1>> {hours};
			}

			KERBAL_CONSTEXPR
			std::chrono::hours operator""_h(unsigned long long hours)
			{
				return std::chrono::hours {hours};
			}

			KERBAL_CONSTEXPR
			std::chrono::duration<long double, std::ratio<60, 1>> operator""_min(long double mins)
			{
				return std::chrono::duration<long double, std::ratio<60, 1>> {mins};
			}

			KERBAL_CONSTEXPR
			std::chrono::minutes operator""_min(unsigned long long mins)
			{
				return std::chrono::minutes {mins};
			}

			KERBAL_CONSTEXPR
			std::chrono::duration<long double> operator""_s(long double secs)
			{
				return std::chrono::duration<long double> {secs};
			}

			KERBAL_CONSTEXPR
			std::chrono::seconds operator""_s(unsigned long long secs)
			{
				return std::chrono::seconds {secs};
			}

			KERBAL_CONSTEXPR
			std::chrono::duration<long double, std::milli> operator""_ms(long double msecs)
			{
				return std::chrono::duration<long double, std::milli> {msecs};
			}

			KERBAL_CONSTEXPR
			std::chrono::milliseconds operator""_ms(unsigned long long msecs)
			{
				return std::chrono::milliseconds {msecs};
			}

			KERBAL_CONSTEXPR
			std::chrono::duration<long double, std::micro> operator""_us(long double usecs)
			{
				return std::chrono::duration<long double, std::micro> {usecs};
			}

			KERBAL_CONSTEXPR
			std::chrono::microseconds operator""_us(unsigned long long usecs)
			{
				return std::chrono::microseconds {usecs};
			}

			KERBAL_CONSTEXPR
			std::chrono::duration<long double, std::nano> operator""_ns(long double nsecs)
			{
				return std::chrono::duration<long double, std::nano> {nsecs};
			}

			KERBAL_CONSTEXPR
			std::chrono::nanoseconds operator""_ns(unsigned long long nsecs)
			{
				return std::chrono::nanoseconds {nsecs};
			}

		} // namespace chrono_suffix

	} // namespace compatibility

} // namespace kerbal

#endif // KERBAL_COMPATIBILITY_CHRONO_SUFFIX_DETAIL_CHRONO_SUFFIX_CXX11_PART_HPP
