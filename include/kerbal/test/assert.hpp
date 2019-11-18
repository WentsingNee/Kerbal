/**
 * @file       assert.hpp
 * @brief      
 * @date       2019-7-7
 * @author     peter
 * @copyright
 *      peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TEST_ASSERT_HPP_
#define KERBAL_TEST_ASSERT_HPP_

#include <cstdio>
#include <cstdlib>

#define KERBAL_TEST_CHECK_EQUAL(lhs, rhs) \
do {\
	if ((lhs) != (rhs)) \
	{ \
		puts("CHECK EQUAL FAILED!"); \
		puts("details: "); \
		puts("    left statement: " #lhs); \
		puts("    right statement: " #rhs); \
		printf("    location: " __FILE__ ":%d\n", __LINE__); \
		return kerbal::test::unit_info::test_failed; \
	} \
} while (false);

#define KERBAL_TEST_CHECK(statement) \
do {\
	if (!static_cast<bool>((statement))) \
	{ \
		puts("CHECK FAILED!"); \
		puts("details: "); \
		puts("    statement: " #statement); \
		printf("    location: " __FILE__ ":%d\n", __LINE__); \
		return kerbal::test::unit_info::test_failed; \
	} \
} while (false);

#endif /* KERBAL_TEST_ASSERT_HPP_ */
