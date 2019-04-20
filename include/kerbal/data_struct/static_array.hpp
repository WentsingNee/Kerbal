/**
 * @file		static_array.hpp
 * @brief
 * @date		2018年4月28日
 * @author		Peter
 * @copyright	Peter
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 */

#ifndef INCLUDE_KERBAL_DATA_STRUCT_STATIC_ARRAY_HPP_
#define INCLUDE_KERBAL_DATA_STRUCT_STATIC_ARRAY_HPP_

#include <kerbal/data_struct/raw_storage.hpp>
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
		 *          automatic storage duration. It is more effective than std::vector
		 *          (especially when type parameter Tp is trivial type) because std::vector
		 *          store elements on heap storage duration (that's required memory allocation
		 *          and deallocation). Meanwhile the static_array has more flexibility
		 *          than std::array for the reason that std::array has fixed length and
		 *          doesn't support operations like `insert` and `erase`. For further,
		 *          std::array and c-style array must call default constructor for initialization
		 *          when it was declared. However, as we all know, sometimes the default construct
		 *          operations are unnecessary.
		 * @tparam Tp Type of the elements.
		 * @tparam N The maximum number of elements that the array can hold.
		 */
		template <typename Tp, size_t N>
		class static_array
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

#		if __cplusplus >= 201103L
				typedef value_type&& rvalue_reference;
				typedef const value_type&& const_rvalue_reference;
