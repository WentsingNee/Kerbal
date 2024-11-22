/**
 * @file       vector.impl.hpp
 * @brief
 * @date       2020-6-12
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_VECTOR_VECTOR_IMPL_HPP
#define KERBAL_CONTAINER_VECTOR_VECTOR_IMPL_HPP


#include <kerbal/config/modules/modules.hpp>

#if KERBAL_ENABLE_MODULES
module;
#endif


#include <kerbal/config/modules/include_header_begin.part.hpp>


#include <kerbal/assign/ilist.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/type_traits/enable_if.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/utility/declval.hpp>
#	include <kerbal/utility/forward.hpp>
#endif

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif

#include <kerbal/container/detail/vector_base/vector_base.impl.hpp>
#include <kerbal/container/vector/vector.decl.hpp>


#include <kerbal/config/modules/include_header_end.part.hpp>


#if KERBAL_ENABLE_MODULES
export module kerbal.container.vector.impl;
#endif


namespace kerbal
{

	namespace container
	{

	//===================
	// construct/copy/destroy

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<T, Allocator>::vector()
			KERBAL_CONDITIONAL_NOEXCEPT(
				vector_allocator_overload::is_nothrow_default_constructible::value &&
				vector_type_only::is_nothrow_default_constructible::value
			) :
			vector_allocator_overload(),
			vector_type_only()
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<T, Allocator>::vector(const Allocator & allocator)
			KERBAL_CONDITIONAL_NOEXCEPT(
				vector_allocator_overload::is_nothrow_constructible_from_allocator_const_reference::value &&
				vector_type_only::is_nothrow_default_constructible::value
			) :
			vector_allocator_overload(allocator),
			vector_type_only()
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<T, Allocator>::vector(const vector & src) :
			vector_allocator_overload(src.alloc()),
			vector_type_only(this->alloc(), src.cbegin().current, src.cend().current)
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<T, Allocator>::vector(const vector & src, const Allocator & allocator) :
			vector_allocator_overload(allocator),
			vector_type_only(this->alloc(), src.cbegin().current, src.cend().current)
		{
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<T, Allocator>::vector(vector && src)
			KERBAL_CONDITIONAL_NOEXCEPT(
				vector_allocator_overload::is_nothrow_constructible_from_allocator_rvalue_reference::value &&
				vector_type_only::is_nothrow_move_constructible::value
			) :
			vector_allocator_overload(kerbal::compatibility::move(src.alloc())),
			vector_type_only(static_cast<vector_type_only &&>(src))
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<T, Allocator>::vector(vector && src, const Allocator & allocator)
			KERBAL_CONDITIONAL_NOEXCEPT(
				vector_allocator_overload::is_nothrow_constructible_from_allocator_const_reference::value &&
				vector_type_only::template is_nothrow_move_constructible_using_allocator<allocator_type>::value
			) :
			vector_allocator_overload(allocator),
			vector_type_only(
				this->alloc(),
				static_cast<Allocator &&>(src.alloc()),
				static_cast<vector_type_only &&>(src)
			)
		{
		}

#	endif

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<T, Allocator>::vector(size_type count) :
			vector_allocator_overload(),
			vector_type_only(this->alloc(), count)
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<T, Allocator>::vector(size_type count, const Allocator & allocator) :
			vector_allocator_overload(allocator),
			vector_type_only(this->alloc(), count)
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<T, Allocator>::vector(size_type count, const_reference value) :
			vector_allocator_overload(),
			vector_type_only(this->alloc(), count, value)
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<T, Allocator>::vector(size_type count, const_reference value, const Allocator & allocator) :
			vector_allocator_overload(allocator),
			vector_type_only(this->alloc(), count, value)
		{
		}

		template <typename T, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		vector<T, Allocator>::vector(
			InputIterator first, InputIterator last,
			typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
				int
			>::type
		) :
			vector_allocator_overload(),
			vector_type_only(this->alloc(), first, last)
		{
		}

		template <typename T, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		vector<T, Allocator>::vector(
			InputIterator first, InputIterator last,
			const Allocator & allocator,
			typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
				int
			>::type
		) :
			vector_allocator_overload(allocator),
			vector_type_only(this->alloc(), first, last)
		{
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<T, Allocator>::vector(std::initializer_list<value_type> ilist) :
			vector(ilist.begin(), ilist.end())
		{
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<T, Allocator>::vector(std::initializer_list<value_type> ilist, const Allocator & allocator) :
			vector(ilist.begin(), ilist.end(), allocator)
		{
		}

#	else

		template <typename T, typename Allocator>
		vector<T, Allocator>::vector(const kerbal::assign::assign_list<void> & ilist) :
			vector_allocator_overload(),
			vector_type_only()
		{
		}

		template <typename T, typename Allocator>
		template <typename U>
		vector<T, Allocator>::vector(const kerbal::assign::assign_list<U> & ilist) :
			vector_allocator_overload(),
			vector_type_only(this->alloc(), ilist.cbegin(), ilist.cend())
		{
		}

		template <typename T, typename Allocator>
		vector<T, Allocator>::vector(const kerbal::assign::assign_list<void> & ilist, const Allocator & allocator) :
			vector_allocator_overload(allocator),
			vector_type_only()
		{
		}

		template <typename T, typename Allocator>
		template <typename U>
		vector<T, Allocator>::vector(const kerbal::assign::assign_list<U> & ilist, const Allocator & allocator) :
			vector_allocator_overload(allocator),
			vector_type_only(this->alloc(), ilist.cbegin(), ilist.cend())
		{
		}

#	endif

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<T, Allocator>::~vector()
		{
			vector_type_only::k_destroy_using_allocator(this->alloc());
		}


	//===================
	// assign

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<T, Allocator> &
		vector<T, Allocator>::operator=(const vector & src)
		{
			this->assign(src);
			return *this;
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<T, Allocator> &
		vector<T, Allocator>::operator=(vector && src)
			KERBAL_CONDITIONAL_NOEXCEPT(
				noexcept(kerbal::utility::declthis<vector>()->assign(kerbal::compatibility::move(src)))
			)
		{
			this->assign(kerbal::compatibility::move(src));
			return *this;
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<T, Allocator> &
		vector<T, Allocator>::operator=(std::initializer_list<value_type> ilist)
		{
			this->assign(ilist.begin(), ilist.end());
			return *this;
		}

#	else

		template <typename T, typename Allocator>
		vector<T, Allocator> &
		vector<T, Allocator>::operator=(const kerbal::assign::assign_list<void> & ilist)
		{
			this->assign(ilist);
			return *this;
		}

		template <typename T, typename Allocator>
		template <typename U>
		vector<T, Allocator> &
		vector<T, Allocator>::operator=(const kerbal::assign::assign_list<U> & ilist)
		{
			this->assign(ilist);
			return *this;
		}

#	endif

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<T, Allocator>::assign(const vector & src)
		{
			this->vector_type_only::k_assign_using_allocator(
				this->alloc(),
				src.alloc(),
				static_cast<const vector_type_only &>(src)
			);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<T, Allocator>::assign(vector && src)
			KERBAL_CONDITIONAL_NOEXCEPT(
				vector_type_only::template is_nothrow_move_assign_using_allocator<allocator_type>::value
			)
		{
			this->vector_type_only::k_assign_using_allocator(
				this->alloc(),
				kerbal::compatibility::move(src.alloc()),
				static_cast<vector_type_only &&>(src)
			);
		}

#	endif

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<T, Allocator>::assign(size_type new_size, const_reference value)
		{
			vector_type_only::k_assign_using_allocator(this->alloc(), new_size, value);
		}

		template <typename T, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		typename kerbal::type_traits::enable_if<
			kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
		>::type
		vector<T, Allocator>::assign(InputIterator first, InputIterator last)
		{
			vector_type_only::k_assign_using_allocator(this->alloc(), first, last);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<T, Allocator>::assign(std::initializer_list<value_type> ilist)
		{
			this->assign(ilist.begin(), ilist.end());
		}

#	else

		template <typename T, typename Allocator>
		void vector<T, Allocator>::assign(const kerbal::assign::assign_list<void> & ilist)
		{
			this->clear();
		}

		template <typename T, typename Allocator>
		template <typename U>
		void vector<T, Allocator>::assign(const kerbal::assign::assign_list<U> & ilist)
		{
			this->assign(ilist.cbegin(), ilist.cend());
		}

#	endif


	//===================
	// capacity

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<T, Allocator>::reserve(size_type new_capacity)
		{
			vector_type_only::k_reserve_using_allocator(this->alloc(), new_capacity);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<T, Allocator>::shrink_to_fit()
		{
			vector_type_only::k_shrink_to_fit_using_allocator(this->alloc());
		}


	//===================
	// insert

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename
		vector<T, Allocator>::iterator
		vector<T, Allocator>::emplace(const_iterator pos, Args && ... args)
		{
			return vector_type_only::k_emplace_using_allocator(
				this->alloc(),
				pos,
				kerbal::utility::forward<Args>(args)...
			);
		}

#	else

#	define EMPTY
#	define LEFT_JOIN_COMMA(exp) , exp
#	define THEAD_NOT_EMPTY(exp) template <exp>
#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#	define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#	define FBODY(i) \
		template <typename T, typename Allocator> \
		KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
		typename \
		vector<T, Allocator>::iterator \
		vector<T, Allocator>::emplace( \
			const_iterator pos \
			KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
		) \
		{ \
			return vector_type_only::k_emplace_using_allocator( \
				this->alloc(), \
				pos \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i) \
			); \
		} \

		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#	undef EMPTY
#	undef LEFT_JOIN_COMMA
#	undef THEAD_NOT_EMPTY
#	undef TARGS_DECL
#	undef ARGS_DECL
#	undef ARGS_USE
#	undef FBODY

#	endif

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		vector<T, Allocator>::iterator
		vector<T, Allocator>::insert(const_iterator pos, const_reference val)
		{
			return vector_type_only::k_insert_using_allocator(
				this->alloc(),
				pos,
				val
			);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		vector<T, Allocator>::iterator
		vector<T, Allocator>::insert(const_iterator pos, rvalue_reference val)
		{
			return vector_type_only::k_insert_using_allocator(
				this->alloc(),
				pos,
				kerbal::compatibility::move(val)
			);
		}

#	endif

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		vector<T, Allocator>::iterator
		vector<T, Allocator>::insert(const_iterator pos, size_type n, const_reference val)
		{
			return vector_type_only::k_insert_using_allocator(
				this->alloc(),
				pos,
				n, val
			);
		}

		template <typename T, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		typename kerbal::type_traits::enable_if<
			kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
			typename vector<T, Allocator>::iterator
		>::type
		vector<T, Allocator>::insert(const_iterator pos, InputIterator first, InputIterator last)
		{
			return vector_type_only::k_insert_using_allocator(
				this->alloc(),
				pos,
				first, last
			);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		vector<T, Allocator>::iterator
		vector<T, Allocator>::insert(const_iterator pos, std::initializer_list<value_type> ilist)
		{
			return this->insert(pos, ilist.begin(), ilist.end());
		}

#	else

		template <typename T, typename Allocator>
		typename
		vector<T, Allocator>::iterator
		vector<T, Allocator>::insert(const_iterator pos, const kerbal::assign::assign_list<void> & ilist)
		{
			return pos.cast_to_mutable();
		}

		template <typename T, typename Allocator>
		template <typename U>
		typename
		vector<T, Allocator>::iterator
		vector<T, Allocator>::insert(const_iterator pos, const kerbal::assign::assign_list<U> & ilist)
		{
			return this->insert(pos, ilist.cbegin(), ilist.cend());
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename
		vector<T, Allocator>::reference
		vector<T, Allocator>::emplace_back(Args && ... args)
		{
			return vector_type_only::k_emplace_back_using_allocator(
				this->alloc(),
				kerbal::utility::forward<Args>(args)...
			);
		}

#	else

#	define EMPTY
#	define REMAINF(exp) exp
#	define LEFT_JOIN_COMMA(exp) , exp
#	define THEAD_NOT_EMPTY(exp) template <exp>
#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#	define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#	define FBODY(i) \
		template <typename T, typename Allocator> \
		KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
		typename \
		vector<T, Allocator>::reference \
		vector<T, Allocator>::emplace_back(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
		{ \
			return vector_type_only::k_emplace_back_using_allocator( \
				this->alloc() \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i) \
			); \
		} \

		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#	undef EMPTY
#	undef REMAINF
#	undef LEFT_JOIN_COMMA
#	undef THEAD_NOT_EMPTY
#	undef TARGS_DECL
#	undef ARGS_DECL
#	undef ARGS_USE
#	undef FBODY

#	endif

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<T, Allocator>::push_back(const_reference src)
		{
			vector_type_only::k_push_back_using_allocator(
				this->alloc(),
				src
			);
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<T, Allocator>::push_back(rvalue_reference src)
		{
			vector_type_only::k_push_back_using_allocator(
				this->alloc(),
				kerbal::compatibility::move(src)
			);
		}

#	endif


	//===================
	// erase

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		vector<T, Allocator>::iterator
		vector<T, Allocator>::erase(const_iterator pos)
		{
			return vector_type_only::k_erase_using_allocator(this->alloc(), pos);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		vector<T, Allocator>::iterator
		vector<T, Allocator>::erase(const_iterator first, const_iterator last)
		{
			return vector_type_only::k_erase_using_allocator(this->alloc(), first, last);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<T, Allocator>::pop_back() KERBAL_NOEXCEPT
		{
			vector_type_only::k_pop_back_using_allocator(this->alloc());
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<T, Allocator>::clear() KERBAL_NOEXCEPT
		{
			vector_type_only::k_clear_using_allocator(this->alloc());
		}


	//===================
	// operation

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<T, Allocator>::resize(size_type new_size)
		{
			vector_type_only::k_resize_using_allocator(this->alloc(), new_size);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<T, Allocator>::resize(size_type new_size, const_reference value)
		{
			vector_type_only::k_resize_using_allocator(this->alloc(), new_size, value);
		}

		template <typename T, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<T, Allocator>::swap(vector & with)
			KERBAL_CONDITIONAL_NOEXCEPT(
				noexcept(
					vector_allocator_overload::k_swap_allocator_if_propagate(
						kerbal::utility::declval<vector_allocator_overload &>(),
						kerbal::utility::declval<vector_allocator_overload &>()
					)
				) &&
				noexcept(
					vector_type_only::k_swap_type_unrelated(
						kerbal::utility::declval<vector_type_only &>(),
						kerbal::utility::declval<vector_type_only &>()
					)
				)
			)
		{
			vector_allocator_overload::k_swap_allocator_if_propagate(
				static_cast<vector_allocator_overload &>(*this),
				static_cast<vector_allocator_overload &>(with)
			);
			vector_type_only::k_swap_type_unrelated(
				static_cast<vector_type_only &>(*this),
				static_cast<vector_type_only &>(with)
			);
		}

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_VECTOR_VECTOR_IMPL_HPP
