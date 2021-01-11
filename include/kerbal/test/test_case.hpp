/**
 * @file       test_case.hpp
 * @brief      
 * @date       2019-7-7
 * @author     peter
 * @copyright
 *      peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TEST_TEST_CASE_HPP
#define KERBAL_TEST_TEST_CASE_HPP

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/macro/join_line.hpp>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

namespace kerbal
{

	namespace test
	{

		struct running_result
		{
				enum circumstance
				{
					SUCCESS,
					FAILURE,
					EXCEPTION,
				};
		};

		struct assert_item
		{
				const char* file;
				int line;
				const char* item;
				running_result::circumstance result;

				assert_item(const char * file,
						int line,
						const char * item) KERBAL_NOEXCEPT
					:
						file(file),
						line(line),
						item(item),
						result(running_result::SUCCESS)
				{
				}
		};

		struct assert_record
		{
				std::vector<assert_item> items;
		};

		struct test_case
		{

				typedef void (*call_ptr_t) (kerbal::test::assert_record&);

				const char * name;
				call_ptr_t call_ptr;
				const char * description;

				test_case(const char * name,
						call_ptr_t call_ptr,
						const char * description) KERBAL_NOEXCEPT
					:
						name(name),
						call_ptr(call_ptr),
						description(description)
				{
				}

		};

		typedef std::vector<test_case> register_list_type;

		int __register_test_suit(
				const char * name,
				kerbal::test::test_case::call_ptr_t call_ptr,
				const char * description) KERBAL_NOEXCEPT;

		void select_test_case(int argc, char* argv[]);

		void run_all_test_case(int argc, char* argv[]);

		template <typename T, typename U>
		bool compare_and_out(const T& lhs, const U& rhs)
		{
			if (lhs != rhs) {
				puts("CHECK EQUAL FAILED!");
				printf(" left is: "); std::cout << lhs << std::endl;
				printf("right is: "); std::cout << rhs << std::endl;
				return true;
			}
			return false;
		}

	} // namespace test

} // namespace kerbal


#define KERBAL_TEST_CASE(name, description) \
	void name(kerbal::test::assert_record&); \
	static const int KERBAL_JOIN_LINE(__kerbal_test_register_unit_tag) = (__register_test_suit(#name, name, description), 0); \
	void name(kerbal::test::assert_record& record)




#if __cplusplus >= 201103L

#define KERBAL_TEST_CHECK_EQUAL(lhs, rhs) \
do {\
	record.items.emplace_back(__FILE__, __LINE__, #lhs " == " #rhs); \
	if (kerbal::test::compare_and_out((lhs), (rhs))) { \
		puts("CHECK EQUAL FAILED!"); \
		puts("details: "); \
		puts("    left statement: " #lhs); \
		puts("    right statement: " #rhs); \
		printf("    location: " __FILE__ ":%d\n", __LINE__); \
		record.items.back().result = kerbal::test::running_result::FAILURE; \
	} \
} while (false);

#define KERBAL_TEST_CHECK(statement) \
do {\
	record.items.emplace_back(__FILE__, __LINE__, #statement " == true"); \
	if (!static_cast<bool>((statement))) { \
		puts("CHECK FAILED!"); \
		puts("details: "); \
		puts("    statement: " #statement); \
		printf("    location: " __FILE__ ":%d\n", __LINE__); \
		record.items.back().result = kerbal::test::running_result::FAILURE; \
	} \
} while (false);

#else

#define KERBAL_TEST_CHECK_EQUAL(lhs, rhs) \
do {\
	record.items.push_back(kerbal::test::assert_item(__FILE__, __LINE__, #lhs " == " #rhs)); \
	if (kerbal::test::compare_and_out((lhs), (rhs))) { \
		puts("CHECK EQUAL FAILED!"); \
		puts("details: "); \
		puts("    left statement: " #lhs); \
		puts("    right statement: " #rhs); \
		printf("    location: " __FILE__ ":%d\n", __LINE__); \
		record.items.back().result = kerbal::test::running_result::FAILURE; \
	} \
} while (false);

#define KERBAL_TEST_CHECK(statement) \
do {\
	record.items.push_back(kerbal::test::assert_item(__FILE__, __LINE__, #statement " == true")); \
	if (!static_cast<bool>((statement))) { \
		puts("CHECK FAILED!"); \
		puts("details: "); \
		puts("    statement: " #statement); \
		printf("    location: " __FILE__ ":%d\n", __LINE__); \
		record.items.back().result = kerbal::test::running_result::FAILURE; \
	} \
} while (false);

#endif


#define KERBAL_TEST_CHECK_EQUAL_STATIC(lhs, rhs) do {\
	KERBAL_STATIC_ASSERT((lhs) == (rhs), "Check failed!"); \
	KERBAL_TEST_CHECK_EQUAL(lhs, rhs); \
} while(false);

#define KERBAL_TEST_CHECK_STATIC(statement) do {\
	KERBAL_STATIC_ASSERT(static_cast<bool>(statement), "Check failed!"); \
	KERBAL_TEST_CHECK(statement); \
} while(false);


#include <kerbal/test/impl/test_case.impl.hpp>


#endif // KERBAL_TEST_TEST_CASE_HPP
