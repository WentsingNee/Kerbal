/**
 * @file       tuple.cxx98.part.hpp
 * @brief
 * @date       2021-12-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_TUPLE_DETAIL_TUPLE_CXX98_PART_HPP
#define KERBAL_UTILITY_TUPLE_DETAIL_TUPLE_CXX98_PART_HPP

#include <kerbal/utility/tuple/tuple.fwd.hpp>

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compare/basic_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/macro/macro_concat.hpp>
#include <kerbal/macro/ppexpand.hpp>
#include <kerbal/tmp/type_vector.hpp>
#include <kerbal/type_traits/add_lvalue_reference.hpp>
#include <kerbal/type_traits/add_const_lvalue_reference.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/utility/member_compress_helper.hpp>

#include <cstddef>


namespace kerbal
{

	namespace utility
	{

		template <>
		struct tuple<>
		{
			protected:
				typedef kerbal::tmp::type_vector<> targs_vector;

			public:
				typedef kerbal::type_traits::integral_constant<std::size_t, 0> TUPLE_SIZE;

			public:
				KERBAL_CONSTEXPR
				std::size_t size() const KERBAL_NOEXCEPT
				{
					return TUPLE_SIZE::value;
				}

				KERBAL_CONSTEXPR
				tuple<> ref() KERBAL_NOEXCEPT
				{
					return tuple<>();
				}

				KERBAL_CONSTEXPR
				tuple<> ref() const KERBAL_NOEXCEPT
				{
					return tuple<>();
				}

				KERBAL_CONSTEXPR
				tuple<> cref() const KERBAL_NOEXCEPT
				{
					return tuple<>();
				}

				template <typename F>
				KERBAL_CONSTEXPR14
				void for_each(F f) KERBAL_NOEXCEPT
				{
				}

				template <typename F>
				KERBAL_CONSTEXPR14
				void for_each(F f) const KERBAL_NOEXCEPT
				{
				}

				KERBAL_CONSTEXPR
				tuple<> reverse() const KERBAL_NOEXCEPT
				{
					return tuple<>();
				}

				KERBAL_CONSTEXPR14
				void swap(tuple &) KERBAL_NOEXCEPT
				{
				}

				KERBAL_CONSTEXPR
				bool operator==(const tuple & ano) const KERBAL_NOEXCEPT
				{
					return true;
				}

				KERBAL_CONSTEXPR
				bool operator!=(const tuple & ano) const KERBAL_NOEXCEPT
				{
					return false;
				}

				KERBAL_CONSTEXPR
				bool operator<(const tuple & ano) const KERBAL_NOEXCEPT
				{
					return false;
				}

				KERBAL_CONSTEXPR
				bool operator>(const tuple & ano) const KERBAL_NOEXCEPT
				{
					return false;
				}

				KERBAL_CONSTEXPR
				bool operator<=(const tuple & ano) const KERBAL_NOEXCEPT
				{
					return true;
				}

				KERBAL_CONSTEXPR
				bool operator>=(const tuple & ano) const KERBAL_NOEXCEPT
				{
					return true;
				}

		};


#	define EMPTY
#	define REMAINF(exp) exp
#	define LEFT_JOIN_COLON(exp) : exp
#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define TARGS_USE(i) KERBAL_MACRO_CONCAT(Arg, i)
#	define SUPER_TYPE(i) kerbal::utility::member_compress_helper<KERBAL_MACRO_CONCAT(Arg, i), (i) - 1>
#	define SUPER_TYPEDEF_USE(i) super<(i) - 1>::type
#	define DFT_CNSTRCTOR_INIT_SUPER_TYPE(i) SUPER_TYPEDEF_USE(i)(kerbal::utility::in_place_t())

#	define EACH_INIT_CNSTRCTOR_TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(UArg, i)
#	define EACH_INIT_CNSTRCTOR_ARGS_DECL(i) KERBAL_MACRO_CONCAT(UArg, i) & KERBAL_MACRO_CONCAT(uarg, i)
#	define EACH_INIT_CNSTRCTOR_INIT_SUPER_TYPE(i) SUPER_TYPEDEF_USE(i)(kerbal::utility::in_place_t(), KERBAL_MACRO_CONCAT(uarg, i))

#	define EACH_CONST_INIT_CNSTRCTOR_TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(UArg, i)
#	define EACH_CONST_INIT_CNSTRCTOR_ARGS_DECL(i) const KERBAL_MACRO_CONCAT(UArg, i) & KERBAL_MACRO_CONCAT(uarg, i)
#	define EACH_CONST_INIT_CNSTRCTOR_INIT_SUPER_TYPE(i) SUPER_TYPEDEF_USE(i)(kerbal::utility::in_place_t(), KERBAL_MACRO_CONCAT(uarg, i))

#	define VARIANCE_INIT_CNSTRCTOR_TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(UArg, i)
#	define VARIANCE_INIT_CNSTRCTOR_TARGS_USE(i) KERBAL_MACRO_CONCAT(UArg, i)
#	define VARIANCE_INIT_CNSTRCTOR_INIT_SUPER_TYPE(i) SUPER_TYPEDEF_USE(i)(kerbal::utility::in_place_t(), t.template get<(i) - 1>())

#	define VARIANCE_ASSIGN_TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(UArg, i)
#	define VARIANCE_ASSIGN_TARGS_USE(i) KERBAL_MACRO_CONCAT(UArg, i)
#	define VARIANCE_ASSIGN_EACH_ASSIGN(i) (this->template get<(i) - 1>() = t.template get<(i) - 1>())

#	define REF_EACH_TYPE(i) typename reference<(i) - 1>::type
#	define REF_EACH_GET(i) this->template get<(i) - 1>()

#	define CREF_EACH_TYPE(i) typename const_reference<(i) - 1>::type
#	define CREF_EACH_GET(i) this->template get<(i) - 1>()

#	define FOR_EACH_EACH_APPLY(i) (f(kerbal::type_traits::integral_constant<std::size_t, (i) - 1>(), this->template get<(i) - 1>()))
#	define RFOR_EACH_EACH_APPLY(i) (f(kerbal::type_traits::integral_constant<std::size_t, TUPLE_SIZE::value - 1 - ((i) - 1)>(), this->template get<TUPLE_SIZE::value - 1 - ((i) - 1)>()))
#	define VISIT_APPLY(i) (((i) == idx) ? f(kerbal::type_traits::integral_constant<std::size_t, (i) - 1>(), this->template get<(i) - 1>()), 0 : 0)

#	define REVERSE_EACH_TYPE(i) typename value_type<TUPLE_SIZE::value - 1 - ((i) - 1)>::type
#	define REVERSE_EACH_GET(i) this->template get<TUPLE_SIZE::value - 1 - ((i) - 1)>()

#	define SWAP_EACH_SWAP(i) (kerbal::algorithm::swap(this->template get<(i) - 1>(), ano.template get<(i) - 1>()))

#	define DBODY(i) \
		template <KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_DECL, i)> \
		struct tuple<KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_USE, i)> \
			KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COLON, EMPTY, SUPER_TYPE, i) \
		{ \
			protected: \
				typedef kerbal::tmp::type_vector<KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_USE, i)> targs_vector; \
 \
			public: \
				typedef kerbal::type_traits::integral_constant<std::size_t, i> TUPLE_SIZE; \
 \
				template <std::size_t I> \
				struct value_type \
				{ \
						typedef typename kerbal::tmp::type_vector_at<targs_vector, I>::result type; \
				}; \
 \
			private: \
 \
				template <std::size_t I> \
				struct super \
				{ \
					private: \
						KERBAL_STATIC_ASSERT(I < TUPLE_SIZE::value, "Index out of range"); \
 \
					public: \
						typedef kerbal::utility::member_compress_helper<typename value_type<I>::type, I> type; \
				}; \
 \
			public: \
 \
				template <std::size_t I> \
				struct const_type \
				{ \
					private: \
						KERBAL_STATIC_ASSERT(I < TUPLE_SIZE::value, "Index out of range"); \
 \
					public: \
						typedef const typename value_type<I>::type type; \
				}; \
 \
				template <std::size_t I> \
				struct reference \
				{ \
					private: \
						KERBAL_STATIC_ASSERT(I < TUPLE_SIZE::value, "Index out of range"); \
 \
					public: \
						typedef typename kerbal::type_traits::add_lvalue_reference< \
								typename value_type<I>::type \
						>::type type; \
				}; \
 \
				template <std::size_t I> \
				struct const_reference \
				{ \
					private: \
						KERBAL_STATIC_ASSERT(I < TUPLE_SIZE::value, "Index out of range"); \
 \
					public: \
						typedef typename kerbal::type_traits::add_const_lvalue_reference< \
								typename value_type<I>::type \
						>::type type; \
				}; \
 \
			public: \
 \
				KERBAL_CONSTEXPR \
				tuple() \
					KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COLON, EMPTY, DFT_CNSTRCTOR_INIT_SUPER_TYPE, i) \
				{ \
				} \
 \
				template <KERBAL_PPEXPAND_WITH_COMMA_N(EACH_INIT_CNSTRCTOR_TARGS_DECL, i)> \
				KERBAL_CONSTEXPR \
				explicit tuple(KERBAL_PPEXPAND_WITH_COMMA_N(EACH_INIT_CNSTRCTOR_ARGS_DECL, i)) \
					KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COLON, EMPTY, EACH_INIT_CNSTRCTOR_INIT_SUPER_TYPE, i) \
				{ \
				} \
 \
				template <KERBAL_PPEXPAND_WITH_COMMA_N(EACH_CONST_INIT_CNSTRCTOR_TARGS_DECL, i)> \
				KERBAL_CONSTEXPR \
				explicit tuple(KERBAL_PPEXPAND_WITH_COMMA_N(EACH_CONST_INIT_CNSTRCTOR_ARGS_DECL, i)) \
					KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COLON, EMPTY, EACH_CONST_INIT_CNSTRCTOR_INIT_SUPER_TYPE, i) \
				{ \
				} \
 \
				template <KERBAL_PPEXPAND_WITH_COMMA_N(VARIANCE_INIT_CNSTRCTOR_TARGS_DECL, i)> \
				KERBAL_CONSTEXPR \
				explicit tuple(const kerbal::utility::tuple<KERBAL_PPEXPAND_WITH_COMMA_N(VARIANCE_INIT_CNSTRCTOR_TARGS_USE, i)> & t) \
					KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COLON, EMPTY, VARIANCE_INIT_CNSTRCTOR_INIT_SUPER_TYPE, i) \
				{ \
				} \
 \
				template <KERBAL_PPEXPAND_WITH_COMMA_N(VARIANCE_ASSIGN_TARGS_DECL, i)> \
				KERBAL_CONSTEXPR14 \
				tuple & operator=(const kerbal::utility::tuple<KERBAL_PPEXPAND_WITH_COMMA_N(VARIANCE_ASSIGN_TARGS_USE, i)> & t) \
				{ \
					KERBAL_PPEXPAND_WITH_COMMA_N(VARIANCE_ASSIGN_EACH_ASSIGN, i); \
					return *this; \
				} \
 \
			public: \
 \
				KERBAL_CONSTEXPR \
				std::size_t size() const KERBAL_NOEXCEPT \
				{ \
					return TUPLE_SIZE::value; \
				} \
 \
				template <std::size_t I> \
				KERBAL_CONSTEXPR14 \
				typename reference<I>::type \
				get() KERBAL_NOEXCEPT \
				{ \
					KERBAL_STATIC_ASSERT(I < TUPLE_SIZE::value, "Index out of range"); \
					return super<I>::type::member(); \
				} \
 \
				template <std::size_t I> \
				KERBAL_CONSTEXPR \
				typename const_reference<I>::type \
				get() const KERBAL_NOEXCEPT \
				{ \
					KERBAL_STATIC_ASSERT(I < TUPLE_SIZE::value, "Index out of range"); \
					return super<I>::type::member(); \
				} \
 \
				template <std::size_t I> \
				KERBAL_CONSTEXPR \
				typename const_reference<I>::type \
				cget() const KERBAL_NOEXCEPT \
				{ \
					KERBAL_STATIC_ASSERT(I < TUPLE_SIZE::value, "Index out of range"); \
					return super<I>::type::member(); \
				} \
 \
				KERBAL_CONSTEXPR14 \
				kerbal::utility::tuple<KERBAL_PPEXPAND_WITH_COMMA_N(REF_EACH_TYPE, i)> \
				ref() KERBAL_NOEXCEPT \
				{ \
					return kerbal::utility::tuple<KERBAL_PPEXPAND_WITH_COMMA_N(REF_EACH_TYPE, i)> \
						(KERBAL_PPEXPAND_WITH_COMMA_N(REF_EACH_GET, i)); \
				} \
 \
				KERBAL_CONSTEXPR14 \
				kerbal::utility::tuple<KERBAL_PPEXPAND_WITH_COMMA_N(CREF_EACH_TYPE, i)> \
				ref() const KERBAL_NOEXCEPT \
				{ \
					return kerbal::utility::tuple<KERBAL_PPEXPAND_WITH_COMMA_N(CREF_EACH_TYPE, i)> \
						(KERBAL_PPEXPAND_WITH_COMMA_N(CREF_EACH_GET, i)); \
				} \
 \
				KERBAL_CONSTEXPR14 \
				kerbal::utility::tuple<KERBAL_PPEXPAND_WITH_COMMA_N(CREF_EACH_TYPE, i)> \
				cref() const KERBAL_NOEXCEPT \
				{ \
					return kerbal::utility::tuple<KERBAL_PPEXPAND_WITH_COMMA_N(CREF_EACH_TYPE, i)> \
						(KERBAL_PPEXPAND_WITH_COMMA_N(CREF_EACH_GET, i)); \
				} \
 \
				template <typename F> \
				KERBAL_CONSTEXPR14 \
				tuple & for_each(F f) \
				{ \
					KERBAL_PPEXPAND_WITH_COMMA_N(FOR_EACH_EACH_APPLY, i); \
					return *this; \
				} \
 \
				template <typename F> \
				KERBAL_CONSTEXPR14 \
				const tuple & for_each(F f) const \
				{ \
					KERBAL_PPEXPAND_WITH_COMMA_N(FOR_EACH_EACH_APPLY, i); \
					return *this; \
				} \
 \
				template <typename F> \
				KERBAL_CONSTEXPR14 \
				tuple & rfor_each(F f) \
				{ \
					KERBAL_PPEXPAND_WITH_COMMA_N(RFOR_EACH_EACH_APPLY, i); \
					return *this; \
				} \
 \
				template <typename F> \
				KERBAL_CONSTEXPR14 \
				const tuple & rfor_each(F f) const \
				{ \
					KERBAL_PPEXPAND_WITH_COMMA_N(RFOR_EACH_EACH_APPLY, i); \
					return *this; \
				} \
 \
				template <typename F> \
				KERBAL_CONSTEXPR14 \
				tuple & visit(std::size_t idx, F f) \
				{ \
					KERBAL_PPEXPAND_WITH_COMMA_N(VISIT_APPLY, i); \
					return *this; \
				} \
 \
				template <typename F> \
				KERBAL_CONSTEXPR14 \
				const tuple & visit(std::size_t idx, F f) const \
				{ \
					KERBAL_PPEXPAND_WITH_COMMA_N(VISIT_APPLY, i); \
					return *this; \
				} \
 \
				KERBAL_CONSTEXPR14 \
				kerbal::utility::tuple<KERBAL_PPEXPAND_WITH_COMMA_N(REVERSE_EACH_TYPE, i)> \
				reverse() const \
				{ \
					return kerbal::utility::tuple<KERBAL_PPEXPAND_WITH_COMMA_N(REVERSE_EACH_TYPE, i)> \
						(KERBAL_PPEXPAND_WITH_COMMA_N(REVERSE_EACH_GET, i)); \
				} \
 \
				KERBAL_CONSTEXPR14 \
				void swap(tuple & ano) \
				{ \
					KERBAL_PPEXPAND_WITH_COMMA_N(SWAP_EACH_SWAP, i); \
				} \
 \
 \
			protected: \
 \
				template <std::size_t N> \
				KERBAL_CONSTEXPR \
				bool k_equal_to_impl(const tuple & ano, kerbal::type_traits::integral_constant<std::size_t, N>) const \
				{ \
					typedef kerbal::compare::equal_to<typename value_type<N>::type> Pred; \
					return \
						static_cast<bool>(Pred()(this->template get<N>(), ano.template get<N>())) && \
						this->k_equal_to_impl(ano, kerbal::type_traits::integral_constant<std::size_t, N + 1>()); \
				} \
 \
				KERBAL_CONSTEXPR \
				bool k_equal_to_impl(const tuple & ano, kerbal::type_traits::integral_constant<std::size_t, TUPLE_SIZE::value>) const \
				{ \
					return true; \
				} \
 \
			public: \
 \
				KERBAL_CONSTEXPR \
				bool operator==(const tuple & ano) const \
				{ \
					return this->k_equal_to_impl(ano, kerbal::type_traits::integral_constant<std::size_t, 0>()); \
				} \
 \
 \
			protected: \
 \
				template <std::size_t N> \
				KERBAL_CONSTEXPR \
				bool k_not_equal_to_impl(const tuple & ano, kerbal::type_traits::integral_constant<std::size_t, N>) const \
				{ \
					typedef kerbal::compare::not_equal_to<typename value_type<N>::type> Pred; \
					return \
						static_cast<bool>(Pred()(this->template get<N>(), ano.template get<N>())) || \
						this->k_not_equal_to_impl(ano, kerbal::type_traits::integral_constant<std::size_t, N + 1>()); \
				} \
 \
				KERBAL_CONSTEXPR \
				bool k_not_equal_to_impl(const tuple & ano, kerbal::type_traits::integral_constant<std::size_t, TUPLE_SIZE::value>) const \
				{ \
					return false; \
				} \
 \
			public: \
 \
				KERBAL_CONSTEXPR \
				bool operator!=(const tuple & ano) const \
				{ \
					return this->k_not_equal_to_impl(ano, kerbal::type_traits::integral_constant<std::size_t, 0>()); \
				} \
 \
 \
			protected: \
 \
				template <std::size_t N> \
				KERBAL_CONSTEXPR \
				bool k_less_impl(const tuple & ano, kerbal::type_traits::integral_constant<std::size_t, N>) const \
				{ \
					typedef kerbal::compare::less<typename value_type<N>::type> Pred; \
					return \
						static_cast<bool>(Pred()(this->template get<N>(), ano.template get<N>())) /* *this < ano */ || \
						( \
							!static_cast<bool>(Pred()(ano.template get<N>(), this->template get<N>())) /* *this <= ano */ && \
							this->k_less_impl(ano, kerbal::type_traits::integral_constant<std::size_t, N + 1>()) \
						); \
				} \
 \
				KERBAL_CONSTEXPR \
				bool k_less_impl(const tuple & ano, kerbal::type_traits::integral_constant<std::size_t, TUPLE_SIZE::value>) const \
				{ \
					return false; \
				} \
 \
			public: \
 \
				KERBAL_CONSTEXPR \
				bool operator<(const tuple & ano) const \
				{ \
					return this->k_less_impl(ano, kerbal::type_traits::integral_constant<std::size_t, 0>()); \
				} \
 \
 \
			protected: \
 \
				template <std::size_t N> \
				KERBAL_CONSTEXPR \
				bool k_greater_impl(const tuple & ano, kerbal::type_traits::integral_constant<std::size_t, N>) const \
				{ \
					typedef kerbal::compare::greater<typename value_type<N>::type> Pred; \
					return \
						static_cast<bool>(Pred()(this->template get<N>(), ano.template get<N>())) /* *this > ano */ || \
						( \
							!static_cast<bool>(Pred()(ano.template get<N>(), this->template get<N>())) /* *this >= ano */ && \
							this->k_greater_impl(ano, kerbal::type_traits::integral_constant<std::size_t, N + 1>()) \
						); \
				} \
 \
				KERBAL_CONSTEXPR \
				bool k_greater_impl(const tuple & ano, kerbal::type_traits::integral_constant<std::size_t, TUPLE_SIZE::value>) const \
				{ \
					return false; \
				} \
 \
			public: \
 \
				KERBAL_CONSTEXPR \
				bool operator>(const tuple & ano) const \
				{ \
					return this->k_greater_impl(ano, kerbal::type_traits::integral_constant<std::size_t, 0>()); \
				} \
 \
 \
			protected: \
 \
				template <std::size_t N> \
				KERBAL_CONSTEXPR \
				bool k_less_equal_impl(const tuple & ano, kerbal::type_traits::integral_constant<std::size_t, N>) const \
				{ \
					typedef kerbal::compare::less_equal<typename value_type<N>::type> Pred; \
					return \
						static_cast<bool>(Pred()(this->template get<N>(), ano.template get<N>())) /* *this <= ano */ && \
						( \
							static_cast<bool>(Pred()(ano.template get<N>(), this->template get<N>())) ? /* ano <= *this */ \
							this->k_less_equal_impl(ano, kerbal::type_traits::integral_constant<std::size_t, N + 1>()) : /* *this == ano */ \
							true /* *this < ano */ \
						); \
				} \
 \
				KERBAL_CONSTEXPR \
				bool k_less_equal_impl(const tuple & ano, kerbal::type_traits::integral_constant<std::size_t, TUPLE_SIZE::value>) const \
				{ \
					return true; \
				} \
 \
			public: \
 \
				KERBAL_CONSTEXPR \
				bool operator<=(const tuple & ano) const \
				{ \
					return this->k_less_equal_impl(ano, kerbal::type_traits::integral_constant<std::size_t, 0>()); \
				} \
 \
 \
			protected: \
 \
				template <std::size_t N> \
				KERBAL_CONSTEXPR \
				bool k_greater_equal_impl(const tuple & ano, kerbal::type_traits::integral_constant<std::size_t, N>) const \
				{ \
					typedef kerbal::compare::greater_equal<typename value_type<N>::type> Pred; \
					return \
						static_cast<bool>(Pred()(this->template get<N>(), ano.template get<N>())) /* *this >= ano */ && \
						( \
							static_cast<bool>(Pred()(ano.template get<N>(), this->template get<N>())) ? /* ano >= *this */ \
							this->k_greater_equal_impl(ano, kerbal::type_traits::integral_constant<std::size_t, N + 1>()) : /* *this == ano */ \
							true /* *this > ano */ \
						); \
				} \
 \
				KERBAL_CONSTEXPR \
				bool k_greater_equal_impl(const tuple & ano, kerbal::type_traits::integral_constant<std::size_t, TUPLE_SIZE::value>) const \
				{ \
					return true; \
				} \
 \
			public: \
 \
				KERBAL_CONSTEXPR \
				bool operator>=(const tuple & ano) const \
				{ \
					return this->k_greater_equal_impl(ano, kerbal::type_traits::integral_constant<std::size_t, 0>()); \
				} \
 \
		}; \

		KERBAL_PPEXPAND_N(DBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 19)

