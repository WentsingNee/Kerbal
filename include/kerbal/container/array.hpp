/**
 * @file       array.hpp
 * @brief
 * @date       2019-10-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_ARRAY_HPP_
#define KERBAL_CONTAINER_ARRAY_HPP_

#include <kerbal/algorithm/sequence_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/operators/dereferenceable.hpp>
#include <kerbal/operators/equality_comparable.hpp>
#include <kerbal/operators/incr_decr.hpp>
#include <kerbal/operators/less_than_comparable.hpp>
#include <kerbal/type_traits/type_traits_details/array_traits.hpp>
#include <kerbal/type_traits/type_traits_details/enable_if.hpp>

#include <cstddef>
#include <stdexcept>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif

namespace kerbal
{

	namespace container
	{

		template <typename Tp, size_t N>
		class array;

		namespace detail
		{

			template <typename Pointer>
			struct __arr_iterbase_traits
			{
				private:
					typedef kerbal::iterator::iterator_traits<Pointer>		__traits_type;

				public:
					typedef typename __traits_type::iterator_category		iterator_category;
					typedef typename __traits_type::value_type				value_type;
					typedef typename __traits_type::difference_type			difference_type;
					typedef typename __traits_type::pointer					pointer;
					typedef typename __traits_type::reference				reference;

					typedef std::iterator<
							std::random_access_iterator_tag,
							value_type,
							difference_type,
							pointer,
							reference
					> type;
			};

			template <typename DerivedIterator, typename Pointer>
			class __arr_iterbase:
					public __arr_iterbase_traits<Pointer>::type,
					public kerbal::operators::dereferenceable<DerivedIterator, Pointer>,
					public kerbal::operators::equality_comparable<DerivedIterator>,
					public kerbal::operators::less_than_comparable<DerivedIterator>,
					public kerbal::operators::incrementable<DerivedIterator>,
					public kerbal::operators::decrementable<DerivedIterator>
			{
				private:
					typedef typename __arr_iterbase_traits<Pointer>::type iterator_base_t;

					Pointer current;

				public:
					explicit KERBAL_CONSTEXPR __arr_iterbase(Pointer current) KERBAL_NOEXCEPT :
							current(current)
					{
					}

					KERBAL_CONSTEXPR
					typename iterator_base_t::reference operator*() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14 DerivedIterator& operator++() KERBAL_NOEXCEPT;
					KERBAL_CONSTEXPR14 DerivedIterator& operator--() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR DerivedIterator operator+(const typename __arr_iterbase::difference_type & delta) const KERBAL_NOEXCEPT;
					KERBAL_CONSTEXPR DerivedIterator operator-(const typename __arr_iterbase::difference_type & delta) const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR
					typename __arr_iterbase::difference_type operator-(const DerivedIterator & with) const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14 DerivedIterator& operator+=(const typename __arr_iterbase::difference_type & delta) KERBAL_NOEXCEPT;
					KERBAL_CONSTEXPR14 DerivedIterator& operator-=(const typename __arr_iterbase::difference_type & delta) KERBAL_NOEXCEPT;

					friend KERBAL_CONSTEXPR
					bool operator<(const DerivedIterator & lhs, const DerivedIterator & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current < rhs.current;
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const DerivedIterator & lhs, const DerivedIterator & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current == rhs.current;
					}
			};

			template <typename ValueType>
			class __arr_kiter;

			/// @brief Iterator to array.
			template <typename ValueType>
			class __arr_iter: public __arr_iterbase<__arr_iter<ValueType>, ValueType*>
			{
				private:
					template <typename Tp, size_t N>
					friend class kerbal::container::array;

					friend class __arr_kiter<ValueType>;

					typedef __arr_iterbase<__arr_iter<ValueType>, ValueType*> super;

				public:
					explicit KERBAL_CONSTEXPR __arr_iter(ValueType* current) KERBAL_NOEXCEPT :
							super(current)
					{
					}
			};

			/// @brief Iterator to array.
			template <typename ValueType>
			class __arr_kiter: public __arr_iterbase<__arr_kiter<ValueType>, const ValueType*>
			{
				private:
					template <typename Tp, size_t N>
					friend class kerbal::container::array;

					typedef __arr_iterbase<__arr_kiter<ValueType>, const ValueType*> super;
					typedef __arr_iter<ValueType> iterator;

				public:
					explicit KERBAL_CONSTEXPR __arr_kiter(const ValueType* current) KERBAL_NOEXCEPT :
							super(current)
					{
					}

					KERBAL_CONSTEXPR __arr_kiter(const iterator & current) KERBAL_NOEXCEPT :
							super(current.current)
					{
					}
			};

		} //namespace detail

		template <typename Tp, size_t N>
		class array
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

				/// @brief 与该 array 所等价的 C 风格数组的类型, 即 value_type[N]
				typedef value_type equal_c_array[N];
				typedef equal_c_array& equal_c_array_reference;
				typedef const value_type const_equal_c_array[N];
				typedef const_equal_c_array& const_equal_c_array_reference;

			private:
				typedef typename kerbal::type_traits::remove_all_extents<value_type>::type remove_all_extents_t;

				/**
				 * @brief 数据存储区
				 */
				value_type storage[N];

			public:

				/// @brief Iterator to array.
				typedef kerbal::container::detail::__arr_iter<value_type> iterator;
				/// @brief Constant iterator to array.
				typedef kerbal::container::detail::__arr_kiter<value_type> const_iterator;
				/// @brief Reverse iterator to array.
				typedef std::reverse_iterator<iterator> reverse_iterator;
				/// @brief Constant reverse iterator to array.
				typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

			public:
				/** @brief Initialize the array with default value (Default constructor) */
