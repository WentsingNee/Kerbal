/**
 * @file		static_vector.hpp
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
#include <kerbal/data_struct/static_container_base/static_container_exception.hpp>
#include <kerbal/algorithm/iterator.hpp>
#include <kerbal/type_traits/type_traits_details/enable_if.hpp>

#include <cstddef>
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
		template <bool enable_memecpy_optimization>
		struct __static_array_copy_details;

		template <bool enable_memecpy_optimization>
		struct __static_array_range_copy_details;

		template <bool enable_memecpy_optimization>
		struct __static_array_n_assign_details;

		template <bool enable_memecpy_optimization>
		struct __static_array_insert_details;

		template <bool enable_memecpy_optimization>
		struct __static_array_erase_details;

		/**
		 * @brief Array with flexible length that stored on automatic storage duration
		 * @details The class is an encapsulation class of array that could be stored on
		 *          automatic storage duration. It is more effective than std::vector
		 *          (especially when type parameter Tp is trivial type) because std::vector
		 *          store elements on heap storage duration (that's required memory allocation
		 *          and deallocation). Meanwhile the static_vector has more flexibility
		 *          than std::array for the reason that std::array has fixed length and
		 *          doesn't support operations like `insert` and `erase`. For further,
		 *          std::array and c-style array must call default constructor for initialization
		 *          when it was declared. However, as we all know, sometimes the default construct
		 *          operations are unnecessary.
		 * @tparam Tp Type of the elements.
		 * @tparam N The maximum number of elements that the array can hold.
		 */
		template <typename Tp, size_t N>
		class static_vector
		{
			public:

				/// @brief Type of the elements.
				typedef Tp value_type;

				/// @brief Constant type of the elements.
				typedef const value_type const_type;

				/// @brief Reference of the elements.
				typedef value_type& reference;

				/// @brief Constant reference of the elements.
				typedef const value_type& const_reference;

				/// @brief Pointer type to the elements.
				typedef value_type* pointer;

				/// @brief Constant pointer type to the elements.
				typedef const value_type* const_pointer;

#		if __cplusplus >= 201103L
				typedef value_type&& rvalue_reference;
				typedef const value_type&& const_rvalue_reference;
#		endif

				typedef std::size_t size_type;
				typedef std::ptrdiff_t difference_type;

				/// @brief 与该 static_vector 所等价的 C 风格数组的类型, 即 value_type[N]
				typedef value_type equal_c_array[N];
				typedef equal_c_array& equal_c_array_reference;
				typedef const value_type const_equal_c_array[N];
				typedef const_equal_c_array& const_equal_c_array_reference;

			private:

				typedef kerbal::data_struct::raw_storage<value_type> storage_type;

				/**
				 * @brief 数据存储区
				 */
				storage_type storage[N];

				const storage_type* p_to_end;

			public:
				class const_iterator;

				/// @brief Iterator to static_vector.
				typedef class iterator : public std::iterator<std::random_access_iterator_tag, static_vector::value_type>
				{
					private:
						storage_type* current;
						friend class static_vector;
						friend class static_vector::const_iterator;

					public:
						explicit iterator(storage_type* current) KERBAL_NOEXCEPT :
								current(current)
						{
						}

						static_vector::reference operator*() const;
						static_vector::pointer operator->() const;

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

				/// @brief Const iterator to static_vector.
				typedef class const_iterator : public std::iterator<std::random_access_iterator_tag, static_vector::const_type>
				{
					private:
						const storage_type* current;

						friend class static_vector;

					public:
						explicit const_iterator(const storage_type* current) KERBAL_NOEXCEPT :
								current(current)
						{
						}

						const_iterator(const iterator & current) KERBAL_NOEXCEPT :
								current(current.current)
						{
						}

						static_vector::const_reference operator*() const;
						static_vector::const_pointer operator->() const;

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

				/// @brief Constant reverse iterator to static_vector.
				typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

				/// @brief Reverse iterator to static_vector.
				typedef std::reverse_iterator<iterator> reverse_iterator;

			public:
				/** @brief Empty container constructor (Default constructor) */
				static_vector();

				friend struct __static_array_copy_details<false>;
				friend struct __static_array_copy_details<true>;

				/**
				 * @brief Copy constructor
				 * @param src Another static_vector object of the same type (must have the same template arguments type and N)
				 */
				static_vector(const static_vector & src);

#			if __cplusplus >= 201103L

				/**
				 * @brief Construct the array by coping the contents in initializer list
				 * @param src An initializer list
				 * @warning Compile terminate if the length of the initializer list large than the arg N of the static_vector
				 * @warning The constructor only be provided under the environment of C++11 standard
				 */
				static_vector(std::initializer_list<value_type> src);
#			endif

				friend struct __static_array_range_copy_details<false>;
				friend struct __static_array_range_copy_details<true>;

				static_vector(size_type n, const_reference val);

				/**
				 * @brief Range constructor
				 * @param begin the iterator that points to the range begin
				 * @param end the iterator that points to the range end
				 * @tparam InputIterator An input iterator type that points to elements of a type
				 * @warning If the range contains elements more than N, only the first N elements
				 *          will be used. The others will be ignored.
				 */
				template <typename InputCompatibleIterator>
				static_vector(InputCompatibleIterator first, InputCompatibleIterator last,
						typename kerbal::type_traits::enable_if<
								kerbal::type_traits::is_input_compatible_iterator<InputCompatibleIterator>::value
								, int
						>::type = 0
				);

				/**
				 * @brief 析构函数
				 */
				~static_vector();

				static_vector& operator=(const static_vector & src);

#	if __cplusplus >= 201103L
				/**
				 * @brief Assign the array by using the content of an initializer list
				 * @param src the initializer list
				 * @return the reference to the array be assigned
				 */
				static_vector& operator=(std::initializer_list<value_type> src);
#	endif

				friend struct __static_array_n_assign_details<false>;
				friend struct __static_array_n_assign_details<true>;

				/**
				 * @brief Assign the array by using n value(s).
				 * @param n numbers of the value(s)
				 * @param val value
				 */
				void assign(size_type n, const_reference val);

				/**
				 * @brief Assign the array by using a range of elements.
				 * @param begin the iterator that points to the range begin
				 * @param end the iterator that points to the range end
				 * @tparam InputIterator An input iterator type that points to elements of a type
				 * @warning 若区间长度超出 static_vector 所能存放的最大元素数目, 超过部分将自动截断
				 */
				template <typename InputCompatibleIterator>
				typename kerbal::type_traits::enable_if<
						kerbal::type_traits::is_input_compatible_iterator<InputCompatibleIterator>::value
				>::type
				assign(InputCompatibleIterator begin, InputCompatibleIterator end);

#if __cplusplus >= 201103L
				/**
				 * @brief Assign the array by using the content of an initializer list
				 * @param src the initializer list
				 */
				void assign(std::initializer_list<value_type> src);
#endif

				/** @brief 返回指向数组首元素的迭代器 */
				iterator begin() KERBAL_NOEXCEPT;

				/** @brief 返回指向数组末尾元素的后一个元素位置的迭代器 */
				iterator end() KERBAL_NOEXCEPT;

				const_iterator begin() const KERBAL_NOEXCEPT;

				/** @brief 返回指向数组末尾元素的后一个元素位置的迭代器 */
				const_iterator end() const KERBAL_NOEXCEPT;

				const_iterator cbegin() const KERBAL_NOEXCEPT;

				const_iterator cend() const KERBAL_NOEXCEPT;

				reverse_iterator rbegin() KERBAL_NOEXCEPT;
				reverse_iterator rend() KERBAL_NOEXCEPT;

				const_reverse_iterator rbegin() const KERBAL_NOEXCEPT;
				const_reverse_iterator rend() const KERBAL_NOEXCEPT;

				const_reverse_iterator crbegin() const KERBAL_NOEXCEPT;
				const_reverse_iterator crend() const KERBAL_NOEXCEPT;

				/**
				 * @brief Count the number of the elements that the array has contained.
				 * @return the number of the elements that the array has contained
				 */
				size_type size() const KERBAL_NOEXCEPT;

				/**
				 * @brief Returns the size() of the largest possible static_vector.
				 */
				KERBAL_CONSTEXPR size_type max_size() const KERBAL_NOEXCEPT
				{
					return N;
				}

				/**
				 * @brief Judge whether the array is empty.
				 * @return If the array is empty, return true, otherwise return false
				 */
				bool empty() const KERBAL_NOEXCEPT;

				void alert_empty() const
				{
					if (empty()) {
						throw kerbal::data_struct::static_container_empty_exception();
					}
				}

				/**
				 * @brief Judge whether the array has been full.
				 * @return If the array has been full, return true, otherwise return false
				 */
				bool full() const KERBAL_NOEXCEPT;

				void alert_full() const
				{
					if (full()) {
						throw kerbal::data_struct::static_container_full_exception(N);
					}
				}

				reference operator[](size_type index) KERBAL_NOEXCEPT;
				const_reference operator[](size_type index) const KERBAL_NOEXCEPT;

				reference at(size_type index);
				const_reference at(size_type index) const;

				/**
				 * @brief Get the reference of the element at the beginning of the array.
				 * @return the reference of the element at the beginning of the array.
				 */
				reference front();

				/**
				 * @brief Get the const_reference of the element at the beginning of the array.
				 * @return the const_reference of the element at the beginning of the array.
				 */
				const_reference front() const;

				/**
				 * @brief Get the reference of the element at the end of the array.
				 * @return the reference of the element at the end of the array.
				 */
				reference back();

				/**
				 * @brief Get the const_reference of the element at the end of the array.
				 * @return the const_reference of the element at the end of the array.
				 */
				const_reference back() const;

				/**
				 * @brief 返回与该 static_vector 所等价的 C 风格数组类型的引用, 方便与专门为 C 风格数组类型设计的 API 交互
				 * @return 与该 static_vector 所等价的 C 风格数组类型的引用
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

				template <typename ... Args>
				reference emplace_back(Args&& ...args);
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

				template <typename ... Args>
				reference emplace_front(Args&& ...args);

#			endif

				/**
				 * @brief 移除数组首部的元素
				 */
				void pop_front();


				friend struct __static_array_insert_details<false>;
				friend struct __static_array_insert_details<true>;

				iterator insert(const_iterator pos, const_reference val);

#			if __cplusplus >= 201103L
				iterator insert(const_iterator pos, rvalue_reference val);

				template <typename ... Args>
				iterator emplace(const_iterator pos, Args&& ...args);
#			endif

				friend struct __static_array_erase_details<false>;
				friend struct __static_array_erase_details<true>;

				iterator erase(const_iterator pos);

//				iterator erase(const_iterator begin, const_iterator end);

				/**
				 * @brief Swap the array with another one.
				 * @param with another array to be swaped with
				 */
				void swap(static_vector & with);

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

			private:

#	if __cplusplus < 201103L
				void __construct_at(size_type);

				template <typename T0>
				void __construct_at(size_type, const T0&);

				template <typename T0, typename T1>
				void __construct_at(size_type, const T0&, const T1&);

				template <typename T0, typename T1, typename T2>
				void __construct_at(size_type, const T0&, const T1&, const T2&);

				template <typename T0, typename T1, typename T2, typename T3>
				void __construct_at(size_type, const T0&, const T1&, const T2&, const T3&);

				template <typename T0, typename T1, typename T2, typename T3, typename T4>
				void __construct_at(size_type, const T0&, const T1&, const T2&, const T3&, const T4&);

				void __construct_at(iterator);

				template <typename T0>
				void __construct_at(iterator, const T0&);

				template <typename T0, typename T1>
				void __construct_at(iterator, const T0&, const T1&);

				template <typename T0, typename T1, typename T2>
				void __construct_at(iterator, const T0&, const T1&, const T2&);

				template <typename T0, typename T1, typename T2, typename T3>
				void __construct_at(iterator, const T0&, const T1&, const T2&, const T3&);

				template <typename T0, typename T1, typename T2, typename T3, typename T4>
				void __construct_at(iterator, const T0&, const T1&, const T2&, const T3&, const T4&);


#	else
				template <typename ... Args>
				void __construct_at(size_type, Args&& ...);

				template <typename ... Args>
				void __construct_at(iterator, Args&& ...);
#	endif

				void __destroy_at(size_type);

				void __destroy_at(iterator);


		};

		template <typename Tp, size_t M, size_t N>
		bool operator==(const static_vector<Tp, M> & lhs, const static_vector<Tp, N> & rhs)
		{
			if (lhs.size() != rhs.size()) {
				return false;
			}
			typename static_vector<Tp, M>::const_iterator i = lhs.cbegin();
			typename static_vector<Tp, M>::const_iterator const i_end = lhs.cend();
			typename static_vector<Tp, N>::const_iterator j = rhs.cbegin();
			while (i != i_end) { // size are equal and j will not out of range
				if (*i == *j) {
					++i;
					++j;
				} else {
					return false;
				}
			}
			return true;
		}

		template <typename Tp, size_t M, size_t N>
		bool operator!=(const static_vector<Tp, M> & lhs, const static_vector<Tp, N> & rhs)
		{
			if (lhs.size() != rhs.size()) {
				return true;
			}
			typename static_vector<Tp, M>::const_iterator i = lhs.cbegin();
			typename static_vector<Tp, M>::const_iterator const i_end = lhs.cend();
			typename static_vector<Tp, N>::const_iterator j = rhs.cbegin();
			while (i != i_end) {
				if (*i != *j) {
					return true;
				} else {
					++i;
					++j;
				}
			}
			return false;
		}

		template <typename Tp, size_t M, size_t N>
		bool operator<(const static_vector<Tp, M> & lhs, const static_vector<Tp, N> & rhs)
		{
			return std::lexicographical_compare(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, size_t M, size_t N>
		bool operator<=(const static_vector<Tp, M> & lhs, const static_vector<Tp, N> & rhs);

		template <typename Tp, size_t M, size_t N>
		bool operator>(const static_vector<Tp, M> & lhs, const static_vector<Tp, N> & rhs);

		template <typename Tp, size_t M, size_t N>
		bool operator>=(const static_vector<Tp, M> & lhs, const static_vector<Tp, N> & rhs);

	}
}

#include <kerbal/data_struct/static_container_base/static_vector_base.hpp>
#include <kerbal/data_struct/static_container_base/static_vector_iterator.hpp>

#endif /* INCLUDE_KERBAL_DATA_STRUCT_STATIC_ARRAY_HPP_ */
