/**
 * @file       md5.decl.hpp
 * @brief
 * @date       20020-08-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_HASH_MD5_MD5_DECL_HPP
#define KERBAL_HASH_MD5_MD5_DECL_HPP

#include <kerbal/hash/md5/md5.fwd.hpp>
#include <kerbal/hash/md5/detail/md5_transform_overload.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#include <cstddef>


namespace kerbal
{

	namespace hash
	{

		template <typename Policy>
		class MD5_context :
			protected kerbal::hash::detail::MD5_transform_overload<Policy>
		{
			private:
				typedef kerbal::hash::detail::MD5_transform_overload<Policy> super;

			protected:
				typedef typename super::uint8_t		uint8_t;
				typedef typename super::uint32_t	uint32_t;

			public:
				typedef detail::MD5_context_base::result result;

#		if __cplusplus >= 201103L
				constexpr
				MD5_context() = default;
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

#endif // KERBAL_HASH_MD5_MD5_DECL_HPP
