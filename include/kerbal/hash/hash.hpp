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

#ifndef KERBAL_HASH_HASH_HPP_
#define KERBAL_HASH_HASH_HPP_

#include <cstddef>
#include <kerbal/type_traits/type_traits_details/enable_if.hpp>
#include <kerbal/type_traits/type_traits_details/fundamental_deduction.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/utility/addressof.hpp>

namespace kerbal
{
	namespace data_struct
	{

		template <typename Result, typename Arg>
		struct hash_base
		{
				typedef Result result_type;
				typedef Arg argument_type;
		};

		template <typename Tp, typename kerbal::type_traits::enable_if<
							kerbal::type_traits::is_integral<Tp>::value,
							int>::type = 0 >
		struct integral_hash : hash_base<size_t, Tp>
		{
					KERBAL_CONSTEXPR
					size_t operator()(const Tp & val) const KERBAL_NOEXCEPT
					{
						return static_cast<size_t>(val);
					}
		};

		/// Primary class template hash.
		template <typename >
		struct hash;

		template <>
		struct hash<bool> : integral_hash<bool>
		{
		};

		template <>
		struct hash<char> : integral_hash<char>
		{
		};

#	if __cplusplus >= 201103L

		template <>
		struct hash<char16_t> : integral_hash<char16_t>
		{
		};

		template <>
		struct hash<char32_t> : integral_hash<char32_t>
		{
		};

#	endif

		template <>
		struct hash<signed char> : integral_hash<signed char>
		{
		};

		template <>
		struct hash<unsigned char> : integral_hash<unsigned char>
		{
		};

		template <>
		struct hash<short> : integral_hash<short>
		{
		};

		template <>
		struct hash<unsigned short> : integral_hash<unsigned short>
		{
		};

		template <>
		struct hash<int> : integral_hash<int>
		{
		};

		template <>
		struct hash<unsigned int> : integral_hash<unsigned int>
		{
		};

		template <>
		struct hash<long> : integral_hash<long>
		{
		};

		template <>
		struct hash<unsigned long> : integral_hash<unsigned long>
		{
		};

		template <>
		struct hash<long long> : integral_hash<long long>
		{
		};

		template <>
		struct hash<unsigned long long> : integral_hash<unsigned long long>
		{
		};

		template <typename Tp, size_t seed = static_cast<size_t>(0xc70f6907UL)>
		struct stdlibcxx_bytes_hash : hash_base<size_t, Tp>
		{
			private:
				static size_t unaligned_load(const char* p) KERBAL_NOEXCEPT
				{
					return *reinterpret_cast<const size_t*>(p);
				}

				static size_t _Hash_bytes(const void* ptr, size_t len) KERBAL_NOEXCEPT
				{
					const size_t m = 0x5bd1e995;
					size_t hash = seed ^ len;
					const char* buf = static_cast<const char*>(ptr);

					// Mix 4 bytes at a time into the hash.
					while (len >= 4) {
						size_t k = unaligned_load(buf);
						k *= m;
						k ^= k >> 24;
						k *= m;
						hash *= m;
						hash ^= k;
						buf += 4;
						len -= 4;
					}

					// Handle the last few bytes of the input array.
					switch (len) {
						case 3:
							hash ^= static_cast<unsigned char>(buf[2]) << 16;
						case 2:
							hash ^= static_cast<unsigned char>(buf[1]) << 8;
						case 1:
							hash ^= static_cast<unsigned char>(buf[0]);
							hash *= m;
					};

					// Do a few final mixes of the hash.
					hash ^= hash >> 13;
					hash *= m;
					hash ^= hash >> 15;
					return hash;
				}

			public:
				size_t operator()(const Tp & val) const KERBAL_NOEXCEPT
				{
					const void * start = reinterpret_cast<const void*>(kerbal::utility::addressof(val));
					return _Hash_bytes(start, sizeof(Tp));
				}
		};

		template <>
		struct hash<float> : hash_base<size_t, float>
		{
				size_t operator()(float val) const KERBAL_NOEXCEPT
				{
					return val == 0.0 ? 0 : stdlibcxx_bytes_hash<float>()(val);
				}
		};

		template <>
		struct hash<double> : hash_base<size_t, double>
		{
				size_t operator()(double val) const KERBAL_NOEXCEPT
				{
					return val == 0.0 ? 0 : stdlibcxx_bytes_hash<double>()(val);
				}
		};

		template <>
		struct hash<long double> : hash_base<size_t, long double>
		{
				size_t operator()(long double val) const KERBAL_NOEXCEPT
				{
					return val == 0.0 ? 0 : stdlibcxx_bytes_hash<long double>()(val);
				}
		};

		template <typename Tp>
		struct hash<Tp*> : hash_base<size_t, Tp*>
		{
				size_t operator()(Tp* p) const KERBAL_NOEXCEPT
				{
					return reinterpret_cast<size_t>(p);
				}
		};

		template <typename Tp, size_t seed = static_cast<size_t>(0xc70f6907UL)>
		struct shallow_hash : hash_base<size_t, Tp>
		{
				size_t operator()(const Tp & val) const KERBAL_NOEXCEPT
				{
					const char * start = reinterpret_cast<const char*>(kerbal::utility::addressof(val));
					size_t ret = 0;
					hash<char> hs;
					for (size_t i = 0; i < sizeof(Tp); ++i) {
						ret += seed * hs(start[i]);
					}
					return ret;
				}
		};

	} /* namespace data_struct */

} /* namespace kerbal */


#endif /* KERBAL_HASH_HASH_HPP_ */
