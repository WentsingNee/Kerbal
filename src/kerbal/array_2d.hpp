#ifndef _ARRAY_2D_HPP_
#define _ARRAY_2D_HPP_

#include <iostream>
#include "except_C++0x.hpp"

#if __cplusplus >= 201103L //C++0x
#	include <initializer_list>
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
	void swap(kerbal::data_struct::array_2d::Array_2d<Type> &A, kerbal::data_struct::array_2d::Array_2d<Type> &B) throw ();
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
			template <class Type> inline std::ostream& operator<<(std::ostream &output, const Array_2d<Type> &src); //重载输出

			/**
			 * @brief 动态二维数组类的安全下标类
			 * @author 倪文卿
			 * @remarks 本类用来提供对动态二维数组Array_2d类的下标运算的安全访问
			 */
			template <class Type>
			class safety
			{
				protected:
					Array_2d<Type> *p_to_matrix;
					mutable int row_point_to;
				public:
					safety(Array_2d<Type> *p_to_matrix, const int row_point_to);
					safety(const Array_2d<Type> * const p2, const int row);

					virtual ~safety();

					inline bool is_const() throw ();
					inline bool is_const() const throw ();

					inline Type& operator[](int row) throw (std::out_of_range);
					inline const Type& operator[](int row) const throw (std::out_of_range);

					inline Type* begin();
					inline const Type* begin() const;

					inline Type* end();
					inline const Type* end() const;

					inline safety<Type>& operator++() const;

					inline bool operator!=(const safety<Type> &with) const throw (std::invalid_argument);
			};

			/**
			 * @brief 动态二维数组类
			 * @author 倪文卿
			 * @remarks 本类提供了对动态二维数组的支持, 相比于 std::vector<std::vector<Type> > , 此类可确保二维数组的每一行拥有相同的元素个数, 且更节省存储空间
			 */
			template <class Type>
			class Array_2d
			{
				protected:
					/** @brief 行数 */
					int row;

					/** @brief 列数 */
					int column;

					/** @brief 数据区 */
					Type **p = NULL;

					/** @brief 内存初始化 */
					void mem_init();

				public:
					friend class safety<Type> ;

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
					Array_2d(const int row, const int column);

					/**
					 * @brief 构造一个 row 行 column 列的二维数组, 数组中每个元素的初始值由参数 val 指定
					 * @param row 行数
					 * @param column 列数
					 * @param val 初始值
					 */
					Array_2d(const int row, const int column, const Type &val);

					/**
					 * @brief 构造一个 row 行 column 列的二维数组, 数组中每个元素的初始值通过调用函数 function 获得
					 * @param function 构造函数
					 * @param row 行数
					 * @param column 列数
					 * @param para
					 */
					Array_2d(Type (*function)(), const int row, const int column, bool para);
					//动态开辟一个以p为首地址的、row * column的二维数组, 并使用 function() 初始化每个元素
					Array_2d(Type (*function)(int, int), const int row, const int column, bool para);
					//动态开辟一个以p为首地址的、row * column的二维数组, 并使用 function(i,j) 初始化每个元素

					template <size_t M, size_t N>
					Array_2d(const Type (&src)[M][N], const int row, const int column); //利用二维数组进行构造

					Array_2d(const Type arr[], int len, bool in_a_row = true); //利用一维数组进行构造

#	if __cplusplus >= 201103L //C++0x
					Array_2d(std::initializer_list<std::initializer_list<Type>> src) throw (std::invalid_argument); //利用二维初始化列表进行构造
					Array_2d(std::initializer_list<Type> src);//利用一维初始化列表进行构造
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

					void resize(int new_row, int new_column);

					/**
					 * @brief 获取动态二维数组的行数
					 * @return 行数
					 */
					inline int get_row() const;
					inline int get_column() const;
					inline const Type** get_data() const;
					inline bool is_const();
					inline bool is_const() const;

					Type& get(int row, int column) throw (std::out_of_range);
					const Type& get(int row, int column) const throw (std::out_of_range);

					inline void set(int row, int column, const Type &value) throw (std::out_of_range);
					template <class T> void set(const T src[], int row, int column); //根据二维数组设值
					void do_call(Type (*__pf)(Type));
					void do_call(Type (*__pf)(int, int));
					void do_call(Type (*__pf)(Type, int, int));
					const Array_2d<Type> call_of(Type (*__pf)(Type)) const;
					const Array_2d<Type> call_of(Type (*__pf)(int, int)) const;
					const Array_2d<Type> call_of(Type (*__pf)(Type, int, int)) const;

					enum Print_style
					{
						frame_with_corner, frame_only, none
					};

					virtual void print(Print_style style = frame_with_corner, std::ostream &output = std::cout) const;

					//void print_to_file(char file_name[],bool if_output_frame) const;

					inline safety<Type> operator[](int row) throw (std::out_of_range);
					inline const safety<Type> operator[](int row) const throw (std::out_of_range);
					inline Type& operator()(int row, int column) throw (std::out_of_range);
					inline const Type& operator()(int row, int column) const throw (std::out_of_range);

					virtual size_t get_digit_size() const;

					friend void std::swap<>(Array_2d<Type> &A, Array_2d<Type> &B) throw ();

					virtual void test_row(const int row_test) const throw (std::out_of_range);
					virtual void test_column(const int column_test) const throw (std::out_of_range);

//					virtual bool operator==(const Array_2d<Type> &with) const;
//					virtual bool operator!=(const Array_2d<Type> &with) const;

					void do_reflect_row() throw ();
					void do_reflect_column(); //这里有可能会抛出异常, 具体会不会取决于 swap(Type&, Type&)
					void do_rotate_180();
					void do_rotate_90(); // 逆时针转90度
					void do_rotate_270(); // 逆时针转270度

					const Array_2d<Type> sub_of(int up, int down, int left, int right) const throw (std::invalid_argument, std::out_of_range);

			};
		}/* Namespace array_2d */

	}/* namespace data_struct */

}/* namespace kerbal */

#include "array_2d_base.hpp"
#endif	/* End _ARRAY_2D_HPP_ */
