#ifndef _ARRAY_SERVE_H_
#define _ARRAY_SERVE_H_

//#pragma message(__DATE__ "  " __TIME__"  ÕýÔÚ±àÒë"__FILE__)

#include <iostream>
#include <string>
#include <typeinfo>
#include <fstream>

#include "exe_serve.hpp"

using namespace std;

template <class T> int arraylen(const T &array);
template <class T> void print_array(T a[], int len, string separator = " , ", bool if_output_number = false) throw (invalid_argument);
template <class T> void print_array_to_file(T a[], int len, string separator, string file_name, bool if_output_number =
		false) throw (invalid_argument);
template <typename T> int array_dimension(const T &a);

template <class T>
int arraylen(const T &array)
{
	return (sizeof(array) / sizeof(array[0]));
}

template <class T>
void print_array(T a[], int len, string separator, bool if_output_number) throw (invalid_argument)
{
	if (len > 0) {
		if (if_output_number == true) {
			cout << 0 << " : " << a[0];
			for (int i = 1; i < len; i++) {
				cout << separator << i << " : " << a[i];
			}
		} else {
			cout << a[0];
			for (int i = 1; i < len; i++) {
				cout << separator << a[i];
			}
		}
		cout << endl;
	} else if (len < 0) {
		throw invalid_argument("length < 0");
	}
}

template <class T>
void print_array_to_file(T a[], int len, string separator, string file_name, bool if_output_number) throw (invalid_argument)
{
	if (len > 0) {
		ofstream fout(&file_name[0], ios::out);
		fout << a[0];
		for (int i = 1; i < len; i++) {
			fout << separator << a[i];
		}
		fout.close();
	} else if (len < 0) {
		throw invalid_argument("length < 0");
	}
}

template <typename T>
int array_dimension(const T &a)
{
	const type_info &info = typeid(a);
	const string name = info.name();

	int dimension = 0;

	cout << name << endl;

	for (int i = 0; i < name.length() - 2;) {
		//cout<<"i="<<i<<endl;
		if (name[i] == 'A') {
			//&&name[i+2]=='_'
			//i+=3;
			i++;
			dimension++;
		} else {
			i++;
		}
	}

//cout<<dimension<<endl;
	return dimension;
}

namespace
{
	class Array_serve
	{
		public:
			template <typename T>
			int length(const T &array)
			{
				return (sizeof(array) / sizeof(array[0]));
			}

			template <typename T>
			void print(T a[], int len, string separator = " , ", bool if_output_number = false) throw (invalid_argument)
			{
				print_array(a, len, separator, if_output_number);
			}

			template <class T>
			void print_to_file(T a[], int len, string separator, string file_name, bool if_output_number = false) throw (invalid_argument)
			{
				print_array_to_file(a, len, separator, file_name, if_output_number);
			}

			template <typename T>
			int dimension(const T &a)
			{
				return array_dimension(a);
			}
	};
}
Array_serve MyArray;

namespace
{
	void _Array_init()
	{
		//remove unused warning
		(void) MyArray;
	}
}

#endif	/* End _ARRAY_SERVE_H_ */
