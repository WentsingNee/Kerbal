/*
 * array_2d_base.hpp
 *
 *  Created on: 2017年10月29日
 *      Author: Peter
 */

#ifndef ARRAY_2D_BASE_HPP_
#define ARRAY_2D_BASE_HPP_

#include <iomanip>
#include <cstring>
#include "string_serve.hpp"

namespace std
{
	template <class Type>
	void swap(kerbal::data_struct::array_2d::Array_2d<Type> &A, kerbal::data_struct::array_2d::Array_2d<Type> &B) throw ()
	{
		std::swap(A.row, B.row);
		std::swap(A.column, B.column);
		std::swap(A.p, B.p);
	}
}/* Namespace std */

namespace kerbal
{
	namespace data_struct
	{
		namespace array_2d
		{

			template <class Type>
			safety<Type>::safety(Array_2d<Type> *p_to_matrix, const int row_point_to) :
					p_to_matrix(p_to_matrix), row_point_to(row_point_to)
			{
			}

			template <class Type>
			safety<Type>::safety(const Array_2d<Type> * const p2, const int row) :
					p_to_matrix((Array_2d<Type> *) p2), row_point_to(row)
			{
			}

			template <class Type>
			safety<Type>::~safety()
			{
			}

			template <class Type>
			inline bool safety<Type>::is_const() throw ()
			{
				return false;
			}

			template <class Type>
			inline bool safety<Type>::is_const() const throw ()
			{
				return true;
			}

			template <class Type>
			inline Type& safety<Type>::operator[](int column) throw (std::out_of_range)
			{
				p_to_matrix->test_column(column);
				return p_to_matrix->p[row_point_to][column];
			}

			template <class Type>
			inline const Type& safety<Type>::operator[](int column) const throw (std::out_of_range)
			{
				p_to_matrix->test_column(column);
				return p_to_matrix->p[row_point_to][column];
			}

			template <class Type>
			inline Type* safety<Type>::begin()
			{
				return p_to_matrix->p[row_point_to];
			}

			template <class Type>
			inline const Type* safety<Type>::begin() const
			{
				return p_to_matrix->p[row_point_to];
			}

			template <class Type>
			inline Type* safety<Type>::end()
			{
				return p_to_matrix->p[row_point_to] + p_to_matrix->column;
			}

			template <class Type>
			inline const Type* safety<Type>::end() const
			{
				return p_to_matrix->p[row_point_to] + p_to_matrix->column;
			}

			template <class Type>
			inline safety<Type>& safety<Type>::operator++() const
			{
				++row_point_to;
				return *this;
			}

			template <class Type>
			inline bool safety<Type>::operator!=(const safety<Type> &with) const throw (std::invalid_argument)
			{
				if (this->p_to_matrix == with.p_to_matrix) {
					return this->row_point_to != with.row_point_to;
				} else {
					throw std::invalid_argument("comparation between two iterators not belong to same Array_2d");
				}
			}

			template <class Type>
			void Array_2d<Type>::mem_init()
			{
				int i = 0;
				try {
					p = new Type*[row]; //开辟行
					for (i = 0; i < row; i++) {
						p[i] = new Type[column]; //开辟列
					}
				} catch (const std::bad_alloc &exct) {
					for (int j = 0; j < i; ++j)
						delete[] p[j];
					delete[] p;
					p = NULL;
					row = 0;
					column = 0;
					throw;
				}
			}

			template <class Type>
			Array_2d<Type>::Array_2d() throw () :
					row(0), column(0), p(NULL)
			{
			}

			template <class Type>
			Array_2d<Type>::Array_2d(const int row, const int column)
			{
				if (row > 0 && column > 0) {
					this->row = row;
					this->column = column;

					mem_init();
				} else {
					this->row = 0;
					this->column = 0;
					this->p = NULL;
				}
			}

			template <class Type>
			Array_2d<Type>::Array_2d(const int row, const int column, const Type &val)
			{
				if (row > 0 && column > 0) {
					this->row = row;
					this->column = column;

					mem_init();
					for (int i = 0; i < row; i++) {
						for (int j = 0; j < column; j++) {
							p[i][j] = val;
						}
					}
				} else {
					this->row = 0;
					this->column = 0;
					this->p = NULL;
				}
			}

