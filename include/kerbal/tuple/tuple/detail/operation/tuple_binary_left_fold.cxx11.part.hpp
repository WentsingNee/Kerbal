/**
 * @file       tuple_binary_left_fold.cxx11.part.hpp
 * @brief
 * @date       2023-10-20
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TUPLE_TUPLE_DETAIL_OPERATION_TUPLE_BINARY_LEFT_FOLD_CXX11_PART_HPP
#define KERBAL_TUPLE_TUPLE_DETAIL_OPERATION_TUPLE_BINARY_LEFT_FOLD_CXX11_PART_HPP

namespace kerbal
{

	namespace utility
	{

		namespace detail
		{

			template <typename TupleSelf, typename Folded, typename F, std::size_t N>
			struct tuple_binary_left_fold_result;

			template <typename TupleSelf, typename Folded, typename F, std::size_t N, bool>
			struct tuple_binary_left_fold_result_impl;

			template <typename TupleSelf, typename Folded, typename F, std::size_t N>
			struct tuple_binary_left_fold_result_impl<TupleSelf, Folded, F, N, true>
			{
					typedef Folded type;
			};

			template <typename TupleSelf, typename Folded, typename F, std::size_t N>
			struct tuple_binary_left_fold_result_impl<TupleSelf, Folded, F, N, false>
			{
				private:
					typedef typename tuple_binary_left_fold_result<
						TupleSelf,
						decltype(
							kerbal::utility::declval<F>()(
								kerbal::utility::declval<Folded>(),
								kerbal::utility::declval<TupleSelf>().template get<N>()
							)
						),
						F,
						N + 1
					>::type type0;

				public:
					typedef typename kerbal::type_traits::conditional<
						kerbal::type_traits::is_rvalue_reference<type0>::value,
						typename kerbal::type_traits::remove_reference<type0>::type,
						type0
					>::type type;
			};

			template <typename TupleSelf, typename Folded, typename F, std::size_t N>
			struct tuple_binary_left_fold_result :
				tuple_binary_left_fold_result_impl<TupleSelf, Folded, F, N, N == kerbal::type_traits::remove_reference<TupleSelf>::type::TUPLE_SIZE::value>
			{
			};

			template <typename Tuple, typename Folded, typename F, std::size_t N>
			KERBAL_CONSTEXPR
			auto
			tuple_binary_left_fold(
				Tuple && t, Folded && folded, F f,
				kerbal::type_traits::integral_constant<std::size_t, N>
			) ->
				typename tuple_binary_left_fold_result<Tuple &&, Folded &&, F, N>::type;

			template <typename Tuple, typename Folded, typename F, std::size_t N>
			KERBAL_CONSTEXPR
			Folded &&
			tuple_binary_left_fold_impl(
				Tuple && /*self*/, Folded && folded, F /*f*/,
				kerbal::type_traits::integral_constant<std::size_t, N>,
				kerbal::type_traits::true_type
			)
			{
				return kerbal::utility::forward<Folded>(folded);
			}

			template <typename Tuple, typename Folded, typename F, std::size_t N>
			KERBAL_CONSTEXPR
			auto
			tuple_binary_left_fold_impl(
				Tuple && t, Folded && folded, F f,
				kerbal::type_traits::integral_constant<std::size_t, N>,
				kerbal::type_traits::false_type
			) ->
				typename tuple_binary_left_fold_result<Tuple &&, Folded &&, F, N>::type
			{
				return tuple_binary_left_fold(
					kerbal::utility::forward<Tuple>(t),
					f(kerbal::utility::forward<Folded>(folded), kerbal::utility::forward<Tuple>(t).template get<N>()),
					f,
					kerbal::type_traits::integral_constant<std::size_t, N + 1>()
				);
			}

			template <typename Tuple, typename Folded, typename F, std::size_t N>
			KERBAL_CONSTEXPR
			auto
			tuple_binary_left_fold(
				Tuple && t, Folded && folded, F f,
				kerbal::type_traits::integral_constant<std::size_t, N> index
			) ->
				typename tuple_binary_left_fold_result<Tuple &&, Folded &&, F, N>::type
			{
				typedef typename kerbal::type_traits::remove_reference<Tuple>::type TupleRemoveRef;
				return tuple_binary_left_fold_impl(
					kerbal::utility::forward<Tuple>(t),
					kerbal::utility::forward<Folded>(folded),
					f,
					index,
					kerbal::type_traits::bool_constant<N == TupleRemoveRef::TUPLE_SIZE::value>()
				);
			}


		} // namespace detail

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_TUPLE_TUPLE_DETAIL_OPERATION_TUPLE_BINARY_LEFT_FOLD_CXX11_PART_HPP
