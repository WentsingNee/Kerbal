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

#include <kerbal/algorithm/modifier.hpp>
#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/memory/raw_storage.hpp>
#include <kerbal/memory/uninitialized_using_allocator.hpp>
#include <kerbal/operators/generic_assign.hpp>
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
			vector_allocator_unrelated<Tp>::vector_allocator_unrelated() KERBAL_NOEXCEPT :
					_K_buffer(NULL), _K_capacity(0), _K_size(0)
			{
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			vector_allocator_unrelated<Tp>::vector_allocator_unrelated(Allocator & alloc, size_type count)
			{
				if (count == 0) {
					this->_K_buffer = NULL;
					this->_K_capacity = 0;
					this->_K_size = 0;
					return;
				}

				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				this->_K_capacity = count;
				this->_K_buffer = allocator_traits::allocate(alloc, this->_K_capacity);
#		if !__cpp_exceptions
				if (this->_K_buffer == NULL) {
					kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
				}
#		endif

#		if __cpp_exceptions
				try {
#		endif
					kerbal::memory::uninitialized_value_construct_using_allocator(alloc, this->_K_buffer, this->_K_buffer + count);
#		if __cpp_exceptions
				} catch (...) {
					allocator_traits::deallocate(alloc, this->_K_buffer, this->_K_capacity);
					throw;
				}
#		endif
				this->_K_size = count;
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			vector_allocator_unrelated<Tp>::vector_allocator_unrelated(Allocator & alloc, size_type count, const_reference value)
			{
				if (count == 0) {
					this->_K_buffer = NULL;
					this->_K_capacity = 0;
					this->_K_size = 0;
					return;
				}

				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				this->_K_capacity = count;
				this->_K_buffer = allocator_traits::allocate(alloc, this->_K_capacity);
#		if !__cpp_exceptions
				if (this->_K_buffer == NULL) {
					kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
				}
#		endif

#		if __cpp_exceptions
				try {
#		endif
					kerbal::memory::uninitialized_fill_using_allocator(alloc, this->_K_buffer, this->_K_buffer + count, value);
#		if __cpp_exceptions
				} catch (...) {
					allocator_traits::deallocate(alloc, this->_K_buffer, this->_K_capacity);
					throw;
				}
#		endif
				this->_K_size = count;
			}

			template <typename Tp>
			template <typename Allocator, typename InputIterator>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::_K_range_copy_cnstrct_impl(Allocator & alloc, InputIterator first, InputIterator last,
																			std::input_iterator_tag)
			{
				this->_K_buffer = NULL;
				this->_K_capacity = 0;
				this->_K_size = 0;

#		if __cpp_exceptions
				try {
#		endif
					while (first != last) {
						this->emplace_back_using_allocator(alloc, *first);
						++first;
					}
#		if __cpp_exceptions
				} catch (...) {
					if (this->_K_buffer != NULL) {
						typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;
						kerbal::memory::reverse_destroy_using_allocator(alloc, this->begin().current, this->end().current);
						allocator_traits::deallocate(alloc, this->_K_buffer, this->_K_capacity);
					}
					throw;
				}
#		endif

			}

			template <typename Tp>
			template <typename Allocator, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::_K_range_copy_cnstrct_impl(Allocator & alloc, ForwardIterator first, ForwardIterator last,
																			std::forward_iterator_tag)
			{
				size_type len = static_cast<size_type>(kerbal::iterator::distance(first, last));

				if (len == 0) {
					this->_K_buffer = NULL;
					this->_K_capacity = 0;
					this->_K_size = 0;
					return;
				}

				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				this->_K_capacity = len;
				this->_K_buffer = allocator_traits::allocate(alloc, this->_K_capacity);
#		if !__cpp_exceptions
				if (this->_K_buffer == NULL) {
					kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
				}
#		endif

#		if __cpp_exceptions
				try {
#		endif
					kerbal::memory::uninitialized_copy_using_allocator(alloc, first, last, this->_K_buffer);
#		if __cpp_exceptions
				} catch (...) {
					allocator_traits::deallocate(alloc, this->_K_buffer, this->_K_capacity);
					throw;
				}
#		endif
				this->_K_size = len;
			}

			template <typename Tp>
			template <typename Allocator, typename InputIterator>
			KERBAL_CONSTEXPR20
			vector_allocator_unrelated<Tp>::vector_allocator_unrelated(Allocator & alloc, InputIterator first, InputIterator last)
			{
				this->_K_range_copy_cnstrct_impl(alloc, first, last, kerbal::iterator::iterator_category(first));
			}

#		if __cplusplus >= 201103L

			template <typename Tp>
			KERBAL_CONSTEXPR14
			vector_allocator_unrelated<Tp>::vector_allocator_unrelated(vector_allocator_unrelated && src) KERBAL_NOEXCEPT :
					_K_buffer(src._K_buffer), _K_capacity(src._K_capacity), _K_size(src._K_size)
			{
				src._K_buffer = NULL;
				src._K_size = 0;
				src._K_capacity = 0;
			}

			// move construct using allocator, allocator is equal
			template <typename Tp>
			KERBAL_CONSTEXPR14
			void vector_allocator_unrelated<Tp>::_K_move_cnstrct_ua_ae(vector_allocator_unrelated && src) KERBAL_NOEXCEPT
			{
				this->_K_buffer = src._K_buffer;
				this->_K_size = src._K_size;
				this->_K_capacity = src._K_capacity;
				src._K_buffer = NULL;
				src._K_size = 0;
				src._K_capacity = 0;
			}

			// move construct using allocator, allocator is not equal
			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::_K_move_cnstrct_ua_ane(Allocator & alloc, Allocator && /*src_alloc*/, vector_allocator_unrelated && src)
			{
				if (src._K_buffer != NULL) {
					typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

					this->_K_capacity = src._K_size;
					this->_K_buffer = allocator_traits::allocate(alloc, this->_K_capacity);
#		if !__cpp_exceptions
					if (this->_K_buffer == NULL) {
						kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
					}
#		endif

#		if __cpp_exceptions
					try {
#		endif
						kerbal::memory::uninitialized_move_using_allocator(alloc, src.begin().current, src.end().current, this->_K_buffer);
#		if __cpp_exceptions
					} catch (...) {
						allocator_traits::deallocate(alloc, this->_K_buffer, this->_K_capacity);
						throw;
					}
#		endif
					this->_K_size = src._K_size;
				} else {
					this->_K_buffer = NULL;
					this->_K_size = 0;
					this->_K_capacity = 0;
				}
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::_K_move_cnstrct_ua_helper(Allocator & alloc, Allocator && src_alloc, vector_allocator_unrelated && src,
																		   kerbal::type_traits::false_type /*is_always_equal*/)
			{
				if (alloc != src_alloc) {
					this->_K_move_cnstrct_ua_ane(alloc, kerbal::compatibility::move(src_alloc), kerbal::compatibility::move(src));
				} else {
					this->_K_move_cnstrct_ua_ae(kerbal::compatibility::move(src));
				}
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR14
			void vector_allocator_unrelated<Tp>::_K_move_cnstrct_ua_helper(Allocator & /*alloc*/, Allocator && /*src_alloc*/, vector_allocator_unrelated && src,
																		   kerbal::type_traits::true_type /*is_always_equal*/) KERBAL_NOEXCEPT
			{
				this->_K_move_cnstrct_ua_ae(kerbal::compatibility::move(src));
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR14
			vector_allocator_unrelated<Tp>::vector_allocator_unrelated(Allocator & alloc, Allocator && src_alloc, vector_allocator_unrelated && src)
					KERBAL_CONDITIONAL_NOEXCEPT(is_nothrow_move_constructible_using_allocator<Allocator>::value)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;
				typedef typename allocator_traits::is_always_equal is_always_equal;

				this->_K_move_cnstrct_ua_helper(alloc, kerbal::compatibility::move(src_alloc), kerbal::compatibility::move(src), is_always_equal());
			}

#		endif

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::destroy_using_allocator(Allocator & alloc) KERBAL_NOEXCEPT
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				if (this->_K_buffer != NULL) {
					kerbal::memory::reverse_destroy_using_allocator(alloc, this->begin().current, this->end().current);
					allocator_traits::deallocate(alloc, this->_K_buffer, this->_K_capacity);
				}
			}



		//===================
		// assign

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::assign_using_allocator(Allocator & alloc, size_type new_size, const_reference value)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				size_type ori_size = this->_K_size;
				if (new_size <= ori_size) { // also suitable for new_size == 0
					/*
					 * a a a a a a x x
					 * b b b x x x x x
					 */
					kerbal::algorithm::fill(this->begin().current, this->nth(new_size).current, value);
					kerbal::memory::reverse_destroy_using_allocator(alloc, this->nth(new_size).current, this->end().current);
					this->_K_size = new_size;
				} else { // new_size > ori_size
					/*
					 * a a a x x x x x
					 * b b b b b b x x
					 */
					if (new_size <= this->_K_capacity) {
						pointer ori_end(this->end().current);
						kerbal::algorithm::fill(this->begin().current, ori_end, value);
						kerbal::memory::uninitialized_fill_using_allocator(alloc, ori_end, this->nth(new_size).current, value);
						this->_K_size = new_size;
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

						if (this->_K_buffer != NULL) {
							kerbal::memory::reverse_destroy_using_allocator(alloc, this->begin().current, this->end().current);
							allocator_traits::deallocate(alloc, this->_K_buffer, this->_K_capacity);
						}
						this->_K_buffer = new_buffer;
						this->_K_capacity = new_capacity;
						this->_K_size = new_size;
					}
				}
			}

			template <typename Tp>
			template <typename Allocator, typename InputIterator>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::_K_range_assign_using_allocator_impl(Allocator & alloc, InputIterator first, InputIterator last, std::input_iterator_tag)
			{
				iterator it(this->begin());
				iterator end(this->end());
				while (it != end) {
					if (first != last) {
						kerbal::operators::generic_assign(*it, *first);
						++first;
						++it;
					} else {
						this->erase_using_allocator(alloc, it, end);
						return;
					}
				}
				while (first != last) {
					this->emplace_back_using_allocator(alloc, *first);
					++first;
				}
			}

			template <typename Tp>
			template <typename Allocator, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::_K_range_assign_using_allocator_impl(Allocator & alloc, ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				size_type ori_size = this->_K_size;
				size_type new_size = static_cast<size_type>(kerbal::iterator::distance(first, last));

				if (new_size <= ori_size) { // also suitable for new_size == 0
					/*
					 * a a a a a a x x
					 * b b b x x x x x
					 */
					pointer new_end(kerbal::algorithm::copy(first, last, this->begin().current));
					kerbal::memory::reverse_destroy_using_allocator(alloc, new_end, this->end().current);
					this->_K_size = new_size;
				} else { // new_size > ori_size
					/*
					 * a a a x x x x x
					 * b b b b b b x x
					 */
					if (new_size <= this->_K_capacity) {
						kerbal::utility::compressed_pair<ForwardIterator, pointer> copy_n_r(kerbal::algorithm::copy_n(first, ori_size, this->_K_buffer));
						kerbal::memory::uninitialized_copy_using_allocator(alloc, copy_n_r.first(), last, copy_n_r.second());
						this->_K_size = new_size;
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

						if (this->_K_buffer != NULL) {
							kerbal::memory::reverse_destroy_using_allocator(alloc, this->begin().current, this->end().current);
							allocator_traits::deallocate(alloc, this->_K_buffer, this->_K_capacity);
						}
						this->_K_buffer = new_buffer;
						this->_K_capacity = new_capacity;
						this->_K_size = new_size;
					}
				}
			}

			template <typename Tp>
			template <typename Allocator, typename InputIterator>
			KERBAL_CONSTEXPR20
			typename kerbal::type_traits::enable_if<
					kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
			>::type
			vector_allocator_unrelated<Tp>::assign_using_allocator(Allocator & alloc, InputIterator first, InputIterator last)
			{
				this->_K_range_assign_using_allocator_impl(alloc, first, last, kerbal::iterator::iterator_category(first));
			}


			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::_K_cpy_ass_ua_impl(Allocator & alloc, const Allocator & src_alloc, const vector_allocator_unrelated & src,
																	CPYASS_VER_NOT_PROPAGATE)
			{
				if (alloc != src_alloc) {
					this->destroy_using_allocator(alloc);
					this->_K_buffer = NULL;
					this->_K_capacity = 0;
					this->_K_size = 0;
				}
				this->assign_using_allocator(alloc, src.cbegin().current, src.cend().current);
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::_K_cpy_ass_ua_impl(Allocator & alloc, const Allocator & src_alloc, const vector_allocator_unrelated & src,
																	CPYASS_VER_PROPAGATE)
			{
				if (alloc != src_alloc) {
					this->destroy_using_allocator(alloc);
					this->_K_buffer = NULL;
					this->_K_capacity = 0;
					this->_K_size = 0;
				}
				alloc = src_alloc;
				this->assign_using_allocator(alloc, src.cbegin().current, src.cend().current);
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::_K_cpy_ass_ua_impl(Allocator & alloc, const Allocator & /*src_alloc*/, const vector_allocator_unrelated & src,
																	CPYASS_VER_ALWAYS_EQUAL)
			{
				this->assign_using_allocator(alloc, src.cbegin().current, src.cend().current);
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::assign_using_allocator(Allocator & alloc, const Allocator & src_alloc, const vector_allocator_unrelated & src)
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

				this->_K_cpy_ass_ua_impl(alloc, src_alloc, src, VER());
			}


#		if __cplusplus >= 201103L

			// move assign using allocator, allocator is equal
			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::_K_mov_ass_ua_ae(Allocator & alloc, vector_allocator_unrelated && src) KERBAL_NOEXCEPT
			{
				this->destroy_using_allocator(alloc);
				this->_K_buffer = src._K_buffer;
				this->_K_capacity = src._K_capacity;
				this->_K_size = src._K_size;
				src._K_buffer = NULL;
				src._K_capacity = 0;
				src._K_size = 0;
			}

			// move assign using allocator, allocator is not equal
			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::_K_mov_ass_ua_ane(Allocator & alloc, Allocator && /*src_alloc*/, vector_allocator_unrelated && src)
			{
				this->assign_using_allocator(alloc, kerbal::iterator::make_move_iterator(src.begin().current), kerbal::iterator::make_move_iterator(src.end().current));
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::_K_mov_ass_ua_impl(Allocator & alloc, Allocator && src_alloc, vector_allocator_unrelated && src,
																	MOVASS_VER_NOT_PROPAGATE)
			{
				if (alloc != src_alloc) {
					this->_K_mov_ass_ua_ane(alloc, kerbal::compatibility::move(src_alloc), kerbal::compatibility::move(src));
				} else {
					this->_K_mov_ass_ua_ae(alloc, kerbal::compatibility::move(src));
				}
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::_K_mov_ass_ua_impl(Allocator & alloc, Allocator && src_alloc, vector_allocator_unrelated && src,
																	MOVASS_VER_PROPAGATE)
			{
				this->destroy_using_allocator(alloc);
				this->_K_buffer = NULL;
				this->_K_capacity = 0;
				this->_K_size = 0;
				alloc = kerbal::compatibility::move(src_alloc);
				this->_K_buffer = src._K_buffer;
				this->_K_capacity = src._K_capacity;
				this->_K_size = src._K_size;
				src._K_buffer = NULL;
				src._K_capacity = 0;
				src._K_size = 0;
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::_K_mov_ass_ua_impl(Allocator & alloc, Allocator && /*src_alloc*/, vector_allocator_unrelated && src,
																	MOVASS_VER_ALWAYS_EQUAL) KERBAL_NOEXCEPT
			{
				this->_K_mov_ass_ua_ae(alloc, kerbal::compatibility::move(src));
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::assign_using_allocator(Allocator & alloc, Allocator && src_alloc, vector_allocator_unrelated && src)
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

				this->_K_mov_ass_ua_impl(
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
			typename vector_allocator_unrelated<Tp>::reference
			vector_allocator_unrelated<Tp>::at(size_type index)
			{
				if (index >= this->_K_size) {
					kerbal::utility::throw_this_exception_helper<std::out_of_range>::throw_this_exception((const char*)"range check fail in static_array");
				}
				return (*this)[index];
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::const_reference
			vector_allocator_unrelated<Tp>::at(size_type index) const
			{
				if (index >= this->_K_size) {
					kerbal::utility::throw_this_exception_helper<std::out_of_range>::throw_this_exception((const char*)"range check fail in static_array");
				}
				return (*this)[index];
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::reference
			vector_allocator_unrelated<Tp>::operator[](size_type index) KERBAL_NOEXCEPT
			{
				return this->_K_buffer[index];
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::const_reference
			vector_allocator_unrelated<Tp>::operator[](size_type index) const KERBAL_NOEXCEPT
			{
				return this->_K_buffer[index];
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::reference
			vector_allocator_unrelated<Tp>::front()
			{
				return *this->begin();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::const_reference
			vector_allocator_unrelated<Tp>::front() const
			{
				return *this->cbegin();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::reference
			vector_allocator_unrelated<Tp>::back()
			{
				return *this->rbegin();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::const_reference
			vector_allocator_unrelated<Tp>::back() const
			{
				return *this->crbegin();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR
			typename vector_allocator_unrelated<Tp>::const_pointer
			vector_allocator_unrelated<Tp>::data() const KERBAL_NOEXCEPT
			{
				return this->_K_buffer;
			}


		//===================
		// iterator

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename vector_allocator_unrelated<Tp>::iterator
			vector_allocator_unrelated<Tp>::begin() KERBAL_NOEXCEPT
			{
				return iterator(this->_K_buffer + 0);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename vector_allocator_unrelated<Tp>::iterator
			vector_allocator_unrelated<Tp>::end() KERBAL_NOEXCEPT
			{
				return iterator(this->_K_buffer + this->_K_size);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR
			typename vector_allocator_unrelated<Tp>::const_iterator
			vector_allocator_unrelated<Tp>::begin() const KERBAL_NOEXCEPT
			{
				return this->cbegin();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR
			typename vector_allocator_unrelated<Tp>::const_iterator
			vector_allocator_unrelated<Tp>::end() const KERBAL_NOEXCEPT
			{
				return this->cend();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR
			typename vector_allocator_unrelated<Tp>::const_iterator
			vector_allocator_unrelated<Tp>::cbegin() const KERBAL_NOEXCEPT
			{
				return const_iterator(this->_K_buffer + 0);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR
			typename vector_allocator_unrelated<Tp>::const_iterator
			vector_allocator_unrelated<Tp>::cend() const KERBAL_NOEXCEPT
			{
				return const_iterator(this->_K_buffer + this->_K_size);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename vector_allocator_unrelated<Tp>::reverse_iterator
			vector_allocator_unrelated<Tp>::rbegin() KERBAL_NOEXCEPT
			{
				return reverse_iterator(this->end());
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename vector_allocator_unrelated<Tp>::reverse_iterator
			vector_allocator_unrelated<Tp>::rend() KERBAL_NOEXCEPT
			{
				return reverse_iterator(this->begin());
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename vector_allocator_unrelated<Tp>::const_reverse_iterator
			vector_allocator_unrelated<Tp>::rbegin() const KERBAL_NOEXCEPT
			{
				return this->crbegin();
			}
			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename vector_allocator_unrelated<Tp>::const_reverse_iterator
			vector_allocator_unrelated<Tp>::rend() const KERBAL_NOEXCEPT
			{
				return this->crend();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename vector_allocator_unrelated<Tp>::const_reverse_iterator
			vector_allocator_unrelated<Tp>::crbegin() const KERBAL_NOEXCEPT
			{
				return const_reverse_iterator(this->end());
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename vector_allocator_unrelated<Tp>::const_reverse_iterator
			vector_allocator_unrelated<Tp>::crend() const KERBAL_NOEXCEPT
			{
				return const_reverse_iterator(this->cbegin());
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename vector_allocator_unrelated<Tp>::iterator
			vector_allocator_unrelated<Tp>::nth(size_type index)
			{
				return this->begin() + index;
			}

			template <typename Tp>
			KERBAL_CONSTEXPR
			typename vector_allocator_unrelated<Tp>::const_iterator
			vector_allocator_unrelated<Tp>::nth(size_type index) const
			{
				return this->cbegin() + index;
			}

			template <typename Tp>
			KERBAL_CONSTEXPR
			typename vector_allocator_unrelated<Tp>::const_iterator
			vector_allocator_unrelated<Tp>::cnth(size_type index) const
			{
				return this->cbegin() + index;
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			typename vector_allocator_unrelated<Tp>::size_type
			vector_allocator_unrelated<Tp>::index_of(iterator it)
			{
				return it - this->begin();
			}

			template <typename Tp>
			KERBAL_CONSTEXPR
			typename vector_allocator_unrelated<Tp>::size_type
			vector_allocator_unrelated<Tp>::index_of(const_iterator it) const
			{
				return it - this->cbegin();
			}


		//===================
		// capacity

			template <typename Tp>
			KERBAL_CONSTEXPR
			bool vector_allocator_unrelated<Tp>::empty() const KERBAL_NOEXCEPT
			{
				return this->_K_size == 0;
			}

			template <typename Tp>
			KERBAL_CONSTEXPR
			typename vector_allocator_unrelated<Tp>::size_type
			vector_allocator_unrelated<Tp>::size() const KERBAL_NOEXCEPT
			{
				return this->_K_size;
			}

			template <typename Tp>
			KERBAL_CONSTEXPR
			typename vector_allocator_unrelated<Tp>::size_type
			vector_allocator_unrelated<Tp>::capacity() const KERBAL_NOEXCEPT
			{
				return this->_K_capacity;
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::reserve_using_allocator(Allocator & alloc, size_type new_capacity)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				if (new_capacity <= this->_K_capacity) {
					return;
				}

				pointer new_buffer = allocator_traits::allocate(alloc, new_capacity);
#		if !__cpp_exceptions
				if (new_buffer == NULL) {
					kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
				}
#		endif

				if (this->_K_buffer != NULL) {
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
					allocator_traits::deallocate(alloc, this->_K_buffer, this->_K_capacity);
				}

				this->_K_buffer = new_buffer;
				this->_K_capacity = new_capacity;
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::shrink_to_fit_using_allocator(Allocator & alloc)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				if (this->_K_size == this->_K_capacity) { // also suitable for buffer == NULL (size == capacity == 0)
					return;
				}

				if (this->_K_size == 0) { // size == 0 but still have buffer
					allocator_traits::deallocate(alloc, this->_K_buffer, this->_K_capacity);
					this->_K_buffer = NULL;
					this->_K_capacity = 0;
					return;
				}

				size_type new_capacity = this->_K_size;
				pointer new_buffer = allocator_traits::allocate(alloc, new_capacity);
#		if !__cpp_exceptions
				if (new_buffer == NULL) {
					kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
				}
#		endif

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
				allocator_traits::deallocate(alloc, this->_K_buffer, this->_K_capacity);
				this->_K_buffer = new_buffer;
				this->_K_capacity = new_capacity;
			}



		//===================
		// insert

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::emplace_realloc_aux(Allocator & alloc, size_type insert_pos_index, pointer new_buffer, size_type new_capacity)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				if (this->_K_buffer != NULL) {
					pointer insert_pos = this->_K_buffer + insert_pos_index;
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
					allocator_traits::deallocate(alloc, this->_K_buffer, this->_K_capacity);
				}

				this->_K_buffer = new_buffer;
				this->_K_capacity = new_capacity;
				++this->_K_size;
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
			typename vector_allocator_unrelated<Tp>::iterator
			vector_allocator_unrelated<Tp>::emplace_using_allocator(Allocator & alloc, const_iterator pos, Args&& ... args)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				size_type insert_pos_index = this->index_of(pos);
				size_type ori_size = this->_K_size;
				size_type new_size = ori_size + 1;
				if (new_size <= this->_K_capacity) {
					pointer insert_pos = pos.cast_to_mutable().current;
					if (pos == this->cend()) {
						// A A A O O O
						//       ^
						// construct at the end
						kerbal::memory::construct_at_using_allocator(alloc, this->end().current, kerbal::utility::forward<Args>(args)...);
						this->_K_size = new_size;
					} else {
						vector_emplace_helper<Tp, Allocator> helper(alloc, kerbal::utility::forward<Args>(args)...);

						// construct at the end
						kerbal::memory::construct_at_using_allocator(alloc, this->end().current, kerbal::compatibility::to_xvalue(this->back()));
						this->_K_size = new_size;
						// A A A X Y Z Z O O
						//             ^
						kerbal::algorithm::move_backward(insert_pos, this->end().current - 2, this->end().current - 1);
						// A A A X X Y Z O O
						//           ^
						kerbal::operators::generic_assign(*insert_pos, kerbal::compatibility::to_xvalue(helper.storage.raw_value()));
						// *insert_pos = kerbal::compatibility::to_xvalue(helper.storage.raw_value());
					}
				} else { // new_size > this->_K_capacity
					size_type new_capacity = this->_K_capacity == 0 ? 1 : 2 * this->_K_capacity;
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
					size_type new_capacity = this->_K_capacity == 0 ? 1 : 2 * this->_K_capacity; \
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
					size_type new_capacity = this->_K_capacity == 0 ? 1 : 2 * this->_K_capacity; \
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
			typename vector_allocator_unrelated<Tp>::iterator \
			vector_allocator_unrelated<Tp>::emplace_using_allocator(Allocator & alloc, const_iterator pos KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits; \
 \
				size_type insert_pos_index = this->index_of(pos); \
				size_type ori_size = this->_K_size; \
				size_type new_size = ori_size + 1; \
				if (new_size <= this->_K_capacity) { \
					pointer insert_pos = pos.cast_to_mutable().current; \
					if (pos == this->cend()) { \
						kerbal::memory::construct_at_using_allocator(alloc, this->end().current KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
						this->_K_size = new_size; \
					} else { \
						vector_emplace_helper<Tp, Allocator> helper(alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
 \
						kerbal::memory::construct_at_using_allocator(alloc, this->end().current, kerbal::compatibility::to_xvalue(this->back())); \
						this->_K_size = new_size; \
						kerbal::algorithm::move_backward(insert_pos, this->end().current - 2, this->end().current - 1); \
						kerbal::operators::generic_assign(*insert_pos, kerbal::compatibility::to_xvalue(helper.storage.raw_value())); \
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
			typename vector_allocator_unrelated<Tp>::iterator
			vector_allocator_unrelated<Tp>::insert_using_allocator(Allocator & alloc, const_iterator pos, const_reference val)
			{
				return this->emplace_using_allocator(alloc, pos, val);
			}

#		if __cplusplus >= 201103L

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::iterator
			vector_allocator_unrelated<Tp>::insert_using_allocator(Allocator & alloc, const_iterator pos, rvalue_reference val)
			{
				return this->emplace_using_allocator(alloc, pos, kerbal::compatibility::move(val));
			}

#		endif

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::insert_realloc_aux(Allocator & alloc, size_type insert_pos_index, size_type n, pointer new_buffer, size_type new_capacity, size_type new_size)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				if (this->_K_buffer != NULL) {
					pointer insert_pos = this->_K_buffer + insert_pos_index;
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
					allocator_traits::deallocate(alloc, this->_K_buffer, this->_K_capacity);
				}

				this->_K_buffer = new_buffer;
				this->_K_capacity = new_capacity;
				this->_K_size = new_size;
			}


			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::iterator
			vector_allocator_unrelated<Tp>::insert_using_allocator(Allocator & alloc, const_iterator pos, size_type n, const_reference val)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				size_type insert_pos_index = this->index_of(pos);
				size_type ori_size = this->_K_size;
				size_type new_size = ori_size + n;
				if (new_size <= this->_K_capacity) {
					pointer insert_pos = pos.cast_to_mutable().current;
					if (n == 0) {
						// pass
					} else if (pos == this->cend()) {
						// A A A O O O
						//       ^
						// construct at the end
						kerbal::memory::uninitialized_fill_using_allocator(alloc, this->end().current, this->nth(new_size).current, val);
						this->_K_size = new_size;
					} else if (insert_pos_index + n <= ori_size) {
						// A A A 1 2 3 4 5 6
						// A A A X X 1 2 3 4 5 6

						// construct at the end
						// A A A 1 2 3 4 5 6
						// A A A 1 2 3 4 5 6 5 6
						kerbal::memory::uninitialized_copy_using_allocator(alloc, this->cend().current - n, this->cend().current, this->end().current);
						this->_K_size = new_size;

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
						this->_K_size = new_size;
						// A A A 1 2 3
						// A A A X X X X X 1 2 3
						kerbal::algorithm::fill(insert_pos, this->nth(ori_size).current, val);
					}
				} else { // new_size > this->_K_capacity
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
			typename vector_allocator_unrelated<Tp>::iterator
			vector_allocator_unrelated<Tp>::_K_range_insert_using_allocator_impl(Allocator & alloc, const_iterator pos, InputIterator first, InputIterator last, std::input_iterator_tag)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				vector_allocator_unrelated vt(alloc, first, last);

				struct destroy_helper
				{
						Allocator & alloc;
						vector_allocator_unrelated & vt;

						KERBAL_CONSTEXPR20
						destroy_helper(Allocator & alloc, vector_allocator_unrelated & vt) KERBAL_NOEXCEPT :
								alloc(alloc), vt(vt)
						{
						}

						KERBAL_CONSTEXPR20
						~destroy_helper() KERBAL_NOEXCEPT
						{
							this->vt.destroy_using_allocator(alloc);
						}

				} auto_destroy_helper(alloc, vt);

				size_type insert_pos_index = this->index_of(pos);
				size_type n = vt.size();
				size_type ori_size = this->_K_size;
				size_type new_size = ori_size + n;
				if (new_size <= this->_K_capacity) {
					pointer insert_pos = this->_K_buffer + insert_pos_index;
					if (n == 0) {
						// pass
					} else if (pos == this->cend()) {
						// A A A O O O
						//       ^
						// construct at the end
						ui_move_if_noexcept_ow_copy_phase1(alloc, vt.begin().current, vt.end().current, this->end().current);
						this->_K_size = new_size;
						ui_move_if_noexcept_ow_copy_phase2(alloc, vt.begin().current, vt.end().current);
						vt._K_size = 0;
					} else if (insert_pos_index + n <= ori_size) {
						// A A A 1 2 3 4 5 6
						// A A A X X 1 2 3 4 5 6

						// construct at the end
						// A A A 1 2 3 4 5 6
						// A A A 1 2 3 4 5 6 5 6
						kerbal::memory::uninitialized_copy_using_allocator(alloc, this->cend().current - n, this->cend().current, this->end().current);
						this->_K_size = new_size;

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
							this->_K_size = new_size;
							ui_move_if_noexcept_ow_copy_phase2(alloc, copy_n_r.first(), vt.end().current);
							vt._K_size = ori_size - insert_pos_index;
#		if __cpp_exceptions
						} catch (...) {
							kerbal::memory::reverse_destroy_using_allocator(alloc, insert_pos + n, this->nth(new_size).current);
							throw;
						}
#		endif
					}
				} else { // new_size > this->_K_capacity
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
					vt._K_size = 0;

					this->insert_realloc_aux(alloc, insert_pos_index, n, new_buffer, new_capacity, new_size);
				}
				return this->nth(insert_pos_index);
			}

			template <typename Tp>
			template <typename Allocator, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::iterator
			vector_allocator_unrelated<Tp>::_K_range_insert_using_allocator_impl(Allocator & alloc, const_iterator pos, ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				size_type insert_pos_index = this->index_of(pos);
				size_type n = static_cast<size_type>(kerbal::iterator::distance(first, last));
				size_type ori_size = this->_K_size;
				size_type new_size = ori_size + n;
				if (new_size <= this->_K_capacity) {
					pointer insert_pos = this->_K_buffer + insert_pos_index;
					if (n == 0) {
						// pass
					} else if (pos == this->cend()) {
						// A A A O O O
						//       ^
						// construct at the end
						kerbal::memory::uninitialized_copy_using_allocator(alloc, first, last, this->end().current);
						this->_K_size = new_size;
					} else if (insert_pos_index + n <= ori_size) {
						// A A A 1 2 3 4 5 6
						// A A A X X 1 2 3 4 5 6

						// construct at the end
						// A A A 1 2 3 4 5 6
						// A A A 1 2 3 4 5 6 5 6
						kerbal::memory::uninitialized_copy_using_allocator(alloc, this->cend().current - n, this->cend().current, this->end().current);
						this->_K_size = new_size;

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
						this->_K_size = new_size;
					}
				} else { // new_size > this->_K_capacity
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
					typename vector_allocator_unrelated<Tp>::iterator
			>::type
			vector_allocator_unrelated<Tp>::insert_using_allocator(Allocator & alloc, const_iterator pos, InputIterator first, InputIterator last)
			{
				return this->_K_range_insert_using_allocator_impl(alloc, pos, first, last, kerbal::iterator::iterator_category(first));
			}


			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::emplace_back_realloc_aux(Allocator & alloc, pointer new_buffer, size_type new_capacity)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				if (this->_K_buffer != NULL) {
#		if __cpp_exceptions
					try {
#		endif
						ui_move_if_noexcept_ow_copy_phase1(alloc, this->begin().current, this->end().current, new_buffer);
#		if __cpp_exceptions
					} catch (...) {
						pointer emplace_pos = new_buffer + this->_K_size;
						kerbal::memory::destroy_at_using_allocator(alloc, emplace_pos);
						allocator_traits::deallocate(alloc, new_buffer, new_capacity);
						throw;
					}
#		endif
					ui_move_if_noexcept_ow_copy_phase2(alloc, this->begin().current, this->end().current);
					allocator_traits::deallocate(alloc, this->_K_buffer, this->_K_capacity);
				}
				this->_K_buffer = new_buffer;
				this->_K_capacity = new_capacity;
				++this->_K_size;
			}

#		if __cplusplus >= 201103L

			template <typename Tp>
			template <typename Allocator, typename ... Args>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::reference
			vector_allocator_unrelated<Tp>::emplace_back_using_allocator(Allocator & alloc, Args&& ... args)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				size_type ori_size = this->_K_size;
				size_type new_size = ori_size + 1;
				if (new_size <= this->_K_capacity) {
					kerbal::memory::construct_at_using_allocator(alloc, this->end().current, kerbal::utility::forward<Args>(args)...);
					++this->_K_size;
				} else {
					size_type new_capacity = this->_K_capacity == 0 ? 1 : this->_K_capacity * 2;
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

					this->emplace_back_realloc_aux(alloc, new_buffer, new_capacity);
				}
				return this->_K_buffer[this->_K_size];
			}

#		else

#		define EMPTY
#		define LEFT_JOIN_COMMA(exp) , exp
#		define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#		define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#		define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#	if __cpp_exceptions
#		define FBODY(i) \
			template <typename Tp> \
			template <typename Allocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			typename vector_allocator_unrelated<Tp>::reference \
			vector_allocator_unrelated<Tp>::emplace_back_using_allocator(Allocator & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits; \
 \
				size_type ori_size = this->_K_size; \
				size_type new_size = ori_size + 1; \
				if (new_size <= this->_K_capacity) { \
					kerbal::memory::construct_at_using_allocator(alloc, this->end().current KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
					++this->_K_size; \
				} else { \
					size_type new_capacity = this->_K_capacity == 0 ? 1 : this->_K_capacity * 2; \
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
					this->emplace_back_realloc_aux(alloc, new_buffer, new_capacity); \
				} \
				return this->_K_buffer[this->_K_size]; \
			}
#	else // __cpp_exceptions
#		define FBODY(i) \
			template <typename Tp> \
			template <typename Allocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
			typename vector_allocator_unrelated<Tp>::reference \
			vector_allocator_unrelated<Tp>::emplace_back_using_allocator(Allocator & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
			{ \
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits; \
 \
				size_type ori_size = this->_K_size; \
				size_type new_size = ori_size + 1; \
				if (new_size <= this->_K_capacity) { \
					kerbal::memory::construct_at_using_allocator(alloc, this->end().current KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
					++this->_K_size; \
				} else { \
					size_type new_capacity = this->_K_capacity == 0 ? 1 : this->_K_capacity * 2; \
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
					this->emplace_back_realloc_aux(alloc, new_buffer, new_capacity); \
				} \
				return this->_K_buffer[this->_K_size]; \
			}
#	endif // __cpp_exceptions

			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
			KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#		undef EMPTY
#		undef LEFT_JOIN_COMMA
#		undef TARGS_DECL
#		undef ARGS_DECL
#		undef ARGS_USE
#		undef FBODY

#		endif

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::push_back_using_allocator(Allocator & alloc, const_reference src)
			{
				this->emplace_back_using_allocator(alloc, src);
			}

#		if __cplusplus >= 201103L

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::push_back_using_allocator(Allocator & alloc, rvalue_reference src)
			{
				this->emplace_back_using_allocator(alloc, kerbal::compatibility::move(src));
			}

#		endif



		//===================
		// erase

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::iterator
			vector_allocator_unrelated<Tp>::erase_using_allocator(Allocator & alloc, const_iterator pos)
			{
				iterator pos_mut(pos.cast_to_mutable());

				if (pos == this->cend()) {
					return pos_mut;
				}

				// pre-condition: pos != cend()
				kerbal::algorithm::move(pos_mut.current + 1, this->end().current, pos_mut.current);
				this->pop_back_using_allocator(alloc);
				return pos_mut;
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			typename vector_allocator_unrelated<Tp>::iterator
			vector_allocator_unrelated<Tp>::erase_using_allocator(Allocator & alloc, const_iterator first, const_iterator last)
			{
				iterator first_mut(first.cast_to_mutable());
				if (first == last) {
					return first_mut;
				}
				iterator last_mut(last.cast_to_mutable());

				pointer new_end(kerbal::algorithm::move(last_mut.current, this->end().current, first_mut.current));
				kerbal::memory::reverse_destroy_using_allocator(alloc, new_end, this->end().current);
				size_type new_size = new_end - this->_K_buffer;
				this->_K_size = new_size;
				return first_mut;
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::pop_back_using_allocator(Allocator & alloc) KERBAL_NOEXCEPT
			{
				kerbal::memory::destroy_on_using_allocator(alloc, this->back());
				--this->_K_size;
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::clear_using_allocator(Allocator & alloc) KERBAL_NOEXCEPT
			{
				kerbal::memory::reverse_destroy_using_allocator(alloc, this->begin().current, this->end().current);
				this->_K_size = 0;
			}


		//===================
		// operation

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::resize_realloc_aux(Allocator & alloc, pointer new_buffer, size_type new_capacity, size_type new_size)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				if (this->_K_buffer != NULL) {
#		if __cpp_exceptions
					try {
#		endif
						ui_move_if_noexcept_ow_copy_phase1(alloc, this->begin().current, this->end().current, new_buffer);
#		if __cpp_exceptions
					} catch (...) {
						size_type ori_size = this->_K_size;
						kerbal::memory::reverse_destroy_using_allocator(alloc, new_buffer + ori_size, new_buffer + new_size);
						allocator_traits::deallocate(alloc, new_buffer, new_capacity);
						throw;
					}
#		endif
					ui_move_if_noexcept_ow_copy_phase2(alloc, this->begin().current, this->end().current);
					allocator_traits::deallocate(alloc, this->_K_buffer, this->_K_capacity);
				}
				this->_K_buffer = new_buffer;
				this->_K_capacity = new_capacity;
				this->_K_size = new_size;
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::resize_using_allocator(Allocator & alloc, size_type new_size)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				size_type ori_size = this->_K_size;
				if (new_size <= ori_size) { // also suitable for new_size == 0
					/*
					 * a a a a a a x x
					 * a a a x x x x x
					 */
					kerbal::memory::reverse_destroy_using_allocator(alloc, this->nth(new_size).current, this->nth(ori_size).current);
					this->_K_size = new_size;
				} else { // new_size > ori_size
					/*
					 * a a a x x x x x
					 * a a a b b b x x
					 */
					if (new_size <= this->_K_capacity) {
						kerbal::memory::uninitialized_value_construct_using_allocator(alloc, this->nth(ori_size).current, this->nth(new_size).current);
						this->_K_size = new_size;
					} else {
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

						this->resize_realloc_aux(alloc, new_buffer, new_capacity, new_size);
					}
				}
			}

			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::resize_using_allocator(Allocator & alloc, size_type new_size, const_reference value)
			{
				typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

				size_type ori_size = this->_K_size;
				if (new_size <= ori_size) { // also suitable for new_size == 0
					/*
					 * a a a a a a x x
					 * a a a x x x x x
					 */
					kerbal::memory::reverse_destroy_using_allocator(alloc, this->nth(new_size).current, this->nth(ori_size).current);
					this->_K_size = new_size;
				} else { // new_size > ori_size
					/*
					 * a a a x x x x x
					 * a a a b b b x x
					 */
					if (new_size <= this->_K_capacity) {
						kerbal::memory::uninitialized_fill_using_allocator(alloc, this->nth(ori_size).current, this->nth(new_size).current, value);
						this->_K_size = new_size;
					} else {
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

						this->resize_realloc_aux(alloc, new_buffer, new_capacity, new_size);
					}
				}
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			void vector_allocator_unrelated<Tp>::_K_swap_type_unrelated(vector_allocator_unrelated & lhs, vector_allocator_unrelated & rhs) KERBAL_NOEXCEPT
			{
				kerbal::algorithm::swap(lhs._K_buffer, rhs._K_buffer);
				kerbal::algorithm::swap(lhs._K_size, rhs._K_size);
				kerbal::algorithm::swap(lhs._K_capacity, rhs._K_capacity);
			}



			template <typename Tp>
			template <typename Allocator>
			KERBAL_CONSTEXPR20
			void vector_allocator_unrelated<Tp>::ui_move_if_noexcept_ow_copy_phase1(Allocator & alloc, pointer first, pointer last, pointer to)
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
			void vector_allocator_unrelated<Tp>::ui_move_if_noexcept_ow_copy_phase2(Allocator & alloc, pointer first, pointer last) KERBAL_NOEXCEPT
			{
				kerbal::memory::ui_move_if_noexcept_ow_copy<Allocator, pointer, pointer>::phase2(alloc, first, last);
			}

		} // namespace detail

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_DETAIL_VECTOR_BASE_VECTOR_BASE_IMPL_HPP
