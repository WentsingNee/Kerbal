/**
 * @file       can_be_nothrow_advance_iterator.hpp
 * @brief
 * @date       2022-01-20
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_DETAIL_CAN_BE_NOTHROW_ADVANCE_ITERATOR_HPP
#define KERBAL_MEMORY_DETAIL_CAN_BE_NOTHROW_ADVANCE_ITERATOR_HPP

#if __cpp_exceptions
#	if __cplusplus < 201103L
#		include <kerbal/type_traits/is_pointer.hpp>
#	else
#		include <kerbal/type_traits/integral_constant.hpp>
#		include <kerbal/utility/declval.hpp>
#	endif
#else
#	include <kerbal/type_traits/integral_constant.hpp>
#endif


namespace kerbal
{

	namespace memory
	{

		namespace detail
		{

#	if __cpp_exceptions

#		if __cplusplus < 201103L

			template <typename Iterator>
			struct can_be_nothrow_advance_iterator :
					kerbal::type_traits::is_pointer<Iterator>
			{
			};

#		else

			template <typename Iterator>
			struct can_be_nothrow_advance_iterator :
					kerbal::type_traits::bool_constant<noexcept(++(kerbal::utility::declval<Iterator&>()))>
			{
			};

#		endif

#	else

			template <typename Iterator>
			struct can_be_nothrow_advance_iterator :
					kerbal::type_traits::true_type
			{
			};

#	endif

		} // namespace detail

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_DETAIL_CAN_BE_NOTHROW_ADVANCE_ITERATOR_HPP
