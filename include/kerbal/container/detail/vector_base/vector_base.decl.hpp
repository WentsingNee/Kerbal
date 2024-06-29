/**
 * @file       vector_base.decl.hpp
 * @brief
 * @date       2020-08-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_VECTOR_BASE_VECTOR_BASE_DECL_HPP
#define KERBAL_CONTAINER_DETAIL_VECTOR_BASE_VECTOR_BASE_DECL_HPP

#include <kerbal/container/vector/vector.fwd.hpp>

//#include <kerbal/assign/assign_list.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/iterator/reverse_iterator.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/memory/uninitialized_using_allocator.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/remove_all_extents.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#include <limits>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif

#include <kerbal/container/detail/vector_base/vector_iterator.hpp>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename T>
			class vector_type_only
			{
				public:
					typedef T							value_type;
					typedef const value_type			const_type;
					typedef value_type &				reference;
					typedef const value_type &			const_reference;
					typedef value_type *				pointer;
					typedef const value_type *			const_pointer;

#			if __cplusplus >= 201103L
					typedef value_type &&				rvalue_reference;
					typedef const value_type &&			const_rvalue_reference;
#			endif

					typedef std::size_t					size_type;
					typedef std::ptrdiff_t				difference_type;

					typedef typename kerbal::type_traits::remove_all_extents<value_type>::type remove_all_extents_t;

					typedef kerbal::container::detail::vec_iter<value_type>		iterator;
					typedef kerbal::container::detail::vec_kiter<value_type>	const_iterator;
					typedef kerbal::iterator::reverse_iterator<iterator>		reverse_iterator;
					typedef kerbal::iterator::reverse_iterator<const_iterator>	const_reverse_iterator;

				protected:
					pointer k_buffer;
					size_type k_capacity;
					size_type k_size;

				public:

				//===================
				// construct/copy/destroy

#			if __cplusplus >= 201103L

					struct is_nothrow_default_constructible :
						kerbal::type_traits::true_type
					{
					};

#			endif

					KERBAL_CONSTEXPR
					vector_type_only() KERBAL_NOEXCEPT;

#			if __cplusplus >= 201103L

					struct is_nothrow_move_constructible :
						kerbal::type_traits::true_type
					{
					};

					KERBAL_CONSTEXPR14
					vector_type_only(vector_type_only && src) KERBAL_NOEXCEPT;

				private:

					// move construct using allocator, allocator is equal
					KERBAL_CONSTEXPR14
					void k_move_cnstrct_ua_ae(vector_type_only && src) KERBAL_NOEXCEPT;

					// move construct using allocator, allocator is not equal
					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_move_cnstrct_ua_ane(
						Allocator & this_alloc,
						vector_type_only && src
					);

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_move_cnstrct_ua_helper(
						Allocator & this_alloc,
						Allocator && src_alloc, vector_type_only && src,
						kerbal::type_traits::false_type /*is_always_equal*/
					);

					template <typename Allocator>
					KERBAL_CONSTEXPR14
					void k_move_cnstrct_ua_helper(
						Allocator & this_alloc,
						Allocator && src_alloc, vector_type_only && src,
						kerbal::type_traits::true_type /*is_always_equal*/
					) KERBAL_NOEXCEPT;

				public:

					template <typename Allocator>
					struct is_nothrow_move_constructible_using_allocator :
						kerbal::memory::allocator_traits<Allocator>::is_always_equal
					{
					};

					template <typename Allocator>
					KERBAL_CONSTEXPR14
					vector_type_only(
						Allocator & this_alloc,
						Allocator && src_alloc, vector_type_only && src
					)
						KERBAL_CONDITIONAL_NOEXCEPT(
							is_nothrow_move_constructible_using_allocator<Allocator>::value
						)
					;

#			endif

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					vector_type_only(
						Allocator & alloc,
						size_type count
					);

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					vector_type_only(
						Allocator & alloc,
						size_type count, const_reference value
					);

				private:

					template <typename Allocator, typename InputIterator>
					KERBAL_CONSTEXPR20
					void k_range_copy_cnstrct_impl(
						Allocator & alloc,
						InputIterator first, InputIterator last,
						std::input_iterator_tag
					);

					template <typename Allocator, typename ForwardIterator>
					KERBAL_CONSTEXPR20
					void k_range_copy_cnstrct_impl(
						Allocator & alloc,
						ForwardIterator first, ForwardIterator last,
						std::forward_iterator_tag
					);

				public:

					template <typename Allocator, typename InputIterator>
					KERBAL_CONSTEXPR20
					vector_type_only(
						Allocator & alloc,
						InputIterator first, InputIterator last
					);

#			if __cplusplus >= 201103L

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					vector_type_only(
						NodeAllocator & alloc,
						std::initializer_list<value_type> ilist
					);

