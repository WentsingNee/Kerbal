/**
 * @file       static_assert.hpp
 * @brief
 * @date       2019-11-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COMPATIBILITY_STATIC_ASSERT_HPP
#define KERBAL_COMPATIBILITY_STATIC_ASSERT_HPP

#if __cplusplus >= 201103L

#	define KERBAL_STATIC_ASSERT(condition, msg) \
	static_assert(condition, msg)

#else

#	include <kerbal/compatibility/attribute_unused.hpp>
#	include <kerbal/macro/join_line.hpp>
#	include <kerbal/type_traits/integral_constant.hpp>


namespace kerbal
{

	namespace compatibility
	{

		namespace detail
		{

			template <bool>
			struct static_assert_helper
			{
			};

			template <>
			struct static_assert_helper<true>: kerbal::type_traits::true_type
			{
			};

			template <bool>
			struct static_assert_test
			{
			};

		} // namespace detail

	}

}


#define KERBAL_STATIC_ASSERT(condition, msg) \
	typedef kerbal::compatibility::detail::static_assert_test< \
		kerbal::compatibility::detail::static_assert_helper<static_cast<bool>(condition)>::value \
	> KERBAL_JOIN_LINE(__KERBAL_STATIC_ASSERT_TYPEDEF) KERBAL_ATTRIBUTE_UNUSED

#endif

#endif // KERBAL_COMPATIBILITY_STATIC_ASSERT_HPP
