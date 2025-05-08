/**
 * @file       flat_ordered_base.decl.hpp
 * @brief
 * @date       2019-12-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_FLAT_ORDERED_BASE_FLAT_ORDERED_BASE_DECL_HPP
#define KERBAL_CONTAINER_DETAIL_FLAT_ORDERED_BASE_FLAT_ORDERED_BASE_DECL_HPP

#include <kerbal/container/detail/flat_ordered_base/flat_ordered_base.fwd.hpp>

#include <kerbal/assign/ilist.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/associative_container_facility/associative_unique_insert_r.hpp>
#include <kerbal/container/associative_container_facility/key_compare_is_transparent.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/iterator/transform_iterator.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/is_same.hpp>
#include <kerbal/utility/compressed_pair.hpp>
#include <kerbal/utility/member_compress_helper.hpp>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Entity, typename Extract, typename KeyCompare, typename Sequence>
			class flat_ordered_base :
				private kerbal::utility::member_compress_helper<Extract>,
				private kerbal::utility::member_compress_helper<KeyCompare>
			{
				protected:
					typedef kerbal::utility::member_compress_helper<Extract>	extract_compress_helper;
					typedef kerbal::utility::member_compress_helper<KeyCompare>	key_compare_compress_helper;

				public:
					typedef Entity					value_type;
					typedef const value_type		const_type;
					typedef value_type &			reference;
					typedef const value_type &		const_reference;
					typedef value_type *			pointer;
					typedef const value_type *		const_pointer;

#			if __cplusplus >= 201103L
					typedef value_type &&			rvalue_reference;
					typedef const value_type &&		const_rvalue_reference;
#			endif

					typedef typename Sequence::size_type				size_type;
					typedef typename Sequence::difference_type			difference_type;

					typedef typename Sequence::iterator					iterator;
					typedef typename Sequence::const_iterator			const_iterator;
					typedef typename Sequence::reverse_iterator			reverse_iterator;
					typedef typename Sequence::const_reverse_iterator	const_reverse_iterator;
					typedef kerbal::container::associative_unique_insert_r<iterator>
																		unique_insert_r;

					typedef typename Extract::key_type					key_type;
					typedef KeyCompare									key_compare;

				protected:
					Sequence sequence;

				//===================
				// Observers

				public:

					KERBAL_CONSTEXPR14
					Extract &
					extract() KERBAL_NOEXCEPT
					{
						return extract_compress_helper::member();
					}

					KERBAL_CONSTEXPR
					const Extract &
					extract() const KERBAL_NOEXCEPT
					{
						return extract_compress_helper::member();
					}

					KERBAL_CONSTEXPR14
					key_compare &
					key_comp() KERBAL_NOEXCEPT
					{
						return key_compare_compress_helper::member();
					}

					KERBAL_CONSTEXPR14
					const key_compare &
					key_comp() const KERBAL_NOEXCEPT
					{
						return key_compare_compress_helper::member();
					}


					KERBAL_CONSTEXPR14
					void k_sort();

				public:

					struct value_compare
					{
							friend class flat_ordered_base;

						private:
							const flat_ordered_base * self;

							KERBAL_CONSTEXPR
							explicit
							value_compare(const flat_ordered_base * self) KERBAL_NOEXCEPT :
								self(self)
							{
							}

						public:
							KERBAL_CONSTEXPR14
							bool
							operator()(const_reference lhs, const_reference rhs) const
							{
								return self->key_comp()(self->extract()(lhs), self->extract()(rhs));
							}
					};

					KERBAL_CONSTEXPR14
					value_compare
					value_comp() const
					{
						return value_compare(this);
					}


				//===================
				// construct/copy/destroy

				protected:

#			if __cplusplus >= 201103L
					flat_ordered_base() = default;
#			else
					flat_ordered_base();
#			endif

					KERBAL_CONSTEXPR
					explicit
					flat_ordered_base(key_compare kc);

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					flat_ordered_base(
						InputIterator first, InputIterator last,
						typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							int
						>::type = 0
					);

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					flat_ordered_base(
						InputIterator first, InputIterator last, key_compare kc,
						typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							int
						>::type = 0
					);


#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					flat_ordered_base(std::initializer_list<value_type> ilist);

					KERBAL_CONSTEXPR14
					flat_ordered_base(std::initializer_list<value_type> ilist, key_compare kc);

#			else

					flat_ordered_base(const kerbal::assign::assign_list<void> & ilist) :
						key_compare_compress_helper(),
						sequence()
					{
					}

					flat_ordered_base(const kerbal::assign::assign_list<void> & ilist, key_compare kc) :
						key_compare_compress_helper(kerbal::utility::in_place_t(), kc),
						sequence()
					{
					}

					template <typename U>
					flat_ordered_base(const kerbal::assign::assign_list<U> & ilist) :
						key_compare_compress_helper(),
						sequence(ilist.cbegin(), ilist.cend())
					{
						this->k_sort();
					}

					template <typename U>
					flat_ordered_base(const kerbal::assign::assign_list<U> & ilist, key_compare kc) :
						key_compare_compress_helper(kerbal::utility::in_place_t(), kc),
						sequence(ilist.cbegin(), ilist.cend())
					{
						this->k_sort();
					}

#			endif

				public:
					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
					>::type
					assign(InputIterator first, InputIterator last);

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
					>::type
					assign(InputIterator first, InputIterator last, key_compare kc);

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					void
					assign(std::initializer_list<value_type> ilist);

					KERBAL_CONSTEXPR14
					void
					assign(std::initializer_list<value_type> ilist, key_compare kc);

#			else

					void
					assign(const kerbal::assign::assign_list<void> & ilist)
					{
						this->clear();
					}

					void
					assign(const kerbal::assign::assign_list<void> & ilist, key_compare kc)
					{
						this->clear();
						this->key_comp() = kc;
					}

					template <typename U>
					void
					assign(const kerbal::assign::assign_list<U> & ilist)
					{
						this->assign(ilist.cbegin(), ilist.cend());
					}

					template <typename U>
					void
					assign(const kerbal::assign::assign_list<U> & ilist, key_compare kc)
					{
						this->assign(ilist.cbegin(), ilist.cend(), kc);
					}

#			endif


				//===================
				// iterator

				public:

					KERBAL_CONSTEXPR14
					iterator
					begin();

					KERBAL_CONSTEXPR14
					const_iterator
					begin() const;

					KERBAL_CONSTEXPR14
					iterator
					end();

					KERBAL_CONSTEXPR14
					const_iterator
					end() const;

					KERBAL_CONSTEXPR
					const_iterator
					cbegin() const;

					KERBAL_CONSTEXPR
					const_iterator
					cend() const;

					KERBAL_CONSTEXPR14
					reverse_iterator
					rbegin();

					KERBAL_CONSTEXPR14
					const_reverse_iterator
					rbegin() const;

					KERBAL_CONSTEXPR14
					reverse_iterator
					rend();

					KERBAL_CONSTEXPR14
					const_reverse_iterator
					rend() const;

					KERBAL_CONSTEXPR
					const_reverse_iterator
					crbegin() const;

					KERBAL_CONSTEXPR
					const_reverse_iterator
					crend() const;

					KERBAL_CONSTEXPR14
					iterator
					nth(size_type index);

					KERBAL_CONSTEXPR14
					const_iterator
					nth(size_type index) const;

					KERBAL_CONSTEXPR14
					size_type
					index_of(iterator it);

					KERBAL_CONSTEXPR
					size_type
					index_of(const_iterator it) const;

				//===================
				// capacity

				public:

					KERBAL_CONSTEXPR
					size_type
					size() const;

					KERBAL_CONSTEXPR
					size_type
					max_size() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR
					bool
					empty() const;

				//===================
				// lookup

				protected:
					friend struct key_view_iterator_extract_adapter;

					struct key_view_iterator_extract_adapter
					{
						public:
							typedef typename Extract::key_type const & result_type;

						private:
							const flat_ordered_base * k_self;

						public:
							KERBAL_CONSTEXPR
							explicit
							key_view_iterator_extract_adapter(const flat_ordered_base * self) KERBAL_NOEXCEPT :
								k_self(self)
							{
							}

							KERBAL_CONSTEXPR14
							result_type
							operator()(const_reference item) const
							{
								return k_self->extract()(item);
							}
					};

					template <typename Iterator>
					KERBAL_CONSTEXPR14
					kerbal::iterator::transform_iterator<Iterator, key_view_iterator_extract_adapter>
					make_key_view_iterator(Iterator iterator) const
					{
						return kerbal::iterator::transform_iterator<Iterator, key_view_iterator_extract_adapter>(
							iterator,
							key_view_iterator_extract_adapter(this)
						);
					}

					typedef kerbal::iterator::transform_iterator<iterator, key_view_iterator_extract_adapter>		key_view_iterator;
					typedef kerbal::iterator::transform_iterator<const_iterator, key_view_iterator_extract_adapter>	key_view_const_iterator;

					KERBAL_CONSTEXPR14
					key_view_iterator
					key_view_begin()
					{
						return this->make_key_view_iterator(this->begin());
					}

					KERBAL_CONSTEXPR14
					key_view_const_iterator
					key_view_begin() const
					{
						return this->make_key_view_iterator(this->begin());
					}

					KERBAL_CONSTEXPR14
					key_view_const_iterator
					key_view_cbegin() const
					{
						return this->make_key_view_iterator(this->begin());
					}

					KERBAL_CONSTEXPR14
					key_view_iterator
					key_view_end()
					{
						return this->make_key_view_iterator(this->end());
					}

					KERBAL_CONSTEXPR14
					key_view_const_iterator
					key_view_end() const
					{
						return this->make_key_view_iterator(this->end());
					}

					KERBAL_CONSTEXPR14
					key_view_const_iterator
					key_view_cend() const
					{
						return this->make_key_view_iterator(this->end());
					}

				private:
					template <typename Key, typename Result>
					struct enable_if_transparent_lookup :
						kerbal::type_traits::enable_if<
							(
								kerbal::container::key_compare_is_transparent<KeyCompare>::value &&
								!kerbal::type_traits::is_same<const Key &, const typename Extract::key_type &>::value
							),
							Result
						>
					{
					};


				public:

					KERBAL_CONSTEXPR14
					iterator
					lower_bound(const key_type & key);

					KERBAL_CONSTEXPR14
					const_iterator
					lower_bound(const key_type & key) const;

					KERBAL_CONSTEXPR14
					iterator
					lower_bound(const key_type & key, const_iterator hint);

					KERBAL_CONSTEXPR14
					const_iterator
					lower_bound(const key_type & key, const_iterator hint) const;

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						iterator
					>::type
					lower_bound(const Key & key);

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						const_iterator
					>::type
					lower_bound(const Key & key) const;

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						iterator
					>::type
					lower_bound(const Key & key, const_iterator hint);

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						const_iterator
					>::type
					lower_bound(const Key & key, const_iterator hint) const;


					KERBAL_CONSTEXPR14
					iterator
					upper_bound(const key_type & key);

					KERBAL_CONSTEXPR14
					const_iterator
					upper_bound(const key_type & key) const;

					KERBAL_CONSTEXPR14
					iterator
					upper_bound(const key_type & key, const_iterator hint);

					KERBAL_CONSTEXPR14
					const_iterator
					upper_bound(const key_type & key, const_iterator hint) const;

					KERBAL_CONSTEXPR14
					kerbal::utility::compressed_pair<iterator, iterator>
					equal_range(const key_type & key);

					KERBAL_CONSTEXPR14
					kerbal::utility::compressed_pair<const_iterator, const_iterator>
					equal_range(const key_type & key) const;

					KERBAL_CONSTEXPR14
					kerbal::utility::compressed_pair<iterator, iterator>
					equal_range(const key_type & key, const_iterator hint);

					KERBAL_CONSTEXPR14
					kerbal::utility::compressed_pair<const_iterator, const_iterator>
					equal_range(const key_type & key, const_iterator hint) const;

				protected:
					KERBAL_CONSTEXPR14
					iterator
					k_find_impl(iterator lower_bound_pos, const key_type & key)
					{
						iterator end_it(this->end());
						if (lower_bound_pos != end_it && this->key_comp()(key, this->extract()(*lower_bound_pos))) {
							// key < *lower_bound_pos
							/*
							* 1 1 1 3 3 3
							*       ^
							*/
							return end_it;
						} else {
							return lower_bound_pos;
						}
					}

					KERBAL_CONSTEXPR14
					const_iterator
					k_find_impl(const_iterator lower_bound_pos, const key_type & key) const;

				public:
					KERBAL_CONSTEXPR14
					iterator
					find(const key_type & key)
					{
						return this->k_find_impl(this->lower_bound(key), key);
					}

					KERBAL_CONSTEXPR14
					const_iterator
					find(const key_type & key) const;

					KERBAL_CONSTEXPR14
					iterator
					find(const key_type & key, const_iterator hint)
					{
						return this->k_find_impl(this->lower_bound(key, hint), key);
					}

					KERBAL_CONSTEXPR14
					const_iterator
					find(const key_type & key, const_iterator hint) const;

					KERBAL_CONSTEXPR14
					size_type
					count(const key_type & key) const;

					KERBAL_CONSTEXPR14
					size_type
					count(const key_type & key, const_iterator hint) const;

					KERBAL_CONSTEXPR14
					bool
					contains(const key_type & key) const;

					KERBAL_CONSTEXPR14
					bool
					contains(const key_type & key, const_iterator hint) const;


				//===================
				// insert

				protected:
					KERBAL_CONSTEXPR14
					unique_insert_r
					k_insert_unique_impl(iterator ub, const_reference src);

				public:
					KERBAL_CONSTEXPR14
					unique_insert_r
					insert_unique(const_reference src);

					KERBAL_CONSTEXPR14
					unique_insert_r
					insert_unique(const_iterator hint, const_reference src);

