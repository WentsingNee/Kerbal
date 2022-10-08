/**
 * @file       reverse_iterator.hpp
 * @brief
 * @date       2020-4-20
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ITERATOR_REVERSE_ITERATOR_HPP
#define KERBAL_ITERATOR_REVERSE_ITERATOR_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/config/cuda.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/operators/addable.hpp>
#include <kerbal/operators/dereferenceable.hpp>
#include <kerbal/operators/incr_decr.hpp>
#include <kerbal/operators/subtractable.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/remove_cv.hpp>
#include <kerbal/utility/declval.hpp>

#include <cstddef>

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/is_nothrow_copy_constructible.hpp>
#	include <kerbal/type_traits/is_nothrow_default_constructible.hpp>
#endif


namespace kerbal
{

	namespace iterator
	{

		namespace detail
		{

			template <typename BidirectionalIterator>
			struct reverse_iterator_base_is_inplace :
				kerbal::type_traits::false_type
			{
			};

			template <typename T>
			struct reverse_iterator_base_is_inplace<T *> :
				kerbal::type_traits::true_type
			{
			};

		} // namespace detail

		template <
			typename Iter,
			bool IsInplace = kerbal::iterator::detail::reverse_iterator_base_is_inplace<
				typename kerbal::type_traits::remove_cv<Iter>::type
			>::value
		>
		class reverse_iterator;


		namespace detail
		{

			template <typename BidirectionalIterator, bool IsInplace>
			class reverse_iterator_base;


			template <typename BidirectionalIterator>
			class reverse_iterator_base<BidirectionalIterator, false>
			{
				private:
					typedef BidirectionalIterator iterator_type;
					typedef kerbal::iterator::iterator_traits<iterator_type> iterator_traits;

					typedef typename iterator_traits::reference				reference;

				public:
					typedef kerbal::type_traits::false_type					is_inplace_base;

				protected:
					iterator_type iter;

					KERBAL_CONSTEXPR
					explicit reverse_iterator_base()
						KERBAL_CONDITIONAL_NOEXCEPT(
							kerbal::type_traits::try_test_is_nothrow_default_constructible<
								iterator_type
							>::IS_TRUE::value
						) :
						iter()
					{
					}

					KERBAL_CONSTEXPR
					explicit reverse_iterator_base(const iterator_type & iter)
						KERBAL_CONDITIONAL_NOEXCEPT(
							kerbal::type_traits::try_test_is_nothrow_copy_constructible<
								iterator_type
							>::IS_TRUE::value
						) :
						iter(iter)
					{
					}

				public:
					KERBAL_CONSTEXPR14
					KERBAL_CUDA_HOST KERBAL_CUDA_DEVICE
					reference operator*() const
					{
						return *kerbal::iterator::prev(iter);
					}

					KERBAL_CONSTEXPR
					KERBAL_CUDA_HOST KERBAL_CUDA_DEVICE
					iterator_type base() const KERBAL_NOEXCEPT
					{
						return this->iter;
					}
			};

			template <typename BidirectionalIterator>
			class reverse_iterator_base<BidirectionalIterator, true>
			{
				private:
					typedef BidirectionalIterator iterator_type;
					typedef kerbal::iterator::iterator_traits<iterator_type> iterator_traits;

					typedef typename iterator_traits::reference				reference;

				public:
					typedef kerbal::type_traits::true_type					is_inplace_base;

				protected:
					iterator_type iter;

					KERBAL_CONSTEXPR
					explicit reverse_iterator_base() :
						iter(kerbal::iterator::prev(iterator_type()))
					{
					}

					KERBAL_CONSTEXPR
					explicit reverse_iterator_base(const iterator_type & iter) :
						iter(kerbal::iterator::prev(iter))
					{
					}

				public:
					KERBAL_CONSTEXPR14
					KERBAL_CUDA_HOST KERBAL_CUDA_DEVICE
					reference operator*() const
					{
						return *iter;
					}

					KERBAL_CONSTEXPR
					KERBAL_CUDA_HOST KERBAL_CUDA_DEVICE
					iterator_type base() const
					{
						return kerbal::iterator::next(this->iter);
					}
			};

			template <typename BidirectionalIterator, typename IteratorTag, bool IsInplace>
			class reverse_iterator_impl;

			template <typename Iter, bool IsInplace>
			class reverse_iterator_impl<Iter, std::bidirectional_iterator_tag, IsInplace> :
				public kerbal::iterator::detail::reverse_iterator_base<Iter, IsInplace>,

				// input iterator interface
				public kerbal::operators::dereferenceable<
					kerbal::iterator::reverse_iterator<Iter, IsInplace>,
					typename kerbal::iterator::iterator_traits<Iter>::pointer
				>, // it->
				public kerbal::operators::incrementable<
					kerbal::iterator::reverse_iterator<Iter, IsInplace>
				>, // it++

				// bidirectional iterator interface
				public kerbal::operators::decrementable<
					kerbal::iterator::reverse_iterator<Iter, IsInplace>
				> // it--
			{
				private:
					typedef kerbal::iterator::detail::reverse_iterator_base<Iter, IsInplace> super;
					typedef reverse_iterator_impl this_type;
					typedef kerbal::iterator::reverse_iterator<Iter, IsInplace> reverse_iterator;
					typedef kerbal::iterator::iterator_traits<Iter> base_iterator_traits;

				protected:
					typedef std::bidirectional_iterator_tag						iterator_category;
					typedef typename base_iterator_traits::value_type			value_type;
					typedef typename base_iterator_traits::difference_type		difference_type;
					typedef typename base_iterator_traits::pointer				pointer;
					typedef typename base_iterator_traits::reference			reference;

				protected:
					KERBAL_CONSTEXPR
					explicit reverse_iterator_impl() :
						super()
					{
					}

					KERBAL_CONSTEXPR
					explicit reverse_iterator_impl(const Iter & iter) :
						super(iter)
					{
					}

				public:

				//===================
				// input iterator interface

					KERBAL_CONSTEXPR14
					KERBAL_CUDA_HOST KERBAL_CUDA_DEVICE
					reverse_iterator & operator++()
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(
								--(kerbal::utility::declthis<this_type>()->iter)
							)
						)
					{
						--this->iter;
						return static_cast<reverse_iterator &>(*this);
					}

					KERBAL_CONSTEXPR
					KERBAL_CUDA_HOST KERBAL_CUDA_DEVICE
					friend
					bool operator==(const reverse_iterator & lhs, const reverse_iterator & rhs)
#	if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_ICC
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs.iter == rhs.iter))
#	endif
					{
						return lhs.iter == rhs.iter;
					}

					KERBAL_CONSTEXPR
					KERBAL_CUDA_HOST KERBAL_CUDA_DEVICE
					friend
					bool operator!=(const reverse_iterator & lhs, const reverse_iterator & rhs)
#	if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_ICC
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs.iter != rhs.iter))
#	endif
					{
						return lhs.iter != rhs.iter;
					}

				//===================
				// bidirectional iterator interface

					KERBAL_CONSTEXPR14
					KERBAL_CUDA_HOST KERBAL_CUDA_DEVICE
					reverse_iterator & operator--()
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(
								++kerbal::utility::declthis<this_type>()->iter
							)
						)
					{
						++this->iter;
						return static_cast<reverse_iterator &>(*this);
					}

			};

			template <typename Iter, bool IsInplace>
			class reverse_iterator_impl<Iter, std::random_access_iterator_tag, IsInplace> :
				public reverse_iterator_impl<Iter, std::bidirectional_iterator_tag, IsInplace>,

				// random access iterator interface
				public kerbal::operators::addable<
					kerbal::iterator::reverse_iterator<Iter, IsInplace>,
					typename kerbal::iterator::iterator_traits<Iter>::difference_type
				>, // it + N
				public kerbal::operators::addable_left<
					kerbal::iterator::reverse_iterator<Iter, IsInplace>,
					typename kerbal::iterator::iterator_traits<Iter>::difference_type
				>, // N + it
				public kerbal::operators::subtractable<
					kerbal::iterator::reverse_iterator<Iter, IsInplace>,
					typename kerbal::iterator::iterator_traits<Iter>::difference_type
				> // it - N
			{
				private:
					typedef reverse_iterator_impl<Iter, std::bidirectional_iterator_tag, IsInplace> super;
					typedef reverse_iterator_impl this_type;
					typedef kerbal::iterator::reverse_iterator<Iter, IsInplace> reverse_iterator;
					typedef kerbal::iterator::iterator_traits<Iter> base_iterator_traits;

				protected:
					typedef std::random_access_iterator_tag						iterator_category;
					typedef typename base_iterator_traits::value_type			value_type;
					typedef typename base_iterator_traits::difference_type		difference_type;
					typedef typename base_iterator_traits::pointer				pointer;
					typedef typename base_iterator_traits::reference			reference;

				protected:
					KERBAL_CONSTEXPR
					explicit reverse_iterator_impl() :
						super()
					{
					}

					KERBAL_CONSTEXPR
					explicit reverse_iterator_impl(const Iter & iter) :
						super(iter)
					{
					}

				public:

				//===================
				// random access iterator interface

					KERBAL_CONSTEXPR
					KERBAL_CUDA_HOST KERBAL_CUDA_DEVICE
					friend
					difference_type
					operator-(const reverse_iterator & lhs, const reverse_iterator & rhs)
#	if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_ICC
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(rhs.iter - lhs.iter))
#	endif
					{
						return rhs.iter - lhs.iter;
					}

					KERBAL_CONSTEXPR14
					KERBAL_CUDA_HOST KERBAL_CUDA_DEVICE
					reverse_iterator & operator+=(const difference_type & delta)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(
								kerbal::utility::declthis<this_type>()->iter -= delta
							)
						)
					{
						this->iter -= delta;
						return static_cast<reverse_iterator &>(*this);
					}

					KERBAL_CONSTEXPR14
					KERBAL_CUDA_HOST KERBAL_CUDA_DEVICE
					reverse_iterator & operator-=(const difference_type & delta)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(
								kerbal::utility::declthis<this_type>()->iter += delta
							)
						)
					{
						this->iter += delta;
						return static_cast<reverse_iterator &>(*this);
					}

					KERBAL_CONSTEXPR14
					KERBAL_CUDA_HOST KERBAL_CUDA_DEVICE
					reference operator[](const difference_type & dist) const
					{
						return *(static_cast<const reverse_iterator &>(*this) + dist);
					}

					KERBAL_CONSTEXPR
					KERBAL_CUDA_HOST KERBAL_CUDA_DEVICE
					friend
					bool operator<(const reverse_iterator & lhs, const reverse_iterator & rhs)
#	if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_ICC
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs.iter > rhs.iter))
#	endif
					{
						return lhs.iter > rhs.iter;
					}

					KERBAL_CONSTEXPR
					KERBAL_CUDA_HOST KERBAL_CUDA_DEVICE
					friend
					bool operator<=(const reverse_iterator & lhs, const reverse_iterator & rhs)
#	if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_ICC
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs.iter >= rhs.iter))
#	endif
					{
						return lhs.iter >= rhs.iter;
					}

					KERBAL_CONSTEXPR
					KERBAL_CUDA_HOST KERBAL_CUDA_DEVICE
					friend
					bool operator>(const reverse_iterator & lhs, const reverse_iterator & rhs)
#	if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_ICC
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs.iter < rhs.iter))
#	endif
					{
						return lhs.iter < rhs.iter;
					}

					KERBAL_CONSTEXPR
					KERBAL_CUDA_HOST KERBAL_CUDA_DEVICE
					friend
					bool operator>=(const reverse_iterator & lhs, const reverse_iterator & rhs)
#	if KERBAL_COMPILER_ID != KERBAL_COMPILER_ID_ICC
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs.iter <= rhs.iter))
#	endif
					{
						return lhs.iter <= rhs.iter;
					}

			};

		} // namespace detail

		template <typename Iter, bool IsInplace>
		class reverse_iterator :
			public kerbal::iterator::detail::reverse_iterator_impl<
				Iter,
				typename kerbal::iterator::iterator_traits<Iter>::iterator_category,
				IsInplace
			>
		{
			public:
				typedef Iter iterator_type;

			private:
				typedef kerbal::iterator::detail::reverse_iterator_impl<
					iterator_type,
					typename kerbal::iterator::iterator_traits<iterator_type>::iterator_category,
					IsInplace
				> super;

			public:
				typedef typename super::iterator_category		iterator_category;
				typedef typename super::value_type				value_type;
				typedef typename super::difference_type			difference_type;
				typedef typename super::pointer					pointer;
				typedef typename super::reference				reference;

			public:
				KERBAL_CONSTEXPR
				explicit reverse_iterator() :
					super()
				{
				}

				KERBAL_CONSTEXPR
				explicit reverse_iterator(const iterator_type & iter) :
					super(iter)
				{
				}

		};

#	if __cplusplus >= 201703L

		template <typename BidirectionalIterator>
		reverse_iterator(const BidirectionalIterator &) ->
		reverse_iterator<BidirectionalIterator>;

#	endif

		template <typename Iter>
		KERBAL_CONSTEXPR
		KERBAL_CUDA_HOST KERBAL_CUDA_DEVICE
		reverse_iterator<Iter>
		make_reverse_iterator(const Iter & iter)
		{
			return reverse_iterator<Iter>(iter);
		}

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR
		KERBAL_CUDA_HOST KERBAL_CUDA_DEVICE
		reverse_iterator<T *, false>
		make_reverse_iterator(T (&arr) [N])
		{
			return reverse_iterator<T *, false>(arr);
		}

	} // namespace iterator

} // namespace kerbal

#endif // KERBAL_ITERATOR_REVERSE_ITERATOR_HPP
