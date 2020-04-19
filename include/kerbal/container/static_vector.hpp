/**
 * @file       static_vector.hpp
 * @brief
 * @date       2018-4-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_STATIC_VECTOR_HPP
#define KERBAL_CONTAINER_STATIC_VECTOR_HPP

#include <kerbal/algorithm/sequence_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/static_container_exception.hpp>
#include <kerbal/data_struct/raw_storage.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/type_traits/array_traits.hpp>
#include <kerbal/type_traits/enable_if.hpp>

#include <cstddef>
#include <stdexcept>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif

#include <kerbal/container/impl/static_vector_iterator.impl.hpp>

namespace kerbal
{

	namespace container
	{
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
				typedef Tp							value_type;
				typedef const value_type			const_type;
				typedef value_type&					reference;
				typedef const value_type&			const_reference;
				typedef value_type*					pointer;
				typedef const value_type*			const_pointer;

#		if __cplusplus >= 201103L
				typedef value_type&&				rvalue_reference;
				typedef const value_type&&			const_rvalue_reference;
#		endif

				typedef std::size_t					size_type;
				typedef std::ptrdiff_t				difference_type;

				/// @brief 与该 static_vector 所等价的 C 风格数组的类型, 即 value_type[N]
				typedef value_type equal_c_array[N];
				typedef equal_c_array& equal_c_array_reference;
				typedef const equal_c_array& equal_const_c_array_reference;
				typedef const value_type const_equal_c_array[N];
				typedef const_equal_c_array& const_equal_c_array_reference;

			private:
				typedef typename kerbal::type_traits::remove_all_extents<value_type>::type remove_all_extents_t;

				typedef kerbal::data_struct::raw_storage<value_type> storage_type;

				/**
				 * @brief 数据存储区
				 */
				storage_type storage[N];

				const storage_type* p_to_end;

			public:

				/// @brief Iterator to static_vector.
				typedef detail::__stavec_iter<value_type> iterator;
				/// @brief Constant iterator to static_vector.
				typedef detail::__stavec_kiter<value_type> const_iterator;
				/// @brief Reverse iterator to static_vector.
				typedef std::reverse_iterator<iterator> reverse_iterator;
				/// @brief Constant reverse iterator to static_vector.
				typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

			public:
				/** @brief Empty container constructor (Default constructor) */
				static_vector() KERBAL_NOEXCEPT;

			private:
				void __copy_constructor(const static_vector & src, kerbal::type_traits::false_type);
				void __copy_constructor(const static_vector & src, kerbal::type_traits::true_type) KERBAL_NOEXCEPT;

			public:
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

			private:
				void __move_constructor(static_vector && src, kerbal::type_traits::false_type);
				void __move_constructor(static_vector && src, kerbal::type_traits::true_type) noexcept;

			public:
				static_vector(static_vector && src);

