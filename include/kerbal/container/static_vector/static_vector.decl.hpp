/**
 * @file       static_vector.decl.hpp
 * @brief
 * @date       2018-4-28
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_STATIC_VECTOR_STATIC_VECTOR_DECL_HPP
#define KERBAL_CONTAINER_STATIC_VECTOR_STATIC_VECTOR_DECL_HPP

#include <kerbal/assign/ilist.hpp>
#include <kerbal/compare/sequence_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/static_container_exception.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/iterator/reverse_iterator.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/remove_all_extents.hpp>
#include <kerbal/utility/throw_this_exception.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#include <cstddef>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif

#include <kerbal/container/detail/static_vector_base.hpp>
#include <kerbal/container/detail/static_vector_base/static_vector_iterator.hpp>


namespace kerbal
{

	namespace container
	{

		/**
		 * @brief Array with flexible length that stored on automatic storage duration
		 * @details The class is an encapsulation class of array that could be stored on
		 *          automatic storage duration. It is more effective than std::vector
		 *          (especially when type parameter T is trivial type) because std::vector
		 *          store elements on heap storage duration (that's required memory allocation
		 *          and deallocation). Meanwhile the static_vector has more flexibility
		 *          than std::array for the reason that std::array has fixed length and
		 *          doesn't support operations like `insert` and `erase`. For further,
		 *          std::array and c-style array must call default constructor for initialization
		 *          when it was declared. However, as we all know, sometimes the default construct
		 *          operations are unnecessary.
		 * @tparam T Type of the elements.
		 * @tparam N The maximum number of elements that the array can hold.
		 */
		template <typename T, std::size_t N>
		class static_vector :
			protected kerbal::container::detail::sv_trivially_des_overload<T, N>
		{
			private:
				typedef kerbal::container::detail::sv_trivially_des_overload<T, N> super;

			public:
				typedef typename super::value_type			value_type;
				typedef typename super::const_type			const_type;
				typedef typename super::reference			reference;
				typedef typename super::const_reference		const_reference;
				typedef typename super::pointer				pointer;
				typedef typename super::const_pointer		const_pointer;

#			if __cplusplus >= 201103L
				typedef typename super::rvalue_reference			rvalue_reference;
				typedef typename super::const_rvalue_reference		const_rvalue_reference;
#			endif

				typedef typename super::size_type	size_type;
				typedef typename super::difference_type		difference_type;

				typedef value_type				equal_c_array[N];
				typedef equal_c_array &			equal_c_array_reference;
				typedef const equal_c_array &	equal_const_c_array_reference;
				typedef const value_type		const_equal_c_array[N];
				typedef const_equal_c_array &	const_equal_c_array_reference;

			private:
				typedef typename super::size_compressed_type	size_compressed_type;
				typedef typename super::storage_type			storage_type;
				typedef typename kerbal::type_traits::remove_all_extents<value_type>::type remove_all_extents_t;

			public:

				/// @brief Iterator to static_vector.
				typedef detail::sv_iter<value_type>							iterator;
				/// @brief Constant iterator to static_vector.
				typedef detail::sv_kiter<value_type>						const_iterator;
				/// @brief Reverse iterator to static_vector.
				typedef kerbal::iterator::reverse_iterator<iterator>		reverse_iterator;
				/// @brief Constant reverse iterator to static_vector.
				typedef kerbal::iterator::reverse_iterator<const_iterator>	const_reverse_iterator;

			public:

			//===================
			// construct/copy/destroy

				KERBAL_CONSTEXPR
				/** @brief Empty container constructor (Default constructor) */
				static_vector() KERBAL_NOEXCEPT;

				/**
				 * @brief Copy constructor
				 * @param src Another static_vector object of the same type (must have the same template arguments type and N)
				 */
				KERBAL_CONSTEXPR14
				static_vector(const static_vector & src);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				static_vector(static_vector && src);

#		endif

				KERBAL_CONSTEXPR14
				explicit static_vector(size_type n);

				KERBAL_CONSTEXPR14
				static_vector(size_type n, const_reference val);

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
				static_vector(
					InputIterator first, InputIterator last,
					typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
						int
					>::type = 0
				);

#		if __cplusplus >= 201103L

				/**
				 * @brief Construct the array by coping the contents in initializer list
				 * @param ilist An initializer list
				 */
				KERBAL_CONSTEXPR14
				static_vector(std::initializer_list<value_type> ilist);

#		else

				static_vector(const kerbal::assign::assign_list<void> & ilist);

				template <typename U>
				static_vector(const kerbal::assign::assign_list<U> & ilist);

#		endif


			//===================
			// assign

				KERBAL_CONSTEXPR14
				static_vector & operator=(const static_vector & src);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				static_vector & operator=(static_vector && src);

#		endif

#		if __cplusplus >= 201103L

				/**
				 * @brief Assign the array by using the content of an initializer list
				 * @param ilist the initializer list
				 * @return the reference to the array be assigned
				 */
				KERBAL_CONSTEXPR14
				static_vector & operator=(std::initializer_list<value_type> ilist);

#		else

				static_vector & operator=(const kerbal::assign::assign_list<void> & ilist);

				template <typename U>
				static_vector & operator=(const kerbal::assign::assign_list<U> & ilist);

#		endif

			private:

				KERBAL_CONSTEXPR14
				void k_assign_unsafe_n_val(
					size_type new_size, const_reference val,
					kerbal::type_traits::false_type enable_optimization
				);

				KERBAL_CONSTEXPR14
				void k_assign_unsafe_n_val(
					size_type new_size, const_reference val,
					kerbal::type_traits::true_type enable_optimization
				);

			public:

				KERBAL_CONSTEXPR14
				void assign_unsafe(size_type new_size, const_reference val);

				/**
				 * @brief Assign the array by using n value(s).
				 * @param new_size numbers of the value(s)
				 * @param val value
				 */
				KERBAL_CONSTEXPR20
				void assign(size_type new_size, const_reference val);

			private:

				template <typename InputIterator>
				KERBAL_CONSTEXPR14
				void k_assign_unsafe_range(
					InputIterator first, InputIterator last,
					std::input_iterator_tag
				);

				template <typename ForwardIterator>
				KERBAL_CONSTEXPR14
				void k_assign_unsafe_range(
					ForwardIterator first, ForwardIterator last,
					std::forward_iterator_tag
				);

			public:

				template <typename InputIterator>
				KERBAL_CONSTEXPR14
				typename kerbal::type_traits::enable_if<
					kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
				>::type
				assign_unsafe(InputIterator first, InputIterator last);

			private:

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				void k_assign_range(
					InputIterator first, InputIterator last,
					std::input_iterator_tag
				);

				template <typename ForwardIterator>
				KERBAL_CONSTEXPR20
				void k_assign_range(
					ForwardIterator first, ForwardIterator last,
					std::forward_iterator_tag
				);

			public:

				/**
				 * @brief Assign the array by using a range of elements.
				 * @param first the iterator that points to the range begin
				 * @param last the iterator that points to the range end
				 * @tparam InputIterator An input iterator type that points to elements of a type
				 * @throw 若区间长度超出 static_vector 所能存放的最大元素数目, 则抛出 logic_error 异常
				 */
				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				typename kerbal::type_traits::enable_if<
					kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
				>::type
				assign(InputIterator first, InputIterator last);

#		if __cplusplus >= 201103L

				/**
				 * @brief Assign the array by using the content of an initializer list
				 * @param ilist the initializer list
				 */
				KERBAL_CONSTEXPR14
				void assign_unsafe(std::initializer_list<value_type> ilist);

				KERBAL_CONSTEXPR20
				void assign(std::initializer_list<value_type> ilist);

#		else

				void assign_unsafe(const kerbal::assign::assign_list<void> & ilist);

				template <typename U>
				void assign_unsafe(const kerbal::assign::assign_list<U> & ilist);

				void assign(const kerbal::assign::assign_list<void> & ilist);

				template <typename U>
				void assign(const kerbal::assign::assign_list<U> & ilist);

#		endif


			//===================
			// element access

				KERBAL_CONSTEXPR14
				reference operator[](size_type index) KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				const_reference operator[](size_type index) const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				reference at(size_type index);

				KERBAL_CONSTEXPR20
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

				equal_c_array_reference c_arr();
				const_equal_c_array_reference c_arr() const;
				const_equal_c_array_reference const_c_arr() const;

				const_pointer data() const KERBAL_NOEXCEPT;


			//===================
			// iterator

				KERBAL_CONSTEXPR14
				iterator begin() KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR
				const_iterator begin() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR
				const_iterator cbegin() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				iterator end() KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR
				const_iterator end() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR
				const_iterator cend() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				reverse_iterator rbegin() KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR
				const_reverse_iterator rbegin() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR
				const_reverse_iterator crbegin() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				reverse_iterator rend() KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR
				const_reverse_iterator rend() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR
				const_reverse_iterator crend() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR14
				iterator nth(size_type index)
				{
					return this->begin() + index;
				}

				KERBAL_CONSTEXPR
				const_iterator nth(size_type index) const
				{
					return this->cbegin() + index;
				}

				KERBAL_CONSTEXPR14
				size_type index_of(iterator it)
				{
					return it - this->begin();
				}

				KERBAL_CONSTEXPR
				size_type index_of(const_iterator it) const
				{
					return it - this->cbegin();
				}


			//===================
			// capacity

				/**
				 * @brief Count the number of the elements that the array has contained.
				 * @return the number of the elements that the array has contained
				 */
				KERBAL_CONSTEXPR
				size_type size() const KERBAL_NOEXCEPT;

				/**
				 * @brief Returns the size() of the largest possible static_vector.
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

				KERBAL_CONSTEXPR20
				void alert_empty() const
				{
					if (empty()) {
						kerbal::utility::throw_this_exception_helper<kerbal::container::static_container_empty_exception>::throw_this_exception();
					}
				}

				/**
				 * @brief Judge whether the array has been full.
				 * @return If the array has been full, return true, otherwise return false
				 */
				KERBAL_CONSTEXPR
				bool full() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				void alert_full() const
				{
					if (full()) {
						kerbal::utility::throw_this_exception_helper<kerbal::container::static_container_full_exception>::throw_this_exception(N);
					}
				}


			//===================
			// insert

#		if __cplusplus >= 201103L

				template <typename ... Args>
				KERBAL_CONSTEXPR14
				iterator emplace_unsafe(const_iterator pos, Args && ... args);

				template <typename ... Args>
				KERBAL_CONSTEXPR20
				iterator emplace(const_iterator pos, Args && ... args);

#		else

#			define EMPTY
#			define LEFT_JOIN_COMMA(exp) , exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#			define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				iterator emplace_unsafe(const_iterator pos KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)); \
 \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				iterator emplace(const_iterator pos KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)); \

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#			undef EMPTY
#			undef LEFT_JOIN_COMMA
#			undef THEAD_NOT_EMPTY
#			undef TARGS_DECL
#			undef ARGS_DECL
#			undef FBODY

