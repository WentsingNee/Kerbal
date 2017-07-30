#include "exe_serve.hpp"

using namespace std;

unsigned long start_time = 0;
bool debug = false;

void program_start(bool is_debug)
{
	start_time = GetTickCount();
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout << PRODUCT_NAME << " [版本 " << VER_STRING << "]\n" << "(c) " << COMPANY_NAME << "。保留所有权利。" << endl;
	/*
	 Microsoft Windows [版本 10.0.14393]
	 (c) 2016 Microsoft Corporation。保留所有权利。
	 */

	cout << "本产品授权给" << get_user_name() << "使用\n" << endl;
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
	cout << "\n运行耗时 " << time_cost << " ms" << endl;
	return time_cost;
}

bool program_will_end()
{
	show_time_cost();
	char if_redo;

	const bool wait = false;
	if (wait) {
		printf("Press any key to continue...");
		scanf("%c", &if_redo);
		printf("%c\n", if_redo);
		if (if_redo == 'y' || if_redo == 'Y') {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

//template <class T>
//string get_typename(T &a)
//{
//	typeid(a).name()<<endl;
//}

void print_string_bit(char * const a)
{
	char *p = a;
	while (*p) {
		for (int j = 7; j >= 0; j--) {
			cout << ((*p >> j) & 1);
		}
		cout << " ";
		p++;
	}
	cout << endl;
}

void print_string_16(char * const a)
{
	unsigned char tmp;
	char *p = a;
	while (*p) {
		tmp = *p;
		tmp >>= 4;
		if (tmp > 9) {
			//cout << char('A' + tmp - 10);
			cout << char(tmp + 55);
		} else {
			cout << char(tmp + '0');
		}

		tmp = *p;
		tmp <<= 4;
		tmp >>= 4;
		if (tmp > 9) {
			cout << char(tmp + 55);
		} else {
			cout << char(tmp + '0');
		}
		cout << " ";
		p++;
	}
	cout << endl;
}

void print_string_bit(string a)
{
	print_string_bit(&a[0]);
}
void print_string_16(string a)
{
	print_string_16(&a[0]);
}

#pragma comment(lib,"Advapi32.lib")
string get_user_name()
{
	char strBuffer[256] = { 0 };
	unsigned long dwSize = 256;
	GetUserName(strBuffer, &dwSize);

	return string(strBuffer);
}

class dbstream
{
	private:
		bool swit;

	public:
		dbstream()
		{
			swit = true;
		}

		void why_cannot_use()
		{
			if (debug == true) {
			} else {
				cout << "只有在调用program_start函数时,is_debug值传入的是true,调试输出流才会输出信息" << endl;
			}
		}
		template <class T> friend dbstream& operator <<(dbstream&, T&);

};

#define enddb "enddb"
#include <iomanip>
//#include "basic_math.h"
template <class T>
dbstream& operator <<(dbstream& output, T&z)
{
	if (debug == true) {
		if (output.swit == true) {
			cout << "- ";
			output.swit = false;
		}

		/*if(strcmp((char*)(&z),"\n")==0) {
		 cout<< "\n  ";
		 } else*/if (strcmp((char*) (&z), enddb) == 0) {
			output.swit = true;
			cout << endl;
		} else {
			if (typeid(T).name() == typeid(double).name() || typeid(T).name() == typeid(float).name()) {
				cout << z;
			} else {
				cout << z;
			}

		}
	}

	return output;
}
dbstream cdb;
