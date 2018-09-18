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
#include <stdexcept>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif

namespace kerbal
{
	/**
	 * @brief data structure
	 */
	namespace data_struct
	{
		/**
		 * @brief Array with flexible length that stored on automatic storage duration
		 * @details The class is an encapsulation class of array that could be stored on
		 *          automatic storage duration. It is more effective than std::vector because
		 *          std::vector store elements on heap storage duration (that's required memory
		 *          allocate and deallocate). Meanwhile the Auto_array has more flexibility
		 *          than std::array because std::array has fixed length and doesn't support
		 *          options like insert or erase. For further, std::array and c-style array
		 *          must call default constructor when it was declared. However, as we
		 *          all know, sometimes the default construct options are unnecessary.
		 * @tparam Tp Type of the elements.
		 * @tparam N The maximum number of elements that the array can hold.
		 */
		template <typename Tp, size_t N>
		class Auto_array
		{
			public:

				/// @brief Type of the elements.
				typedef Tp value_type;

				/// @brief Constant type of the elements.
				typedef const Tp const_type;

				/// @brief Reference of the elements.
				typedef Tp& reference;

				/// @brief Constant reference of the elements.
				typedef const Tp& const_reference;

				/// @brief Pointer type to the elements.
				typedef Tp* pointer;

				/// @brief Constant pointer type to the elements.
				typedef const Tp* const_pointer;

				/// @brief 与该 Auto_array 所等价的 C 风格数组的类型, 即 Tp[N]
				typedef value_type equal_c_array[N];
				typedef equal_c_array& equal_c_array_reference;
				typedef const value_type const_equal_c_array[N];
				typedef const_equal_c_array& const_equal_c_array_reference;

