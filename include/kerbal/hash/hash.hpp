/**
 * @file       hash.hpp
 * @brief      
 * @date       2019-5-14
 * @author     peter
 * @copyright
 *      peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_HASH_HASH_HPP
#define KERBAL_HASH_HASH_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/hash/murmur_hash2.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/fundamental_deduction.hpp>
#include <kerbal/utility/addressof.hpp>

#include <cstddef>

namespace kerbal
{

	namespace hash
	{

		template <typename Tp>
		struct integral_hash
		{
			private:
				KERBAL_STATIC_ASSERT(kerbal::type_traits::is_integral<Tp>::value, "");

			public:
				typedef size_t result_type;
				typedef Tp argument_type;

				KERBAL_CONSTEXPR
				result_type operator()(const Tp & val) const KERBAL_NOEXCEPT
				{
					return static_cast<size_t>(val);
				}
		};

		/// Primary class template hash.
		template <typename >
		struct hash;

		template <>
		struct hash<bool> : kerbal::hash::integral_hash<bool>
		{
		};

		template <>
		struct hash<char> : kerbal::hash::integral_hash<char>
		{
		};

#	if __cplusplus >= 201103L

		template <>
		struct hash<char16_t> : kerbal::hash::integral_hash<char16_t>
		{
		};

		template <>
		struct hash<char32_t> : kerbal::hash::integral_hash<char32_t>
		{
		};

#	endif

		template <>
		struct hash<signed char> : kerbal::hash::integral_hash<signed char>
		{
		};

		template <>
		struct hash<unsigned char> : kerbal::hash::integral_hash<unsigned char>
		{
		};

		template <>
		struct hash<short> : kerbal::hash::integral_hash<short>
		{
		};

		template <>
		struct hash<unsigned short> : kerbal::hash::integral_hash<unsigned short>
		{
		};

		template <>
		struct hash<int> : kerbal::hash::integral_hash<int>
		{
		};

		template <>
		struct hash<unsigned int> : kerbal::hash::integral_hash<unsigned int>
		{
		};

		template <>
		struct hash<long> : kerbal::hash::integral_hash<long>
		{
		};

		template <>
		struct hash<unsigned long> : kerbal::hash::integral_hash<unsigned long>
		{
		};

		template <>
		struct hash<long long> : kerbal::hash::integral_hash<long long>
		{
		};

		template <>
		struct hash<unsigned long long> : kerbal::hash::integral_hash<unsigned long long>
		{
		};

		template <>
		struct hash<float>
		{
				typedef kerbal::hash::murmur_hash2<float>::result_type result_type;
				typedef float argument_type;

				size_t operator()(float val) const KERBAL_NOEXCEPT
				{
					return val == 0.0 ? 0 : kerbal::hash::murmur_hash2<float>()(val);
				}
		};

		template <>
		struct hash<double>
		{
				typedef kerbal::hash::murmur_hash2<double>::result_type result_type;
				typedef double argument_type;

				size_t operator()(double val) const KERBAL_NOEXCEPT
				{
					return val == 0.0 ? 0 : kerbal::hash::murmur_hash2<double>()(val);
				}
		};

		template <>
		struct hash<long double>
		{
				typedef kerbal::hash::murmur_hash2<long double>::result_type result_type;
				typedef long double argument_type;

				size_t operator()(long double val) const KERBAL_NOEXCEPT
				{
					return val == 0.0 ? 0 : kerbal::hash::murmur_hash2<long double>()(val);
				}
		};

		template <typename Tp>
		struct hash<Tp*>
		{
				typedef size_t result_type;
				typedef Tp* argument_type;

				size_t operator()(Tp* p) const KERBAL_NOEXCEPT
				{
					return reinterpret_cast<size_t>(p);
				}
		};

	} // namespace hash

} // namespace kerbal

#endif // KERBAL_HASH_HASH_HPP