#	undef EMPTY
#	undef REMAINF
#	undef LEFT_JOIN_COLON
#	undef TARGS_DECL
#	undef TARGS_USE
#	undef SUPER_TYPE
#	undef SUPER_TYPEDEF_USE
#	undef DFT_CNSTRCTOR_INIT_SUPER_TYPE

#	undef EACH_INIT_CNSTRCTOR_TARGS_DECL
#	undef EACH_INIT_CNSTRCTOR_ARGS_DECL
#	undef EACH_INIT_CNSTRCTOR_INIT_SUPER_TYPE

#	undef EACH_CONST_INIT_CNSTRCTOR_TARGS_DECL
#	undef EACH_CONST_INIT_CNSTRCTOR_ARGS_DECL
#	undef EACH_CONST_INIT_CNSTRCTOR_INIT_SUPER_TYPE

#	undef VARIANCE_INIT_CNSTRCTOR_TARGS_DECL
#	undef VARIANCE_INIT_CNSTRCTOR_TARGS_USE
#	undef VARIANCE_INIT_CNSTRCTOR_INIT_SUPER_TYPE

#	undef VARIANCE_ASSIGN_TARGS_DECL
#	undef VARIANCE_ASSIGN_TARGS_USE
#	undef VARIANCE_ASSIGN_EACH_ASSIGN

