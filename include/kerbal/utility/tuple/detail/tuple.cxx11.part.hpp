/**
 * @file       tuple.cxx11.part.hpp
 * @brief
 * @date       2020-07-22
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_TUPLE_DETAIL_TUPLE_CXX11_PART_HPP
#define KERBAL_UTILITY_TUPLE_DETAIL_TUPLE_CXX11_PART_HPP

#if __cplusplus < 201103L
#	error This file requires compiler and library support for the ISO C++ 2011 standard.
#endif

#include <kerbal/utility/tuple/tuple.fwd.hpp>

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/tmp/type_vector.hpp>
#include <kerbal/type_traits/add_const_lvalue_reference.hpp>
#include <kerbal/type_traits/add_const_rvalue_reference.hpp>
#include <kerbal/type_traits/add_lvalue_reference.hpp>
#include <kerbal/type_traits/add_rvalue_reference.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_nothrow_constructible.hpp>
#include <kerbal/type_traits/is_nothrow_default_constructible.hpp>
#include <kerbal/type_traits/logical.hpp>
#include <kerbal/type_traits/remove_const.hpp>
#include <kerbal/type_traits/remove_cvref.hpp>
#include <kerbal/type_traits/remove_reference.hpp>
#include <kerbal/type_traits/tribool_constant.hpp>
#include <kerbal/utility/declval.hpp>
#include <kerbal/utility/forward.hpp>
#include <kerbal/utility/ignore_unused.hpp>
#include <kerbal/utility/integer_sequence.hpp>
#include <kerbal/utility/member_compress_helper.hpp>
#include <kerbal/utility/piecewise_construct.hpp>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif

#include <cstddef>


namespace kerbal
{

	namespace utility
	{

		namespace detail
		{

			template <typename IndexSequence, typename ... Args>
			struct tuple_impl;


			template <typename TupleImpl, typename HeadIndexSequence, typename TailIndexSequence, typename ... UArgs>
			struct tuple_impl_is_nothrow_partially_init_constructible_helper;

			template <typename TupleImpl, std::size_t ... HeadIndex, std::size_t ... TailIndex, typename ... UArgs>
			struct tuple_impl_is_nothrow_partially_init_constructible_helper<
				TupleImpl,
				kerbal::utility::index_sequence<HeadIndex...>,
				kerbal::utility::index_sequence<TailIndex...>,
				UArgs...
			>
			{
				private:
					typedef TupleImpl k_tuple_impl;

					typedef typename kerbal::type_traits::tribool_conjunction<
						kerbal::type_traits::try_test_is_nothrow_constructible<
							typename k_tuple_impl::template super<HeadIndex>::type,
							kerbal::utility::in_place_t,
							UArgs &&
						>...
					>::result::IS_TRUE is_head_nothrow_constructible;

					typedef typename kerbal::type_traits::tribool_conjunction<
						kerbal::type_traits::try_test_is_nothrow_constructible<
							typename k_tuple_impl::template super<TailIndex + sizeof...(HeadIndex)>::type,
							kerbal::utility::in_place_t
						>...
					>::result::IS_TRUE is_tail_nothrow_constructible;

				public:
					typedef kerbal::type_traits::conjunction<
						is_head_nothrow_constructible,
						is_tail_nothrow_constructible
					> type;
			};


			template <std::size_t ... Index, typename ... Args>
			struct tuple_impl<kerbal::utility::index_sequence<Index...>, Args...> :
				public kerbal::utility::member_compress_helper<Args, Index>...
			{
				public:
					typedef kerbal::type_traits::integral_constant<std::size_t, sizeof...(Args)> TUPLE_SIZE;

					template <std::size_t I>
					struct value_type
					{
						private:
							KERBAL_STATIC_ASSERT(I < TUPLE_SIZE::value, "Index out of range");

						public:
							typedef typename kerbal::tmp::type_vector_at<
								kerbal::tmp::type_vector<Args...>, I
							>::result type;
					};

				private:

					template <std::size_t I>
					struct super
					{
						private:
							KERBAL_STATIC_ASSERT(I < TUPLE_SIZE::value, "Index out of range");

						public:
							typedef kerbal::utility::member_compress_helper<typename value_type<I>::type, I> type;
					};

				public:

					template <std::size_t I>
					struct const_type
					{
						private:
							KERBAL_STATIC_ASSERT(I < TUPLE_SIZE::value, "Index out of range");

						public:
							typedef const typename value_type<I>::type type;
					};

					template <std::size_t I>
					struct reference
					{
						private:
							KERBAL_STATIC_ASSERT(I < TUPLE_SIZE::value, "Index out of range");

						public:
							typedef typename kerbal::type_traits::add_lvalue_reference<
								typename value_type<I>::type
							>::type type;
					};

					template <std::size_t I>
					struct const_reference
					{
						private:
							KERBAL_STATIC_ASSERT(I < TUPLE_SIZE::value, "Index out of range");

						public:
							typedef typename kerbal::type_traits::add_const_lvalue_reference<
								typename value_type<I>::type
							>::type type;
					};

					template <std::size_t I>
					struct rvalue_reference
					{
						private:
							KERBAL_STATIC_ASSERT(I < TUPLE_SIZE::value, "Index out of range");

						public:
							typedef typename kerbal::type_traits::add_rvalue_reference<
								typename value_type<I>::type
							>::type type;
					};

					template <std::size_t I>
					struct const_rvalue_reference
					{
						private:
							KERBAL_STATIC_ASSERT(I < TUPLE_SIZE::value, "Index out of range");

						public:
							typedef typename kerbal::type_traits::add_const_rvalue_reference<
								typename value_type<I>::type
							>::type type;
					};


				protected:

					struct is_nothrow_default_constructible :
						kerbal::type_traits::tribool_conjunction<
							kerbal::type_traits::try_test_is_nothrow_default_constructible<typename super<Index>::type>...
						>::result::IS_TRUE
					{
					};

				public:

					KERBAL_CONSTEXPR
					tuple_impl() KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_default_constructible::value) :
						super<Index>::type(kerbal::utility::in_place_t())...
					{
					}


				protected:

					template <typename TupleImpl, typename HeadIndexSequence, typename TailIndexSequence, typename ... UArgs>
					friend struct tuple_impl_is_nothrow_partially_init_constructible_helper;

					template <typename ... UArgs>
					struct is_nothrow_partially_init_constructible :
						tuple_impl_is_nothrow_partially_init_constructible_helper<
							tuple_impl,
							kerbal::utility::make_index_sequence<sizeof...(UArgs)>,
							kerbal::utility::make_index_sequence<TUPLE_SIZE::value - sizeof...(UArgs)>,
							UArgs && ...
						>::type
					{
					};

				private:

					template <std::size_t ... HeadIndex, std::size_t ... TailIndex, typename ... UArgs>
					KERBAL_CONSTEXPR
					explicit tuple_impl(
						tuple_partially_init_t,
						kerbal::utility::index_sequence<HeadIndex...>,
						kerbal::utility::index_sequence<TailIndex...>,
						UArgs && ... args
					)
						KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_partially_init_constructible<UArgs && ...>::value) :
						super<HeadIndex>::type(kerbal::utility::in_place_t(), kerbal::utility::forward<UArgs>(args))...,
						super<TailIndex + sizeof...(HeadIndex)>::type(kerbal::utility::in_place_t())...
					{
					}

				public:

					template <
						typename ... UArgs,
						typename /*msvc_compat*/ =
							typename kerbal::type_traits::enable_if<
								sizeof...(UArgs) <= TUPLE_SIZE::value,
								int
							>::type
					>
					KERBAL_CONSTEXPR
					explicit tuple_impl(tuple_partially_init_t tag, UArgs && ... args)
						KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_partially_init_constructible<UArgs && ...>::value) :
						tuple_impl(
							tag,
							kerbal::utility::make_index_sequence<sizeof...(UArgs)>(),
							kerbal::utility::make_index_sequence<TUPLE_SIZE::value - sizeof...(UArgs)>(),
							kerbal::utility::forward<UArgs>(args)...
						)
					{
						KERBAL_STATIC_ASSERT(sizeof...(UArgs) <= sizeof...(Args), "Too many arguments");
					}


				protected:

					template <typename ... UArgs>
					struct is_nothrow_completely_init_constructible :
						kerbal::type_traits::tribool_conjunction<
							kerbal::type_traits::try_test_is_nothrow_constructible<
								typename super<Index>::type, kerbal::utility::in_place_t, UArgs &&
							>...
						>::result::IS_TRUE
					{
					};

				public:

					template <
						typename ... UArgs,
						typename =
							typename kerbal::type_traits::enable_if<
								sizeof...(UArgs) == TUPLE_SIZE::value,
								int
							>::type
					>
					KERBAL_CONSTEXPR
					explicit tuple_impl(UArgs && ... args)
						KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_completely_init_constructible<UArgs && ...>::value) :
						super<Index>::type(kerbal::utility::in_place_t(), kerbal::utility::forward<UArgs>(args))...
					{
						KERBAL_STATIC_ASSERT(sizeof...(UArgs) == sizeof...(Args), "Wrong number of arguments");
					}

				protected:

					template <
						typename ... TupleArgs,
						typename =
							typename kerbal::type_traits::enable_if<
								sizeof...(TupleArgs) == TUPLE_SIZE::value,
								int
							>::type
					>
					KERBAL_CONSTEXPR
					explicit tuple_impl(kerbal::utility::piecewise_construct_t pie, TupleArgs && ... args) :
						super<Index>::type(pie, kerbal::utility::forward<TupleArgs>(args))...
					{
						KERBAL_STATIC_ASSERT(sizeof...(TupleArgs) == sizeof...(Args), "Wrong number of arguments");
					}

				public:

					template <std::size_t I>
					KERBAL_CONSTEXPR14
					typename reference<I>::type
					get() & KERBAL_NOEXCEPT
					{
						KERBAL_STATIC_ASSERT(I < TUPLE_SIZE::value, "Index out of range");
						return super<I>::type::member();
					}

					template <std::size_t I>
					KERBAL_CONSTEXPR
					typename const_reference<I>::type
					get() const & KERBAL_NOEXCEPT
					{
						KERBAL_STATIC_ASSERT(I < TUPLE_SIZE::value, "Index out of range");
						return super<I>::type::member();
					}

					template <std::size_t I>
					KERBAL_CONSTEXPR
					typename const_reference<I>::type
					cget() const & KERBAL_NOEXCEPT
					{
						KERBAL_STATIC_ASSERT(I < TUPLE_SIZE::value, "Index out of range");
						return super<I>::type::member();
					}

					template <std::size_t I>
					KERBAL_CONSTEXPR14
					typename rvalue_reference<I>::type
					get() && KERBAL_NOEXCEPT
					{
						KERBAL_STATIC_ASSERT(I < TUPLE_SIZE::value, "Index out of range");
						return static_cast<tuple_impl &&>(*this).super<I>::type::member();
					}

					template <std::size_t I>
					KERBAL_CONSTEXPR
					typename const_rvalue_reference<I>::type
					get() const && KERBAL_NOEXCEPT
					{
						KERBAL_STATIC_ASSERT(I < TUPLE_SIZE::value, "Index out of range");
						return static_cast<const tuple_impl &&>(*this).super<I>::type::member();
					}

					template <std::size_t I>
					KERBAL_CONSTEXPR
					typename const_rvalue_reference<I>::type
					cget() const && KERBAL_NOEXCEPT
					{
						KERBAL_STATIC_ASSERT(I < TUPLE_SIZE::value, "Index out of range");
						return static_cast<const tuple_impl &&>(*this).super<I>::type::member();
					}

			};


			template <typename Tuple, typename IndexSequence, typename ... UArgs>
			struct tuple_is_nothrow_covariant_copy_constructible_helper;

			template <typename Tuple, std::size_t ... Index, typename ... UArgs>
			struct tuple_is_nothrow_covariant_copy_constructible_helper<
				Tuple,
				kerbal::utility::index_sequence<Index...>,
				UArgs...
			>
			{
				private:
					typedef kerbal::utility::tuple<UArgs...> ano_tuple;

				public:
					typedef typename Tuple::template is_nothrow_completely_init_constructible<
						decltype(kerbal::utility::declval<const ano_tuple &>().template get<Index>())...
					> type;
			};


			template <typename Tuple, typename IndexSequence, typename ... UArgs>
			struct tuple_is_nothrow_covariant_move_constructible_helper;

			template <typename Tuple, std::size_t ... Index, typename ... UArgs>
			struct tuple_is_nothrow_covariant_move_constructible_helper<
				Tuple,
				kerbal::utility::index_sequence<Index...>,
				UArgs...
			>
			{
				private:
					typedef kerbal::utility::tuple<UArgs...> ano_tuple;

				public:
					typedef typename Tuple::template is_nothrow_completely_init_constructible<
						decltype(kerbal::utility::declval<ano_tuple &&>().template get<Index>())...
					> type;
			};


		} // namespace detail


		template <typename ... Args>
		struct tuple : detail::tuple_impl<kerbal::utility::make_index_sequence<sizeof...(Args)>, Args...>
		{
			private:
				typedef detail::tuple_impl<kerbal::utility::make_index_sequence<sizeof...(Args)>, Args...> super;

			public:
				typedef typename super::TUPLE_SIZE			TUPLE_SIZE;
				typedef kerbal::tmp::type_vector<Args...>	targs_vector;

				template <std::size_t I>
				struct value_type : super::template value_type<I>
				{
				};

				template <std::size_t I>
				struct const_type : super::template const_type<I>
				{
				};

				template <std::size_t I>
				struct reference : super::template reference<I>
				{
				};

				template <std::size_t I>
				struct const_reference : super::template const_reference<I>
				{
				};

				template <std::size_t I>
				struct rvalue_reference : super::template rvalue_reference<I>
				{
				};

				template <std::size_t I>
				struct const_rvalue_reference : super::template const_rvalue_reference<I>
				{
				};


			protected:

				struct is_nothrow_default_constructible : super::is_nothrow_default_constructible
				{
				};

				template <typename ... UArgs>
				struct is_nothrow_partially_init_constructible :
					super::template is_nothrow_partially_init_constructible<UArgs && ...>
				{
				};

				template <typename ... UArgs>
				struct is_nothrow_completely_init_constructible :
					super::template is_nothrow_completely_init_constructible<UArgs && ...>
				{
				};

			public:

				tuple() = default;

				template <
					typename ... UArgs,
					typename /*msvc_compat*/ =
						typename kerbal::type_traits::enable_if<
							sizeof...(UArgs) <= TUPLE_SIZE::value,
							int
						>::type
				>
				KERBAL_CONSTEXPR
				explicit tuple(tuple_partially_init_t tag, UArgs && ... args)
					KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_partially_init_constructible<UArgs && ...>::value) :
					super(tag, kerbal::utility::forward<UArgs>(args)...)
				{
					KERBAL_STATIC_ASSERT(sizeof...(UArgs) <= sizeof...(Args), "Too many arguments");
				}

				template <
					typename ... UArgs,
					typename =
						typename kerbal::type_traits::enable_if<
							sizeof...(UArgs) == TUPLE_SIZE::value,
							int
						>::type
				>
				KERBAL_CONSTEXPR
				explicit tuple(UArgs && ... args)
					KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_completely_init_constructible<UArgs && ...>::value) :
					super(kerbal::utility::forward<UArgs>(args)...)
				{
					KERBAL_STATIC_ASSERT(sizeof...(UArgs) == sizeof...(Args), "Wrong number of arguments");
				}


			protected:

				template <typename Tuple, typename IndexSequence, typename ... UArgs>
				friend struct detail::tuple_is_nothrow_covariant_copy_constructible_helper;

				template <typename ... UArgs>
				struct is_nothrow_covariant_copy_constructible :
					detail::tuple_is_nothrow_covariant_copy_constructible_helper<
						tuple,
						kerbal::utility::make_index_sequence<sizeof...(UArgs)>,
						UArgs...
					>::type
				{
				};

				template <typename Tuple, typename IndexSequence, typename ... UArgs>
				friend struct detail::tuple_is_nothrow_covariant_move_constructible_helper;

				template <typename ... UArgs>
				struct is_nothrow_covariant_move_constructible :
					detail::tuple_is_nothrow_covariant_move_constructible_helper<
						tuple,
						kerbal::utility::make_index_sequence<sizeof...(UArgs)>,
						UArgs...
					>::type
				{
				};

				template <
					std::size_t ... Index,
					typename ... UArgs,
					typename =
						typename kerbal::type_traits::enable_if<
							sizeof...(UArgs) == TUPLE_SIZE::value,
							int
						>::type
				>
				KERBAL_CONSTEXPR
				explicit tuple(kerbal::utility::index_sequence<Index...>, const tuple<UArgs...> & t)
					KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_covariant_copy_constructible<UArgs...>::value) :
					super(t.template get<Index>()...)
				{
				}

				template <
					std::size_t ... Index,
					typename ... UArgs,
					typename =
						typename kerbal::type_traits::enable_if<sizeof...(UArgs) == TUPLE_SIZE::value, int>::type
				>
				KERBAL_CONSTEXPR
				explicit tuple(kerbal::utility::index_sequence<Index...>, tuple<UArgs...> && t)
					KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_covariant_move_constructible<UArgs...>::value) :
					super(kerbal::compatibility::move(t).template get<Index>()...)
				{
				}

			public:

				template <typename ... UArgs>
				KERBAL_CONSTEXPR
				explicit tuple(const tuple<UArgs...> & t)
					KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_covariant_copy_constructible<UArgs...>::value) :
					tuple(kerbal::utility::make_index_sequence<sizeof...(UArgs)>(), t)
				{
					KERBAL_STATIC_ASSERT(sizeof...(UArgs) == sizeof...(Args), "Wrong size tuple");
				}

				template <typename ... UArgs>
				KERBAL_CONSTEXPR
				explicit tuple(tuple<UArgs...> && t)
					KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_covariant_move_constructible<UArgs...>::value) :
					tuple(kerbal::utility::make_index_sequence<sizeof...(UArgs)>(), kerbal::compatibility::move(t))
				{
					KERBAL_STATIC_ASSERT(sizeof...(UArgs) == sizeof...(Args), "Wrong size tuple");
				}


				template <
					typename ... TupleArgs,
					typename =
						typename kerbal::type_traits::enable_if<
							sizeof...(TupleArgs) == TUPLE_SIZE::value,
							int
						>::type
				>
				KERBAL_CONSTEXPR
				explicit tuple(kerbal::utility::piecewise_construct_t pie, TupleArgs && ... args) :
					super(pie, kerbal::utility::forward<TupleArgs>(args)...)
				{
					KERBAL_STATIC_ASSERT(sizeof...(TupleArgs) == sizeof...(Args), "Wrong number of arguments");
				}

			protected:

				template <typename ... UArgs, std::size_t ... Index>
				KERBAL_CONSTEXPR14
				void k_covariant_assign_impl(
					const kerbal::utility::tuple<UArgs...> & t,
					kerbal::utility::index_sequence<Index...>
				)
				{
					kerbal::utility::ignore_unused(
						std::initializer_list<int>{
							(
								this->template get<Index>() = t.template get<Index>(),
								0
							)...
						}
					);
				}

			public:

				template <typename ... UArgs>
				KERBAL_CONSTEXPR14
				tuple & operator=(const kerbal::utility::tuple<UArgs...> & t)
				{
					KERBAL_STATIC_ASSERT(sizeof...(UArgs) == sizeof...(Args), "Wrong size tuple");
					k_covariant_assign_impl(t, kerbal::utility::make_index_sequence<TUPLE_SIZE::value>());
					return *this;
				}


			protected:

				template <typename ... UArgs, std::size_t ... Index>
				KERBAL_CONSTEXPR14
				void k_covariant_move_assign_impl(
					kerbal::utility::tuple<UArgs...> && t,
					kerbal::utility::index_sequence<Index...>
				)
				{
					kerbal::utility::ignore_unused(
						std::initializer_list<int>{
							(
								this->template get<Index>() = kerbal::compatibility::move(t).template get<Index>(),
								0
							)...
						}
					);
				}

			public:

				template <typename ... UArgs>
				KERBAL_CONSTEXPR14
				tuple & operator=(kerbal::utility::tuple<UArgs...> && t)
				{
					k_covariant_move_assign_impl(
						kerbal::compatibility::move(t),
						kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
					);
					return *this;
				}


			public:

				KERBAL_CONSTEXPR
				std::size_t size() const KERBAL_NOEXCEPT
				{
					return TUPLE_SIZE::value;
				}


			protected:

				template <std::size_t ... Index>
				KERBAL_CONSTEXPR14
				tuple<typename reference<Index>::type...>
				k_ref_impl(kerbal::utility::index_sequence<Index...>) & KERBAL_NOEXCEPT
				{
					return tuple<typename reference<Index>::type...>(this->template get<Index>()...);
				}

			public:

				KERBAL_CONSTEXPR14
				auto ref() & KERBAL_NOEXCEPT ->
					decltype(
						kerbal::utility::declval<tuple &>().k_ref_impl(
							kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
						)
					)
				{
					return
						k_ref_impl(
							kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
						);
				}


			protected:

				template <std::size_t ... Index>
				KERBAL_CONSTEXPR14
				tuple<typename const_reference<Index>::type...>
				k_cref_impl(kerbal::utility::index_sequence<Index...>) const & KERBAL_NOEXCEPT
				{
					return tuple<typename const_reference<Index>::type...>(this->template get<Index>()...);
				}

			public:

				KERBAL_CONSTEXPR14
				auto ref() const & KERBAL_NOEXCEPT ->
					decltype(
						kerbal::utility::declval<const tuple &>().k_cref_impl(
							kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
						)
					)
				{
					return
						k_cref_impl(
							kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
						);
				}

				KERBAL_CONSTEXPR14
				auto cref() const & KERBAL_NOEXCEPT ->
					decltype(
						kerbal::utility::declval<const tuple &>().k_cref_impl(
							kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
						)
					)
				{
					return
						k_cref_impl(
							kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
						);
				}


			protected:

				template <typename Self, typename F, std::size_t ... Index>
				KERBAL_CONSTEXPR
				static
				Self &&
				k_for_each_impl(Self && self, F f, kerbal::utility::index_sequence<Index...>)
				{
					return
						kerbal::utility::ignore_unused(
							std::initializer_list<int>{
								(
									f(
										kerbal::type_traits::integral_constant<std::size_t, Index>(),
										kerbal::utility::forward<Self>(self).template get<Index>()
									), 0
								)...
							}
						),
						kerbal::utility::forward<Self>(self);
				}

			public:

				template <typename F>
				KERBAL_CONSTEXPR14
				tuple & for_each(F f) &
				{
					return k_for_each_impl(
						*this,
						f,
						kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
					);
				}

				template <typename F>
				KERBAL_CONSTEXPR
				const tuple & for_each(F f) const &
				{
					return k_for_each_impl(
						*this,
						f,
						kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
					);
				}

				template <typename F>
				KERBAL_CONSTEXPR14
				tuple && for_each(F f) &&
				{
					return k_for_each_impl(
						kerbal::compatibility::move(*this),
						f,
						kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
					);
				}

				template <typename F>
				KERBAL_CONSTEXPR
				const tuple && for_each(F f) const &&
				{
					return k_for_each_impl(
						kerbal::compatibility::move(*this),
						f,
						kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
					);
				}


			protected:

				template <typename Self, typename F, std::size_t ... Index>
				KERBAL_CONSTEXPR
				static
				Self &&
				k_rfor_each_impl(Self && self, F f, kerbal::utility::index_sequence<Index...>)
				{
					return
						kerbal::utility::ignore_unused(
							std::initializer_list<int>{
								(
									f(
										kerbal::type_traits::integral_constant<
											std::size_t,
											TUPLE_SIZE::value - 1 - Index
										>(),
										kerbal::utility::forward<Self>(self).template get<
											TUPLE_SIZE::value - 1 - Index
										>()
									),
									0
								)...
							}
						),
						kerbal::utility::forward<Self>(self);
				}

			public:

				template <typename F>
				KERBAL_CONSTEXPR14
				tuple & rfor_each(F f) &
				{
					return k_rfor_each_impl(
						*this,
						f,
						kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
					);
				}

				template <typename F>
				KERBAL_CONSTEXPR
				const tuple & rfor_each(F f) const &
				{
					return k_rfor_each_impl(
						*this,
						f,
						kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
					);
				}

				template <typename F>
				KERBAL_CONSTEXPR14
				tuple && rfor_each(F f) &&
				{
					return k_rfor_each_impl(
						kerbal::compatibility::move(*this),
						f,
						kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
					);
				}

				template <typename F>
				KERBAL_CONSTEXPR
				const tuple && rfor_each(F f) const &&
				{
					return k_rfor_each_impl(
						kerbal::compatibility::move(*this),
						f,
						kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
					);
				}


			protected:

				template <typename Self, typename F, std::size_t ... Index>
				KERBAL_CONSTEXPR
				static
				auto k_apply_to_impl(Self && self, F f, kerbal::utility::index_sequence<Index...>) ->
					decltype(f(kerbal::utility::forward<Self>(self).template get<Index>()...))
				{
					return f(kerbal::utility::forward<Self>(self).template get<Index>()...);
				}

			public:

				template <typename F>
				KERBAL_CONSTEXPR14
				auto apply_to(F f) & ->
					decltype(
						k_apply_to_impl(
							*this,
							f,
							kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
						)
					)
				{
					return
						k_apply_to_impl(
							*this,
							f,
							kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
						);
				}

				template <typename F>
				KERBAL_CONSTEXPR
				auto apply_to(F f) const & ->
					decltype(
						k_apply_to_impl(
							*this,
							f,
							kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
						)
					)
				{
					return
						k_apply_to_impl(
							*this,
							f,
							kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
						);
				}

				template <typename F>
				KERBAL_CONSTEXPR14
				auto apply_to(F f) && ->
					decltype(
						k_apply_to_impl(
							kerbal::compatibility::move(*this),
							f,
							kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
						)
					)
				{
					return
						k_apply_to_impl(
							kerbal::compatibility::move(*this),
							f,
							kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
						);
				}

				template <typename F>
				KERBAL_CONSTEXPR
				auto apply_to(F f) const && ->
					decltype(
						k_apply_to_impl(
							kerbal::compatibility::move(*this),
							f,
							kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
						)
					)
				{
					return
						k_apply_to_impl(
							kerbal::compatibility::move(*this),
							f,
							kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
						);
				}

			protected:

				template <typename Self, typename F, typename JoinF, std::size_t ... Index>
				KERBAL_CONSTEXPR
				static
				int k_join_impl2(Self && self, F f, JoinF joinf, kerbal::utility::index_sequence<Index...>)
				{
					return
						kerbal::utility::ignore_unused(
							std::initializer_list<int>{
								(
									Index % 2 == 0 ?
									(
										f(
											kerbal::type_traits::integral_constant<std::size_t, Index / 2>(),
											kerbal::utility::forward<Self>(self).template get<Index / 2>()
										),
										0
									) :
									(
										joinf(
											kerbal::type_traits::integral_constant<std::size_t, Index / 2>()
										),
										0
									)
								)...
							}
						),
						0;
				}

				template <typename Self, typename HeadF, typename F, typename JoinF, typename TailF, std::size_t N>
				KERBAL_CONSTEXPR
				static Self && k_join_impl(
					Self && self, HeadF headf, F f, JoinF joinf, TailF tailf,
					kerbal::type_traits::integral_constant<std::size_t, N>
				)
				{
					return
						headf(),
						k_join_impl2(kerbal::utility::forward<Self>(self), f, joinf, kerbal::utility::make_index_sequence<2 * N - 1>()),
						tailf(),
						kerbal::utility::forward<Self>(self)
					;
				}

				template <typename Self, typename HeadF, typename F, typename JoinF, typename TailF>
				KERBAL_CONSTEXPR
				static Self && k_join_impl(
					Self && self, HeadF headf, F /*f*/, JoinF /*joinf*/, TailF tailf,
					kerbal::type_traits::integral_constant<std::size_t, 0>
				)
				{
					return headf(), tailf(), kerbal::utility::forward<Self>(self);
				}

			public:

				template <typename HeadF, typename F, typename JoinF, typename TailF>
				KERBAL_CONSTEXPR14
				tuple & join(HeadF headf, F f, JoinF joinf, TailF tailf) &
				{
					return k_join_impl(
						*this,
						headf, f, joinf, tailf,
						TUPLE_SIZE()
					);
				}

				template <typename HeadF, typename F, typename JoinF, typename TailF>
				KERBAL_CONSTEXPR
				const tuple & join(HeadF headf, F f, JoinF joinf, TailF tailf) const &
				{
					return k_join_impl(
						*this,
						headf, f, joinf, tailf,
						TUPLE_SIZE()
					);
				}

				template <typename HeadF, typename F, typename JoinF, typename TailF>
				KERBAL_CONSTEXPR14
				tuple && join(HeadF headf, F f, JoinF joinf, TailF tailf) &&
				{
					return k_join_impl(
						kerbal::compatibility::move(*this),
						headf, f, joinf, tailf,
						TUPLE_SIZE()
					);
				}

				template <typename HeadF, typename F, typename JoinF, typename TailF>
				KERBAL_CONSTEXPR
				const tuple && join(HeadF headf, F f, JoinF joinf, TailF tailf) const &&
				{
					return k_join_impl(
						kerbal::compatibility::move(*this),
						headf, f, joinf, tailf,
						TUPLE_SIZE()
					);
				}


			protected:

				template <typename Self, typename F, std::size_t ... Index>
				KERBAL_CONSTEXPR
				static
				auto k_transform_impl(Self && self, F f, kerbal::utility::index_sequence<Index...>) ->
					decltype(kerbal::utility::make_tuple(
						f(
							kerbal::type_traits::integral_constant<std::size_t, Index>(),
							kerbal::utility::forward<Self>(self).template get<Index>()
						)...
					))
				{
					return kerbal::utility::make_tuple(
						f(
							kerbal::type_traits::integral_constant<std::size_t, Index>(),
							kerbal::utility::forward<Self>(self).template get<Index>()
						)...
					);
				}

			public:

				template <typename F>
				KERBAL_CONSTEXPR14
				auto transform(F f) & ->
					decltype(
						k_transform_impl(
							*this,
							f,
							kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
						)
					)
				{
					return
						k_transform_impl(
							*this,
							f,
							kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
						);
				}

				template <typename F>
				KERBAL_CONSTEXPR
				auto transform(F f) const & ->
					decltype(
						k_transform_impl(
							*this,
							f,
							kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
						)
					)
				{
					return
						k_transform_impl(
							*this,
							f,
							kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
						);
				}

				template <typename F>
				KERBAL_CONSTEXPR14
				auto transform(F f) && ->
					decltype(
						k_transform_impl(
							kerbal::compatibility::move(*this),
							f,
							kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
						)
					)
				{
					return
						k_transform_impl(
							kerbal::compatibility::move(*this),
							f,
							kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
						);
				}

				template <typename F>
				KERBAL_CONSTEXPR
				auto transform(F f) const && ->
					decltype(
						k_transform_impl(
							kerbal::compatibility::move(*this),
							f,
							kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
						)
					)
				{
					return
						k_transform_impl(
							kerbal::compatibility::move(*this),
							f,
							kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
						);
				}


			protected:

				template <typename Self, std::size_t ... Index>
				KERBAL_CONSTEXPR
				static
				tuple<typename value_type<Index>::type...>
				k_select_impl(Self && self, kerbal::utility::index_sequence<Index...>)
				{
					return tuple<typename value_type<Index>::type...>(
						kerbal::utility::forward<Self>(self).template get<Index>()...
					);
				}

			public:

				template <std::size_t ... Index>
				KERBAL_CONSTEXPR
				auto select() const & ->
					decltype(
						k_select_impl(
							*this,
							kerbal::utility::index_sequence<Index...>()
						)
					)
				{
					return
						k_select_impl(
							*this,
							kerbal::utility::index_sequence<Index...>()
						);
				}

				template <std::size_t ... Index>
				KERBAL_CONSTEXPR14
				auto select() && ->
					decltype(
						k_select_impl(
							kerbal::compatibility::move(*this),
							kerbal::utility::index_sequence<Index...>()
						)
					)
				{
					return
						k_select_impl(
							kerbal::compatibility::move(*this),
							kerbal::utility::index_sequence<Index...>()
						);
				}


			protected:

				template <typename Self, std::size_t ... Index>
				KERBAL_CONSTEXPR
				static
				tuple<typename value_type<TUPLE_SIZE::value - 1 - Index>::type...>
				k_reverse_impl(Self && self, kerbal::utility::index_sequence<Index...>)
				{
					return tuple<typename value_type<TUPLE_SIZE::value - 1 - Index>::type...>(
						kerbal::utility::forward<Self>(self).template get<TUPLE_SIZE::value - 1 - Index>()...
					);
				}

			public:

				KERBAL_CONSTEXPR
				auto reverse() const & ->
					decltype(
						k_reverse_impl(
							*this,
							kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
						)
					)
				{
					return
						k_reverse_impl(
							*this,
							kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
						);
				}

				KERBAL_CONSTEXPR14
				auto reverse() && ->
					decltype(
						k_reverse_impl(
							kerbal::compatibility::move(*this),
							kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
						)
					)
				{
					return
						k_reverse_impl(
							kerbal::compatibility::move(*this),
							kerbal::utility::make_index_sequence<TUPLE_SIZE::value>()
						);
				}


			protected:

				template <std::size_t ... Index>
				KERBAL_CONSTEXPR14
				void k_swap_impl(tuple & ano, kerbal::utility::index_sequence<Index...>)
				{
					kerbal::utility::ignore_unused(
						std::initializer_list<int>{
							(
								kerbal::algorithm::swap(
									this->template get<Index>(),
									ano.template get<Index>()
								),
								0
							)...
						}
					);
				}

			public:

				KERBAL_CONSTEXPR14
				void swap(tuple & ano)
				{
					k_swap_impl(ano, kerbal::utility::make_index_sequence<TUPLE_SIZE::value>());
				}


			protected:

				template <std::size_t N>
				KERBAL_CONSTEXPR
				bool k_equal_to_impl(const tuple & ano, kerbal::type_traits::integral_constant<std::size_t, N>) const
				{
					typedef kerbal::compare::equal_to<typename value_type<N>::type> Pred;
					return
						static_cast<bool>(Pred()(this->template get<N>(), ano.template get<N>())) &&
						this->k_equal_to_impl(ano, kerbal::type_traits::integral_constant<std::size_t, N + 1>());
				}

				KERBAL_CONSTEXPR
				bool k_equal_to_impl(const tuple & ano, kerbal::type_traits::integral_constant<std::size_t, TUPLE_SIZE::value>) const
				{
					return true;
				}

			public:

				KERBAL_CONSTEXPR
				bool operator==(const tuple & ano) const
				{
					return this->k_equal_to_impl(ano, kerbal::type_traits::integral_constant<std::size_t, 0>());
				}


			protected:

				template <std::size_t N>
				KERBAL_CONSTEXPR
				bool k_not_equal_to_impl(const tuple & ano, kerbal::type_traits::integral_constant<std::size_t, N>) const
				{
					typedef kerbal::compare::not_equal_to<typename value_type<N>::type> Pred;
					return
						static_cast<bool>(Pred()(this->template get<N>(), ano.template get<N>())) ||
						this->k_not_equal_to_impl(ano, kerbal::type_traits::integral_constant<std::size_t, N + 1>());
				}

				KERBAL_CONSTEXPR
				bool k_not_equal_to_impl(const tuple & ano, kerbal::type_traits::integral_constant<std::size_t, TUPLE_SIZE::value>) const
				{
					return false;
				}

			public:

				KERBAL_CONSTEXPR
				bool operator!=(const tuple & ano) const
				{
					return this->k_not_equal_to_impl(ano, kerbal::type_traits::integral_constant<std::size_t, 0>());
				}


			protected:

				template <std::size_t N>
				KERBAL_CONSTEXPR
				bool k_less_impl(const tuple & ano, kerbal::type_traits::integral_constant<std::size_t, N>) const
				{
					typedef kerbal::compare::less<typename value_type<N>::type> Pred;
					return
						static_cast<bool>(Pred()(this->template get<N>(), ano.template get<N>())) /* *this < ano */ ||
						(
							!static_cast<bool>(Pred()(ano.template get<N>(), this->template get<N>())) /* *this <= ano */ &&
							this->k_less_impl(ano, kerbal::type_traits::integral_constant<std::size_t, N + 1>())
						);
				}

				KERBAL_CONSTEXPR
				bool k_less_impl(const tuple & ano, kerbal::type_traits::integral_constant<std::size_t, TUPLE_SIZE::value>) const
				{
					return false;
				}

			public:

				KERBAL_CONSTEXPR
				bool operator<(const tuple & ano) const
				{
					return this->k_less_impl(ano, kerbal::type_traits::integral_constant<std::size_t, 0>());
				}


			protected:

				template <std::size_t N>
				KERBAL_CONSTEXPR
				bool k_greater_impl(const tuple & ano, kerbal::type_traits::integral_constant<std::size_t, N>) const
				{
					typedef kerbal::compare::greater<typename value_type<N>::type> Pred;
					return
						static_cast<bool>(Pred()(this->template get<N>(), ano.template get<N>())) /* *this > ano */ ||
						(
							!static_cast<bool>(Pred()(ano.template get<N>(), this->template get<N>())) /* *this >= ano */ &&
							this->k_greater_impl(ano, kerbal::type_traits::integral_constant<std::size_t, N + 1>())
						);
				}

				KERBAL_CONSTEXPR
				bool k_greater_impl(const tuple & ano, kerbal::type_traits::integral_constant<std::size_t, TUPLE_SIZE::value>) const
				{
					return false;
				}

			public:

				KERBAL_CONSTEXPR
				bool operator>(const tuple & ano) const
				{
					return this->k_greater_impl(ano, kerbal::type_traits::integral_constant<std::size_t, 0>());
				}


			protected:

				template <std::size_t N>
				KERBAL_CONSTEXPR
				bool k_less_equal_impl(const tuple & ano, kerbal::type_traits::integral_constant<std::size_t, N>) const
				{
					typedef kerbal::compare::less_equal<typename value_type<N>::type> Pred;
					return
						static_cast<bool>(Pred()(this->template get<N>(), ano.template get<N>())) /* *this <= ano */ &&
						(
							static_cast<bool>(Pred()(ano.template get<N>(), this->template get<N>())) ? /* ano <= *this */
							this->k_less_equal_impl(ano, kerbal::type_traits::integral_constant<std::size_t, N + 1>()) : /* *this == ano */
							true /* *this < ano */
						);
				}

				KERBAL_CONSTEXPR
				bool k_less_equal_impl(const tuple & ano, kerbal::type_traits::integral_constant<std::size_t, TUPLE_SIZE::value>) const
				{
					return true;
				}

			public:

				KERBAL_CONSTEXPR
				bool operator<=(const tuple & ano) const
				{
					return this->k_less_equal_impl(ano, kerbal::type_traits::integral_constant<std::size_t, 0>());
				}


			protected:

				template <std::size_t N>
				KERBAL_CONSTEXPR
				bool k_greater_equal_impl(const tuple & ano, kerbal::type_traits::integral_constant<std::size_t, N>) const
				{
					typedef kerbal::compare::greater_equal<typename value_type<N>::type> Pred;
					return
						static_cast<bool>(Pred()(this->template get<N>(), ano.template get<N>())) /* *this >= ano */ &&
						(
							static_cast<bool>(Pred()(ano.template get<N>(), this->template get<N>())) ? /* ano >= *this */
							this->k_greater_equal_impl(ano, kerbal::type_traits::integral_constant<std::size_t, N + 1>()) : /* *this == ano */
							true /* *this > ano */
						);
				}

				KERBAL_CONSTEXPR
				bool k_greater_equal_impl(const tuple & ano, kerbal::type_traits::integral_constant<std::size_t, TUPLE_SIZE::value>) const
				{
					return true;
				}

			public:

				KERBAL_CONSTEXPR
				bool operator>=(const tuple & ano) const
				{
					return this->k_greater_equal_impl(ano, kerbal::type_traits::integral_constant<std::size_t, 0>());
				}

		};


		template <typename ... Args>
		KERBAL_CONSTEXPR
		kerbal::utility::tuple<
			typename kerbal::type_traits::remove_cvref<Args>::type...
		>
		make_tuple(Args && ... args)
		{
			return
				kerbal::utility::tuple<
					typename kerbal::type_traits::remove_cvref<Args>::type...
				>(
					kerbal::utility::forward<Args>(args)...
				);
		}

