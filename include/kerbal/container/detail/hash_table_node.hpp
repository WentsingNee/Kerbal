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

#ifndef KERBAL_CONTAINER_DETAIL_HASH_TABLE_NODE_HPP
#define KERBAL_CONTAINER_DETAIL_HASH_TABLE_NODE_HPP

#include <kerbal/container/fwd/hash_table.fwd.hpp>

#include <kerbal/container/detail/single_list_node.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/fundamental_deduction.hpp>
#include <kerbal/type_traits/integral_constant.hpp>


namespace kerbal
{

	namespace container
	{

		template <typename Entity, typename Hash>
		struct cache_hash_result :
				kerbal::type_traits::bool_constant<
						kerbal::type_traits::is_floating_point<Entity>::value
				>
		{
		};

		namespace detail
		{

			template <typename Entity, typename Hash, bool CacheHashResult = kerbal::container::cache_hash_result<Entity, Hash>::value>
			class hash_table_node;

			template <typename Entity, typename Hash>
			class hash_table_node<Entity, Hash, false> :
					public kerbal::container::detail::sl_node<Entity>
			{
				private:
					typedef kerbal::container::detail::sl_node<Entity> super;

					template <typename Entity2,
							typename Extract,
							typename Hash2,
							typename KeyEqual,
							typename NodeAllocatorBR,
							typename BucketAllocatorBR
					>
					friend class kerbal::container::hash_table;

				protected:
					typedef kerbal::type_traits::false_type		CACHE_HASH_CODE;
					typedef typename Hash::result_type			hash_code_type;

#		if __cplusplus < 201103L

					explicit hash_table_node(kerbal::utility::in_place_t in_place)
							: super(in_place)
					{
					}

					template <typename Arg0>
					explicit hash_table_node(kerbal::utility::in_place_t in_place, const Arg0 & arg0)
							: super(in_place, arg0)
					{
					}

					template <typename Arg0, typename Arg1>
					explicit hash_table_node(kerbal::utility::in_place_t in_place, const Arg0 & arg0, const Arg1 & arg1)
							: super(in_place, arg0, arg1)
					{
					}

					template <typename Arg0, typename Arg1, typename Arg2>
					explicit hash_table_node(kerbal::utility::in_place_t in_place, const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2)
							: super(in_place, arg0, arg1, arg2)
					{
					}

#		else
					using super::super;
#		endif

					KERBAL_CONSTEXPR14
					void set_cached_hash_code(hash_code_type /*hash_code*/) KERBAL_NOEXCEPT
					{
					}

					KERBAL_CONSTEXPR14
					hash_code_type get_cached_hash_code(Hash & hash) const
					{
						return hash(this->value);
					}
			};

			template <typename Entity, typename Hash>
			class hash_table_node<Entity, Hash, true> :
					public kerbal::container::detail::sl_node<Entity>
			{
				private:
					typedef kerbal::container::detail::sl_node<Entity> super;

					template <typename Entity2,
							typename Extract,
							typename Hash2,
							typename KeyEqual,
							typename NodeAllocatorBR,
							typename BucketAllocatorBR
					>
					friend class kerbal::container::hash_table;

				protected:
					typedef kerbal::type_traits::true_type		CACHE_HASH_CODE;
					typedef typename Hash::result_type			hash_code_type;

					hash_code_type _K_hash_code;

#		if __cplusplus < 201103L

					explicit hash_table_node(kerbal::utility::in_place_t in_place)
							: super(in_place)
					{
					}

					template <typename Arg0>
					explicit hash_table_node(kerbal::utility::in_place_t in_place, const Arg0 & arg0)
							: super(in_place, arg0)
					{
					}

					template <typename Arg0, typename Arg1>
					explicit hash_table_node(kerbal::utility::in_place_t in_place, const Arg0 & arg0, const Arg1 & arg1)
							: super(in_place, arg0, arg1)
					{
					}

					template <typename Arg0, typename Arg1, typename Arg2>
					explicit hash_table_node(kerbal::utility::in_place_t in_place, const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2)
							: super(in_place, arg0, arg1, arg2)
					{
					}

#		else
					using super::super;
#		endif

					KERBAL_CONSTEXPR14
					void set_cached_hash_code(hash_code_type hash_code) KERBAL_NOEXCEPT
					{
						this->_K_hash_code = hash_code;
					}

					KERBAL_CONSTEXPR
					hash_code_type get_cached_hash_code(const Hash & /*hash*/) const KERBAL_NOEXCEPT
					{
						return this->_K_hash_code;
					}
			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_HASH_TABLE_NODE_HPP