#		endif

				KERBAL_CONSTEXPR14
				iterator insert_unsafe(const_iterator pos, const_reference val);

				KERBAL_CONSTEXPR20
				iterator insert(const_iterator pos, const_reference val);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				iterator insert_unsafe(const_iterator pos, rvalue_reference val);

				KERBAL_CONSTEXPR20
				iterator insert(const_iterator pos, rvalue_reference val);

#		endif

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				iterator k_range_insert(
					const_iterator pos,
					InputIterator first, InputIterator last,
					std::input_iterator_tag
				);

				template <typename ForwardIterator>
				KERBAL_CONSTEXPR20
				iterator k_range_insert(
					const_iterator pos,
					ForwardIterator first, ForwardIterator last,
					std::forward_iterator_tag
				);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				typename kerbal::type_traits::enable_if<
					kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
					iterator
				>::type
				insert(
					const_iterator pos,
					InputIterator first, InputIterator last
				);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				iterator insert(
					const_iterator pos,
					std::initializer_list<T> ilist
				);

#		else

				iterator insert(
					const_iterator pos,
					const kerbal::assign::assign_list<void> & ilist
				);

				template <typename U>
				iterator insert(
					const_iterator pos,
					const kerbal::assign::assign_list<U> & ilist
				);

#		endif