			template <class Type>
			Array_2d<Type>::Array_2d(Type (*function)(), const int row, const int column, bool para)
			{
				//动态开辟一个以p为首地址的、row * column的二维数组, 并使用 function() 初始化每个元素
				if (row > 0 && column > 0) {
					this->row = row;
					this->column = column;

					mem_init();
					for (int i = 0; i < row; i++) {
						for (int j = 0; j < column; j++) {
							p[i][j] = function();
						}
					}

				} else {
					this->row = 0;
					this->column = 0;
					this->p = NULL;
				}
			}

			template <class Type>
			Array_2d<Type>::Array_2d(Type (*function)(int, int), const int row, const int column, bool para)
			{
				//动态开辟一个以p为首地址的、row * column的二维数组, 并使用 function(i,j) 初始化每个元素
				if (row > 0 && column > 0) {
					this->row = row;
					this->column = column;

					mem_init();
					for (int i = 0; i < row; i++) {
						for (int j = 0; j < column; j++) {
							p[i][j] = function(i, j);
						}
					}

				} else {
					this->row = 0;
					this->column = 0;
					this->p = NULL;
				}
			}

			template <class Type>
			template <size_t M, size_t N>
			Array_2d<Type>::Array_2d(const Type (&src)[M][N], const int row, const int column)
			{ //利用二维数组进行构造
				if (row > 0 && column > 0) {
					this->row = row;
					this->column = column;

					mem_init();
					for (int i = 0; i < row; i++) {
						for (int j = 0; j < column; j++) {
							p[i][j] = src[i][j];
						}
					}
				} else {
					this->row = 0;
					this->column = 0;
					this->p = NULL;
				}
			}

			template <class Type>
			Array_2d<Type>::Array_2d(const Type arr[], int len, bool in_a_row)
			{ //利用一维数组进行构造
				if (len > 0) {
					if (in_a_row) {
						this->row = 1;
						this->column = len;

						mem_init();
						std::copy(arr, arr + column, p[0]);
					} else {
						this->row = len;
						this->column = 1;

						mem_init();
						for (int i = 0; i < row; i++) {
							p[i][0] = arr[i];
						}
					}
				} else {
					this->row = 0;
					this->column = 0;
					this->p = NULL;
				}
			}

#if __cplusplus >= 201103L //C++0x

			template <class Type>
			Array_2d<Type>::Array_2d(std::initializer_list<std::initializer_list<Type>> src) throw (std::invalid_argument)
			{
				//利用二维初始化列表进行构造

				const int row_pre = src.size(); //最终定下的行数
				const int column_pre = src.begin()->size(); //最终定下的列数
				//扫描src每行的列数, 不一致则抛异常
				for (auto it = src.begin() + 1; it != src.end(); ++it) {
					if (it->size() != (unsigned) column_pre) {
						throw std::invalid_argument("the initializer list is not a standard Array_2d");
					}
				}

				if (row_pre > 0 && column_pre > 0) {
					this->row = row_pre;
					this->column = column_pre;

					mem_init();
					int i = 0;
					auto it = src.begin();
					while (i < row) {
						std::copy(it->begin(), it->end(), p[i]);
						++i;
						++it;
					}
				} else {
					this->row = 0;
					this->column = 0;
					this->p = NULL;
				}
			}

			template <class Type>
			Array_2d<Type>::Array_2d(std::initializer_list<Type> src)
			{
				//利用一维初始化列表进行构造
				const int column_pre = src.size();		//最终定下的列数

				if (column_pre > 0) {
					this->row = 1;
					this->column = column_pre;

					mem_init();
					std::copy(src.begin(), src.end(), p[0]);

				} else {
					this->row = 0;
					this->column = 0;
					this->p = NULL;
				}
			}

#endif //C++0x

			template <class Type>
			Array_2d<Type>::Array_2d(const Array_2d<Type> &src) //拷贝构造函数
			{
				if (src.row > 0 && src.column > 0) {
					this->row = src.row;
					this->column = src.column;

					mem_init();
					for (int i = 0; i < row; i++) {
						std::copy(src.p[i], src.p[i] + column, p[i]);
					}
				} else {
					this->row = 0;
					this->column = 0;
					this->p = NULL;
				}
			}

			template <class Type>
			Array_2d<Type>::~Array_2d() // virtual
			{
				//归还一个row行的二维数组
				for (int i = 0; i < row; i++)
					delete[] p[i];
				delete[] p;
				p = NULL;
//		cout << "析构数组" << endl;
			}

