#ifndef _ARRAY_2D_HPP_
#define _ARRAY_2D_HPP_

#include <iostream>
#include "except_C++0x.hpp"

#if __cplusplus >= 201103L //C++0x
#	include <initializer_list>
#	include <functional>
#endif //C++0x

namespace kerbal
{
	namespace data_struct
	{
		namespace array_2d
		{
			template <class Type> class Array_2d;
		}
	}
}

namespace std
{
	template <class Type>
	void swap(kerbal::data_struct::array_2d::Array_2d<Type> &A, kerbal::data_struct::array_2d::Array_2d<
			Type> &B) throw ();
}

namespace kerbal
{
	namespace data_struct
	{
		namespace array_2d
		{
			/**
			 * 计算二维数组的行数
			 * @param arr 待计算的二维数组
			 * @return 行数
			 */
			template <class Type, size_t M, size_t N>
			inline size_t array_2d_row(const Type (&arr)[M][N])
			{
				return M;
			}

			/**
			 * 计算二维数组的列数
			 * @param arr 待计算的二维数组
			 * @return 列数
			 */
			template <class Type, size_t M, size_t N>
			inline size_t array_2d_column(const Type (&arr)[M][N])
			{
				return N;
			}

			template <class Type> class Array_2d;
			template <class Type> inline std::ostream& operator<<(std::ostream &output, const Array_2d<
					Type> &src); //重载输出

			/**
			 * @brief 动态二维数组类
			 * @author 倪文卿
			 * @remarks 本类提供了对动态二维数组的支持, 相比于 std::vector<std::vector<Type> > , 此类可确保二维数组的每一行拥有相同的元素个数, 且更节省存储空间
			 */
			template <class Type>
			class Array_2d
			{
				protected:
					/** @brief 数据区 */
					Type **p = NULL;

					/** @brief 行数 */
					size_t row;

					/** @brief 列数 */
					size_t column;

					/** @brief 内存初始化 */
					void mem_init();

					struct Uninit
					{
					};

					static Uninit uninit_tag;

					Array_2d(size_t row, size_t column, Uninit);

				public:

					typedef Type type;
					typedef Type& reference;
					typedef const Type& const_reference;

					/**
					 * @brief 构造一个 0 行 0 列的空二维数组
					 * @throws 本函数承诺不抛出任何异常
					 */
					Array_2d() throw ();

					/**
					 * @brief 构造一个 row 行 column 列的二维数组, 数组中每个元素的初始值由默认构造函数生成
					 * @param row 行数
					 * @param column 列数
					 */
					Array_2d(size_t row, size_t column);

					/**
					 * @brief 构造一个 row 行 column 列的二维数组, 数组中每个元素的初始值由参数 val 指定
					 * @param row 行数
					 * @param column 列数
					 * @param val 初始值
					 */
					Array_2d(size_t row, size_t column, const Type &val);

#if __cplusplus < 201103L
					/**
					 * @brief 构造一个 row 行 column 列的二维数组, 数组中每个元素的初始值通过调用函数 function 获得
					 * @param function 构造函数
					 * @param row 行数
					 * @param column 列数
					 * @param para
					 */
					Array_2d(Type (*function)(), size_t row, size_t column, bool para=false);
					//动态开辟一个以p为首地址的、row * column的二维数组, 并使用 function() 初始化每个元素
					Array_2d(Type (*function)(size_t, size_t), size_t row, size_t column, bool para=false);
					//动态开辟一个以p为首地址的、row * column的二维数组, 并使用 function(i,j) 初始化每个元素
#else

					Array_2d(std::function<Type()> fun, size_t row, size_t column, bool para = false);
					Array_2d(std::function<Type(size_t, size_t)> fun, size_t row, size_t column, bool para =
							false);

#endif

					template <size_t LEN>
					explicit Array_2d(const Type (&src)[LEN], bool in_row = true); //利用一维数组进行构造

