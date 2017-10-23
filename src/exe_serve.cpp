#include "exe_serve.hpp"

unsigned long start_time = 0;
bool debug = true;

void program_start(bool is_debug)
{
#ifndef __DATE__
#	define __DATE__ "UNKNOWN DATE"
#	pragma message("\n"\
"			Failed to get compile date"\
	)
#endif

#ifndef __TIME__
#	define __TIME__ "UNKNOWN TIME"
#	pragma message("\n"\
"			Failed to get compile time"\
	)
#endif

	start_time = GetTickCount();
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout << PRODUCT_NAME << " [版本 " << VER_STRING << " . " << __DATE__ << " . " << __TIME__;
#ifdef __GNUC__
	std::cout << " , 编译 Gcc 版本号 " << __GNUC__ << " ]";
#endif
	std::cout << std::endl;
	std::cout << "(c) " << COMPANY_NAME << "。保留所有权利。" << std::endl;
	/*
	 Microsoft Windows [版本 10.0.14393]
	 (c) 2016 Microsoft Corporation。保留所有权利。
	 */

	std::cout << "本产品授权给" << get_user_name() << "使用\n" << std::endl;
	/*
	 本产品授权给Peter使用
	 */

	/*	cout << __LINE__ << endl;
	 cout << __FILE__ << endl;
	 cout << __DATE__ << endl;
	 cout << __TIME__ << endl;
	 cout << __STDC__ << endl;*/

	debug = is_debug;
}

unsigned long show_time_cost()
{
	unsigned long time_cost = GetTickCount() - start_time;
	std::cout << "\n运行耗时 " << time_cost << " ms" << std::endl;
	return time_cost;
}

void program_will_end()
{
	show_time_cost();
}

std::string bit_of(const char * const a)
{
	std::string result = "";
	for (const char *p = a; *p; ++p) {
		for (int j = 7; j >= 0; --j) {
			if ((*p >> j) & 1) {
				result += '1';
			} else {
				result += '0';
			}
		}
		result += " ";
	}
	return result;
}

std::string ocx_of(const char * const a)
{
	char buffer[10];
	std::string result = "";
	const char *p = a;
	while (*p) {
		get_16(buffer, *p);
		(result += buffer) += " ";
		++p;
	}
	return result;
}