#	if __cplusplus >= 201703L

		template <typename ... Args>
		tuple(Args && ...) ->
		tuple<typename kerbal::type_traits::remove_cvref<Args>::type...>;

#	endif

		template <typename ... Args>
		KERBAL_CONSTEXPR
		kerbal::utility::tuple<Args & ...>
		tie(Args & ... args) KERBAL_NOEXCEPT
		{
			return kerbal::utility::tuple<Args & ...>(args...);
		}

		template <typename ... Args>
		KERBAL_CONSTEXPR
		kerbal::utility::tuple<Args && ...>
		forward_as_tuple(Args && ... args)
		{
			return kerbal::utility::tuple<Args && ...>(
				kerbal::utility::forward<Args>(args)...
			);
		}

	} // namespace utility


	namespace algorithm
	{

		template <typename ... Args>
		KERBAL_CONSTEXPR20
		void swap(
			kerbal::utility::tuple<Args...> & a,
			kerbal::utility::tuple<Args...> & b
		)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
		{
			a.swap(b);
		}

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <typename ... Args>
	KERBAL_CONSTEXPR20
	void swap(
		kerbal::utility::tuple<Args...> & a,
		kerbal::utility::tuple<Args...> & b
	)
		KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END


#if __cplusplus >= 201103L

#include <kerbal/utility/std_tuple/std_tuple.fwd.hpp>

#include <type_traits> // std::integral_constant


KERBAL_NAMESPACE_STD_BEGIN

	template <typename ... Args>
	struct tuple_size<kerbal::utility::tuple<Args...> > :
		std::integral_constant<std::size_t, kerbal::utility::tuple<Args...>::TUPLE_SIZE::value>
	{
	};

	template <std::size_t I, typename ... Args>
	struct tuple_element<I, kerbal::utility::tuple<Args...> > :
		kerbal::utility::tuple<Args...>::template value_type<I>
	{
	};

	template <std::size_t I, typename ... Args>
	KERBAL_CONSTEXPR14
	typename kerbal::utility::tuple<Args...>::template reference<I>::type
	get(kerbal::utility::tuple<Args...> & t) KERBAL_NOEXCEPT
	{
		return t.template get<I>();
	}

	template <std::size_t I, typename ... Args>
	KERBAL_CONSTEXPR
	typename kerbal::utility::tuple<Args...>::template const_reference<I>::type
	get(const kerbal::utility::tuple<Args...> & t) KERBAL_NOEXCEPT
	{
		return t.template get<I>();
	}

	template <std::size_t I, typename ... Args>
	KERBAL_CONSTEXPR14
	typename kerbal::utility::tuple<Args...>::template rvalue_reference<I>::type
	get(kerbal::utility::tuple<Args...> && t) KERBAL_NOEXCEPT
	{
		return kerbal::compatibility::move(t).template get<I>();
	}

	template <std::size_t I, typename ... Args>
	KERBAL_CONSTEXPR
	typename kerbal::utility::tuple<Args...>::template const_rvalue_reference<I>::type
	get(const kerbal::utility::tuple<Args...> && t) KERBAL_NOEXCEPT
	{
		return kerbal::compatibility::move(t).template get<I>();
	}

KERBAL_NAMESPACE_STD_END

#endif


namespace kerbal
{

	namespace utility
	{

		namespace detail
		{

			template <typename T, typename>
			struct k_elements_type_vector_helper;

			template <typename T, std::size_t ... I>
			struct k_elements_type_vector_helper<T, kerbal::utility::index_sequence<I...> >
			{
					typedef kerbal::tmp::type_vector<typename std::tuple_element<I, T>::type ...> type;
			};

			template <typename T>
			struct elements_type_vector :
					k_elements_type_vector_helper<T, kerbal::utility::make_index_sequence<std::tuple_size<T>::value> >
			{
			};


			template <typename ... Ts>
			struct elements_type_vector_cat;

			template <>
			struct elements_type_vector_cat<>
			{
					typedef kerbal::tmp::type_vector<> type;
			};

			template <typename T, typename ... Ts>
			struct elements_type_vector_cat<T, Ts...>
			{
					typedef typename kerbal::tmp::type_vector_cat<
						typename elements_type_vector<T>::type,
						typename elements_type_vector_cat<Ts...>::type
					>::result type;
			};


			template <typename TypeVector>
			struct replace_type_vector_to_tuple;

			template <typename ... Args>
			struct replace_type_vector_to_tuple<kerbal::tmp::type_vector<Args...> >
			{
					typedef kerbal::utility::tuple<Args...> result;
			};


			template <std::size_t I, typename ... Ts>
			struct element_index_in_tuples;

			template <std::size_t I, typename T>
			struct element_index_in_tuples<I, T>
			{
				private:
					KERBAL_STATIC_ASSERT(I < std::tuple_size<T>::value, "Index out of range");

				public:
					typedef kerbal::type_traits::integral_constant<std::size_t, 0> tuple_index;
					typedef kerbal::type_traits::integral_constant<std::size_t, I> tuple_inner_index;
			};

			template <bool in_the_first, std::size_t I, typename T, typename ... Ts>
			struct k_element_index_in_tuples_helper;

			template <std::size_t I, typename T, typename ... Ts>
			struct k_element_index_in_tuples_helper<true, I, T, Ts...>
			{
					typedef kerbal::type_traits::integral_constant<std::size_t, 0> tuple_index;
					typedef kerbal::type_traits::integral_constant<std::size_t, I> tuple_inner_index;
			};

			template <std::size_t I, typename T, typename ... Ts>
			struct k_element_index_in_tuples_helper<false, I, T, Ts...>
			{
				private:
					typedef element_index_in_tuples<I - std::tuple_size<T>::value, Ts...> next;

				public:
					typedef kerbal::type_traits::integral_constant<std::size_t, next::tuple_index::value + 1> tuple_index;
					typedef typename next::tuple_inner_index tuple_inner_index;
			};

			template <std::size_t I, typename T, typename ... Ts>
			struct element_index_in_tuples<I, T, Ts...> :
				k_element_index_in_tuples_helper<I < std::tuple_size<T>::value, I, T, Ts...>
			{
			};


			template <std::size_t I, typename T>
			struct std_get_result_type
			{
					typedef decltype(std::get<I>(kerbal::utility::declval<T>())) type;
			};


			template <std::size_t I, typename ... Ts>
			struct get_in_tuples_result_type
			{
					typedef element_index_in_tuples<I, typename kerbal::type_traits::remove_reference<Ts>::type ...> ele_index;
					typedef typename ele_index::tuple_index tuple_index;
					typedef typename ele_index::tuple_inner_index tuple_inner_index;
					typedef kerbal::tmp::type_vector<Ts...> tuples_type_vector;
					typedef typename kerbal::tmp::type_vector_at<tuples_type_vector, tuple_index::value>::result tuple_with_ref;

					typedef typename std_get_result_type<tuple_inner_index::value, tuple_with_ref>::type type;
			};


			template <std::size_t I>
			struct forward_packs_at;

			template <>
			struct forward_packs_at<0>
			{
					template <typename T, typename ... Args>
					KERBAL_CONSTEXPR
					static T && f(T && t, Args && ...) KERBAL_NOEXCEPT
					{
						return kerbal::utility::forward<T>(t);
					}
			};

			template <std::size_t I>
			struct forward_packs_at
			{
					template <typename T, typename ... Args>
					KERBAL_CONSTEXPR
					static auto f(T &&, Args && ... args) KERBAL_NOEXCEPT ->
						decltype(forward_packs_at<I - 1>::f(kerbal::utility::forward<Args>(args)...))
					{
						return forward_packs_at<I - 1>::f(kerbal::utility::forward<Args>(args)...);
					}
			};


			template <std::size_t I, typename ... Args>
			KERBAL_CONSTEXPR
			auto get_in_tuples(Args && ... args) KERBAL_NOEXCEPT ->
				typename get_in_tuples_result_type<I, Args && ...>::type
			{
				typedef element_index_in_tuples<I, typename kerbal::type_traits::remove_reference<Args>::type ...> ele_index;
				typedef typename ele_index::tuple_index tuple_index;
				typedef typename ele_index::tuple_inner_index tuple_inner_index;

				return std::get<tuple_inner_index::value>(forward_packs_at<tuple_index::value>::f(kerbal::utility::forward<Args>(args)...));
			}


			template <typename ... Tuples>
			struct tuple_cat_helper
			{

					typedef typename elements_type_vector_cat<
						typename kerbal::type_traits::remove_const<
							typename kerbal::type_traits::remove_reference<Tuples>::type
						>::type ...
					>::type elements_type_vector_cat_result;

					typedef typename replace_type_vector_to_tuple<elements_type_vector_cat_result>::result tuple_cat_result_type;
					typedef typename elements_type_vector_cat_result::SIZE SIZE_TOTAL;

					template <std::size_t ... Index>
					KERBAL_CONSTEXPR
					static tuple_cat_result_type k_cat_impl(kerbal::utility::index_sequence<Index...>, Tuples && ... tuples)
					{
						return tuple_cat_result_type(get_in_tuples<Index>(kerbal::utility::forward<Tuples>(tuples)...)...);
					}

					KERBAL_CONSTEXPR
					static tuple_cat_result_type cat(Tuples && ... tuples)
					{
						return k_cat_impl(
							kerbal::utility::make_index_sequence<SIZE_TOTAL::value>(),
							kerbal::utility::forward<Tuples>(tuples)...
						);
					}
			};

		} // namespace detail


		template <typename ... Tuples>
		KERBAL_CONSTEXPR
		typename detail::tuple_cat_helper<Tuples...>::tuple_cat_result_type
		tuple_cat(Tuples && ... tuples)
		{
			return detail::tuple_cat_helper<Tuples...>::cat(kerbal::utility::forward<Tuples>(tuples)...);
		}


		template <typename ... Args, typename ... UArgs>
		KERBAL_CONSTEXPR
		auto operator+(const tuple<Args...> & t0, const tuple<UArgs...> & t1) ->
			decltype(tuple_cat(t0, t1))
		{
			return tuple_cat(t0, t1);
		}

		template <typename ... Args, typename ... UArgs>
		KERBAL_CONSTEXPR
		auto operator+(const tuple<Args...> & t0, tuple<UArgs...> && t1) ->
			decltype(tuple_cat(t0, kerbal::compatibility::move(t1)))
		{
			return tuple_cat(t0, kerbal::compatibility::move(t1));
		}

		template <typename ... Args, typename ... UArgs>
		KERBAL_CONSTEXPR
		auto operator+(tuple<Args...> && t0, const tuple<UArgs...> & t1) ->
			decltype(tuple_cat(kerbal::compatibility::move(t0), t1))
		{
			return tuple_cat(kerbal::compatibility::move(t0), t1);
		}

		template <typename ... Args, typename ... UArgs>
		KERBAL_CONSTEXPR
		auto operator+(tuple<Args...> && t0, tuple<UArgs...> && t1) ->
			decltype(tuple_cat(kerbal::compatibility::move(t0), kerbal::compatibility::move(t1)))
		{
			return tuple_cat(kerbal::compatibility::move(t0), kerbal::compatibility::move(t1));
		}

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_UTILITY_TUPLE_DETAIL_TUPLE_CXX11_PART_HPP
