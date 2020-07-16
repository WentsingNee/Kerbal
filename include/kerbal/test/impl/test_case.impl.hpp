/**
 * @file       test_case.impl.hpp
 * @brief
 * @date       2019-11-26
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TEST_IMPL_TEST_CASE_IMPL_HPP
#define KERBAL_TEST_IMPL_TEST_CASE_IMPL_HPP

#include <cstdio>
#include <vector>
#include <kerbal/compatibility/noexcept.hpp>

namespace kerbal
{

	namespace test
	{

		inline
		register_list_type& __get_register_list() KERBAL_NOEXCEPT
		{
			static register_list_type register_list;
			return register_list;
		}

		inline
		int __register_test_suit(
				const char * name,
				kerbal::test::test_case::call_ptr_t call_ptr,
				const char * description)
				KERBAL_NOEXCEPT
		{
#	if __cplusplus < 201103L
			__get_register_list().push_back(kerbal::test::test_case(name, call_ptr, description));
#	else
			__get_register_list().emplace_back(name, call_ptr, description);
#	endif
			return 0;
		}

		inline
		void run_test_case(size_t case_id, int argc, char* argv[])
		{
			register_list_type & register_list = __get_register_list();
			typedef register_list_type::size_type size_type;
			typedef register_list_type::const_reference const_reference;

			const_reference item = register_list[case_id];
			const char * name = item.name;
			kerbal::test::test_case::call_ptr_t call_ptr = item.call_ptr;
			const char * description = item.description;
			printf("test case[%zu]: %s (%s) running\n", case_id, name, description);

			kerbal::test::assert_record record;

			try {
				call_ptr(argc, argv, record);
			} catch (...) {
				record.items.back().result = running_result::EXCEPTION;
				printf("test case[%zu]: %s (%s): EXCEPTION\n", case_id, name, description);
				throw;
			}

			int success = 0;
			int failure = 0;

			for (int i = 0; i < record.items.size(); ++i) {
				switch (record.items[i].result) {
					case kerbal::test::running_result::SUCCESS: {
						++success;
						break;
					}
					case kerbal::test::running_result::FAILURE: {
						++failure;
						break;
					}
					case running_result::EXCEPTION:
						break;
				}
			}

			if (failure == 0) {
				printf("test case[%zu]: %s (%s): SUCCESS\n", case_id, name, description);
			} else {
				printf("test case[%zu]: %s (%s): FAILURE\n", case_id, name, description);
			}

			printf(" ------------------------\n");
			printf("|SUCCESS    | %10d |\n", success);
			printf("|FAILURE    | %10d |\n", failure);
			printf("|------------------------|\n");
			printf("|TOTAL      | %10d |\n", success + failure);
			printf(" ------------------------\n");
		}

		inline
		void select_test_case(int argc, char* argv[])
		{
			register_list_type & register_list = __get_register_list();

			typedef typename register_list_type::size_type size_type;
			typedef typename register_list_type::const_reference const_reference;
			for (size_type i = 0; i < register_list.size(); ++i) {
				const_reference item = register_list[i];
				const char * case_name = item.name;
				const char * case_description = item.description;

				printf("test case[%zu]: %s (%s)\n", i, case_name, case_description);
			}
			printf("Please select the test case num: \n");
			int i = 0;
			scanf("%u", &i);
			run_test_case(i, argc, argv);
		}

		inline
		void run_all_test_case(int argc, char* argv[])
		{
			register_list_type & register_list = __get_register_list();
			typedef typename register_list_type::size_type size_type;

			for (size_type i = 0; i < register_list.size(); ++i) {
				run_test_case(i, argc, argv);
				printf("\n\n");
			}
		}

	} // namespace test

} // namespace kerbal

#endif // KERBAL_TEST_IMPL_TEST_CASE_IMPL_HPP
