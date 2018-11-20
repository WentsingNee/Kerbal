/*
 * memory_storage.hpp
 *
 *  Created on: 2018年6月18日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_UTILITY_STORAGE_HPP_
#define INCLUDE_KERBAL_UTILITY_STORAGE_HPP_

#include <chrono>
#include <cstdint>
#include <kerbal/type_traits/type_traits.hpp>

namespace kerbal
{
	namespace utility
	{
		template <typename size_type, typename Ratio>
		class storage : public std::chrono::duration<size_type, Ratio>
		{
			public:
				typedef std::chrono::duration<size_type, Ratio> supper_t;
				typedef typename supper_t::rep rep;
				typedef typename supper_t::period period;

				using std::chrono::duration<size_type, Ratio>::duration;
				using supper_t::count;

				storage(const supper_t & src) :
						supper_t(src)
				{
				}
		};

		typedef storage<std::int64_t, std::ratio<1, 1> > Byte;
		typedef storage<std::int64_t, std::ratio<1024, 1> > KB;
		typedef storage<std::int64_t, std::ratio<1024 * 1024, 1> > MB;
		typedef storage<std::int64_t, std::ratio<1024 * 1024 * 1024, 1> > GB;

		constexpr KB operator""_KB(unsigned long long x)
		{
			return KB(x);
		}

		constexpr MB operator""_MB(unsigned long long x)
		{
			return MB(x);
		}

		constexpr GB operator""_GB(unsigned long long x)
		{
			return GB(x);
		}

		template <typename>
		struct __is_storage_helper: kerbal::type_traits::false_type
		{
		};

		template <typename size_type, typename Ratio>
		struct __is_storage_helper<storage<size_type, Ratio> > : kerbal::type_traits::true_type
		{
		};

		template <typename Type>
		struct is_storage: __is_storage_helper<typename kerbal::type_traits::remove_cvref<Type>::type>
		{
		};

		template <typename ToStor, typename size_type, typename Ratio>
		constexpr
		typename kerbal::type_traits::enable_if<is_storage<ToStor>::value, ToStor>::type
		storage_cast(const storage<size_type, Ratio>& __d)
		{
			return ToStor(std::chrono::duration_cast<typename ToStor::supper_t>(__d));
		}
	}
}



#endif /* INCLUDE_KERBAL_UTILITY_STORAGE_HPP_ */
