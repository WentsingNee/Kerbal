/**
 * @file       vector_base.impl.hpp
 * @brief
 * @date       2020-08-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_VECTOR_BASE_VECTOR_BASE_IMPL_HPP
#define KERBAL_CONTAINER_DETAIL_VECTOR_BASE_VECTOR_BASE_IMPL_HPP

#include <kerbal/algorithm/modifier/copy.hpp>
#include <kerbal/algorithm/modifier/copy_n.hpp>
#include <kerbal/algorithm/modifier/fill.hpp>
#include <kerbal/algorithm/modifier/move.hpp>
#include <kerbal/algorithm/modifier/move_backward.hpp>
#include <kerbal/algorithm/swap.hpp>
#include <kerbal/assign/generic_assign.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/memory/raw_storage.hpp>
#include <kerbal/memory/uninitialized_using_allocator.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/utility/compressed_pair.hpp>
#include <kerbal/utility/throw_this_exception.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/iterator/move_iterator.hpp>
#	include <kerbal/utility/forward.hpp>
#endif

#if !__cpp_exceptions
#	include <kerbal/memory/bad_alloc.hpp>
#endif

#include <stdexcept>

#include <kerbal/container/detail/vector_base/vector_base.decl.hpp>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

		//===================
		// construct/copy/destroy

			template <typename Tp>
			KERBAL_CONSTEXPR
			vector_type_only<Tp>::vector_type_only() KERBAL_NOEXCEPT :
					k_buffer(NULL), k_capacity(0), k_size(0)
			{
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			vector_type_only<Tp>::vector_type_only(Allocator & alloc, size_type count)
			{
				if (count == 0) {
					this->k_buffer = NULL;
					this->k_capacity = 0;
					this->k_size = 0;
					return;
				}

				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				this->k_capacity = count;
				this->k_buffer = allocator_traits::allocate(alloc, this->k_capacity);
#		if !__cpp_exceptions
				if (this->k_buffer == NULL) {
					kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
				}
#		endif

#		if __cpp_exceptions
				try {
#		endif
					kerbal::memory::uninitialized_value_construct_using_allocator(alloc, this->k_buffer, this->k_buffer + count);
#		if __cpp_exceptions
				} catch (...) {
					allocator_traits::deallocate(alloc, this->k_buffer, this->k_capacity);
					throw;
				}
#		endif
				this->k_size = count;
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			vector_type_only<Tp>::vector_type_only(Allocator & alloc, size_type count, const_reference value)
			{
				if (count == 0) {
					this->k_buffer = NULL;
					this->k_capacity = 0;
					this->k_size = 0;
					return;
				}

				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				this->k_capacity = count;
				this->k_buffer = allocator_traits::allocate(alloc, this->k_capacity);
#		if !__cpp_exceptions
				if (this->k_buffer == NULL) {
					kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
				}
#		endif

#		if __cpp_exceptions
				try {
#		endif
					kerbal::memory::uninitialized_fill_using_allocator(alloc, this->k_buffer, this->k_buffer + count, value);
#		if __cpp_exceptions
				} catch (...) {
					allocator_traits::deallocate(alloc, this->k_buffer, this->k_capacity);
					throw;
				}
#		endif
				this->k_size = count;
			}

			template <typename Tp>
			template <typename Allocator, typename InputIterator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_range_copy_cnstrct_impl(Allocator & alloc, InputIterator first, InputIterator last,
																			std::input_iterator_tag)
			{
				this->k_buffer = NULL;
				this->k_capacity = 0;
				this->k_size = 0;

#		if __cpp_exceptions
				try {
#		endif
					while (first != last) {
						this->k_emplace_back_using_allocator(alloc, *first);
						++first;
					}
#		if __cpp_exceptions
				} catch (...) {
					if (this->k_buffer != NULL) {
						typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;
						kerbal::memory::reverse_destroy_using_allocator(alloc, this->begin().current, this->end().current);
						allocator_traits::deallocate(alloc, this->k_buffer, this->k_capacity);
					}
					throw;
				}
#		endif

			}

			template <typename Tp>
			template <typename Allocator, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_range_copy_cnstrct_impl(Allocator & alloc, ForwardIterator first, ForwardIterator last,
																			std::forward_iterator_tag)
			{
				size_type len = static_cast<size_type>(kerbal::iterator::distance(first, last));

				if (len == 0) {
					this->k_buffer = NULL;
					this->k_capacity = 0;
					this->k_size = 0;
					return;
				}

				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				this->k_capacity = len;
				this->k_buffer = allocator_traits::allocate(alloc, this->k_capacity);
#		if !__cpp_exceptions
				if (this->k_buffer == NULL) {
					kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
				}
#		endif

#		if __cpp_exceptions
				try {
#		endif
					kerbal::memory::uninitialized_copy_using_allocator(alloc, first, last, this->k_buffer);
#		if __cpp_exceptions
				} catch (...) {
					allocator_traits::deallocate(alloc, this->k_buffer, this->k_capacity);
					throw;
				}
#		endif
				this->k_size = len;
			}

			template <typename Tp>
			template <typename Allocator, typename InputIterator>
			KERBAL_CONSTEXPR20
			vector_type_only<Tp>::vector_type_only(Allocator & alloc, InputIterator first, InputIterator last)
			{
				this->k_range_copy_cnstrct_impl(alloc, first, last, kerbal::iterator::iterator_category(first));
			}

#		if __cplusplus >= 201103L

			template <typename Tp>
			KERBAL_CONSTEXPR14
			vector_type_only<Tp>::vector_type_only(vector_type_only && src) KERBAL_NOEXCEPT :
					k_buffer(src.k_buffer), k_capacity(src.k_capacity), k_size(src.k_size)
			{
				src.k_buffer = NULL;
				src.k_size = 0;
				src.k_capacity = 0;
			}

			// move construct using allocator, allocator is equal
			template <typename Tp>
			KERBAL_CONSTEXPR14
			void vector_type_only<Tp>::k_move_cnstrct_ua_ae(vector_type_only && src) KERBAL_NOEXCEPT
			{
				this->k_buffer = src.k_buffer;
				this->k_size = src.k_size;
				this->k_capacity = src.k_capacity;
				src.k_buffer = NULL;
				src.k_size = 0;
				src.k_capacity = 0;
			}

			// move construct using allocator, allocator is not equal
			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_move_cnstrct_ua_ane(Allocator & this_alloc, vector_type_only && src)
			{
				if (src.k_buffer != NULL) {
					typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

					this->k_capacity = src.k_size;
					this->k_buffer = allocator_traits::allocate(this_alloc, this->k_capacity);
#		if !__cpp_exceptions
					if (this->k_buffer == NULL) {
						kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
					}
#		endif

#		if __cpp_exceptions
					try {
#		endif
						kerbal::memory::uninitialized_move_using_allocator(this_alloc, src.begin().current, src.end().current, this->k_buffer);
#		if __cpp_exceptions
					} catch (...) {
						allocator_traits::deallocate(this_alloc, this->k_buffer, this->k_capacity);
						throw;
					}
#		endif
					this->k_size = src.k_size;
				} else {
					this->k_buffer = NULL;
					this->k_size = 0;
					this->k_capacity = 0;
				}
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_move_cnstrct_ua_helper(Allocator & this_alloc, Allocator && src_alloc, vector_type_only && src,
																		   kerbal::type_traits::false_type /*is_always_equal*/)
			{
				if (this_alloc != src_alloc) {
					this->k_move_cnstrct_ua_ane(this_alloc, kerbal::compatibility::move(src));
				} else {
					this->k_move_cnstrct_ua_ae(kerbal::compatibility::move(src));
				}
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR14
			void vector_type_only<Tp>::k_move_cnstrct_ua_helper(Allocator & /*this_alloc*/, Allocator && /*src_alloc*/, vector_type_only && src,
																		   kerbal::type_traits::true_type /*is_always_equal*/) KERBAL_NOEXCEPT
			{
				this->k_move_cnstrct_ua_ae(kerbal::compatibility::move(src));
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR14
			vector_type_only<Tp>::vector_type_only(Allocator & this_alloc, Allocator && src_alloc, vector_type_only && src)
					KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_move_constructible_using_allocator<Allocator>::value)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;
				typedef typename allocator_traits::is_always_equal is_always_equal;

				this->k_move_cnstrct_ua_helper(this_alloc, kerbal::compatibility::move(src_alloc), kerbal::compatibility::move(src), is_always_equal());
			}