#			endif

				explicit static_vector(size_type n);

				static_vector(size_type n, const_reference val);

			private:

				template <typename InputIterator>
				void __range_copy_constructor(InputIterator first, InputIterator last, std::input_iterator_tag, kerbal::type_traits::false_type);

				template <typename InputIterator>
				void __range_copy_constructor(InputIterator first, InputIterator last, std::input_iterator_tag, kerbal::type_traits::true_type) KERBAL_NOEXCEPT;

				template <typename RandomAccessIterator>
				void __range_copy_constructor(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag, kerbal::type_traits::false_type);

				template <typename RandomAccessIterator>
				void __range_copy_constructor(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag, kerbal::type_traits::true_type) KERBAL_NOEXCEPT;

			public:

				/**
				 * @brief Range constructor
				 * @param begin the iterator that points to the range begin
				 * @param end the iterator that points to the range end
				 * @tparam InputIterator An input iterator type that points to elements of a type
				 * @warning If the range contains elements more than N, only the first N elements
				 *          will be used. The others will be ignored.
				 */
				template <typename InputIterator>
				static_vector(InputIterator first, InputIterator last,
						typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
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

			private:

				void __assign(size_type new_size, const_reference val, kerbal::type_traits::false_type enable_mem_optimization);
				void __assign(size_type new_size, const_reference val, kerbal::type_traits::true_type enable_mem_optimization);

			public:

				/**
				 * @brief Assign the array by using n value(s).
				 * @param new_size numbers of the value(s)
				 * @param val value
				 */
				void assign(size_type new_size, const_reference val);

				/**
				 * @brief Assign the array by using a range of elements.
				 * @param begin the iterator that points to the range begin
				 * @param end the iterator that points to the range end
				 * @tparam InputIterator An input iterator type that points to elements of a type
				 * @warning 若区间长度超出 static_vector 所能存放的最大元素数目, 超过部分将自动截断
				 */
				template <typename InputIterator>
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
				>::type
				assign(InputIterator begin, InputIterator end);

#if __cplusplus >= 201103L
				/**
				 * @brief Assign the array by using the content of an initializer list
				 * @param src the initializer list
				 */
				void assign(std::initializer_list<value_type> src);
#endif

				/** @brief 返回指向数组首元素的迭代器 */
				KERBAL_CONSTEXPR14 iterator begin() KERBAL_NOEXCEPT;

				/** @brief 返回指向数组末尾元素的后一个元素位置的迭代器 */
				KERBAL_CONSTEXPR14 iterator end() KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14 const_iterator begin() const KERBAL_NOEXCEPT;

				/** @brief 返回指向数组末尾元素的后一个元素位置的迭代器 */
				KERBAL_CONSTEXPR14 const_iterator end() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14 const_iterator cbegin() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14 const_iterator cend() const KERBAL_NOEXCEPT;

				reverse_iterator rbegin() KERBAL_NOEXCEPT;
				reverse_iterator rend() KERBAL_NOEXCEPT;

				const_reverse_iterator rbegin() const KERBAL_NOEXCEPT;
				const_reverse_iterator rend() const KERBAL_NOEXCEPT;

				const_reverse_iterator crbegin() const KERBAL_NOEXCEPT;
				const_reverse_iterator crend() const KERBAL_NOEXCEPT;

				iterator nth(size_type index)
				{
					return this->begin() + index;
				}

				const_iterator nth(size_type index) const
				{
					return this->cbegin() + index;
				}

				size_type index_of(iterator it)
				{
					return it - this->begin();
				}

				size_type index_of(const_iterator it) const
				{
					return it - this->cbegin();
				}

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
						kerbal::container::static_container_empty_exception::throw_this_exception();
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
						kerbal::container::static_container_full_exception::throw_this_exception(N);
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

#			endif

#			if __cplusplus >= 201103L

				template <typename ... Args>
				reference emplace_back(Args&& ...args);

#			else

				reference emplace_back();

				template <typename Arg0>
				reference emplace_back(const Arg0& arg0);

				template <typename Arg0, typename Arg1>
				reference emplace_back(const Arg0& arg0, const Arg1& arg1);

				template <typename Arg0, typename Arg1, typename Arg2>
				reference emplace_back(const Arg0& arg0, const Arg1& arg1, const Arg2& arg2);

#			endif

				/**
				 * @brief 移除数组末尾的元素
				 */
				void pop_back();

			private:
				void __shrink_back_to(const_iterator to, kerbal::type_traits::false_type);

				void __shrink_back_to(const_iterator to, kerbal::type_traits::true_type) KERBAL_NOEXCEPT;

			public:
				void shrink_back_to(const_iterator to);

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

				iterator insert(const_iterator pos, const_reference val);

#			if __cplusplus >= 201103L

				iterator insert(const_iterator pos, rvalue_reference val);

				template <typename ... Args>
				iterator emplace(const_iterator pos, Args&& ...args);

#			endif

				iterator erase(const_iterator pos);

				iterator erase(const_iterator begin, const_iterator end);

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
				void __construct_at(iterator, Args&& ...);
#	endif

				void __destroy_at(iterator);


		};

		template <typename Tp, size_t M, size_t N>
		bool operator==(const static_vector<Tp, M> & lhs, const static_vector<Tp, N> & rhs)
		{
			return kerbal::algorithm::sequence_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, size_t M, size_t N>
		bool operator!=(const static_vector<Tp, M> & lhs, const static_vector<Tp, N> & rhs)
		{
			return kerbal::algorithm::sequence_not_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, size_t M, size_t N>
		bool operator<(const static_vector<Tp, M> & lhs, const static_vector<Tp, N> & rhs)
		{
			return kerbal::algorithm::sequence_less(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, size_t M, size_t N>
		bool operator<=(const static_vector<Tp, M> & lhs, const static_vector<Tp, N> & rhs)
		{
			return kerbal::algorithm::sequence_less_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, size_t M, size_t N>
		bool operator>(const static_vector<Tp, M> & lhs, const static_vector<Tp, N> & rhs)
		{
			return kerbal::algorithm::sequence_greater(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, size_t M, size_t N>
		bool operator>=(const static_vector<Tp, M> & lhs, const static_vector<Tp, N> & rhs)
		{
			return kerbal::algorithm::sequence_greater_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

	}
}

#include <kerbal/container/impl/static_vector.impl.hpp>

#endif // KERBAL_CONTAINER_STATIC_VECTOR_HPP
