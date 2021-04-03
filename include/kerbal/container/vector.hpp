/**
 * @file       vector.hpp
 * @brief
 * @date       2020-6-12
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_VECTOR_HPP
#define KERBAL_CONTAINER_VECTOR_HPP

#include <kerbal/algorithm/sequence_compare.hpp>
#include <kerbal/assign/ilist.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/static_container_exception.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/iterator/reverse_iterator.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/type_traits/array_traits.hpp>
#include <kerbal/type_traits/enable_if.hpp>

#include <memory>

#if __cplusplus >= 201103L
#	include <initializer_list>
#	include <type_traits>
#endif

#if __cplusplus >= 201703L
#	if __has_include(<memory_resource>)
#		include <memory_resource>
#	endif
#endif

#include <kerbal/container/detail/vector_base.hpp>
#include <kerbal/container/detail/vector_iterator.hpp>

namespace kerbal
{

	namespace container
	{

		template <typename Tp, typename Allocator>
		class vector:
				protected kerbal::container::detail::vector_allocator_overload<Allocator>,
				protected kerbal::container::detail::vector_allocator_unrelated<Tp>
		{
			private:
				typedef kerbal::container::detail::vector_allocator_overload<Allocator>		vector_allocator_overload;
				typedef kerbal::container::detail::vector_allocator_unrelated<Tp>			vector_allocator_unrelated;

			public:
				typedef typename vector_allocator_unrelated::value_type					value_type;
				typedef typename vector_allocator_unrelated::const_type					const_type;
				typedef typename vector_allocator_unrelated::reference					reference;
				typedef typename vector_allocator_unrelated::const_reference			const_reference;
				typedef typename vector_allocator_unrelated::pointer					pointer;
				typedef typename vector_allocator_unrelated::const_pointer				const_pointer;

#		if __cplusplus >= 201103L
				typedef typename vector_allocator_unrelated::rvalue_reference			rvalue_reference;
				typedef typename vector_allocator_unrelated::const_rvalue_reference		const_rvalue_reference;
#		endif

				typedef typename vector_allocator_unrelated::size_type					size_type;
				typedef typename vector_allocator_unrelated::difference_type			difference_type;

				typedef typename vector_allocator_unrelated::iterator					iterator;
				typedef typename vector_allocator_unrelated::const_iterator				const_iterator;
				typedef typename vector_allocator_unrelated::reverse_iterator			reverse_iterator;
				typedef typename vector_allocator_unrelated::const_reverse_iterator		const_reverse_iterator;

			private:
				typedef typename kerbal::type_traits::remove_all_extents<value_type>::type remove_all_extents_t;

			public:
				typedef typename vector_allocator_overload::allocator_type				allocator_type;
				typedef kerbal::memory::allocator_traits<allocator_type>				allocator_traits;

			private:
				using vector_allocator_overload::alloc;

			public:
				KERBAL_CONSTEXPR20
				vector() KERBAL_CONDITIONAL_NOEXCEPT(
						std::is_nothrow_default_constructible<vector_allocator_overload>::value &&
						std::is_nothrow_default_constructible<vector_allocator_unrelated>::value
				);

				KERBAL_CONSTEXPR20
				explicit
				vector(const Allocator & allocator) KERBAL_CONDITIONAL_NOEXCEPT(
						std::is_nothrow_copy_constructible<vector_allocator_overload>::value &&
						std::is_nothrow_default_constructible<vector_allocator_unrelated>::value
				);

				KERBAL_CONSTEXPR20
				explicit
				vector(size_type n);

				KERBAL_CONSTEXPR20
				vector(size_type n, const_reference val);

				KERBAL_CONSTEXPR20
				vector(size_type n, const_reference val, const Allocator & allocator);

			private:

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				void _K_range_copy_cnstrct_impl(InputIterator first, InputIterator last, std::input_iterator_tag);

				template <typename RandomAccessIterator>
				KERBAL_CONSTEXPR20
				void _K_range_copy_cnstrct_impl(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag);

			public:

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				vector(InputIterator first, InputIterator last,
						typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
								, int
						>::type = 0
				);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				vector(InputIterator first, InputIterator last, const Allocator & allocator,
						typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
								, int
						>::type = 0
				);

				KERBAL_CONSTEXPR20
				vector(const vector & src);

				KERBAL_CONSTEXPR20
				vector(const vector & src, const Allocator & allocator);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				vector(vector && src);

				KERBAL_CONSTEXPR20
				vector(vector && src, const Allocator & allocator);

#		endif

#		if __cplusplus < 201103L

				template <typename Up>
				vector(const kerbal::assign::assign_list<Up> & ilist);

				template <typename Up>
				vector(const kerbal::assign::assign_list<Up> & ilist, const Allocator & allocator);

#		else

				KERBAL_CONSTEXPR20
				vector(std::initializer_list<value_type> ilist);

				KERBAL_CONSTEXPR20
				vector(std::initializer_list<value_type> ilist, const Allocator & allocator);

#		endif

				KERBAL_CONSTEXPR20
				~vector();

				KERBAL_CONSTEXPR20
				vector& operator=(const vector & src);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				vector& operator=(vector && src);

#		endif

#		if __cplusplus < 201103L

				template <typename Up>
				KERBAL_CONSTEXPR20
				vector& operator=(const kerbal::assign::assign_list<Up> & ilist);

#		else

				KERBAL_CONSTEXPR20
				vector& operator=(std::initializer_list<value_type> ilist);

#		endif

			private:

				KERBAL_CONSTEXPR20
				void _K_assign(size_type new_size, const_reference val, kerbal::type_traits::false_type enable_optimization);

				KERBAL_CONSTEXPR20
				void _K_assign(size_type new_size, const_reference val, kerbal::type_traits::true_type enable_optimization);

			public:

				KERBAL_CONSTEXPR20
				void assign(size_type new_size, const_reference val);

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
				>::type
				assign(InputIterator first, InputIterator last);

				KERBAL_CONSTEXPR20
				void assign(const vector & src);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void assign(vector && src);

#		endif

#		if __cplusplus < 201103L

				template <typename Up>
				KERBAL_CONSTEXPR20
				void assign(const kerbal::assign::assign_list<Up> & ilist);

#		else

				KERBAL_CONSTEXPR20
				void assign(std::initializer_list<value_type> ilist);

#		endif

			//===================
			// element access

				using vector_allocator_unrelated::at;
				using vector_allocator_unrelated::operator[];
				using vector_allocator_unrelated::front;
				using vector_allocator_unrelated::back;
				using vector_allocator_unrelated::data;

			//===================
			// iterator

				using vector_allocator_unrelated::begin;
				using vector_allocator_unrelated::end;

				using vector_allocator_unrelated::cbegin;
				using vector_allocator_unrelated::cend;

				using vector_allocator_unrelated::rbegin;
				using vector_allocator_unrelated::rend;

				using vector_allocator_unrelated::crbegin;
				using vector_allocator_unrelated::crend;

				using vector_allocator_unrelated::nth;
				using vector_allocator_unrelated::index_of;

			//===================
			// capacity

				using vector_allocator_unrelated::empty;
				using vector_allocator_unrelated::size;
				using vector_allocator_unrelated::max_size;
				using vector_allocator_unrelated::capacity;

				KERBAL_CONSTEXPR20
				void reserve(size_type new_capacity);

			private:
				KERBAL_CONSTEXPR20
				void __shrink_back_to(const_iterator to, kerbal::type_traits::false_type);

				KERBAL_CONSTEXPR20
				void __shrink_back_to(const_iterator to, kerbal::type_traits::true_type) KERBAL_NOEXCEPT;

			public:
				KERBAL_CONSTEXPR20
				void shrink_back_to(const_iterator to);

				KERBAL_CONSTEXPR20
				void shrink_to_fit();

			//===================
			// insert

#		if __cplusplus < 201103L

				iterator emplace();

				template <typename Arg0>
				iterator emplace(const Arg0& arg0);

				template <typename Arg0, typename Arg1>
				iterator emplace(const Arg0& arg0, const Arg1& arg1);

				template <typename Arg0, typename Arg1, typename Arg2>
				iterator emplace(const Arg0& arg0, const Arg1& arg1, const Arg2& arg2);

#		else

				template <typename ... Args>
				KERBAL_CONSTEXPR20
				iterator emplace(const_iterator pos, Args&& ...args);

#		endif

				KERBAL_CONSTEXPR20
				iterator insert(const_iterator pos, const_reference val);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				iterator insert(const_iterator pos, rvalue_reference val);

#		endif

#		if __cplusplus < 201103L

				reference emplace_back();

				template <typename Arg0>
				reference emplace_back(const Arg0 & arg0);

				template <typename Arg0, typename Arg1>
				reference emplace_back(const Arg0 & arg0, const Arg1 & arg1);

				template <typename Arg0, typename Arg1, typename Arg2>
				reference emplace_back(const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2);

#		else

				template <typename ... Args>
				KERBAL_CONSTEXPR20
				reference emplace_back(Args&& ...args);

#		endif

				KERBAL_CONSTEXPR20
				void push_back(const_reference src);

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void push_back(rvalue_reference src);

#		endif

			//===================
			// erase

				KERBAL_CONSTEXPR20
				void pop_back() KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR20
				iterator erase(const_iterator pos);

				KERBAL_CONSTEXPR20
				iterator erase(const_iterator begin, const_iterator end);

				KERBAL_CONSTEXPR20
				void clear() KERBAL_NOEXCEPT;

			//===================
			// operation

				KERBAL_CONSTEXPR20
				void resize(size_type count);

				KERBAL_CONSTEXPR20
				void resize(size_type count, const_reference value);

				KERBAL_CONSTEXPR20
				void swap(vector & with);

		};

#	if __cplusplus >= 201703L

		template <typename InputIterator, typename Alloc =
					std::allocator<typename kerbal::iterator::iterator_traits<InputIterator>::value_type> >
		vector(InputIterator, InputIterator, Alloc = Alloc())
				-> vector<typename kerbal::iterator::iterator_traits<InputIterator>::value_type, Alloc>;

#	if __has_include(<memory_resource>)

		namespace pmr
		{
			template <typename Tp>
			using vector = kerbal::container::vector<Tp, std::pmr::polymorphic_allocator<Tp> >;
		}

#	endif

#	endif


		template <typename Tp, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator==(const vector<Tp, Allocator> & lhs, const vector<Tp, Allocator2> & rhs)
		{
			return kerbal::algorithm::sequence_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator!=(const vector<Tp, Allocator> & lhs, const vector<Tp, Allocator2> & rhs)
		{
			return kerbal::algorithm::sequence_not_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator<(const vector<Tp, Allocator> & lhs, const vector<Tp, Allocator2> & rhs)
		{
			return kerbal::algorithm::sequence_less(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator<=(const vector<Tp, Allocator> & lhs, const vector<Tp, Allocator2> & rhs)
		{
			return kerbal::algorithm::sequence_less_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator>(const vector<Tp, Allocator> & lhs, const vector<Tp, Allocator2> & rhs)
		{
			return kerbal::algorithm::sequence_greater(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator, typename Allocator2>
		KERBAL_CONSTEXPR20
		bool operator>=(const vector<Tp, Allocator> & lhs, const vector<Tp, Allocator2> & rhs)
		{
			return kerbal::algorithm::sequence_greater_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

	} // namespace container

} // namespace kerbal

#include <kerbal/container/impl/vector.impl.hpp>

#endif // KERBAL_CONTAINER_VECTOR_HPP