#		endif

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_destroy_using_allocator(Allocator & alloc) KERBAL_NOEXCEPT
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				if (allocator_traits::allow_deallocate_null::value || this->k_buffer != NULL) {
					kerbal::memory::reverse_destroy_using_allocator(alloc, this->begin().current, this->end().current);
					allocator_traits::deallocate(alloc, this->k_buffer, this->k_capacity);
				}
			}



		//===================
		// assign

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_assign_using_allocator(Allocator & alloc, size_type new_size, const_reference value)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				size_type ori_size = this->k_size;
				if (new_size <= ori_size) { // also suitable for new_size == 0
					/*
					 * a a a a a a x x
					 * b b b x x x x x
					 */
					kerbal::algorithm::fill(this->begin().current, this->nth(new_size).current, value);
					kerbal::memory::reverse_destroy_using_allocator(alloc, this->nth(new_size).current, this->end().current);
					this->k_size = new_size;
				} else { // new_size > ori_size
					/*
					 * a a a x x x x x
					 * b b b b b b x x
					 */
					if (new_size <= this->k_capacity) {
						pointer ori_end(this->end().current);
						kerbal::algorithm::fill(this->begin().current, ori_end, value);
						kerbal::memory::uninitialized_fill_using_allocator(alloc, ori_end, this->nth(new_size).current, value);
						this->k_size = new_size;
					} else { // new_size > this->capacity
						size_type new_capacity = new_size;
						pointer new_buffer = allocator_traits::allocate(alloc, new_capacity);
#		if !__cpp_exceptions
						if (new_buffer == NULL) {
							kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
						}
#		endif

#		if __cpp_exceptions
						try {
#		endif
							kerbal::memory::uninitialized_fill_using_allocator(alloc, new_buffer, new_buffer + new_size, value);
#		if __cpp_exceptions
						} catch (...) {
							allocator_traits::deallocate(alloc, new_buffer, new_capacity);
							throw;
						}
#		endif

						if (allocator_traits::allow_deallocate_null::value || this->k_buffer != NULL) {
							kerbal::memory::reverse_destroy_using_allocator(alloc, this->begin().current, this->end().current);
							allocator_traits::deallocate(alloc, this->k_buffer, this->k_capacity);
						}
						this->k_buffer = new_buffer;
						this->k_capacity = new_capacity;
						this->k_size = new_size;
					}
				}
			}

			template <typename Tp>
			template <typename Allocator, typename InputIterator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_range_assign_using_allocator_impl(Allocator & alloc, InputIterator first, InputIterator last, std::input_iterator_tag)
			{
				iterator it(this->begin());
				iterator end(this->end());
				while (it != end) {
					if (first != last) {
						kerbal::assign::generic_assign(*it, *first);
						++first;
						++it;
					} else {
						this->k_erase_using_allocator(alloc, it, end);
						return;
					}
				}
				while (first != last) {
					this->k_emplace_back_using_allocator(alloc, *first);
					++first;
				}
			}

			template <typename Tp>
			template <typename Allocator, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_range_assign_using_allocator_impl(Allocator & alloc, ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				size_type ori_size = this->k_size;
				size_type new_size = static_cast<size_type>(kerbal::iterator::distance(first, last));

				if (new_size <= ori_size) { // also suitable for new_size == 0
					/*
					 * a a a a a a x x
					 * b b b x x x x x
					 */
					pointer new_end(kerbal::algorithm::copy(first, last, this->begin().current));
					kerbal::memory::reverse_destroy_using_allocator(alloc, new_end, this->end().current);
					this->k_size = new_size;
				} else { // new_size > ori_size
					/*
					 * a a a x x x x x
					 * b b b b b b x x
					 */
					if (new_size <= this->k_capacity) {
						kerbal::utility::compressed_pair<ForwardIterator, pointer> copy_n_r(kerbal::algorithm::copy_n(first, ori_size, this->k_buffer));
						kerbal::memory::uninitialized_copy_using_allocator(alloc, copy_n_r.first(), last, copy_n_r.second());
						this->k_size = new_size;
					} else { // new_size > this->capacity
						size_type new_capacity = new_size;
						pointer new_buffer = allocator_traits::allocate(alloc, new_capacity);
#		if !__cpp_exceptions
						if (new_buffer == NULL) {
							kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
						}
#		endif

#		if __cpp_exceptions
						try {
#		endif
							kerbal::memory::uninitialized_copy_using_allocator(alloc, first, last, new_buffer);
#		if __cpp_exceptions
						} catch (...) {
							allocator_traits::deallocate(alloc, new_buffer, new_capacity);
							throw;
						}
#		endif

						if (allocator_traits::allow_deallocate_null::value || this->k_buffer != NULL) {
							kerbal::memory::reverse_destroy_using_allocator(alloc, this->begin().current, this->end().current);
							allocator_traits::deallocate(alloc, this->k_buffer, this->k_capacity);
						}
						this->k_buffer = new_buffer;
						this->k_capacity = new_capacity;
						this->k_size = new_size;
					}
				}
			}

			template <typename Tp>
			template <typename Allocator, typename InputIterator>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<
					kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
			>::type
			vector_type_only<Tp>::k_assign_using_allocator(Allocator & alloc, InputIterator first, InputIterator last)
			{
				this->k_range_assign_using_allocator_impl(alloc, first, last, kerbal::iterator::iterator_category(first));
			}


			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_cpy_ass_ua_impl(Allocator & alloc, const Allocator & src_alloc, const vector_type_only & src,
																	CPYASS_VER_NOT_PROPAGATE)
			{
				if (alloc != src_alloc) {
					this->k_destroy_using_allocator(alloc);
					this->k_buffer = NULL;
					this->k_capacity = 0;
					this->k_size = 0;
				}
				this->k_assign_using_allocator(alloc, src.cbegin().current, src.cend().current);
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_cpy_ass_ua_impl(Allocator & alloc, const Allocator & src_alloc, const vector_type_only & src,
																	CPYASS_VER_PROPAGATE)
			{
				if (alloc != src_alloc) {
					this->k_destroy_using_allocator(alloc);
					this->k_buffer = NULL;
					this->k_capacity = 0;
					this->k_size = 0;
				}
				alloc = src_alloc;
				this->k_assign_using_allocator(alloc, src.cbegin().current, src.cend().current);
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_cpy_ass_ua_impl(Allocator & alloc, const Allocator & /*src_alloc*/, const vector_type_only & src,
																	CPYASS_VER_ALWAYS_EQUAL)
			{
				this->k_assign_using_allocator(alloc, src.cbegin().current, src.cend().current);
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_assign_using_allocator(Allocator & alloc, const Allocator & src_alloc, const vector_type_only & src)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;
				typedef typename allocator_traits::propagate_on_container_copy_assignment propagate;
				typedef typename allocator_traits::is_always_equal is_always_equal;

				typedef typename kerbal::type_traits::conditional<
						is_always_equal::value,
						CPYASS_VER_ALWAYS_EQUAL,
						typename kerbal::type_traits::conditional<
								propagate::value,
								CPYASS_VER_PROPAGATE,
								CPYASS_VER_NOT_PROPAGATE
						>::type
				>::type VER;

				this->k_cpy_ass_ua_impl(alloc, src_alloc, src, VER());
			}


#		if __cplusplus >= 201103L

			// move assign using allocator, allocator is equal
			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_mov_ass_ua_ae(Allocator & alloc, vector_type_only && src) KERBAL_NOEXCEPT
			{
				this->k_destroy_using_allocator(alloc);
				this->k_buffer = src.k_buffer;
				this->k_capacity = src.k_capacity;
				this->k_size = src.k_size;
				src.k_buffer = NULL;
				src.k_capacity = 0;
				src.k_size = 0;
			}

			// move assign using allocator, allocator is not equal
			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_mov_ass_ua_ane(Allocator & alloc, Allocator && /*src_alloc*/, vector_type_only && src)
			{
				this->k_assign_using_allocator(alloc, kerbal::iterator::make_move_iterator(src.begin().current), kerbal::iterator::make_move_iterator(src.end().current));
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_mov_ass_ua_impl(Allocator & alloc, Allocator && src_alloc, vector_type_only && src,
																	MOVASS_VER_NOT_PROPAGATE)
			{
				if (alloc != src_alloc) {
					this->k_mov_ass_ua_ane(alloc, kerbal::compatibility::move(src_alloc), kerbal::compatibility::move(src));
				} else {
					this->k_mov_ass_ua_ae(alloc, kerbal::compatibility::move(src));
				}
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_mov_ass_ua_impl(Allocator & alloc, Allocator && src_alloc, vector_type_only && src,
																	MOVASS_VER_PROPAGATE)
			{
				this->k_destroy_using_allocator(alloc);
				this->k_buffer = NULL;
				this->k_capacity = 0;
				this->k_size = 0;
				alloc = kerbal::compatibility::move(src_alloc);
				this->k_buffer = src.k_buffer;
				this->k_capacity = src.k_capacity;
				this->k_size = src.k_size;
				src.k_buffer = NULL;
				src.k_capacity = 0;
				src.k_size = 0;
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_mov_ass_ua_impl(Allocator & alloc, Allocator && /*src_alloc*/, vector_type_only && src,
																	MOVASS_VER_ALWAYS_EQUAL) KERBAL_NOEXCEPT
			{
				this->k_mov_ass_ua_ae(alloc, kerbal::compatibility::move(src));
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_assign_using_allocator(Allocator & alloc, Allocator && src_alloc, vector_type_only && src)
					KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_move_assign_using_allocator<Allocator>::value)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;
				typedef typename allocator_traits::propagate_on_container_move_assignment propagate;
				typedef typename allocator_traits::is_always_equal is_always_equal;

				typedef typename kerbal::type_traits::conditional<
						is_always_equal::value,
						MOVASS_VER_ALWAYS_EQUAL,
						typename kerbal::type_traits::conditional<
								propagate::value,
								MOVASS_VER_PROPAGATE,
								MOVASS_VER_NOT_PROPAGATE
						>::type
				>::type VER;

				this->k_mov_ass_ua_impl(
						alloc,
						kerbal::compatibility::move(src_alloc),
						kerbal::compatibility::move(src),
						VER()
				);
			}

#		endif



		//===================
		// element access

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_type_only<Tp>::reference
			vector_type_only<Tp>::at(size_type index)
			{
				if (index >= this->k_size) {
					kerbal::utility::throw_this_exception_helper<std::out_of_range>::throw_this_exception((const char*)"range check fail in vector");
				}
				return (*this)[index];
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_type_only<Tp>::const_reference
			vector_type_only<Tp>::at(size_type index) const
			{
				if (index >= this->k_size) {
					kerbal::utility::throw_this_exception_helper<std::out_of_range>::throw_this_exception((const char*)"range check fail in vector");
				}
				return (*this)[index];
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_type_only<Tp>::reference
			vector_type_only<Tp>::operator[](size_type index) KERBAL_NOEXCEPT
			{
				return this->k_buffer[index];
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_type_only<Tp>::const_reference
			vector_type_only<Tp>::operator[](size_type index) const KERBAL_NOEXCEPT
			{
				return this->k_buffer[index];
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_type_only<Tp>::reference
			vector_type_only<Tp>::front()
			{
				return *this->begin();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_type_only<Tp>::const_reference
			vector_type_only<Tp>::front() const
			{
				return *this->cbegin();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_type_only<Tp>::reference
			vector_type_only<Tp>::back()
			{
				return *this->rbegin();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_type_only<Tp>::const_reference
			vector_type_only<Tp>::back() const
			{
				return *this->crbegin();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR
			typename vector_type_only<Tp>::const_pointer
			vector_type_only<Tp>::data() const KERBAL_NOEXCEPT
			{
				return this->k_buffer;
			}


		//===================
		// iterator

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename vector_type_only<Tp>::iterator
			vector_type_only<Tp>::begin() KERBAL_NOEXCEPT
			{
				return iterator(this->k_buffer + 0);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename vector_type_only<Tp>::iterator
			vector_type_only<Tp>::end() KERBAL_NOEXCEPT
			{
				return iterator(this->k_buffer + this->k_size);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR
			typename vector_type_only<Tp>::const_iterator
			vector_type_only<Tp>::begin() const KERBAL_NOEXCEPT
			{
				return this->cbegin();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR
			typename vector_type_only<Tp>::const_iterator
			vector_type_only<Tp>::end() const KERBAL_NOEXCEPT
			{
				return this->cend();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR
			typename vector_type_only<Tp>::const_iterator
			vector_type_only<Tp>::cbegin() const KERBAL_NOEXCEPT
			{
				return const_iterator(this->k_buffer + 0);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR
			typename vector_type_only<Tp>::const_iterator
			vector_type_only<Tp>::cend() const KERBAL_NOEXCEPT
			{
				return const_iterator(this->k_buffer + this->k_size);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename vector_type_only<Tp>::reverse_iterator
			vector_type_only<Tp>::rbegin() KERBAL_NOEXCEPT
			{
				return reverse_iterator(this->end());
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename vector_type_only<Tp>::reverse_iterator
			vector_type_only<Tp>::rend() KERBAL_NOEXCEPT
			{
				return reverse_iterator(this->begin());
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename vector_type_only<Tp>::const_reverse_iterator
			vector_type_only<Tp>::rbegin() const KERBAL_NOEXCEPT
			{
				return this->crbegin();
			}
			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename vector_type_only<Tp>::const_reverse_iterator
			vector_type_only<Tp>::rend() const KERBAL_NOEXCEPT
			{
				return this->crend();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename vector_type_only<Tp>::const_reverse_iterator
			vector_type_only<Tp>::crbegin() const KERBAL_NOEXCEPT
			{
				return const_reverse_iterator(this->end());
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename vector_type_only<Tp>::const_reverse_iterator
			vector_type_only<Tp>::crend() const KERBAL_NOEXCEPT
			{
				return const_reverse_iterator(this->cbegin());
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename vector_type_only<Tp>::iterator
			vector_type_only<Tp>::nth(size_type index)
			{
				return this->begin() + index;
			}

			template <typename Tp>
			KERBAL_CONSTEXPR
			typename vector_type_only<Tp>::const_iterator
			vector_type_only<Tp>::nth(size_type index) const
			{
				return this->cbegin() + index;
			}

			template <typename Tp>
			KERBAL_CONSTEXPR
			typename vector_type_only<Tp>::const_iterator
			vector_type_only<Tp>::cnth(size_type index) const
			{
				return this->cbegin() + index;
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename vector_type_only<Tp>::size_type
			vector_type_only<Tp>::index_of(iterator it)
			{
				return it - this->begin();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR
			typename vector_type_only<Tp>::size_type
			vector_type_only<Tp>::index_of(const_iterator it) const
			{
				return it - this->cbegin();
			}


		//===================
		// capacity

			template <typename Tp>
			KERBAL_CONSTEXPR
			bool vector_type_only<Tp>::empty() const KERBAL_NOEXCEPT
			{
				return this->k_size == 0;
			}

			template <typename Tp>
			KERBAL_CONSTEXPR
			typename vector_type_only<Tp>::size_type
			vector_type_only<Tp>::size() const KERBAL_NOEXCEPT
			{
				return this->k_size;
			}

			template <typename Tp>
			KERBAL_CONSTEXPR
			typename vector_type_only<Tp>::size_type
			vector_type_only<Tp>::capacity() const KERBAL_NOEXCEPT
			{
				return this->k_capacity;
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_capacity_adjusted_realloc_aux(Allocator & alloc, pointer new_buffer, size_type new_capacity)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

#		if __cpp_exceptions
				try {
#		endif
					ui_move_if_noexcept_ow_copy_phase1(alloc, this->begin().current, this->end().current, new_buffer);
#		if __cpp_exceptions
				} catch (...) {
					allocator_traits::deallocate(alloc, new_buffer, new_capacity);
					throw;
				}
#		endif
				ui_move_if_noexcept_ow_copy_phase2(alloc, this->begin().current, this->end().current);
				allocator_traits::deallocate(alloc, this->k_buffer, this->k_capacity);
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_reserve_expand_buffer(kerbal::type_traits::false_type, Allocator & alloc, size_type new_capacity)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				pointer new_buffer = allocator_traits::allocate(alloc, new_capacity);
#		if !__cpp_exceptions
				if (new_buffer == NULL) {
					kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
				}
#		endif

				if (this->k_buffer != NULL) {
					this->k_capacity_adjusted_realloc_aux(alloc, new_buffer, new_capacity);
				}

				this->k_buffer = new_buffer;
				this->k_capacity = new_capacity;
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_reserve_expand_buffer(kerbal::type_traits::true_type, Allocator & alloc, size_type new_capacity)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				pointer new_buffer = allocator_traits::reallocate(alloc, this->k_buffer, this->k_capacity, new_capacity);
#		if !__cpp_exceptions
				if (new_buffer == NULL) {
					kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
				}
#		endif

				this->k_buffer = new_buffer;
				this->k_capacity = new_capacity;
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_reserve_using_allocator(Allocator & alloc, size_type new_capacity)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				if (new_capacity <= this->k_capacity) {
					return;
				}

				typedef typename allocator_traits::has_reallocate has_reallocate;
				this->k_reserve_expand_buffer(has_reallocate(), alloc, new_capacity);
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_shrink_buffer(kerbal::type_traits::false_type, Allocator & alloc)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				size_type new_capacity = this->k_size;
				pointer new_buffer = allocator_traits::allocate(alloc, new_capacity);
#		if !__cpp_exceptions
				if (new_buffer == NULL) {
					kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
				}
#		endif

				this->k_capacity_adjusted_realloc_aux(alloc, new_buffer, new_capacity);
				this->k_buffer = new_buffer;
				this->k_capacity = new_capacity;
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_shrink_buffer(kerbal::type_traits::true_type, Allocator & alloc)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				size_type new_capacity = this->k_size;
				allocator_traits::reallocate(alloc, this->k_buffer, this->k_capacity, new_capacity);

				this->k_capacity = new_capacity;
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_shrink_to_fit_using_allocator(Allocator & alloc)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				if (this->k_size == this->k_capacity) { // also suitable for buffer == NULL (size == capacity == 0)
					return;
				}

				if (this->k_size == 0) { // size == 0 but still have buffer
					allocator_traits::deallocate(alloc, this->k_buffer, this->k_capacity);
					this->k_buffer = NULL;
					this->k_capacity = 0;
					return;
				}

				typedef typename allocator_traits::has_reallocate has_reallocate;
				this->k_shrink_buffer(has_reallocate(), alloc);
			}

		//===================
		// insert

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::emplace_realloc_aux(Allocator & alloc, size_type insert_pos_index, pointer new_buffer, size_type new_capacity)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				if (this->k_buffer != NULL) {
					pointer insert_pos = this->k_buffer + insert_pos_index;
					pointer emplace_pos = new_buffer + insert_pos_index;

#		if __cpp_exceptions
					try {
						try {
							ui_move_if_noexcept_ow_copy_phase1(alloc, this->begin().current, insert_pos, new_buffer);
						} catch (...) {
							kerbal::memory::destroy_on_using_allocator(alloc, *emplace_pos);
							throw;
						}
						try {
							ui_move_if_noexcept_ow_copy_phase1(alloc, insert_pos, this->end().current, emplace_pos + 1);
						} catch (...) {
							kerbal::memory::reverse_destroy_using_allocator(alloc, new_buffer, emplace_pos + 1);
							throw;
						}
					} catch (...) {
						allocator_traits::deallocate(alloc, new_buffer, new_capacity);
						throw;
					}
#		else // __cpp_exceptions
					ui_move_if_noexcept_ow_copy_phase1(alloc, this->begin().current, insert_pos, new_buffer);
					ui_move_if_noexcept_ow_copy_phase1(alloc, insert_pos, this->end().current, emplace_pos + 1);
#		endif // __cpp_exceptions

					ui_move_if_noexcept_ow_copy_phase2(alloc, this->begin().current, this->end().current);
					allocator_traits::deallocate(alloc, this->k_buffer, this->k_capacity);
				}

				this->k_buffer = new_buffer;
				this->k_capacity = new_capacity;
				++this->k_size;
			}

			template <typename Tp, typename Allocator>
			struct vector_emplace_helper
			{
					typedef Tp value_type;
					typedef Tp* pointer;

					Allocator & alloc;
					kerbal::memory::raw_storage<value_type> storage;

#		if __cplusplus >= 201103L

					template <typename ... Args>
					KERBAL_CONSTEXPR20
					vector_emplace_helper(Allocator & alloc, Args&& ... args) :
							alloc(alloc)
					{
						this->storage.construct_using_allocator(this->alloc, kerbal::utility::forward<Args>(args)...);
					}

#		else

#			define EMPTY
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define LEFT_JOIN_COMMA(exp) , exp
#			define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#			define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
					KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
					vector_emplace_helper(Allocator & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) : \
							alloc(alloc) \
					{ \
						this->storage.construct_using_allocator(this->alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
					}

					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#			undef EMPTY
#			undef THEAD_NOT_EMPTY
#			undef LEFT_JOIN_COMMA
#			undef TARGS_DECL
#			undef ARGS_DECL
#			undef ARGS_USE
#			undef FBODY

#		endif

					KERBAL_CONSTEXPR20
					~vector_emplace_helper()
					{
						this->storage.destroy_using_allocator(this->alloc);
					}

			};

#		if __cplusplus >= 201103L

			template <typename Tp>
			template <typename Allocator, typename ... Args>
			KERBAL_CONSTEXPR20
			typename vector_type_only<Tp>::iterator
			vector_type_only<Tp>::k_emplace_using_allocator(Allocator & alloc, const_iterator pos, Args&& ... args)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				size_type insert_pos_index = this->index_of(pos);
				size_type ori_size = this->k_size;
				size_type new_size = ori_size + 1;
				if (new_size <= this->k_capacity) {
					pointer insert_pos = pos.cast_to_mutable().current;
					if (pos == this->cend()) {
						// A A A O O O
						//       ^
						// construct at the end
						kerbal::memory::construct_at_using_allocator(alloc, this->end().current, kerbal::utility::forward<Args>(args)...);
						this->k_size = new_size;
					} else {
						vector_emplace_helper<Tp, Allocator> helper(alloc, kerbal::utility::forward<Args>(args)...);

						// construct at the end
						kerbal::memory::construct_at_using_allocator(alloc, this->end().current, kerbal::compatibility::to_xvalue(this->back()));
						this->k_size = new_size;
						// A A A X Y Z Z O O
						//             ^
						kerbal::algorithm::move_backward(insert_pos, this->end().current - 2, this->end().current - 1);
						// A A A X X Y Z O O
						//           ^
						kerbal::assign::generic_assign(*insert_pos, kerbal::compatibility::to_xvalue(helper.storage.raw_value()));
						// *insert_pos = kerbal::compatibility::to_xvalue(helper.storage.raw_value());
					}
				} else { // new_size > this->k_capacity
					size_type new_capacity = this->k_capacity == 0 ? 1 : 2 * this->k_capacity;
					pointer new_buffer = allocator_traits::allocate(alloc, new_capacity);
#		if !__cpp_exceptions
					if (new_buffer == NULL) {
						kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
					}
#		endif
					pointer emplace_pos = new_buffer + insert_pos_index;

#		if __cpp_exceptions
					try {
#		endif
						kerbal::memory::construct_at_using_allocator(alloc, emplace_pos, kerbal::utility::forward<Args>(args)...);
#		if __cpp_exceptions
					} catch (...) {
						allocator_traits::deallocate(alloc, new_buffer, new_capacity);
						throw;
					}
#		endif

					this->emplace_realloc_aux(alloc, insert_pos_index, new_buffer, new_capacity);
				}
				return this->nth(insert_pos_index);
			}

#		else

#		define EMPTY
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)

#	if __cpp_exceptions
#		define FBODY_REALLOC(i) \
				{ \
					size_type new_capacity = this->k_capacity == 0 ? 1 : 2 * this->k_capacity; \
					pointer new_buffer = allocator_traits::allocate(alloc, new_capacity); \
					pointer emplace_pos = new_buffer + insert_pos_index; \
 \
					try { \
						kerbal::memory::construct_at_using_allocator(alloc, emplace_pos KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
					} catch (...) { \
						allocator_traits::deallocate(alloc, new_buffer, new_capacity); \
						throw; \
					} \
 \
					this->emplace_realloc_aux(alloc, insert_pos_index, new_buffer, new_capacity); \
				}
#	else // __cpp_exceptions
#		define FBODY_REALLOC(i) \
				{ \
					size_type new_capacity = this->k_capacity == 0 ? 1 : 2 * this->k_capacity; \
					pointer new_buffer = allocator_traits::allocate(alloc, new_capacity); \
					if (new_buffer == NULL) { \
						kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception(); \
					} \
					pointer emplace_pos = new_buffer + insert_pos_index; \
 \
					{ \
						kerbal::memory::construct_at_using_allocator(alloc, emplace_pos KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
					} \
 \
					this->emplace_realloc_aux(alloc, insert_pos_index, new_buffer, new_capacity); \
				}
#	endif // __cpp_exceptions


#		define FBODY(i) \
			template <typename Tp> \
			template <typename Allocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			typename vector_type_only<Tp>::iterator \
			vector_type_only<Tp>::k_emplace_using_allocator(Allocator & alloc, const_iterator pos KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits; \
 \
				size_type insert_pos_index = this->index_of(pos); \
				size_type ori_size = this->k_size; \
				size_type new_size = ori_size + 1; \
				if (new_size <= this->k_capacity) { \
					pointer insert_pos = pos.cast_to_mutable().current; \
					if (pos == this->cend()) { \
						kerbal::memory::construct_at_using_allocator(alloc, this->end().current KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
						this->k_size = new_size; \
					} else { \
						vector_emplace_helper<Tp, Allocator> helper(alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
 \
						kerbal::memory::construct_at_using_allocator(alloc, this->end().current, kerbal::compatibility::to_xvalue(this->back())); \
						this->k_size = new_size; \
						kerbal::algorithm::move_backward(insert_pos, this->end().current - 2, this->end().current - 1); \
						kerbal::assign::generic_assign(*insert_pos, kerbal::compatibility::to_xvalue(helper.storage.raw_value())); \
					} \
				} else { \
					FBODY_REALLOC(i); \
				} \
				return this->nth(insert_pos_index); \
			}

			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#		undef EMPTY
#		undef LEFT_JOIN_COMMA
#		undef TARGS_DECL
#		undef ARGS_DECL
#		undef ARGS_USE
#		undef FBODY_REALLOC
#		undef FBODY

#		endif

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			typename vector_type_only<Tp>::iterator
			vector_type_only<Tp>::k_insert_using_allocator(Allocator & alloc, const_iterator pos, const_reference val)
			{
				return this->k_emplace_using_allocator(alloc, pos, val);
			}

#		if __cplusplus >= 201103L

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			typename vector_type_only<Tp>::iterator
			vector_type_only<Tp>::k_insert_using_allocator(Allocator & alloc, const_iterator pos, rvalue_reference val)
			{
				return this->k_emplace_using_allocator(alloc, pos, kerbal::compatibility::move(val));
			}

#		endif

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::insert_realloc_aux(Allocator & alloc, size_type insert_pos_index, size_type n, pointer new_buffer, size_type new_capacity, size_type new_size)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				if (this->k_buffer != NULL) {
					pointer insert_pos = this->k_buffer + insert_pos_index;
					pointer new_insert_pos = new_buffer + insert_pos_index;

#		if __cpp_exceptions
					try {
						try {
							// A A A 1 2 3
							// A A A X X X X X O O O
							ui_move_if_noexcept_ow_copy_phase1(alloc, this->begin().current, insert_pos, new_buffer);
						} catch (...) {
							kerbal::memory::reverse_destroy_using_allocator(alloc, new_insert_pos, new_insert_pos + n);
							throw;
						}
						try {
							// A A A 1 2 3
							// A A A X X X X X 1 2 3
							ui_move_if_noexcept_ow_copy_phase1(alloc, insert_pos, this->end().current, new_insert_pos + n);
						} catch (...) {
							kerbal::memory::reverse_destroy_using_allocator(alloc, new_buffer, new_insert_pos + n);
							throw;
						}
					} catch (...) {
						allocator_traits::deallocate(alloc, new_buffer, new_capacity);
						throw;
					}
#		else // __cpp_exceptions
					ui_move_if_noexcept_ow_copy_phase1(alloc, this->begin().current, insert_pos, new_buffer);
					ui_move_if_noexcept_ow_copy_phase1(alloc, insert_pos, this->end().current, new_insert_pos + n);
#		endif // __cpp_exceptions

					ui_move_if_noexcept_ow_copy_phase2(alloc, this->begin().current, this->end().current);
					allocator_traits::deallocate(alloc, this->k_buffer, this->k_capacity);
				}

				this->k_buffer = new_buffer;
				this->k_capacity = new_capacity;
				this->k_size = new_size;
			}


			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			typename vector_type_only<Tp>::iterator
			vector_type_only<Tp>::k_insert_using_allocator(Allocator & alloc, const_iterator pos, size_type n, const_reference val)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				size_type insert_pos_index = this->index_of(pos);
				size_type ori_size = this->k_size;
				size_type new_size = ori_size + n;
				if (new_size <= this->k_capacity) {
					pointer insert_pos = pos.cast_to_mutable().current;
					if (n == 0) {
						// pass
					} else if (pos == this->cend()) {
						// A A A O O O
						//       ^
						// construct at the end
						kerbal::memory::uninitialized_fill_using_allocator(alloc, this->end().current, this->nth(new_size).current, val);
						this->k_size = new_size;
					} else if (insert_pos_index + n <= ori_size) {
						// A A A 1 2 3 4 5 6
						// A A A X X 1 2 3 4 5 6

						// construct at the end
						// A A A 1 2 3 4 5 6
						// A A A 1 2 3 4 5 6 5 6
						kerbal::memory::uninitialized_copy_using_allocator(alloc, this->cend().current - n, this->cend().current, this->end().current);
						this->k_size = new_size;

						// A A A 1 2 3 4 5 6
						// A A A 1 2 1 2 3 4 5 6
						kerbal::algorithm::move_backward(insert_pos, this->end().current - n, this->end().current);

						// A A A 1 2 3 4 5 6
						// A A A X X 1 2 3 4 5 6
						kerbal::algorithm::fill(insert_pos, insert_pos + n, val);
					} else {
						// A A A 1 2 3
						// A A A X X X X X 1 2 3

						// A A A 1 2 3
						// A A A 1 2 3 X X
						kerbal::memory::uninitialized_fill_using_allocator(alloc, this->end().current, insert_pos + n, val);
#		if __cpp_exceptions
						try {
#		endif
							// A A A 1 2 3
							// A A A 1 2 3 X X 1 2 3
							kerbal::memory::uninitialized_copy_using_allocator(alloc, pos.current, this->cend().current, insert_pos + n);
#		if __cpp_exceptions
						} catch (...) {
							kerbal::memory::reverse_destroy_using_allocator(alloc, this->end().current, insert_pos + n);
							throw;
						}
#		endif
						this->k_size = new_size;
						// A A A 1 2 3
						// A A A X X X X X 1 2 3
						kerbal::algorithm::fill(insert_pos, this->nth(ori_size).current, val);
					}
				} else { // new_size > this->k_capacity
					// A A A 1 2 3
					// A A A X X X X X 1 2 3

					size_type new_capacity = 2 * new_size;
					pointer new_buffer = allocator_traits::allocate(alloc, new_capacity);
#		if !__cpp_exceptions
					if (new_buffer == NULL) {
						kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
					}
#		endif
					pointer new_insert_pos = new_buffer + insert_pos_index;

#		if __cpp_exceptions
					try {
#		endif
						// A A A 1 2 3
						// O O O X X X X X O O O
						kerbal::memory::uninitialized_fill_using_allocator(alloc, new_insert_pos, new_insert_pos + n, val);
#		if __cpp_exceptions
					} catch (...) {
						allocator_traits::deallocate(alloc, new_buffer, new_capacity);
						throw;
					}
#		endif

					this->insert_realloc_aux(alloc, insert_pos_index, n, new_buffer, new_capacity, new_size);
				}
				return this->nth(insert_pos_index);
			}

			template <typename Tp>
			template <typename Allocator, typename InputIterator>
			KERBAL_CONSTEXPR20
			typename vector_type_only<Tp>::iterator
			vector_type_only<Tp>::k_range_insert_using_allocator_impl(Allocator & alloc, const_iterator pos, InputIterator first, InputIterator last, std::input_iterator_tag)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				vector_type_only vt(alloc, first, last);

				struct destroy_helper
				{
						Allocator & alloc;
						vector_type_only & vt;

						KERBAL_CONSTEXPR20
						destroy_helper(Allocator & alloc, vector_type_only & vt) KERBAL_NOEXCEPT :
								alloc(alloc), vt(vt)
						{
						}

						KERBAL_CONSTEXPR20
						~destroy_helper() KERBAL_NOEXCEPT
						{
							this->vt.k_destroy_using_allocator(alloc);
						}

				} auto_destroy_helper(alloc, vt);

				size_type insert_pos_index = this->index_of(pos);
				size_type n = vt.size();
				size_type ori_size = this->k_size;
				size_type new_size = ori_size + n;
				if (new_size <= this->k_capacity) {
					pointer insert_pos = this->k_buffer + insert_pos_index;
					if (n == 0) {
						// pass
					} else if (pos == this->cend()) {
						// A A A O O O
						//       ^
						// construct at the end
						ui_move_if_noexcept_ow_copy_phase1(alloc, vt.begin().current, vt.end().current, this->end().current);
						this->k_size = new_size;
						ui_move_if_noexcept_ow_copy_phase2(alloc, vt.begin().current, vt.end().current);
						vt.k_size = 0;
					} else if (insert_pos_index + n <= ori_size) {
						// A A A 1 2 3 4 5 6
						// A A A X X 1 2 3 4 5 6

						// construct at the end
						// A A A 1 2 3 4 5 6
						// A A A 1 2 3 4 5 6 5 6
						kerbal::memory::uninitialized_copy_using_allocator(alloc, this->cend().current - n, this->cend().current, this->end().current);
						this->k_size = new_size;

						// A A A 1 2 3 4 5 6
						// A A A 1 2 1 2 3 4 5 6
						kerbal::algorithm::move_backward(insert_pos, this->end().current - n, this->end().current);

						// A A A 1 2 3 4 5 6
						// A A A X X 1 2 3 4 5 6
						kerbal::algorithm::copy(vt.begin().current, vt.end().current, insert_pos);
					} else {
						// A A A 1 2 3
						// A A A X X X X X 1 2 3

						kerbal::memory::uninitialized_copy_using_allocator(alloc, pos.current, this->cend().current, insert_pos + n);

#		if __cpp_exceptions
						try {
#		endif
							kerbal::utility::compressed_pair<pointer, pointer> copy_n_r(kerbal::algorithm::copy_n(vt.begin().current, ori_size - insert_pos_index, insert_pos));
							ui_move_if_noexcept_ow_copy_phase1(alloc, copy_n_r.first(), vt.end().current, copy_n_r.second());
							this->k_size = new_size;
							ui_move_if_noexcept_ow_copy_phase2(alloc, copy_n_r.first(), vt.end().current);
							vt.k_size = ori_size - insert_pos_index;
#		if __cpp_exceptions
						} catch (...) {
							kerbal::memory::reverse_destroy_using_allocator(alloc, insert_pos + n, this->nth(new_size).current);
							throw;
						}
#		endif
					}
				} else { // new_size > this->k_capacity
					// A A A 1 2 3
					// A A A X X X X X 1 2 3

					size_type new_capacity = 2 * new_size;
					pointer new_buffer = allocator_traits::allocate(alloc, new_capacity);
#		if !__cpp_exceptions
					if (new_buffer == NULL) {
						kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
					}
#		endif
					pointer new_insert_pos = new_buffer + insert_pos_index;

#		if __cpp_exceptions
					try {
#		endif
						// A A A 1 2 3
						// O O O X X X X X O O O
						ui_move_if_noexcept_ow_copy_phase1(alloc, vt.begin().current, vt.end().current, new_insert_pos);
#		if __cpp_exceptions
					} catch (...) {
						allocator_traits::deallocate(alloc, new_buffer, new_capacity);
						throw;
					}
#		endif

					ui_move_if_noexcept_ow_copy_phase2(alloc, vt.begin().current, vt.end().current);
					vt.k_size = 0;

					this->insert_realloc_aux(alloc, insert_pos_index, n, new_buffer, new_capacity, new_size);
				}
				return this->nth(insert_pos_index);
			}

			template <typename Tp>
			template <typename Allocator, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			typename vector_type_only<Tp>::iterator
			vector_type_only<Tp>::k_range_insert_using_allocator_impl(Allocator & alloc, const_iterator pos, ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				size_type insert_pos_index = this->index_of(pos);
				size_type n = static_cast<size_type>(kerbal::iterator::distance(first, last));
				size_type ori_size = this->k_size;
				size_type new_size = ori_size + n;
				if (new_size <= this->k_capacity) {
					pointer insert_pos = this->k_buffer + insert_pos_index;
					if (n == 0) {
						// pass
					} else if (pos == this->cend()) {
						// A A A O O O
						//       ^
						// construct at the end
						kerbal::memory::uninitialized_copy_using_allocator(alloc, first, last, this->end().current);
						this->k_size = new_size;
					} else if (insert_pos_index + n <= ori_size) {
						// A A A 1 2 3 4 5 6
						// A A A X X 1 2 3 4 5 6

						// construct at the end
						// A A A 1 2 3 4 5 6
						// A A A 1 2 3 4 5 6 5 6
						kerbal::memory::uninitialized_copy_using_allocator(alloc, this->cend().current - n, this->cend().current, this->end().current);
						this->k_size = new_size;

						// A A A 1 2 3 4 5 6
						// A A A 1 2 1 2 3 4 5 6
						kerbal::algorithm::move_backward(insert_pos, this->end().current - n, this->end().current);

						// A A A 1 2 3 4 5 6
						// A A A X X 1 2 3 4 5 6
						kerbal::algorithm::copy(first, last, insert_pos);
					} else {
						// A A A 1 2 3
						// A A A X X X X X 1 2 3

						kerbal::memory::uninitialized_copy_using_allocator(alloc, pos.current, this->cend().current, insert_pos + n);

#		if __cpp_exceptions
						try {
#		endif
							kerbal::utility::compressed_pair<ForwardIterator, pointer> copy_n_r(kerbal::algorithm::copy_n(first, ori_size - insert_pos_index, insert_pos));
							kerbal::memory::uninitialized_copy_using_allocator(alloc, copy_n_r.first(), last, copy_n_r.second());
#		if __cpp_exceptions
						} catch (...) {
							kerbal::memory::reverse_destroy_using_allocator(alloc, insert_pos + n, this->nth(new_size).current);
							throw;
						}
#		endif
						this->k_size = new_size;
					}
				} else { // new_size > this->k_capacity
					// A A A 1 2 3
					// A A A X X X X X 1 2 3

					size_type new_capacity = 2 * new_size;
					pointer new_buffer = allocator_traits::allocate(alloc, new_capacity);
#		if !__cpp_exceptions
					if (new_buffer == NULL) {
						kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
					}
#		endif
					pointer new_insert_pos = new_buffer + insert_pos_index;

#		if __cpp_exceptions
					try {
#		endif
						// A A A 1 2 3
						// O O O X X X X X O O O
						kerbal::memory::uninitialized_copy_using_allocator(alloc, first, last, new_insert_pos);
#		if __cpp_exceptions
					} catch (...) {
						allocator_traits::deallocate(alloc, new_buffer, new_capacity);
						throw;
					}
#		endif

					this->insert_realloc_aux(alloc, insert_pos_index, n, new_buffer, new_capacity, new_size);
				}
				return this->nth(insert_pos_index);
			}

			template <typename Tp>
			template <typename Allocator, typename InputIterator>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<
					kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
					typename vector_type_only<Tp>::iterator
			>::type
			vector_type_only<Tp>::k_insert_using_allocator(Allocator & alloc, const_iterator pos, InputIterator first, InputIterator last)
			{
				return this->k_range_insert_using_allocator_impl(alloc, pos, first, last, kerbal::iterator::iterator_category(first));
			}


			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_emplace_back_transfer_ele(Allocator & alloc, pointer new_buffer, size_type new_capacity)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				if (this->k_buffer != NULL) {
#		if __cpp_exceptions
					try {
#		endif
						ui_move_if_noexcept_ow_copy_phase1(alloc, this->begin().current, this->end().current, new_buffer);
#		if __cpp_exceptions
					} catch (...) {
						pointer emplace_pos = new_buffer + this->k_size;
						kerbal::memory::destroy_at_using_allocator(alloc, emplace_pos);
						allocator_traits::deallocate(alloc, new_buffer, new_capacity);
						throw;
					}
#		endif
					ui_move_if_noexcept_ow_copy_phase2(alloc, this->begin().current, this->end().current);
					allocator_traits::deallocate(alloc, this->k_buffer, this->k_capacity);
				}
				this->k_buffer = new_buffer;
				this->k_capacity = new_capacity;
				++this->k_size;
			}

#		if __cplusplus >= 201103L

			template <typename Tp>
			template <typename Allocator, typename ... Args>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_emplace_back_ua_expand_buffer(kerbal::type_traits::false_type, Allocator & alloc, Args&& ... args)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				size_type ori_size = this->k_size;
				size_type new_capacity = this->k_capacity == 0 ? 1 : this->k_capacity * 2;
				pointer new_buffer = allocator_traits::allocate(alloc, new_capacity);
#		if !__cpp_exceptions
				if (new_buffer == NULL) {
					kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
				}
#		endif
				pointer emplace_pos = new_buffer + ori_size;

#		if __cpp_exceptions
				try {
#		endif
					kerbal::memory::construct_at_using_allocator(alloc, emplace_pos, kerbal::utility::forward<Args>(args)...);
#		if __cpp_exceptions
				} catch (...) {
					allocator_traits::deallocate(alloc, new_buffer, new_capacity);
					throw;
				}
#		endif

				this->k_emplace_back_transfer_ele(alloc, new_buffer, new_capacity);
			}

			template <typename Tp>
			template <typename Allocator, typename ... Args>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_emplace_back_ua_expand_buffer(kerbal::type_traits::true_type, Allocator & alloc, Args&& ... args)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				size_type ori_size = this->k_size;
				size_type new_capacity = this->k_capacity == 0 ? 1 : this->k_capacity * 2;
				pointer new_buffer = allocator_traits::reallocate(alloc, this->k_buffer, this->k_capacity, new_capacity);
#		if !__cpp_exceptions
				if (new_buffer == NULL) {
					kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
				}
#		endif
				pointer emplace_pos = new_buffer + ori_size;

				kerbal::memory::construct_at_using_allocator(alloc, emplace_pos, kerbal::utility::forward<Args>(args)...);

				this->k_buffer = new_buffer;
				this->k_capacity = new_capacity;
				++this->k_size;
			}

			template <typename Tp>
			template <typename Allocator, typename ... Args>
			KERBAL_CONSTEXPR20
			typename vector_type_only<Tp>::reference
			vector_type_only<Tp>::k_emplace_back_using_allocator(Allocator & alloc, Args&& ... args)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				size_type ori_size = this->k_size;
				size_type new_size = ori_size + 1;
				if (new_size <= this->k_capacity) {
					kerbal::memory::construct_at_using_allocator(alloc, this->end().current, kerbal::utility::forward<Args>(args)...);
					++this->k_size;
				} else {
					typedef typename allocator_traits::has_reallocate has_reallocate;
					this->k_emplace_back_ua_expand_buffer(has_reallocate(), alloc, kerbal::utility::forward<Args>(args)...);
				}
				return this->k_buffer[this->k_size];
			}

#		else

#		define EMPTY
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#	if __cpp_exceptions
#		define FBODY_EXPAND_BUFFER(i) \
			template <typename Tp> \
			template <typename Allocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			void vector_type_only<Tp>::k_emplace_back_ua_expand_buffer(kerbal::type_traits::false_type, Allocator & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits; \
 \
				size_type ori_size = this->k_size; \
				size_type new_capacity = this->k_capacity == 0 ? 1 : this->k_capacity * 2; \
				pointer new_buffer = allocator_traits::allocate(alloc, new_capacity); \
				pointer emplace_pos = new_buffer + ori_size; \
 \
				try { \
					kerbal::memory::construct_at_using_allocator(alloc, emplace_pos KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				} catch (...) { \
					allocator_traits::deallocate(alloc, new_buffer, new_capacity); \
					throw; \
				} \
 \
				this->k_emplace_back_transfer_ele(alloc, new_buffer, new_capacity); \
			} \
 \
			template <typename Tp> \
			template <typename Allocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			void vector_type_only<Tp>::k_emplace_back_ua_expand_buffer(kerbal::type_traits::true_type, Allocator & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits; \
 \
				size_type ori_size = this->k_size; \
				size_type new_capacity = this->k_capacity == 0 ? 1 : this->k_capacity * 2; \
				pointer new_buffer = allocator_traits::reallocate(alloc, this->k_buffer, this->k_capacity, new_capacity); \
				pointer emplace_pos = new_buffer + ori_size; \
 \
				kerbal::memory::construct_at_using_allocator(alloc, emplace_pos KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
 \
				this->k_buffer = new_buffer; \
				this->k_capacity = new_capacity; \
				++this->k_size; \
			}
#	else // __cpp_exceptions
#		define FBODY_EXPAND_BUFFER(i) \
			template <typename Tp> \
			template <typename Allocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			void vector_type_only<Tp>::k_emplace_back_ua_expand_buffer(kerbal::type_traits::false_type, Allocator & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits; \
 \
				size_type ori_size = this->k_size; \
				size_type new_capacity = this->k_capacity == 0 ? 1 : this->k_capacity * 2; \
				pointer new_buffer = allocator_traits::allocate(alloc, new_capacity); \
				if (new_buffer == NULL) { \
					kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception(); \
				} \
				pointer emplace_pos = new_buffer + ori_size; \
 \
				{ \
					kerbal::memory::construct_at_using_allocator(alloc, emplace_pos KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				} \
 \
				this->k_emplace_back_transfer_ele(alloc, new_buffer, new_capacity); \
			} \
			template <typename Tp> \
			template <typename Allocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			void vector_type_only<Tp>::k_emplace_back_ua_expand_buffer(kerbal::type_traits::true_type, Allocator & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits; \
 \
				size_type ori_size = this->k_size; \
				size_type new_capacity = this->k_capacity == 0 ? 1 : this->k_capacity * 2; \
				pointer new_buffer = allocator_traits::reallocate(alloc, this->k_buffer, this->k_capacity, new_capacity); \
				if (new_buffer == NULL) { \
					kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception(); \
				} \
				pointer emplace_pos = new_buffer + ori_size; \
 \
				kerbal::memory::construct_at_using_allocator(alloc, emplace_pos KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
 \
				this->k_buffer = new_buffer; \
				this->k_capacity = new_capacity; \
				++this->k_size; \
			}
#	endif // __cpp_exceptions

#		define FBODY(i) \
			FBODY_EXPAND_BUFFER(i) \
			template <typename Tp> \
			template <typename Allocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			typename vector_type_only<Tp>::reference \
			vector_type_only<Tp>::k_emplace_back_using_allocator(Allocator & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits; \
 \
				size_type ori_size = this->k_size; \
				size_type new_size = ori_size + 1; \
				if (new_size <= this->k_capacity) { \
					kerbal::memory::construct_at_using_allocator(alloc, this->end().current KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
					++this->k_size; \
				} else { \
					typedef typename allocator_traits::has_reallocate has_reallocate; \
					this->k_emplace_back_ua_expand_buffer(has_reallocate(), alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				} \
				return this->k_buffer[this->k_size]; \
			}

			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#		undef EMPTY
#		undef LEFT_JOIN_COMMA
#		undef TARGS_DECL
#		undef ARGS_DECL
#		undef ARGS_USE
#		undef FBODY_EXPAND_BUFFER
#		undef FBODY

#		endif

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_push_back_using_allocator(Allocator & alloc, const_reference src)
			{
				this->k_emplace_back_using_allocator(alloc, src);
			}

#		if __cplusplus >= 201103L

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_push_back_using_allocator(Allocator & alloc, rvalue_reference src)
			{
				this->k_emplace_back_using_allocator(alloc, kerbal::compatibility::move(src));
			}

#		endif



		//===================
		// erase

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			typename vector_type_only<Tp>::iterator
			vector_type_only<Tp>::k_erase_using_allocator(Allocator & alloc, const_iterator pos)
			{
				iterator pos_mut(pos.cast_to_mutable());

				if (pos == this->cend()) {
					return pos_mut;
				}

				// pre-condition: pos != cend()
				kerbal::algorithm::move(pos_mut.current + 1, this->end().current, pos_mut.current);
				this->k_pop_back_using_allocator(alloc);
				return pos_mut;
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			typename vector_type_only<Tp>::iterator
			vector_type_only<Tp>::k_erase_using_allocator(Allocator & alloc, const_iterator first, const_iterator last)
			{
				iterator first_mut(first.cast_to_mutable());
				if (first == last) {
					return first_mut;
				}
				iterator last_mut(last.cast_to_mutable());

				pointer new_end(kerbal::algorithm::move(last_mut.current, this->end().current, first_mut.current));
				kerbal::memory::reverse_destroy_using_allocator(alloc, new_end, this->end().current);
				size_type new_size = new_end - this->k_buffer;
				this->k_size = new_size;
				return first_mut;
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_pop_back_using_allocator(Allocator & alloc) KERBAL_NOEXCEPT
			{
				kerbal::memory::destroy_on_using_allocator(alloc, this->back());
				--this->k_size;
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_clear_using_allocator(Allocator & alloc) KERBAL_NOEXCEPT
			{
				kerbal::memory::reverse_destroy_using_allocator(alloc, this->begin().current, this->end().current);
				this->k_size = 0;
			}


		//===================
		// operation

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_resize_transfer_ele(Allocator & alloc, pointer new_buffer, size_type new_capacity, size_type new_size)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				if (this->k_buffer != NULL) {
#		if __cpp_exceptions
					try {
#		endif
						ui_move_if_noexcept_ow_copy_phase1(alloc, this->begin().current, this->end().current, new_buffer);
#		if __cpp_exceptions
					} catch (...) {
						size_type ori_size = this->k_size;
						kerbal::memory::reverse_destroy_using_allocator(alloc, new_buffer + ori_size, new_buffer + new_size);
						allocator_traits::deallocate(alloc, new_buffer, new_capacity);
						throw;
					}
#		endif
					ui_move_if_noexcept_ow_copy_phase2(alloc, this->begin().current, this->end().current);
					allocator_traits::deallocate(alloc, this->k_buffer, this->k_capacity);
				}
				this->k_buffer = new_buffer;
				this->k_capacity = new_capacity;
				this->k_size = new_size;
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_resize_expand_buffer(kerbal::type_traits::false_type, Allocator & alloc, size_type new_size)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				size_type ori_size = this->k_size;
				size_type new_capacity = 2 * new_size;
				pointer new_buffer = allocator_traits::allocate(alloc, new_capacity);
#		if !__cpp_exceptions
				if (new_buffer == NULL) {
					kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
				}
#		endif

#		if __cpp_exceptions
				try {
#		endif
					kerbal::memory::uninitialized_value_construct_using_allocator(alloc, new_buffer + ori_size, new_buffer + new_size);
#		if __cpp_exceptions
				} catch (...) {
					allocator_traits::deallocate(alloc, new_buffer, new_capacity);
					throw;
				}
#		endif

				this->k_resize_transfer_ele(alloc, new_buffer, new_capacity, new_size);
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_resize_expand_buffer(kerbal::type_traits::true_type, Allocator & alloc, size_type new_size)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				size_type ori_size = this->k_size;
				size_type new_capacity = 2 * new_size;
				pointer new_buffer = allocator_traits::reallocate(alloc, this->k_buffer, this->k_capacity, new_capacity);
#		if !__cpp_exceptions
				if (new_buffer == NULL) {
					kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
				}
#		endif

				kerbal::memory::uninitialized_value_construct_using_allocator(alloc, new_buffer + ori_size, new_buffer + new_size);

				this->k_buffer = new_buffer;
				this->k_capacity = new_capacity;
				this->k_size = new_size;
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_resize_expand_buffer(kerbal::type_traits::false_type, Allocator & alloc, size_type new_size, const_reference value)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				size_type ori_size = this->k_size;
				size_type new_capacity = 2 * new_size;
				pointer new_buffer = allocator_traits::allocate(alloc, new_capacity);
#		if !__cpp_exceptions
				if (new_buffer == NULL) {
					kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
				}
#		endif

#		if __cpp_exceptions
				try {
#		endif
					kerbal::memory::uninitialized_fill_using_allocator(alloc, new_buffer + ori_size, new_buffer + new_size, value);
#		if __cpp_exceptions
				} catch (...) {
					allocator_traits::deallocate(alloc, new_buffer, new_capacity);
					throw;
				}
#		endif

				this->k_resize_transfer_ele(alloc, new_buffer, new_capacity, new_size);
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_resize_expand_buffer(kerbal::type_traits::true_type, Allocator & alloc, size_type new_size, const_reference value)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				size_type ori_size = this->k_size;
				size_type new_capacity = 2 * new_size;
				pointer new_buffer = allocator_traits::reallocate(alloc, this->k_buffer, this->k_capacity, new_capacity);
#		if !__cpp_exceptions
				if (new_buffer == NULL) {
					kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
				}
#		endif

				kerbal::memory::uninitialized_fill_using_allocator(alloc, new_buffer + ori_size, new_buffer + new_size, value);

				this->k_buffer = new_buffer;
				this->k_capacity = new_capacity;
				this->k_size = new_size;
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_resize_using_allocator(Allocator & alloc, size_type new_size)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				size_type ori_size = this->k_size;
				if (new_size <= ori_size) { // also suitable for new_size == 0
					/*
					 * a a a a a a x x
					 * a a a x x x x x
					 */
					kerbal::memory::reverse_destroy_using_allocator(alloc, this->nth(new_size).current, this->nth(ori_size).current);
					this->k_size = new_size;
				} else { // new_size > ori_size
					if (new_size <= this->k_capacity) {
						/*
						 * a a a x x x x x
						 * a a a b b b x x
						 */
						kerbal::memory::uninitialized_value_construct_using_allocator(alloc, this->nth(ori_size).current, this->nth(new_size).current);
						this->k_size = new_size;
					} else {
						typedef typename allocator_traits::has_reallocate has_reallocate;
						this->k_resize_expand_buffer(has_reallocate(), alloc, new_size);
					}
				}
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::k_resize_using_allocator(Allocator & alloc, size_type new_size, const_reference value)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				size_type ori_size = this->k_size;
				if (new_size <= ori_size) { // also suitable for new_size == 0
					/*
					 * a a a a a a x x
					 * a a a x x x x x
					 */
					kerbal::memory::reverse_destroy_using_allocator(alloc, this->nth(new_size).current, this->nth(ori_size).current);
					this->k_size = new_size;
				} else { // new_size > ori_size
					if (new_size <= this->k_capacity) {
						/*
						 * a a a x x x x x
						 * a a a b b b x x
						 */
						kerbal::memory::uninitialized_fill_using_allocator(alloc, this->nth(ori_size).current, this->nth(new_size).current, value);
						this->k_size = new_size;
					} else {
						typedef typename allocator_traits::has_reallocate has_reallocate;
						this->k_resize_expand_buffer(has_reallocate(), alloc, new_size, value);
					}
				}
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			void vector_type_only<Tp>::k_swap_type_unrelated(vector_type_only & lhs, vector_type_only & rhs) KERBAL_NOEXCEPT
			{
				kerbal::algorithm::swap(lhs.k_buffer, rhs.k_buffer);
				kerbal::algorithm::swap(lhs.k_size, rhs.k_size);
				kerbal::algorithm::swap(lhs.k_capacity, rhs.k_capacity);
			}



			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::ui_move_if_noexcept_ow_copy_phase1(Allocator & alloc, pointer first, pointer last, pointer to)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(
							kerbal::memory::ui_move_if_noexcept_ow_copy<Allocator, pointer, pointer>::phase1(alloc, first, last, to)
						)
					)
			{
				kerbal::memory::ui_move_if_noexcept_ow_copy<Allocator, pointer, pointer>::phase1(alloc, first, last, to);
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_type_only<Tp>::ui_move_if_noexcept_ow_copy_phase2(Allocator & alloc, pointer first, pointer last) KERBAL_NOEXCEPT
			{
				kerbal::memory::ui_move_if_noexcept_ow_copy<Allocator, pointer, pointer>::phase2(alloc, first, last);
			}

		} // namespace detail

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_DETAIL_VECTOR_BASE_VECTOR_BASE_IMPL_HPP
