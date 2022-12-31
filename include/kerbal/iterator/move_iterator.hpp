/**
 * @file       move_iterator.hpp
 * @brief
 * @date       2021-09-01
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ITERATOR_MOVE_ITERATOR_HPP
#define KERBAL_ITERATOR_MOVE_ITERATOR_HPP

#if __cplusplus < 201103L
#	error This file requires compiler and library support for the ISO C++ 2011 standard.
#endif

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/config/compiler_id.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/operators/addable.hpp>
#include <kerbal/operators/incr_decr.hpp>
#include <kerbal/operators/subtractable.hpp>
#include <kerbal/type_traits/add_rvalue_reference.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/is_reference.hpp>
#include <kerbal/utility/declval.hpp>

#include <cstddef>


namespace kerbal
{

	namespace iterator
	{

		template <typename Iter>
		class move_iterator;


		namespace detail
		{

			template <typename InputIterator, typename IteratorTag>
			class move_iterator_impl;

			template <typename Iter>
			class move_iterator_impl<Iter, std::input_iterator_tag> :
					//input iterator interface
					public kerbal::operators::incrementable<
							kerbal::iterator::move_iterator<Iter>
					> // it++
			{
				private:
					typedef Iter iterator_type;

				protected:
					iterator_type iter;

				private:
					typedef move_iterator_impl								this_type;
					typedef kerbal::iterator::move_iterator<Iter>			move_iterator;
					typedef kerbal::iterator::iterator_traits<Iter>			base_iterator_traits;
					typedef typename base_iterator_traits::reference		base_iterator_reference;

				protected:
					typedef std::input_iterator_tag								iterator_category;
					typedef typename base_iterator_traits::value_type			value_type;
					typedef typename base_iterator_traits::difference_type		difference_type;
					typedef iterator_type										pointer;
					typedef typename kerbal::type_traits::conditional<
							kerbal::type_traits::is_reference<base_iterator_reference>::value,
							typename kerbal::type_traits::add_rvalue_reference<value_type>::type,
							base_iterator_reference
					>::type 													reference;

				protected:
					KERBAL_CONSTEXPR
					explicit move_iterator_impl()
							: iter()
					{
					}

					KERBAL_CONSTEXPR
					explicit move_iterator_impl(const Iter& iter)
							: iter(iter)
					{
					}

				public:

					KERBAL_CONSTEXPR14
					reference operator*() const
					{
						return static_cast<reference>(*iter);
					}

					KERBAL_CONSTEXPR
					iterator_type base() const
					{
						return this->iter;
					}

				//===================
				//input iterator interface

					KERBAL_CONSTEXPR14
					move_iterator& operator++()
							KERBAL_CONDITIONAL_NOEXCEPT(noexcept(++(kerbal::utility::declthis<this_type>()->iter)))
					{
						++this->iter;
						return static_cast<move_iterator&>(*this);
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const move_iterator& lhs, const move_iterator& rhs)
#		if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC && __cplusplus >+ 201703L
							KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs.iter == rhs.iter))
#		endif
					{
						return lhs.iter == rhs.iter;
					}

					friend KERBAL_CONSTEXPR
					bool operator!=(const move_iterator& lhs, const move_iterator& rhs)
#		if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC && __cplusplus >+ 201703L
							KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs.iter != rhs.iter))
#		endif
					{
						return lhs.iter != rhs.iter;
					}

			};

			template <typename Iter>
			class move_iterator_impl<Iter, std::forward_iterator_tag> :
					public move_iterator_impl<Iter, std::input_iterator_tag>
			{
				private:
					typedef move_iterator_impl<Iter, std::input_iterator_tag> super;
					typedef move_iterator_impl this_type;
					typedef kerbal::iterator::move_iterator<Iter> move_iterator;
					typedef kerbal::iterator::iterator_traits<Iter> base_iterator_traits;

				protected:
					typedef std::forward_iterator_tag			iterator_category;
					typedef typename super::value_type			value_type;
					typedef typename super::difference_type		difference_type;
					typedef typename super::pointer				pointer;
					typedef typename super::reference			reference;

				protected:
					KERBAL_CONSTEXPR
					explicit move_iterator_impl()
							: super()
					{
					}

					KERBAL_CONSTEXPR
					explicit move_iterator_impl(const Iter& iter)
							: super(iter)
					{
					}

			};

			template <typename Iter>
			class move_iterator_impl<Iter, std::bidirectional_iterator_tag> :
					public move_iterator_impl<Iter, std::forward_iterator_tag>,

					//bidirectional iterator interface
					public kerbal::operators::decrementable<
							kerbal::iterator::move_iterator<Iter>
					> // it--
			{
				private:
					typedef move_iterator_impl<Iter, std::forward_iterator_tag> super;
					typedef move_iterator_impl this_type;
					typedef kerbal::iterator::move_iterator<Iter> move_iterator;
					typedef kerbal::iterator::iterator_traits<Iter> base_iterator_traits;

				protected:
					typedef std::bidirectional_iterator_tag		iterator_category;
					typedef typename super::value_type			value_type;
					typedef typename super::difference_type		difference_type;
					typedef typename super::pointer				pointer;
					typedef typename super::reference			reference;

				protected:
					KERBAL_CONSTEXPR
					explicit move_iterator_impl()
							: super()
					{
					}

					KERBAL_CONSTEXPR
					explicit move_iterator_impl(const Iter& iter)
							: super(iter)
					{
					}

				public:

				//===================
				//bidirectional iterator interface

					KERBAL_CONSTEXPR14
					move_iterator& operator--()
					KERBAL_CONDITIONAL_NOEXCEPT(noexcept(--kerbal::utility::declthis<this_type>()->iter))
					{
						--this->iter;
						return static_cast<move_iterator&>(*this);
					}

			};

			template <typename Iter>
			class move_iterator_impl<Iter, std::random_access_iterator_tag> :
					public move_iterator_impl<Iter, std::bidirectional_iterator_tag>,

					//random access iterator interface
					public kerbal::operators::addable<
							kerbal::iterator::move_iterator<Iter>,
							typename kerbal::iterator::iterator_traits<Iter>::difference_type
					>, // it + N
					public kerbal::operators::addable_left<
							kerbal::iterator::move_iterator<Iter>,
							typename kerbal::iterator::iterator_traits<Iter>::difference_type
					>, // N + it
					public kerbal::operators::subtractable<
							kerbal::iterator::move_iterator<Iter>,
							typename kerbal::iterator::iterator_traits<Iter>::difference_type
					> // it - N
			{
				private:
					typedef move_iterator_impl<Iter, std::bidirectional_iterator_tag> super;
					typedef move_iterator_impl this_type;
					typedef kerbal::iterator::move_iterator<Iter> move_iterator;
					typedef kerbal::iterator::iterator_traits<Iter> base_iterator_traits;

				protected:
					typedef std::random_access_iterator_tag		iterator_category;
					typedef typename super::value_type			value_type;
					typedef typename super::difference_type		difference_type;
					typedef typename super::pointer				pointer;
					typedef typename super::reference			reference;

				protected:
					KERBAL_CONSTEXPR
					explicit move_iterator_impl()
							: super()
					{
					}

					KERBAL_CONSTEXPR
					explicit move_iterator_impl(const Iter& iter)
							: super(iter)
					{
					}

				public:

				//===================
				//random access iterator interface

					friend KERBAL_CONSTEXPR
					difference_type
					operator-(const move_iterator& lhs, const move_iterator& rhs)
#		if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC && __cplusplus >+ 201703L
							KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs.iter - rhs.iter))
#		endif
					{
						return lhs.iter - rhs.iter;
					}

					KERBAL_CONSTEXPR14
					move_iterator& operator+=(const difference_type& delta)
							KERBAL_CONDITIONAL_NOEXCEPT(noexcept(kerbal::utility::declthis<this_type>()->iter += delta))
					{
						this->iter += delta;
						return static_cast<move_iterator&>(*this);
					}

					KERBAL_CONSTEXPR14
					move_iterator& operator-=(const difference_type& delta)
							KERBAL_CONDITIONAL_NOEXCEPT(noexcept(kerbal::utility::declthis<this_type>()->iter -= delta))
					{
						this->iter -= delta;
						return static_cast<move_iterator&>(*this);
					}

					KERBAL_CONSTEXPR14
					reference operator[](const difference_type& dist) const
					{
						return *(static_cast<const move_iterator&>(*this) + dist);
					}

					friend KERBAL_CONSTEXPR
					bool operator<(const move_iterator& lhs, const move_iterator& rhs)
#		if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC && __cplusplus >+ 201703L
							KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs.iter < rhs.iter))
#		endif
					{
						return lhs.iter < rhs.iter;
					}

					friend KERBAL_CONSTEXPR
					bool operator<=(const move_iterator& lhs, const move_iterator& rhs)
#		if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC && __cplusplus >+ 201703L
							KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs.iter <= rhs.iter))
#		endif
					{
						return lhs.iter <= rhs.iter;
					}

					friend KERBAL_CONSTEXPR
					bool operator>(const move_iterator& lhs, const move_iterator& rhs)
#		if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC && __cplusplus >+ 201703L
							KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs.iter > rhs.iter))
#		endif
					{
						return lhs.iter > rhs.iter;
					}

					friend KERBAL_CONSTEXPR
					bool operator>=(const move_iterator& lhs, const move_iterator& rhs)
#		if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC && __cplusplus >+ 201703L
							KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs.iter >= rhs.iter))
#		endif
					{
						return lhs.iter >= rhs.iter;
					}

			};

		} // namespace detail

		template <typename Iter>
		class move_iterator :
				public kerbal::iterator::detail::move_iterator_impl<Iter, typename kerbal::iterator::iterator_traits<Iter>::iterator_category>
		{
			public:
				typedef Iter iterator_type;

			private:
				typedef kerbal::iterator::detail::move_iterator_impl<iterator_type, typename kerbal::iterator::iterator_traits<iterator_type>::iterator_category> super;

			public:
				typedef typename super::iterator_category		iterator_category;
				typedef typename super::value_type				value_type;
				typedef typename super::difference_type			difference_type;
				typedef typename super::pointer					pointer;
				typedef typename super::reference				reference;

			public:
				KERBAL_CONSTEXPR
				explicit move_iterator()
						: super()
				{
				}

				KERBAL_CONSTEXPR
				explicit move_iterator(const iterator_type& iter)
						: super(iter)
				{
				}

		};

#	if __cplusplus >= 201703L

		template <typename InputIterator>
		move_iterator(const InputIterator&) -> move_iterator<InputIterator>;

#	endif

		template <typename Iter>
		KERBAL_CONSTEXPR
		move_iterator<Iter>
		make_move_iterator(const Iter& iter)
		{
			return move_iterator<Iter>(iter);
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR
		move_iterator<Tp*>
		make_move_iterator(Tp (&arr) [N])
		{
			return move_iterator<Tp*>(arr);
		}

	} // namespace iterator

} // namespace kerbal

#endif // KERBAL_ITERATOR_MOVE_ITERATOR_HPP
