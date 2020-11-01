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

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/method_overload_tag.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/is_same.hpp>
#include <kerbal/utility/member_compress_helper.hpp>

#if __cplusplus >= 201103L
#   include <kerbal/utility/forward.hpp>
#endif

#if __cplusplus >= 201103L
#	include <type_traits>
#endif

namespace std
{
	template <typename Tp, typename Up>
	class pair;
}


namespace kerbal
{

	namespace utility
	{

		struct compressed_pair_default_construct_tag
		{
		};

		template <typename Tp, typename Up>
		class compressed_pair;


		template <size_t I, typename CompressedPair>
		struct compressed_pair_method_get_return_type;

		template <typename Tp, typename Up>
		struct compressed_pair_method_get_return_type<0, kerbal::utility::compressed_pair<Tp, Up> >
		{
				typedef typename kerbal::utility::compressed_pair<Tp, Up>::first_type_reference type;
		};

		template <typename Tp, typename Up>
		struct compressed_pair_method_get_return_type<1, kerbal::utility::compressed_pair<Tp, Up> >
		{
				typedef typename kerbal::utility::compressed_pair<Tp, Up>::second_type_reference type;
		};



		template <size_t I, typename CompressedPair>
		struct compressed_pair_const_method_get_return_type;

		template <typename Tp, typename Up>
		struct compressed_pair_const_method_get_return_type<0, kerbal::utility::compressed_pair<Tp, Up> >
		{
				typedef typename kerbal::utility::compressed_pair<Tp, Up>::first_type_const_reference type;
		};

		template <typename Tp, typename Up>
		struct compressed_pair_const_method_get_return_type<1, kerbal::utility::compressed_pair<Tp, Up> >
		{
				typedef typename kerbal::utility::compressed_pair<Tp, Up>::second_type_const_reference type;
		};



		template <size_t I, typename CompressedPair>
		struct compressed_pair_rvalue_method_get_return_type;

		template <typename Tp, typename Up>
		struct compressed_pair_rvalue_method_get_return_type<0, kerbal::utility::compressed_pair<Tp, Up> >
		{
				typedef typename kerbal::utility::compressed_pair<Tp, Up>::first_type_rvalue_reference type;
		};

		template <typename Tp, typename Up>
		struct compressed_pair_rvalue_method_get_return_type<1, kerbal::utility::compressed_pair<Tp, Up> >
		{
				typedef typename kerbal::utility::compressed_pair<Tp, Up>::second_type_rvalue_reference type;
		};



		template <size_t I, typename CompressedPair>
		struct compressed_pair_const_rvalue_method_get_return_type;

		template <typename Tp, typename Up>
		struct compressed_pair_const_rvalue_method_get_return_type<0, kerbal::utility::compressed_pair<Tp, Up> >
		{
				typedef typename kerbal::utility::compressed_pair<Tp, Up>::first_type_const_rvalue_reference type;
		};

		template <typename Tp, typename Up>
		struct compressed_pair_const_rvalue_method_get_return_type<1, kerbal::utility::compressed_pair<Tp, Up> >
		{
				typedef typename kerbal::utility::compressed_pair<Tp, Up>::second_type_const_rvalue_reference type;
		};



