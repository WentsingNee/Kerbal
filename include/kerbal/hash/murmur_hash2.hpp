/**
 * @file       murmur_hash2.hpp
 * @brief
 * @date       2020-09-04
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_HASH_MURMUR_HASH2_HPP
#define KERBAL_HASH_MURMUR_HASH2_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_same.hpp>
#include <kerbal/type_traits/type_identity.hpp>

#include <cstddef>


namespace kerbal
{

	namespace hash
	{

		class murmur_hash2_context
		{
			public:
				typedef kerbal::compatibility::uint32_t result_type;

			private:
				typedef kerbal::type_traits::integral_constant<result_type, 0x5bd1e995> M;

			protected:
				result_type seed;

			public:
				KERBAL_CONSTEXPR
				explicit murmur_hash2_context(result_type seed = 97u) :
					seed(seed)
				{
				}

			private:
				KERBAL_CONSTEXPR14
				static
				result_type final(result_type h) KERBAL_NOEXCEPT
				{
					// Do a few final mixes of the hash to ensure the last few bytes are well-incorporated.
					h ^= h >> 13u;
					h *= M::value;
					h ^= h >> 15u;
					return h;
				}

				template <typename ForwardIterator>
				KERBAL_CONSTEXPR14
				result_type digest_helper(
					ForwardIterator first, ForwardIterator last,
					kerbal::type_traits::type_identity<kerbal::compatibility::uint32_t>
				) const
				{
					typedef ForwardIterator iterator;
					typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

					difference_type len(kerbal::iterator::distance(first, last));
					result_type h = seed ^ len * 4;

					// 4 bytes at a time
					while (first != last) {
						result_type k = *first;
						k *= M::value;
						k ^= k >> 24u;
						k *= M::value;
						h *= M::value;
						h ^= k;
						++first;
					}

					return final(h);
				}

				template <typename ForwardIterator>
				KERBAL_CONSTEXPR14
				static
				result_type char4tolong1(ForwardIterator & it)
				{
					typedef ForwardIterator iterator;
					typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

					KERBAL_STATIC_ASSERT((kerbal::type_traits::is_same<value_type, unsigned char>::value), "");

					result_type k = *it; ++it;
					k |= *it << 8u; ++it;
					k |= *it << 16u; ++it;
					k |= *it << 24u; ++it;
					return k;
				}

				template <typename ForwardIterator>
				KERBAL_CONSTEXPR14
				result_type digest_helper(
					ForwardIterator first, ForwardIterator last,
					kerbal::type_traits::type_identity<unsigned char>
				) const
				{
					typedef ForwardIterator iterator;
					typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

					difference_type len(kerbal::iterator::distance(first, last));
					result_type h = seed ^ static_cast<result_type>(len);

					// 4 bytes at a time
					while (len >= 4) {
						result_type k = char4tolong1(first);
						k *= M::value;
						k ^= k >> 24u;
						k *= M::value;
						h *= M::value;
						h ^= k;
						len -= 4;
					}

					// Handle the last few bytes of the input array
					switch (len) {
						case 1: {
							h ^= *first;
							h *= M::value;
							break;
						}
						case 2: {
							h ^= *first; ++first;
							h ^= *first << 8u;
							h *= M::value;
							break;
						}
						case 3: {
							h ^= *first; ++first;
							h ^= *first << 8u; ++first;
							h ^= *first << 16u;
							h *= M::value;
							break;
						}

					};

					return final(h);
				}

			public:
				template <typename ForwardIterator>
				KERBAL_CONSTEXPR14
				result_type digest(ForwardIterator first, ForwardIterator last) const
				{
					typedef ForwardIterator iterator;
					typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
					return this->digest_helper(first, last, kerbal::type_traits::type_identity<value_type>());
				}

				template <typename T>
				result_type digest(T * first, T * last) const
				{
					const unsigned char * start = (const unsigned char *)(first);
					const unsigned char * end = (const unsigned char *)(last);
					return this->digest_helper(start, end, kerbal::type_traits::type_identity<unsigned char>());
				}

		};

		template <typename T>
		struct murmur_hash2
		{
				typedef murmur_hash2_context::result_type result_type;
				typedef T argument_type;

				result_type operator()(const T & obj) const
				{
					murmur_hash2_context ctx;
					return ctx.digest(&obj, &obj + 1);
				}

		};

	} // namespace hash

} // namespace kerbal

#endif // KERBAL_HASH_MURMUR_HASH2_HPP
