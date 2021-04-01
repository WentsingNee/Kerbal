/**
 * @file       hash_table_node.hpp
 * @brief
 * @date       2020-10-31
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_HASH_TABLE_BASE_HASH_TABLE_NODE_HPP
#define KERBAL_CONTAINER_DETAIL_HASH_TABLE_BASE_HASH_TABLE_NODE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_same.hpp>
#include <kerbal/utility/member_compress_helper.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#include <kerbal/container/detail/hash_table_base/hash_table_base.fwd.hpp>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Entity, typename Hash>
			struct hash_node_traits
			{
				private:
					typedef typename Hash::result_type hash_result_type;
					typedef kerbal::container::cache_hash_result<Entity, Hash> cache_hash_result;

				public:
					typedef typename kerbal::type_traits::conditional<
							cache_hash_result::value,
							hash_result_type,
							not_cache_hash_result_wrapper<hash_result_type>
					>::type hash_result_cache_policy;

					typedef hash_table_node<Entity, hash_result_cache_policy> node_type;
			};



			class hash_table_node_type_unrelated
			{
				private:
					template <typename Entity2,
							typename Extract,
							typename HashCachePolicy
					>
					friend class kerbal::container::detail::hash_table_base;

					template <typename Entity>
					friend class kerbal::container::detail::hash_table_iter;

					template <typename Entity>
					friend class kerbal::container::detail::hash_table_kiter;

				protected:
					hash_table_node_type_unrelated * k_next;

				public:
					KERBAL_CONSTEXPR
					hash_table_node_type_unrelated() KERBAL_NOEXCEPT
							: k_next(NULL)
					{
					}
			};



			template <typename Entity>
			class hash_table_node_type_only:
					protected hash_table_node_type_unrelated,
					protected kerbal::utility::member_compress_helper<Entity>
			{
				private:
					typedef hash_table_node_type_unrelated super;
					typedef kerbal::utility::member_compress_helper<Entity> data;

					template <typename Entity2,
							typename Extract,
							typename HashCachePolicy
					>
					friend class kerbal::container::detail::hash_table_base;

					friend class kerbal::container::detail::hash_table_node_type_unrelated;

					friend class kerbal::container::detail::hash_table_iter<Entity>;
					friend class kerbal::container::detail::hash_table_kiter<Entity>;

				public:

#		if __cplusplus >= 201103L
					template <typename ... Args>
					KERBAL_CONSTEXPR
					explicit hash_table_node_type_only(kerbal::utility::in_place_t in_place, Args && ... args)
							: data(in_place, kerbal::utility::forward<Args>(args)...)
					{
					}
#		else

#				define EMPTY
#				define LEFT_JOIN_COMMA(exp) , exp
#				define THEAD_NOT_EMPTY(exp) template <exp>
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
					explicit hash_table_node_hash_unrelated(kerbal::utility::in_place_t in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
							: data(in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)) \
					{ \
					}

					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#				undef EMPTY
#				undef LEFT_JOIN_COMMA
#				undef THEAD_NOT_EMPTY
#				undef TARGS_DECL
#				undef ARGS_DECL
#				undef ARGS_USE
#				undef FBODY

#		endif

			};

			template <typename Entity, typename HashCachePolicy>
			class hash_table_node:
					protected hash_table_node_type_only<Entity>
			{
				private:
					typedef hash_table_node_type_only<Entity> super;

					template <typename Entity2,
							typename Extract,
							typename HashCachePolicy2
					>
					friend class kerbal::container::detail::hash_table_base;

				protected:
					typedef kerbal::type_traits::true_type		CACHE_HASH_RESULT;
					typedef HashCachePolicy						hash_result_type;

					hash_result_type k_hash_code;

				public:

#		if __cplusplus >= 201103L
					using super::super;
#		else

#				define EMPTY
#				define LEFT_JOIN_COMMA(exp) , exp
#				define THEAD_NOT_EMPTY(exp) template <exp>
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
					explicit hash_table_node(kerbal::utility::in_place_t in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
							: super(in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)) \
					{ \
					}

					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#				undef EMPTY
#				undef LEFT_JOIN_COMMA
#				undef THEAD_NOT_EMPTY
#				undef TARGS_DECL
#				undef ARGS_DECL
#				undef ARGS_USE
#				undef FBODY

#		endif

					KERBAL_CONSTEXPR14
					void set_cached_hash_code(hash_result_type hash_code) KERBAL_NOEXCEPT
					{
						this->k_hash_code = hash_code;
					}

					template <typename Extract, typename Hash>
					KERBAL_CONSTEXPR
					hash_result_type get_cached_hash_code(Extract & /*extract*/, const Hash & /*hash*/) const KERBAL_NOEXCEPT
					{
						KERBAL_STATIC_ASSERT((kerbal::type_traits::is_same<typename Hash::result_type, hash_result_type>::value), "hash result type not matched!");
						return this->k_hash_code;
					}
			};

			template <typename Entity, typename HashResult>
			class hash_table_node<Entity, not_cache_hash_result_wrapper<HashResult> >:
					protected hash_table_node_type_only<Entity>
			{
				private:
					typedef hash_table_node_type_only<Entity> super;

					template <typename Entity2,
							typename Extract,
							typename HashCachePolicy2
					>
					friend class kerbal::container::detail::hash_table_base;

				protected:
					typedef kerbal::type_traits::false_type		CACHE_HASH_RESULT;
					typedef HashResult							hash_result_type;

#		if __cplusplus >= 201103L
					using super::super;
#		else

#				define EMPTY
#				define LEFT_JOIN_COMMA(exp) , exp
#				define THEAD_NOT_EMPTY(exp) template <exp>
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
					explicit hash_table_node(kerbal::utility::in_place_t in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
							: super(in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)) \
					{ \
					}

					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#				undef EMPTY
#				undef LEFT_JOIN_COMMA
#				undef THEAD_NOT_EMPTY
#				undef TARGS_DECL
#				undef ARGS_DECL
#				undef ARGS_USE
#				undef FBODY

#		endif

					KERBAL_CONSTEXPR14
					void set_cached_hash_code(hash_result_type /*hash_code*/) KERBAL_NOEXCEPT
					{
					}

					template <typename Extract, typename Hash>
					KERBAL_CONSTEXPR
					hash_result_type get_cached_hash_code(Extract & extract, Hash & hash) const
					{
						KERBAL_STATIC_ASSERT((kerbal::type_traits::is_same<typename Hash::result_type, hash_result_type>::value), "hash result type not matched!");
						return hash(extract(this->member()));
					}
			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_HASH_TABLE_BASE_HASH_TABLE_NODE_HPP