#		if __cplusplus >= 201103L

				template <typename ... Args>
				KERBAL_CONSTEXPR14
				reference emplace_back_unsafe(Args && ... args);

				template <typename ... Args>
				KERBAL_CONSTEXPR20
				reference emplace_back(Args && ... args);

#		else

#			define EMPTY
#			define REMAINF(exp) exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#			define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				reference emplace_back_unsafe(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)); \
 \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				reference emplace_back(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)); \

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#			undef EMPTY
#			undef REMAINF
#			undef THEAD_NOT_EMPTY
#			undef TARGS_DECL
#			undef ARGS_DECL
#			undef FBODY

#		endif

				KERBAL_CONSTEXPR14
				void push_back_unsafe(const_reference src);

				KERBAL_CONSTEXPR20
				void push_back(const_reference src);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				void push_back_unsafe(rvalue_reference src);

				KERBAL_CONSTEXPR20
				void push_back(rvalue_reference src);

#		endif

				/**
				 * @brief Fill all the blank positions at the end of array by using default constructor of the element type.
				 */
				KERBAL_CONSTEXPR14
				void fill();

				/**
				 * @brief Fill all the blank positions at the end of array by copying the argument val.
				 * @param val
				 */
				KERBAL_CONSTEXPR14
				void fill(const_reference val);


			//===================
			// erase

				KERBAL_CONSTEXPR14
				iterator erase(const_iterator pos);

				KERBAL_CONSTEXPR14
				iterator erase(const_iterator begin, const_iterator end);

				KERBAL_CONSTEXPR14
				void pop_back_unsafe();

				KERBAL_CONSTEXPR20
				void pop_back();

				KERBAL_CONSTEXPR14
				void shrink_back_to(const_iterator to);

				/**
				 * @brief Clear all the elements in the array.
				 */
				KERBAL_CONSTEXPR14
				void clear();


			//===================
			// operation

			private:
				KERBAL_CONSTEXPR14
				void k_swap_helper(static_vector & with);

			public:
				/**
				 * @brief Swap the array with another one.
				 * @param with another array to be swaped with
				 */
				KERBAL_CONSTEXPR14
				void swap(static_vector & with);

				template <typename U, std::size_t N1, std::size_t N2>
				KERBAL_CONSTEXPR14
				friend
				static_vector<U, N1 + N2>
				operator+(const static_vector<U, N1> & lhs, const static_vector<U, N2> & rhs);