			template <class Type>
			bool Array_2d<Type>::empty() const throw ()
			{
				if (row == 0 || column == 0) {
					return true;
				} else {
					return false;
				}
			}

			template <class Type>
			void Array_2d<Type>::clear() throw ()
			{
				//归还一个row行的二维数组
				for (int i = 0; i < row; ++i)
					delete[] p[i];
				delete[] p;
				p = NULL;
				row = 0;
				column = 0;
			}

			template <class Type>
			void Array_2d<Type>::resize(int new_row, int new_column)
			{
				if (new_row <= 0 || new_column <= 0) { //防止非正数
					this->clear();
					return;
				}
				if (row == new_row) {
					if (column == new_column) { //大小与原来一致
						return;
					} else { //行数相等, 列数不等
						for (int i = 0; i < row; ++i) {
							delete[] p[i];
							p[i] = new Type[new_column];
						}
						column = new_column;
					}
				} else {
					if (column == new_column) { //行数不等, 列数相等
						//TODO 查BUG
						Type **p_former = p;
						p = new Type*[new_row];
						if (new_row < row) { //行数减少
							std::memcpy(p, p_former, new_row * sizeof(Type*));
							for (int i = new_row; i < row; ++i) {
								delete[] p_former[i];
							}
						} else { //行数增多
							std::memcpy(p, p_former, row * sizeof(Type*));
							for (int i = row; i < new_row; ++i) {
								p[i] = new Type[column];
							}
						}
						delete[] p_former;
						row = new_row;
					} else { //行数不等, 列数不等
						//TODO 查bug
						for (int i = 0; i < row; ++i)
							delete[] p[i];
						delete[] p;
						row = new_row;
						column = new_column;
						mem_init();
					}
				}
			}

			template <class Type>
			inline int Array_2d<Type>::get_row() const
			{
				return row;
			}

			template <class Type>
			inline int Array_2d<Type>::get_column() const
			{
				return column;
			}

			template <class Type>
			inline const Type** Array_2d<Type>::get_data() const
			{
				return (const Type**) (p);
			}

			template <class Type>
			inline bool Array_2d<Type>::is_const()
			{
				return false;
			}

			template <class Type>
			inline bool Array_2d<Type>::is_const() const
			{
				return true;
			}

			template <class Type>
			inline Type& Array_2d<Type>::get(int row, int column) throw (std::out_of_range)
			{
				test_row(row);
				test_column(column);
				return p[row][column];
			}

			template <class Type>
			inline const Type& Array_2d<Type>::get(int row, int column) const throw (std::out_of_range)
			{
				test_row(row);
				test_column(column);
				return p[row][column];
			}

			template <class Type>
			inline safety<Type> Array_2d<Type>::operator[](int row) throw (std::out_of_range)
			{
				test_row(row);
				return safety < Type > (this, row);
			}

			template <class Type>
			inline const safety<Type> Array_2d<Type>::operator[](int row) const throw (std::out_of_range)
			{
				test_row(row);
				return safety < Type > (this, row);
			}

			template <class Type>
			inline Type& Array_2d<Type>::operator()(int row, int column) throw (std::out_of_range)
			{
				test_row(row);
				test_column(column);
				return this->p[row][column];
			}

			template <class Type>
			inline const Type& Array_2d<Type>::operator()(int row, int column) const throw (std::out_of_range)
			{
				test_row(row);
				test_column(column);
				return this->p[row][column];
			}

			template <class Type>
			inline void Array_2d<Type>::set(int row, int column, const Type &value) throw (std::out_of_range)
			{
				test_row(row);
				test_column(column);
				p[row][column] = value;
			}

			template <class Type>
			template <class T>
			void Array_2d<Type>::set(const T src[], int row, int column) //通过数组赋值///此函数内有 BUG (没有范围判断等)
			{
				this->resize(row, column);
				for (int i = 0; i < row; i++) {
					std::copy(src[i], src[i] + column, p[i]);
				}
			}

			template <class Type>
			void Array_2d<Type>::do_call(Type (*__pf)(Type))
			{
				for (int i = 0; i < row; ++i) {
					for (int j = 0; j < column; ++j) {
						p[i][j] = __pf(p[i][j]);
					}
				}
			}

