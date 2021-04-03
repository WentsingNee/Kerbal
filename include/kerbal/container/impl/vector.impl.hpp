/**
 * @file       vector.impl.hpp
 * @brief
 * @date       2020-6-12
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_IMPL_VECTOR_IMPL_HPP
#define KERBAL_CONTAINER_IMPL_VECTOR_IMPL_HPP

#include <kerbal/container/vector.hpp>

#include <kerbal/algorithm/modifier.hpp>
#include <kerbal/algorithm/swap.hpp>
#include <kerbal/algorithm/uninitialized.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/memory/uninitialized.hpp>
#include <kerbal/operators/generic_assign.hpp>
#include <kerbal/type_traits/can_be_pseudo_destructible.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

#if __cplusplus >= 201103L
#	include <type_traits>
#else
#	include <kerbal/type_traits/fundamental_deduction.hpp>
#	include <kerbal/type_traits/pointer_deduction.hpp>
#endif


namespace kerbal
{

	namespace container
	{

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>::vector()
				KERBAL_CONDITIONAL_NOEXCEPT(
						std::is_nothrow_default_constructible<vector_allocator_overload>::value &&
						std::is_nothrow_default_constructible<vector_allocator_unrelated>::value
				) :
				vector_allocator_overload(),
				vector_allocator_unrelated()
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>::vector(const Allocator & allocator)
				KERBAL_CONDITIONAL_NOEXCEPT(
						std::is_nothrow_copy_constructible<vector_allocator_overload>::value &&
						std::is_nothrow_default_constructible<vector_allocator_unrelated>::value
				) :
				vector_allocator_overload(allocator),
				vector_allocator_unrelated()
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>::vector(size_type n) :
				vector_allocator_overload()
		{
			value_type val;
			this->assign(n, val);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>::vector(size_type n, const_reference val) :
				vector_allocator_overload()
		{
			this->assign(n, val);
		}


		template <typename Tp, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		void vector<Tp, Allocator>::_K_range_copy_cnstrct_impl(InputIterator first, InputIterator last,
													std::input_iterator_tag)
		{
			while (first != last) {
				this->emplace_back(*first);
				++first;
			}
		}

		template <typename Tp, typename Allocator>
		template <typename RandomAccessIterator>
		KERBAL_CONSTEXPR20
		void vector<Tp, Allocator>::_K_range_copy_cnstrct_impl(RandomAccessIterator first, RandomAccessIterator last,
													std::random_access_iterator_tag)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type iter_difference_type;

#	define EACH() do { \
				this->emplace_back(*first); \
				++first; \
			} while (false)

			iter_difference_type trip_count(kerbal::iterator::distance(first, last));
			iter_difference_type remain(trip_count & 3);
			for (trip_count >>= 2; trip_count > 0; --trip_count) {
				EACH();
				EACH();
				EACH();
				EACH();
			}

			if (remain >= 2) {
				EACH();
				EACH();
				remain -= 2;
			}
			if (remain >= 1) {
				EACH();
			}

#	undef EACH

		}

		template <typename Tp, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>::vector(InputIterator first, InputIterator last,
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
						, int
				>::type
		) :
				vector_allocator_overload()
		{
			this->_K_range_copy_cnstrct_impl(first, last, kerbal::iterator::iterator_category(first));
		}


		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>::vector(const vector & src) :
				vector_allocator_overload(src.alloc()),
				vector_allocator_unrelated()
		{
			this->_K_range_copy_cnstrct_impl(src.cbegin(), src.cend(), std::random_access_iterator_tag());
		}


#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>::vector(vector && src) :
				vector_allocator_overload(kerbal::compatibility::move(src.alloc())),
				vector_allocator_unrelated(static_cast<vector_allocator_unrelated &&>(src))
		{
		}

#	endif


#	if __cplusplus < 201103L

#	else

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>::vector(std::initializer_list<value_type> ilist) :
				vector(ilist.begin(), ilist.end())
		{
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>::vector(std::initializer_list<value_type> ilist, const Allocator & allocator) :
				vector(ilist.begin(), ilist.end(), allocator)
		{
		}

#	endif



		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>::~vector()
		{
			kerbal::memory::reverse_destroy(this->_K_p, this->_K_p + this->_K_size);
			kerbal::memory::allocator_traits<Allocator>::deallocate(this->alloc(), this->_K_p, this->_K_capacity);
		}



		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>&
		vector<Tp, Allocator>::operator=(const vector & src)
		{
			this->assign(src.cbegin(), src.cend());
			return *this;
		}

#		if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>&
		vector<Tp, Allocator>::operator=(vector && src)
		{
			this->assign(kerbal::compatibility::move(src));
			return *this;
		}

#		endif

#		if __cplusplus < 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>& vector<Tp, Allocator>::operator=(const kerbal::assign::assign_list<Up> & ilist)
		{
			this->assign(ilist.begin(), ilist.end());
			return *this;
		}

#		else

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		vector<Tp, Allocator>& vector<Tp, Allocator>::operator=(std::initializer_list<value_type> ilist)
		{
			this->assign(ilist.begin(), ilist.end());
			return *this;
		}

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<Tp, Allocator>::_K_assign(size_type new_size, const_reference val, kerbal::type_traits::false_type)
		{
			size_type previous_size = this->size();

			if (previous_size <= new_size) {
				/*
				 * a a a x x x x x
				 * b b b b b b x x
				 */

				kerbal::algorithm::fill(this->begin(), this->end(), val);
				while (previous_size != new_size) {
					this->push_back(val);
					++previous_size;
				}
			} else {
				/*
				 * a a a a a a x x
				 * b b b x x x x x
				 */
				this->shrink_back_to(this->nth(new_size));
				kerbal::algorithm::fill(this->begin(), this->end(), val);
			}
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<Tp, Allocator>::_K_assign(size_type new_size, const_reference val, kerbal::type_traits::true_type)
		{
			kerbal::algorithm::fill(this->begin(), this->nth(new_size), val);
			this->len = new_size;
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<Tp, Allocator>::assign(size_type new_size, const value_type & val)
		{

#		if __cplusplus < 201103L

			struct enable_optimization:
					kerbal::type_traits::bool_constant<
						kerbal::type_traits::is_fundamental<remove_all_extents_t>::value ||
						kerbal::type_traits::is_pointer<remove_all_extents_t>::value
					>
			{
			};

#		else

			struct enable_optimization:
					kerbal::type_traits::bool_constant<
						std::is_trivially_copy_constructible<remove_all_extents_t>::value &&
						std::is_trivially_copy_assignable<remove_all_extents_t>::value &&
						std::is_trivially_destructible<remove_all_extents_t>::value
					>
			{
			};

#		endif

			this->_K_assign(new_size, val, enable_optimization());
		}

		template <typename Tp, typename Allocator>
		template <typename InputIterator>
		KERBAL_CONSTEXPR20
		typename kerbal::type_traits::enable_if<
				kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
		>::type
		vector<Tp, Allocator>::assign(InputIterator first, InputIterator last)
		{
			iterator assign_it = this->begin();
			while (assign_it != this->end() && static_cast<bool>(first != last)) {
				kerbal::operators::generic_assign(*assign_it, *first); // *assign_it = *first;
				++assign_it;
				++first;
			}

			if (assign_it != this->end()) { // namely: first == last
				// X X X X O O O
				// T T
				this->shrink_back_to(assign_it);
			} else {
				// X X X X O O O
				// T T T T T T T T T
				while (!this->full() && static_cast<bool>(first != last)) {
					this->push_back(*first);
					++first;
				}
			}
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<Tp, Allocator>::assign(const vector & src)
		{
			this->assign(src.cbegin(), src.cend());
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<Tp, Allocator>::assign(vector && src)
		{
			vector_allocator_unrelated::_K_swap(*this, src);
			// TODO
		}

#	endif

#	if __cplusplus < 201103L

		template <typename Tp, typename Allocator>
		template <typename Up>
		KERBAL_CONSTEXPR20
		void vector<Tp, Allocator>::assign(const kerbal::assign::assign_list<Up> & ilist)
		{
			this->assign(ilist.cbegin(), ilist.cend());
		}

#	else

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<Tp, Allocator>::assign(std::initializer_list<value_type> ilist)
		{
			this->assign(ilist.begin(), ilist.end());
		}

#	endif


		template <typename Tp, typename Allocator>
		void vector<Tp, Allocator>::reserve(size_type new_capacity)
		{
			if (new_capacity <= this->_K_capacity) {
				return;
			}

			typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

			pointer new_buffer = allocator_traits::allocate(this->alloc(), new_capacity);
			pointer pos = new_buffer;
			const_iterator first(this->cbegin());
			const_iterator last(this->cend());

			try {
				while (first != last) {
					allocator_traits::construct(this->alloc(), pos, kerbal::compatibility::move(*first));
					++pos;
					++first;
				}
			} catch (...) {
				while (pos != new_buffer) {
					--pos;
					allocator_traits::destroy(this->alloc(), pos);
				}
				allocator_traits::deallocate(this->alloc(), new_buffer, new_capacity);
				throw;
			}

			while (last != first) {
				--last;
				allocator_traits::destroy(this->alloc(), last.current);
			}
			allocator_traits::deallocate(this->alloc(), this->_K_p, this->_K_capacity);

			this->_K_p = new_buffer;
			this->_K_capacity = new_capacity;
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<Tp, Allocator>::__shrink_back_to(const_iterator to, kerbal::type_traits::false_type)
		{
			while (this->end() > to) {
				this->pop_back();
			}
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<Tp, Allocator>::__shrink_back_to(const_iterator to, kerbal::type_traits::true_type) KERBAL_NOEXCEPT
		{
			this->len = this->index_of(to);
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<Tp, Allocator>::shrink_back_to(const_iterator to)
		{
			this->__shrink_back_to(to, kerbal::type_traits::can_be_pseudo_destructible<value_type>());
		}


	//===================
	// insert

#	if __cplusplus < 201103L

#	else

		template <typename Tp, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename vector<Tp, Allocator>::iterator
		vector<Tp, Allocator>::emplace(const_iterator pos, Args&& ... args)
		{
			iterator pos_mut(pos.cast_to_mutable());
			if (pos == this->cend()) {
				// A A A O O O
				//          ^
				this->emplace_back(kerbal::utility::forward<Args>(args)...); // construct by args
			} else {
				this->push_back(kerbal::compatibility::move(this->back())); // move construct
				// A A A X Y Z Z O O
				//          ^
				kerbal::algorithm::move_backward(pos_mut, this->end() - 2, this->end() - 1); // move assign
				// A A A X X Y Z O O
				//          ^
				kerbal::operators::generic_assign(*pos_mut, value_type(kerbal::utility::forward<Args>(args)...));
				// *pos_mut = value_type(kerbal::utility::forward<Args>(args)...); // move assign, construct by args
			}
			return pos_mut;
		}

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename vector<Tp, Allocator>::iterator
		vector<Tp, Allocator>::insert(const_iterator pos, const_reference val)
		{
			return this->emplace(pos, val);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename vector<Tp, Allocator>::iterator
		vector<Tp, Allocator>::insert(const_iterator pos, rvalue_reference val)
		{
			return this->emplace(pos, kerbal::compatibility::move(val));
		}

#	endif

#	if __cplusplus < 201103L

		template <typename Tp, typename Allocator>
		typename vector<Tp, Allocator>::reference
		vector<Tp, Allocator>::emplace_back()
		{
			this->__construct_at(this->end());
			++this->len;
			return this->back();
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0>
		typename vector<Tp, Allocator>::reference
		vector<Tp, Allocator>::emplace_back(const Arg0 & arg0)
		{
			this->__construct_at(this->end(), arg0);
			++this->len;
			return this->back();
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1>
		typename vector<Tp, Allocator>::reference
		vector<Tp, Allocator>::emplace_back(const Arg0 & arg0, const Arg1& arg1)
		{
			this->__construct_at(this->end(), arg0, arg1);
			++this->len;
			return this->back();
		}

		template <typename Tp, typename Allocator>
		template <typename Arg0, typename Arg1, typename Arg2>
		typename vector<Tp, Allocator>::reference
		vector<Tp, Allocator>::emplace_back(const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2)
		{
			this->__construct_at(this->end(), arg0, arg1, arg2);
			++this->len;
			return this->back();
		}

#	else

		template <typename Tp, typename Allocator>
		template <typename ... Args>
		KERBAL_CONSTEXPR20
		typename vector<Tp, Allocator>::reference
		vector<Tp, Allocator>::emplace_back(Args&& ... args)
		{
			this->__construct_at(this->end(), kerbal::utility::forward<Args>(args)...);
			++this->len;
			return this->back();
		}

#	endif

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<Tp, Allocator>::push_back(const_reference src)
		{
			this->emplace_back(src);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<Tp, Allocator>::push_back(rvalue_reference src)
		{
			this->emplace_back(kerbal::compatibility::move(src));
		}

#	endif


	//===================
	// erase

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<Tp, Allocator>::pop_back() KERBAL_NOEXCEPT
		{
			kerbal::memory::destroy_on(this>back());
			--this->_K_size;
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename vector<Tp, Allocator>::iterator
		vector<Tp, Allocator>::erase(const_iterator pos)
		{
			iterator pos_mut(pos.cast_to_mutable());

			if (pos == this->cend()) {
				return pos_mut;
			}

			// pre-condition: pos != cend()
			kerbal::algorithm::move(pos_mut + 1, this->end(), pos_mut);
			this->pop_back();
			return pos_mut;
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		typename vector<Tp, Allocator>::iterator
		vector<Tp, Allocator>::erase(const_iterator first, const_iterator last)
		{
			iterator first_mut(first.cast_to_mutable());
			iterator last_mut(last.cast_to_mutable());

			kerbal::algorithm::move(last_mut, this->end(), first_mut);

			iterator new_end(this->end() - (last_mut - first_mut));
			this->shrink_back_to(new_end);
			return first_mut;
		}

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<Tp, Allocator>::clear() KERBAL_NOEXCEPT
		{
			kerbal::memory::reverse_destroy(this->_K_p, this->_K_p + this->_K_size);
			this->_K_size = 0;
		}


	//===================
	// operation

		template <typename Tp, typename Allocator>
		KERBAL_CONSTEXPR20
		void vector<Tp, Allocator>::swap(vector & with)
		{
			this->list_allocator_overload::swap_allocator_if_propagate(ano);

			vector_allocator_unrelated::_K_swap(*this, ano);
		}

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_IMPL_VECTOR_IMPL_HPP