#			else

					template <typename NodeAllocator>
					vector_type_only(
						NodeAllocator & alloc,
						const kerbal::assign::assign_list<void> & ilist
					);

					template <typename NodeAllocator, typename U>
					vector_type_only(
						NodeAllocator & alloc,
						const kerbal::assign::assign_list<U> & ilist
					);

#			endif

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_destroy_using_allocator(Allocator & alloc) KERBAL_NOEXCEPT;


				//===================
				// assign

				private:

					typedef kerbal::type_traits::integral_constant<int, 0> CPYASS_VER_NOT_PROPAGATE;
					typedef kerbal::type_traits::integral_constant<int, 1> CPYASS_VER_PROPAGATE;
					typedef kerbal::type_traits::integral_constant<int, 2> CPYASS_VER_ALWAYS_EQUAL;

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_cpy_ass_ua_impl(
						Allocator & alloc,
						const Allocator & src_alloc, const vector_type_only & src,
						CPYASS_VER_NOT_PROPAGATE
					);

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_cpy_ass_ua_impl(
						Allocator & alloc,
						const Allocator & src_alloc, const vector_type_only & src,
						CPYASS_VER_PROPAGATE
					);

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_cpy_ass_ua_impl(
						Allocator & alloc,
						const Allocator & src_alloc, const vector_type_only & src,
						CPYASS_VER_ALWAYS_EQUAL
					);

				public:

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_assign_using_allocator(
						Allocator & alloc,
						const Allocator & src_alloc, const vector_type_only & src
					);

#			if __cplusplus >= 201103L

				private:

					// move assign using allocator, allocator is equal
					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_mov_ass_ua_ae(Allocator & alloc, vector_type_only && src) KERBAL_NOEXCEPT;

					// move assign using allocator, allocator is not equal
					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_mov_ass_ua_ane(
						Allocator & alloc,
						Allocator && src_alloc, vector_type_only && src
					);

					typedef kerbal::type_traits::integral_constant<int, 0> MOVASS_VER_NOT_PROPAGATE;
					typedef kerbal::type_traits::integral_constant<int, 1> MOVASS_VER_PROPAGATE;
					typedef kerbal::type_traits::integral_constant<int, 2> MOVASS_VER_ALWAYS_EQUAL;

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_mov_ass_ua_impl(
						Allocator & alloc,
						Allocator && src_alloc, vector_type_only && src,
						MOVASS_VER_NOT_PROPAGATE
					);

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_mov_ass_ua_impl(
						Allocator & alloc,
						Allocator && src_alloc, vector_type_only && src,
						MOVASS_VER_PROPAGATE
					);

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_mov_ass_ua_impl(
						Allocator & alloc,
						Allocator && /*src_alloc*/, vector_type_only && src,
						MOVASS_VER_ALWAYS_EQUAL
					) KERBAL_NOEXCEPT;

				public:

					template <typename Allocator>
					struct is_nothrow_move_assign_using_allocator :
						kerbal::memory::allocator_traits<Allocator>::is_always_equal
					{
					};

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_assign_using_allocator(
						Allocator & alloc,
						Allocator && src_alloc, vector_type_only && src
					)
						KERBAL_CONDITIONAL_NOEXCEPT(
							is_nothrow_move_assign_using_allocator<Allocator>::value
						)
					;

#			endif

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_assign_using_allocator(
						Allocator & alloc,
						size_type new_size, const_reference value
					);

				private:

					template <typename Allocator, typename InputIterator>
					KERBAL_CONSTEXPR20
					void k_range_assign_using_allocator_impl(
						Allocator & alloc,
						InputIterator first, InputIterator last,
						std::input_iterator_tag
					);

					template <typename Allocator, typename ForwardIterator>
					KERBAL_CONSTEXPR20
					void k_range_assign_using_allocator_impl(
						Allocator & alloc,
						ForwardIterator first, ForwardIterator last,
						std::forward_iterator_tag
					);

				public:

					template <typename Allocator, typename InputIterator>
					KERBAL_CONSTEXPR20
					typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
					>::type
					k_assign_using_allocator(
						Allocator & alloc,
						InputIterator first, InputIterator last
					);

#			if __cplusplus >= 201103L

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					void k_assign_using_allocator(
						NodeAllocator & alloc,
						std::initializer_list<value_type> ilist
					);

#			else

					template <typename NodeAllocator>
					void k_assign_using_allocator(
						NodeAllocator & alloc,
						const kerbal::assign::assign_list<void> & ilist
					);

					template <typename NodeAllocator, typename U>
					void k_assign_using_allocator(
						NodeAllocator & alloc,
						const kerbal::assign::assign_list<U> & ilist
					);