			template <class Type>
			void Array_2d<Type>::do_call(Type (*__pf)(int, int))
			{
				for (int i = 0; i < row; ++i) {
					for (int j = 0; j < column; ++j) {
						p[i][j] = __pf(i, j);
					}
				}
			}

			template <class Type>
			void Array_2d<Type>::do_call(Type (*__pf)(Type, int, int))
			{
				for (int i = 0; i < row; ++i) {
					for (int j = 0; j < column; ++j) {
						p[i][j] = __pf(p[i][j], i, j);
					}
				}
			}

			template <class Type>
			const Array_2d<Type> Array_2d<Type>::call_of(Type (*__pf)(Type)) const
			{
				Array_2d < Type > result(row, column);
				for (int i = 0; i < row; ++i) {
					for (int j = 0; j < column; ++j) {
						result.p[i][j] = __pf(this->p[i][j]);
					}
				}
				return result;
			}

			template <class Type>
			const Array_2d<Type> Array_2d<Type>::call_of(Type (*__pf)(int, int)) const
			{
				Array_2d < Type > result(row, column);
				for (int i = 0; i < row; ++i) {
					for (int j = 0; j < column; ++j) {
						result.p[i][j] = __pf(i, j);
					}
				}
				return result;
			}

			template <class Type>
			const Array_2d<Type> Array_2d<Type>::call_of(Type (*__pf)(Type, int, int)) const
			{
				Array_2d < Type > result(row, column);
				for (int i = 0; i < row; ++i) {
					for (int j = 0; j < column; ++j) {
						result.p[i][j] = __pf(this->p[i][j], i, j);
					}
				}
				return result;
			}

			template <class Type>
			inline std::ostream& operator<<(std::ostream &output, const Array_2d<Type> &src) //重载输出
			{
				src.print(Array_2d < Type > ::frame_with_corner, output);
				return output;
			}

			template <class Type>
			void Array_2d<Type>::print(Print_style style, std::ostream &output) const
			{
				//void Array_2d<Type>::print(bool print_frame = true, bool print_corner = true, ostream &output = cout) const
				int i, j;
				output << std::resetiosflags(std::ios::right) << std::setiosflags(std::ios::left) << std::setfill(' '); //清除右对齐, 设置左对齐, 设置不足补空格

				if (style != none) {
					{ //上边框
						output << "┌";
						for (j = 0; j < column; j++) {
							output << "  " << std::setw(12) << " ";
						}
						output << " ┐" << std::endl;
					}

					for (i = 0; i < row; i++) {
						output << "│";
						for (j = 0; j < column; j++) {
							output << "  " << std::setw(12) << p[i][j];
						}
						output << " │" << std::endl;
					}

					{ //下边框
						output << "└";
						for (j = 0; j < column; j++) {
							output << "  " << std::setw(12) << " ";
						}
						output << " ┘";
						if (style == frame_with_corner) {
							output << " " << row << " × " << column;
						}
						output << std::endl;
					}
				} else {
					for (i = 0; i < row; i++) {
						for (j = 0; j < column; j++) {
							output << "  " << std::setw(12) << p[i][j];
						}
						output << std::endl;
					}
				}
			}

//	template <class Type>
//	void Array_2d<Type>::print(bool print_frame, bool print_corner, std::ostream &output) const
//	{
//		//void Array_2d<Type>::print(bool print_frame = true, bool print_corner = true, ostream &output = cout) const
//		int i, j;
//		output << std::resetiosflags(std::ios::right) << std::setiosflags(std::ios::left) << std::setfill(' '); //清除右对齐, 设置左对齐, 设置不足补空格
//
//		if (print_frame) {
//			{ //上边框
//				output << "┌";
//				for (j = 0; j < column; j++) {
//					output << "  " << std::setw(12) << " ";
//				}
//				output << " ┐" << std::endl;
//			}
//
//			for (i = 0; i < row; i++) {
//				output << "│";
//				for (j = 0; j < column; j++) {
//					output << "  " << std::setw(12) << p[i][j];
//				}
//				output << " │" << std::endl;
//			}
//
//			{ //下边框
//				output << "└";
//				for (j = 0; j < column; j++) {
//					output << "  " << std::setw(12) << " ";
//				}
//				output << " ┘";
//				if (print_corner) {
//					output << " " << row << " × " << column;
//				}
//				output << std::endl;
//			}
//		} else {
//			for (i = 0; i < row; i++) {
//				for (j = 0; j < column; j++) {
//					output << "  " << std::setw(12) << p[i][j];
//				}
//				output << std::endl;
//			}
//		}
//	}

