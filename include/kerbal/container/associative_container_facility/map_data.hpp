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
#include <kerbal/compatibility/cv_qualified_function.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/add_const.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/utility/compressed_pair.hpp>

#if __cplusplus >= 201703L
#	include <kerbal/type_traits/remove_reference.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/compatibility/move.hpp>
#	include <kerbal/utility/forward.hpp>
#	include <kerbal/utility/piecewise_construct.hpp>
#endif


namespace kerbal
{

	namespace container
	{

		template <typename K, typename M>
		class map_data
		{
			private:
				typedef kerbal::utility::compressed_pair<K, M> cpair;

			protected:
				kerbal::utility::compressed_pair<K, M> k_pair;

			public:
				typedef typename kerbal::type_traits::add_const<typename cpair::first_type>::type key_type;
				typedef typename cpair::second_type mapped_type;

				template <std::size_t I>
				struct value_type
				{
						typedef typename kerbal::type_traits::conditional<
							I == 0,
							key_type,
							typename cpair::template value_type<I>::type
						>::type type;
				};

				template <std::size_t I>
				struct const_reference : cpair::template const_reference<I>
				{
				};

				template <std::size_t I>
				struct reference
				{
						typedef typename kerbal::type_traits::conditional<
							I == 0,
							typename const_reference<I>::type,
							typename cpair::template reference<I>::type
						>::type type;
				};

#		if __cplusplus >= 201103L

				template <std::size_t I>
				struct const_rvalue_reference : cpair::template const_rvalue_reference<I>
				{
				};

				template <std::size_t I>
				struct rvalue_reference
				{
						typedef typename kerbal::type_traits::conditional<
							I == 0,
							typename const_rvalue_reference<I>::type,
							typename cpair::template rvalue_reference<I>::type
						>::type type;
				};

#		endif


#		if __cplusplus >= 201103L

				template <typename K2>
				KERBAL_CONSTEXPR14
				map_data(K2 && k, kerbal::utility::compressed_pair_default_construct_tag tag) :
					k_pair(kerbal::utility::forward<K2>(k), tag)
				{
				}

#		else

				template <typename K2>
				map_data(const K2 & k, kerbal::utility::compressed_pair_default_construct_tag tag) :
					k_pair(k, tag)
				{
				}

#		endif


#		if __cplusplus >= 201103L

				template <typename K2, typename M2>
				KERBAL_CONSTEXPR14
				map_data(K2 && k, M2 && m) :
					k_pair(
						kerbal::utility::forward<K2>(k),
						kerbal::utility::forward<M2>(m)
					)
				{
				}

#		else

				template <typename K2, typename M2>
				map_data(const K2 & k, const M2 & m) :
					k_pair(k, m)
				{
				}

#		endif


#		if __cplusplus >= 201103L

				template <typename Tuple>
				KERBAL_CONSTEXPR14
				map_data(Tuple && tuple) :
					k_pair(tuple)
				{
				}

#		else

				template <typename Tuple>
				map_data(const Tuple & tuple) :
					k_pair(tuple)
				{
				}

#		endif


#		if __cplusplus >= 201103L

				template <typename TupleK, typename TupleV>
				KERBAL_CONSTEXPR
				map_data(kerbal::utility::piecewise_construct_t tag, TupleK && args_for_key, TupleV && args_for_value) :
					k_pair(
						tag,
						kerbal::utility::forward<TupleK>(args_for_key),
						kerbal::utility::forward<TupleV>(args_for_value)
					)
				{
				}

#		endif


				KERBAL_CONSTEXPR14
				const key_type & first() const KERBAL_NOEXCEPT
				{
					return this->k_pair.first();
				}

				KERBAL_CONSTEXPR14
				const key_type & key() const KERBAL_NOEXCEPT
				{
					return this->k_pair.first();
				}

				KERBAL_CONSTEXPR14
				mapped_type & value() KERBAL_NOEXCEPT
				{
					return this->k_pair.second();
				}

				KERBAL_CONSTEXPR14
				const mapped_type & value() const KERBAL_NOEXCEPT
				{
					return this->k_pair.second();
				}


				template <std::size_t I>
				KERBAL_CONSTEXPR14
				typename reference<I>::type
				get() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->k_pair.template get<I>();
				}

				template <std::size_t I>
				KERBAL_CONSTEXPR
				typename const_reference<I>::type
				get() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->k_pair.template get<I>();
				}

#		if __cplusplus >= 201103L

				template <std::size_t I>
				KERBAL_CONSTEXPR14
				typename rvalue_reference<I>::type
				get() && noexcept
				{
					return kerbal::compatibility::move(*this).k_pair.template get<I>();
				}

				template <std::size_t I>
				KERBAL_CONSTEXPR
				typename const_rvalue_reference<I>::type
				get() const && noexcept
				{
					return kerbal::compatibility::move(*this).k_pair.template get<I>();
				}

#		endif

		};


#	if __cplusplus >= 201703L

		template <typename K, typename M>
		map_data(K && k, M && m) ->
		map_data<
			typename kerbal::type_traits::remove_reference<K>::type,
			typename kerbal::type_traits::remove_reference<K>::type
		>;


#	endif // if __cplusplus >= 201703L


	} // namespace container

} // namespace kerbal


#if __cplusplus >= 201103L

#include <kerbal/utility/std_tuple/std_tuple.fwd.hpp>

#include <type_traits> // std::integral_constant


KERBAL_NAMESPACE_STD_BEGIN

	template <typename K, typename M>
	struct tuple_size<kerbal::container::map_data<K, M> > :
		std::integral_constant<std::size_t, 2>
	{
	};

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