#		endif

				typedef std::size_t size_type;
				typedef std::ptrdiff_t difference_type;

				/// @brief 与该 Auto_array 所等价的 C 风格数组的类型, 即 Tp[N]
				typedef value_type equal_c_array[N];
				typedef equal_c_array& equal_c_array_reference;
				typedef const value_type const_equal_c_array[N];
				typedef const_equal_c_array& const_equal_c_array_reference;

				/// @brief Iterator to static_array.
				typedef class iterator : public std::iterator<std::random_access_iterator_tag, static_array::value_type>
				{
					private:
						pointer current;

					public:
						explicit iterator(pointer current);

						reference operator*() const;
						pointer operator->() const;

						/// @brief 前自增
						iterator& operator++();
						/// @brief 后自增
						iterator operator++(int);
						/// @brief 前自减
						iterator& operator--();
						/// @brief 后自减
						iterator operator--(int);

						iterator operator+(const typename iterator::difference_type & delta) const;
						iterator operator-(const typename iterator::difference_type & delta) const;

						typename iterator::difference_type operator-(const iterator & with) const;

						iterator& operator+=(const typename iterator::difference_type & delta);
						iterator& operator-=(const typename iterator::difference_type & delta);

						bool operator==(const iterator & with) const;
						bool operator!=(const iterator & with) const;
						bool operator<(const iterator & with) const;
						bool operator<=(const iterator & with) const;
						bool operator>(const iterator & with) const;
						bool operator>=(const iterator & with) const;

				} iterator;

				/// @brief Const_iterator to static_array.
				typedef class const_iterator : public std::iterator<std::random_access_iterator_tag, static_array::const_type>
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

						const_iterator operator+(const typename const_iterator::difference_type & delta) const;
						const_iterator operator-(const typename const_iterator::difference_type & delta) const;

						typename const_iterator::difference_type operator-(const const_iterator & with) const;

						const_iterator& operator+=(const typename const_iterator::difference_type & delta);
						const_iterator& operator-=(const typename const_iterator::difference_type & delta);

						bool operator==(const const_iterator & with) const;
						bool operator!=(const const_iterator & with) const;
						bool operator<(const const_iterator & with) const;
						bool operator<=(const const_iterator & with) const;
						bool operator>(const const_iterator & with) const;
						bool operator>=(const const_iterator & with) const;

				} const_iterator;

				/// @brief Reverse_iterator to static_array.
				typedef class reverse_iterator : public std::iterator<std::random_access_iterator_tag, static_array::value_type>
				{
					private:
						pointer current;

					public:
						explicit reverse_iterator(pointer current);

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

				/// @brief Const_reverse_iterator to static_array.
				typedef class const_reverse_iterator : public std::iterator<std::random_access_iterator_tag, static_array::const_type>
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

			private:

				typedef kerbal::data_struct::raw_storage<Tp[N]> storage_type;

				/**
				 * @brief 数据存储区
				 */
				storage_type storage;

				typename storage_type::element::const_pointer p_to_end;

			public:
				/** @brief Empty container constructor (Default constructor) */
				static_array();

				/**
				 * @brief Copy constructor
				 * @param src Another Auto_array object of the same type (must have the same template arguments type and N)
				 */
				static_array(const static_array & src);

#			if __cplusplus >= 201103L

				/**
				 * @brief Construct the array by coping the contents in initializer list
				 * @param src An initializer list
				 * @warning Compile terminate if the length of the initializer list large than the arg N of the Auto_array
				 * @warning The constructor only be provided under the environment of C++11 standard
				 */
				static_array(std::initializer_list<value_type> src);
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
				static_array(InputIterator begin, InputIterator end);

				/**
				 * @brief 析构函数
				 */
				~static_array();

				static_array& operator=(const static_array & src);

#if __cplusplus >= 201103L
				/**
				 * @brief Assign the array by using the content of an initializer list
				 * @param src the initializer list
				 * @return the reference to the array be assigned
				 */
				static_array& operator=(std::initializer_list<value_type> src);
#endif

				/**
				 * @brief Assign the array by using n value(s).
				 * @param n numbers of the value(s)
				 * @param val value
				 */
				void assign(size_type n, const value_type & val);

				/**
				 * @brief Assign the array by using a range of elements.
				 * @param begin the iterator that points to the range begin
				 * @param end the iterator that points to the range end
				 * @tparam InputIterator An input iterator type that points to elements of a type
				 * @warning 若区间长度超出 Auto_array 所能存放的最大元素数目, 超过部分将自动截断
				 */
				template <typename InputIterator>
				void assign(InputIterator begin, InputIterator end);

#if __cplusplus >= 201103L
				/**
				 * @brief Assign the array by using the content of an initializer list
				 * @param src the initializer list
				 */
				void assign(std::initializer_list<value_type> src);
#endif

				/** @brief 返回指向数组首元素的迭代器 */
				iterator begin();

				const_iterator begin() const;

				/** @brief 返回指向数组末尾元素的后一个元素位置的迭代器 */
				const_iterator end() const;

				const_iterator cbegin() const;
				const_iterator cend() const;

				reverse_iterator rbegin();
				const_reverse_iterator rbegin() const;
				const_reverse_iterator rend() const;

				const_reverse_iterator crbegin() const;
				const_reverse_iterator crend() const;

				/**
				 * @brief Count the number of the elements that the array has contained.
				 * @return the number of the elements that the array has contained
				 */
				size_type size() const;

				/**
				 * @brief Returns the size() of the largest possible static_array.
				 */
				KERBAL_CONSTEXPR size_type max_size() const KERBAL_NOEXCEPT
				{
					return N;
				}

				/**
				 * @brief Judge whether the array is empty.
				 * @return If the array is empty, return true, otherwise return false
				 */
				bool empty() const;

				/**
				 * @brief Judge whether the array has been full.
				 * @return If the array has been full, return true, otherwise return false
				 */
				bool full() const;

				reference operator[](size_type index);
				const_reference operator[](size_type index) const;

				reference at(size_type index);
				const_reference at(size_type index) const;

				/**
				 * @brief Get the reference of the element at the beginning of the array.
				 * @return the reference of the element at the beginning of the array
				 * @throw std::out_of_range Throw this exception if the array is empty.
				 */
				reference front();

				/**
				 * @brief Get the const_reference of the element at the beginning of the array.
				 * @return the const_reference of the element at the beginning of the array
				 * @throw std::out_of_range Throw this exception if the array is empty.
				 */
				const_reference front() const;

				/**
				 * @brief Get the reference of the element at the end of the array.
				 * @return the reference of the element at the end of the array
				 * @throw std::out_of_range Throw this exception if the array is empty.
				 */
				reference back();

				/**
				 * @brief Get the const_reference of the element at the end of the array.
				 * @return the const_reference of the element at the end of the array
				 * @throw std::out_of_range Throw this exception if the array is empty.
				 */
				const_reference back() const;

				/**
				 * @brief 返回与该 Auto_array 所等价的 C 风格数组类型的引用, 方便与专门为 C 风格数组类型设计的 API 交互
				 * @return 与该 Auto_array 所等价的 C 风格数组类型的引用
				 * @warning 必须保证数组元素存满时才可调用此方法
				 * @throw std::exception Throw this exception when call this method while the array is not full
				 */
				equal_c_array_reference c_arr();
				const_equal_c_array_reference c_arr() const;
				const_equal_c_array_reference const_c_arr() const;

				const_pointer data() const;

				/**
				 * @brief 在数组末尾插入参数 src 指定的元素
				 * @param src
				 */
				void push_back(const_reference src);

#			if __cplusplus >= 201103L
				/**
				 * @brief 在数组末尾插入参数 src 指定的元素
				 * @param src
				 */
				void push_back(rvalue_reference src);
#			endif

				/**
				 * @brief 移除数组末尾的元素
				 */
				void pop_back();

				/**
				 * @brief 在数组首部插入参数 src 指定的元素
				 * @param src
				 */
				void push_front(const_reference src);

#			if __cplusplus >= 201103L
				/**
				 * @brief 在数组首部插入参数 src 指定的元素
				 * @param src
				 */
				void push_front(rvalue_reference src);
#			endif

				/**
				 * @brief 移除数组首部的元素
				 */
				void pop_front();

				void insert(const_iterator pos, const_reference val);

#			if __cplusplus >= 201103L
				void insert(const_iterator pos, rvalue_reference val);
#			endif

				void erase(const_iterator pos);

				void erase(const_iterator begin, const_iterator end);

				/**
				 * @brief Swap the array with another one.
				 * @param with another array to be swaped with
				 */
				void swap(static_array & with);

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
				void fill(const_reference val);

				bool operator==(const static_array & rhs) const;
				bool operator!=(const static_array & rhs) const;
				bool operator<(const static_array & rhs) const;
				bool operator<=(const static_array & rhs) const;
				bool operator>(const static_array & rhs) const;
				bool operator>=(const static_array & rhs) const;
		};

	}
}

#include <kerbal/data_struct/static_container_base/static_array_base.hpp>
#include <kerbal/data_struct/static_container_base/static_array_iterator.hpp>

#endif /* INCLUDE_KERBAL_DATA_STRUCT_STATIC_ARRAY_HPP_ */