		template <typename Tp, typename Up>
		class compressed_pair:
				private kerbal::utility::member_compress_helper<Tp, 0>,
				private kerbal::utility::member_compress_helper<Up, kerbal::type_traits::is_same<Tp, Up>::value ? 1 : 0>
		{
			private:
				typedef kerbal::utility::member_compress_helper<Tp, 0> super0;
				typedef kerbal::utility::member_compress_helper<Up, kerbal::type_traits::is_same<Tp, Up>::value ? 1 : 0> super1;

			public:
				typedef Tp first_type;
				typedef Up second_type;

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

			public:

				KERBAL_CONSTEXPR
				compressed_pair()
								KERBAL_CONDITIONAL_NOEXCEPT(
										std::is_nothrow_default_constructible<super0>::value &&
										std::is_nothrow_default_constructible<super1>::value
								) :
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

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR
				compressed_pair(const Tp2 & first, const Up2 & second) :
						super0(kerbal::utility::in_place_t(), first),
						super1(kerbal::utility::in_place_t(), second)
				{
				}

				template <typename Up2>
				KERBAL_CONSTEXPR
				compressed_pair(compressed_pair_default_construct_tag, const Up2 & second) :
						super0(kerbal::utility::in_place_t()),
						super1(kerbal::utility::in_place_t(), second)
				{
				}

				template <typename Tp2>
				KERBAL_CONSTEXPR
				compressed_pair(const Tp2 & first, compressed_pair_default_construct_tag) :
						super0(kerbal::utility::in_place_t(), first),
						super1(kerbal::utility::in_place_t())
				{
				}

#		else

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR
				compressed_pair(Tp2&& first, Up2&& second)
								KERBAL_CONDITIONAL_NOEXCEPT(
										(std::is_nothrow_constructible<super0, Tp2>::value) &&
										(std::is_nothrow_constructible<super1, Up2>::value)
								) :
						super0(kerbal::utility::in_place_t(), kerbal::utility::forward<Tp2>(first)),
						super1(kerbal::utility::in_place_t(), kerbal::utility::forward<Up2>(second))
				{
				}

				template <typename Up2>
				KERBAL_CONSTEXPR
				compressed_pair(compressed_pair_default_construct_tag, Up2&& second)
								KERBAL_CONDITIONAL_NOEXCEPT(
										std::is_nothrow_default_constructible<super0>::value &&
										(std::is_nothrow_constructible<super1, Up2>::value)
								) :
						super0(kerbal::utility::in_place_t()),
						super1(kerbal::utility::in_place_t(), kerbal::utility::forward<Up2>(second))
				{
				}

				template <typename Tp2>
				KERBAL_CONSTEXPR
				compressed_pair(Tp2&& first, compressed_pair_default_construct_tag)
								KERBAL_CONDITIONAL_NOEXCEPT(
										(std::is_nothrow_constructible<super0, Tp2>::value) &&
										std::is_nothrow_default_constructible<super1>::value
								) :
						super0(kerbal::utility::in_place_t(), kerbal::utility::forward<Tp2>(first)),
						super1(kerbal::utility::in_place_t())
				{
				}

#		endif

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				explicit
				compressed_pair(const kerbal::utility::compressed_pair<Tp2, Up2> & pair)
								KERBAL_CONDITIONAL_NOEXCEPT(
										(std::is_nothrow_constructible<super0, const Tp2 &>::value) &&
										(std::is_nothrow_constructible<super1, const Up2 &>::value)
								) :
						super0(kerbal::utility::in_place_t(), pair.first()),
						super1(kerbal::utility::in_place_t(), pair.second())
				{
				}

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				explicit
				compressed_pair(const std::pair<Tp2, Up2> & pair)
								KERBAL_CONDITIONAL_NOEXCEPT(
										(std::is_nothrow_constructible<super0, const Tp2 &>::value) &&
										(std::is_nothrow_constructible<super1, const Up2 &>::value)
								) :
						super0(kerbal::utility::in_place_t(), pair.first),
						super1(kerbal::utility::in_place_t(), pair.second)
				{
				}


#		if __cplusplus >= 201103L

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				explicit
				compressed_pair(kerbal::utility::compressed_pair<Tp2, Up2> && pair)
								KERBAL_CONDITIONAL_NOEXCEPT(
										(std::is_nothrow_constructible<super0, Tp2 &&>::value) &&
										(std::is_nothrow_constructible<super1, Up2 &&>::value)
								) :
						super0(kerbal::utility::in_place_t(), kerbal::utility::forward<Tp2>(pair.first())),
						super1(kerbal::utility::in_place_t(), kerbal::utility::forward<Up2>(pair.second()))
				{
				}

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				explicit
				compressed_pair(std::pair<Tp2, Up2> && pair)
								KERBAL_CONDITIONAL_NOEXCEPT(
										(std::is_nothrow_constructible<super0, Tp2 &&>::value) &&
										(std::is_nothrow_constructible<super1, Up2 &&>::value)
								) :
						super0(kerbal::utility::in_place_t(), kerbal::utility::forward<Tp2>(pair.first)),
						super1(kerbal::utility::in_place_t(), kerbal::utility::forward<Up2>(pair.second))
				{
				}

#		endif

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				compressed_pair& operator=(const kerbal::utility::compressed_pair<Tp2, Up2> & pair)
				{
					this->first() = pair.first();
					this->second() = pair.second();
					return *this;
				}

#		if __cplusplus >= 201103L

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				compressed_pair& operator=(kerbal::utility::compressed_pair<Tp2, Up2> && pair)
				{
					this->first() = kerbal::compatibility::move(pair.first());
					this->second() = kerbal::compatibility::move(pair.second());
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
				first_type_const_reference first() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return super0::member();
				}

				KERBAL_CONSTEXPR14
				second_type_reference second() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return super1::member();
				}

