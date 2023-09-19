/**
 * @file       flat_set.decl.hpp
 * @brief
 * @date       2023-09-08
 * @author     Peter
 * @remark     split from kerbal/container/flat_set.hpp
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_FLAT_SET_FLAT_SET_DECL_HPP
#define KERBAL_CONTAINER_FLAT_SET_FLAT_SET_DECL_HPP

#include <kerbal/compare/binary_type_compare.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/container/associative_container_facility/key_extractors/identity_extractor.hpp>
#include <kerbal/container/detail/flat_set_base.hpp>
#include <kerbal/container/flat_ordered.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/utility/compressed_pair.hpp>


namespace kerbal
{

	namespace container
	{

		template <typename Tp, typename KeyCompare = kerbal::compare::binary_type_less<void, void>, typename Allocator = std::allocator<Tp> >
		class flat_set :
				private kerbal::container::flat_ordered<Tp, kerbal::container::identity_extractor<Tp>, KeyCompare, Allocator>
		{
			private:
				typedef kerbal::container::flat_ordered<Tp, kerbal::container::identity_extractor<Tp>, KeyCompare, Allocator> ordered;

			public:
				typedef typename ordered::key_compare		key_compare;
				typedef typename ordered::key_type			key_type;
				typedef typename ordered::value_type		value_type;
				typedef typename ordered::const_type		const_type;
				typedef typename ordered::reference			reference;
				typedef typename ordered::const_reference	const_reference;
				typedef typename ordered::pointer			pointer;
				typedef typename ordered::const_pointer		const_pointer;

#		if __cplusplus >= 201103L
				typedef typename ordered::rvalue_reference			rvalue_reference;
				typedef typename ordered::const_rvalue_reference	const_rvalue_reference;
#		endif

				typedef Allocator					allocator_type;

				typedef typename ordered::size_type					size_type;
				typedef typename ordered::difference_type			difference_type;

				typedef typename ordered::const_iterator			const_iterator;
				typedef typename ordered::const_reverse_iterator	const_reverse_iterator;

			public:

#		if __cplusplus >= 201103L
				flat_set() = default;
#		else
				flat_set() :
						ordered()
				{
				}
#		endif

				KERBAL_CONSTEXPR20
				explicit flat_set(key_compare kc) :
						ordered(kc)
				{
				}

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				flat_set(InputIterator first, InputIterator last,
						typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							int
						>::type = 0) :
						ordered(first, last)
				{
				}

				template <typename InputIterator>
				KERBAL_CONSTEXPR20
				flat_set(InputIterator first, InputIterator last, key_compare kc,
						typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							int
						>::type = 0) :
						ordered(first, last, kc)
				{
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				flat_set(std::initializer_list<value_type> src) :
						ordered(src)
				{
				}

				KERBAL_CONSTEXPR20
				flat_set(std::initializer_list<value_type> src, key_compare kc) :
						ordered(src, kc)
				{
				}

#		endif

				KERBAL_CONSTEXPR20
				void assign(const flat_set & src)
				{
					this->ordered::assign(static_cast<const ordered &>(src));
				}

				KERBAL_CONSTEXPR20
				flat_set& operator=(const flat_set & src)
				{
					this->assign(src);
					return *this;
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				flat_set& operator=(std::initializer_list<value_type> src)
				{
					this->ordered::assign(src);
					return *this;
				}

#		endif

			//===================
			// iterator

			public:

				KERBAL_CONSTEXPR20
				const_iterator begin() const
				{
					return this->ordered::begin();
				}

				KERBAL_CONSTEXPR20
				const_iterator end() const
				{
					return this->ordered::end();
				}

				using ordered::cbegin;
				using ordered::cend;

				KERBAL_CONSTEXPR20
				const_reverse_iterator rbegin() const
				{
					return this->ordered::rbegin();
				}

				KERBAL_CONSTEXPR20
				const_reverse_iterator rend() const
				{
					return this->ordered::rend();
				}

				using ordered::crbegin;
				using ordered::crend;

				KERBAL_CONSTEXPR20
				const_iterator nth(size_type index) const
				{
					return this->ordered::nth(index);
				}

				KERBAL_CONSTEXPR
				size_type index_of(const_iterator it) const
				{
					return this->ordered::index_of(it);
				}

			//===================
			// capacity

				using ordered::size;
				using ordered::max_size;
				using ordered::empty;
				using ordered::reserve;

			//===================
			// lookup

				KERBAL_CONSTEXPR20
				const_iterator lower_bound(const key_type & key) const
				{
					return this->ordered::lower_bound(key);
				}

				KERBAL_CONSTEXPR20
				const_iterator lower_bound(const key_type & key, const_iterator hint) const
				{
					return this->ordered::lower_bound(key, hint);
				}

				KERBAL_CONSTEXPR20
				const_iterator upper_bound(const key_type & key) const
				{
					return this->ordered::upper_bound(key);
				}

				KERBAL_CONSTEXPR20
				const_iterator upper_bound(const key_type & key, const_iterator hint) const
				{
					return this->ordered::upper_bound(key, hint);
				}

				KERBAL_CONSTEXPR20
				kerbal::utility::compressed_pair<const_iterator, const_iterator>
				equal_range(const key_type & key) const
				{
					return this->ordered::equal_range(key);
				}

				KERBAL_CONSTEXPR20
				const_iterator find(const key_type & key) const
				{
					return this->ordered::find(key);
				}

				KERBAL_CONSTEXPR20
				const_iterator find(const key_type & key, const_iterator hint) const
				{
					return this->ordered::find(key, hint);
				}

				KERBAL_CONSTEXPR20
				bool contains(const key_type & key) const
				{
					return this->ordered::contains(key);
				}

				KERBAL_CONSTEXPR20
				bool contains(const key_type & key, const_iterator hint) const
				{
					return this->ordered::contains(key, hint);
				}

			//===================
			// erase

				KERBAL_CONSTEXPR20
				const_iterator erase(const_iterator pos)
				{
					return this->ordered::erase(pos);
				}

				KERBAL_CONSTEXPR20
				const_iterator erase(const_iterator first, const_iterator last)
				{
					return this->ordered::erase(first, last);
				}

				KERBAL_CONSTEXPR20
				void clear()
				{
					this->ordered::clear();
				}

			//===================
			// operation

				KERBAL_CONSTEXPR20
				void swap(flat_set & ano)
				{
					this->ordered::swap(static_cast<ordered &>(ano));
				}

				template <typename Allocator2>
				KERBAL_CONSTEXPR20
				friend bool operator==(const flat_set<Tp, KeyCompare, Allocator> & lhs,
										const flat_set<Tp, KeyCompare, Allocator2> & rhs)
				{
					return lhs.ordered == rhs.ordered;
				}

				template <typename Allocator2>
				KERBAL_CONSTEXPR20
				friend bool operator!=(const flat_set<Tp, KeyCompare, Allocator> & lhs,
										const flat_set<Tp, KeyCompare, Allocator2> & rhs)
				{
					return lhs.ordered != rhs.ordered;
				}

				template <typename Allocator2>
				KERBAL_CONSTEXPR20
				friend bool operator<(const flat_set<Tp, KeyCompare, Allocator> & lhs,
										const flat_set<Tp, KeyCompare, Allocator2> & rhs)
				{
					return lhs.ordered < rhs.ordered;
				}

				template <typename Allocator2>
				KERBAL_CONSTEXPR20
				friend bool operator<=(const flat_set<Tp, KeyCompare, Allocator> & lhs,
										const flat_set<Tp, KeyCompare, Allocator2> & rhs)
				{
					return lhs.ordered <= rhs.ordered;
				}

				template <typename Allocator2>
				KERBAL_CONSTEXPR20
				friend bool operator>(const flat_set<Tp, KeyCompare, Allocator> & lhs,
										const flat_set<Tp, KeyCompare, Allocator2> & rhs)
				{
					return lhs.ordered > rhs.ordered;
				}

				template <typename Allocator2>
				KERBAL_CONSTEXPR20
				friend bool operator>=(const flat_set<Tp, KeyCompare, Allocator> & lhs,
										const flat_set<Tp, KeyCompare, Allocator2> & rhs)
				{
					return lhs.ordered >= rhs.ordered;
				}

		};

	} // namespace container


	namespace algorithm
	{

		template <typename Tp, typename KeyCompare, typename Allocator>
		KERBAL_CONSTEXPR20
		void swap(kerbal::container::flat_set<Tp, KeyCompare, Allocator> & a,
				  kerbal::container::flat_set<Tp, KeyCompare, Allocator> & b)
				KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
		{
			a.swap(b);
		}

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <typename Tp, typename KeyCompare, typename Allocator>
	KERBAL_CONSTEXPR20
	void swap(kerbal::container::flat_set<Tp, KeyCompare, Allocator> & a,
			  kerbal::container::flat_set<Tp, KeyCompare, Allocator> & b)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END

#endif // KERBAL_CONTAINER_FLAT_SET_FLAT_SET_DECL_HPP
