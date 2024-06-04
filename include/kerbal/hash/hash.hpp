/**
 * @file       hash.hpp
 * @brief      
 * @date       2019-5-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_HASH_HASH_HPP
#define KERBAL_HASH_HASH_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/hash/murmur_hash2.hpp>
#include <kerbal/type_traits/is_integral.hpp>

#include <cstddef>


namespace kerbal
{

	namespace hash
	{

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct integral_hash
		{
			private:
				KERBAL_STATIC_ASSERT(kerbal::type_traits::is_integral<T>::value, "");

			public:
				typedef std::size_t result_type;
				typedef T argument_type;

				KERBAL_CONSTEXPR
				result_type operator()(const T & val) const KERBAL_NOEXCEPT
				{
					return static_cast<std::size_t>(val);
				}
		};

		/// Primary class template hash.
		KERBAL_MODULE_EXPORT
		template <typename >
		struct hash;

		/*KERBAL_MODULE_EXPORT*/
		template <>
		struct hash<bool> : kerbal::hash::integral_hash<bool>
		{
		};

		/*KERBAL_MODULE_EXPORT*/
		template <>
		struct hash<char> : kerbal::hash::integral_hash<char>
		{
		};

#	if __cplusplus >= 201103L

		/*KERBAL_MODULE_EXPORT*/
		template <>
		struct hash<char16_t> : kerbal::hash::integral_hash<char16_t>
		{
		};

		/*KERBAL_MODULE_EXPORT*/
		template <>
		struct hash<char32_t> : kerbal::hash::integral_hash<char32_t>
		{
		};

#	endif

		/*KERBAL_MODULE_EXPORT*/
		template <>
		struct hash<signed char> : kerbal::hash::integral_hash<signed char>
		{
		};

		/*KERBAL_MODULE_EXPORT*/
		template <>
		struct hash<unsigned char> : kerbal::hash::integral_hash<unsigned char>
		{
		};

		/*KERBAL_MODULE_EXPORT*/
		template <>
		struct hash<short> : kerbal::hash::integral_hash<short>
		{
		};

		/*KERBAL_MODULE_EXPORT*/
		template <>
		struct hash<unsigned short> : kerbal::hash::integral_hash<unsigned short>
		{
		};

		/*KERBAL_MODULE_EXPORT*/
		template <>
		struct hash<int> : kerbal::hash::integral_hash<int>
		{
		};

		/*KERBAL_MODULE_EXPORT*/
		template <>
		struct hash<unsigned int> : kerbal::hash::integral_hash<unsigned int>
		{
		};

		/*KERBAL_MODULE_EXPORT*/
		template <>
		struct hash<long> : kerbal::hash::integral_hash<long>
		{
		};

		/*KERBAL_MODULE_EXPORT*/
		template <>
		struct hash<unsigned long> : kerbal::hash::integral_hash<unsigned long>
		{
		};

		/*KERBAL_MODULE_EXPORT*/
		template <>
		struct hash<long long> : kerbal::hash::integral_hash<long long>
		{
		};

		/*KERBAL_MODULE_EXPORT*/
		template <>
		struct hash<unsigned long long> : kerbal::hash::integral_hash<unsigned long long>
		{
		};

		/*KERBAL_MODULE_EXPORT*/
		template <>
		struct hash<float>
		{
				typedef kerbal::hash::murmur_hash2<float>::result_type result_type;
				typedef float argument_type;

				std::size_t operator()(float val) const KERBAL_NOEXCEPT
				{
					return val == 0.0 ? 0 : kerbal::hash::murmur_hash2<float>()(val);
				}
		};

		/*KERBAL_MODULE_EXPORT*/
		template <>
		struct hash<double>
		{
				typedef kerbal::hash::murmur_hash2<double>::result_type result_type;
				typedef double argument_type;

				std::size_t operator()(double val) const KERBAL_NOEXCEPT
				{
					return val == 0.0 ? 0 : kerbal::hash::murmur_hash2<double>()(val);
				}
		};

		/*KERBAL_MODULE_EXPORT*/
		template <>
		struct hash<long double>
		{
				typedef kerbal::hash::murmur_hash2<long double>::result_type result_type;
				typedef long double argument_type;

				std::size_t operator()(long double val) const KERBAL_NOEXCEPT
				{
					return val == 0.0 ? 0 : kerbal::hash::murmur_hash2<long double>()(val);
				}
		};

		/*KERBAL_MODULE_EXPORT*/
		template <typename T>
		struct hash<T *>
		{
				typedef std::size_t result_type;
				typedef T * argument_type;

				std::size_t operator()(T * p) const KERBAL_NOEXCEPT
				{
					return reinterpret_cast<std::size_t>(p);
				}
		};

	} // namespace hash

} // namespace kerbal

#endif // KERBAL_HASH_HASH_HPP
