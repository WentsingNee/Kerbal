/**
 * @file       array.decl.hpp
 * @brief
 * @date       2019-10-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_ARRAY_ARRAY_DECL_HPP
#define KERBAL_CONTAINER_ARRAY_ARRAY_DECL_HPP

#include <kerbal/container/array/array.fwd.hpp>

#include <kerbal/assign/ilist.hpp>
#include <kerbal/compare/sequence_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/iterator/reverse_iterator.hpp>
#include <kerbal/type_traits/array_traits.hpp>
#include <kerbal/type_traits/enable_if.hpp>

#include <cstddef>
#include <stdexcept>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif

#include <kerbal/container/detail/array_iterator.hpp>


namespace kerbal
{

	namespace container
	{

		template <typename Tp, std::size_t N>
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

				/// @brief Iterator to array.
				typedef kerbal::container::detail::__arr_iter<value_type> iterator;
				/// @brief Constant iterator to array.
				typedef kerbal::container::detail::__arr_kiter<value_type> const_iterator;
				/// @brief Reverse iterator to array.
				typedef kerbal::iterator::reverse_iterator<iterator> reverse_iterator;
				/// @brief Constant reverse iterator to array.
				typedef kerbal::iterator::reverse_iterator<const_iterator> const_reverse_iterator;

				/// @brief 与该 array 所等价的 C 风格数组的类型, 即 value_type[N]
				typedef value_type equal_c_array[N];
				typedef equal_c_array& equal_c_array_reference;
				typedef const value_type const_equal_c_array[N];
				typedef const_equal_c_array& const_equal_c_array_reference;

			public:
				value_type _K_data[N];

			public:

#		if __cplusplus < 201103L

				/** @brief Initialize the array with default value (Default constructor) */
				array();

				template <typename Up>
				array(const kerbal::assign::assign_list<Up> & src);

				template <typename Up>
				array& operator=(const kerbal::assign::assign_list<Up> & src);

#		endif

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

#		if __cplusplus >= 201103L
				/**
				 * @brief Assign the array by using the content of an initializer list
				 * @param src the initializer list
				 */
				KERBAL_CONSTEXPR14
				void assign(std::initializer_list<value_type> src);

#		else

				template <typename Up>
				void assign(const kerbal::assign::assign_list<Up> & src);