#		if __cplusplus >= 201103L

				template <typename U, std::size_t N1, std::size_t N2>
				KERBAL_CONSTEXPR14
				friend
				static_vector<U, N1 + N2>
				operator+(const static_vector<U, N1> & lhs, const static_vector<U, N2> && rhs);

				template <typename U, std::size_t N1, std::size_t N2>
				KERBAL_CONSTEXPR14
				friend
				static_vector<U, N1 + N2>
				operator+(const static_vector<U, N1> && lhs, const static_vector<U, N2> & rhs);

				template <typename U, std::size_t N1, std::size_t N2>
				KERBAL_CONSTEXPR14
				friend
				static_vector<U, N1 + N2>
				operator+(const static_vector<U, N1> && lhs, const static_vector<U, N2> && rhs);

#		endif

				template <std::size_t M>
				KERBAL_CONSTEXPR14
				static_vector<T, N>
				operator*(const static_vector<T, M> & rhs) const;

		};

		template <typename T, std::size_t M, std::size_t N>
		KERBAL_CONSTEXPR14
		bool operator==(
			const static_vector<T, M> & lhs,
			const static_vector<T, N> & rhs
		)
		{
			return kerbal::compare::sequence_equal_to(
				lhs.cbegin(), lhs.cend(),
				rhs.cbegin(), rhs.cend()
			);
		}

		template <typename T, std::size_t M, std::size_t N>
		KERBAL_CONSTEXPR14
		bool operator!=(
			const static_vector<T, M> & lhs,
			const static_vector<T, N> & rhs
		)
		{
			return kerbal::compare::sequence_not_equal_to(
				lhs.cbegin(), lhs.cend(),
				rhs.cbegin(), rhs.cend()
			);
		}

		template <typename T, std::size_t M, std::size_t N>
		KERBAL_CONSTEXPR14
		bool operator<(
			const static_vector<T, M> & lhs,
			const static_vector<T, N> & rhs
		)
		{
			return kerbal::compare::sequence_less(
				lhs.cbegin(), lhs.cend(),
				rhs.cbegin(), rhs.cend()
			);
		}

		template <typename T, std::size_t M, std::size_t N>
		KERBAL_CONSTEXPR14
		bool operator<=(
			const static_vector<T, M> & lhs,
			const static_vector<T, N> & rhs
		)
		{
			return kerbal::compare::sequence_less_equal(
				lhs.cbegin(), lhs.cend(),
				rhs.cbegin(), rhs.cend()
			);
		}

		template <typename T, std::size_t M, std::size_t N>
		KERBAL_CONSTEXPR14
		bool operator>(
			const static_vector<T, M> & lhs,
			const static_vector<T, N> & rhs
		)
		{
			return kerbal::compare::sequence_greater(
				lhs.cbegin(), lhs.cend(),
				rhs.cbegin(), rhs.cend()
			);
		}

		template <typename T, std::size_t M, std::size_t N>
		KERBAL_CONSTEXPR14
		bool operator>=(
			const static_vector<T, M> & lhs,
			const static_vector<T, N> & rhs
		)
		{
			return kerbal::compare::sequence_greater_equal(
				lhs.cbegin(), lhs.cend(),
				rhs.cbegin(), rhs.cend()
			);
		}

	} // namespace container


	namespace algorithm
	{

		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR14
		void swap(
			kerbal::container::static_vector<T, N> & a,
			kerbal::container::static_vector<T, N> & b
		)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
		{
			a.swap(b);
		}

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <typename T, std::size_t N>
	KERBAL_CONSTEXPR14
	void swap(
		kerbal::container::static_vector<T, N> & a,
		kerbal::container::static_vector<T, N> & b
	)
		KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END

#endif // KERBAL_CONTAINER_STATIC_VECTOR_STATIC_VECTOR_DECL_HPP
