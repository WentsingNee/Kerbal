/**
 * @file       make_function_traits.hpp
 * @brief
 * @date       2020-4-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */
 
#include <iostream>
#include <sstream>
#include <string>
#include <fmt/format.h>
#include <fmt/printf.h>

using namespace std;

void generate_function_traits(std::ostream & cout)
{
	cout << R"(MODULE_EXPORT
template <typename >
struct function_traits;
)" << endl;

	cout << "#	if __cplusplus < 201103L\n" << endl;

	{
		std::string fmts = R"(template <typename Ret%s>
struct function_traits<Ret(%s%s)%s%s>
{
		typedef kerbal::type_traits::%s_type			has_var_list;
		typedef kerbal::type_traits::%s_type			is_const;
		typedef kerbal::type_traits::%s_type			is_volatile;

		typedef Ret										return_type;
		typedef kerbal::type_traits::integral_constant<int, %d>		args_num;
};

)";

		for (int tnum = 0; tnum <= 25; ++tnum) {
			for (const auto& v : {""s, " volatile"s}) {
				for (const auto & c : {""s, " const"s}) {
					for (const auto& var_arg : {""s, "..."s}) {
						fmt::fprintf(cout, fmts,
									[tnum]() {
										std::string args;
										for (int i = 0; i < tnum; ++i) {
											args += ", typename T";
											args += std::to_string(i);
										}
										return args;
									}(),
									[tnum, var_arg]() {
										std::string args;
										for (int i = 0; i < tnum; ++i) {
											args += 'T';
											args += std::to_string(i);
											if (i != tnum - 1 || var_arg == "..."s)
												args += ", ";
										}
										return args;
									}(),
									var_arg, c, v,
									var_arg == ""s ? "false" : "true",
									c == ""s ? "false" : "true",
									v == ""s ? "false" : "true",
									tnum
						);
					}
				}
			}
		}
	}

	cout << "#	else // __cplusplus >= 201103L\n" << endl;

	{
		std::string fmts = R"(MODULE_EXPORT
template <typename Ret, typename ... Args>
struct function_traits<Ret(Args...%s)%s%s%s>
{
		typedef kerbal::type_traits::%s_type			has_var_list;
		typedef kerbal::type_traits::%s_type			is_const;
		typedef kerbal::type_traits::%s_type			is_volatile;
		typedef kerbal::type_traits::%s_type			is_lref;
		typedef kerbal::type_traits::%s_type			is_rref;
#	if __cplusplus >= 201703L
		typedef kerbal::type_traits::false_type			is_noexcept;
#	endif // __cplusplus >= 201703L

		typedef Ret										return_type;
		typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
		template <size_t i>
		struct argument: kerbal::type_traits::type_chooser<i, Args...>
		{
		};
};

)";

		for (const auto & ref : {""s, " &"s, " &&"s}) {
			for (const auto & v : {""s, " volatile"s}) {
				for (const auto & c : {""s, " const"s}) {
					for (const auto & var_arg : {""s, ", ..."s}) {
						fmt::fprintf(cout, fmts, var_arg, c, v, ref,
									var_arg == ""s ? "false" : "true",
									c == ""s ? "false" : "true",
									v == ""s ? "false" : "true",
									ref == " &"s ? "true" : "false",
									ref == " &&"s ? "true" : "false"
						);
					}
				}
			}
		}

		cout << "#		if __cplusplus >= 201703L\n" << endl;

		{
			std::string fmts = R"(MODULE_EXPORT
template <typename Ret, typename ... Args>
struct function_traits<Ret(Args...%s)%s%s%s noexcept>
{
		typedef kerbal::type_traits::%s_type			has_var_list;
		typedef kerbal::type_traits::%s_type			is_const;
		typedef kerbal::type_traits::%s_type			is_volatile;
		typedef kerbal::type_traits::%s_type			is_lref;
		typedef kerbal::type_traits::%s_type			is_rref;
		typedef kerbal::type_traits::true_type			is_noexcept;

		typedef Ret										return_type;
		typedef kerbal::type_traits::integral_constant<int, sizeof...(Args)>	args_num;
		template <size_t i>
		struct argument: kerbal::type_traits::type_chooser<i, Args...>
		{
		};
};

)";

			for (const auto & ref : {""s, " &"s, " &&"s}) {
				for (const auto & v : {""s, " volatile"s}) {
					for (const auto & c : {""s, " const"s}) {
						for (const auto & var_arg : {""s, ", ..."s}) {
							fmt::fprintf(cout, fmts, var_arg, c, v, ref,
										 var_arg == ""s ? "false" : "true",
										 c == ""s ? "false" : "true",
										 v == ""s ? "false" : "true",
										 ref == " &"s ? "true" : "false",
										 ref == " &&"s ? "true" : "false"
							);
						}
					}
				}
			}

		}

		cout << "#		endif // __cplusplus >= 201703L\n" << endl;

	}

	cout << "#	endif // __cplusplus < 201103L\n" << endl;

}

int main()
{
	cout << R"(/**
 * @file       function_traits.hpp
 * @brief
 * @date       2020-4-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_FUNCTION_FUNCTION_TRAITS_HPP
#define KERBAL_FUNCTION_FUNCTION_TRAITS_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/type_chooser.hpp>

#include <cstddef>

namespace kerbal
{
	namespace function
	{
)"<< endl;

{
	std::stringstream ss;
	generate_function_traits(ss);
	std::string line;
	while (std::getline(ss, line)) {
		if (!line.empty() && line[0] != '#') {
			std::cout << "\t\t";
		}
		std::cout << line << std::endl;
	}
}

cout << R"(
	} // namespace function

} // namespace kerbal

#endif // KERBAL_FUNCTION_FUNCTION_TRAITS_HPP
)" << endl << endl;
}