				KERBAL_CONSTEXPR14
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
				first_type_const_rvalue_reference first() const && KERBAL_NOEXCEPT
				{
					return kerbal::compatibility::move(*this).super0::member();
				}

				KERBAL_CONSTEXPR14
				second_type_rvalue_reference second() && KERBAL_NOEXCEPT
				{
					return kerbal::compatibility::move(*this).super1::member();
				}

				KERBAL_CONSTEXPR14
				second_type_const_rvalue_reference second() const && KERBAL_NOEXCEPT
				{
					return kerbal::compatibility::move(*this).super1::member();
				}

#		endif

				void swap(compressed_pair & other)
				{
					kerbal::algorithm::swap(this->first(), other.first());
					kerbal::algorithm::swap(this->second(), other.second());
				}

				template <size_t I>
				KERBAL_CONSTEXPR14
				typename kerbal::utility::compressed_pair_method_get_return_type<I, compressed_pair>::type
				get() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT;

				template <size_t I>
				KERBAL_CONSTEXPR14
				typename kerbal::utility::compressed_pair_const_method_get_return_type<I, compressed_pair>::type
				get() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT;

#		if __cplusplus >= 201103L

				template <size_t I>
				KERBAL_CONSTEXPR14
				typename kerbal::utility::compressed_pair_rvalue_method_get_return_type<I, compressed_pair>::type
				get() && noexcept;

				template <size_t I>
				KERBAL_CONSTEXPR14
				typename kerbal::utility::compressed_pair_const_rvalue_method_get_return_type<I, compressed_pair>::type
				get() const && noexcept;

#		endif

		};

		template <typename Tp, typename Up>
		bool operator==(const kerbal::utility::compressed_pair<Tp, Up>& lhs, const kerbal::utility::compressed_pair<Tp, Up>& rhs)
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(static_cast<bool>(lhs.first() == rhs.first())) &&
						noexcept(static_cast<bool>(lhs.second() == rhs.second()))
				)
		{
			return static_cast<bool>(lhs.first() == rhs.first()) && static_cast<bool>(lhs.second() == rhs.second());
		}

		template <typename Tp, typename Up>
		bool operator!=(const kerbal::utility::compressed_pair<Tp, Up>& lhs, const kerbal::utility::compressed_pair<Tp, Up>& rhs)
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(static_cast<bool>(lhs.first() != rhs.first())) &&
						noexcept(static_cast<bool>(lhs.second() != rhs.second()))
				)
		{
			return static_cast<bool>(lhs.first() != rhs.first()) || static_cast<bool>(lhs.second() != rhs.second());
		}

		template <typename Tp, typename Up>
		bool operator<(const kerbal::utility::compressed_pair<Tp, Up>& lhs, const kerbal::utility::compressed_pair<Tp, Up>& rhs)
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(static_cast<bool>(lhs.first() < rhs.first())) &&
						noexcept(!static_cast<bool>(rhs.first() < lhs.first())) &&
						noexcept(static_cast<bool>(lhs.second() < rhs.second()))
				)
		{
			return static_cast<bool>(lhs.first() < rhs.first())
				|| (!static_cast<bool>(rhs.first() < lhs.first()) && static_cast<bool>(lhs.second() < rhs.second()));
		}

		template <typename Tp, typename Up>
		bool operator>(const kerbal::utility::compressed_pair<Tp, Up>& lhs, const kerbal::utility::compressed_pair<Tp, Up>& rhs)
		{
			return static_cast<bool>(lhs.first() > rhs.first())
				|| (!static_cast<bool>(rhs.first() > lhs.first()) && static_cast<bool>(lhs.second() > rhs.second()));
		}

		template <typename Tp, typename Up>
		bool operator<=(const kerbal::utility::compressed_pair<Tp, Up>& lhs, const kerbal::utility::compressed_pair<Tp, Up>& rhs)
		{
			return static_cast<bool>(lhs.first() <= rhs.first()) && (
					!static_cast<bool>(rhs.first() <= lhs.first()) || static_cast<bool>(lhs.second() <= rhs.second()));
		}

		template <typename Tp, typename Up>
		bool operator>=(const kerbal::utility::compressed_pair<Tp, Up>& lhs, const kerbal::utility::compressed_pair<Tp, Up>& rhs)
		{
			return static_cast<bool>(lhs.first() >= rhs.first()) && (
					!static_cast<bool>(rhs.first() >= lhs.first()) || static_cast<bool>(lhs.second() >= rhs.second()));
		}

		template <typename Tp, typename Up>
		KERBAL_CONSTEXPR
		kerbal::utility::compressed_pair<Tp, Up>
		make_compressed_pair(const Tp & first, const Up & second)
								KERBAL_CONDITIONAL_NOEXCEPT(
										(std::is_nothrow_constructible<kerbal::utility::compressed_pair<Tp, Up>, const Tp &, const Up &>::value)
								)
		{
			return kerbal::utility::compressed_pair<Tp, Up>(first, second);
		}

