/**
 * @file       list_base.hpp
 * @brief
 * @date       2020-6-13
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_LIST_BASE_HPP
#define KERBAL_CONTAINER_DETAIL_LIST_BASE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/type_traits/can_be_empty_base.hpp>
#include <kerbal/type_traits/cv_deduction.hpp>

#include <kerbal/container/impl/list_node.impl.hpp>

namespace kerbal
{

	namespace container
	{

		template <typename Tp, typename Allocator>
		class list;

		namespace detail
		{

			template <typename Tp, typename Allocator>
			struct list_node_allocator_helper
			{
				private:
					typedef Tp														value_type;
					typedef kerbal::container::detail::list_node<value_type>		node;
					typedef kerbal::memory::allocator_traits<Allocator>				tp_allocator_traits;

				public:
					typedef typename tp_allocator_traits::template rebind_alloc<node>::other	type;
			};

			template <typename Tp, typename Allocator, bool allocator_can_be_empty_base =
								kerbal::type_traits::can_be_empty_base<Allocator>::value >
			class list_base;

			template <typename Tp, typename Allocator>
			class list_base<Tp, Allocator, false>
			{
					friend class kerbal::container::list<Tp, Allocator>;

				public:
					typedef Tp							value_type;

				private:
					typedef kerbal::container::detail::list_node_base					node_base;
					typedef typename list_node_allocator_helper<Tp, Allocator>::type	node_allocator_type;

				protected:
					node_base head_node;
					node_allocator_type node_allocator;

					KERBAL_CONSTEXPR
					list_base()
								KERBAL_CONDITIONAL_NOEXCEPT(
										std::is_nothrow_default_constructible<node_allocator_type>::value
								)
							: head_node(), node_allocator()
					{
					}

					KERBAL_CONSTEXPR
					explicit list_base(init_list_node_ptr_to_self_tag tag)
								KERBAL_CONDITIONAL_NOEXCEPT(
										std::is_nothrow_default_constructible<node_allocator_type>::value
								)
							: head_node(tag), node_allocator()
					{
					}

					KERBAL_CONSTEXPR
					explicit list_base(const Allocator & allocator) KERBAL_NOEXCEPT
							: head_node(), node_allocator(allocator)
					{
					}

					KERBAL_CONSTEXPR
					explicit list_base(init_list_node_ptr_to_self_tag tag, const Allocator & allocator) KERBAL_NOEXCEPT
							: head_node(tag), node_allocator(allocator)
					{
					}

#	if __cplusplus >= 201103L

					KERBAL_CONSTEXPR
					explicit list_base(Allocator && allocator) KERBAL_NOEXCEPT
							: head_node(), node_allocator(kerbal::compatibility::move(allocator))
					{
					}

					KERBAL_CONSTEXPR
					explicit list_base(init_list_node_ptr_to_self_tag tag, Allocator && allocator) KERBAL_NOEXCEPT
							: head_node(tag), node_allocator(kerbal::compatibility::move(allocator))
					{
					}

#	endif

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
			class list_base<Tp, Allocator, true>:
								kerbal::type_traits::remove_cv<
										typename list_node_allocator_helper<Tp, Allocator>::type
								>::type
			{
					friend class kerbal::container::list<Tp, Allocator>;

				private:
					typedef typename kerbal::type_traits::remove_cv<
							typename list_node_allocator_helper<Tp, Allocator>::type
					>::type super;

				public:
					typedef Tp							value_type;

				private:
					typedef kerbal::container::detail::list_node_base					node_base;
					typedef typename list_node_allocator_helper<Tp, Allocator>::type	node_allocator_type;

				protected:
					node_base head_node;

					KERBAL_CONSTEXPR
					list_base()
								KERBAL_CONDITIONAL_NOEXCEPT(
										std::is_nothrow_default_constructible<super>::value
								)
							: head_node(), super()
					{
					}

					KERBAL_CONSTEXPR
					explicit list_base(init_list_node_ptr_to_self_tag tag)
								KERBAL_CONDITIONAL_NOEXCEPT(
										std::is_nothrow_default_constructible<super>::value
								)
							: head_node(tag), super()
					{
					}

					KERBAL_CONSTEXPR
					explicit list_base(const Allocator & allocator) KERBAL_NOEXCEPT
							: head_node(), super(allocator)
					{
					}

					KERBAL_CONSTEXPR
					explicit list_base(init_list_node_ptr_to_self_tag tag, const Allocator & allocator) KERBAL_NOEXCEPT
							: head_node(tag), super()
					{
					}

#	if __cplusplus >= 201103L

					KERBAL_CONSTEXPR
					explicit list_base(Allocator && allocator) KERBAL_NOEXCEPT
							: head_node(), super(kerbal::compatibility::move(allocator))
					{
					}

					KERBAL_CONSTEXPR
					explicit list_base(init_list_node_ptr_to_self_tag tag, Allocator && allocator) KERBAL_NOEXCEPT
							: head_node(tag), super(kerbal::compatibility::move(allocator))
					{
					}

#	endif

					KERBAL_CONSTEXPR14
					node_allocator_type& alloc() KERBAL_NOEXCEPT
					{
						return static_cast<node_allocator_type&>(*this);
					}

					KERBAL_CONSTEXPR14
					const node_allocator_type& alloc() const KERBAL_NOEXCEPT
					{
						return static_cast<const node_allocator_type&>(*this);
					}

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_LIST_BASE_HPP
