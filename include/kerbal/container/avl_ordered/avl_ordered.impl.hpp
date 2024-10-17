/**
 * @file       avl_ordered.impl.hpp
 * @brief
 * @date       2022-09-08
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_AVL_ORDERED_AVL_ORDERED_IMPL_HPP
#define KERBAL_CONTAINER_AVL_ORDERED_AVL_ORDERED_IMPL_HPP

#include <kerbal/container/avl_ordered/avl_ordered.decl.hpp>
#include <kerbal/container/detail/avl_base/avl_base.impl.hpp>

#include <kerbal/assign/generic_assign.hpp>
#include <kerbal/assign/ilist.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/associative_container_facility/unique_tag_t.hpp>
#include <kerbal/utility/compressed_pair.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/compatibility/move.hpp>
#	include <kerbal/utility/forward.hpp>
#endif

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif


namespace kerbal
{

	namespace container
	{

		//===================
		// construct with empty

#	if __cplusplus < 201103L

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered()
		{
		}

#	endif

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(const Allocator & alloc) :
			avl_allocator_overload(alloc)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(const KeyCompare & key_comp) :
			key_compare_compress_helper(kerbal::utility::in_place_t(), key_comp)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(const KeyCompare & key_comp, const Allocator & alloc) :
			key_compare_compress_helper(kerbal::utility::in_place_t(), key_comp),
			avl_allocator_overload(alloc)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(const Extract & e) :
			extract_compress_helper(kerbal::utility::in_place_t(), e)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(const Extract & e, const Allocator & alloc) :
			extract_compress_helper(kerbal::utility::in_place_t(), e),
			avl_allocator_overload(alloc)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(const Extract & e, const KeyCompare & key_comp) :
			extract_compress_helper(kerbal::utility::in_place_t(), e),
			key_compare_compress_helper(kerbal::utility::in_place_t(), key_comp)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(const Extract & e, const KeyCompare & key_comp, const Allocator & alloc)  :
			extract_compress_helper(kerbal::utility::in_place_t(), e),
			key_compare_compress_helper(kerbal::utility::in_place_t(), key_comp),
			avl_allocator_overload(alloc)
		{
		}


		//===================
		// copy constructor

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(const avl_ordered & src) :
			extract_compress_helper(static_cast<const extract_compress_helper &>(src)),
			key_compare_compress_helper(static_cast<const key_compare_compress_helper &>(src)),
			avl_allocator_overload(src.alloc()),
			avl_type_only(
				this->alloc(), this->extract(), this->key_comp(),
				static_cast<const avl_type_only &>(src)
			)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(const avl_ordered & src, const Allocator & alloc) :
			extract_compress_helper(static_cast<const extract_compress_helper &>(src)),
			key_compare_compress_helper(static_cast<const key_compare_compress_helper &>(src)),
			avl_allocator_overload(alloc),
			avl_type_only(
				this->alloc(), this->extract(), this->key_comp(),
				static_cast<const avl_type_only &>(src)
			)
		{
		}

#	if __cplusplus >= 201103L

		//===================
		// move constructor

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(avl_ordered && src) :
			extract_compress_helper(static_cast<const extract_compress_helper &>(src)),
			key_compare_compress_helper(static_cast<const key_compare_compress_helper &>(src)),
			avl_allocator_overload(kerbal::compatibility::move(src.alloc())),
			avl_type_only(static_cast<avl_type_only &&>(src))
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(avl_ordered && src, const Allocator & alloc) :
			extract_compress_helper(static_cast<const extract_compress_helper &>(src)),
			key_compare_compress_helper(static_cast<const key_compare_compress_helper &>(src)),
			avl_allocator_overload(alloc),
			avl_type_only(
				this->alloc(), this->extract(), this->key_comp(),
				kerbal::compatibility::move(src.alloc()), static_cast<avl_type_only &&>(src)
			)
		{
		}

#	endif


		//===================
		// construct with iterators range

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			InputIterator first, InputIterator last
		) :
			avl_type_only(this->alloc(), this->extract(), this->key_comp(), first, last)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			InputIterator first, InputIterator last,
			const Allocator & alloc
		) :
			avl_allocator_overload(alloc),
			avl_type_only(this->alloc(), this->extract(), this->key_comp(), first, last)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			InputIterator first, InputIterator last,
			const KeyCompare & key_comp
		) :
			key_compare_compress_helper(kerbal::utility::in_place_t(), key_comp),
			avl_type_only(this->alloc(), this->extract(), this->key_comp(), first, last)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			InputIterator first, InputIterator last,
			const KeyCompare & key_comp, const Allocator & alloc
		) :
			key_compare_compress_helper(kerbal::utility::in_place_t(), key_comp),
			avl_allocator_overload(alloc),
			avl_type_only(this->alloc(), this->extract(), this->key_comp(), first, last)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			InputIterator first, InputIterator last,
			const Extract & e
		) :
			extract_compress_helper(kerbal::utility::in_place_t(), e),
			avl_type_only(this->alloc(), this->extract(), this->key_comp(), first, last)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			InputIterator first, InputIterator last,
			const Extract & e, const Allocator & alloc
		) :
			extract_compress_helper(kerbal::utility::in_place_t(), e),
			avl_allocator_overload(alloc),
			avl_type_only(this->alloc(), this->extract(), this->key_comp(), first, last)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			InputIterator first, InputIterator last,
			const Extract & e, const KeyCompare & key_comp
		) :
			extract_compress_helper(kerbal::utility::in_place_t(), e),
			key_compare_compress_helper(kerbal::utility::in_place_t(), key_comp),
			avl_type_only(this->alloc(), this->extract(), this->key_comp(), first, last)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			InputIterator first, InputIterator last,
			const Extract & e, const KeyCompare & key_comp, const Allocator & alloc
		) :
			extract_compress_helper(kerbal::utility::in_place_t(), e),
			key_compare_compress_helper(kerbal::utility::in_place_t(), key_comp),
			avl_allocator_overload(alloc),
			avl_type_only(this->alloc(), this->extract(), this->key_comp(), first, last)
		{
		}


		//===================
		// construct with iterators range (unique)

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			kerbal::container::unique_tag_t unique_tag,
			InputIterator first, InputIterator last
		) :
			avl_type_only(unique_tag, this->alloc(), this->extract(), this->key_comp(), first, last)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			kerbal::container::unique_tag_t unique_tag,
			InputIterator first, InputIterator last,
			const Allocator & alloc
		) :
			avl_allocator_overload(alloc),
			avl_type_only(unique_tag, this->alloc(), this->extract(), this->key_comp(), first, last)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			kerbal::container::unique_tag_t unique_tag,
			InputIterator first, InputIterator last,
			const KeyCompare & key_comp
		) :
			key_compare_compress_helper(kerbal::utility::in_place_t(), key_comp),
			avl_type_only(unique_tag, this->alloc(), this->extract(), this->key_comp(), first, last)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			kerbal::container::unique_tag_t unique_tag,
			InputIterator first, InputIterator last,
			const KeyCompare & key_comp, const Allocator & alloc
		) :
			key_compare_compress_helper(kerbal::utility::in_place_t(), key_comp),
			avl_allocator_overload(alloc),
			avl_type_only(unique_tag, this->alloc(), this->extract(), this->key_comp(), first, last)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			kerbal::container::unique_tag_t unique_tag,
			InputIterator first, InputIterator last,
			const Extract & e
		) :
			extract_compress_helper(kerbal::utility::in_place_t(), e),
			avl_type_only(unique_tag, this->alloc(), this->extract(), this->key_comp(), first, last)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			kerbal::container::unique_tag_t unique_tag,
			InputIterator first, InputIterator last,
			const Extract & e, const Allocator & alloc
		) :
			extract_compress_helper(kerbal::utility::in_place_t(), e),
			avl_allocator_overload(alloc),
			avl_type_only(unique_tag, this->alloc(), this->extract(), this->key_comp(), first, last)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			kerbal::container::unique_tag_t unique_tag,
			InputIterator first, InputIterator last,
			const Extract & e, const KeyCompare & key_comp
		) :
			extract_compress_helper(kerbal::utility::in_place_t(), e),
			key_compare_compress_helper(kerbal::utility::in_place_t(), key_comp),
			avl_type_only(unique_tag, this->alloc(), this->extract(), this->key_comp(), first, last)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			kerbal::container::unique_tag_t unique_tag,
			InputIterator first, InputIterator last,
			const Extract & e, const KeyCompare & key_comp, const Allocator & alloc
		) :
			extract_compress_helper(kerbal::utility::in_place_t(), e),
			key_compare_compress_helper(kerbal::utility::in_place_t(), key_comp),
			avl_allocator_overload(alloc),
			avl_type_only(unique_tag, this->alloc(), this->extract(), this->key_comp(), first, last)
		{
		}


#	if __cplusplus >= 201103L

		//===================
		// construct with initializer_list

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			std::initializer_list<value_type> ilist
		) :
			avl_type_only(this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			std::initializer_list<value_type> ilist,
			const Allocator & alloc
		) :
			avl_allocator_overload(alloc),
			avl_type_only(this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			std::initializer_list<value_type> ilist,
			const KeyCompare & key_comp
		) :
			key_compare_compress_helper(kerbal::utility::in_place_t(), key_comp),
			avl_type_only(this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			std::initializer_list<value_type> ilist,
			const KeyCompare & key_comp, const Allocator & alloc
		) :
			key_compare_compress_helper(kerbal::utility::in_place_t(), key_comp),
			avl_allocator_overload(alloc),
			avl_type_only(this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			std::initializer_list<value_type> ilist,
			const Extract & e
		) :
			extract_compress_helper(kerbal::utility::in_place_t(), e),
			avl_type_only(this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			std::initializer_list<value_type> ilist,
			const Extract & e, const Allocator & alloc
		) :
			extract_compress_helper(kerbal::utility::in_place_t(), e),
			avl_allocator_overload(alloc),
			avl_type_only(this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			std::initializer_list<value_type> ilist,
			const Extract & e, const KeyCompare & key_comp
		) :
			extract_compress_helper(kerbal::utility::in_place_t(), e),
			key_compare_compress_helper(kerbal::utility::in_place_t(), key_comp),
			avl_type_only(this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			std::initializer_list<value_type> ilist,
			const Extract & e, const KeyCompare & key_comp, const Allocator & alloc
		) :
			extract_compress_helper(kerbal::utility::in_place_t(), e),
			key_compare_compress_helper(kerbal::utility::in_place_t(), key_comp),
			avl_allocator_overload(alloc),
			avl_type_only(this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}


		//===================
		// construct with initializer_list (unique)

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			kerbal::container::unique_tag_t unique_tag,
			std::initializer_list<value_type> ilist
		) :
			avl_type_only(unique_tag, this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			kerbal::container::unique_tag_t unique_tag,
			std::initializer_list<value_type> ilist,
			const Allocator & alloc
		) :
			avl_allocator_overload(alloc),
			avl_type_only(unique_tag, this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			kerbal::container::unique_tag_t unique_tag,
			std::initializer_list<value_type> ilist,
			const KeyCompare & key_comp
		) :
			key_compare_compress_helper(kerbal::utility::in_place_t(), key_comp),
			avl_type_only(unique_tag, this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			kerbal::container::unique_tag_t unique_tag,
			std::initializer_list<value_type> ilist,
			const KeyCompare & key_comp, const Allocator & alloc
		) :
			key_compare_compress_helper(kerbal::utility::in_place_t(), key_comp),
			avl_allocator_overload(alloc),
			avl_type_only(unique_tag, this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			kerbal::container::unique_tag_t unique_tag,
			std::initializer_list<value_type> ilist,
			const Extract & e
		) :
			extract_compress_helper(kerbal::utility::in_place_t(), e),
			avl_type_only(unique_tag, this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			kerbal::container::unique_tag_t unique_tag,
			std::initializer_list<value_type> ilist,
			const Extract & e, const Allocator & alloc
		) :
			extract_compress_helper(kerbal::utility::in_place_t(), e),
			avl_allocator_overload(alloc),
			avl_type_only(unique_tag, this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			kerbal::container::unique_tag_t unique_tag,
			std::initializer_list<value_type> ilist,
			const Extract & e, const KeyCompare & key_comp
		) :
			extract_compress_helper(kerbal::utility::in_place_t(), e),
			key_compare_compress_helper(kerbal::utility::in_place_t(), key_comp),
			avl_type_only(unique_tag, this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			kerbal::container::unique_tag_t unique_tag,
			std::initializer_list<value_type> ilist,
			const Extract & e, const KeyCompare & key_comp, const Allocator & alloc
		) :
			extract_compress_helper(kerbal::utility::in_place_t(), e),
			key_compare_compress_helper(kerbal::utility::in_place_t(), key_comp),
			avl_allocator_overload(alloc),
			avl_type_only(unique_tag, this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}

#	else

		//===================
		// construct with assign_list

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename U>
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			const kerbal::assign::assign_list<U> & ilist
		) :
			avl_type_only(this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename U>
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			const kerbal::assign::assign_list<U> & ilist,
			const Allocator & alloc
		) :
			avl_allocator_overload(alloc),
			avl_type_only(this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename U>
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			const kerbal::assign::assign_list<U> & ilist,
			const KeyCompare & key_comp
		) :
			key_compare_compress_helper(kerbal::utility::in_place_t(), key_comp),
			avl_type_only(this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename U>
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			const kerbal::assign::assign_list<U> & ilist,
			const KeyCompare & key_comp, const Allocator & alloc
		) :
			key_compare_compress_helper(kerbal::utility::in_place_t(), key_comp),
			avl_allocator_overload(alloc),
			avl_type_only(this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename U>
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			const kerbal::assign::assign_list<U> & ilist,
			const Extract & e
		) :
			extract_compress_helper(kerbal::utility::in_place_t(), e),
			avl_type_only(this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename U>
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			const kerbal::assign::assign_list<U> & ilist,
			const Extract & e, const Allocator & alloc
		) :
			extract_compress_helper(kerbal::utility::in_place_t(), e),
			avl_allocator_overload(alloc),
			avl_type_only(this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename U>
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			const kerbal::assign::assign_list<U> & ilist,
			const Extract & e, const KeyCompare & key_comp
		) :
			extract_compress_helper(kerbal::utility::in_place_t(), e),
			key_compare_compress_helper(kerbal::utility::in_place_t(), key_comp),
			avl_type_only(this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename U>
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			const kerbal::assign::assign_list<U> & ilist,
			const Extract & e, const KeyCompare & key_comp, const Allocator & alloc
		) :
			extract_compress_helper(kerbal::utility::in_place_t(), e),
			key_compare_compress_helper(kerbal::utility::in_place_t(), key_comp),
			avl_allocator_overload(alloc),
			avl_type_only(this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}


		//===================
		// construct with assign_list (unique)

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename U>
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			kerbal::container::unique_tag_t unique_tag,
			const kerbal::assign::assign_list<U> & ilist
		) :
			avl_type_only(unique_tag, this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename U>
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			kerbal::container::unique_tag_t unique_tag,
			const kerbal::assign::assign_list<U> & ilist,
			const Allocator & alloc
		) :
			avl_allocator_overload(alloc),
			avl_type_only(unique_tag, this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename U>
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			kerbal::container::unique_tag_t unique_tag,
			const kerbal::assign::assign_list<U> & ilist,
			const KeyCompare & key_comp
		) :
			key_compare_compress_helper(kerbal::utility::in_place_t(), key_comp),
			avl_type_only(unique_tag, this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename U>
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			kerbal::container::unique_tag_t unique_tag,
			const kerbal::assign::assign_list<U> & ilist,
			const KeyCompare & key_comp, const Allocator & alloc
		) :
			key_compare_compress_helper(kerbal::utility::in_place_t(), key_comp),
			avl_allocator_overload(alloc),
			avl_type_only(unique_tag, this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename U>
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			kerbal::container::unique_tag_t unique_tag,
			const kerbal::assign::assign_list<U> & ilist,
			const Extract & e
		) :
			extract_compress_helper(kerbal::utility::in_place_t(), e),
			avl_type_only(unique_tag, this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename U>
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			kerbal::container::unique_tag_t unique_tag,
			const kerbal::assign::assign_list<U> & ilist,
			const Extract & e, const Allocator & alloc
		) :
			extract_compress_helper(kerbal::utility::in_place_t(), e),
			avl_allocator_overload(alloc),
			avl_type_only(unique_tag, this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename U>
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			kerbal::container::unique_tag_t unique_tag,
			const kerbal::assign::assign_list<U> & ilist,
			const Extract & e, const KeyCompare & key_comp
		) :
			extract_compress_helper(kerbal::utility::in_place_t(), e),
			key_compare_compress_helper(kerbal::utility::in_place_t(), key_comp),
			avl_type_only(unique_tag, this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename U>
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		avl_ordered(
			kerbal::container::unique_tag_t unique_tag,
			const kerbal::assign::assign_list<U> & ilist,
			const Extract & e, const KeyCompare & key_comp, const Allocator & alloc
		) :
			extract_compress_helper(kerbal::utility::in_place_t(), e),
			key_compare_compress_helper(kerbal::utility::in_place_t(), key_comp),
			avl_allocator_overload(alloc),
			avl_type_only(unique_tag, this->alloc(), this->extract(), this->key_comp(), ilist)
		{
		}

#	endif


		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		~avl_ordered()
		{
			this->avl_type_only::k_destroy_using_allocator(this->alloc());
		}


		//===================
		// assign

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator> &
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		operator=(const avl_ordered & src)
		{
			this->assign(src);
			return *this;
		}

#	if __cplusplus >= 201103L

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator> &
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		operator=(avl_ordered && src)
		{
			this->assign(kerbal::compatibility::move(src));
			return *this;
		}

#	endif

#	if __cplusplus >= 201103L

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		avl_ordered<Entity, Extract, KeyCompare, Allocator> &
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		operator=(std::initializer_list<value_type> ilist)
		{
			this->assign(ilist);
			return *this;
		}

#	else

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename U>
		avl_ordered<Entity, Extract, KeyCompare, Allocator> &
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		operator=(const kerbal::assign::assign_list<U> & ilist)
		{
			this->assign(ilist);
			return *this;
		}

#	endif

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		void
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		assign(const avl_ordered & src)
		{
			kerbal::assign::generic_assign(this->extract(), src.extract());
			kerbal::assign::generic_assign(this->key_comp(), src.key_comp());
			this->avl_type_only::k_assign_using_allocator(
				this->alloc(), this->extract(), this->key_comp(),
				src.alloc(), static_cast<const avl_type_only &>(src)
			);
		}

#	if __cplusplus >= 201103L

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		void
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		assign(avl_ordered && src)
		{
			kerbal::assign::generic_assign(this->extract(), src.extract());
			kerbal::assign::generic_assign(this->key_comp(), src.key_comp());
			this->avl_type_only::k_assign_using_allocator(
				this->alloc(), this->extract(), this->key_comp(),
				kerbal::compatibility::move(src.alloc()), static_cast<avl_type_only &&>(src)
			);
		}

#	endif

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		void
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		assign(InputIterator first, InputIterator last)
		{
			this->avl_type_only::k_assign_using_allocator(
				this->alloc(), this->extract(), this->key_comp(),
				first, last
			);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		void
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		assign_unique(InputIterator first, InputIterator last)
		{
			this->avl_type_only::k_assign_unique_using_allocator(
				this->alloc(), this->extract(), this->key_comp(),
				first, last
			);
		}

#	if __cplusplus >= 201103L

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		void
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		assign(std::initializer_list<value_type> ilist)
		{
			this->avl_type_only::k_assign_using_allocator(
				this->alloc(), this->extract(), this->key_comp(),
				ilist
			);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		void
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		assign_unique(std::initializer_list<value_type> ilist)
		{
			this->avl_type_only::k_assign_unique_using_allocator(
				this->alloc(), this->extract(), this->key_comp(),
				ilist
			);
		}

#	else

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename U>
		void
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		assign(const kerbal::assign::assign_list<U> & ilist)
		{
			this->avl_type_only::k_assign_using_allocator(
				this->alloc(), this->extract(), this->key_comp(),
				ilist
			);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename U>
		void
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		assign_unique(const kerbal::assign::assign_list<U> & ilist)
		{
			this->avl_type_only::k_assign_unique_using_allocator(
				this->alloc(), this->extract(), this->key_comp(),
				ilist
			);
		}

#	endif


		//===================
		// lookup

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::const_iterator
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		find(const key_type & key) const
		{
			return this->avl_type_only::k_find(this->extract(), this->key_comp(), key);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::iterator
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		find(const key_type & key)
		{
			return this->avl_type_only::k_find(this->extract(), this->key_comp(), key);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename Key>
		KERBAL_CONSTEXPR20
		typename
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::template enable_if_transparent_lookup<
			Key,
			typename avl_ordered<Entity, Extract, KeyCompare, Allocator>::const_iterator
		>::type
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		find(const Key & key) const
		{
			return this->avl_type_only::k_find(this->extract(), this->key_comp(), key);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename Key>
		KERBAL_CONSTEXPR20
		typename
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::template enable_if_transparent_lookup<
			Key,
			typename avl_ordered<Entity, Extract, KeyCompare, Allocator>::iterator
		>::type
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		find(const Key & key)
		{
			return this->avl_type_only::k_find(this->extract(), this->key_comp(), key);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::const_iterator
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		lower_bound(const key_type & key) const
		{
			return this->avl_type_only::k_lower_bound(this->extract(), this->key_comp(), key);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::iterator
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		lower_bound(const key_type & key)
		{
			return this->avl_type_only::k_lower_bound(this->extract(), this->key_comp(), key);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename Key>
		KERBAL_CONSTEXPR20
		typename
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::template enable_if_transparent_lookup<
			Key,
			typename avl_ordered<Entity, Extract, KeyCompare, Allocator>::const_iterator
		>::type
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		lower_bound(const Key & key) const
		{
			return this->avl_type_only::k_lower_bound(this->extract(), this->key_comp(), key);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename Key>
		KERBAL_CONSTEXPR20
		typename
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::template enable_if_transparent_lookup<
			Key,
			typename avl_ordered<Entity, Extract, KeyCompare, Allocator>::iterator
		>::type
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		lower_bound(const Key & key)
		{
			return this->avl_type_only::k_lower_bound(this->extract(), this->key_comp(), key);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::const_iterator
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		upper_bound(const key_type & key) const
		{
			return this->avl_type_only::k_upper_bound(this->extract(), this->key_comp(), key);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::iterator
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		upper_bound(const key_type & key)
		{
			return this->avl_type_only::k_upper_bound(this->extract(), this->key_comp(), key);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename Key>
		KERBAL_CONSTEXPR20
		typename
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::template enable_if_transparent_lookup<
			Key,
			typename avl_ordered<Entity, Extract, KeyCompare, Allocator>::const_iterator
		>::type
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		upper_bound(const Key & key) const
		{
			return this->avl_type_only::k_upper_bound(this->extract(), this->key_comp(), key);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename Key>
		KERBAL_CONSTEXPR20
		typename
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::template enable_if_transparent_lookup<
			Key,
			typename avl_ordered<Entity, Extract, KeyCompare, Allocator>::iterator
		>::type
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		upper_bound(const Key & key)
		{
			return this->avl_type_only::k_upper_bound(this->extract(), this->key_comp(), key);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		kerbal::utility::compressed_pair<
			typename avl_ordered<Entity, Extract, KeyCompare, Allocator>::const_iterator,
			typename avl_ordered<Entity, Extract, KeyCompare, Allocator>::const_iterator
		>
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		equal_range(const key_type & key) const
		{
			return this->avl_type_only::k_equal_range(this->extract(), this->key_comp(), key);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		kerbal::utility::compressed_pair<
			typename avl_ordered<Entity, Extract, KeyCompare, Allocator>::iterator,
			typename avl_ordered<Entity, Extract, KeyCompare, Allocator>::iterator
		>
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		equal_range(const key_type & key)
		{
			return this->avl_type_only::k_equal_range(this->extract(), this->key_comp(), key);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename Key>
		KERBAL_CONSTEXPR20
		typename
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::template enable_if_transparent_lookup<
			Key,
			kerbal::utility::compressed_pair<
				typename avl_ordered<Entity, Extract, KeyCompare, Allocator>::const_iterator,
				typename avl_ordered<Entity, Extract, KeyCompare, Allocator>::const_iterator
			>
		>::type
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		equal_range(const Key & key) const
		{
			return this->avl_type_only::k_equal_range(this->extract(), this->key_comp(), key);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename Key>
		KERBAL_CONSTEXPR20
		typename
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::template enable_if_transparent_lookup<
			Key,
			kerbal::utility::compressed_pair<
				typename avl_ordered<Entity, Extract, KeyCompare, Allocator>::iterator,
				typename avl_ordered<Entity, Extract, KeyCompare, Allocator>::iterator
			>
		>::type
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		equal_range(const Key & key)
		{
			return this->avl_type_only::k_equal_range(this->extract(), this->key_comp(), key);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		bool
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		contains(const key_type & key) const
		{
			return this->avl_type_only::k_contains(this->extract(), this->key_comp(), key);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename Key>
		KERBAL_CONSTEXPR20
		typename
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::template enable_if_transparent_lookup<
			Key,
			bool
		>::type
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		contains(const Key & key) const
		{
			return this->avl_type_only::k_contains(this->extract(), this->key_comp(), key);
		}

		//===================
		// insert

#	if __cplusplus >= 201103L

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::iterator
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		emplace(Args && ... args)
		{
			return this->avl_type_only::k_emplace_using_allocator(
				this->alloc(), this->extract(), this->key_comp(),
				kerbal::utility::forward<Args>(args)...
			);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::unique_insert_r
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		emplace_unique(Args && ... args)
		{
			return this->avl_type_only::k_emplace_unique_using_allocator(
				this->alloc(), this->extract(), this->key_comp(),
				kerbal::utility::forward<Args>(args)...
			);
		}

#	else

#	define EMPTY
#	define REMAINF(exp) exp
#	define LEFT_JOIN_COMMA(exp) , exp
#	define THEAD_NOT_EMPTY(exp) template <exp>
#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#	define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#	define FBODY(i) \
		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator> \
		KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
		typename \
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::iterator \
		avl_ordered<Entity, Extract, KeyCompare, Allocator>:: \
		emplace(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
		{ \
			return this->avl_type_only::k_emplace_using_allocator( \
				this->alloc(), this->extract(), this->key_comp() \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i) \
			); \
		} \
 \
		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator> \
		KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
		typename \
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::unique_insert_r \
		avl_ordered<Entity, Extract, KeyCompare, Allocator>:: \
		emplace_unique(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
		{ \
			return this->avl_type_only::k_emplace_unique_using_allocator( \
				this->alloc(), this->extract(), this->key_comp() \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i) \
			); \
		} \

		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#	undef EMPTY
#	undef REMAINF
#	undef LEFT_JOIN_COMMA
#	undef THEAD_NOT_EMPTY
#	undef TARGS_DECL
#	undef ARGS_DECL
#	undef ARGS_USE
#	undef FBODY

#	endif

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::iterator
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		insert(const_reference src)
		{
			return this->avl_type_only::k_insert_using_allocator(
				this->alloc(), this->extract(), this->key_comp(),
				src
			);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::unique_insert_r
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		unique_insert(const_reference src)
		{
			return this->avl_type_only::k_unique_insert_using_allocator(
				this->alloc(), this->extract(), this->key_comp(),
				src
			);
		}

#	if __cplusplus >= 201103L

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::iterator
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		insert(rvalue_reference src)
		{
			return this->avl_type_only::k_insert_using_allocator(
				this->alloc(), this->extract(), this->key_comp(),
				kerbal::compatibility::move(src)
			);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::unique_insert_r
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		unique_insert(rvalue_reference src)
		{
			return this->avl_type_only::k_unique_insert_using_allocator(
				this->alloc(), this->extract(), this->key_comp(),
				kerbal::compatibility::move(src)
			);
		}

#	endif

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		void
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		insert(InputIterator first, InputIterator last)
		{
			this->avl_type_only::k_insert_using_allocator(
				this->alloc(), this->extract(), this->key_comp(),
				first, last
			);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		void
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		unique_insert(InputIterator first, InputIterator last)
		{
			this->avl_type_only::k_unique_insert_using_allocator(
				this->alloc(), this->extract(), this->key_comp(),
				first, last
			);
		}

#	if __cplusplus >= 201103L

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		void
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		insert(std::initializer_list<value_type> ilist)
		{
			this->avl_type_only::k_insert_using_allocator(
				this->alloc(), this->extract(), this->key_comp(),
				ilist
			);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		void
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		unique_insert(std::initializer_list<value_type> ilist)
		{
			this->avl_type_only::k_unique_insert_using_allocator(
				this->alloc(), this->extract(), this->key_comp(),
				ilist
			);
		}

#	else

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename U>
		void
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		insert(const kerbal::assign::assign_list<U> & ilist)
		{
			this->avl_type_only::k_insert_using_allocator(
				this->alloc(), this->extract(), this->key_comp(),
				ilist
			);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename U>
		void
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		unique_insert(const kerbal::assign::assign_list<U> & ilist)
		{
			this->avl_type_only::k_unique_insert_using_allocator(
				this->alloc(), this->extract(), this->key_comp(),
				ilist
			);
		}

#	endif

		//===================
		// erase

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::iterator
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		erase_not_end_unsafe(const_iterator pos) KERBAL_NOEXCEPT
		{
			return this->avl_type_only::k_erase_not_end_using_allocator_unsafe(
				this->alloc(),
				pos
			);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::iterator
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		erase(const_iterator pos) KERBAL_NOEXCEPT
		{
			return this->avl_type_only::k_erase_using_allocator(
				this->alloc(),
				pos
			);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::iterator
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		erase(const_iterator first, const_iterator last) KERBAL_NOEXCEPT
		{
			return this->avl_type_only::k_erase_using_allocator(
				this->alloc(),
				first, last
			);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		typename
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::size_type
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		erase(const key_type & key) KERBAL_NOEXCEPT
		{
			return this->avl_type_only::k_erase_using_allocator(
				this->alloc(), this->extract(), this->key_comp(),
				key
			);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename Key>
		KERBAL_CONSTEXPR20
		typename
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::template enable_if_transparent_lookup<
			Key,
			typename avl_ordered<Entity, Extract, KeyCompare, Allocator>::size_type
		>::type
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		erase(const Key & key) KERBAL_NOEXCEPT
		{
			return this->avl_type_only::k_erase_using_allocator(
				this->alloc(), this->extract(), this->key_comp(),
				key
			);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		void
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		clear() KERBAL_NOEXCEPT
		{
			this->avl_type_only::k_clear_using_allocator(this->alloc());
		}


		//===================
		// replace

#	if __cplusplus >= 201103L

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::iterator
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		replace_emplace(const_iterator replace, Args && ... args)
		{
			return this->avl_type_only::k_replace_emplace_using_allocator(
				this->alloc(), this->extract(), this->key_comp(),
				replace,
				kerbal::utility::forward<Args>(args)...
			);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::unique_insert_r
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		replace_emplace_unique(const_iterator replace, Args && ... args)
		{
			return this->avl_type_only::k_replace_emplace_unique_using_allocator(
				this->alloc(), this->extract(), this->key_comp(),
				replace,
				kerbal::utility::forward<Args>(args)...
			);
		}

#	else

#	define EMPTY
#	define LEFT_JOIN_COMMA(exp) , exp
#	define THEAD_NOT_EMPTY(exp) template <exp>
#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#	define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#	define FBODY(i) \
		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator> \
		KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
		typename \
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::iterator \
		avl_ordered<Entity, Extract, KeyCompare, Allocator>:: \
		replace_emplace( \
			const_iterator replace \
			KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
		) \
		{ \
			return this->avl_type_only::k_replace_emplace_using_allocator( \
				this->alloc(), this->extract(), this->key_comp(), \
				replace \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i) \
			); \
		} \
 \
		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator> \
		KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
		typename \
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::unique_insert_r \
		avl_ordered<Entity, Extract, KeyCompare, Allocator>:: \
		replace_emplace_unique( \
			const_iterator replace \
			KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
		) \
		{ \
			return this->avl_type_only::k_replace_emplace_unique_using_allocator( \
				this->alloc(), this->extract(), this->key_comp(), \
				replace \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i) \
			); \
		} \

		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#	undef EMPTY
#	undef LEFT_JOIN_COMMA
#	undef THEAD_NOT_EMPTY
#	undef TARGS_DECL
#	undef ARGS_DECL
#	undef ARGS_USE
#	undef FBODY

#	endif


		//===================
		// operation

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename OtherExtract, typename OtherKeyCompare>
		KERBAL_CONSTEXPR20
		void
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		merge(avl_ordered<Entity, OtherExtract, OtherKeyCompare, Allocator> & other)
		{
			this->avl_type_only::k_merge(
				this->extract(), this->key_comp(),
				static_cast<avl_type_only &>(other)
			);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename OtherExtract, typename OtherKeyCompare>
		KERBAL_CONSTEXPR20
		void
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		merge_unique(avl_ordered<Entity, OtherExtract, OtherKeyCompare, Allocator> & other)
		{
			this->avl_type_only::k_merge_unique(
				this->extract(), this->key_comp(),
				static_cast<avl_type_only &>(other)
			);
		}

#	if __cplusplus >= 201103L

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename OtherExtract, typename OtherKeyCompare>
		KERBAL_CONSTEXPR20
		void
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		merge(avl_ordered<Entity, OtherExtract, OtherKeyCompare, Allocator> && other)
		{
			this->avl_type_only::k_merge(
				this->extract(), this->key_comp(),
				static_cast<avl_type_only &&>(other)
			);
		}

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		template <typename OtherExtract, typename OtherKeyCompare>
		KERBAL_CONSTEXPR20
		void
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		merge_unique(avl_ordered<Entity, OtherExtract, OtherKeyCompare, Allocator> && other)
		{
			this->avl_type_only::k_merge_unique(
				this->extract(), this->key_comp(),
				static_cast<avl_type_only &&>(other)
			);
		}

#	endif

		template <typename Entity, typename Extract, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		void
		avl_ordered<Entity, Extract, KeyCompare, Allocator>::
		swap(avl_ordered & other)
		{
			avl_allocator_overload::k_swap_allocator_if_propagate(
				static_cast<avl_allocator_overload &>(*this),
				static_cast<avl_allocator_overload &>(other)
			);
			kerbal::algorithm::swap(this->extract(), other.extract());
			kerbal::algorithm::swap(this->key_comp(), other.key_comp());
			avl_type_unrelated::k_swap(
				static_cast<avl_type_unrelated &>(*this),
				static_cast<avl_type_unrelated &>(other)
			);
		}


	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_AVL_ORDERED_AVL_ORDERED_IMPL_HPP