#	if __cplusplus >= 201703L

		template <typename Tp, typename Up>
		compressed_pair(const Tp &, const Up &) -> compressed_pair<Tp, Up>;

#	endif

	} // namespace utility

} // namespace kerbal

#if __cplusplus >= 201402L

namespace std
{
	template <typename Tp>
	struct tuple_size;

	template <typename Tp, typename Up>
	struct tuple_size<kerbal::utility::compressed_pair<Tp, Up> >
			: std::integral_constant<size_t, 2>
	{
	};

	template <std::size_t I, typename Tp>
	struct tuple_element;

	template <typename Tp, typename Up>
	struct tuple_element<0, kerbal::utility::compressed_pair<Tp, Up> >
	{
			typedef Tp type;
	};

	template <typename Tp, typename Up>
	struct tuple_element<1, kerbal::utility::compressed_pair<Tp, Up> >
	{
			typedef Up type;
	};

	template <typename Tp, typename Up>
	struct tuple_element<0, const kerbal::utility::compressed_pair<Tp, Up> >
	{
			typedef const Tp type;
	};

	template <typename Tp, typename Up>
	struct tuple_element<1, const kerbal::utility::compressed_pair<Tp, Up> >
	{
			typedef const Up type;
	};

	template <std::size_t I>
	struct kerbal_compressed_pair_get;

	template <>
	struct kerbal_compressed_pair_get<0>
	{
			template <typename Tp, typename Up>
			static constexpr Tp&
			__get(kerbal::utility::compressed_pair<Tp, Up>& p) noexcept
			{
				return p.first();
			}

			template <typename Tp, typename Up>
			static constexpr Tp&&
			__move_get(kerbal::utility::compressed_pair<Tp, Up>&& p) noexcept
			{
				return kerbal::utility::forward<Tp>(p.first());
			}

			template <typename Tp, typename Up>
			static constexpr const Tp&
			__const_get(const kerbal::utility::compressed_pair<Tp, Up>& p) noexcept
			{
				return p.first();
			}

			template <typename Tp, typename Up>
			static constexpr const Tp&&
			__const_move_get(const kerbal::utility::compressed_pair<Tp, Up>&& p) noexcept
			{
				return kerbal::utility::forward<const Tp>(p.first());
			}
	};

	template <>
	struct kerbal_compressed_pair_get<1>
	{
			template <typename Tp, typename Up>
			static constexpr Up&
			__get(kerbal::utility::compressed_pair<Tp, Up>& p) noexcept
			{
				return p.second();
			}

			template <typename Tp, typename Up>
			static constexpr Up&&
			__move_get(kerbal::utility::compressed_pair<Tp, Up>&& p) noexcept
			{
				return kerbal::utility::forward<Up>(p.second());
			}

			template <typename Tp, typename Up>
			static constexpr const Up&
			__const_get(const kerbal::utility::compressed_pair<Tp, Up>& p) noexcept
			{
				return p.second();
			}

			template <typename Tp, typename Up>
			static constexpr const Up&&
			__const_move_get(const kerbal::utility::compressed_pair<Tp, Up>&& p) noexcept
			{
				return kerbal::utility::forward<const Up>(p.second());
			}
	};

	template <std::size_t I, typename Tp, typename Up>
	constexpr
	auto&
	get(kerbal::utility::compressed_pair<Tp, Up>& pair) noexcept
	{
		return kerbal_compressed_pair_get<I>::__get(pair);
	}

	template <std::size_t I, typename Tp, typename Up>
	constexpr
	auto&&
	get(kerbal::utility::compressed_pair<Tp, Up>&& pair) noexcept
	{
		return kerbal_compressed_pair_get<I>::__move_get(kerbal::compatibility::move(pair));
	}

