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

#ifndef KERBAL_TEST_TEST_CASE_TEST_CASE_IMPL_HPP
#define KERBAL_TEST_TEST_CASE_TEST_CASE_IMPL_HPP

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/config/exceptions.hpp>
#include <kerbal/container/vector.hpp>
#include <kerbal/costream/costream.hpp>
#include <kerbal/test/runtime_timer.hpp>

#include <cstddef>
#include <cstdio>

#include <kerbal/test/test_case/test_case.decl.hpp>


namespace kerbal
{

	namespace test
	{

		namespace detail
		{

			inline
			register_list_type & get_register_list() KERBAL_NOEXCEPT
			{
				static register_list_type register_list;
				return register_list;
			}

			inline
			int register_test_suit(
				const char * name,
				kerbal::test::test_case::call_ptr_t call_ptr,
				const char * description
			) KERBAL_NOEXCEPT
			{
				kerbal::test::detail::get_register_list().emplace_back(name, call_ptr, description);
				return 0;
			}

		} // namespace detail

		inline
		int run_test_case(std::size_t case_id, int, char * [])
		{
			register_list_type & register_list = kerbal::test::detail::get_register_list();
			typedef register_list_type::const_reference const_reference;

			const_reference item = register_list[case_id];
			const char * name = item.name;
			kerbal::test::test_case::call_ptr_t call_ptr = item.call_ptr;
			const char * description = item.description;
			printf("test case[%zu]: %s (%s) running\n", case_id, name, description);

			kerbal::test::assert_record record;

#	if KERBAL_HAS_RUNTIME_TIMER_SUPPORT
			kerbal::test::runtime_timer timer;
#	endif

#	if KERBAL_HAS_EXCEPTIONS_SUPPORT
			try {
#	endif
				call_ptr(record);
#	if KERBAL_HAS_EXCEPTIONS_SUPPORT
			} catch (...) {
				record.items.back().result = test_case_running_result::EXCEPTION;
				printf("test case[%zu]: %s (%s): EXCEPTION\n", case_id, name, description);
				throw;
			}
#	endif

#	if KERBAL_HAS_RUNTIME_TIMER_SUPPORT
			unsigned long time_usage = timer.count();
#	endif

			int success = 0;
			int failure = 0;

			for (kerbal::container::vector<assert_item>::size_type i = 0; i < record.items.size(); ++i) {
				switch (record.items[i].result) {
					case kerbal::test::test_case_running_result::SUCCESS: {
						++success;
						break;
					}
					case kerbal::test::test_case_running_result::FAILURE: {
						++failure;
						break;
					}
					case test_case_running_result::EXCEPTION:
						break;
				}
			}

			if (failure == 0) {
				kerbal::costream::costream out(std::cout, kerbal::costream::GREEN);
				out << "test case[" << case_id << "]: " << name << " (" << description << "): SUCCESS\n";
//				printf("test case[%zu]: %s (%s): SUCCESS\n", case_id, name, description);
			} else {
				printf("test case[%zu]: %s (%s): FAILURE\n", case_id, name, description);
			}

#	if KERBAL_HAS_RUNTIME_TIMER_SUPPORT
			{
				unsigned long milliseconds = time_usage;
				unsigned long seconds = milliseconds / 1000;
				milliseconds %= 1000;
				unsigned long minutes = seconds / 60;
				seconds %= 60;

				printf("time usage:");
				if (minutes != 0) {
					printf("%lu min", minutes);
				}
				if (minutes != 0 || seconds != 0) {
					printf(" %lu s", seconds);
				}
				printf(" %lu ms (%lu ms)\n", milliseconds, time_usage);
			}
#	else
			printf("time usage: --- (not supported)\n");
#	endif

			printf(
					" ------------------------\n"
					"|SUCCESS    | %10d |\n"
					"|FAILURE    | %10d |\n"
					"|------------------------|\n"
					"|TOTAL      | %10d |\n"
					" ------------------------\n",
			success, failure, success + failure);

			if (failure == 0) {
				return -1;
			} else {
				return 0;
			}
		}

		inline
		int select_test_case(int argc, char * argv[])
		{
			register_list_type & register_list = kerbal::test::detail::get_register_list();

			typedef register_list_type::size_type size_type;
			typedef register_list_type::const_reference const_reference;
			for (size_type i = 0; i < register_list.size(); ++i) {
				const_reference item = register_list[i];
				const char * case_name = item.name;
				const char * case_description = item.description;

				printf("test case[%zu]: %s (%s)\n", i, case_name, case_description);
			}
			printf("Please select the test case num: \n");
			int i = 0;
			scanf("%u", &i);
			return run_test_case(i, argc, argv);
		}

		inline
		int run_all_test_case(int argc, char * argv[])
		{
			register_list_type & register_list = kerbal::test::detail::get_register_list();
			int ret = 0;
			typedef register_list_type::size_type size_type;
			for (size_type i = 0; i < register_list.size(); ++i) {
				if (run_test_case(i, argc, argv) != 0) {
					ret = 1;
				}
				printf("\n\n");
			}
			return ret;
		}

	} // namespace test

} // namespace kerbal

#endif // KERBAL_TEST_TEST_CASE_TEST_CASE_IMPL_HPP