			template <class Type>
			size_t Array_2d<Type>::get_digit_size() const
			{
				return row * (sizeof(Type*) + column * sizeof(Type));
			}

			template <class Type>
			inline void Array_2d<Type>::test_row(const int row_test) const throw (std::out_of_range)
			{
#	if __cplusplus >= 201103L
				using std::to_string;
#	else
				using kerbal::string_serve::to_string;
#	endif

				if (row_test < 0 || row_test >= this->row) {
					throw std::out_of_range(
							"The " + to_string(this->row) + " × " + to_string(this->column)
									+ " Array doesn't have the no." + to_string(row_test) + " row!");
				}
			}

			template <class Type>
			inline void Array_2d<Type>::test_column(const int column_test) const throw (std::out_of_range)
			{
#	if __cplusplus >= 201103L
				using std::to_string;
#	else
				using kerbal::string_serve::to_string;
#	endif

				if (column_test < 0 || column_test >= this->column) {
					throw std::out_of_range(
							"The " + to_string(this->row) + " × " + to_string(this->column)
									+ " Array doesn't have the no." + to_string(column_test) + " column!");
				}
			}

			template <class Type>
			bool Array_2d<Type>::operator==(const Array_2d<Type> &with) const
			{
				if (row != with.row || column != with.column) {
					return false;
				}
				for (int i = 0; i < row; i++) {
					for (int j = 0; j < column; j++) {
						if (!(this->p[i][j] == with.p[i][j])) {
							return false;
						}
					}
				}
				return true;
			}

			template <class Type>
			bool Array_2d<Type>::operator!=(const Array_2d<Type> &with) const
			{
				return !(this->operator==(with));
			}

			template <class Type>
			void Array_2d<Type>::do_reflect_row() throw ()
			{
				for (int i = 0; i < row / 2; ++i) {
					std::swap(p[i], p[row - 1 - i]);
				}
			}

			template <class Type>
			void Array_2d<Type>::do_reflect_column()
			{
				for (int i = 0; i < row; ++i) {
					for (int j = 0; j < column / 2; ++j) {
						std::swap(p[i][j], p[i][column - 1 - j]); //这里有可能会抛出异常, 具体会不会取决于 swap(Type&, Type&)
					}
				}
			}

			template <class Type>
			void Array_2d<Type>::do_rotate_180()
			{
				do_reflect_row();
				do_reflect_column();
			}

			template <class Type>
			void Array_2d<Type>::do_rotate_90()
			{ // 逆时针转90度
				std::swap(row, column);

				Type **p_former = p;
				p = new Type*[row];
				for (int i = 0; i < row; ++i) {
					p[i] = new Type[column];
					for (int j = 0; j < column; ++j) {
						p[i][j] = p_former[j][row - 1 - i];
					}
				}
				for (int i = 0; i < column; ++i) {
					delete[] p_former[i];
				}
				delete[] p_former;
			}

			template <class Type>
			void Array_2d<Type>::do_rotate_270()
			{ // 逆时针转270度
				std::swap(row, column);

				Type **p_former = p;
				p = new Type*[row];
				for (int i = 0; i < row; ++i) {
					p[i] = new Type[column];
					for (int j = 0; j < column; ++j) {
						p[i][j] = p_former[column - 1 - j][i];
					}
				}
				for (int i = 0; i < column; ++i) {
					delete[] p_former[i];
				}
				delete[] p_former;
			}

			template <class Type>
			const Array_2d<Type> Array_2d<Type>::sub_of(int up, int down, int left, int right) const throw (std::invalid_argument, std::out_of_range)
			{
				if (up >= down || left >= right) {
					throw new std::invalid_argument("up >= down or left >= right");
				}

				this->test_row(up);
				this->test_row(down - 1);
				this->test_column(left);
				this->test_column(right - 1);

				Array_2d < Type > result(down - up, right - left);
				for (int i = up; i < down; ++i) {
					std::copy(p[i] + left, p[i] + right, result.p[i - up]);
				}
				return result;
			}
		}/* Namespace array_2d */

	}/* namespace data_struct */

}/* namespace kerbal */

#endif /* ARRAY_2D_BASE_HPP_ */
