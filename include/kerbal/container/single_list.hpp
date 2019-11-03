/**
 * @file       single_list.hpp
 * @brief      
 * @date       2019-7-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_SINGLE_LIST_HPP_
#define KERBAL_CONTAINER_SINGLE_LIST_HPP_

#include <kerbal/algorithm/sequence_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/method_overload_tag.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/operators/dereferenceable.hpp>
#include <kerbal/operators/equality_comparable.hpp>
#include <kerbal/operators/incr_decr.hpp>
#include <kerbal/type_traits/type_traits_details/enable_if.hpp>
#include <kerbal/utility/noncopyable.hpp>

#include <memory>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif

namespace kerbal
{

	namespace container
	{

		template <typename Tp, typename Allocator>
		class single_list;

		namespace detail
		{

			class __sl_node_base: kerbal::utility::noncopyable
			{
				public:
					__sl_node_base * next;

					KERBAL_CONSTEXPR __sl_node_base() KERBAL_NOEXCEPT :
							next(NULL)
					{
					}
			};

			template <typename Tp>
			class __sl_node: public __sl_node_base
			{
				private:
					typedef Tp value_type;
					typedef Tp& reference;
					typedef const Tp& const_reference;
					typedef Tp&& rvalue_reference;
					typedef const Tp&& const_rvalue_reference;

					template <typename Up, typename Allocator>
					friend class kerbal::container::single_list;

					value_type __value;

#		if __cplusplus >= 201103L

					template <typename ... Args>
					KERBAL_CONSTEXPR
					explicit __sl_node(Args&& ... args): __value(std::forward<Args>(args)...)
					{
					}

#		else
					KERBAL_CONSTEXPR
					__sl_node()
							: __value()
					{
					}

					template <typename Arg0>
					KERBAL_CONSTEXPR
					explicit __sl_node(const Arg0 & arg0)
							: __value(arg0)
					{
					}

					template <typename Arg0, typename Arg1>
					KERBAL_CONSTEXPR
					__sl_node(const Arg0 & arg0, const Arg1 & arg1)
							: __value(arg0, arg1)
					{
					}

					template <typename Arg0, typename Arg1, typename Arg2>
					KERBAL_CONSTEXPR
					__sl_node(const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2)
							: __value(arg0, arg1, arg2)
					{
					}

#		endif

				public:

					KERBAL_CONSTEXPR14 reference value()
							KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return this->__value;
					}

					KERBAL_CONSTEXPR14 const_reference value()
							KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return this->__value;
					}

#		if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14 rvalue_reference value() && KERBAL_NOEXCEPT
					{
						return this->__value;
					}

					KERBAL_CONSTEXPR14 const_rvalue_reference value() const && KERBAL_NOEXCEPT
					{
						return this->__value;
					}

#		endif

			};

			template <typename Pointer>
			struct __sl_iterbase_traits
			{
				private:
					typedef kerbal::iterator::iterator_traits<Pointer>		iterator_traits;

				public:
					typedef std::forward_iterator_tag						iterator_category;
					typedef typename iterator_traits::value_type			value_type;
					typedef typename iterator_traits::difference_type		difference_type;
					typedef typename iterator_traits::pointer				pointer;
					typedef typename iterator_traits::reference				reference;

					typedef std::iterator<
							iterator_category,
							value_type,
							difference_type,
							pointer,
							reference
					> type;
			};

			template <typename Tp>
			class __sl_iter;

			template <typename Tp>
			class __sl_kiter;

			template <typename DerivedIterator, typename Tp, typename Pointer, typename PointerToNode>
			class __sl_iterbase: public __sl_iterbase_traits<Pointer>::type,
								public kerbal::operators::dereferenceable<DerivedIterator, Pointer>,
								public kerbal::operators::equality_comparable<DerivedIterator>,
								public kerbal::operators::incrementable<DerivedIterator>
			{
				private:
					friend class __sl_iter<Tp>;
					friend class __sl_kiter<Tp>;

					PointerToNode current;

					typedef __sl_iterbase_traits<Pointer> iterator_base_t;

					template <typename Up, typename Allocator>
					friend class kerbal::container::single_list;

				protected:
					KERBAL_CONSTEXPR
					explicit __sl_iterbase(PointerToNode current) KERBAL_NOEXCEPT :
							current(current)
					{
					}

				public:
					friend KERBAL_CONSTEXPR14
					typename iterator_base_t::reference
					operator*(const DerivedIterator & iter) KERBAL_NOEXCEPT
					{
						return static_cast<kerbal::container::detail::__sl_node<Tp>*>(iter.current->next)->value();
					}

					friend KERBAL_CONSTEXPR14
					DerivedIterator& operator++(DerivedIterator & iter) KERBAL_NOEXCEPT
					{
						iter.current = iter.current->next;
						return iter;
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const DerivedIterator & lhs, const DerivedIterator & rhs) KERBAL_NOEXCEPT
					{
						return lhs.current == rhs.current;
					}
			};

			template <typename Tp>
			class __sl_iter : public __sl_iterbase<__sl_iter<Tp>, Tp, Tp*, kerbal::container::detail::__sl_node_base*>
			{
				private:
					template <typename Up, typename Allocator>
					friend class kerbal::container::single_list;

					friend class __sl_kiter<Tp>;

					typedef __sl_iterbase<__sl_iter<Tp>, Tp, Tp*, kerbal::container::detail::__sl_node_base*> super;

				private:
					KERBAL_CONSTEXPR
					explicit __sl_iter(__sl_node_base* current) KERBAL_NOEXCEPT :
							super(current)
					{
					}
			};

			template <typename Tp>
			class __sl_kiter : public __sl_iterbase<__sl_kiter<Tp>, Tp, const Tp*, const kerbal::container::detail::__sl_node_base*>
			{
				private:
					template <typename Up, typename Allocator>
					friend class kerbal::container::single_list;

					typedef __sl_iterbase<__sl_kiter<Tp>, Tp, const Tp*, const kerbal::container::detail::__sl_node_base*> super;

				private:
					KERBAL_CONSTEXPR
					explicit __sl_kiter(const __sl_node_base* current) KERBAL_NOEXCEPT :
							super(current)
					{
					}

				public:
					KERBAL_CONSTEXPR
					__sl_kiter(const __sl_iter<Tp>& iter) KERBAL_NOEXCEPT :
							super(iter.current)
					{
					}
			};

		} //namespace detail

		template <typename Tp, typename Allocator = std::allocator<Tp> >
		class single_list
		{
			public:
				/// @brief Type of the elements.
				typedef Tp value_type;

				/// @brief Constant type of the elements.
				typedef const value_type const_type;

				/// @brief Reference of the elements.
				typedef value_type& reference;

				/// @brief Constant reference of the elements.
				typedef const value_type& const_reference;

				/// @brief Pointer type to the elements.
				typedef value_type* pointer;

				/// @brief Constant pointer type to the elements.
				typedef const value_type* const_pointer;

#		if __cplusplus >= 201103L
				typedef value_type&& rvalue_reference;
				typedef const value_type&& const_rvalue_reference;
#		endif

				typedef std::size_t size_type;
				typedef std::ptrdiff_t difference_type;

				typedef kerbal::container::detail::__sl_iter<value_type>  iterator;
				typedef kerbal::container::detail::__sl_kiter<value_type> const_iterator;

			private:
				typedef kerbal::container::detail::__sl_node_base __sl_node_base;
				typedef kerbal::container::detail::__sl_node<value_type> node;
				typedef typename Allocator::template rebind<node>::other node_allocator_type;

				__sl_node_base __head;
				iterator __last;
				node_allocator_type alloc;
				
				static KERBAL_CONSTEXPR
				node* __node_cast(__sl_node_base * base) KERBAL_NOEXCEPT;

				static KERBAL_CONSTEXPR
				const node* __node_cast(const __sl_node_base * base) KERBAL_NOEXCEPT;

				struct release_uninit_res
				{
					node_allocator_type& alloc;
					
					KERBAL_CONSTEXPR release_uninit_res(node_allocator_type& alloc) KERBAL_NOEXCEPT :
							alloc(alloc)
					{
					}

					void operator()(node *p) KERBAL_NOEXCEPT
					{
						this->alloc.deallocate(p, 1);
					}
				};

			public:
				single_list();

				explicit single_list(const Allocator& alloc);

				single_list(const single_list & src);

				single_list(const single_list & src, const Allocator& alloc);

				explicit single_list(size_type n, const Allocator& alloc = Allocator());

				single_list(size_type n, const_reference val, const Allocator& alloc = Allocator());

				template <typename InputIterator>
				single_list(InputIterator first, InputIterator last, const Allocator& alloc = Allocator(),
						typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
								, int
						>::type = 0
				);

#		if __cplusplus >= 201103L

				single_list(single_list && src);

				single_list(single_list && src, const Allocator& alloc);

				single_list(std::initializer_list<value_type> src, const Allocator& alloc = Allocator());

#		endif

				~single_list();

				single_list& operator=(const single_list & src);

#		if __cplusplus >= 201103L
				single_list& operator=(single_list && src);

				single_list& operator=(std::initializer_list<value_type> src);

#		endif

				void assign(const single_list & src);

				void assign(size_type count, const_reference val);

				template <typename InputIterator>
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
				>::type
				assign(InputIterator first, InputIterator last);

#		if __cplusplus >= 201103L

				void assign(single_list&& src);

				void assign(std::initializer_list<value_type> src);

#		endif

				reference front();
				const_reference front() const;

				reference back();
				const_reference back() const;

				/** @brief 返回指向首元素的迭代器 */
				iterator begin() KERBAL_NOEXCEPT;

				/** @brief 返回指向尾元素的后一个元素位置的迭代器 */
				iterator end() KERBAL_NOEXCEPT;

				const_iterator begin() const KERBAL_NOEXCEPT;

				/** @brief 返回指向末尾元素的后一个元素位置的迭代器 */
				const_iterator end() const KERBAL_NOEXCEPT;

				const_iterator cbegin() const KERBAL_NOEXCEPT;

				const_iterator cend() const KERBAL_NOEXCEPT;

				iterator nth(size_type index);
				const_iterator nth(size_type index) const;

				size_type index_of(iterator it);
				size_type index_of(const_iterator it) const;

				bool empty() const KERBAL_NOEXCEPT;

				size_type size() const KERBAL_NOEXCEPT;

				KERBAL_CONSTEXPR size_type max_size() const
				{
					return static_cast<size_type>(-1);
				}

			private:
				void __insert_back_helper(node * p) KERBAL_NOEXCEPT;

			public:
				/**
				 * @brief 在末尾插入参数 val 指定的元素
				 * @param val
				 */
				void push_back(const_reference val);