#			if __cplusplus >= 201103L

				protected:
					KERBAL_CONSTEXPR14
					unique_insert_r
					k_insert_unique_impl(iterator ub, rvalue_reference src);

				public:
					KERBAL_CONSTEXPR14
					unique_insert_r
					insert_unique(rvalue_reference src);

					KERBAL_CONSTEXPR14
					unique_insert_r
					insert_unique(const_iterator hint, rvalue_reference src);

#			endif

					struct equal_adapter
					{
						private:
							const flat_ordered_base * self;

						public:
							KERBAL_CONSTEXPR
							explicit
							equal_adapter(const flat_ordered_base * self) KERBAL_NOEXCEPT :
								self(self)
							{
							}

							KERBAL_CONSTEXPR14
							bool
							operator()(const_reference lhs, const_reference rhs) const
							{
								Extract const & e = self->extract();
								return
									!static_cast<bool>(self->key_comp()(e(lhs), e(rhs))) &&
									!static_cast<bool>(self->key_comp()(e(rhs), e(lhs)))
								;
							}
					};

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
						InputIterator
					>::type
					insert_unique(InputIterator first, InputIterator last);

					KERBAL_CONSTEXPR14
					iterator
					insert(const_reference src);

					KERBAL_CONSTEXPR14
					iterator
					insert(const_iterator hint, const_reference src);

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					iterator
					insert(rvalue_reference src);

					KERBAL_CONSTEXPR14
					iterator
					insert(const_iterator hint, rvalue_reference src);

#			endif

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
						InputIterator
					>::type
					insert(InputIterator first, InputIterator last);


				//===================
				// erase

				public:

					KERBAL_CONSTEXPR14
					const_iterator
					erase(const_iterator pos);

					KERBAL_CONSTEXPR14
					const_iterator
					erase(const_iterator first, const_iterator last);

					KERBAL_CONSTEXPR14
					size_type
					erase(const key_type & key);

					KERBAL_CONSTEXPR14
					const_iterator
					erase_one(const key_type & key);

					KERBAL_CONSTEXPR14
					void
					clear();

			};


		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_FLAT_ORDERED_BASE_FLAT_ORDERED_BASE_DECL_HPP
