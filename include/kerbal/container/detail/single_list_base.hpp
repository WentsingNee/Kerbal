/**
 * @file       single_list_base.hpp
 * @brief
 * @date       2020-08-31
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_SINGLE_LIST_BASE_HPP
#define KERBAL_CONTAINER_DETAIL_SINGLE_LIST_BASE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/type_traits/can_be_empty_base.hpp>
#include <kerbal/type_traits/cv_deduction.hpp>

#include <kerbal/container/detail/single_list_node.hpp>
#include <kerbal/container/detail/single_list_iterator.hpp>

namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			class sl_type_unrelated
			{
				protected:
					typedef std::size_t					size_type;
					typedef std::ptrdiff_t				difference_type;

					typedef kerbal::container::detail::sl_node_base					node_base;
					typedef kerbal::container::detail::sl_iter_type_unrelated		basic_iterator;
					typedef kerbal::container::detail::sl_kiter_type_unrelated		basic_const_iterator;

				protected:
					node_base head_node;
					basic_iterator last_iter;

					KERBAL_CONSTEXPR14
					sl_type_unrelated() KERBAL_NOEXCEPT
							: head_node(), last_iter(this->basic_begin())
					{
					}

					KERBAL_CONSTEXPR14
					basic_iterator basic_begin() KERBAL_NOEXCEPT
					{
						return basic_iterator(&this->head_node);
					}

					KERBAL_CONSTEXPR14
					basic_const_iterator basic_begin() const KERBAL_NOEXCEPT
					{
						return basic_const_iterator(&this->head_node);
					}

					KERBAL_CONSTEXPR14
					basic_iterator basic_end() KERBAL_NOEXCEPT
					{
						return basic_iterator(this->last_iter);
					}

					KERBAL_CONSTEXPR14
					basic_const_iterator basic_end() const KERBAL_NOEXCEPT
					{
						return basic_const_iterator(this->last_iter);
					}

				//===================
				//capacity

					KERBAL_CONSTEXPR20
					bool empty() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					size_type size() const KERBAL_NOEXCEPT;

				//===================
				//operation

					KERBAL_CONSTEXPR20
					void iter_swap(basic_iterator a, basic_iterator b) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					void reverse(basic_iterator first, basic_iterator last) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					void splice(basic_iterator pos, sl_type_unrelated & other, basic_iterator opos) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					void splice(basic_iterator pos, sl_type_unrelated & other, basic_iterator first, basic_iterator last) KERBAL_NOEXCEPT;

				//===================
				//private

					KERBAL_CONSTEXPR20
					void __hook_node_back(node_base * p) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					void __hook_node_front(node_base * p) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					void __hook_node(basic_const_iterator pos, node_base * p) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					void __hook_node(basic_const_iterator pos, node_base * start, node_base * back) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					node_base * __unhook_node(basic_iterator pos) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					void __unhook_node(node_base * start, node_base * back) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					void swap_with_empty(sl_type_unrelated& not_empty_list, sl_type_unrelated& empty_list) KERBAL_NOEXCEPT;

			};

			template <typename Tp>
			class sl_allocator_unrelated:
					protected sl_type_unrelated
			{
				private:
					typedef sl_type_unrelated super;

					template <typename Up, typename Allocator>
					friend class kerbal::container::single_list;

				protected:
					typedef Tp							value_type;
					typedef const value_type			const_type;
					typedef value_type&					reference;
					typedef const value_type&			const_reference;
					typedef value_type*					pointer;
					typedef const value_type*			const_pointer;

#			if __cplusplus >= 201103L
					typedef value_type&&				rvalue_reference;
					typedef const value_type&&			const_rvalue_reference;
#			endif

					typedef std::size_t					size_type;
					typedef std::ptrdiff_t				difference_type;

					typedef kerbal::container::detail::sl_iter<Tp>			iterator;
					typedef kerbal::container::detail::sl_kiter<Tp>			const_iterator;

					typedef kerbal::container::detail::sl_node_base			node_base;
					typedef kerbal::container::detail::sl_node<value_type>	node;


				protected:

#			if __cplusplus >= 201103L

					using super::super;

#			else

					sl_allocator_unrelated() KERBAL_NOEXCEPT
							: super()
					{
					}

#			endif

				//===================
				//element access

					KERBAL_CONSTEXPR20
					reference front() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_reference front() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					reference back() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_reference back() const KERBAL_NOEXCEPT;

				//===================
				//iterator

					KERBAL_CONSTEXPR20
					iterator begin() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					iterator end() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_iterator begin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_iterator end() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_iterator cbegin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_iterator cend() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					iterator nth(size_type index) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_iterator nth(size_type index) const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					size_type index_of(iterator it) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					size_type index_of(const_iterator it) const KERBAL_NOEXCEPT;

				//===================
				//capacity

					KERBAL_CONSTEXPR
					size_type max_size() const KERBAL_NOEXCEPT
					{
						return static_cast<size_type>(-1);
					}

				//===================
				//operation

					KERBAL_CONSTEXPR20
					void iter_swap_unstable(iterator a, iterator b);

					KERBAL_CONSTEXPR20
					void iter_swap(iterator a, iterator b) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					void iter_swap_fast(iterator a, iterator b);

					KERBAL_CONSTEXPR20
					void swap_allocator_unrelated(sl_allocator_unrelated & ano) KERBAL_NOEXCEPT;

			};

			template <typename Tp, typename Allocator>
			struct sl_node_allocator_helper
			{
				private:
					typedef Tp														value_type;
					typedef kerbal::container::detail::sl_node<value_type>			node;
					typedef kerbal::memory::allocator_traits<Allocator>				tp_allocator_traits;

				public:
					typedef typename tp_allocator_traits::template rebind_alloc<node>::other	type;
			};

			template <typename Tp, typename Allocator, bool allocator_can_be_empty_base =
								kerbal::type_traits::can_be_empty_base<Allocator>::value >
			class sl_allocator_overload;

			template <typename Tp, typename Allocator>
			class sl_allocator_overload<Tp, Allocator, false>
			{
				protected:
					typedef typename sl_node_allocator_helper<Tp, Allocator>::type	node_allocator_type;

				protected:
					node_allocator_type node_allocator;

					KERBAL_CONSTEXPR
					sl_allocator_overload()
								KERBAL_CONDITIONAL_NOEXCEPT(
										std::is_nothrow_default_constructible<node_allocator_type>::value
								)
							: node_allocator()
					{
					}

					KERBAL_CONSTEXPR
					explicit sl_allocator_overload(const Allocator & allocator)
								KERBAL_CONDITIONAL_NOEXCEPT(
										(std::is_nothrow_constructible<node_allocator_type, const Allocator&>::value)
								)
							: node_allocator(allocator)
					{
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR
					explicit sl_allocator_overload(Allocator && allocator)
								KERBAL_CONDITIONAL_NOEXCEPT(
										(std::is_nothrow_constructible<node_allocator_type, Allocator&&>::value)
								)
							: node_allocator(kerbal::compatibility::move(allocator))
					{
					}

#			endif

					KERBAL_CONSTEXPR14
					node_allocator_type& alloc() KERBAL_NOEXCEPT
					{
						return this->node_allocator;
					}

					KERBAL_CONSTEXPR14
					const node_allocator_type& alloc() const KERBAL_NOEXCEPT
					{
						return this->node_allocator;
					}

			};

			template <typename Tp, typename Allocator>
			class sl_allocator_overload<Tp, Allocator, true>:
					private kerbal::type_traits::remove_cv<
							typename sl_node_allocator_helper<Tp, Allocator>::type
					>::type
			{
				private:
					typedef typename kerbal::type_traits::remove_cv<
							typename sl_node_allocator_helper<Tp, Allocator>::type
					>::type super;

				protected:
					typedef typename sl_node_allocator_helper<Tp, Allocator>::type	node_allocator_type;

				protected:

					KERBAL_CONSTEXPR
					sl_allocator_overload()
								KERBAL_CONDITIONAL_NOEXCEPT(
										std::is_nothrow_default_constructible<super>::value
								)
							: super()
					{
					}

					KERBAL_CONSTEXPR
					explicit sl_allocator_overload(const Allocator & allocator)
								KERBAL_CONDITIONAL_NOEXCEPT(
										(std::is_nothrow_constructible<super, const Allocator&>::value)
								)
							: super(allocator)
					{
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR
					explicit sl_allocator_overload(Allocator && allocator)
								KERBAL_CONDITIONAL_NOEXCEPT(
										(std::is_nothrow_constructible<super, Allocator&&>::value)
								)
							: super(kerbal::compatibility::move(allocator))
					{
					}

#			endif

					KERBAL_CONSTEXPR14
					node_allocator_type& alloc() KERBAL_NOEXCEPT
					{
						return static_cast<super&>(*this);
					}

					KERBAL_CONSTEXPR14
					const node_allocator_type& alloc() const KERBAL_NOEXCEPT
					{
						return static_cast<const super&>(*this);
					}

			};


		} // namespace detail

	} // namespace container

} // namespace kerbal

#include <kerbal/container/impl/single_list_base.impl.hpp>

#endif // KERBAL_CONTAINER_DETAIL_SINGLE_LIST_BASE_HPP
