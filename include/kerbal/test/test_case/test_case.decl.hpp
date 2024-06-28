/**
 * @file       test_case.decl.hpp
 * @brief      
 * @date       2019-7-7
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TEST_TEST_CASE_TEST_CASE_DECL_HPP
#define KERBAL_TEST_TEST_CASE_TEST_CASE_DECL_HPP

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/compatibility/attribute_unused.hpp>
#include <kerbal/container/vector.hpp>
#include <kerbal/macro/join_line.hpp>

#include <cstdio>
#include <cstdlib>
#include <iostream>


namespace kerbal
{

	namespace test
	{

		struct test_case_running_result
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
				const char * file;
				int line;
				const char * item;
				test_case_running_result::circumstance result;

				assert_item(
					const char * file,
					int line,
					const char * item
				) KERBAL_NOEXCEPT :
					file(file),
					line(line),
					item(item),
					result(test_case_running_result::SUCCESS)
				{
				}
		};

		struct assert_record
		{
				kerbal::container::vector<assert_item> items;
		};

		struct test_case
		{

				typedef void (*call_ptr_t) (kerbal::test::assert_record &);

				const char * name;
				call_ptr_t call_ptr;
				const char * description;

				test_case(
					const char * name,
					call_ptr_t call_ptr,
					const char * description
				) KERBAL_NOEXCEPT :
					name(name),
					call_ptr(call_ptr),
					description(description)
				{
				}

		};

		typedef kerbal::container::vector<test_case> register_list_type;

		namespace detail
		{

			int register_test_suit(
				const char * name,
				kerbal::test::test_case::call_ptr_t call_ptr,
				const char * description
			) KERBAL_NOEXCEPT;

		} // namespace detail

		int run_test_case(std::size_t case_id, int, char * []);

		int select_test_case(int argc, char * argv[]);

		int run_all_test_case(int argc, char * argv[]);

		template <typename T, typename U>
		bool compare_and_out(const T & lhs, const U & rhs)
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
	void name(kerbal::test::assert_record &); \
	static const int KERBAL_JOIN_LINE(kerbal_test_register_unit_tag) KERBAL_ATTRIBUTE_UNUSED = \
		(kerbal::test::detail::register_test_suit(#name, name, description), 0); \
	void name(kerbal::test::assert_record & record)


#define KERBAL_TEMPLATE_TEST_CASE(name, description) \
	void name(kerbal::test::assert_record & record)

#define KERBAL_TEMPLATE_TEST_CASE_INST(name, description, ...) \
	static const int KERBAL_JOIN_LINE(kerbal_test_register_unit_tag) KERBAL_ATTRIBUTE_UNUSED = \
		(kerbal::test::detail::register_test_suit(#name "<" #__VA_ARGS__ ">", name<__VA_ARGS__>, description), 0);


#define KERBAL_TEST_CHECK_EQUAL(lhs, rhs) do { \
	record.items.emplace_back(+__FILE__, __LINE__, +(#lhs " == " #rhs)); \
	if (kerbal::test::compare_and_out((lhs), (rhs))) { \
		puts( \
			"CHECK EQUAL FAILED!\n" \
			"details: \n" \
			"    left statement: " #lhs "\n" \
			"    right statement: " #rhs "\n" \
		); \
		printf("    location: " __FILE__ ":%d\n", __LINE__); \
		record.items.back().result = kerbal::test::test_case_running_result::FAILURE; \
	} \
} while (false)

#define KERBAL_TEST_CHECK(statement) do { \
	record.items.emplace_back(+__FILE__, __LINE__, +(#statement " == true")); \
	if (!static_cast<bool>((statement))) { \
		puts( \
			"CHECK FAILED!\n" \
			"details: \n" \
			"    statement: " #statement "\n" \
		); \
		printf("    location: " __FILE__ ":%d\n", __LINE__); \
		record.items.back().result = kerbal::test::test_case_running_result::FAILURE; \
	} \
} while (false)


#define KERBAL_TEST_CHECK_EQUAL_STATIC(lhs, rhs) do { \
	KERBAL_STATIC_ASSERT((lhs) == (rhs), "Check failed!"); \
	KERBAL_TEST_CHECK_EQUAL(lhs, rhs); \
} while(false)

#define KERBAL_TEST_CHECK_STATIC(statement) do { \
	KERBAL_STATIC_ASSERT(static_cast<bool>(statement), "Check failed!"); \
	KERBAL_TEST_CHECK(statement); \
} while(false)


#endif // KERBAL_TEST_TEST_CASE_TEST_CASE_DECL_HPP
