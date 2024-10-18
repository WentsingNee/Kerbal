/**
 * @file       transform_iterator_impl._0_input.part.hpp
 * @brief
 * @date       2024-10-18
 * @author     peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ITERATOR_TRANSFORM_ITERATOR_DETAIL_TRANSFORM_ITERATOR_IMPL__0_INPUT_PART_HPP
#define KERBAL_ITERATOR_TRANSFORM_ITERATOR_DETAIL_TRANSFORM_ITERATOR_IMPL__0_INPUT_PART_HPP

#include <kerbal/iterator/transform_iterator/transform_iterator.fwd.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/config/compiler_id.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/operators/incr_decr.hpp>
#include <kerbal/utility/declval.hpp>
#include <kerbal/utility/in_place.hpp>
#include <kerbal/utility/member_compress_helper.hpp>


namespace kerbal
{

	namespace iterator
	{

		namespace detail
		{

			template <typename Iter, typename Transformer>
			class transform_iterator_impl<Iter, Transformer, std::input_iterator_tag> :
				kerbal::utility::member_compress_helper<Transformer>,
				// input iterator interface
				public kerbal::operators::incrementable<
					kerbal::iterator::transform_iterator<Iter, Transformer>
				> // it++
			{
				private:
					typedef Iter iterator_type;
					typedef kerbal::utility::member_compress_helper<Transformer>	transformer_compress_helper;

				protected:
					iterator_type iter;

				private:
					typedef transform_iterator_impl								this_type;
					typedef kerbal::iterator::transform_iterator<Iter, Transformer>
																				transform_iterator;
					typedef kerbal::iterator::iterator_traits<Iter>				base_iterator_traits;
					typedef typename base_iterator_traits::reference			base_iterator_reference;

				protected:
					typedef std::input_iterator_tag								iterator_category;
					typedef typename Transformer::result_type					value_type;
					typedef typename base_iterator_traits::difference_type		difference_type;
					typedef iterator_type										pointer;
					typedef typename Transformer::result_type					reference;

				protected:
					KERBAL_CONSTEXPR14
					Transformer &
					transformer() KERBAL_NOEXCEPT
					{
						return transformer_compress_helper::member();
					}

					KERBAL_CONSTEXPR
					Transformer const &
					transformer() const KERBAL_NOEXCEPT
					{
						return transformer_compress_helper::member();
					}

				protected:
					KERBAL_CONSTEXPR
					explicit
					transform_iterator_impl() :
						iter()
					{
					}

					KERBAL_CONSTEXPR
					explicit
					transform_iterator_impl(const Iter & iter) :
						iter(iter)
					{
					}

					KERBAL_CONSTEXPR
					explicit
					transform_iterator_impl(const Iter & iter, Transformer const & transformer) :
						iter(iter),
						transformer_compress_helper(
							kerbal::utility::in_place_t(),
							transformer
						)
					{
					}

				public:

					KERBAL_CONSTEXPR14
					reference
					operator*() const
					{
						return this->transformer()(*this->iter);
					}

					KERBAL_CONSTEXPR
					iterator_type
					base() const
					{
						return this->iter;
					}

				//===================
				// input iterator interface

					KERBAL_CONSTEXPR14
					transform_iterator &
					operator++()
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(
								++(kerbal::utility::declthis<this_type>()->iter)
							)
						)
					{
						++this->iter;
						return static_cast<transform_iterator &>(*this);
					}

					KERBAL_CONSTEXPR14
					friend
					bool operator==(
						const transform_iterator & lhs,
						const transform_iterator & rhs
					)
#		if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC && __cplusplus >= 201703L
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs.iter == rhs.iter))
#		endif
					{
						return lhs.iter == rhs.iter;
					}

					KERBAL_CONSTEXPR14
					friend
					bool operator!=(
						const transform_iterator & lhs,
						const transform_iterator & rhs
					)
#		if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC && __cplusplus >= 201703L
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs.iter != rhs.iter))
#		endif
					{
						return lhs.iter != rhs.iter;
					}

			};

		} // namespace detail

	} // namespace iterator

} // namespace kerbal

#endif // KERBAL_ITERATOR_TRANSFORM_ITERATOR_DETAIL_TRANSFORM_ITERATOR_IMPL__0_INPUT_PART_HPP
