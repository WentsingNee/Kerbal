/**
 * @file       static_flat_map.hpp
 * @brief
 * @date       2019-8-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_STATIC_FLAT_MAP_HPP
#define KERBAL_CONTAINER_STATIC_FLAT_MAP_HPP

#include <kerbal/container/detail/flat_map_base.hpp>
#include <kerbal/container/detail/key_of_value_extractor.hpp>

#include <kerbal/container/static_ordered.hpp>

namespace kerbal
{

	namespace container
	{

		template <typename Key, typename Value, std::size_t N, typename KeyCompare = std::less<Key> >
		class static_flat_map
				: public kerbal::container::detail::flat_map_base<Key, Value,
						kerbal::container::static_ordered<
								std::pair<Key, Value>, N, Key, KeyCompare,
								detail::default_map_key_extractor<std::pair<Key, Value>, Key>
						>
					>
		{
			private:
				typedef kerbal::container::static_ordered<
								std::pair<Key, Value>, N, Key, KeyCompare,
								detail::default_map_key_extractor<std::pair<Key, Value>, Key>
				> Ordered;
				typedef kerbal::container::detail::flat_map_base<Key, Value, Ordered> super;

			public:
				typedef typename super::key_compare			key_compare;
				typedef typename super::key_type			key_type;
				typedef typename super::mapped_type			mapped_type;
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

			public:

				KERBAL_CONSTEXPR
				static_flat_map() :
						super()
				{
				}

				KERBAL_CONSTEXPR
				explicit static_flat_map(key_compare kc) :
						super(kc)
				{
				}

				template <typename InputIterator>
				KERBAL_CONSTEXPR14
				static_flat_map(InputIterator first, InputIterator last,
						typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							int
						>::type = 0) :
						super(first, last)
				{
				}

				template <typename InputIterator>
				KERBAL_CONSTEXPR14
				static_flat_map(InputIterator first, InputIterator last, key_compare kc,
						typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							int
						>::type = 0) :
						super(first, last, kc)
				{
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				static_flat_map(std::initializer_list<value_type> src) :
						super(src)
				{
				}

				KERBAL_CONSTEXPR14
				static_flat_map(std::initializer_list<value_type> src, key_compare kc) :
						super(src, kc)
				{
				}

#		endif

				KERBAL_CONSTEXPR14
				void assign(const static_flat_map & src)
				{
					this->ordered.assign(src.ordered);
				}

				KERBAL_CONSTEXPR14
				static_flat_map& operator=(const static_flat_map & src)
				{
					this->assign(src);
					return *this;
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				static_flat_map& operator=(std::initializer_list<value_type> src)
				{
					this->super::assign(src);
					return *this;
				}

#		endif

				KERBAL_CONSTEXPR
				bool full() const
				{
					return this->ordered.full();
				}

				KERBAL_CONSTEXPR14
				void swap(static_flat_map & ano)
				{
					this->ordered.swap(ano.ordered);
				}

				template <size_t M>
				KERBAL_CONSTEXPR14
				friend bool operator==(const static_flat_map<Key, Value, M, KeyCompare> & lhs,
										const static_flat_map<Key, Value, N, KeyCompare> & rhs)
				{
					return lhs.ordered == rhs.ordered;
				}

				template <size_t M>
				KERBAL_CONSTEXPR14
				friend bool operator!=(const static_flat_map<Key, Value, M, KeyCompare> & lhs,
										const static_flat_map<Key, Value, N, KeyCompare> & rhs)
				{
					return lhs.ordered != rhs.ordered;
				}

				template <size_t M>
				KERBAL_CONSTEXPR14
				friend bool operator<(const static_flat_map<Key, Value, M, KeyCompare> & lhs,
										const static_flat_map<Key, Value, N, KeyCompare> & rhs)
				{
					return lhs.ordered < rhs.ordered;
				}

				template <size_t M>
				KERBAL_CONSTEXPR14
				friend bool operator<=(const static_flat_map<Key, Value, M, KeyCompare> & lhs,
										const static_flat_map<Key, Value, N, KeyCompare> & rhs)
				{
					return lhs.ordered <= rhs.ordered;
				}

				template <size_t M>
				KERBAL_CONSTEXPR14
				friend bool operator>(const static_flat_map<Key, Value, M, KeyCompare> & lhs,
										const static_flat_map<Key, Value, N, KeyCompare> & rhs)
				{
					return lhs.ordered > rhs.ordered;
				}

				template <size_t M>
				KERBAL_CONSTEXPR14
				friend bool operator>=(const static_flat_map<Key, Value, M, KeyCompare> & lhs,
										const static_flat_map<Key, Value, N, KeyCompare> & rhs)
				{
					return lhs.ordered >= rhs.ordered;
				}

		};

		template <typename Key, typename Value, std::size_t N, typename KeyCompare = std::less<Key> >
		class static_flat_multimap
				: public kerbal::container::detail::flat_multimap_base<Key, Value,
						kerbal::container::static_ordered<
								std::pair<Key, Value>, N, Key, KeyCompare,
								detail::default_map_key_extractor<std::pair<Key, Value>, Key>
						>
				>
		{
			private:
				typedef kerbal::container::static_ordered<
						std::pair<Key, Value>, N, Key, KeyCompare,
						detail::default_map_key_extractor<std::pair<Key, Value>, Key>
				> Ordered;
				typedef kerbal::container::detail::flat_multimap_base<Key, Value, Ordered> super;

			public:
				typedef typename super::key_compare			key_compare;
				typedef typename super::key_type			key_type;
				typedef typename super::mapped_type			mapped_type;
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

			public:

				KERBAL_CONSTEXPR
				static_flat_multimap() :
						super()
				{
				}

				KERBAL_CONSTEXPR
				explicit static_flat_multimap(key_compare kc) :
						super(kc)
				{
				}

				template <typename InputIterator>
				KERBAL_CONSTEXPR14
				static_flat_multimap(InputIterator first, InputIterator last,
						typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							int
						>::type = 0) :
						super(first, last)
				{
				}

				template <typename InputIterator>
				KERBAL_CONSTEXPR14
				static_flat_multimap(InputIterator first, InputIterator last, key_compare kc,
						typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							int
						>::type = 0) :
						super(first, last, kc)
				{
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				static_flat_multimap(std::initializer_list<value_type> src) :
						super(src)
				{
				}

				KERBAL_CONSTEXPR14
				static_flat_multimap(std::initializer_list<value_type> src, key_compare kc) :
						super(src, kc)
				{
				}

#		endif

				KERBAL_CONSTEXPR14
				void assign(const static_flat_multimap & src)
				{
					this->ordered.assign(src.ordered);
				}

				KERBAL_CONSTEXPR14
				static_flat_multimap& operator=(const static_flat_multimap & src)
				{
					this->assign(src);
					return *this;
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				static_flat_multimap& operator=(std::initializer_list<value_type> src)
				{
					this->super::assign(src);
					return *this;
				}

#		endif

				KERBAL_CONSTEXPR
				bool full() const
				{
					return this->ordered.full();
				}

				KERBAL_CONSTEXPR14
				void swap(static_flat_multimap & ano)
				{
					this->ordered.swap(ano.ordered);
				}

				template <size_t M>
				KERBAL_CONSTEXPR14
				friend bool operator==(const static_flat_multimap<Key, Value, M, KeyCompare> & lhs,
										const static_flat_multimap<Key, Value, N, KeyCompare> & rhs)
				{
					return lhs.ordered == rhs.ordered;
				}

				template <size_t M>
				KERBAL_CONSTEXPR14
				friend bool operator!=(const static_flat_multimap<Key, Value, M, KeyCompare> & lhs,
										const static_flat_multimap<Key, Value, N, KeyCompare> & rhs)
				{
					return lhs.ordered != rhs.ordered;
				}

				template <size_t M>
				KERBAL_CONSTEXPR14
				friend bool operator<(const static_flat_multimap<Key, Value, M, KeyCompare> & lhs,
										const static_flat_multimap<Key, Value, N, KeyCompare> & rhs)
				{
					return lhs.ordered < rhs.ordered;
				}

				template <size_t M>
				KERBAL_CONSTEXPR14
				friend bool operator<=(const static_flat_multimap<Key, Value, M, KeyCompare> & lhs,
										const static_flat_multimap<Key, Value, N, KeyCompare> & rhs)
				{
					return lhs.ordered <= rhs.ordered;
				}

				template <size_t M>
				KERBAL_CONSTEXPR14
				friend bool operator>(const static_flat_multimap<Key, Value, M, KeyCompare> & lhs,
										const static_flat_multimap<Key, Value, N, KeyCompare> & rhs)
				{
					return lhs.ordered > rhs.ordered;
				}

				template <size_t M>
				KERBAL_CONSTEXPR14
				friend bool operator>=(const static_flat_multimap<Key, Value, M, KeyCompare> & lhs,
										const static_flat_multimap<Key, Value, N, KeyCompare> & rhs)
				{
					return lhs.ordered >= rhs.ordered;
				}

		};

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_STATIC_FLAT_MAP_HPP
