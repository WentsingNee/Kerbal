/**
 * @file       chrono_suffix.hpp
 * @brief
 * @date       2018-7-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COMPATIBILITY_CHRONO_SUFFIX_HPP
#define KERBAL_COMPATIBILITY_CHRONO_SUFFIX_HPP

#include <chrono>


namespace kerbal
{

	namespace compatibility
	{

		namespace chrono_suffix
		{

			constexpr std::chrono::duration<long double, std::ratio<3600, 1>> operator""_h(long double hours)
			{
				return std::chrono::duration<long double, std::ratio<3600, 1>> {hours};
			}

			constexpr std::chrono::hours operator""_h(unsigned long long hours)
			{
				return std::chrono::hours {hours};
			}

			constexpr std::chrono::duration<long double, std::ratio<60, 1>> operator""_min(long double mins)
			{
				return std::chrono::duration<long double, std::ratio<60, 1>> {mins};
			}

			constexpr std::chrono::minutes operator""_min(unsigned long long mins)
			{
				return std::chrono::minutes {mins};
			}

			constexpr std::chrono::duration<long double> operator""_s(long double secs)
			{
				return std::chrono::duration<long double> {secs};
			}

			constexpr std::chrono::seconds operator""_s(unsigned long long secs)
			{
				return std::chrono::seconds {secs};
			}

			constexpr std::chrono::duration<long double, std::milli> operator""_ms(long double msecs)
			{
				return std::chrono::duration<long double, std::milli> {msecs};
			}

			constexpr std::chrono::milliseconds operator""_ms(unsigned long long msecs)
			{
				return std::chrono::milliseconds {msecs};
			}

			constexpr std::chrono::duration<long double, std::micro> operator""_us(long double usecs)
			{
				return std::chrono::duration<long double, std::micro> {usecs};
			}

			constexpr std::chrono::microseconds operator""_us(unsigned long long usecs)
			{
				return std::chrono::microseconds {usecs};
			}

			constexpr std::chrono::duration<long double, std::nano> operator""_ns(long double nsecs)
			{
				return std::chrono::duration<long double, std::nano> {nsecs};
			}

			constexpr std::chrono::nanoseconds operator""_ns(unsigned long long nsecs)
			{
				return std::chrono::nanoseconds {nsecs};
			}

		} // namespace chrono_suffix

	} // namespace compatibility

} // namespace kerbal

#endif // KERBAL_COMPATIBILITY_CHRONO_SUFFIX_HPP
