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

#ifndef KERBAL_CONTAINER_IMPL_VECTOR_IMPL_HPP
#define KERBAL_CONTAINER_IMPL_VECTOR_IMPL_HPP

#include <kerbal/container/detail/vector_base.hpp>

#include <kerbal/compatibility/move.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/memory/uninitialized.hpp>
#include <kerbal/memory/uninitialized_using_allocator.hpp>
#include <kerbal/type_traits/enable_if.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

#if __cplusplus >= 201103L
#	include <type_traits>
#endif


namespace kerbal
{

	namespace container
	{

	//===================
	// construct/copy/destroy

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>::vector()
				KERBAL_CONDITIONAL_NOEXCEPT(
						std::is_nothrow_default_constructible<vector_allocator_overload>::value &&
						std::is_nothrow_default_constructible<vector_allocator_unrelated>::value
				) :
				vector_allocator_overload(),
				vector_allocator_unrelated()
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>::vector(const Allocator & allocator)
				KERBAL_CONDITIONAL_NOEXCEPT((
						std::is_nothrow_constructible<vector_allocator_overload, const Allocator &>::value &&
						std::is_nothrow_default_constructible<vector_allocator_unrelated>::value
				)) :
				vector_allocator_overload(allocator),
				vector_allocator_unrelated()
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>::vector(size_type count) :
				vector_allocator_overload(),
				vector_allocator_unrelated(this->alloc(), count)
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>::vector(size_type count, const Allocator & allocator) :
				vector_allocator_overload(allocator),
				vector_allocator_unrelated(this->alloc(), count)
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>::vector(size_type count, const_reference value) :
				vector_allocator_overload(),
				vector_allocator_unrelated(this->alloc(), count, value)
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>::vector(size_type count, const_reference value, const Allocator & allocator) :
				vector_allocator_overload(allocator),
				vector_allocator_unrelated(this->alloc(), count, value)
		{
		}


		template <typename Tp, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>::vector(InputIterator first, InputIterator last,
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
						, int
				>::type
		) :
				vector_allocator_overload(),
				vector_allocator_unrelated(this->alloc(), first, last)
		{
		}

		template <typename Tp, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>::vector(InputIterator first, InputIterator last, const Allocator & allocator,
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
						, int
				>::type
		) :
				vector_allocator_overload(allocator),
				vector_allocator_unrelated(this->alloc(), first, last)
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>::vector(const vector & src) :
				vector_allocator_overload(src.alloc()),
				vector_allocator_unrelated(this->alloc(), src.cbegin().current, src.cend().current)
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>::vector(const vector & src, const Allocator & allocator) :
				vector_allocator_overload(allocator),
				vector_allocator_unrelated(this->alloc(), src.cbegin().current, src.cend().current)
		{
		}


#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>::vector(vector && src)
				KERBAL_CONDITIONAL_NOEXCEPT((
						std::is_nothrow_constructible<vector_allocator_overload, Allocator &&>::value &&
						std::is_nothrow_constructible<vector_allocator_unrelated, vector_allocator_unrelated &&>::value
				)) :
				vector_allocator_overload(kerbal::compatibility::move(src.alloc())),
				vector_allocator_unrelated(static_cast<vector_allocator_unrelated &&>(src))
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>::vector(vector && src, const Allocator & allocator)
				KERBAL_CONDITIONAL_NOEXCEPT((
						std::is_nothrow_constructible<vector_allocator_overload, const Allocator &>::value &&
						std::is_nothrow_constructible<vector_allocator_unrelated, Allocator &, Allocator &&, vector_allocator_unrelated &&>::value
				)) :
				vector_allocator_overload(allocator),
				vector_allocator_unrelated(this->alloc(), static_cast<Allocator &&>(src.alloc()), static_cast<vector_allocator_unrelated &&>(src))
		{
		}

#	endif


#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>::vector(std::initializer_list<value_type> ilist) :
				vector(ilist.begin(), ilist.end())
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>::vector(std::initializer_list<value_type> ilist, const Allocator & allocator) :
				vector(ilist.begin(), ilist.end(), allocator)
		{
		}

#	else

		template <typename Tp, typename Allocator>
		template <typename Up>
		vector<Tp, Allocator>::vector(const kerbal::assign::assign_list<Up> & ilist) :
				vector_allocator_overload(),
				vector_allocator_unrelated(this->alloc(), ilist.cbegin(), ilist.cend())
		{
		}

		template <typename Tp, typename Allocator>
		template <typename Up>
		vector<Tp, Allocator>::vector(const kerbal::assign::assign_list<Up> & ilist, const Allocator & allocator) :
				vector_allocator_overload(allocator),
				vector_allocator_unrelated(this->alloc(), ilist.cbegin(), ilist.cend())
		{
		}

#	endif



		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>::~vector()
		{
			vector_allocator_unrelated::destroy_using_allocator(this->alloc());
		}



