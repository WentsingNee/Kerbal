/**
 * @file       static_vector_base.hpp
 * @brief
 * @date       2020-6-5
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_STATIC_VECTOR_BASE_HPP
#define KERBAL_CONTAINER_DETAIL_STATIC_VECTOR_BASE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/container/detail/static_container_trivially_destructible_traits.hpp>
#include <kerbal/data_struct/raw_storage.hpp>

#include <cstddef>

namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Tp, size_t N, bool is_trivially_destructible =
					kerbal::container::detail::static_container_trivially_destructible_traits<Tp>::value>
			class static_vector_base;

			template <typename Tp, size_t N>
			class static_vector_base<Tp, N, false>
			{
				public:
					typedef Tp			value_type;
					typedef size_t		size_type;

				protected:
					typedef kerbal::data_struct::raw_storage<value_type> storage_type;

				protected:
					size_type len;

					storage_type storage[N];

					KERBAL_CONSTEXPR
					static_vector_base() KERBAL_NOEXCEPT
#			if __cplusplus >= 201103L
							: len(0), storage{}
#			else
							: len(0)
#			endif
					{
					}

					KERBAL_CONSTEXPR20
					~static_vector_base() KERBAL_NOEXCEPT
					{
						while (this->len != 0) {
							--this->len;
							this->storage[this->len].destroy();
						}
					}

			};

			template <typename Tp, size_t N>
			class static_vector_base<Tp, N, true>
			{
				public:
					typedef Tp			value_type;
					typedef size_t		size_type;

				protected:
					typedef kerbal::data_struct::raw_storage<value_type> storage_type;

				protected:
					size_type len;

					storage_type storage[N];

					KERBAL_CONSTEXPR
					static_vector_base() KERBAL_NOEXCEPT
#			if __cplusplus >= 201103L
							: len(0), storage{}
#			else
							: len(0)
#			endif
					{
					}
			};

		} // namespace detail

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_DETAIL_STATIC_VECTOR_BASE_HPP
