/**
 * @file       list_node.hpp
 * @brief
 * @date       2020-03-21
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_LIST_BASE_LIST_NODE_HPP
#define KERBAL_CONTAINER_DETAIL_LIST_BASE_LIST_NODE_HPP

#include <kerbal/container/detail/list_base/list_base.fwd.hpp>
#include <kerbal/autonm/list/list.fwd.hpp>
#include <kerbal/container/list/list.fwd.hpp>

#include <kerbal/algorithm/modifier.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/method_overload_tag.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/utility/in_place.hpp>
#include <kerbal/utility/noncopyable.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/integral_constant.hpp>
#	include <kerbal/utility/forward.hpp>
#	include <kerbal/utility/integer_sequence.hpp>
#endif

#include <cstddef>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			struct init_list_node_ptr_to_self_tag
			{
			};

			class list_node_base: private kerbal::utility::noncopyable
			{
				private:
					friend class kerbal::container::detail::list_type_unrelated;

					template <typename Tp>
					friend class kerbal::container::detail::list_allocator_unrelated;

					template <typename Tp, typename SemiAllocator>
					friend class kerbal::autonm::list;

					template <typename Tp>
					friend class list_iter;

					template <typename Tp>
					friend class list_kiter;

				public:
					list_node_base* prev;
					list_node_base* next;

				protected:
					KERBAL_CONSTEXPR
					list_node_base() KERBAL_NOEXCEPT :
							prev(NULL), next(NULL)
					{
					}

					KERBAL_CONSTEXPR
					explicit list_node_base(init_list_node_ptr_to_self_tag) KERBAL_NOEXCEPT :
							prev(this), next(this)
					{
					}

					template <typename Tp>
					KERBAL_CONSTEXPR14
					list_node<Tp> & reinterpret_as() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return static_cast<list_node<Tp> &>(*this);
					}

					template <typename Tp>
					KERBAL_CONSTEXPR14
					const list_node<Tp> & reinterpret_as() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return static_cast<const list_node<Tp> &>(*this);
					}

#			if __cplusplus >= 201103L

					template <typename Tp>
					KERBAL_CONSTEXPR14
					list_node<Tp> && reinterpret_as() && KERBAL_NOEXCEPT
					{
						return static_cast<list_node<Tp> &&>(*this);
					}

					template <typename Tp>
					KERBAL_CONSTEXPR14
					const list_node<Tp> && reinterpret_as() const && KERBAL_NOEXCEPT
					{
						return static_cast<const list_node<Tp> &&>(*this);
					}

#			endif

			};

			template <typename Tp>
			class list_node: public list_node_base
			{
				private:
					typedef list_node_base super;

				public:
					Tp value;

				public:

#		if __cplusplus >= 201103L

					template <typename ... Args>
					KERBAL_CONSTEXPR
					explicit list_node(kerbal::utility::in_place_t, Args&& ... args)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<Tp, Args&&...>::value)
										)
							: super(), value(kerbal::utility::forward<Args>(args)...)
					{
					}

#		else

#				define EMPTY
#				define REMAINF(exp) exp
#				define LEFT_JOIN_COMMA(exp) , exp
#				define THEAD_NOT_EMPTY(exp) template <exp>
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
					explicit list_node(kerbal::utility::in_place_t KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
							: super(), value(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i)) \
					{ \
					}

					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#				undef EMPTY
#				undef REMAINF
#				undef LEFT_JOIN_COMMA
#				undef THEAD_NOT_EMPTY
#				undef TARGS_DECL
#				undef ARGS_DECL
#				undef ARGS_USE
#				undef FBODY

#		endif

			};

			template <typename Tp, std::size_t N>
			class list_node<Tp[N]>: public list_node_base
			{
				private:
					typedef list_node_base super;

				public:
					Tp value[N];

#		if __cplusplus >= 201103L

				private:

					typedef kerbal::type_traits::integral_constant<std::size_t, 32> BRACE_INIT_LIMIT;

					template <typename Up, std::size_t ... I>
					KERBAL_CONSTEXPR
					explicit list_node(const Up (&arg)[N], kerbal::utility::integer_sequence<std::size_t, I...>)
							: super(), value{arg[I]...}
					{
					}

					template <typename Up>
					KERBAL_CONSTEXPR
					explicit list_node(const Up (&arg) [N], kerbal::type_traits::true_type) // for N < BRACE_INIT_LIMIT
							: list_node(arg, kerbal::utility::make_index_sequence<N>())
					{
					}

					template <typename Up>
					KERBAL_CONSTEXPR14
					explicit list_node(const Up (&arg) [N], kerbal::type_traits::false_type) // for N >= BRACE_INIT_LIMIT
							: list_node(arg, kerbal::utility::make_index_sequence<BRACE_INIT_LIMIT::value>())
					{
						kerbal::algorithm::copy(arg + BRACE_INIT_LIMIT::value, arg + N, this->value + BRACE_INIT_LIMIT::value);
					}

				public:

					KERBAL_CONSTEXPR
					explicit list_node(kerbal::utility::in_place_t)
							: super(), value{}
					{
					}

					template <typename Up>
					KERBAL_CONSTEXPR
					explicit list_node(kerbal::utility::in_place_t, const Up (&arg) [N])
							: list_node(arg, kerbal::type_traits::bool_constant<N < BRACE_INIT_LIMIT::value>())
					{
					}

#		else

				public:

					explicit list_node(kerbal::utility::in_place_t)
							: super()
					{
					}

					template <typename Up>
					explicit list_node(kerbal::utility::in_place_t, const Up (&arg) [N])
							: super()
					{
						kerbal::algorithm::copy(arg, arg + N, this->value);
					}

#		endif

			};

			struct list_node_base_chain
			{
					list_node_base * start;
					list_node_base * back;

					KERBAL_CONSTEXPR
					list_node_base_chain(list_node_base * start, list_node_base * back) KERBAL_NOEXCEPT :
							start(start), back(back)
					{
					}

			};

			template <typename Tp>
			struct list_node_chain
			{
					list_node<Tp> * start;
					list_node<Tp> * back;

					KERBAL_CONSTEXPR
					list_node_chain(list_node<Tp> * start, list_node<Tp> * back) KERBAL_NOEXCEPT :
							start(start), back(back)
					{
					}

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_LIST_BASE_LIST_NODE_HPP
