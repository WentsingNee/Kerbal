/*
 * chrono_suffix.hpp
 *
 *  Created on: 2018年7月24日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_COMPATIBILITY_CHRONO_SUFFIX_HPP_
#define INCLUDE_KERBAL_COMPATIBILITY_CHRONO_SUFFIX_HPP_

#include <chrono>
#include <type_traits>

namespace kerbal
{
	namespace compatibility
	{
		namespace chrono_suffix
		{

			constexpr std::chrono::duration<long double, std::ratio<3600, 1>> operator""_h(long double __hours)
			{
				return std::chrono::duration<long double, std::ratio<3600, 1>> { __hours };
			}

			constexpr std::chrono::hours operator""_h(unsigned long long __hours)
			{
				return std::chrono::hours { __hours };
			}

			constexpr std::chrono::duration<long double, std::ratio<60, 1>> operator""_min(long double __mins)
			{
				return std::chrono::duration<long double, std::ratio<60, 1>> { __mins };
			}

			constexpr std::chrono::minutes operator""_min(unsigned long long __mins)
			{
				return std::chrono::minutes { __mins };
			}

			constexpr std::chrono::duration<long double> operator""_s(long double __secs)
			{
				return std::chrono::duration<long double> { __secs };
			}

			constexpr std::chrono::seconds operator""_s(unsigned long long __secs)
			{
				return std::chrono::seconds { __secs };
			}

			constexpr std::chrono::duration<long double, std::milli> operator""_ms(long double __msecs)
			{
				return std::chrono::duration<long double, std::milli> { __msecs };
			}

			constexpr std::chrono::milliseconds operator""_ms(unsigned long long __msecs)
			{
				return std::chrono::milliseconds { __msecs };
			}

			constexpr std::chrono::duration<long double, std::micro> operator""_us(long double __usecs)
			{
				return std::chrono::duration<long double, std::micro> { __usecs };
			}

			constexpr std::chrono::microseconds operator""_us(unsigned long long __usecs)
			{
				return std::chrono::microseconds { __usecs };
			}

			constexpr std::chrono::duration<long double, std::nano> operator""_ns(long double __nsecs)
			{
				return std::chrono::duration<long double, std::nano> { __nsecs };
			}

			constexpr std::chrono::nanoseconds operator""_ns(unsigned long long __nsecs)
			{
				return std::chrono::nanoseconds { __nsecs };
			}
		}
	}
}



#endif /* INCLUDE_KERBAL_COMPATIBILITY_CHRONO_SUFFIX_HPP_ */
