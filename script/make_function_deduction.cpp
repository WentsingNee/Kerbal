/**
 * @file       make_function_deduction.hpp
 * @brief
 * @date       2019-6-25
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

void generate_is_function(std::ostream & cout)
{
	cout << R"(MODULE_EXPORT
template <typename >
struct is_function: kerbal::type_traits::false_type {};
)" << endl;

	cout << "#	if __cplusplus < 201103L\n" << endl;

	{
		std::string fmts = R"(template <typename Ret%s>
struct is_function<Ret(%s%s)%s%s>: kerbal::type_traits::true_type {};

)";

		for (int tnum = 0; tnum <= 25; ++tnum) {
			for (const auto & v : {""s, " volatile"s}) {
				for (const auto & c : {""s, " const"s}) {
					for (const auto & var_arg : {""s, "..."s}) {
						fmt::fprintf(cout, fmts,
									 [tnum](){
										 std::string args;
										 for (int i = 0; i < tnum; ++i) {
											 args += ", typename T";
											 args += std::to_string(i);
										 }
										 return args;
									 }(),
									 [tnum, var_arg](){
										 std::string args;
										 for (int i = 0; i < tnum; ++i) {
											 args += 'T';
											 args += std::to_string(i);
											 if (i != tnum - 1 || var_arg == "..."s) args += ", ";
										 }
										 return args;
									 }(),
									 var_arg, c, v);
					}
				}
			}
		}
	}

	cout << "#	else // __cplusplus < 201103L\n" << endl;

	{
		std::string fmts = R"(MODULE_EXPORT
template <typename Ret, typename ... Args>
struct is_function<Ret(Args...%s)%s%s%s>: kerbal::type_traits::true_type {};

)";

		for (const auto & ref : {""s, " &"s, " &&"s}) {
			for (const auto & v : {""s, " volatile"s}) {
				for (const auto& c : {""s, " const"s}) {
					for (const auto& var_arg : {""s, ", ..."s}) {
						fmt::fprintf(cout, fmts, var_arg, c, v, ref);
					}
				}
			}
		}

		cout << "#		if __cplusplus >= 201703L\n" << endl;

		{
			std::string fmts = R"(MODULE_EXPORT
template <typename Ret, typename ... Args>
struct is_function<Ret(Args...%s)%s%s%s noexcept>: kerbal::type_traits::true_type {};

)";

			for (const auto & ref : {""s, " &"s, " &&"s}) {
				for (const auto & v : {""s, " volatile"s}) {
					for (const auto& c : {""s, " const"s}) {
						for (const auto& var_arg : {""s, ", ..."s}) {
							fmt::fprintf(cout, fmts, var_arg, c, v, ref);
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
 * @file       function_deduction.hpp
 * @brief
 * @date       2019-6-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_FUNCTION_DEDUCTION_HPP
#define KERBAL_TYPE_TRAITS_FUNCTION_DEDUCTION_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/type_chooser.hpp>

#include <cstddef>

namespace kerbal
{
	namespace type_traits
	{
)"<< endl;

	{
		std::stringstream ss;
		generate_is_function(ss);
		std::string line;
		while (std::getline(ss, line)) {
			if (!line.empty() && line[0] != '#') {
				std::cout << "\t\t";
			}
			std::cout << line << std::endl;
		}
	}

	cout << R"(
	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_FUNCTION_DEDUCTION_HPP
)" << endl << endl;
}