#		if __cplusplus >= 201103L
				/**
				 * @brief 在末尾插入参数 val 指定的元素
				 * @param val
				 */
				void push_back(rvalue_reference val);

				template <typename ... Args>
				reference emplace_back(Args&& ...args);

#		else

				reference emplace_back();

				template <typename Arg0>
				reference emplace_back(const Arg0& arg0);

				template <typename Arg0, typename Arg1>
				reference emplace_back(const Arg0& arg0, const Arg1& arg1);

				template <typename Arg0, typename Arg1, typename Arg2>
				reference emplace_back(const Arg0& arg0, const Arg1& arg1, const Arg2& arg2);

#		endif

			private:
				void __insert_front_helper(node * p) KERBAL_NOEXCEPT;

			public:
				/**
				 * @brief 在首部插入参数 val 指定的元素
				 * @param val
				 */
				void push_front(const_reference val);

#		if __cplusplus >= 201103L
				/**
				 * @brief 在首部插入参数 val 指定的元素
				 * @param src
				 */
				void push_front(rvalue_reference val);

				template <typename ... Args>
				reference emplace_front(Args&& ...args);

#		else

				reference emplace_front();

				template <typename Arg0>
				reference emplace_front(const Arg0& arg0);

				template <typename Arg0, typename Arg1>
				reference emplace_front(const Arg0& arg0, const Arg1& arg1);

				template <typename Arg0, typename Arg1, typename Arg2>
				reference emplace_front(const Arg0& arg0, const Arg1& arg1, const Arg2& arg2);