#			endif


				//===================
				// element access

					KERBAL_CONSTEXPR20
					reference at(size_type index);

					KERBAL_CONSTEXPR20
					const_reference at(size_type index) const;

					KERBAL_CONSTEXPR20
					reference operator[](size_type index) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_reference operator[](size_type index) const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					reference front();

					KERBAL_CONSTEXPR20
					const_reference front() const;

					KERBAL_CONSTEXPR20
					reference back();

					KERBAL_CONSTEXPR20
					const_reference back() const;

					KERBAL_CONSTEXPR
					const_pointer data() const KERBAL_NOEXCEPT;

				//===================
				// iterator

					KERBAL_CONSTEXPR14
					iterator begin() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR
					const_iterator begin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR
					const_iterator cbegin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					iterator end() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR
					const_iterator end() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR
					const_iterator cend() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					reverse_iterator rbegin() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					const_reverse_iterator rbegin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					const_reverse_iterator crbegin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					reverse_iterator rend() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					const_reverse_iterator rend() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					const_reverse_iterator crend() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					iterator nth(size_type index);

					KERBAL_CONSTEXPR
					const_iterator nth(size_type index) const;

					KERBAL_CONSTEXPR
					const_iterator cnth(size_type index) const;

					KERBAL_CONSTEXPR14
					size_type index_of(iterator it);

					KERBAL_CONSTEXPR
					size_type index_of(const_iterator it) const;

				//===================
				// capacity

					KERBAL_CONSTEXPR
					bool empty() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR
					size_type size() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR
					size_type capacity() const KERBAL_NOEXCEPT;

				private:
					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_capacity_adjusted_realloc_aux(
						Allocator & alloc, pointer new_buffer, size_type new_capacity
					);

				private:
					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_reserve_expand_buffer(
						kerbal::type_traits::false_type,
						Allocator & alloc, size_type new_capacity
					);

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_reserve_expand_buffer(
						kerbal::type_traits::true_type,
						Allocator & alloc, size_type new_capacity
					);

				public:
					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_reserve_using_allocator(Allocator & alloc, size_type new_capacity);

				private:
					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_shrink_buffer(
						kerbal::type_traits::false_type /*has_reallocate*/,
						Allocator & alloc
					);

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_shrink_buffer(
						kerbal::type_traits::true_type /*has_reallocate*/,
						Allocator & alloc
					);

				public:
					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_shrink_to_fit_using_allocator(Allocator & alloc);

				//===================
				// insert

				private:
					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void emplace_realloc_aux(
						Allocator & alloc, size_type insert_pos_index, pointer new_buffer, size_type new_capacity
					);

				public:

#			if __cplusplus >= 201103L

					template <typename Allocator, typename ... Args>
					KERBAL_CONSTEXPR20
					iterator
					k_emplace_using_allocator(
						Allocator & alloc,
						const_iterator pos,
						Args && ... args
					);

#			else

#				define EMPTY
#				define LEFT_JOIN_COMMA(exp) , exp
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					template < \
						typename Allocator \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i) \
					> \
					iterator \
					k_emplace_using_allocator( \
						Allocator & alloc, \
						const_iterator pos \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
					); \

					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#				undef EMPTY
#				undef LEFT_JOIN_COMMA
#				undef TARGS_DECL
#				undef ARGS_DECL
#				undef FBODY

#			endif

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					iterator
					k_insert_using_allocator(
						Allocator & alloc,
						const_iterator pos,
						const_reference val
					);

#			if __cplusplus >= 201103L

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					iterator
					k_insert_using_allocator(
						Allocator & alloc,
						const_iterator pos,
						rvalue_reference val
					);

#			endif

				private:
					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void insert_realloc_aux(
						Allocator & alloc, size_type insert_pos_index, size_type n,
						pointer new_buffer, size_type new_capacity, size_type new_size
					);

				public:

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					iterator
					k_insert_using_allocator(
						Allocator & alloc,
						const_iterator pos,
						size_type n, const_reference val
					);

				private:

					template <typename Allocator, typename InputIterator>
					KERBAL_CONSTEXPR20
					iterator
					k_range_insert_using_allocator_impl(
						Allocator & alloc,
						const_iterator pos,
						InputIterator first, InputIterator last,
						std::input_iterator_tag
					);

					template <typename Allocator, typename ForwardIterator>
					KERBAL_CONSTEXPR20
					iterator
					k_range_insert_using_allocator_impl(
						Allocator & alloc,
						const_iterator pos,
						ForwardIterator first, ForwardIterator last,
						std::forward_iterator_tag
					);

				public:
					template <typename Allocator, typename InputIterator>
					KERBAL_CONSTEXPR20
					typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
						iterator
					>::type
					k_insert_using_allocator(
						Allocator & alloc,
						const_iterator pos,
						InputIterator first, InputIterator last
					);