#			if __cplusplus >= 201103L
				KERBAL_CONSTEXPR array() = default;
#			else
				array();
#			endif

				/**
				 * @brief Copy constructor
				 * @param src Another array object of the same type (must have the same template arguments type and N)
				 */
#			if __cplusplus >= 201103L
				KERBAL_CONSTEXPR array(const array & src) = default;
#			else
				array(const array & src);
#			endif

#			if __cplusplus >= 201103L

				/**
				 * @brief Construct the array by coping the contents in initializer list
				 * @param src An initializer list
				 * @warning Compile terminate if the length of the initializer list large than the arg N of the array
				 * @warning The constructor only be provided under the environment of C++11 standard
				 */
				KERBAL_CONSTEXPR14 array(std::initializer_list<value_type> src);

				KERBAL_CONSTEXPR array(array && src) = default;

#			endif

				KERBAL_CONSTEXPR14 array(size_type n, const_reference val);

				/**
				 * @brief Range constructor
				 * @param begin the iterator that points to the range begin
				 * @param end the iterator that points to the range end
				 * @tparam InputIterator An input iterator type that points to elements of a type
				 * @warning If the range contains elements more than N, only the first N elements
				 *          will be used. The others will be ignored.
				 */
				template <typename InputIterator>
				KERBAL_CONSTEXPR14
				array(InputIterator first, InputIterator last,
						typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
								, int
						>::type = 0
				);

#			if __cplusplus >= 201103L
				KERBAL_CONSTEXPR array& operator=(const array & src) = default;
#			else
				array& operator=(const array & src);
#			endif

#	if __cplusplus >= 201103L

				/**
				 * @brief Assign the array by using the content of an initializer list
				 * @param src the initializer list
				 * @return the reference to the array be assigned
				 */
				KERBAL_CONSTEXPR14
				array& operator=(std::initializer_list<value_type> src);

				KERBAL_CONSTEXPR array& operator=(array && src) = default;

#	endif

				/**
				 * @brief Assign the array by using n value(s).
				 * @param new_size numbers of the value(s)
				 * @param val value
				 */
				KERBAL_CONSTEXPR14
				void assign(size_type new_size, const_reference val);

				/**
				 * @brief Assign the array by using a range of elements.
				 * @param begin the iterator that points to the range begin
				 * @param end the iterator that points to the range end
				 * @tparam InputIterator An input iterator type that points to elements of a type
				 * @warning 若区间长度超出 array 所能存放的最大元素数目, 超过部分将自动截断
				 */
				template <typename InputIterator>
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
				>::type
				KERBAL_CONSTEXPR14
				assign(InputIterator first, InputIterator last);

#if __cplusplus >= 201103L
				/**
				 * @brief Assign the array by using the content of an initializer list
				 * @param src the initializer list
				 */
				KERBAL_CONSTEXPR14
				void assign(std::initializer_list<value_type> src);
