/**
 * @file       basic_copy_n.hpp
 * @brief
 * @date       2024-02-20
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_MODIFIER_DETAIL_COPY_N_BASIC_COPY_N_HPP
#define KERBAL_ALGORITHM_MODIFIER_DETAIL_COPY_N_BASIC_COPY_N_HPP

#include <kerbal/assign/generic_assign.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <kerbal/algorithm/modifier/detail/is_memmove_optimizable.hpp>

#if KERBAL_ALGORITHM_COPY_ENABLE_MEMMOVE_OPTIMIZATION
#	include <kerbal/compatibility/is_constant_evaluated.hpp>
#	include <kerbal/iterator/iterator_traits.hpp>

#	include <cstddef>
#	include <cstring>
#endif


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename InputIterator, typename OutputIterator>
			struct basic_copy_n_ret
			{
				InputIterator first;
				OutputIterator second;

				KERBAL_CONSTEXPR
				basic_copy_n_ret(const InputIterator & first, const OutputIterator & second) :
					first(first),
					second(second)
				{
				}

			};

			template <typename InputIterator, typename SizeType, typename OutputIterator>
			KERBAL_CONSTEXPR14
			basic_copy_n_ret<InputIterator, OutputIterator>
			copy_n_memmove_opt_dispatcher(
				InputIterator first, SizeType n, OutputIterator to,
				kerbal::type_traits::false_type
			)
			{
				while (n != 0) {
					kerbal::assign::generic_assign(*to, *first); // *to = *first;
					--n;
					++to;
					++first;
				}
				return basic_copy_n_ret<InputIterator, OutputIterator>(first, to);
			}

#	if KERBAL_ALGORITHM_COPY_ENABLE_MEMMOVE_OPTIMIZATION

			template <typename ContiguousIterator, typename SizeType, typename ContiguousOutputIterator>
			basic_copy_n_ret<ContiguousIterator, ContiguousOutputIterator>
			copy_n_memmove_opt_dispatcher(
				ContiguousIterator first, SizeType n, ContiguousOutputIterator to,
				kerbal::type_traits::true_type
			)
			{
				typedef ContiguousIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

				std::memmove(&*to, &*first, n * sizeof(value_type));
				return basic_copy_n_ret<ContiguousIterator, ContiguousOutputIterator>(first + n, to + n);
			}

#	endif

			template <typename InputIterator, typename SizeType, typename OutputIterator>
			KERBAL_CONSTEXPR14
			basic_copy_n_ret<InputIterator, OutputIterator>
			basic_copy_n(InputIterator first, SizeType n, OutputIterator to)
			{

#	if KERBAL_ALGORITHM_COPY_ENABLE_MEMMOVE_OPTIMIZATION

				typedef kerbal::algorithm::detail::is_memmove_optimizable<InputIterator, OutputIterator> is_memmove_optimizable;

#		if __cplusplus >= 201402L

#			if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT

				return KERBAL_IS_CONSTANT_EVALUATED() ?
					kerbal::algorithm::detail::copy_n_memmove_opt_dispatcher(first, n, to, kerbal::type_traits::false_type()) :
					kerbal::algorithm::detail::copy_n_memmove_opt_dispatcher(first, n, to, is_memmove_optimizable());

#			else

				return kerbal::algorithm::detail::copy_n_memmove_opt_dispatcher(first, n, to, kerbal::type_traits::false_type());

#			endif

#		else

				return kerbal::algorithm::detail::copy_n_memmove_opt_dispatcher(first, n, to, is_memmove_optimizable());

#		endif

#	else
				return kerbal::algorithm::detail::copy_n_memmove_opt_dispatcher(first, n, to, kerbal::type_traits::false_type());
#	endif

			}

		} // namespace detail

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_DETAIL_COPY_N_BASIC_COPY_N_HPP
