/**
 * @file		auto_array.hpp
 * @brief
 * @date		2018年4月28日
 * @author		Peter
 * @copyright	Peter
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 */

#ifndef INCLUDE_KERBAL_DATA_STRUCT_AUTO_ARRAY_HPP_
#define INCLUDE_KERBAL_DATA_STRUCT_AUTO_ARRAY_HPP_

#include <cctype>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif

namespace kerbal
{
	namespace data_struct
	{
		namespace auto_array
		{
			/**
			 * @class 存储在栈上的，大小可变的数组
			 * @tparam Tp 类型
			 * @tparam N 最大支持的长度
			 */
			template <typename Tp, size_t N>
			class Auto_array
			{
				public:
					typedef char byte;

					/** @typedef 数组所存放的元素的类型 */
					typedef Tp type;
					/** @typedef 数组所存放的元素的常量类型 */
					typedef const Tp const_type;
					/** @typedef 数组所存放的元素的引用类型 */
					typedef Tp& reference;
					/** @typedef 数组所存放的元素的常引用类型 */
					typedef const Tp& const_reference;
					/** @typedef 数组所存放的元素的指针类型 */
					typedef Tp* pointer;
					/** @typedef 数组所存放的元素的常量指针类型 */
					typedef const Tp* const_pointer;

					/** @typedef 与该 Auto_array 所等价的 C 风格数组的类型, 即 Tp[N] */
					typedef type equal_c_array[N];
					typedef equal_c_array& equal_c_array_reference;
					typedef const type const_equal_c_array[N];
					typedef const_equal_c_array& const_equal_c_array_reference;

					/** class 正向迭代器 */
					typedef class iterator
					{
						private:
							pointer p;
							const Auto_array * const p_to_src_array;

						public:


							iterator(pointer p, const Auto_array * const p_to_src_array) :
									p(p), p_to_src_array(p_to_src_array)
							{
							}

							reference operator*() const;

							//前自增
							iterator& operator++();
							//后自增
							iterator operator++(int);
							iterator& operator--();
							iterator operator--(int);

							iterator operator+(int delta);
							iterator operator-(int delta);

							const iterator operator+(int delta) const;
							const iterator operator-(int delta) const;

							bool operator==(const iterator & with) const;
							bool operator!=(const iterator & with) const;
							bool operator<(const iterator & with) const;
							bool operator<=(const iterator & with) const;
							bool operator>(const iterator & with) const;
							bool operator>=(const iterator & with) const;

					} iterator;

#if __cplusplus >= 201103L
					/** @brief 数组所能容纳的最大元素数目 */
					static constexpr size_t max_size = N;
#else
					/** @brief 数组所能容纳的最大元素数目 */
					static const size_t max_size;
#endif

				private:
					byte p_byte[N * sizeof(type) / sizeof(byte)];
					equal_c_array & p;
					size_t n;

				public:
					/** @brief 默认的构造函数 */
					Auto_array();

					/**
					 * @brief 拷贝构造函数
					 * @param src 拷贝源
					 */
					Auto_array(const Auto_array & src);

#				if __cplusplus >= 201103L

					/**
					 * @brief 从初始化列表构造
					 * @param src 初始化列表
					 * @warning
					 */
					Auto_array(std::initializer_list<type> src);
#				endif

					/**
					 * @brief 以一段区间内的内容初始化数组
					 * @param begin 区间的起始迭代器
					 * @param end 区间的终止迭代器
					 * @tparam InputIterator 输入迭代器
					 * @warning 若区间长度超出 Auto_array 所能存放的最大元素数目, 超过部分将自动截断
					 */
					template<typename InputIterator>
					Auto_array(InputIterator begin, InputIterator end);

					/**
					 * @brief 析构函数
					 */
					~Auto_array();

					Auto_array& assign(const Auto_array & src);

					/**
					 * @brief 以一段区间内的内容给数组赋值
					 * @param begin 区间的起始迭代器
					 * @param end 区间的终止迭代器
					 * @tparam InputIterator 输入迭代器
					 * @warning 若区间长度超出 Auto_array 所能存放的最大元素数目, 超过部分将自动截断
					 */
					template <typename InputIterator>
					Auto_array& assign(InputIterator begin, InputIterator end);

					Auto_array& operator=(const Auto_array & src);

					/**
					 * @brief 在数组末尾插入参数 src 指定的元素
					 * @param src
					 */
					void push_back(const type & src);

					/**
					 * @brief 移除数组末尾的元素
					 */
					void pop_back();

					/**
					 * @brief 在数组首部插入参数 src 指定的元素
					 */
					void push_front(const type & src);

					/**
					 * @brief 移除数组首部的元素
					 */
					void pop_front();

					reference front();
					const_reference front() const;

					reference back();
					const_reference back() const;

					reference operator[](size_t index);
					const_reference operator[](size_t index) const;

					/** @brief 返回指向数组首元素的迭代器 */
					iterator begin();
					/** @brief 返回指向数组末尾元素的后一个元素位置的迭代器 */
					iterator end();

					/**
					 * @brief 返回与该 Auto_array 所等价的 C 风格数组类型的引用, 方便与专门为 C 风格数组类型设计的 API 交互
					 * @return 与该 Auto_array 所等价的 C 风格数组类型的引用
					 * @warning 必须保证数组元素存满时才可调用此方法
					 * @throw std::exception 当数组未满就调用此方法时, 抛出此异常
					 */
					equal_c_array_reference c_arr();
					const_equal_c_array_reference const_c_arr() const;

					void clear();
					void fill();
					void fill(const type & val);

					/**
					 * @brief 测算数组是否为空
					 * @return 若为空, 返回 true, 否则返回 false
					 */
					bool empty() const;

					/**
					 * @brief 测算数组是否已满
					 * @return 若已满, 返回 true, 否则返回 false
					 */
					bool full() const;

					/**
					 * @brief 测算数组当前已存放的元素的个数
					 * @return 数组当前已存放的元素的个数
					 */
					size_t size() const;


					iterator find(const type & src);
					//const_iterator find(const type & src) const;

					//reverse_iterator rfind(const type & src);
					//const_reverse_iterator rfind(const type & src) const;

					template<typename JudgeFunction>
					iterator find_if(JudgeFunction judge_function);

			};
		}
	}
}

#include "auto_array_base.hpp"

#endif /* INCLUDE_KERBAL_DATA_STRUCT_AUTO_ARRAY_HPP_ */
