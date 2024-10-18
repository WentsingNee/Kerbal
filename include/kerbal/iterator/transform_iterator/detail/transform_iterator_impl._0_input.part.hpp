/**
 * @file       transform_iterator_impl._0_input.part.hpp
 * @brief
 * @date       2024-10-18
 * @author     Peter
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
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/operators/incr_decr.hpp>
#include <kerbal/type_traits/remove_reference.hpp>
#include <kerbal/utility/declval.hpp>
#include <kerbal/utility/in_place.hpp>
#include <kerbal/utility/member_compress_helper.hpp>


namespace kerbal
{

	namespace iterator
	{

		namespace detail
		{

			template <typename BaseIter, typename Transformer, typename TargetIter>
			class transform_iterator_impl<BaseIter, Transformer, TargetIter, std::input_iterator_tag> :
				kerbal::utility::member_compress_helper<Transformer>,
				// input iterator interface
				public kerbal::operators::incrementable<TargetIter> // it++
			{
				private:
					typedef BaseIter											base_iterator_type;
					typedef kerbal::utility::member_compress_helper<Transformer>
																				transformer_compress_helper;
					typedef transform_iterator_impl								this_type;
					typedef kerbal::iterator::iterator_traits<base_iterator_type>
																				base_iterator_traits;

				protected:
					base_iterator_type k_base_iter;

				protected:
					typedef std::input_iterator_tag								iterator_category;
					typedef typename base_iterator_traits::difference_type		difference_type;
					typedef void												pointer;
					typedef typename Transformer::result_type					reference;
					typedef typename kerbal::type_traits::remove_reference<reference>::type
																				value_type;

				protected:
					KERBAL_CONSTEXPR
					explicit
					transform_iterator_impl() :
						k_base_iter()
					{
					}

					KERBAL_CONSTEXPR
					explicit
					transform_iterator_impl(BaseIter const & base_iter) :
						k_base_iter(base_iter)
					{
					}

					KERBAL_CONSTEXPR
					explicit
					transform_iterator_impl(BaseIter const & base_iter, Transformer const & transformer) :
						transformer_compress_helper(
							kerbal::utility::in_place_t(),
							transformer
						),
						k_base_iter(base_iter)
					{
					}

				public:

					KERBAL_CONSTEXPR
					reference
					operator*() const
					{
						return this->transformer()(*this->k_base_iter);
					}

					KERBAL_CONSTEXPR
					base_iterator_type
					base() const
					{
						return this->k_base_iter;
					}

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

				//===================
				// input iterator interface

					KERBAL_CONSTEXPR14
					TargetIter &
					operator++()
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(
								++(kerbal::utility::declthis<this_type>()->k_base_iter)
							)
						)
					{
						++this->k_base_iter;
						return static_cast<TargetIter &>(*this);
					}

					KERBAL_CONSTEXPR
					friend
					bool operator==(
						const TargetIter & lhs,
						const TargetIter & rhs
					)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(lhs.k_base_iter == rhs.k_base_iter)
						)
					{
						return lhs.k_base_iter == rhs.k_base_iter;
					}

					KERBAL_CONSTEXPR
					friend
					bool operator!=(
						const TargetIter & lhs,
						const TargetIter & rhs
					)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(lhs.k_base_iter != rhs.k_base_iter)
						)
					{
						return lhs.k_base_iter != rhs.k_base_iter;
					}

			};

		} // namespace detail

	} // namespace iterator

} // namespace kerbal

#endif // KERBAL_ITERATOR_TRANSFORM_ITERATOR_DETAIL_TRANSFORM_ITERATOR_IMPL__0_INPUT_PART_HPP