#		endif

				/** @brief 返回指向数组首元素的迭代器 */
				KERBAL_CONSTEXPR14
				iterator begin() KERBAL_NOEXCEPT;

				/** @brief 返回指向数组末尾元素的后一个元素位置的迭代器 */
				KERBAL_CONSTEXPR14
				iterator end() KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				const_iterator begin() const KERBAL_NOEXCEPT;

				/** @brief 返回指向数组末尾元素的后一个元素位置的迭代器 */
				KERBAL_CONSTEXPR14
				const_iterator end() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR
				const_iterator cbegin() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR
				const_iterator cend() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				reverse_iterator rbegin() KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				reverse_iterator rend() KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				const_reverse_iterator rbegin() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				const_reverse_iterator rend() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR
				const_reverse_iterator crbegin() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR
				const_reverse_iterator crend() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				iterator nth(size_type index) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				const_iterator nth(size_type index) const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				size_type index_of(iterator it) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR
				size_type index_of(const_iterator it) const KERBAL_NOEXCEPT;

				/**
				 * @brief Count the number of the elements that the array has contained.
				 * @return the number of the elements that the array has contained
				 */
				KERBAL_CONSTEXPR
				size_type size() const KERBAL_NOEXCEPT;

				/**
				 * @brief Returns the size() of the largest possible array.
				 */
				KERBAL_CONSTEXPR
				size_type max_size() const KERBAL_NOEXCEPT
				{
					return N;
				}

				/**
				 * @brief Judge whether the array is empty.
				 * @return If the array is empty, return true, otherwise return false
				 */
				KERBAL_CONSTEXPR
				bool empty() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				reference operator[](size_type index) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				const_reference operator[](size_type index) const KERBAL_NOEXCEPT;

				reference at(size_type index);

				const_reference at(size_type index) const;

				/**
				 * @brief Get the reference of the element at the beginning of the array.
				 * @return the reference of the element at the beginning of the array.
				 */
				KERBAL_CONSTEXPR14
				reference front();

				/**
				 * @brief Get the const_reference of the element at the beginning of the array.
				 * @return the const_reference of the element at the beginning of the array.
				 */
				KERBAL_CONSTEXPR14
				const_reference front() const;

				/**
				 * @brief Get the reference of the element at the end of the array.
				 * @return the reference of the element at the end of the array.
				 */
				KERBAL_CONSTEXPR14
				reference back();

				/**
				 * @brief Get the const_reference of the element at the end of the array.
				 * @return the const_reference of the element at the end of the array.
				 */
				KERBAL_CONSTEXPR14
				const_reference back() const;

				/**
				 * @brief 返回与该 array 所等价的 C 风格数组类型的引用, 方便与专门为 C 风格数组类型设计的 API 交互
				 * @return 与该 array 所等价的 C 风格数组类型的引用
				 * @warning 必须保证数组元素存满时才可调用此方法
				 */
				KERBAL_CONSTEXPR14
				equal_c_array_reference c_arr() KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				const_equal_c_array_reference c_arr() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR
				const_equal_c_array_reference const_c_arr() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR
				const_pointer data() const KERBAL_NOEXCEPT;

				/**
				 * @brief Swap the array with another one.
				 * @param with another array to be swaped with
				 */
				KERBAL_CONSTEXPR14
				void swap(array & with);

				/**
				 * @brief Fill all the blank positions at the end of array by copying the argument val.
				 * @param val
				 */
				KERBAL_CONSTEXPR14
				void fill(const_reference val);

		};

		template <typename Tp, std::size_t M, std::size_t N>
		KERBAL_CONSTEXPR
		bool operator==(const array<Tp, M> &, const array<Tp, N> &) KERBAL_NOEXCEPT
		{
			return false;
		}

		template <typename Tp, std::size_t M, std::size_t N>
		KERBAL_CONSTEXPR
		bool operator!=(const array<Tp, M> &, const array<Tp, N> &) KERBAL_NOEXCEPT
		{
			return true;
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		bool operator==(const array<Tp, N> & lhs, const array<Tp, N> & rhs)
		{
			return kerbal::compare::sequence_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		bool operator!=(const array<Tp, N> & lhs, const array<Tp, N> & rhs)
		{
			return kerbal::compare::sequence_not_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, std::size_t M, std::size_t N>
		KERBAL_CONSTEXPR14
		bool operator<(const array<Tp, M> & lhs, const array<Tp, N> & rhs)
		{
			return kerbal::compare::sequence_less(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, std::size_t M, std::size_t N>
		KERBAL_CONSTEXPR14
		bool operator<=(const array<Tp, M> & lhs, const array<Tp, N> & rhs)
		{
			return kerbal::compare::sequence_less_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, std::size_t M, std::size_t N>
		KERBAL_CONSTEXPR14
		bool operator>(const array<Tp, M> & lhs, const array<Tp, N> & rhs)
		{
			return kerbal::compare::sequence_greater(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, std::size_t M, std::size_t N>
		KERBAL_CONSTEXPR14
		bool operator>=(const array<Tp, M> & lhs, const array<Tp, N> & rhs)
		{
			return kerbal::compare::sequence_greater_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

	} // namespace container


	namespace algorithm
	{

		template <typename Tp, std::size_t N>
		KERBAL_CONSTEXPR14
		void swap(kerbal::container::array<Tp, N> & a, kerbal::container::array<Tp, N> & b)
				KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
		{
			a.swap(b);
		}

	} // namespace algorithm

} //namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <typename Tp, std::size_t N>
	KERBAL_CONSTEXPR14
	void swap(kerbal::container::array<Tp, N> & a, kerbal::container::array<Tp, N> & b)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END


#endif // KERBAL_CONTAINER_ARRAY_ARRAY_DECL_HPP