#			if __cplusplus >= 201103L

					template <typename NodeAllocator>
					KERBAL_CONSTEXPR20
					iterator
					k_insert_using_allocator(
						NodeAllocator & alloc,
						const_iterator pos,
						std::initializer_list<value_type> ilist
					);

#			else

					template <typename NodeAllocator>
					iterator
					k_insert_using_allocator(
						NodeAllocator & alloc,
						const_iterator pos,
						const kerbal::assign::assign_list<void> & ilist
					);

					template <typename NodeAllocator, typename U>
					iterator
					k_insert_using_allocator(
						NodeAllocator & alloc,
						const_iterator pos,
						const kerbal::assign::assign_list<U> & ilist
					);

#			endif

				private:
					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_emplace_back_transfer_ele(
						Allocator & alloc,
						pointer new_buffer, size_type new_capacity
					);

#			if __cplusplus >= 201103L

				private:
					template <typename Allocator, typename ... Args>
					KERBAL_CONSTEXPR20
					void k_emplace_back_ua_expand_buffer(
						kerbal::type_traits::false_type,
						Allocator & alloc, Args && ... args
					);

					template <typename Allocator, typename ... Args>
					KERBAL_CONSTEXPR20
					void k_emplace_back_ua_expand_buffer(
						kerbal::type_traits::true_type,
						Allocator & alloc, Args && ... args
					);

				public:
					template <typename Allocator, typename ... Args>
					KERBAL_CONSTEXPR20
					reference k_emplace_back_using_allocator(Allocator & alloc, Args && ... args);

#			else

#				define EMPTY
#				define LEFT_JOIN_COMMA(exp) , exp
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
				private: \
					template < \
						typename Allocator \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i) \
					> \
					void \
					k_emplace_back_ua_expand_buffer( \
						kerbal::type_traits::false_type, \
						Allocator & alloc \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
					); \
 \
					template <typename Allocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
					void k_emplace_back_ua_expand_buffer( \
						kerbal::type_traits::true_type, \
						Allocator & alloc \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
					); \
 \
				public: \
					template < \
						typename Allocator \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i) \
					> \
					reference \
					k_emplace_back_using_allocator( \
						Allocator & alloc \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i) \
					); \

					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#				undef EMPTY
#				undef LEFT_JOIN_COMMA
#				undef TARGS_DECL
#				undef ARGS_DECL
#				undef FBODY

#			endif

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_push_back_using_allocator(
						Allocator & alloc,
						const_reference src
					);

#			if __cplusplus >= 201103L

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_push_back_using_allocator(
						Allocator & alloc,
						rvalue_reference src
					);

#			endif

				//===================
				// erase

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					iterator
					k_erase_using_allocator(
						Allocator & alloc,
						const_iterator pos
					);

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					iterator
					k_erase_using_allocator(
						Allocator & alloc,
						const_iterator first, const_iterator last
					);

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_pop_back_using_allocator(Allocator & alloc) KERBAL_NOEXCEPT;

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_clear_using_allocator(Allocator & alloc) KERBAL_NOEXCEPT;

				//===================
				// operation

				private:
					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_resize_transfer_ele(
						Allocator & alloc,
						pointer new_buffer, size_type new_capacity, size_type new_size
					);

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_resize_expand_buffer(
						kerbal::type_traits::false_type,
						Allocator & alloc,
						size_type new_size
					);

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_resize_expand_buffer(
						kerbal::type_traits::true_type,
						Allocator & alloc,
						size_type new_size
					);

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_resize_expand_buffer(
						kerbal::type_traits::false_type,
						Allocator & alloc,
						size_type new_size, const_reference value
					);

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_resize_expand_buffer(
						kerbal::type_traits::true_type,
						Allocator & alloc,
						size_type new_size, const_reference value
					);

				public:
					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_resize_using_allocator(
						Allocator & alloc,
						size_type new_size
					);

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void k_resize_using_allocator(
						Allocator & alloc,
						size_type new_size, const_reference value
					);

					KERBAL_CONSTEXPR14
					static
					void k_swap_type_unrelated(
						vector_type_only & lhs,
						vector_type_only & rhs
					) KERBAL_NOEXCEPT;


				private:

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					static
					void ui_move_if_noexcept_ow_copy_phase1(
						Allocator & alloc,
						pointer first, pointer last, pointer to
					)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(
								kerbal::memory::ui_move_if_noexcept_ow_copy<Allocator, pointer, pointer>::phase1(alloc, first, last, to)
							)
						)
					;

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					static
					void ui_move_if_noexcept_ow_copy_phase2(
						Allocator & alloc,
						pointer first, pointer last
					) KERBAL_NOEXCEPT;

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_VECTOR_BASE_VECTOR_BASE_DECL_HPP