				/// @brief Iterator to Auto_array.
				typedef class iterator : public std::iterator<std::random_access_iterator_tag, Auto_array::value_type>
				{
					private:
						pointer current;

					public:
						explicit iterator(pointer current);

						operator typename Auto_array::const_iterator();

						reference operator*() const;
						pointer operator->() const;

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

				/// @brief Const_iterator to Auto_array.
				typedef class const_iterator : public std::iterator<std::random_access_iterator_tag, Auto_array::const_type>
				{
					private:
						const_pointer current;

					public:
						explicit const_iterator(const_pointer current);

						const_reference operator*() const;
						const_pointer operator->() const;

						//前自增
						const_iterator& operator++();
						//后自增
						const_iterator operator++(int);
						const_iterator& operator--();
						const_iterator operator--(int);

						const_iterator operator+(int delta);
						const_iterator operator-(int delta);

						const const_iterator operator+(int delta) const;
						const const_iterator operator-(int delta) const;

						bool operator==(const const_iterator & with) const;
						bool operator!=(const const_iterator & with) const;
						bool operator<(const const_iterator & with) const;
						bool operator<=(const const_iterator & with) const;
						bool operator>(const const_iterator & with) const;
						bool operator>=(const const_iterator & with) const;

				} const_iterator;

				/// @brief Reverse_iterator to Auto_array.
				typedef class reverse_iterator : public std::iterator<std::random_access_iterator_tag, Auto_array::value_type>
				{
					private:
						pointer current;

					public:
						explicit reverse_iterator(pointer current);

						operator typename Auto_array::const_reverse_iterator();

						reference operator*() const;
						pointer operator->() const;

						//前自增
						reverse_iterator& operator++();
						//后自增
						reverse_iterator operator++(int);
						reverse_iterator& operator--();
						reverse_iterator operator--(int);

						reverse_iterator operator+(int delta);
						reverse_iterator operator-(int delta);

						const reverse_iterator operator+(int delta) const;
						const reverse_iterator operator-(int delta) const;

						bool operator==(const reverse_iterator & with) const;
						bool operator!=(const reverse_iterator & with) const;
						bool operator<(const reverse_iterator & with) const;
						bool operator<=(const reverse_iterator & with) const;
						bool operator>(const reverse_iterator & with) const;
						bool operator>=(const reverse_iterator & with) const;

				} reverse_iterator;

				/// @brief Const_reverse_iterator to Auto_array.
				typedef class const_reverse_iterator : public std::iterator<std::random_access_iterator_tag, Auto_array::const_type>
				{
					private:
						const_pointer current;

					public:
						explicit const_reverse_iterator(const_pointer current);

						const_reference operator*() const;
						const_pointer operator->() const;

						//前自增
						const_reverse_iterator& operator++();
						//后自增
						const_reverse_iterator operator++(int);
						const_reverse_iterator& operator--();
						const_reverse_iterator operator--(int);

						const_reverse_iterator operator+(int delta);
						const_reverse_iterator operator-(int delta);

						const const_reverse_iterator operator+(int delta) const;
						const const_reverse_iterator operator-(int delta) const;

						bool operator==(const const_reverse_iterator & with) const;
						bool operator!=(const const_reverse_iterator & with) const;
						bool operator<(const const_reverse_iterator & with) const;
						bool operator<=(const const_reverse_iterator & with) const;
						bool operator>(const const_reverse_iterator & with) const;
						bool operator>=(const const_reverse_iterator & with) const;

				} const_reverse_iterator;

#if __cplusplus >= 201103L
				/** @brief The maximum number of elements that the array can hold. */
				static constexpr size_t max_size = N;
#else
				/** @brief The maximum number of elements that the array can hold. */
				static const size_t max_size;
#endif

			private:

				/**
				 * @note 使用一层匿名联合体包裹抑制调用构造函数
				 */
				union
				{
						/// data
						value_type p[N];
				};

				pointer p_to_end;

			public:
				/** @brief Empty container constructor (Default constructor) */
				Auto_array();

				/**
				 * @brief Copy constructor
				 * @param src Another Auto_array object of the same type (must have the same template arguments type and N)
				 */
				Auto_array(const Auto_array & src);

#			if __cplusplus >= 201103L

				/**
				 * @brief Construct the array by coping the contents in initializer list
				 * @param src An initializer list
				 * @warning Compile terminate if the length of the initializer list large than the arg N of the Auto_array
				 * @warning The constructor only be provided under the environment of C++11 standard
				 */
				Auto_array(std::initializer_list<value_type> src);
#			endif

				/**
				 * @brief Range constructor
				 * @param begin the iterator that points to the range begin
				 * @param end the iterator that points to the range end
				 * @tparam InputIterator An input iterator type that points to elements of a type
				 * @warning If the range contains elements more than N, only the first N elements
				 *          will be used. The others will be ignored.
				 */
				template<typename InputIterator>
				Auto_array(InputIterator begin, InputIterator end);

				/**
				 * @brief 析构函数
				 */
				~Auto_array();

				/**
				 * @brief Assign the array by using n value(s).
				 * @param n numbers of the value(s)
				 * @param val value
				 */
				void assign(size_t n, const value_type & val);

				/**
				 * @brief Assign the array by using a range of elements.
				 * @param begin the iterator that points to the range begin
				 * @param end the iterator that points to the range end
				 * @tparam InputIterator An input iterator type that points to elements of a type
				 * @warning 若区间长度超出 Auto_array 所能存放的最大元素数目, 超过部分将自动截断
				 */
				template <typename InputIterator>
				void assign(InputIterator begin, InputIterator end);

				Auto_array& operator=(const Auto_array & src);

#if __cplusplus >= 201103L
				/**
				 * @brief Assign the array by using the content of an initializer list
				 * @param src the initializer list
				 * @return the reference to the array be assigned
				 */
				Auto_array& operator=(std::initializer_list<value_type> src);
#endif

				/**
				 *
				 * @param src
				 */
				void insert(const_iterator pos, const_reference val);

				/**
				 * @brief 在数组末尾插入参数 src 指定的元素
				 * @param src
				 */
				void push_back(const value_type & src);

				/**
				 * @brief 移除数组末尾的元素
				 */
				void pop_back();

				/**
				 * @brief 在数组首部插入参数 src 指定的元素
				 */
				void push_front(const value_type & src);

				/**
				 * @brief 移除数组首部的元素
				 */
				void pop_front();

				/**
				 * @brief Get the reference of the element at the beginning of the array.
				 * @return the reference of the element at the beginning of the array
				 * @throw std::exception Throw this exception if the array is empty.
				 */
				reference front();

				/**
				 * @brief Get the const_reference of the element at the beginning of the array.
				 * @return the const_reference of the element at the beginning of the array
				 * @throw std::exception Throw this exception if the array is empty.
				 */
				const_reference front() const;

				/**
				 * @brief Get the reference of the element at the end of the array.
				 * @return the reference of the element at the end of the array
				 * @throw std::exception Throw this exception if the array is empty.
				 */
				reference back();

				/**
				 * @brief Get the const_reference of the element at the end of the array.
				 * @return the const_reference of the element at the end of the array
				 * @throw std::exception Throw this exception if the array is empty.
				 */
				const_reference back() const;

				reference operator[](size_t index);
				const_reference operator[](size_t index) const;

				/** @brief 返回指向数组首元素的迭代器 */
				iterator begin();
				/** @brief 返回指向数组末尾元素的后一个元素位置的迭代器 */
				iterator end();

				const_iterator begin() const;
				const_iterator end() const;

				const_iterator cbegin() const;
				const_iterator cend() const;

				reverse_iterator rbegin();
				reverse_iterator rend();

				const_reverse_iterator rbegin() const;
				const_reverse_iterator rend() const;

				const_reverse_iterator crbegin() const;
				const_reverse_iterator crend() const;

//				bool is_valid_iterator(const iterator & it) const;

				/**
				 * @brief 返回与该 Auto_array 所等价的 C 风格数组类型的引用, 方便与专门为 C 风格数组类型设计的 API 交互
				 * @return 与该 Auto_array 所等价的 C 风格数组类型的引用
				 * @warning 必须保证数组元素存满时才可调用此方法
				 * @throw std::exception Throw this exception when call this method while the array is not full
				 */
				equal_c_array_reference c_arr();
				const_equal_c_array_reference const_c_arr() const;

				const_pointer data() const;

				/**
				 * @brief Clear all the elements in the array.
				 */
				void clear();

				/**
				 * @brief Fill all the blank positions at the end of array by using default constructor of the element type.
				 */
				void fill();

				/**
				 * @brief Fill all the blank positions at the end of array by copying the argument val.
				 * @param val
				 */
				void fill(const value_type & val);

				/**
				 * @brief Swap the array with another one.
				 * @param with another array to be swaped with
				 */
				void swap(Auto_array & with);

				/**
				 * @brief Judege whether the array is empty.
				 * @return If the array is empty, return true, otherwise return false
				 */
				bool empty() const;

				/**
				 * @brief Judege whether the array has been full.
				 * @return If the array has been full, return true, otherwise return false
				 */
				bool full() const;

				/**
				 * @brief Count the number of the elements that the array has contained.
				 * @return the number of the elements that the array has contained
				 */
				size_t size() const;


				iterator find(const value_type & src);
				const_iterator find(const value_type & src) const;

				reverse_iterator rfind(const value_type & src);
				const_reverse_iterator rfind(const value_type & src) const;

				template<typename JudgeFunction>
				iterator find_if(JudgeFunction judge_function);

				template<typename JudgeFunction>
				const_iterator find_if(JudgeFunction judge_function) const;

				template<typename JudgeFunction>
				reverse_iterator rfind_if(JudgeFunction judge_function);

				template<typename JudgeFunction>
				const_reverse_iterator rfind_if(JudgeFunction judge_function) const;

				bool operator==(const Auto_array & with) const;
				bool operator!=(const Auto_array & with) const;
				bool operator<(const Auto_array & with) const;
				bool operator<=(const Auto_array & with) const;
				bool operator>(const Auto_array & with) const;
				bool operator>=(const Auto_array & with) const;
		};

	}
}

#include <kerbal/data_struct/auto_container_base/auto_array_base.hpp>
#include <kerbal/data_struct/auto_container_base/auto_array_iterator.hpp>

#endif /* INCLUDE_KERBAL_DATA_STRUCT_AUTO_ARRAY_HPP_ */