#	undef REF_EACH_TYPE
#	undef REF_EACH_GET

#	undef CREF_EACH_TYPE
#	undef CREF_EACH_GET

#	undef FOR_EACH_EACH_APPLY
#	undef RFOR_EACH_EACH_APPLY

#	undef REVERSE_EACH_TYPE
#	undef REVERSE_EACH_GET

#	undef SWAP_EACH_SWAP
#	undef DBODY


#	define EMPTY
#	define REMAINF(exp) exp
#	define THEAD_NOT_EMPTY(exp) template <exp>
#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define TARGS_USE(i) KERBAL_MACRO_CONCAT(Arg, i)
#	define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#	define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#	define FBODY(i) \
		KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
		inline \
		kerbal::utility::tuple<KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_USE, i)> \
		make_tuple(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
		{ \
			return kerbal::utility::tuple<KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_USE, i)>( \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i) \
			); \
		} \

		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 19)

#	undef EMPTY
#	undef REMAINF
#	undef THEAD_NOT_EMPTY
#	undef TARGS_DECL
#	undef TARGS_USE
#	undef ARGS_DECL
#	undef ARGS_USE
#	undef FBODY


#	define EMPTY
#	define REMAINF(exp) exp
#	define THEAD_NOT_EMPTY(exp) template <exp>
#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define TARGS_USE(i) KERBAL_MACRO_CONCAT(Arg, i) &
#	define ARGS_DECL(i) KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#	define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#	define FBODY(i) \
		KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
		inline \
		kerbal::utility::tuple<KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_USE, i)> \
		tie(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
		{ \
			return kerbal::utility::tuple<KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_USE, i)>( \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i) \
			); \
		} \

		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 19)

