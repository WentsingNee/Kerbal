/**
 * @file       is_memmove_optimizable.hpp
 * @brief
 * @date       2024-01-21
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_MODIFIER_DETAIL_IS_MEMMOVE_OPTIMIZABLE_HPP
#define KERBAL_ALGORITHM_MODIFIER_DETAIL_IS_MEMMOVE_OPTIMIZABLE_HPP


#ifndef KERBAL_ALGORITHM_COPY_ENABLE_MEMMOVE_OPTIMIZATION

#	if __cplusplus >= 201402L
#		include <kerbal/compatibility/is_constant_evaluated.hpp>
#		if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
#			define KERBAL_ALGORITHM_COPY_ENABLE_MEMMOVE_OPTIMIZATION 1
#		else
#			define KERBAL_ALGORITHM_COPY_ENABLE_MEMMOVE_OPTIMIZATION 0
#		endif
#	else
#		define KERBAL_ALGORITHM_COPY_ENABLE_MEMMOVE_OPTIMIZATION 1
#	endif

#endif


#if KERBAL_ALGORITHM_COPY_ENABLE_MEMMOVE_OPTIMIZATION

#	include <kerbal/iterator/iterator_traits.hpp>
#	include <kerbal/type_traits/integral_constant.hpp>
#	include <kerbal/type_traits/is_same.hpp>
#	include <kerbal/type_traits/is_trivially_copyable.hpp>
#	include <kerbal/type_traits/is_volatile.hpp>
#	include <kerbal/type_traits/remove_const.hpp>

#endif


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

#	if KERBAL_ALGORITHM_COPY_ENABLE_MEMMOVE_OPTIMIZATION

			template <typename InputIterator, typename OutputIterator>
			struct is_memmove_optimizable_helper
			{
				private:
					typedef typename kerbal::iterator::iterator_traits<InputIterator>::value_type input_value_type;
					typedef typename kerbal::iterator::iterator_traits<OutputIterator>::value_type output_value_type;

				public:
					typedef kerbal::type_traits::bool_constant<
						kerbal::iterator::is_contiguous_iterator<InputIterator>::value &&
						!kerbal::type_traits::is_volatile<input_value_type>::value &&
						kerbal::type_traits::try_test_is_trivially_copyable<input_value_type>::IS_TRUE::value &&
						kerbal::iterator::is_contiguous_iterator<OutputIterator>::value &&
						!kerbal::type_traits::is_volatile<output_value_type>::value &&
						kerbal::type_traits::is_same<
							typename kerbal::type_traits::remove_const<input_value_type>::type,
							output_value_type
						>::value
					> type;
			};


			template <typename InputIterator, typename OutputIterator>
			struct is_memmove_optimizable:
					is_memmove_optimizable_helper<InputIterator, OutputIterator>::type
			{
			};

#	endif

		} // namespace detail

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_DETAIL_IS_MEMMOVE_OPTIMIZABLE_HPP
