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

#ifndef KERBAL_COMPATIBILITY_STATIC_ASSERT_HPP_
#define KERBAL_COMPATIBILITY_STATIC_ASSERT_HPP_

#if __cplusplus >= 201103L
#	define KERBAL_STATIC_ASSERT(condition, msg)\
	static_assert(condition, msg)

#else

namespace kerbal
{
	namespace compatibility
	{
		template <bool condition>
		struct __static_assert_helper
		{
		};

		template <>
		struct __static_assert_helper<true>
		{
			typedef const char * type;
		};

	}

}

#define __KERBAL_JOIN_LINE(m, line) m ## line
#define __KERBAL_JOIN_LINE_HELPER(m, line) __KERBAL_JOIN_LINE(m, line)
#define KERBAL_JOIN_LINE(m) __KERBAL_JOIN_LINE_HELPER(m, __LINE__)


#define KERBAL_STATIC_ASSERT(condition, msg)\
typedef typename kerbal::compatibility::__static_assert_helper<static_cast<bool>(condition)>::type KERBAL_JOIN_LINE(__KERBAL_STATIC_ASSERT_TYPEDEF) __attribute__((unused))

#endif

#endif /* KERBAL_COMPATIBILITY_STATIC_ASSERT_HPP_ */
