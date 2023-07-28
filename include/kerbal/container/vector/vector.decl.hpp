/**
 * @file       vector.decl.hpp
 * @brief
 * @date       2021-08-17
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_VECTOR_VECTOR_DECL_HPP
#define KERBAL_CONTAINER_VECTOR_VECTOR_DECL_HPP

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/assign/ilist.hpp>
#include <kerbal/compare/sequence_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/remove_all_extents.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/utility/declval.hpp>
#endif

#include <memory>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif

#include <kerbal/container/detail/vector_base/vector_base.decl.hpp>
#include <kerbal/container/detail/container_allocator_overload.hpp>

#include <kerbal/container/detail/vector_base/vector_iterator.hpp>


namespace kerbal
{

	namespace container
	{

		template <typename Tp, typename Allocator>
		class vector:
				protected kerbal::container::detail::container_allocator_overload<Allocator>,
				protected kerbal::container::detail::vector_type_only<Tp>
		{
			private:
				typedef kerbal::container::detail::container_allocator_overload<Allocator>	vector_allocator_overload;
				typedef kerbal::container::detail::vector_type_only<Tp>			vector_type_only;

			public:
				typedef typename vector_type_only::value_type				value_type;
				typedef typename vector_type_only::const_type				const_type;
				typedef typename vector_type_only::reference				reference;
				typedef typename vector_type_only::const_reference			const_reference;
				typedef typename vector_type_only::pointer					pointer;
				typedef typename vector_type_only::const_pointer			const_pointer;

#		if __cplusplus >= 201103L
				typedef typename vector_type_only::rvalue_reference			rvalue_reference;
				typedef typename vector_type_only::const_rvalue_reference	const_rvalue_reference;
#		endif

				typedef typename vector_type_only::size_type				size_type;
				typedef typename vector_type_only::difference_type			difference_type;

				typedef typename vector_type_only::iterator					iterator;
				typedef typename vector_type_only::const_iterator			const_iterator;
				typedef typename vector_type_only::reverse_iterator			reverse_iterator;
				typedef typename vector_type_only::const_reverse_iterator	const_reverse_iterator;

			private:
				typedef typename kerbal::type_traits::remove_all_extents<value_type>::type remove_all_extents_t;

			public:
				typedef typename vector_allocator_overload::allocator_type				allocator_type;
				typedef kerbal::memory::allocator_traits<allocator_type>				allocator_traits;

			private:
				using vector_allocator_overload::alloc;

			public:

			//===================
			// construct/copy/destroy

				KERBAL_CONSTEXPR20
				vector() KERBAL_CONDITIONAL_NOEXCEPT(
						vector_allocator_overload::is_nothrow_default_constructible::value &&
						vector_type_only::is_nothrow_default_constructible::value
				);

				KERBAL_CONSTEXPR20
				explicit
				vector(const Allocator & allocator) KERBAL_CONDITIONAL_NOEXCEPT(
						vector_allocator_overload::is_nothrow_constructible_from_allocator_const_reference::value &&
						vector_type_only::is_nothrow_default_constructible::value
				);

				KERBAL_CONSTEXPR20
				explicit
				vector(size_type count);

				KERBAL_CONSTEXPR20
				vector(size_type count, const Allocator & allocator);

				KERBAL_CONSTEXPR20
				vector(size_type count, const_reference value);

				KERBAL_CONSTEXPR20
				vector(size_type count, const_reference value, const Allocator & allocator);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				vector(InputIterator first, InputIterator last,
						typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
								, int
						>::type = 0
				);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				vector(InputIterator first, InputIterator last, const Allocator & allocator,
						typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
								, int
						>::type = 0
				);

				KERBAL_CONSTEXPR20
				vector(const vector & src);

				KERBAL_CONSTEXPR20
				vector(const vector & src, const Allocator & allocator);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				vector(vector && src) KERBAL_CONDITIONAL_NOEXCEPT(
						vector_allocator_overload::is_nothrow_constructible_from_allocator_rvalue_reference::value &&
						vector_type_only::is_nothrow_move_constructible::value
				);

				KERBAL_CONSTEXPR20
				vector(vector && src, const Allocator & allocator) KERBAL_CONDITIONAL_NOEXCEPT(
						vector_allocator_overload::is_nothrow_constructible_from_allocator_const_reference::value &&
						vector_type_only::template is_nothrow_move_constructible_using_allocator<allocator_type>::value
				);


#		endif

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				vector(std::initializer_list<value_type> ilist);

				KERBAL_CONSTEXPR20
				vector(std::initializer_list<value_type> ilist, const Allocator & allocator);

#		else

				vector(const kerbal::assign::assign_list<void> & ilist);

				template <typename Up>
				vector(const kerbal::assign::assign_list<Up> & ilist);

				vector(const kerbal::assign::assign_list<void> & ilist, const Allocator & allocator);

				template <typename Up>
				vector(const kerbal::assign::assign_list<Up> & ilist, const Allocator & allocator);

#		endif

				KERBAL_CONSTEXPR20
				~vector();

			//===================
			// assign

				KERBAL_CONSTEXPR20
				vector& operator=(const vector & src);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				vector& operator=(vector && src) KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<vector>()->assign(kerbal::compatibility::move(src)))
				);

#		endif

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				vector& operator=(std::initializer_list<value_type> ilist);

#		else

				vector& operator=(const kerbal::assign::assign_list<void> & ilist);

				template <typename Up>
				vector& operator=(const kerbal::assign::assign_list<Up> & ilist);

#		endif

			public:

				KERBAL_CONSTEXPR20
				void assign(size_type new_size, const_reference value);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
				>::type
				assign(InputIterator first, InputIterator last);

				KERBAL_CONSTEXPR20
				void assign(const vector & src);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void assign(vector && src) KERBAL_CONDITIONAL_NOEXCEPT(
						vector_type_only::template is_nothrow_move_assign_using_allocator<allocator_type>::value
				);

#		endif

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void assign(std::initializer_list<value_type> ilist);

#		else

				void assign(const kerbal::assign::assign_list<void> & ilist);

				template <typename Up>
				void assign(const kerbal::assign::assign_list<Up> & ilist);

#		endif

			//===================
			// element access

				using vector_type_only::at;
				using vector_type_only::operator[];
				using vector_type_only::front;
				using vector_type_only::back;
				using vector_type_only::data;

			//===================
			// iterator

				using vector_type_only::begin;
				using vector_type_only::end;

				using vector_type_only::cbegin;
				using vector_type_only::cend;

				using vector_type_only::rbegin;
				using vector_type_only::rend;

				using vector_type_only::crbegin;
				using vector_type_only::crend;

				using vector_type_only::nth;
				using vector_type_only::cnth;
				using vector_type_only::index_of;

			//===================
			// capacity

				using vector_type_only::empty;
				using vector_type_only::size;
				using vector_type_only::capacity;

				KERBAL_CONSTEXPR
				size_type max_size() const KERBAL_NOEXCEPT
				{
					return allocator_traits::max_size(this->alloc());
				}

				KERBAL_CONSTEXPR20
				void reserve(size_type new_capacity);

				KERBAL_CONSTEXPR20
				void shrink_to_fit();

			//===================
			// insert

#		if __cplusplus >= 201103L

				template <typename ... Args>
				KERBAL_CONSTEXPR20
				iterator emplace(const_iterator pos, Args&& ...args);

#		else

#			define EMPTY
#			define LEFT_JOIN_COMMA(exp) , exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#			define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				iterator emplace(const_iterator pos KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i));

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#			undef EMPTY
#			undef LEFT_JOIN_COMMA
#			undef THEAD_NOT_EMPTY
#			undef TARGS_DECL
#			undef ARGS_DECL
#			undef FBODY

#		endif

				KERBAL_CONSTEXPR20
				iterator insert(const_iterator pos, const_reference val);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				iterator insert(const_iterator pos, rvalue_reference val);

#		endif

				KERBAL_CONSTEXPR20
				iterator insert(const_iterator pos, size_type n, const_reference val);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
						iterator
				>::type
				insert(const_iterator pos, InputIterator first, InputIterator last);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				iterator insert(const_iterator pos, std::initializer_list<value_type> ilist);

#		else

				iterator insert(const_iterator pos, const kerbal::assign::assign_list<void> & ilist);

				template <typename Up>
				iterator insert(const_iterator pos, const kerbal::assign::assign_list<Up> & ilist);

#		endif


#		if __cplusplus >= 201103L

				template <typename ... Args>
				KERBAL_CONSTEXPR20
				reference emplace_back(Args&& ...args);

#		else

#			define EMPTY
#			define REMAINF(exp) exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#			define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				reference emplace_back(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i));

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#			undef EMPTY
#			undef REMAINF
#			undef THEAD_NOT_EMPTY
#			undef TARGS_DECL
#			undef ARGS_DECL
#			undef FBODY

#		endif

				KERBAL_CONSTEXPR20
				void push_back(const_reference src);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void push_back(rvalue_reference src);

#		endif

			//===================
			// erase

				KERBAL_CONSTEXPR20
				iterator erase(const_iterator pos);

				KERBAL_CONSTEXPR20
				iterator erase(const_iterator first, const_iterator last);

				KERBAL_CONSTEXPR20
				void pop_back() KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				void clear() KERBAL_NOEXCEPT;

			//===================
			// operation

				KERBAL_CONSTEXPR20
				void resize(size_type new_size);

				KERBAL_CONSTEXPR20
				void resize(size_type new_size, const_reference value);

				KERBAL_CONSTEXPR20
				void swap(vector & with) KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(vector_allocator_overload::k_swap_allocator_if_propagate(
								kerbal::utility::declval<vector_allocator_overload&>(), kerbal::utility::declval<vector_allocator_overload&>()
						)) &&
						noexcept(vector_type_only::k_swap_type_unrelated(
								kerbal::utility::declval<vector_type_only&>(), kerbal::utility::declval<vector_type_only&>()
						))
				);

		};

#	if __cplusplus >= 201703L

		template <typename InputIterator, typename Alloc =
					std::allocator<typename kerbal::iterator::iterator_traits<InputIterator>::value_type> >
		vector(InputIterator, InputIterator, Alloc = Alloc())
				-> vector<typename kerbal::iterator::iterator_traits<InputIterator>::value_type, Alloc>;

#	endif


		template <typename Tp, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator==(const vector<Tp, Allocator> & lhs, const vector<Tp, Allocator2> & rhs)
		{
			return kerbal::compare::sequence_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator!=(const vector<Tp, Allocator> & lhs, const vector<Tp, Allocator2> & rhs)
		{
			return kerbal::compare::sequence_not_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator<(const vector<Tp, Allocator> & lhs, const vector<Tp, Allocator2> & rhs)
		{
			return kerbal::compare::sequence_less(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator<=(const vector<Tp, Allocator> & lhs, const vector<Tp, Allocator2> & rhs)
		{
			return kerbal::compare::sequence_less_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator>(const vector<Tp, Allocator> & lhs, const vector<Tp, Allocator2> & rhs)
		{
			return kerbal::compare::sequence_greater(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator>=(const vector<Tp, Allocator> & lhs, const vector<Tp, Allocator2> & rhs)
		{
			return kerbal::compare::sequence_greater_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

	} // namespace container

	namespace algorithm
	{

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void swap(kerbal::container::vector<Tp, Allocator> & a, kerbal::container::vector<Tp, Allocator> & b)
				KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
		{
			a.swap(b);
		}

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <typename Tp, typename Allocator>
	KERBAL_CONSTEXPR20
	void swap(kerbal::container::vector<Tp, Allocator> & a, kerbal::container::vector<Tp, Allocator> & b)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END

#endif // KERBAL_CONTAINER_VECTOR_VECTOR_DECL_HPP
