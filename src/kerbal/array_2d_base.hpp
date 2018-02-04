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
#include <memory>

#ifdef _OPENMP
# include <omp.h>
# pragma message("\n\
        * " __FILE__ " 已启用 openMP. 版本代码为: " STR2(_OPENMP)\
)
#endif

namespace std
{
	template <class Type>
	void swap(kerbal::data_struct::array_2d::Array_2d<Type> &A, kerbal::data_struct::array_2d::Array_2d<
			Type> &B) throw ()
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
			typename Array_2d<Type>::Uninit Array_2d<Type>::uninit_tag;

			template <class Type>
			void Array_2d<Type>::mem_init()
			{
				if (row != 0 && column != 0) {
					p = (Type**) malloc(row * sizeof(Type*));
					if (p == NULL) {
						throw std::bad_alloc();
					}
					for (size_t i = 0; i != row; ++i) {
						p[i] = (Type*) malloc(column * sizeof(column));
						if (p[i] == NULL) {
							while (i != 0) {
								--i;
								free (p[i]);
							}
							free (p);
							throw std::bad_alloc();
						}
					}
				} else {
					row = 0;
					column = 0;
					p = NULL;
				}
			}

			template <class Type>
			Array_2d<Type>::Array_2d(size_t row, size_t column, Uninit) :
					p(NULL), row(row), column(column)
			{
				mem_init();
			}

			template <class Type>
			Array_2d<Type>::Array_2d() throw () :
					p(NULL), row(0), column(0)
			{
			}

			template <class Type>
			Array_2d<Type>::Array_2d(size_t row, size_t column) :
					p(NULL), row(row), column(column)
			{
				mem_init();
				for (size_t i = 0; i != row; ++i) {
					for (size_t j = 0; j != column; ++j) {
						new (p[i] + j) Type();
					}
				}
			}

			template <class Type>
			Array_2d<Type>::Array_2d(size_t row, size_t column, const Type &val) :
					p(NULL), row(row), column(column)
			{
				mem_init();
				for (size_t i = 0; i != row; ++i) {
					std::uninitialized_fill_n(p[i], column, val);
				}
			}

#if __cplusplus < 201103L
			template <class Type>
			Array_2d<Type>::Array_2d(Type (*function)(), size_t row, size_t column, bool para) :
			p(NULL), row(row), column(column)
			{
				//动态开辟一个以p为首地址的、row * column的二维数组, 并使用 function() 初始化每个元素
				mem_init();
				for (size_t i = 0; i != row; ++i) {
					for (size_t j = 0; j != column; ++j) {
						new (p[i] + j) Type(function());
					}
				}
			}

			template <class Type>
			Array_2d<Type>::Array_2d(Type (*function)(size_t, size_t), size_t row, size_t column, bool para) :
			p(NULL),row(row), column(column)
			{
				//动态开辟一个以p为首地址的、row * column的二维数组, 并使用 function(i,j) 初始化每个元素
				mem_init();
				for (size_t i = 0; i != row; ++i) {
					for (size_t j = 0; j != column; ++j) {
						new (p[i] + j) Type(function(i, j));
					}
				}
			}

#else
			template <class Type>
			Array_2d<Type>::Array_2d(std::function<Type()> fun, size_t row, size_t column, bool para) :
					p(NULL), row(row), column(column)
			{
				//动态开辟一个以p为首地址的、row * column的二维数组, 并使用 function() 初始化每个元素
				mem_init();
#			ifndef _OPENMP
				for (size_t i = 0; i != row; ++i) {
					for (size_t j = 0; j != column; ++j) {
						new (p[i] + j) Type(fun());
					}
				}
#			else

#pragma message("\n\
        * parallel constructor enable"\
)

#				pragma omp parallel for
				for (size_t i = 0; i < row; ++i) {
					for (size_t j = 0; j != column; ++j) {
						new (p[i] + j) Type(fun());
					}
				}

#			endif
			}

			template <class Type>
			Array_2d<Type>::Array_2d(std::function<Type(size_t, size_t)> fun, size_t row, size_t column, bool para) :
					p(NULL), row(row), column(column)
			{
				//动态开辟一个以p为首地址的、row * column的二维数组, 并使用 function(i,j) 初始化每个元素
				mem_init();
				for (size_t i = 0; i != row; ++i) {
					for (size_t j = 0; j != column; ++j) {
						new (p[i] + j) Type(fun(i, j));
					}
				}
			}
#endif

