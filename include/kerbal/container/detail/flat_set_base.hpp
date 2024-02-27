/**
 * @file       flat_set_base.hpp
 * @brief
 * @date       2019-12-15
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_FLAT_SET_BASE_HPP
#define KERBAL_CONTAINER_DETAIL_FLAT_SET_BASE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/container/associative_container_facility/associative_unique_insert_r.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/type_traits/enable_if.hpp>

#include <kerbal/container/detail/flat_set_common_base.hpp>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Tp, typename Ordered>
			class flat_set_base: public flat_set_common_base<Tp, Ordered>
			{
				private:
					typedef flat_set_common_base<Tp, Ordered> super;

				public:
					typedef typename super::key_compare			key_compare;
					typedef typename super::key_type			key_type;
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

					typedef typename super::const_iterator				const_iterator;
					typedef typename super::const_reverse_iterator		const_reverse_iterator;
					typedef kerbal::container::associative_unique_insert_r<const_iterator> unique_insert_r;

				protected:
					KERBAL_CONSTEXPR
					flat_set_base() :
							super()
					{
					}

					KERBAL_CONSTEXPR
					explicit flat_set_base(key_compare kc) :
							super(kc)
					{
					}

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					flat_set_base(InputIterator first, InputIterator last,
								  typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
								int
							>::type = 0) :
							super()
					{
						this->assign(first, last);
					}

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					flat_set_base(InputIterator first, InputIterator last, key_compare kc,
								  typename kerbal::type_traits::enable_if<
								kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
								int
							>::type = 0) :
							super(kc)
					{
						this->assign(first, last);
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					flat_set_base(std::initializer_list<value_type> src) :
							flat_set_base(src.begin(), src.end())
					{
					}

					KERBAL_CONSTEXPR14
					flat_set_base(std::initializer_list<value_type> src, key_compare kc) :
							flat_set_base(src.begin(), src.end(), kc)
					{
					}

#			endif

				public:

					KERBAL_CONSTEXPR14
					size_type count(const key_type & key) const
					{
						return this->contains(key) ? 1 : 0;
					}

					KERBAL_CONSTEXPR14
					size_type count(const key_type & key, const_iterator hint) const
					{
						return this->contains(key, hint) ? 1 : 0;
					}

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
					>::type
					assign(InputIterator first, InputIterator last)
					{
						this->clear();
						this->insert(first, last);
					}

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
					>::type
					assign(InputIterator first, InputIterator last, key_compare kc)
					{
						this->clear();
						this->key_comp_obj() = kc;
						this->insert(first, last);
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					void assign(std::initializer_list<value_type> src)
					{
						this->assign(src.begin(), src.end());
					}

					KERBAL_CONSTEXPR14
					void assign(std::initializer_list<value_type> src, key_compare kc)
					{
						this->assign(src.begin(), src.end(), kc);
					}

#			endif

					KERBAL_CONSTEXPR14
					unique_insert_r insert(const_reference src)
					{
						return this->ordered.unique_insert(src);
					}

					KERBAL_CONSTEXPR14
					unique_insert_r insert(const_iterator hint, const_reference src)
					{
						return this->ordered.unique_insert(hint, src);
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					unique_insert_r insert(rvalue_reference src)
					{
						return this->ordered.unique_insert(kerbal::compatibility::move(src));
					}

					KERBAL_CONSTEXPR14
					unique_insert_r insert(const_iterator hint, rvalue_reference src)
					{
						return this->ordered.unique_insert(hint, kerbal::compatibility::move(src));
					}

#			endif

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					void insert(InputIterator first, InputIterator last)
					{
						this->ordered.unique_insert(first, last);
					}

					KERBAL_CONSTEXPR14
					const_iterator erase(const key_type & key)
					{
						return this->ordered.erase_one(key);
					}

					KERBAL_CONSTEXPR14
					const_iterator erase(const_iterator hint, const key_type & key)
					{
						return this->erase(this->find(key, hint));
					}

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_DETAIL_FLAT_SET_BASE_HPP