	template <std::size_t I, typename Tp, typename Up>
	constexpr
	const auto&
	get(const kerbal::utility::compressed_pair<Tp, Up>& pair) noexcept
	{
		return kerbal_compressed_pair_get<I>::__const_get(pair);
	}

	template <std::size_t I, typename Tp, typename Up>
	constexpr
	const auto&&
	get(const kerbal::utility::compressed_pair<Tp, Up>&& pair) noexcept
	{
		return kerbal_compressed_pair_get<I>::__const_move_get(kerbal::compatibility::move(pair));
	}

} // namespace std

namespace kerbal
{

	namespace utility
	{

		template <typename Tp, typename Up>
		template <size_t I>
		KERBAL_CONSTEXPR14
		typename kerbal::utility::compressed_pair_method_get_return_type<I, compressed_pair<Tp, Up> >::type
		compressed_pair<Tp, Up>::get() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
		{
			return std::get<I>(*this);
		}

		template <typename Tp, typename Up>
		template <size_t I>
		KERBAL_CONSTEXPR14
		typename kerbal::utility::compressed_pair_const_method_get_return_type<I, compressed_pair<Tp, Up> >::type
		compressed_pair<Tp, Up>::get() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
		{
			return std::get<I>(*this);
		}

#	if __cplusplus >= 201103L

		template <typename Tp, typename Up>
		template <size_t I>
		KERBAL_CONSTEXPR14
		typename kerbal::utility::compressed_pair_rvalue_method_get_return_type<I, compressed_pair<Tp, Up> >::type
		compressed_pair<Tp, Up>::get() && noexcept
		{
			return std::get<I>(static_cast<compressed_pair&&>(*this));
		}

		template <typename Tp, typename Up>
		template <size_t I>
		KERBAL_CONSTEXPR14
		typename kerbal::utility::compressed_pair_const_rvalue_method_get_return_type<I, compressed_pair<Tp, Up> >::type
		compressed_pair<Tp, Up>::get() const && noexcept
		{
			return std::get<I>(static_cast<const compressed_pair&&>(*this));
		}

#	endif


	} // namespace utility

} // namespace kerbal

#endif


/*

 note: constructor for compressed_pair

	KERBAL_CONSTEXPR
	compressed_pair();

#if __cplusplus < 201103L

	KERBAL_CONSTEXPR
	compressed_pair(first_type_const_reference first, second_type_const_reference second);

	KERBAL_CONSTEXPR
	compressed_pair(compressed_pair_default_construct_tag tag, second_type_const_reference second);

	KERBAL_CONSTEXPR
	compressed_pair(first_type_const_reference first, compressed_pair_default_construct_tag tag);

	template <typename Tp2, typename Up2>
	KERBAL_CONSTEXPR
	compressed_pair(const Tp2 & first, const Up2 & second);

	template <typename Up2>
	KERBAL_CONSTEXPR
	compressed_pair(compressed_pair_default_construct_tag tag, const Up2 & second);

	template <typename Tp2>
	KERBAL_CONSTEXPR
	compressed_pair(const Tp2 & first, compressed_pair_default_construct_tag tag);

#else

	template <typename Tp2, typename Up2>
	KERBAL_CONSTEXPR
	compressed_pair(Tp2&& first, Up2&& second);

	template <typename Up2>
	KERBAL_CONSTEXPR
	compressed_pair(compressed_pair_default_construct_tag tag, Up2&& second);

	template <typename Tp2>
	KERBAL_CONSTEXPR
	compressed_pair(Tp2&& first, compressed_pair_default_construct_tag tag);

#endif

	template <typename Tp2, typename Up2>
	KERBAL_CONSTEXPR14
	explicit
	compressed_pair(const kerbal::utility::compressed_pair<Tp2, Up2> & pair);

	template <typename Tp2, typename Up2>
	KERBAL_CONSTEXPR14
	explicit
	compressed_pair(const std::pair<Tp2, Up2> & pair);


#if __cplusplus >= 201103L

	template <typename Tp2, typename Up2>
	KERBAL_CONSTEXPR14
	compressed_pair(kerbal::utility::compressed_pair<Tp2, Up2> && pair);

	template <typename Tp2, typename Up2>
	KERBAL_CONSTEXPR14
	compressed_pair(std::pair<Tp2, Up2> && pair);

#endif

*/


#endif // KERBAL_UTILITY_COMPRESSED_PAIR_HPP
