/**
 * @file       move_iterator.cxx11.part.hpp
 * @brief
 * @date       2021-09-01
 * @author     Peter
 * @remark     move from kerbal/iterator/move_iterator.hpp, 2023-08-25
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ITERATOR_MOVE_ITERATOR_DETAIL_MOVE_ITERATOR_CXX11_PART_HPP
#define KERBAL_ITERATOR_MOVE_ITERATOR_DETAIL_MOVE_ITERATOR_CXX11_PART_HPP

#if __cplusplus < 201103L
#	error This file requires compiler and library support for the ISO C++ 2011 standard.
#endif

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/iterator/transform_iterator.hpp>
#include <kerbal/type_traits/add_rvalue_reference.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/is_reference.hpp>

#include <cstddef>

#include "kerbal/iterator/transform_iterator/transform_iterator.decl.hpp"


namespace kerbal
{

	namespace iterator
	{

		namespace detail
		{

			template <typename Iter>
			struct move_iterator_transformer
			{
				private:
					typedef Iter iterator_type;

				private:
					typedef kerbal::iterator::iterator_traits<Iter>			base_iterator_traits;
					typedef typename base_iterator_traits::reference		base_iterator_reference;
					typedef typename base_iterator_traits::value_type		base_iterator_value_type;

				public:
					typedef typename kerbal::type_traits::conditional<
						kerbal::type_traits::is_reference<base_iterator_reference>::value,
						typename kerbal::type_traits::add_rvalue_reference<base_iterator_value_type>::type,
						base_iterator_reference
					>::type 												result_type;

					KERBAL_CONSTEXPR14
					result_type
					operator()(base_iterator_reference x)
					{
						return static_cast<result_type>(x);
					}

			};

		} // namespace detail


		template <typename Iter>
		class move_iterator :
			public kerbal::iterator::transform_iterator<
				Iter,
				kerbal::iterator::detail::move_iterator_transformer<Iter>
			>
		{
			public:
				typedef Iter iterator_type;

			private:
				typedef kerbal::iterator::transform_iterator<
					Iter,
					kerbal::iterator::detail::move_iterator_transformer<Iter>
				> super;

			public:
				typedef typename super::iterator_category		iterator_category;
				typedef typename super::value_type				value_type;
				typedef typename super::difference_type			difference_type;
				typedef typename super::pointer					pointer;
				typedef typename super::reference				reference;

			public:
				KERBAL_CONSTEXPR
				explicit move_iterator() :
					super()
				{
				}

				KERBAL_CONSTEXPR
				explicit move_iterator(const iterator_type & iter) :
					super(iter)
				{
				}

		};

#	if __cplusplus >= 201703L

		template <typename InputIterator>
		move_iterator(const InputIterator &) -> move_iterator<InputIterator>;

#	endif

		template <typename Iter>
		KERBAL_CONSTEXPR
		move_iterator<Iter>
		make_move_iterator(const Iter & iter)
		{
			return move_iterator<Iter>(iter);
		}

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR
		move_iterator<T *>
		make_move_iterator(T (&arr) [N])
		{
			return move_iterator<T *>(arr);
		}

	} // namespace iterator

} // namespace kerbal

#endif // KERBAL_ITERATOR_MOVE_ITERATOR_DETAIL_MOVE_ITERATOR_CXX11_PART_HPP
