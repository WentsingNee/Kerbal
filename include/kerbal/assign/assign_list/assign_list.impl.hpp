/**
 * @file       assign_list.impl.hpp
 * @brief
 * @date       2024-01-23
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ASSIGN_ASSIGN_LIST_ASSIGN_LIST_IMPL_HPP
#define KERBAL_ASSIGN_ASSIGN_LIST_ASSIGN_LIST_IMPL_HPP

#include <kerbal/assign/assign_list/assign_list.decl.hpp>
#include <kerbal/container/detail/vector_base/vector_base.impl.hpp>

#include <kerbal/compatibility/noexcept.hpp>


namespace kerbal
{

	namespace assign
	{

		template <typename T>
		assign_list<T>::assign_list()
		{
			v.k_reserve_using_allocator(this->alloc(), 20);
		}

		template <typename T>
		assign_list<T>::~assign_list() KERBAL_NOEXCEPT
		{
			v.template k_destroy_using_allocator(this->alloc());
		}

		template <typename T>
		assign_list<T> &
		assign_list<T>::operator,(const_reference val)
		{
			v.k_push_back_using_allocator(this->alloc(), val);
			return *this;
		}

		template <typename T>
		typename assign_list<T>::iterator
		assign_list<T>::begin()
		{
			return v.begin();
		}

		template <typename T>
		typename assign_list<T>::iterator
		assign_list<T>::end()
		{
			return v.end();
		}

		template <typename T>
		typename assign_list<T>::const_iterator
		assign_list<T>::begin() const
		{
			return v.begin();
		}

		template <typename T>
		typename assign_list<T>::const_iterator
		assign_list<T>::end() const
		{
			return v.end();
		}

		template <typename T>
		typename assign_list<T>::const_iterator
		assign_list<T>::cbegin() const
		{
			return v.begin();
		}

		template <typename T>
		typename assign_list<T>::const_iterator
		assign_list<T>::cend() const
		{
			return v.end();
		}

	} // namespace assign

} // namespace kerbal

#endif // KERBAL_ASSIGN_ASSIGN_LIST_ASSIGN_LIST_IMPL_HPP
