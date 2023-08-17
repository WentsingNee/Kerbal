/**
 * @file       map_data.hpp
 * @brief
 * @date       2022-11-22
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_ASSOCIATIVE_CONTAINER_FACILITY_MAP_DATA_HPP
#define KERBAL_CONTAINER_ASSOCIATIVE_CONTAINER_FACILITY_MAP_DATA_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/utility/compressed_pair.hpp>

#if __cplusplus >= 201703L
#	include <kerbal/type_traits/remove_reference.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/compatibility/move.hpp>
#	include <kerbal/utility/forward.hpp>
#endif


namespace kerbal
{

	namespace container
	{

		template <typename K, typename M>
		class map_data :
				public kerbal::utility::compressed_pair<K, M>
		{
			private:
				typedef kerbal::utility::compressed_pair<K, M> super;

			public:
				typedef typename super::first_type key_type;
				typedef typename super::second_type mapped_type;

				template <std::size_t I>
				struct value_type : super::template value_type<I>
				{
				};

				template <std::size_t I>
				struct reference : super::template reference<I>
				{
				};

				template <std::size_t I>
				struct const_reference : super::template const_reference<I>
				{
				};

#		if __cplusplus >= 201103L

				template <std::size_t I>
				struct rvalue_reference : super::template rvalue_reference<I>
				{
				};

				template <std::size_t I>
				struct const_rvalue_reference : super::template const_rvalue_reference<I>
				{
				};

#		endif


#		if __cplusplus >= 201103L

				template <typename K2>
				KERBAL_CONSTEXPR14
				map_data(K2 && k, kerbal::utility::compressed_pair_default_construct_tag tag) :
						super(kerbal::utility::forward<K2>(k), tag)
				{
				}

#		else

				template <typename K2>
				map_data(const K2 & k, kerbal::utility::compressed_pair_default_construct_tag tag) :
						super(k, tag)
				{
				}

#		endif


#		if __cplusplus >= 201103L

				template <typename K2, typename M2>
				KERBAL_CONSTEXPR14
				map_data(K2 && k, M2 && m) :
						super(
							kerbal::utility::forward<K2>(k),
							kerbal::utility::forward<M2>(m)
						)
				{
				}

#		else

				template <typename K2, typename M2>
				map_data(const K2 & k, const M2 & m) :
						super(k, m)
				{
				}

#		endif


#		if __cplusplus >= 201103L

				template <typename Tuple>
				KERBAL_CONSTEXPR14
				map_data(Tuple && tuple) :
						super(tuple)
				{
				}

#		else

				template <typename Tuple>
				map_data(const Tuple & tuple) :
						super(tuple)
				{
				}

#		endif


				KERBAL_CONSTEXPR14
				key_type & key() KERBAL_NOEXCEPT
				{
					return super::first();
				}

				KERBAL_CONSTEXPR14
				const key_type & key() const KERBAL_NOEXCEPT
				{
					return super::first();
				}

				KERBAL_CONSTEXPR14
				mapped_type & value() KERBAL_NOEXCEPT
				{
					return super::second();
				}

				KERBAL_CONSTEXPR14
				const mapped_type & value() const KERBAL_NOEXCEPT
				{
					return super::second();
				}

		};


#	if __cplusplus >= 201703L

		template <typename K, typename M>
		map_data(K && k, M && m)
		-> map_data<
				typename kerbal::type_traits::remove_reference<K>::type,
				typename kerbal::type_traits::remove_reference<K>::type
		>;


#	endif // if __cplusplus >= 201703L


	} // namespace container

} // namespace kerbal


#if __cplusplus >= 201103L

#include <type_traits> // std::integral_constant

KERBAL_NAMESPACE_STD_BEGIN

	template <typename T>
	struct tuple_size;

	template <typename K, typename M>
	struct tuple_size<kerbal::container::map_data<K, M> > :
			std::integral_constant<std::size_t, 2>
	{
	};

	template <std::size_t I, typename T>
	struct tuple_element;

	template <std::size_t I, typename K, typename M>
	struct tuple_element<I, kerbal::container::map_data<K, M> > :
			kerbal::container::map_data<K, M>::template value_type<I>
	{
	};

	template <std::size_t I, typename K, typename M>
	KERBAL_CONSTEXPR14
	typename kerbal::container::map_data<K, M>::template reference<I>::type
	get(kerbal::container::map_data<K, M> & pair) KERBAL_NOEXCEPT
	{
		return pair.template get<I>();
	}

	template <std::size_t I, typename K, typename M>
	KERBAL_CONSTEXPR
	typename kerbal::container::map_data<K, M>::template const_reference<I>::type
	get(const kerbal::container::map_data<K, M> & pair) KERBAL_NOEXCEPT
	{
		return pair.template get<I>();
	}

	template <std::size_t I, typename K, typename M>
	KERBAL_CONSTEXPR14
	typename kerbal::container::map_data<K, M>::template rvalue_reference<I>::type
	get(kerbal::container::map_data<K, M> && pair) KERBAL_NOEXCEPT
	{
		return kerbal::compatibility::move(pair).template get<I>();
	}

	template <std::size_t I, typename K, typename M>
	KERBAL_CONSTEXPR
	typename kerbal::container::map_data<K, M>::template const_rvalue_reference<I>::type
	get(const kerbal::container::map_data<K, M> && pair) KERBAL_NOEXCEPT
	{
		return kerbal::compatibility::move(pair).template get<I>();
	}

KERBAL_NAMESPACE_STD_END

#endif


#endif // KERBAL_CONTAINER_ASSOCIATIVE_CONTAINER_FACILITY_MAP_DATA_HPP
