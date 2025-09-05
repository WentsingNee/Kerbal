/**
 * @file       md5.impl.hpp
 * @brief
 * @date       2020-08-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_HASH_MD5_MD5_IMPL_HPP
#define KERBAL_HASH_MD5_MD5_IMPL_HPP

#include <kerbal/hash/md5/md5.decl.hpp>
#include <kerbal/hash/md5/md5_result.hpp>

#include <kerbal/algorithm/modifier/copy.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/type_traits/is_same.hpp>


namespace kerbal
{

	namespace hash
	{

		template <typename Policy>
		template <typename RandomAccessIterator>
		KERBAL_CONSTEXPR14
		void
		MD5_context<Policy>::
		update_helper(
			RandomAccessIterator first, RandomAccessIterator last,
			std::random_access_iterator_tag
		) KERBAL_NOEXCEPT
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			difference_type const len(last - first);

			uint32_t j = (this->count[0] / 8) % 64;

			if (len >= static_cast<uint32_t>(64 - j)) {
				iterator next = first + static_cast<uint32_t>(64 - j);
				kerbal::algorithm::copy(first, next, this->buffer + j);
				first = next;
				this->transform(this->buffer);

				difference_type loop = (last - first) / 64;
				for (difference_type i = 0; i < loop; ++i) {
					next = first + 64;
					kerbal::algorithm::copy(first, next, this->buffer);
					first = next;
					this->transform(this->buffer);
				}
				j = 0;
			}

			kerbal::algorithm::copy(first, last, this->buffer + j);

			j = this->count[0];
			this->count[0] += static_cast<uint32_t>(len << 3);
			if (this->count[0] < j) {
				++this->count[1];
			}
			this->count[1] += static_cast<uint32_t>(len >> 29);

		}

		template <typename Policy>
		KERBAL_CONSTEXPR14
		void
		MD5_context<Policy>::
		update(const uint8_t * first, const uint8_t * last) KERBAL_NOEXCEPT
		{
			typedef const uint8_t * iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

			difference_type const len(last - first);

			uint32_t j = (this->count[0] / 8) % 64;

			if (len >= static_cast<uint32_t>(64 - j)) {
				if (j != 0) {
					iterator next = first + static_cast<uint32_t>(64 - j);
					kerbal::algorithm::copy(first, next, this->buffer + j);
					first = next;
					this->transform(this->buffer);
				}

				difference_type loop = (last - first) / 64;
				for (difference_type i = 0; i < loop; ++i) {
					this->transform(first);
					first += 64;
				}
				j = 0;
			}

			kerbal::algorithm::copy(first, last, this->buffer + j);

			j = this->count[0];
			this->count[0] += static_cast<uint32_t>(len << 3);
			if (this->count[0] < j) {
				++this->count[1];
			}
			this->count[1] += static_cast<uint32_t>(len >> 29);

		}

		template <typename Policy>
		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void
		MD5_context<Policy>::
		update(ForwardIterator first, ForwardIterator last) KERBAL_NOEXCEPT
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			KERBAL_STATIC_ASSERT(
				(kerbal::type_traits::is_same<value_type, uint8_t>::value),
				"Iterator must refers to uint8_t"
			);

			this->update_helper(first, last, kerbal::iterator::iterator_category(first));
		}

		template <typename Policy>
		KERBAL_CONSTEXPR14
		typename
		MD5_context<Policy>::result
		MD5_context<Policy>::
		digest() KERBAL_NOEXCEPT
		{
			uint32_t const count[2] = {
				this->count[0],
				this->count[1],
			};

			{
				uint8_t const * const p = context_base::PADDING;

				// 504 = 0b111111000
				// 448 = 0b111000000
				std::size_t padding_size = (count[0] + 8) & 504;
				padding_size = (padding_size > 448) ? (448 + (512 - padding_size)) : (448 - padding_size);
				padding_size /= 8;
				this->update(p, p + 1 + padding_size);
			}

			this->buffer[56] = static_cast<uint8_t>(count[0] >> 0);
			this->buffer[57] = static_cast<uint8_t>(count[0] >> 8);
			this->buffer[58] = static_cast<uint8_t>(count[0] >> 16);
			this->buffer[59] = static_cast<uint8_t>(count[0] >> 24);
			this->buffer[60] = static_cast<uint8_t>(count[1] >> 0);
			this->buffer[61] = static_cast<uint8_t>(count[1] >> 8);
			this->buffer[62] = static_cast<uint8_t>(count[1] >> 16);
			this->buffer[63] = static_cast<uint8_t>(count[1] >> 24);
			this->transform(this->buffer);

			return result(this->a, this->b, this->c, this->d);
		}

	} // namespace hash

} // namespace kerbal

#endif // KERBAL_HASH_MD5_MD5_IMPL_HPP
