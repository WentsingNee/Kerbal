/**
 * @file       vector_base.hpp
 * @brief
 * @date       2020-08-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_VECTOR_BASE_HPP
#define KERBAL_CONTAINER_DETAIL_VECTOR_BASE_HPP

#include <kerbal/container/detail/vector_iterator.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/reverse_iterator.hpp>
#include <kerbal/type_traits/array_traits.hpp>
#include <kerbal/utility/member_compress_helper.hpp>

#include <limits>

#if __cplusplus >= 201103L
#	include <type_traits>
#endif

namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Tp>
			class vector_allocator_unrelated
			{
				protected:
					typedef Tp							value_type;
					typedef const value_type			const_type;
					typedef value_type&					reference;
					typedef const value_type&			const_reference;
					typedef value_type*					pointer;
					typedef const value_type*			const_pointer;

#		if __cplusplus >= 201103L
					typedef value_type&&				rvalue_reference;
					typedef const value_type&&			const_rvalue_reference;
#		endif

					typedef std::size_t					size_type;
					typedef std::ptrdiff_t				difference_type;

					typedef typename kerbal::type_traits::remove_all_extents<value_type>::type remove_all_extents_t;

					typedef kerbal::container::detail::vec_iter<value_type>		iterator;
					typedef kerbal::container::detail::vec_kiter<value_type>	const_iterator;
					typedef kerbal::iterator::reverse_iterator<iterator>		reverse_iterator;
					typedef kerbal::iterator::reverse_iterator<const_iterator>	const_reverse_iterator;

				protected:
					pointer _K_p;
					size_type _K_size;
					size_type _K_capacity;

					KERBAL_CONSTEXPR20
					vector_allocator_unrelated() KERBAL_NOEXCEPT;

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR20
					vector_allocator_unrelated(vector_allocator_unrelated && src) KERBAL_NOEXCEPT;

#			endif

					KERBAL_CONSTEXPR20
					iterator begin() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					iterator end() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_iterator begin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_iterator end() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_iterator cbegin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_iterator cend() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					reverse_iterator rbegin() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					reverse_iterator rend() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_reverse_iterator rbegin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_reverse_iterator rend() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_reverse_iterator crbegin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_reverse_iterator crend() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					iterator nth(size_type index);

					KERBAL_CONSTEXPR20
					const_iterator nth(size_type index) const;

					KERBAL_CONSTEXPR20
					size_type index_of(iterator it);

					KERBAL_CONSTEXPR20
					size_type index_of(const_iterator it) const;

					KERBAL_CONSTEXPR20
					size_type size() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					size_type capacity() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR
					size_type max_size() const KERBAL_NOEXCEPT
					{
						return -1;
					}

					KERBAL_CONSTEXPR20
					bool empty() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					reference operator[](size_type index) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_reference operator[](size_type index) const KERBAL_NOEXCEPT;

					reference at(size_type index);
					const_reference at(size_type index) const;

					KERBAL_CONSTEXPR20
					reference front();

					KERBAL_CONSTEXPR20
					const_reference front() const;

					KERBAL_CONSTEXPR20
					reference back();

					KERBAL_CONSTEXPR20
					const_reference back() const;

					KERBAL_CONSTEXPR20
					const_pointer data() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					static void _K_swap(vector_allocator_unrelated & lhs, vector_allocator_unrelated & rhs) KERBAL_NOEXCEPT;

			};


			template <typename Allocator>
			class vector_allocator_overload:
					private kerbal::utility::member_compress_helper<Allocator>
			{
				private:
					typedef kerbal::utility::member_compress_helper<Allocator> super;

				protected:
					typedef Allocator allocator_type;

				protected:

					KERBAL_CONSTEXPR
					vector_allocator_overload()
								KERBAL_CONDITIONAL_NOEXCEPT(
										std::is_nothrow_default_constructible<super>::value
								)
							: super(kerbal::utility::in_place_t())
					{
					}

					KERBAL_CONSTEXPR
					explicit
					vector_allocator_overload(const allocator_type & allocator)
								KERBAL_CONDITIONAL_NOEXCEPT(
										std::is_nothrow_copy_constructible<super>::value
								)
							: super(kerbal::utility::in_place_t(), allocator)
					{
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR
					explicit
					vector_allocator_overload(allocator_type && allocator)
								KERBAL_CONDITIONAL_NOEXCEPT(
										std::is_nothrow_move_constructible<super>::value
								)
							: super(kerbal::utility::in_place_t(), kerbal::compatibility::move(allocator))
					{
					}

#			endif

					KERBAL_CONSTEXPR14
					allocator_type& alloc() KERBAL_NOEXCEPT
					{
						return super::member();
					}

					KERBAL_CONSTEXPR14
					const allocator_type& alloc() const KERBAL_NOEXCEPT
					{
						return super::member();
					}

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#include <kerbal/container/impl/vector_base.impl.hpp>

#endif // KERBAL_CONTAINER_DETAIL_VECTOR_BASE_HPP