#endif

				/** @brief 返回指向数组首元素的迭代器 */
				KERBAL_CONSTEXPR14 iterator begin() KERBAL_NOEXCEPT;

				/** @brief 返回指向数组末尾元素的后一个元素位置的迭代器 */
				KERBAL_CONSTEXPR14 iterator end() KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14 const_iterator begin() const KERBAL_NOEXCEPT;

				/** @brief 返回指向数组末尾元素的后一个元素位置的迭代器 */
				KERBAL_CONSTEXPR14 const_iterator end() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR const_iterator cbegin() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR const_iterator cend() const KERBAL_NOEXCEPT;

				reverse_iterator rbegin() KERBAL_NOEXCEPT;
				reverse_iterator rend() KERBAL_NOEXCEPT;

				const_reverse_iterator rbegin() const KERBAL_NOEXCEPT;
				const_reverse_iterator rend() const KERBAL_NOEXCEPT;

				const_reverse_iterator crbegin() const KERBAL_NOEXCEPT;
				const_reverse_iterator crend() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14 iterator nth(size_type index) KERBAL_NOEXCEPT;
				KERBAL_CONSTEXPR14 const_iterator nth(size_type index) const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14 size_type index_of(iterator it) KERBAL_NOEXCEPT;
				KERBAL_CONSTEXPR size_type index_of(const_iterator it) const KERBAL_NOEXCEPT;

				/**
				 * @brief Count the number of the elements that the array has contained.
				 * @return the number of the elements that the array has contained
				 */
				KERBAL_CONSTEXPR size_type size() const KERBAL_NOEXCEPT;

				/**
				 * @brief Returns the size() of the largest possible array.
				 */
				KERBAL_CONSTEXPR size_type max_size() const KERBAL_NOEXCEPT
				{
					return N;
				}

				/**
				 * @brief Judge whether the array is empty.
				 * @return If the array is empty, return true, otherwise return false
				 */
				KERBAL_CONSTEXPR bool empty() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14 reference operator[](size_type index) KERBAL_NOEXCEPT;
				KERBAL_CONSTEXPR14 const_reference operator[](size_type index) const KERBAL_NOEXCEPT;

				reference at(size_type index);
				const_reference at(size_type index) const;

				/**
				 * @brief Get the reference of the element at the beginning of the array.
				 * @return the reference of the element at the beginning of the array.
				 */
				KERBAL_CONSTEXPR14 reference front();

				/**
				 * @brief Get the const_reference of the element at the beginning of the array.
				 * @return the const_reference of the element at the beginning of the array.
				 */
				KERBAL_CONSTEXPR14 const_reference front() const;

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
				 * @brief 返回与该 array 所等价的 C 风格数组类型的引用, 方便与专门为 C 风格数组类型设计的 API 交互
				 * @return 与该 array 所等价的 C 风格数组类型的引用
				 * @warning 必须保证数组元素存满时才可调用此方法
				 * @throw std::exception Throw this exception when call this method while the array is not full
				 */
				KERBAL_CONSTEXPR14 equal_c_array_reference c_arr();
				KERBAL_CONSTEXPR14 const_equal_c_array_reference c_arr() const;
				KERBAL_CONSTEXPR const_equal_c_array_reference const_c_arr() const;

				KERBAL_CONSTEXPR const_pointer data() const;

				/**
				 * @brief Swap the array with another one.
				 * @param with another array to be swaped with
				 */
				KERBAL_CONSTEXPR14 void swap(array & with);

				/**
				 * @brief Fill all the blank positions at the end of array by copying the argument val.
				 * @param val
				 */
				KERBAL_CONSTEXPR14 void fill(const_reference val);

		};

		template <typename Tp, size_t M, size_t N>
		KERBAL_CONSTEXPR14 bool operator==(const array<Tp, M> & lhs, const array<Tp, N> & rhs)
		{
			return kerbal::algorithm::sequence_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, size_t M, size_t N>
		KERBAL_CONSTEXPR14 bool operator!=(const array<Tp, M> & lhs, const array<Tp, N> & rhs)
		{
			return kerbal::algorithm::sequence_not_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, size_t M, size_t N>
		KERBAL_CONSTEXPR14 bool operator<(const array<Tp, M> & lhs, const array<Tp, N> & rhs)
		{
			return kerbal::algorithm::sequence_less(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, size_t M, size_t N>
		KERBAL_CONSTEXPR14 bool operator<=(const array<Tp, M> & lhs, const array<Tp, N> & rhs)
		{
			return kerbal::algorithm::sequence_less_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, size_t M, size_t N>
		KERBAL_CONSTEXPR14 bool operator>(const array<Tp, M> & lhs, const array<Tp, N> & rhs)
		{
			return kerbal::algorithm::sequence_greater(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, size_t M, size_t N>
		KERBAL_CONSTEXPR14 bool operator>=(const array<Tp, M> & lhs, const array<Tp, N> & rhs)
		{
			return kerbal::algorithm::sequence_greater_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

	} // namespace container

} //namespace kerbal

#include <kerbal/container/impl/array.impl.hpp>
#include <kerbal/container/impl/array_iterator.impl.hpp>

#endif /* KERBAL_CONTAINER_ARRAY_HPP_ */