#		endif

			private:
				iterator __node_insert_helper(const_iterator pos, node * p) KERBAL_NOEXCEPT;

			public:

				iterator insert(const_iterator pos, const_reference val);

#		if __cplusplus >= 201103L

				iterator insert(const_iterator pos, rvalue_reference val);

				template <typename ... Args>
				iterator emplace(const_iterator pos, Args&& ...args);

#		else

				iterator emplace(const_iterator pos);

				template <typename Arg0>
				iterator emplace(const_iterator pos, const Arg0& arg0);

				template <typename Arg0, typename Arg1>
				iterator emplace(const_iterator pos, const Arg0& arg0, const Arg1& arg1);

				template <typename Arg0, typename Arg1, typename Arg2>
				iterator emplace(const_iterator pos, const Arg0& arg0, const Arg1& arg1, const Arg2& arg2);

#		endif

				/**
				 * @brief 移除首部的元素
				 */
				void pop_front();

				iterator erase(const_iterator pos);

				iterator erase(const_iterator first, const_iterator last);

				void clear();

				void resize(size_type count);

				void resize(size_type count, const_reference value);

				void swap(single_list & ano);

			private:
				void __consecutive_destroy_node(node *start);

#		if __cplusplus >= 201103L

				template <typename ... Args>
				node* __alloc_new_node(Args&& ...args);

