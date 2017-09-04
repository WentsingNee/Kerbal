#include "exe_serve.hpp"

using namespace std;

unsigned long start_time = 0;
bool debug = true;

unsigned long show_time_cost()
{
	unsigned long time_cost = GetTickCount() - start_time;
	cout << "\n运行耗时 " << time_cost << " ms" << endl;
	return time_cost;
}

void program_will_end()
{
	show_time_cost();
}

string bit_of(const char * const a)
{
	string result = "";
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

string ocx_of(const char * const a)
{
	char buffer[10];
	string result = "";
	const char *p = a;
	while (*p) {
		get_16(buffer, *p);
		(result += buffer) += " ";
		++p;
	}
	return result;
}

#pragma comment(lib,"Advapi32.lib")
string get_user_name()
{
	char strBuffer[256] = { 0 };
	unsigned long dwSize = 256;
	GetUserName(strBuffer, &dwSize);

	return string(strBuffer);
}

