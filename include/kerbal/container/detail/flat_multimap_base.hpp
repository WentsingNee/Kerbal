/**
 * @file       flat_multimap_base.hpp
 * @brief
 * @date       2024-08-22
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_FLAT_MULTIMAP_BASE_HPP
#define KERBAL_CONTAINER_DETAIL_FLAT_MULTIMAP_BASE_HPP

#include <kerbal/container/detail/flat_map_common_base.hpp>

#include <kerbal/assign/ilist.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/type_traits/enable_if.hpp>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Ordered>
			class flat_multimap_base : public flat_map_common_base<Ordered>
			{
				private:
					typedef flat_map_common_base<Ordered> super;

				public:
					typedef typename super::value_type			value_type;
					typedef typename super::const_type			const_type;
					typedef typename super::reference			reference;
					typedef typename super::const_reference		const_reference;
					typedef typename super::pointer				pointer;
					typedef typename super::const_pointer		const_pointer;

#		if __cplusplus >= 201103L
					typedef typename super::rvalue_reference			rvalue_reference;
					typedef typename super::const_rvalue_reference		const_rvalue_reference;
#		endif

					typedef typename super::size_type					size_type;
					typedef typename super::difference_type				difference_type;

					typedef typename super::iterator					iterator;
					typedef typename super::const_iterator				const_iterator;
					typedef typename super::reverse_iterator			reverse_iterator;
					typedef typename super::const_reverse_iterator		const_reverse_iterator;

					typedef typename super::key_type			key_type;
					typedef typename super::key_compare			key_compare;
					typedef typename super::mapped_type			mapped_type;


					template <
						typename Key, typename Result
					>
					struct enable_if_transparent_lookup :
						super::template enable_if_transparent_lookup<Key, Result>
					{
					};


				//===================
				// construct/copy/destroy

				protected:

					KERBAL_CONSTEXPR
					flat_multimap_base() :
						super()
					{
					}

					KERBAL_CONSTEXPR
					explicit
					flat_multimap_base(key_compare kc) :
						super(kc)
					{
					}

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					flat_multimap_base(
						InputIterator first, InputIterator last,
						typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							int
						>::type = 0
					) :
						super()
					{
						this->assign(first, last);
					}

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					flat_multimap_base(
						InputIterator first, InputIterator last,
						key_compare kc,
						typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							int
						>::type = 0
					) :
						super(kc)
					{
						this->assign(first, last);
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					flat_multimap_base(std::initializer_list<value_type> ilist) :
						flat_multimap_base(ilist.begin(), ilist.end())
					{
					}

					KERBAL_CONSTEXPR14
					flat_multimap_base(std::initializer_list<value_type> ilist, key_compare kc) :
						flat_multimap_base(ilist.begin(), ilist.end(), kc)
					{
					}

#			else

					flat_multimap_base(const kerbal::assign::assign_list<void> & ilist) :
						super()
					{
					}

					flat_multimap_base(const kerbal::assign::assign_list<void> & ilist, key_compare kc) :
						super(kc)
					{
					}

					template <typename U>
					flat_multimap_base(const kerbal::assign::assign_list<U> & ilist) :
						super()
					{
						this->assign(ilist.cbegin(), ilist.cend());
					}

					template <typename U>
					flat_multimap_base(const kerbal::assign::assign_list<U> & ilist, key_compare kc) :
						super(kc)
					{
						this->assign(ilist.cbegin(), ilist.cend());
					}

#			endif


				//===================
				// assign

				public:

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
					>::type
					assign(InputIterator first, InputIterator last)
					{
						this->ordered.assign(first, last);
					}

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
					>::type
					assign(InputIterator first, InputIterator last, key_compare kc)
					{
						this->ordered.assign(first, last, kc);
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					void
					assign(std::initializer_list<value_type> ilist)
					{
						this->assign(ilist.begin(), ilist.end());
					}

					KERBAL_CONSTEXPR14
					void
					assign(std::initializer_list<value_type> ilist, key_compare kc)
					{
						this->assign(ilist.begin(), ilist.end(), kc);
					}

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
				// lookup

				public:

					KERBAL_CONSTEXPR14
					size_type
					count(const key_type & key) const
					{
						return this->ordered.count(key);
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						size_type
					>::type
					count(const Key & key) const
					{
						return this->ordered.count(key);
					}

					KERBAL_CONSTEXPR14
					size_type
					count(const_iterator hint, const key_type & key) const
					{
						return this->ordered.count(hint, key);
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						size_type
					>::type
					count(const_iterator hint, const Key & key) const
					{
						return this->ordered.count(hint, key);
					}


				//===================
				// insert

				public:

					KERBAL_CONSTEXPR14
					const_iterator
					insert(const_reference src)
					{
						return this->ordered.insert(src);
					}

					KERBAL_CONSTEXPR14
					const_iterator
					insert(const_iterator hint, const_reference src)
					{
						return this->ordered.insert(hint, src);
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					const_iterator
					insert(rvalue_reference src)
					{
						return this->ordered.insert(kerbal::compatibility::move(src));
					}

					KERBAL_CONSTEXPR14
					const_iterator
					insert(const_iterator hint, rvalue_reference src)
					{
						return this->ordered.insert(hint, kerbal::compatibility::move(src));
					}

#			endif

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					void
					insert(InputIterator first, InputIterator last)
					{
						this->ordered.insert(first, last);
					}


				//===================
				// erase

				public:

					using super::erase;

					KERBAL_CONSTEXPR14
					size_type
					erase(const key_type & key)
					{
						return this->ordered.erase(key);
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						size_type
					>::type
					erase(const Key & key)
					{
						return this->ordered.erase(key);
					}

					KERBAL_CONSTEXPR14
					size_type
					erase(const_iterator hint, const key_type & key)
					{
						return this->ordered.erase(hint, key);
					}

					template <typename Key>
					KERBAL_CONSTEXPR14
					typename enable_if_transparent_lookup<
						Key,
						size_type
					>::type
					erase(const_iterator hint, const Key & key)
					{
						return this->ordered.erase(hint, key);
					}

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_FLAT_MULTIMAP_BASE_HPP