#		else

				node* __alloc_new_node();

				template <typename Arg0>
				node* __alloc_new_node(const Arg0& arg0);

				template <typename Arg0, typename Arg1>
				node* __alloc_new_node(const Arg0& arg0, const Arg1& arg1);

				template <typename Arg0, typename Arg1, typename Arg2>
				node* __alloc_new_node(const Arg0& arg0, const Arg1& arg1, const Arg2& arg2);

#		endif


		};


		template <typename Tp, typename Allocator>
		bool operator==(const single_list<Tp, Allocator> & lhs, const single_list<Tp, Allocator> & rhs)
		{
			return kerbal::algorithm::sequence_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator>
		bool operator!=(const single_list<Tp, Allocator> & lhs, const single_list<Tp, Allocator> & rhs)
		{
			return kerbal::algorithm::sequence_not_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator>
		bool operator<(const single_list<Tp, Allocator> & lhs, const single_list<Tp, Allocator> & rhs)
		{
			return kerbal::algorithm::sequence_less(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator>
		bool operator>(const single_list<Tp, Allocator> & lhs, const single_list<Tp, Allocator> & rhs)
		{
			return kerbal::algorithm::sequence_greater(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator>
		bool operator<=(const single_list<Tp, Allocator> & lhs, const single_list<Tp, Allocator> & rhs)
		{
			return kerbal::algorithm::sequence_less_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename Allocator>
		bool operator>=(const single_list<Tp, Allocator> & lhs, const single_list<Tp, Allocator> & rhs)
		{
			return kerbal::algorithm::sequence_greater_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

	} //namespace container

} //namespace kerbal

#include <kerbal/container/impl/single_list.impl.hpp>

#endif /* KERBAL_CONTAINER_SINGLE_LIST_HPP_ */
