/**
 * @file       static_vector_base.impl.hpp
 * @brief
 * @date       2022-03-21
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_STATIC_VECTOR_BASE_STATIC_VECTOR_BASE_IMPL_HPP
#define KERBAL_CONTAINER_DETAIL_STATIC_VECTOR_BASE_STATIC_VECTOR_BASE_IMPL_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/memory/raw_storage_uninitialized.hpp>
#include <kerbal/type_traits/enable_if.hpp>

#include <cstddef>

#include <kerbal/container/detail/static_vector_base/static_vector_base.decl.hpp>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Tp, std::size_t N>
			KERBAL_CONSTEXPR
			static_vector_base<Tp, N>::static_vector_base() KERBAL_NOEXCEPT :
					len(0)
#		if __cplusplus >= 201103L
					, storage()
#		endif
			{
			}

			template <typename Tp, std::size_t N>
			KERBAL_CONSTEXPR14
			static_vector_base<Tp, N>::static_vector_base(const static_vector_base & src) :
					len(0)
#		if __cplusplus >= 201103L
					, storage()
#		endif
			{
				kerbal::memory::raw_storage_uninitialized_copy_n(src.cbegin(), src.len, this->storage);
				this->len = src.len;
			}

#		if __cplusplus >= 201103L

			template <typename Tp, std::size_t N>
			KERBAL_CONSTEXPR14
			static_vector_base<Tp, N>::static_vector_base(static_vector_base && src) :
					len(0)
					, storage()
			{
				kerbal::memory::raw_storage_uninitialized_move_n(src.begin(), src.len, this->storage);
				this->len = src.len;
			}

#		endif

			template <typename Tp, std::size_t N>
			KERBAL_CONSTEXPR14
			static_vector_base<Tp, N>::static_vector_base(size_type n) :
					len(0)
#		if __cplusplus >= 201103L
					, storage()
#		endif
			{
				kerbal::memory::raw_storage_uninitialized_value_construct_n(this->storage, n);
				this->len = n;
			}

			template <typename Tp, std::size_t N>
			KERBAL_CONSTEXPR14
			static_vector_base<Tp, N>::static_vector_base(size_type n, const_reference val) :
					len(0)
#		if __cplusplus >= 201103L
					, storage()
#		endif
			{
				kerbal::memory::raw_storage_uninitialized_fill_n(this->storage, n, val);
				this->len = n;
			}

			template <typename Tp, std::size_t N>
			template <typename InputIterator>
			KERBAL_CONSTEXPR14
			void static_vector_base<Tp, N>::
			k_range_copy_cnstrctr(InputIterator first, InputIterator last,
								  std::input_iterator_tag)
			{
				// input iterator, no throw copy constructible
				// if any exception thrown, static_vector_base will do the cleanup job

				while (this->len != N && static_cast<bool>(first != last)) {
					this->storage[this->len].construct(*first);
					++this->len;
					++first;
				}
			}

			template <typename Tp, std::size_t N>
			template <typename ForwardIterator>
			KERBAL_CONSTEXPR14
			void static_vector_base<Tp, N>::
			k_range_copy_cnstrctr(ForwardIterator first, ForwardIterator last,
								  std::forward_iterator_tag)
			{
				size_type range_len(kerbal::iterator::distance(first, last));
				if (range_len > N) {
					range_len = N;
				}
				kerbal::memory::raw_storage_uninitialized_copy_n(first, range_len, this->storage);
				this->len = range_len;
			}

			template <typename Tp, std::size_t N>
			template <typename InputIterator>
			KERBAL_CONSTEXPR14
			static_vector_base<Tp, N>::static_vector_base(InputIterator first, InputIterator last,
					typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
							, int
					>::type
			) :
					len(0)
#		if __cplusplus >= 201103L
					, storage()
#		endif
			{
				this->k_range_copy_cnstrctr(first, last, kerbal::iterator::iterator_category(first));
			}

			template <typename Tp, std::size_t N>
			KERBAL_CONSTEXPR14
			typename static_vector_base<Tp, N>::iterator
			static_vector_base<Tp, N>::begin() KERBAL_NOEXCEPT
			{
				return iterator(this->storage + 0);
			}

			template <typename Tp, std::size_t N>
			KERBAL_CONSTEXPR14
			typename static_vector_base<Tp, N>::iterator
			static_vector_base<Tp, N>::end() KERBAL_NOEXCEPT
			{
				return iterator(this->storage + this->len);
			}

			template <typename Tp, std::size_t N>
			KERBAL_CONSTEXPR
			typename static_vector_base<Tp, N>::const_iterator
			static_vector_base<Tp, N>::begin() const KERBAL_NOEXCEPT
			{
				return this->cbegin();
			}

			template <typename Tp, std::size_t N>
			KERBAL_CONSTEXPR
			typename static_vector_base<Tp, N>::const_iterator
			static_vector_base<Tp, N>::end() const KERBAL_NOEXCEPT
			{
				return this->cend();
			}

			template <typename Tp, std::size_t N>
			KERBAL_CONSTEXPR
			typename static_vector_base<Tp, N>::const_iterator
			static_vector_base<Tp, N>::cbegin() const KERBAL_NOEXCEPT
			{
				return const_iterator(this->storage + 0);
			}

			template <typename Tp, std::size_t N>
			KERBAL_CONSTEXPR
			typename static_vector_base<Tp, N>::const_iterator
			static_vector_base<Tp, N>::cend() const KERBAL_NOEXCEPT
			{
				return const_iterator(this->storage + this->len);
			}

		} // namespace detail

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_DETAIL_STATIC_VECTOR_BASE_STATIC_VECTOR_BASE_IMPL_HPP