			template <class Type>
			template <size_t LEN>
			Array_2d<Type>::Array_2d(const Type (&src)[LEN], bool in_row) :
					p(NULL), row(0), column(0)
			{ //利用一维数组进行构造

				if (in_row) {
					this->row = 1;
					this->column = LEN;

					mem_init();
					std::uninitialized_copy(src, src + LEN, p[0]);

				} else {
					this->row = LEN;
					this->column = 1;

					mem_init();
					const Type *it = src;
					for (size_t i = 0; i != row; ++i) {
						new (p[i]) Type(*it);
						++it;
					}
				}
			}

			template <class Type>
			template <size_t ROW, size_t COLUMN>
			Array_2d<Type>::Array_2d(const Type (&src)[ROW][COLUMN]) :
					p(NULL), row(ROW), column(COLUMN)
			{ //利用二维数组进行构造
				mem_init();
				for (size_t i = 0; i != row; ++i) {
					for (size_t j = 0; j != column; ++j) {
						new (p[i] + j) Type(src[i][j]);
					}
				}
			}

#if __cplusplus >= 201103L //C++0x

			template <class Type>
			Array_2d<Type>::Array_2d(std::initializer_list<std::initializer_list<Type>> src)
			{
				//利用二维初始化列表进行构造

				const size_t row_pre = src.size(); //最终定下的行数
				const size_t column_pre = src.begin()->size(); //最终定下的列数
				//扫描src每行的列数, 不一致则抛异常
				for (auto it = src.begin() + 1; it != src.end(); ++it) {
					if (it->size() != (unsigned) column_pre) {
						throw std::invalid_argument(
								"the initializer list is not a standard Array_2d");
					}
				}

				if (row_pre > 0 && column_pre > 0) {
					this->row = row_pre;
					this->column = column_pre;

					mem_init();
					size_t i = 0;
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
			Array_2d<Type>::Array_2d(std::initializer_list<Type> src) :
					p(NULL), row(1), column(src.size())
			{				//利用一维初始化列表进行构造

				mem_init();
				std::uninitialized_copy(src.begin(), src.end(), p[0]);
			}

#endif //C++0x

			template <class Type>
			Array_2d<Type>::Array_2d(const Array_2d<Type> &src) :
					p(NULL), row(src.row), column(src.column)
			{ //拷贝构造函数
				mem_init();
				for (size_t i = 0; i != row; ++i) {
					std::uninitialized_copy(src.p[i], src.p[i] + column, p[i]);
				}
			}

			template <class Type>
			Array_2d<Type>::~Array_2d() // virtual
			{ //归还一个row行的二维数组
				clear();
			}

			template <class Type>
			bool Array_2d<Type>::empty() const throw ()
			{
				return !(row && column);
			}

			template <class Type>
			void Array_2d<Type>::clear() throw ()
			{
//				for (size_t i = 0; i != row; ++i) {
//					for (size_t j = 0; j != column; ++j) {
//						(p[i] + j)->~Type();
//					}
//					free (p[i]);
//					p[i] = NULL;
//				}
				for (size_t i = row; i != 0;) {
					--i;
					for (size_t j = column; j != 0;) {
						--j;
						(p[i] + j)->~Type();
					}
					free (p[i]);
					p[i] = NULL;
				}
				free (p);
				p = NULL;
				row = 0;
				column = 0;
			}

			template <class Type>
			size_t Array_2d<Type>::shrink_row(size_t new_row)
			{
				if (new_row < this->row) {
					if (new_row == 0) {
						this->clear();
					} else {
						for (size_t i = row; i != new_row;) {
							--i;
							for (size_t j = column; j != 0;) {
								--j;
								(p[i] + j)->~Type();
							}
							free (p[i]);
							p[i] = NULL;
						}
						this->p = (Type**) realloc(this->p, new_row * sizeof(Type*));
						this->row = new_row;
					}
				}
				return this->row;
			}

			template <class Type>
			size_t Array_2d<Type>::shrink_column(size_t new_column)
			{
				if (new_column < this->column) {
					if (new_column == 0) {
						this->clear();
					} else {
						for (size_t i = row; i != 0;) {
							--i;
							for (size_t j = column; j != new_column;) {
								--j;
								(p[i] + j)->~Type();
							}
							p[i] = (Type*) realloc(p[i], new_column * sizeof(Type));
						}
						this->column = new_column;
					}
				}
				return this->column;
			}

			template <class Type>
			size_t Array_2d<Type>::enlarge_row_buffer(size_t new_row)
			{
				return 0;
			}

			template <class Type>
			size_t Array_2d<Type>::enlarge_column_buffer(size_t new_column)
			{
				if (new_column > this->column) {
					for (size_t i = 0; i != this->row; ++i) {
						Type * p_new = (Type*) realloc(p[i], new_column * sizeof(Type));
						if (p_new == NULL) {
							//realloc
							throw std::bad_alloc();
						}
						p[i] = p_new;
					}
				}
				return this->column;
			}

			template <class Type>
			void Array_2d<Type>::resize(size_t new_row, size_t new_column)
			{
//				if (new_row == 0 || new_column == 0) {
//					this->clear();
//					return;
//				}
//				if (row == new_row) {
//					if (column == new_column) { //大小与原来一致
//						return;
//					} else { //行数相等, 列数不等
//						for (int i = 0; i < row; ++i) {
//							delete[] p[i];
//							p[i] = new Type[new_column];
//						}
//						column = new_column;
//					}
//				} else {
//					if (column == new_column) { //行数不等, 列数相等
//						//TODO 查BUG
//						Type **p_former = p;
//						p = new Type*[new_row];
//						if (new_row < row) { //行数减少
//							std::memcpy(p, p_former, new_row * sizeof(Type*));
//							for (int i = new_row; i < row; ++i) {
//								delete[] p_former[i];
//							}
//						} else { //行数增多
//							std::memcpy(p, p_former, row * sizeof(Type*));
//							for (int i = row; i < new_row; ++i) {
//								p[i] = new Type[column];
//							}
//						}
//						delete[] p_former;
//						row = new_row;
//					} else { //行数不等, 列数不等
//						//TODO 查bug
//						for (int i = 0; i < row; ++i)
//							delete[] p[i];
//						delete[] p;
//						row = new_row;
//						column = new_column;
//						mem_init();
//					}
//				}

				if (new_row <= this->row) {
					this->shrink_row(new_row);
				} else {
//					this->enlarge_row_buffer(new_row);
					//构造
				}
			}

			template <class Type>
			size_t Array_2d<Type>::get_row() const
			{
				return row;
			}

			template <class Type>
			size_t Array_2d<Type>::get_column() const
			{
				return column;
			}

			template <class Type>
			const Type** Array_2d<Type>::get_data() const
			{
				return (const Type**) (p);
			}

			template <class Type>
			bool Array_2d<Type>::is_const()
			{
				return false;
			}

			template <class Type>
			bool Array_2d<Type>::is_const() const
			{
				return true;
			}

			template <class Type>
			Type& Array_2d<Type>::get(size_t row, size_t column) throw (std::out_of_range)
			{
				test_row(row);
				test_column(column);
				return p[row][column];
			}

			template <class Type>
			const Type& Array_2d<Type>::get(size_t row, size_t column) const
					throw (std::out_of_range)
			{
				test_row(row);
				test_column(column);
				return p[row][column];
			}

			template <class Type>
			Type& Array_2d<Type>::operator()(size_t row, size_t column) throw (std::out_of_range)
			{
				test_row(row);
				test_column(column);
				return p[row][column];
			}

			template <class Type>
			const Type& Array_2d<Type>::operator()(size_t row, size_t column) const
					throw (std::out_of_range)
			{
				test_row(row);
				test_column(column);
				return p[row][column];
			}

			template <class Type>
			void Array_2d<Type>::set(size_t row, size_t column, const Type &value)
					throw (std::out_of_range)
			{
				test_row(row);
				test_column(column);
				p[row][column] = value;
			}

#if __cplusplus >= 201103L
			template <class Type>
			void Array_2d<Type>::set(size_t row, size_t column, Type && value)
			{
				test_row(row);
				test_column(column);
				p[row][column] = value;
			}
#endif

			template <class Type>
#if __cplusplus < 201103L
			void Array_2d<Type>::do_call(Type (*__pf)(Type))
#else
			void Array_2d<Type>::do_call(std::function<Type(const Type &)> && __pf)
#endif
			{
				for (size_t i = 0; i != row; ++i) {
					for (size_t j = 0; j != column; ++j) {
						p[i][j] = __pf(p[i][j]);
					}
				}
			}

			template <class Type>
#if __cplusplus < 201103L
			void Array_2d<Type>::do_call(Type (*__pf)(size_t, size_t))
#else
			void Array_2d<Type>::do_call(std::function<Type(size_t, size_t)> && __pf)
#endif
			{
				for (size_t i = 0; i != row; ++i) {
					for (size_t j = 0; j != column; ++j) {
						p[i][j] = __pf(i, j);
					}
				}
			}

			template <class Type>
#if __cplusplus < 201103L
			void Array_2d<Type>::do_call(Type (*__pf)(Type, size_t, size_t))
#else
			void Array_2d<Type>::do_call(std::function<Type(const Type &, size_t, size_t)> && __pf)
#endif
			{
				for (size_t i = 0; i != row; ++i) {
					for (size_t j = 0; j != column; ++j) {
						p[i][j] = __pf(p[i][j], i, j);
					}
				}
			}

			template <class Type>
#if __cplusplus < 201103L
			const Array_2d<Type> Array_2d<Type>::call_of(Type (*__pf)(Type)) const
#else
			const Array_2d<Type> Array_2d<Type>::call_of(std::function<Type(const Type &)> && __pf) const
#endif
			{
				Array_2d < Type > result(row, column, Array_2d < Type > ::uninit_tag);
				for (size_t i = 0; i != row; ++i) {
					for (size_t j = 0; j != column; ++j) {
						new (result.p[i] + j) Type(__pf(this->p[i][j]));
					}
				}
				return result;
			}

			template <class Type>
#if __cplusplus < 201103L
			const Array_2d<Type> Array_2d<Type>::call_of(Type (*__pf)(size_t, size_t)) const
#else
			const Array_2d<Type> Array_2d<Type>::call_of(std::function<Type(size_t, size_t)> && __pf) const
#endif
			{
				Array_2d < Type > result(row, column, Array_2d < Type > ::uninit_tag);
				for (size_t i = 0; i != row; ++i) {
					for (size_t j = 0; j != column; ++j) {
						new (result.p[i] + j) Type(__pf(i, j));
					}
				}
				return result;
			}

			template <class Type>
#if __cplusplus < 201103L
			const Array_2d<Type> Array_2d<Type>::call_of(Type (*__pf)(Type, size_t, size_t)) const
#else
			const Array_2d<Type> Array_2d<Type>::call_of(std::function<
					Type(const Type &, size_t, size_t)> && __pf) const
#endif
			{
				Array_2d < Type > result(row, column, Array_2d < Type > ::uninit_tag);
				for (size_t i = 0; i != row; ++i) {
					for (size_t j = 0; j != column; ++j) {
						new (result.p[i] + j) Type(__pf(this->p[i][j], i, j));
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
				size_t i, j;
				output << std::resetiosflags(std::ios::right) << std::setiosflags(std::ios::left)
						<< std::setfill(' '); //清除右对齐, 设置左对齐, 设置不足补空格

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

			template <class Type>
			size_t Array_2d<Type>::get_digit_size() const
			{
				return row * (sizeof(Type*) + column * sizeof(Type));
			}

			template <class Type>
			inline void Array_2d<Type>::test_row(size_t row_test) const throw (std::out_of_range)
			{
#	if __cplusplus >= 201103L
				using std::to_string;
#	else
				using kerbal::string_serve::to_string;
#	endif

				if (row_test >= this->row) {
					throw std::out_of_range(
							"The " + to_string(this->row) + " × " + to_string(this->column)
									+ " Array doesn't have the no." + to_string(row_test)
									+ " row!");
				}
			}

			template <class Type>
			inline void Array_2d<Type>::test_column(size_t column_test) const
					throw (std::out_of_range)
			{
#	if __cplusplus >= 201103L
				using std::to_string;
#	else
				using kerbal::string_serve::to_string;
#	endif

				if (column_test >= this->column) {
					throw std::out_of_range(
							"The " + to_string(this->row) + " × " + to_string(this->column)
									+ " Array doesn't have the no." + to_string(column_test)
									+ " column!");
				}
			}

			template <class Type>
			void Array_2d<Type>::do_reflect_row() throw ()
			{
				for (size_t i = 0; i < row / 2; ++i) {
					std::swap(p[i], p[row - 1 - i]);
				}
			}

			template <class Type>
			void Array_2d<Type>::do_reflect_column()
			{
				for (size_t i = 0; i < row; ++i) {
					for (size_t j = 0; j < column / 2; ++j) {
						//这里有可能会抛出异常, 具体会不会取决于 swap(Type&, Type&)
						std::swap(p[i][j], p[i][column - 1 - j]);
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
				Array_2d < Type > result = this->rotate_90_of();
				this->clear();
				this->row = result.row;
				this->column = result.column;
				this->p = result.p;

				result.p = NULL;
				result.column = 0;
				result.row = 0;
			}

			template <class Type>
			void Array_2d<Type>::do_rotate_270()
			{ // 逆时针转270度
				Array_2d < Type > result = this->rotate_270_of();
				this->clear();
				this->row = result.row;
				this->column = result.column;
				this->p = result.p;

				result.p = NULL;
				result.column = 0;
				result.row = 0;
			}

			template <class Type>
			Array_2d<Type> Array_2d<Type>::reflect_row_of() const
			{
				Array_2d < Type > result(this->row, this->column, Array_2d < Type > ::uninit_tag);

				for (size_t i = 0; i < this->row; ++i) {
					std::uninitialized_copy(this->p[this->row - 1 - i],
							this->p[this->row - 1 - i] + this->column, result.p[i]);
				}
				return result;
			}

			template <class Type>
			Array_2d<Type> Array_2d<Type>::reflect_column_of() const
			{
				Array_2d < Type > result(this->row, this->column, Array_2d < Type > ::uninit_tag);

				for (size_t i = 0; i < this->row; ++i) {
					for (size_t j = 0; j < this->column; ++j) {
						new (result.p[i] + j) Type(this->p[i][this->column - 1 - j]);
					}
				}
				return result;
			}

			template <class Type>
			Array_2d<Type> Array_2d<Type>::rotate_180_of() const
			{
				Array_2d < Type > result(this->row, this->column, Array_2d < Type > ::uninit_tag);

				for (size_t i = 0; i < this->row; ++i) {
					for (size_t j = 0; j < this->column; ++j) {
						new (result.p[i] + j) Type(
								this->p[this->row - 1 - i][this->column - 1 - j]);
					}
				}
				return result;
			}

			template <class Type>
			Array_2d<Type> Array_2d<Type>::rotate_90_of() const
			{
				// 逆时针转90度
				Array_2d < Type > result(this->column, this->row, Array_2d < Type > ::uninit_tag);

				for (size_t i = 0; i < this->column; ++i) {
					for (size_t j = 0; j < this->row; ++j) {
						new (result.p[i] + j) Type(this->p[j][this->column - 1 - i]);
					}
				}
				return result;
			}

			template <class Type>
			Array_2d<Type> Array_2d<Type>::rotate_270_of() const
			{
				// 逆时针转270度
				Array_2d < Type > result(this->column, this->row, Array_2d < Type > ::uninit_tag);

				for (size_t i = 0; i < this->column; ++i) {
					for (size_t j = 0; j < this->row; ++j) {
						new (result.p[i] + j) Type(this->p[this->row - 1 - j][i]);
					}
				}
				return result;
			}

			template <class Type>
			const Array_2d<Type> Array_2d<Type>::sub_of(size_t up, size_t down, size_t left, size_t right) const
					throw (std::invalid_argument, std::out_of_range)
			{
				if (up >= down || left >= right) {
					throw new std::invalid_argument("up >= down or left >= right");
				}

				this->test_row(up);
				this->test_row(down - 1);
				this->test_column(left);
				this->test_column(right - 1);

				Array_2d < Type > result(down - up, right - left, Array_2d < Type > ::uninit_tag);
				for (size_t i = up; i < down; ++i) {
					std::uninitialized_copy(p[i] + left, p[i] + right, result.p[i - up]);
				}
				return result;
			}
		}/* Namespace array_2d */

	}/* namespace data_struct */

}/* namespace kerbal */

#endif /* ARRAY_2D_BASE_HPP_ */
