/*
 * make_is_function.cpp
 *
 *  Created on: 2019-6-25
 *      Author: peter
 */
 
#include <iostream>
#include <string>

using namespace std;

void body(int tnum, const string& cv, const string& ref, int ntab = 0)
{
	cout << string(ntab, '\t') << "template <typename Ret";
	for (int i = 0; i < tnum; ++i) {
		cout << ", typename T" << i;
	}
	cout << ">" << endl;
	cout << string(ntab, '\t') << "struct is_function<Ret(";
	if (tnum == 0) {
		cout << "void";
	}
	for (int i = 0; i < tnum; ++i) {
		cout << "T" << i << ((i == tnum - 1) ? "" : ", ");
	}
	cout << ") ";
	cout << cv << ref << "> : kerbal::type_traits::true_type {};" << endl;
	cout << endl;
}

void varargbody(int tnum, const string& cv, const string& ref, int ntab = 0)
{
	cout << string(ntab, '\t') << "template <typename Ret";
	for (int i = 0; i < tnum; ++i) {
		cout << ", typename T" << i;
	}
	cout << ">" << endl;
	cout << string(ntab, '\t') << "struct is_function<Ret(";
	for (int i = 0; i < tnum; ++i) {
		cout << "T" << i << ((i == tnum - 1) ? "" : ", ");
	}
	if (tnum != 0) {
		cout << ", ";
	}
	cout << "...) ";
	cout << cv << ref << "> : kerbal::type_traits::true_type {};" << endl;
	cout << endl;
}

void varargbody11(const string& cv, const string& ref, int ntab = 0)
{
	cout << string(ntab, '\t') << "MODULE_EXPORT" << endl;
	cout << string(ntab, '\t') << "template <typename Ret, typename ... Args>" << endl;
	cout << string(ntab, '\t') << "struct is_function<Ret(Args...) ";
	cout << cv << ref << "> : kerbal::type_traits::true_type {};" << endl;
	cout << endl;
	
	cout << string(ntab, '\t') << "MODULE_EXPORT" << endl;
	cout << string(ntab, '\t') << "template <typename Ret, typename ... Args>" << endl;
	cout << string(ntab, '\t') << "struct is_function<Ret(Args......) ";
	cout << cv << ref << "> : kerbal::type_traits::true_type {};" << endl;
	cout << endl;
}

int main()
{
	cout << R"(/*
 * is_function.hpp
 *
 *  Created on: 2019-6-25
 *      Author: peter
 */)" << endl << endl;
 
	cout << "#ifndef INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_IS_FUNCTION_HPP_" << endl;
	cout << "#define INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_IS_FUNCTION_HPP_" << endl;
	cout << endl;
	
	cout << "#include <kerbal/ts/modules_ts/modules_ts.hpp>" << endl;
	cout << "#include <kerbal/type_traits/type_traits_details/integral_constant.hpp>" << endl;
	cout << endl;

	cout << "namespace kerbal" << endl;
	cout << "{" << endl;
	cout << "	namespace type_traits" << endl;
	cout << "	{" << endl;
	cout << "		MODULE_EXPORT" << endl;
	cout << "		template <typename >" << endl;
	cout << "		struct is_function : kerbal::type_traits::false_type {};" << endl;
	cout << endl;
	
	{
		auto cv = "";
		auto ref = "";
		cout << "#	if __cplusplus < 201103L" << endl << endl;
	
		for (int tnum = 0; tnum <= 50; ++tnum) {
			body(tnum, cv, ref, 2);
			varargbody(tnum, cv, ref, 2);
		}
		
		cout << "#	else // c++11" << endl;
		cout << endl;
	
		varargbody11(cv, ref, 2);
		
		cout << "#	endif // c++11" << endl;
		cout << endl;
	}
	
	cout << "#	if __cplusplus >= 201103L" << endl << endl;

	for (auto ref : {""s, "& "s, "&& "s} ) {
		for (auto cv : {"", "const ", "volatile ", "const volatile "}) {
			if (ref == "" && cv == "") {
				
			} else {
				varargbody11(cv, ref, 2);
			}
		}
	}
	cout << "#	endif // c++11" << endl;
	cout << endl;

	cout << "	} // namespace type_traits" << endl;
	cout << endl;
	cout << "} // namespace kerbal" << endl;
	cout << endl;

	cout << "#endif // INCLUDE_KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_IS_FUNCTION_HPP_" << endl;

}
