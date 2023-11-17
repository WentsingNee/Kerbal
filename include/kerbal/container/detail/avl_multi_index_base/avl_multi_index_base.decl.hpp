/**
 * @file       avl_multi_index_base.decl.hpp
 * @brief
 * @date       2023-11-16
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science &
 * Technology](http://www.nuist.edu.cn/) all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_AVL_MULTI_INDEX_BASE_AVL_MULTI_INDEX_BASE_DECL_HPP
#define KERBAL_CONTAINER_DETAIL_AVL_MULTI_INDEX_BASE_AVL_MULTI_INDEX_BASE_DECL_HPP

#include <kerbal/container/detail/avl_multi_index_base/avl_multi_index_policy.hpp>
#include <kerbal/container/detail/avl_multi_index_base/avl_multi_index_node.hpp>
#include <kerbal/container/detail/avl_multi_index_base/avl_multi_index_iterator.hpp>

#include <kerbal/container/detail/avl_base/avl_base.decl.hpp>

#include <kerbal/container/associative_container_facility/key_extractors/tuple_index_extractor.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/tmp/type_vector.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/utility/forward.hpp>
#include <kerbal/utility/integer_sequence.hpp>
#include <kerbal/utility/member_compress_helper.hpp>
#include <kerbal/utility/tuple.hpp>

#include <cstddef>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename T, typename Tuple, std::size_t ... Index>
			KERBAL_CONSTEXPR
			auto tuple_push_front_impl(T && t, Tuple && tuple, kerbal::utility::index_sequence<Index...>)
			{
				return kerbal::utility::make_tuple(
					kerbal::utility::forward<T>(t),
					kerbal::utility::forward<Tuple>(tuple).template get<Index>()...
				);
			}

			template <typename T, typename Tuple>
			KERBAL_CONSTEXPR
			auto tuple_push_front(T && t, Tuple && tuple)
			{
				typedef typename kerbal::type_traits::remove_reference<Tuple>::type remove_ref;

				return tuple_push_front_impl(
					kerbal::utility::forward<T>(t),
					kerbal::utility::forward<Tuple>(tuple),
					kerbal::utility::make_index_sequence<remove_ref::TUPLE_SIZE::value>()
				);
			}

			template <typename Entity, typename ... PolicyField>
			struct avl_multi_index_base_typedef_helper
			{
					typedef kerbal::tmp::type_vector<PolicyField...> policy_vector;

					template <std::size_t I>
					struct policy_by_id
					{
						typedef typename kerbal::tmp::type_vector_at<policy_vector, I>::result type;
					};

					template <std::size_t I>
					struct policy_traits_by_id
					{
						typedef kerbal::container::detail::avl_multi_index_policy_traits<typename policy_by_id<I>::type> type;
					};

					template <std::size_t I>
					struct key_type_by_id
					{
						typedef typename policy_traits_by_id<I>::type::key_type type;
					};

					typedef Entity data;
					typedef kerbal::container::detail::avl_type_only<Entity> avl_type_only;

					template <std::size_t I>
					struct super
					{
						typedef kerbal::utility::member_compress_helper<avl_type_only, I> type;
					};

			};


			template <typename Entity, typename ... PolicyField>
			class avl_multi_index_base :
					protected kerbal::utility::tuple<
						typename kerbal::type_traits::conditional<
							true,
							typename avl_multi_index_base_typedef_helper<Entity, PolicyField...>::avl_type_only,
							PolicyField
						>::type ...
					>
			{
				private:
					typedef avl_multi_index_base_typedef_helper<Entity, PolicyField...> typedef_helper;
					typedef typename typedef_helper::avl_type_only avl_type_only;

				public:
					typedef kerbal::type_traits::integral_constant<std::size_t, sizeof...(PolicyField)> KeyCount;

					template <std::size_t I>
					struct super :
							typedef_helper::template super<I>
					{
					};

					template <std::size_t I>
					struct policy_by_id :
							typedef_helper::template policy_by_id<I>
					{
					};

					template <std::size_t I>
					struct policy_traits_by_id :
							typedef_helper::template policy_traits_by_id<I>
					{
					};

					template <std::size_t I>
					struct extractor_by_id
					{
							typedef typename policy_traits_by_id<I>::type::extractor type;
					};

					template <std::size_t I>
					struct key_type_by_id
					{
							typedef typename policy_traits_by_id<I>::type::key_type type;
					};

					template <std::size_t I>
					struct key_compare_by_id
					{
							typedef typename policy_traits_by_id<I>::type::key_compare type;
					};

					template <std::size_t I>
					struct is_unique_by_id :
							kerbal::type_traits::bool_constant<policy_traits_by_id<I>::type::is_unique::value>
					{
					};

					typedef typename typedef_helper::data		data;
					typedef kerbal::container::detail::avl_multi_index_node<
							data,
							KeyCount::value
					> node;

					// typedef typename avl_type_only::value_type			value_type;
					// typedef typename avl_type_only::const_type			const_type;
					// typedef typename avl_type_only::reference			reference;
					// typedef typename avl_type_only::const_reference		const_reference;
					// typedef typename avl_type_only::pointer				pointer;
					// typedef typename avl_type_only::const_pointer		const_pointer;

					template <std::size_t I>
					struct iterator_by_id
					{
						typedef kerbal::container::detail::avl_multi_index_iter<
							Entity, KeyCount::value, I
						> type;
					};

				public:

#		if __cplusplus >= 201103L
					avl_multi_index_base() = default;
#		else
					avl_multi_index_base();
#		endif


				private:
					template <std::size_t I>
					KERBAL_CONSTEXPR14
					avl_type_only & avl_tree_by_index() KERBAL_NOEXCEPT
					{
						return static_cast<typename super<I>::type &>(*this).member();
					}

				public:
					template <std::size_t I>
					KERBAL_CONSTEXPR14
					typename iterator_by_id<I>::type
					begin_by_id() KERBAL_NOEXCEPT
					{
						return typename iterator_by_id<I>::type(avl_tree_by_index<I>().begin_());
					}

					template <std::size_t I>
					typename iterator_by_id<I>::type
					end_by_id()
					{
						return typename iterator_by_id<I>::type(avl_tree_by_index<I>().end_());
					}

				public:

					template <std::size_t I>
					auto hook_duplicate_detected_branch_impl(kerbal::type_traits::false_type /*is_final*/)
					{
						avl_type_only & tree = avl_tree_by_index<I>();
						return tuple_push_front(tree.end(), hook_duplicate_detected_branch<I + 1>());
					}

					template <std::size_t I>
					auto hook_duplicate_detected_branch_impl(kerbal::type_traits::true_type /*is_final*/)
					{
						avl_type_only & tree = avl_tree_by_index<I>();
						return kerbal::utility::make_tuple(tree.end());
					}

					template <std::size_t I>
					auto hook_duplicate_detected_branch()
					{
						return hook_duplicate_detected_branch_impl<I>(
							kerbal::type_traits::bool_constant<I == KeyCount::value - 1>()
						);
					}

					template <std::size_t I>
					auto hook_impl(node * p, bool & inserted, kerbal::type_traits::false_type /*is_unique*/, kerbal::type_traits::false_type /*is_final*/)
					{
						typename extractor_by_id<I>::type e;
						typename key_compare_by_id<I>::type kc;
						avl_type_only & tree = avl_tree_by_index<I>();
						auto context = tree.k_prepare_hook_node(e, kc, p, typename node::template up_caster<I>());

						auto res = hook<I + 1>(p, inserted);

						if (!inserted) {
							return tuple_push_front(
								tree.k_complete_hook_node_duplicated(context),
								res
							);
						}

						return tuple_push_front(
							tree.k_complete_hook_node(context, &p->template as_avl_node_base_by_id<I>()),
							res
						);
					}


					template <std::size_t I>
					auto hook_impl(node * p, bool & inserted, kerbal::type_traits::true_type /*is_unique*/, kerbal::type_traits::false_type /*is_final*/)
					{
						typename extractor_by_id<I>::type e;
						typename key_compare_by_id<I>::type kc;
						avl_type_only & tree = avl_tree_by_index<I>();
						auto context = tree.k_prepare_hook_node_unique(e, kc, &p->template as_avl_node_base_by_id<I>(), typename node::template up_caster<I>());

						if (context.duplicated()) {
							inserted = false;
							return tuple_push_front(
								tree.k_complete_hook_node_duplicated(context),
								hook_duplicate_detected_branch<I + 1>()
							);
						}

						auto res = hook<I + 1>(p, inserted);

						if (!inserted) {
							return tuple_push_front(
								tree.k_complete_hook_node_duplicated(context),
								res
							);
						}

						return tuple_push_front(
							tree.k_complete_hook_node_unique(context, &p->template as_avl_node_base_by_id<I>()),
							res
						);
					}


					template <std::size_t I>
					kerbal::utility::tuple<typename avl_type_only::iterator>
					hook_impl(node * p, bool & inserted, kerbal::type_traits::false_type /*is_unique*/, kerbal::type_traits::true_type /*is_final*/)
					{
						typename extractor_by_id<I>::type e;
						typename key_compare_by_id<I>::type kc;
						avl_type_only & tree = avl_tree_by_index<I>();
						return kerbal::utility::make_tuple(
							tree.k_emplace_hook_node(e, kc, &p->template as_avl_node_base_by_id<I>(), typename node::template up_caster<I>())
						);
					}


					template <std::size_t I>
					kerbal::utility::tuple<typename avl_type_only::iterator>
					hook_impl(node * p, bool & inserted, kerbal::type_traits::true_type /*is_unique*/, kerbal::type_traits::true_type /*is_final*/)
					{
						typename extractor_by_id<I>::type e;
						typename key_compare_by_id<I>::type kc;
						avl_type_only & tree = avl_tree_by_index<I>();
						auto uir = tree.k_emplace_hook_node_unique(e, kc, &p->template as_avl_node_base_by_id<I>(), typename node::template up_caster<I>());
						if (!uir.insert_happen()) {
							inserted = false;
						}
						return kerbal::utility::make_tuple(uir.position());
					}

					template <std::size_t I>
					auto hook(node * p, bool & inserted)
					{
						return hook_impl<I>(
							p, inserted,
							is_unique_by_id<I>(),
							kerbal::type_traits::bool_constant<I == KeyCount::value - 1>()
						);
					}

					template <typename Allocator, typename ... Key>
					auto
					insert_using_allocator(Allocator & alloc, Key && ... key)
					{
						node * p = k_build_node(alloc, kerbal::utility::forward<Key>(key)...);

						try {
							bool inserted = true;
							return tuple_push_front(
								inserted,
								hook<0>(p, inserted)
							);
						} catch (...) {
							k_destroy_node(alloc, p);
							throw;
						}
					}

					template <typename ... Key>
					auto
					insert(Key && ... key)
					{
						std::allocator<node> alloc;
						return this->insert_using_allocator(alloc, kerbal::utility::forward<Key>(key)...);
					}

				private:

					template <typename Allocator, typename ... Key>
					node * k_build_node(Allocator & alloc, Key && ... key)
					{
						typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

						node * p = allocator_traits::allocate_one(alloc);
						try {
							allocator_traits::construct(alloc, p, kerbal::utility::forward<Key>(key)...);
						} catch (...) {
							allocator_traits::deallocate_one(alloc, p);
							throw;
						}
						return p;
					}

					template <typename Allocator>
					void k_destroy_node(Allocator & alloc, node * p)
					{
						typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

						allocator_traits::destroy(alloc, p);
						allocator_traits::deallocate_one(alloc, p);
					}

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_AVL_MULTI_INDEX_BASE_AVL_MULTI_INDEX_BASE_DECL_HPP
