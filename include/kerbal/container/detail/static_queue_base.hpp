/**
 * @file       static_queue_base.hpp
 * @brief
 * @date       2020-6-6
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_STATIC_QUEUE_BASE_HPP
#define KERBAL_CONTAINER_DETAIL_STATIC_QUEUE_BASE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/raw_storage.hpp>
#include <kerbal/type_traits/is_trivially_destructible.hpp>

#include <cstddef>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <std::size_t N>
			class static_queue_ring_helper
			{
				public:
					typedef std::size_t size_type;

				protected:

					KERBAL_CONSTEXPR
					static size_type next(size_type i) KERBAL_NOEXCEPT
					{
						return i == N ? 0 : i + 1;
					}

					KERBAL_CONSTEXPR
					static size_type prev(size_type i) KERBAL_NOEXCEPT
					{
						return i == 0 ? N : i - 1;
					}
			};

			template <
				typename T, std::size_t N,
				bool is_trivially_destructible =
					kerbal::type_traits::try_test_is_trivially_destructible<T>::IS_TRUE::value
			>
			class static_queue_base;

			template <typename T, std::size_t N>
			class static_queue_base<T, N, false> :
				protected static_queue_ring_helper<N>
			{
				public:
					typedef T				value_type;
					typedef std::size_t		size_type;

				protected:
					typedef kerbal::memory::raw_storage<value_type> storage_type;

				protected:
					size_type ibegin;
					size_type iend;

					kerbal::memory::raw_storage<value_type> storage[N + 1];

					KERBAL_CONSTEXPR20
					static_queue_base() KERBAL_NOEXCEPT :
						ibegin(0), iend(0)
#			if __cplusplus >= 201103L
						, storage()
#			endif
					{
					}

					KERBAL_CONSTEXPR20
					~static_queue_base()
					{
						this->clear();
					}

					KERBAL_CONSTEXPR20
					void clear()
					{
						while (this->ibegin != this->iend) {
							this->storage[this->ibegin].destroy();
							this->ibegin = this->next(this->ibegin);
						}
					}

			};

			template <typename T, std::size_t N>
			class static_queue_base<T, N, true> :
				protected static_queue_ring_helper<N>
			{
				public:
					typedef T				value_type;
					typedef std::size_t		size_type;

				protected:
					typedef kerbal::memory::raw_storage<value_type> storage_type;

				protected:
					size_type ibegin;
					size_type iend;

					kerbal::memory::raw_storage<value_type> storage[N + 1];

					KERBAL_CONSTEXPR
					static_queue_base() KERBAL_NOEXCEPT :
						ibegin(0), iend(0)
#			if __cplusplus >= 201103L
						, storage()
#			endif
					{
					}

					KERBAL_CONSTEXPR14
					void clear() KERBAL_NOEXCEPT
					{
						this->iend = this->ibegin;
					}

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_DETAIL_STATIC_QUEUE_BASE_HPP
