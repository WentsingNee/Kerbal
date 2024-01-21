/**
 * @file       reference_wrapper.hpp
 * @brief      
 * @date       2019-7-26
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_REFERENCE_WRAPPER_HPP
#define KERBAL_UTILITY_REFERENCE_WRAPPER_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

KERBAL_MODULE_GLOBAL


#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>


KERBAL_EXPORT_MODULE_DECLARE(kerbal.utility.reference_wrapper)


namespace kerbal
{

	namespace utility
	{

		KERBAL_MODULE_EXPORT
		template <typename T>
		class reference_wrapper
		{
			public:
				typedef T type;

			private:
				T * ptr;

			public:
				KERBAL_CONSTEXPR
				reference_wrapper(T & val) KERBAL_NOEXCEPT :
					ptr(&val)
				{
				}

				KERBAL_CONSTEXPR
				operator T &() const KERBAL_NOEXCEPT
				{
					return *this->ptr;
				}

				KERBAL_CONSTEXPR
				T & get() const KERBAL_NOEXCEPT
				{
					return *this->ptr;
				}
		};

		KERBAL_MODULE_EXPORT
		template <typename T>
		KERBAL_CONSTEXPR
		reference_wrapper<T>
		ref(T & val) KERBAL_NOEXCEPT
		{
			return reference_wrapper<T>(val);
		}

		KERBAL_MODULE_EXPORT
		template <typename T>
		KERBAL_CONSTEXPR
		reference_wrapper<const T>
		cref(const T & val) KERBAL_NOEXCEPT
		{
			return reference_wrapper<const T>(val);
		}

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_UTILITY_REFERENCE_WRAPPER_HPP
