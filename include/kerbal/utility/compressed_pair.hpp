/**
 * @file       compressed_pair.hpp
 * @brief      
 * @date       2019-10-6
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_COMPRESSED_PAIR_HPP
#define KERBAL_UTILITY_COMPRESSED_PAIR_HPP

#include <kerbal/config/compiler_id.hpp>

#include <kerbal/utility/compressed_pair/compressed_pair.fwd.hpp>
#include <kerbal/utility/std_pair/std_pair.fwd.hpp>

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/assign/generic_assign.hpp>
#include <kerbal/compatibility/method_overload_tag.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/tmp/type_vector.hpp>
#include <kerbal/type_traits/is_same.hpp>
#include <kerbal/utility/in_place.hpp>
#include <kerbal/utility/member_compress_helper.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/is_nothrow_constructible.hpp>
#	include <kerbal/type_traits/tribool_constant.hpp>
#	include <kerbal/utility/declval.hpp>
#	include <kerbal/utility/forward.hpp>
#endif


namespace kerbal
{

	namespace utility
	{

		struct compressed_pair_default_construct_tag
		{
		};

		template <typename T, typename U>
		class compressed_pair :
			public kerbal::utility::member_compress_helper<T, 0>,
			public kerbal::utility::member_compress_helper<U, kerbal::type_traits::is_same<T, U>::value ? 1 : 0>
		{
			private:
				typedef kerbal::utility::member_compress_helper<T, 0> super0;
				typedef kerbal::utility::member_compress_helper<U, kerbal::type_traits::is_same<T, U>::value ? 1 : 0> super1;

				template <std::size_t I>
				struct super
				{
					private:
						KERBAL_STATIC_ASSERT(I < 2, "Index out of range");
						typedef kerbal::tmp::type_vector<super0, super1> vec;

					public:
						typedef typename kerbal::tmp::type_vector_at<vec, I>::result type;
				};

			public:
				typedef T first_type;
				typedef U second_type;

				typedef typename super0::IS_COMPRESSED		is_first_compressed;
				typedef typename super1::IS_COMPRESSED		is_second_compressed;

				typedef typename super0::reference				first_type_reference;
				typedef typename super1::reference				second_type_reference;
				typedef typename super0::const_reference		first_type_const_reference;
				typedef typename super1::const_reference		second_type_const_reference;

#		if __cplusplus >= 201103L
				typedef typename super0::rvalue_reference			first_type_rvalue_reference;
				typedef typename super1::rvalue_reference			second_type_rvalue_reference;
				typedef typename super0::const_rvalue_reference		first_type_const_rvalue_reference;
				typedef typename super1::const_rvalue_reference		second_type_const_rvalue_reference;
#		endif


				template <std::size_t I>
				struct value_type
				{
					private:
						KERBAL_STATIC_ASSERT(I < 2, "Index out of range");
						typedef kerbal::tmp::type_vector<T, U> vec;

					public:
						typedef typename kerbal::tmp::type_vector_at<vec, I>::result type;
				};

				template <std::size_t I>
				struct reference
				{
					private:
						KERBAL_STATIC_ASSERT(I < 2, "Index out of range");

					public:
						typedef typename super<I>::type::reference type;
				};

				template <std::size_t I>
				struct const_reference
				{
					private:
						KERBAL_STATIC_ASSERT(I < 2, "Index out of range");

					public:
						typedef typename super<I>::type::const_reference type;
				};

#		if __cplusplus >= 201103L

				template <std::size_t I>
				struct rvalue_reference
				{
					private:
						KERBAL_STATIC_ASSERT(I < 2, "Index out of range");

					public:
						typedef typename super<I>::type::rvalue_reference type;
				};

				template <std::size_t I>
				struct const_rvalue_reference
				{
					private:
						KERBAL_STATIC_ASSERT(I < 2, "Index out of range");

					public:
						typedef typename super<I>::type::const_rvalue_reference type;
				};

#		endif

			public:

				KERBAL_CONSTEXPR
				compressed_pair()
					KERBAL_CONDITIONAL_NOEXCEPT((
						kerbal::type_traits::tribool_conjunction<
							kerbal::type_traits::try_test_is_nothrow_constructible<
								super0, kerbal::utility::in_place_t
							>,
							kerbal::type_traits::try_test_is_nothrow_constructible<
								super1, kerbal::utility::in_place_t
							>
						>::result::IS_TRUE::value
					)) :
					super0(kerbal::utility::in_place_t()),
					super1(kerbal::utility::in_place_t())
				{
				}

#		if __cplusplus < 201103L

				KERBAL_CONSTEXPR
				compressed_pair(first_type_const_reference first, second_type_const_reference second) :
					super0(kerbal::utility::in_place_t(), first),
					super1(kerbal::utility::in_place_t(), second)
				{
				}

				KERBAL_CONSTEXPR
				compressed_pair(compressed_pair_default_construct_tag, second_type_const_reference second) :
					super0(kerbal::utility::in_place_t()),
					super1(kerbal::utility::in_place_t(), second)
				{
				}

				KERBAL_CONSTEXPR
				compressed_pair(first_type_const_reference first, compressed_pair_default_construct_tag) :
					super0(kerbal::utility::in_place_t(), first),
					super1(kerbal::utility::in_place_t())
				{
				}

				template <typename T2, typename U2>
				KERBAL_CONSTEXPR
				compressed_pair(const T2 & first, const U2 & second) :
					super0(kerbal::utility::in_place_t(), first),
					super1(kerbal::utility::in_place_t(), second)
				{
				}

				template <typename U2>
				KERBAL_CONSTEXPR
				compressed_pair(compressed_pair_default_construct_tag, const U2 & second) :
					super0(kerbal::utility::in_place_t()),
					super1(kerbal::utility::in_place_t(), second)
				{
				}

				template <typename T2>
				KERBAL_CONSTEXPR
				compressed_pair(const T2 & first, compressed_pair_default_construct_tag) :
					super0(kerbal::utility::in_place_t(), first),
					super1(kerbal::utility::in_place_t())
				{
				}

#		else

				template <typename T2, typename U2>
				KERBAL_CONSTEXPR
				compressed_pair(T2 && first, U2 && second)
					KERBAL_CONDITIONAL_NOEXCEPT((
						kerbal::type_traits::tribool_conjunction<
							kerbal::type_traits::try_test_is_nothrow_constructible<
								super0, kerbal::utility::in_place_t, T2 &&
							>,
							kerbal::type_traits::try_test_is_nothrow_constructible<
								super1, kerbal::utility::in_place_t, U2 &&
							>
						>::result::IS_TRUE::value
					)) :
					super0(kerbal::utility::in_place_t(), kerbal::utility::forward<T2>(first)),
					super1(kerbal::utility::in_place_t(), kerbal::utility::forward<U2>(second))
				{
				}

				template <typename U2>
				KERBAL_CONSTEXPR
				compressed_pair(compressed_pair_default_construct_tag, U2 && second)
					KERBAL_CONDITIONAL_NOEXCEPT((
						kerbal::type_traits::tribool_conjunction<
							kerbal::type_traits::try_test_is_nothrow_constructible<
								super0, kerbal::utility::in_place_t
							>,
							kerbal::type_traits::try_test_is_nothrow_constructible<
								super1, kerbal::utility::in_place_t, U2 &&
							>
						>::result::IS_TRUE::value
					)) :
					super0(kerbal::utility::in_place_t()),
					super1(kerbal::utility::in_place_t(), kerbal::utility::forward<U2>(second))
				{
				}

				template <typename T2>
				KERBAL_CONSTEXPR
				compressed_pair(T2 && first, compressed_pair_default_construct_tag)
					KERBAL_CONDITIONAL_NOEXCEPT((
						kerbal::type_traits::tribool_conjunction<
							kerbal::type_traits::try_test_is_nothrow_constructible<
								super0, kerbal::utility::in_place_t, T2 &&
							>,
							kerbal::type_traits::try_test_is_nothrow_constructible<
								super1, kerbal::utility::in_place_t
							>
						>::result::IS_TRUE::value
					)) :
					super0(kerbal::utility::in_place_t(), kerbal::utility::forward<T2>(first)),
					super1(kerbal::utility::in_place_t())
				{
				}

#		endif

				template <typename T2, typename U2>
				KERBAL_CONSTEXPR
				explicit
				compressed_pair(const kerbal::utility::compressed_pair<T2, U2> & p)
					KERBAL_CONDITIONAL_NOEXCEPT((
						kerbal::type_traits::tribool_conjunction<
							kerbal::type_traits::try_test_is_nothrow_constructible<
								super0,
								kerbal::utility::in_place_t,
								decltype(kerbal::utility::declval<const kerbal::utility::compressed_pair<T2, U2> &>().first())
							>,
							kerbal::type_traits::try_test_is_nothrow_constructible<
								super1,
								kerbal::utility::in_place_t,
								decltype(kerbal::utility::declval<const kerbal::utility::compressed_pair<T2, U2> &>().second())
							>
						>::result::IS_TRUE::value
					)) :
					super0(kerbal::utility::in_place_t(), p.first()),
					super1(kerbal::utility::in_place_t(), p.second())
				{
				}

				template <typename T2, typename U2>
				KERBAL_CONSTEXPR
				explicit
				compressed_pair(const std::pair<T2, U2> & p)
					KERBAL_CONDITIONAL_NOEXCEPT((
						kerbal::type_traits::tribool_conjunction<
							kerbal::type_traits::try_test_is_nothrow_constructible<
								super0,
								kerbal::utility::in_place_t,
								decltype(kerbal::utility::declval<const std::pair<T2, U2> &>().first)
							>,
							kerbal::type_traits::try_test_is_nothrow_constructible<
								super1,
								kerbal::utility::in_place_t,
								decltype(kerbal::utility::declval<const std::pair<T2, U2> &>().second)
							>
						>::result::IS_TRUE::value
					)) :
					super0(kerbal::utility::in_place_t(), p.first),
					super1(kerbal::utility::in_place_t(), p.second)
				{
				}


#		if __cplusplus >= 201103L

				template <typename T2, typename U2>
				KERBAL_CONSTEXPR14
				explicit
				compressed_pair(kerbal::utility::compressed_pair<T2, U2> && p)
					KERBAL_CONDITIONAL_NOEXCEPT((
						kerbal::type_traits::tribool_conjunction<
							kerbal::type_traits::try_test_is_nothrow_constructible<
								super0,
								kerbal::utility::in_place_t,
								decltype(kerbal::compatibility::move(p).first())
							>,
							kerbal::type_traits::try_test_is_nothrow_constructible<
								super1,
								kerbal::utility::in_place_t,
								decltype(kerbal::compatibility::move(p).second())
							>
						>::result::IS_TRUE::value
					)) :
					super0(kerbal::utility::in_place_t(), kerbal::compatibility::move(p).first()),
					super1(kerbal::utility::in_place_t(), kerbal::compatibility::move(p).second())
				{
				}

				template <typename T2, typename U2>
				KERBAL_CONSTEXPR14
				explicit
				compressed_pair(std::pair<T2, U2> && p)
					KERBAL_CONDITIONAL_NOEXCEPT((
						kerbal::type_traits::tribool_conjunction<
							kerbal::type_traits::try_test_is_nothrow_constructible<
								super0,
								kerbal::utility::in_place_t,
								decltype(kerbal::compatibility::move(p).first)
							>,
							kerbal::type_traits::try_test_is_nothrow_constructible<
								super1,
								kerbal::utility::in_place_t,
								decltype(kerbal::compatibility::move(p).second)
							>
						>::result::IS_TRUE::value
					)) :
					super0(kerbal::utility::in_place_t(), kerbal::compatibility::move(p).first),
					super1(kerbal::utility::in_place_t(), kerbal::compatibility::move(p).second)
				{
				}

#		endif


#		if __cplusplus >= 201103L

				template <typename Tuple1, typename Tuple2>
				KERBAL_CONSTEXPR
				compressed_pair(kerbal::utility::piecewise_construct_t tag, Tuple1 && args_for_first, Tuple2 && args_for_second) :
					super0(tag, kerbal::utility::forward<Tuple1>(args_for_first)),
					super1(tag, kerbal::utility::forward<Tuple2>(args_for_second))
				{
				}

#		endif


				template <typename T2, typename U2>
				KERBAL_CONSTEXPR14
				compressed_pair & operator=(const kerbal::utility::compressed_pair<T2, U2> & p)
				{
					kerbal::assign::generic_assign(this->first(), p.first());
					kerbal::assign::generic_assign(this->second(), p.second());
					return *this;
				}

#		if __cplusplus >= 201103L

				template <typename T2, typename U2>
				KERBAL_CONSTEXPR14
				compressed_pair & operator=(kerbal::utility::compressed_pair<T2, U2> && p)
				{
					kerbal::assign::generic_assign(this->first(), kerbal::compatibility::move(p).first());
					kerbal::assign::generic_assign(this->second(), kerbal::compatibility::move(p).second());
					return *this;
				}

#		endif

			public:

				KERBAL_CONSTEXPR14
				first_type_reference first() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return super0::member();
				}

				KERBAL_CONSTEXPR14
				second_type_reference second() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return super1::member();
				}

				KERBAL_CONSTEXPR
				first_type_const_reference first() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return super0::member();
				}

				KERBAL_CONSTEXPR
				second_type_const_reference second() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return super1::member();
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				first_type_rvalue_reference first() && KERBAL_NOEXCEPT
				{
					return kerbal::compatibility::move(*this).super0::member();
				}

				KERBAL_CONSTEXPR14
				second_type_rvalue_reference second() && KERBAL_NOEXCEPT
				{
					return kerbal::compatibility::move(*this).super1::member();
				}

#			if KERBAL_HAS_CONST_RVALUE_REFERENCE_MEMBER_SUPPORT

				KERBAL_CONSTEXPR
				first_type_const_rvalue_reference first() const && KERBAL_NOEXCEPT
				{
					return kerbal::compatibility::move(*this).super0::member();
				}

				KERBAL_CONSTEXPR
				second_type_const_rvalue_reference second() const && KERBAL_NOEXCEPT
				{
					return kerbal::compatibility::move(*this).super1::member();
				}

#			endif

#		endif

				template <std::size_t I>
				KERBAL_CONSTEXPR14
				typename reference<I>::type
				get() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return super<I>::type::member();
				}

				template <std::size_t I>
				KERBAL_CONSTEXPR
				typename const_reference<I>::type
				get() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return super<I>::type::member();
				}

#		if __cplusplus >= 201103L

				template <std::size_t I>
				KERBAL_CONSTEXPR14
				typename rvalue_reference<I>::type
				get() && noexcept
				{
					return kerbal::compatibility::move(*this).super<I>::type::member();
				}

				template <std::size_t I>
				KERBAL_CONSTEXPR
				typename const_rvalue_reference<I>::type
				get() const && noexcept
				{
					return kerbal::compatibility::move(*this).super<I>::type::member();
				}

#		endif

				KERBAL_CONSTEXPR14
				void swap(compressed_pair & other)
				{
					kerbal::algorithm::swap(this->first(), other.first());
					kerbal::algorithm::swap(this->second(), other.second());
				}

		};

		template <typename T, typename U>
		KERBAL_CONSTEXPR
		bool operator==(
			const kerbal::utility::compressed_pair<T, U> & lhs,
			const kerbal::utility::compressed_pair<T, U> & rhs
		)
			KERBAL_CONDITIONAL_NOEXCEPT(
				noexcept(static_cast<bool>(lhs.first() == rhs.first())) &&
				noexcept(static_cast<bool>(lhs.second() == rhs.second()))
			)
		{
			return
				static_cast<bool>(lhs.first() == rhs.first()) &&
				static_cast<bool>(lhs.second() == rhs.second());
		}

		template <typename T, typename U>
		KERBAL_CONSTEXPR
		bool operator!=(
			const kerbal::utility::compressed_pair<T, U> & lhs,
			const kerbal::utility::compressed_pair<T, U> & rhs
		)
			KERBAL_CONDITIONAL_NOEXCEPT(
				noexcept(static_cast<bool>(lhs.first() != rhs.first())) &&
				noexcept(static_cast<bool>(lhs.second() != rhs.second()))
			)
		{
			return
				static_cast<bool>(lhs.first() != rhs.first()) ||
				static_cast<bool>(lhs.second() != rhs.second());
		}

		template <typename T, typename U>
		KERBAL_CONSTEXPR
		bool operator<(
			const kerbal::utility::compressed_pair<T, U> & lhs,
			const kerbal::utility::compressed_pair<T, U> & rhs
		)
			KERBAL_CONDITIONAL_NOEXCEPT(
				noexcept(static_cast<bool>(lhs.first() < rhs.first())) &&
				noexcept(!static_cast<bool>(rhs.first() < lhs.first())) &&
				noexcept(static_cast<bool>(lhs.second() < rhs.second()))
			)
		{
			return
				static_cast<bool>(lhs.first() < rhs.first()) ||
				(
					!static_cast<bool>(rhs.first() < lhs.first()) &&
					static_cast<bool>(lhs.second() < rhs.second())
				);
		}

		template <typename T, typename U>
		KERBAL_CONSTEXPR
		bool operator>(
			const kerbal::utility::compressed_pair<T, U> & lhs,
			const kerbal::utility::compressed_pair<T, U> & rhs
		)
		{
			return
				static_cast<bool>(lhs.first() > rhs.first()) ||
				(
					!static_cast<bool>(rhs.first() > lhs.first()) &&
					static_cast<bool>(lhs.second() > rhs.second())
				);
		}

		template <typename T, typename U>
		KERBAL_CONSTEXPR
		bool operator<=(
			const kerbal::utility::compressed_pair<T, U> & lhs,
			const kerbal::utility::compressed_pair<T, U> & rhs
		)
		{
			return
				static_cast<bool>(lhs.first() <= rhs.first()) &&
				(
					!static_cast<bool>(rhs.first() <= lhs.first()) ||
					static_cast<bool>(lhs.second() <= rhs.second())
				);
		}

		template <typename T, typename U>
		KERBAL_CONSTEXPR
		bool operator>=(
			const kerbal::utility::compressed_pair<T, U> & lhs,
			const kerbal::utility::compressed_pair<T, U> & rhs
		)
		{
			return
				static_cast<bool>(lhs.first() >= rhs.first()) &&
				(
					!static_cast<bool>(rhs.first() >= lhs.first()) ||
					static_cast<bool>(lhs.second() >= rhs.second())
				);
		}

		template <typename T, typename U>
		KERBAL_CONSTEXPR
		kerbal::utility::compressed_pair<T, U>
		make_compressed_pair(const T & first, const U & second)
			KERBAL_CONDITIONAL_NOEXCEPT((
				kerbal::type_traits::try_test_is_nothrow_constructible<
					kerbal::utility::compressed_pair<T, U>, const T &, const U &
				>::IS_TRUE::value
			))
		{
			return kerbal::utility::compressed_pair<T, U>(first, second);
		}

#	if __cplusplus >= 201703L

		template <typename T, typename U>
		compressed_pair(const T &, const U &) ->
		compressed_pair<T, U>;

#	endif

	} // namespace utility

} // namespace kerbal


namespace kerbal
{

	namespace algorithm
	{

		template <typename T, typename U>
		KERBAL_CONSTEXPR20
		void swap(
			kerbal::utility::compressed_pair<T, U> & a,
			kerbal::utility::compressed_pair<T, U> & b
		)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
		{
			a.swap(b);
		}

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <typename T, typename U>
	KERBAL_CONSTEXPR20
	void swap(
		kerbal::utility::compressed_pair<T, U> & a,
		kerbal::utility::compressed_pair<T, U> & b
	)
		KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END


#if __cplusplus >= 201103L

#include <kerbal/utility/std_tuple/std_tuple.fwd.hpp>

#include <type_traits> // std::integral_constant


KERBAL_NAMESPACE_STD_BEGIN

	template <typename T, typename U>
	struct tuple_size<kerbal::utility::compressed_pair<T, U> > :
		std::integral_constant<std::size_t, 2>
	{
	};

	template <std::size_t I, typename T, typename U>
	struct tuple_element<I, kerbal::utility::compressed_pair<T, U> > :
		kerbal::utility::compressed_pair<T, U>::template value_type<I>
	{
	};

	template <std::size_t I, typename T, typename U>
	KERBAL_CONSTEXPR14
	typename kerbal::utility::compressed_pair<T, U>::template reference<I>::type
	get(kerbal::utility::compressed_pair<T, U> & pair) KERBAL_NOEXCEPT
	{
		return pair.template get<I>();
	}

	template <std::size_t I, typename T, typename U>
	KERBAL_CONSTEXPR
	typename kerbal::utility::compressed_pair<T, U>::template const_reference<I>::type
	get(const kerbal::utility::compressed_pair<T, U> & pair) KERBAL_NOEXCEPT
	{
		return pair.template get<I>();
	}

	template <std::size_t I, typename T, typename U>
	KERBAL_CONSTEXPR14
	typename kerbal::utility::compressed_pair<T, U>::template rvalue_reference<I>::type
	get(kerbal::utility::compressed_pair<T, U> && pair) KERBAL_NOEXCEPT
	{
		return kerbal::compatibility::move(pair).template get<I>();
	}

	template <std::size_t I, typename T, typename U>
	KERBAL_CONSTEXPR
	typename kerbal::utility::compressed_pair<T, U>::template const_rvalue_reference<I>::type
	get(const kerbal::utility::compressed_pair<T, U> && pair) KERBAL_NOEXCEPT
	{
		return kerbal::compatibility::move(pair).template get<I>();
	}

KERBAL_NAMESPACE_STD_END

#endif


#endif // KERBAL_UTILITY_COMPRESSED_PAIR_HPP