#	undef EMPTY
#	undef REMAINF
#	undef THEAD_NOT_EMPTY
#	undef TARGS_DECL
#	undef TARGS_USE
#	undef ARGS_DECL
#	undef ARGS_USE
#	undef FBODY


	} // namespace utility


	namespace algorithm
	{

#	define EMPTY
#	define REMAINF(exp) exp
#	define THEAD_NOT_EMPTY(exp) template <exp>
#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define TARGS_USE(i) KERBAL_MACRO_CONCAT(Arg, i)
#	define FBODY(i) \
		KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
		inline \
		void swap( \
			kerbal::utility::tuple<KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_USE, i)> & a, \
			kerbal::utility::tuple<KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_USE, i)> & b \
		) \
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b))) \
		{ \
			a.swap(b); \
		} \

		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 19)

#	undef EMPTY
#	undef REMAINF
#	undef THEAD_NOT_EMPTY
#	undef TARGS_DECL
#	undef TARGS_USE
#	undef FBODY

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

#	define EMPTY
#	define REMAINF(exp) exp
#	define THEAD_NOT_EMPTY(exp) template <exp>
#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define TARGS_USE(i) KERBAL_MACRO_CONCAT(Arg, i)
#	define FBODY(i) \
	KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
	inline \
	void swap( \
		kerbal::utility::tuple<KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_USE, i)> & a, \
		 kerbal::utility::tuple<KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, TARGS_USE, i)> & b \
	) \
		KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b))) \
	{ \
		a.swap(b); \
	} \

	KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
	KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 19)

#	undef EMPTY
#	undef REMAINF
#	undef THEAD_NOT_EMPTY
#	undef TARGS_DECL
#	undef TARGS_USE
#	undef FBODY

KERBAL_NAMESPACE_STD_END

#endif // KERBAL_UTILITY_TUPLE_DETAIL_TUPLE_CXX98_PART_HPP
