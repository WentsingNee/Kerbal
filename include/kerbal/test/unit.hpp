/**
 * @file       unit.hpp
 * @brief      
 * @date       2019-7-7
 * @author     peter
 * @copyright
 *      peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TEST_UNIT_HPP_
#define KERBAL_TEST_UNIT_HPP_

#include <cstdio>
#include <vector>
#include <kerbal/test/test_case_vector.hpp>
#include <kerbal/compatibility/noexcept.hpp>

namespace kerbal
{
	namespace test
	{
		typedef std::vector<unit_info> register_list_type;

		inline
		register_list_type& __get_register_list() KERBAL_NOEXCEPT
		{
			static register_list_type register_list;
			return register_list;
		}

		inline
		int __register_test_suit(const char * case_name, unit_info::test_unit_type case_call_ptr, const char * case_description) KERBAL_NOEXCEPT
		{
#	if __cplusplus < 201103L
			__get_register_list().push_back(kerbal::test::unit_info(case_name, case_call_ptr, case_description));
#	else
			__get_register_list().emplace_back(case_name, case_call_ptr, case_description);
#	endif
			return 0;
		}

		inline
		void select_test_case(int argc, char* argv[])
		{
			register_list_type & register_list = __get_register_list();

			typedef typename register_list_type::size_type size_type;
			typedef typename register_list_type::const_reference const_reference;
			for (size_type i = 0; i < register_list.size(); ++i) {
				const_reference item = register_list[i];
				const char * case_name = item.case_name;
				const char * case_description = item.case_description;

				printf("%d    %s    %s\n", i, case_name, case_description);
			}
			puts("Please select the test case num: ");
			size_type i;
			scanf("%lld", i);
			kerbal::test::unit_info::running_result res = register_list[i].case_call_ptr(argc, argv);
		}

		inline
		void run_all_test_case(int argc, char* argv[])
		{
			register_list_type & register_list = __get_register_list();
			typedef typename register_list_type::size_type size_type;
			typedef typename register_list_type::const_reference const_reference;
			for (size_type i = 0; i < register_list.size(); ++i) {
				const_reference item = register_list[i];
				const char * case_name = item.case_name;
				unit_info::test_unit_type case_call_ptr = item.case_call_ptr;
				const char * case_description = item.case_description;
				kerbal::test::unit_info::running_result res = case_call_ptr(argc, argv);
				switch (res) {
					case kerbal::test::unit_info::test_passed: {
						printf("test case: %s (%s) pass\n", case_name, case_description);
						break;
					}
					case kerbal::test::unit_info::test_failed: {
						printf("test case: %s (%s) failed\n", case_name, case_description);
						break;
					}
				}
			}
		}

	} // namespace test

} // namespace kerbal

#define __KERBAL_TEST_REGISTER_UNIT_TAG_HLEPER(LINE) __kerbal_test_register_unit_tag ## LINE
#define __KERBAL_TEST_REGISTER_UNIT_TAG(LINE) __KERBAL_TEST_REGISTER_UNIT_TAG_HLEPER(LINE)

#define KERBAL_TEST_CASE(case_name, case_description) \
	kerbal::test::unit_info::running_result case_name(int args, char* argv[]); \
	static const int __KERBAL_TEST_REGISTER_UNIT_TAG(__LINE__) = (__register_test_suit(#case_name, case_name, case_description), 0); \
	kerbal::test::unit_info::running_result case_name(int args, char* argv[]) \
	{


#define KERBAL_TEST_CASE_END \
		return kerbal::test::unit_info::test_passed; \
	}


#endif /* KERBAL_TEST_UNIT_HPP_ */