					template <size_t ROW, size_t COLUMN>
					explicit Array_2d(const Type (&src)[ROW][COLUMN]); //利用二维数组进行构造

#	if __cplusplus >= 201103L //C++0x
					Array_2d(std::initializer_list<std::initializer_list<Type>> src); //利用二维初始化列表进行构造
					Array_2d(std::initializer_list<Type> src); //利用一维初始化列表进行构造
#	endif //C++0x

					Array_2d(const Array_2d &src); //拷贝构造函数

					virtual ~Array_2d();

					/**
					 * @brief 查询动态二维数组是否为空数组
					 * @return 结果
					 */
					bool empty() const throw ();

					/**
					 * @brief 将动态二维数组置为空数组
					 */
					void clear() throw ();

					size_t shrink_row(size_t new_row);
					size_t shrink_column(size_t new_column);

				protected:
					size_t enlarge_row_buffer(size_t new_row);
					size_t enlarge_column_buffer(size_t new_column);

					void resize(size_t new_row, size_t new_column);

				public:
					/**
					 * @brief 获取动态二维数组的行数
					 * @return 行数
					 */
					size_t get_row() const;
					size_t get_column() const;
					const Type** get_data() const;
					bool is_const();
					bool is_const() const;

					Type& get(size_t row, size_t column) throw (std::out_of_range);
					const Type& get(size_t row, size_t column) const throw (std::out_of_range);

					void set(size_t row, size_t column, const Type &value) throw (std::out_of_range);

#if __cplusplus >= 201103L
					void set(size_t row, size_t column, Type && value);
#endif

#if __cplusplus < 201103L
					void do_call(Type (*__pf)(Type));
					void do_call(Type (*__pf)(size_t, size_t));
					void do_call(Type (*__pf)(Type, size_t, size_t));
					const Array_2d<Type> call_of(Type (*__pf)(Type)) const;
					const Array_2d<Type> call_of(Type (*__pf)(size_t, size_t)) const;
					const Array_2d<Type> call_of(Type (*__pf)(Type, size_t, size_t)) const;
#else
					void do_call(std::function<Type(const Type &)> && __pf);
					void do_call(std::function<Type(size_t, size_t)> && __pf);
					void do_call(std::function<Type(const Type &, size_t, size_t)> && __pf);
					const Array_2d<Type> call_of(std::function<Type(const Type &)> && __pf) const;
					const Array_2d<Type> call_of(std::function<Type(size_t, size_t)> && __pf) const;
					const Array_2d<Type> call_of(std::function<Type(const Type &, size_t, size_t)> && __pf) const;
#endif //c++0x

					enum Print_style
					{
						frame_with_corner, frame_only, none
					};

					virtual void print(Print_style style = frame_with_corner, std::ostream &output =
							std::cout) const;

					//void print_to_file(char file_name[],bool if_output_frame) const;

					Type& operator()(size_t row, size_t column) throw (std::out_of_range);
					const Type& operator()(size_t row, size_t column) const
							throw (std::out_of_range);

					virtual size_t get_digit_size() const;

					friend void std::swap<>(Array_2d<Type> &A, Array_2d<Type> &B) throw ();

					virtual void test_row(size_t row_test) const throw (std::out_of_range);
					virtual void test_column(size_t column_test) const throw (std::out_of_range);

					void do_reflect_row() throw ();
					void do_reflect_column(); //这里有可能会抛出异常, 具体会不会取决于 swap(Type&, Type&)
					void do_rotate_180();
					void do_rotate_90(); // 逆时针转90度
					void do_rotate_270(); // 逆时针转270度

					Array_2d<Type> reflect_row_of() const;
					Array_2d<Type> reflect_column_of() const;
					Array_2d<Type> rotate_180_of() const;
					Array_2d<Type> rotate_90_of() const; // 逆时针转90度
					Array_2d<Type> rotate_270_of() const; // 逆时针转270度

					const Array_2d<Type> sub_of(size_t up, size_t down, size_t left, size_t right) const
							throw (std::invalid_argument, std::out_of_range);

			};
		}/* Namespace array_2d */

	}/* namespace data_struct */

}/* namespace kerbal */

#include "array_2d_base.hpp"
#endif	/* End _ARRAY_2D_HPP_ */
