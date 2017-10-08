#include "exe_serve.hpp"

unsigned long start_time = 0;
bool debug = true;

unsigned long show_time_cost()
{
	unsigned long time_cost = GetTickCount() - start_time;
	std::cout << "\nÔËÐÐºÄÊ± " << time_cost << " ms" << std::endl;
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

