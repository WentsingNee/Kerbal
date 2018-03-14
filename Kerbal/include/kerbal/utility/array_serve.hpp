#ifndef _ARRAY_SERVE_HPP_
#define _ARRAY_SERVE_HPP_

#include <kerbal/utility/runtime_timer.hpp>
#include <iostream>
#include <string>
#include <typeinfo>
#include <fstream>


namespace kerbal
{
	namespace utility
	{

		namespace array_serve
		{

			//声明
			template <class Type, size_t N>
			inline size_t arraylen(const Type (&array)[N]);

			/**
			 *
			 * @param a
			 * @param len
			 * @param separator
			 * @param if_output_number
			 * @throw std::invalid_argument
			 */
			template <class T>
			void print_array(T a[], int len, const std::string &separator = " , ", bool if_output_number =
					false);

			/**
			 *
			 * @param a
			 * @param len
			 * @param separator
			 * @param file_name
			 * @param if_output_number
			 * @throw std::invalid_argument
			 */
			template <class T>
			void print_array_to_file(T a[], int len, const std::string &separator, const std::string &file_name, bool if_output_number =
					false);

			template <typename T> int array_dimension(const T &a);

			//实现
			template <class Type, size_t N>
			inline size_t arraylen(const Type (&array)[N])
			{
				return N;
			}

			template <class T>
			void print_array(T a[], int len, const std::string &separator, bool if_output_number)
			{
				if (len > 0) {
					if (if_output_number == true) {
						std::cout << 0 << " : " << a[0];
						for (int i = 1; i < len; i++) {
							std::cout << separator << i << " : " << a[i];
						}
					} else {
						std::cout << a[0];
						for (int i = 1; i < len; i++) {
							std::cout << separator << a[i];
						}
					}
					std::cout << std::endl;
				} else if (len < 0) {
					throw std::invalid_argument("length < 0");
				}
			}

			template <class T>
			void print_array_to_file(T a[], int len, const std::string &separator, const std::string &file_name, bool if_output_number)
			{
				if (len > 0) {
					std::ofstream fout(&file_name[0], std::ios::out);
					fout << a[0];
					for (int i = 1; i < len; i++) {
						fout << separator << a[i];
					}
					fout.close();
				} else if (len < 0) {
					throw std::invalid_argument("length < 0");
				}
			}

			template <typename T>
			int array_dimension(const T &a)
			{
				const std::type_info &info = typeid(a);
				const std::string name = info.name();

				int dimension = 0;

//		cout << name << endl;

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

		} /* Namespace array_serve */

	} /* namespace utility */

} /* namespace kerbal */

#endif	/* End _ARRAY_SERVE_HPP_ */