	//===================
	// assign

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>&
		vector<Tp, Allocator>::operator=(const vector & src)
		{
			this->assign(src);
			return *this;
		}

#		if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>&
		vector<Tp, Allocator>::operator=(vector && src)
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(kerbal::utility::declthis<vector>()->assign(kerbal::compatibility::move(src)))
				)
		{
			this->assign(kerbal::compatibility::move(src));
			return *this;
		}

#		endif

#		if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>&
		vector<Tp, Allocator>::operator=(std::initializer_list<value_type> ilist)
		{
			this->assign(ilist.begin(), ilist.end());
			return *this;
		}

#		else

		template <typename Tp, typename Allocator>
		template <typename Up>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>&
		vector<Tp, Allocator>::operator=(const kerbal::assign::assign_list<Up> & ilist)
		{
			this->assign(ilist.begin(), ilist.end());
			return *this;
		}

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<Tp, Allocator>::assign(size_type new_size, const_reference value)
		{
			vector_allocator_unrelated::assign_using_allocator(this->alloc(), new_size, value);
		}

		template <typename Tp, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
		>::type
		vector<Tp, Allocator>::assign(InputIterator first, InputIterator last)
		{
			vector_allocator_unrelated::assign_using_allocator(this->alloc(), first, last);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<Tp, Allocator>::assign(const vector & src)
		{
			this->vector_allocator_unrelated::assign_using_allocator(
					this->alloc(),
					src.alloc(),
					static_cast<const vector_allocator_unrelated &>(src)
			);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<Tp, Allocator>::assign(vector && src)
				KERBAL_CONDITIONAL_NOEXCEPT(noexcept(
						kerbal::utility::declthis<vector_allocator_unrelated>()->assign_using_allocator(
								kerbal::utility::declthis<vector>()->alloc(),
								kerbal::compatibility::move(kerbal::utility::declval<vector &&>().alloc()),
								kerbal::utility::declval<vector_allocator_unrelated &&>()
						)
				))
		{
			this->vector_allocator_unrelated::assign_using_allocator(
					this->alloc(),
					kerbal::compatibility::move(src.alloc()),
					static_cast<vector_allocator_unrelated &&>(src)
			);
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<Tp, Allocator>::assign(std::initializer_list<value_type> ilist)
		{
			this->assign(ilist.begin(), ilist.end());
		}

#	else

		template <typename Tp, typename Allocator>
		template <typename Up>
		KERBAL_CONSTEXPR20
		void vector<Tp, Allocator>::assign(const kerbal::assign::assign_list<Up> & ilist)
		{
			this->assign(ilist.cbegin(), ilist.cend());
		}

#	endif



	//===================
	// capacity

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<Tp, Allocator>::reserve(size_type new_capacity)
		{
			vector_allocator_unrelated::reserve_using_allocator(this->alloc(), new_capacity);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<Tp, Allocator>::shrink_to_fit()
		{
			vector_allocator_unrelated::shrink_to_fit_using_allocator(this->alloc());
		}


	//===================
	// insert

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename vector<Tp, Allocator>::iterator
		vector<Tp, Allocator>::emplace(const_iterator pos, Args&& ... args)
		{
			return vector_allocator_unrelated::emplace_using_allocator(this->alloc(), pos, kerbal::utility::forward<Args>(args)...);
		}

#	else

		template <typename Tp, typename Allocator>
		typename vector<Tp, Allocator>::iterator
		vector<Tp, Allocator>::emplace(const_iterator pos)
		{
			return vector_allocator_unrelated::emplace_using_allocator(this->alloc(), pos);
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0>
		typename vector<Tp, Allocator>::iterator
		vector<Tp, Allocator>::emplace(const_iterator pos, const Arg0 & arg0)
		{
			return vector_allocator_unrelated::emplace_using_allocator(this->alloc(), pos, arg0);
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1>
		typename vector<Tp, Allocator>::iterator
		vector<Tp, Allocator>::emplace(const_iterator pos, const Arg0 & arg0, const Arg1& arg1)
		{
			return vector_allocator_unrelated::emplace_using_allocator(this->alloc(), pos, arg0, arg1);
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1, typename Arg2>
		typename vector<Tp, Allocator>::iterator
		vector<Tp, Allocator>::emplace(const_iterator pos, const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2)
		{
			return vector_allocator_unrelated::emplace_using_allocator(this->alloc(), pos, arg0, arg1, arg2);
		}

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename vector<Tp, Allocator>::iterator
		vector<Tp, Allocator>::insert(const_iterator pos, const_reference val)
		{
			return vector_allocator_unrelated::insert_using_allocator(this->alloc(), pos, val);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename vector<Tp, Allocator>::iterator
		vector<Tp, Allocator>::insert(const_iterator pos, rvalue_reference val)
		{
			return vector_allocator_unrelated::insert_using_allocator(this->alloc(), pos, kerbal::compatibility::move(val));
		}

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename vector<Tp, Allocator>::iterator
		vector<Tp, Allocator>::insert(const_iterator pos, size_type n, const_reference val)
		{
			return vector_allocator_unrelated::insert_using_allocator(this->alloc(), pos, n, val);
		}

		template <typename Tp, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
				typename vector<Tp, Allocator>::iterator
		>::type
		vector<Tp, Allocator>::insert(const_iterator pos, InputIterator first, InputIterator last)
		{
			return vector_allocator_unrelated::insert_using_allocator(this->alloc(), pos, first, last);
		}

#		if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename vector<Tp, Allocator>::iterator
		vector<Tp, Allocator>::insert(const_iterator pos, std::initializer_list<value_type> ilist)
		{
			return this->insert(pos, ilist.begin(), ilist.end());
		}

#		else

		template <typename Tp, typename Allocator>
		template <typename Up>
		typename vector<Tp, Allocator>::iterator
		vector<Tp, Allocator>::insert(const_iterator pos, const kerbal::assign::assign_list<Up> & ilist)
		{
			return this->insert(pos, ilist.cbegin(), ilist.cend());
		}

#		endif



#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename vector<Tp, Allocator>::reference
		vector<Tp, Allocator>::emplace_back(Args&& ... args)
		{
			return vector_allocator_unrelated::emplace_back_using_allocator(this->alloc(), kerbal::utility::forward<Args>(args)...);
		}

#	else

		template <typename Tp, typename Allocator>
		typename vector<Tp, Allocator>::reference
		vector<Tp, Allocator>::emplace_back()
		{
			return vector_allocator_unrelated::emplace_back_using_allocator(this->alloc());
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0>
		typename vector<Tp, Allocator>::reference
		vector<Tp, Allocator>::emplace_back(const Arg0 & arg0)
		{
			return vector_allocator_unrelated::emplace_back_using_allocator(this->alloc(), arg0);
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1>
		typename vector<Tp, Allocator>::reference
		vector<Tp, Allocator>::emplace_back(const Arg0 & arg0, const Arg1& arg1)
		{
			return vector_allocator_unrelated::emplace_back_using_allocator(this->alloc(), arg0, arg1);
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1, typename Arg2>
		typename vector<Tp, Allocator>::reference
		vector<Tp, Allocator>::emplace_back(const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2)
		{
			return vector_allocator_unrelated::emplace_back_using_allocator(this->alloc(), arg0, arg1, arg2);
		}

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<Tp, Allocator>::push_back(const_reference src)
		{
			vector_allocator_unrelated::push_back_using_allocator(this->alloc(), src);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<Tp, Allocator>::push_back(rvalue_reference src)
		{
			vector_allocator_unrelated::push_back_using_allocator(this->alloc(), kerbal::compatibility::move(src));
		}

#	endif


	//===================
	// erase

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename vector<Tp, Allocator>::iterator
		vector<Tp, Allocator>::erase(const_iterator pos)
		{
			return vector_allocator_unrelated::erase_using_allocator(this->alloc(), pos);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename vector<Tp, Allocator>::iterator
		vector<Tp, Allocator>::erase(const_iterator first, const_iterator last)
		{
			return vector_allocator_unrelated::erase_using_allocator(this->alloc(), first, last);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<Tp, Allocator>::pop_back() KERBAL_NOEXCEPT
		{
			vector_allocator_unrelated::pop_back_using_allocator(this->alloc());
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<Tp, Allocator>::clear() KERBAL_NOEXCEPT
		{
			vector_allocator_unrelated::clear_using_allocator(this->alloc());
		}


	//===================
	// operation

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<Tp, Allocator>::resize(size_type new_size)
		{
			vector_allocator_unrelated::resize_using_allocator(this->alloc(), new_size);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<Tp, Allocator>::resize(size_type new_size, const_reference value)
		{
			vector_allocator_unrelated::resize_using_allocator(this->alloc(), new_size, value);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<Tp, Allocator>::swap(vector & with)
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(vector_allocator_overload::_K_swap_allocator_if_propagate(
								kerbal::utility::declval<vector_allocator_overload&>(), kerbal::utility::declval<vector_allocator_overload&>()
						)) &&
						noexcept(vector_allocator_unrelated::_K_swap_type_unrelated(
								kerbal::utility::declval<vector_allocator_unrelated&>(), kerbal::utility::declval<vector_allocator_unrelated&>()
						))
				)
		{
			vector_allocator_overload::_K_swap_allocator_if_propagate(
					static_cast<vector_allocator_overload&>(*this),
					static_cast<vector_allocator_overload&>(with));
			vector_allocator_unrelated::_K_swap_type_unrelated(
					static_cast<vector_allocator_unrelated&>(*this),
					static_cast<vector_allocator_unrelated&>(with));
		}

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_IMPL_VECTOR_IMPL_HPP
