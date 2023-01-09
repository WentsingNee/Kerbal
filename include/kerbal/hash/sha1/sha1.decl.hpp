/**
 * @file       sha1.decl.hpp
 * @brief
 * @date       2024-10-06
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_HASH_SHA1_SHA1_DECL_HPP
#define KERBAL_HASH_SHA1_SHA1_DECL_HPP

#include <kerbal/hash/sha1/sha1.fwd.hpp>
#include <kerbal/hash/sha1/detail/sha1_transform_overload.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#include <cstddef>


namespace kerbal
{

	namespace hash
	{

		template <typename Policy>
		class SHA1_context :
			protected kerbal::hash::detail::SHA1_transform_overload<Policy>
		{
			private:
				typedef kerbal::hash::detail::SHA1_transform_overload<Policy> super;

			protected:
				typedef typename super::uint8_t		uint8_t;
				typedef typename super::uint32_t	uint32_t;

			public:
				typedef detail::SHA1_context_base::result result;

#		if __cplusplus >= 201103L
				constexpr
				SHA1_context() = default;
#		endif

			private:

				template <typename RandomAccessIterator>
				KERBAL_CONSTEXPR14
				void update_helper(
					RandomAccessIterator first, RandomAccessIterator last,
					std::random_access_iterator_tag
				) KERBAL_NOEXCEPT;

			public:
				/*
				 * Run your data through this.
				 */
				template <typename ForwardIterator> // uint8_t
				KERBAL_CONSTEXPR14
				void update(ForwardIterator first, ForwardIterator last) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				void update(const uint8_t * first, const uint8_t * last) KERBAL_NOEXCEPT;

				/**
				 * Add padding and return the message digest.
				 */
				KERBAL_CONSTEXPR14
				result digest() KERBAL_NOEXCEPT;

		};

	} // namespace hash

} // namespace kerbal

#endif // KERBAL_HASH_SHA1_SHA1_DECL_HPP
