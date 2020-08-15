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
#include <kerbal/type_traits/can_be_empty_base.hpp>
#include <kerbal/type_traits/cv_deduction.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/logical.hpp>

#include <utility>

#if __cplusplus >= 201103L
# include <type_traits>
#endif

namespace kerbal
{

	namespace utility
	{

		struct compressed_pair_default_construct_tag
		{
		};

		template <typename Tp, typename Up>
		struct compressed_pair;

		template <typename Tp, typename Up, int>
		struct __compressed_pair_impl;

		template <typename Tp, typename Up>
		struct __compressed_pair_inner_typedef_helper
		{
			public:
				typedef Tp first_type;
				typedef Up second_type;

			protected:
				typedef typename kerbal::type_traits::add_lvalue_reference<first_type>::type			first_type_reference;
				typedef typename kerbal::type_traits::add_lvalue_reference<second_type>::type			second_type_reference;
				typedef typename kerbal::type_traits::add_const_lvalue_reference<first_type>::type		first_type_const_reference;
				typedef typename kerbal::type_traits::add_const_lvalue_reference<second_type>::type		second_type_const_reference;

#		if __cplusplus >= 201103L
				typedef typename kerbal::type_traits::add_rvalue_reference<first_type>::type			first_type_rvalue_reference;
				typedef typename kerbal::type_traits::add_rvalue_reference<second_type>::type			second_type_rvalue_reference;
				typedef typename kerbal::type_traits::add_const_rvalue_reference<first_type>::type		first_type_const_rvalue_reference;
				typedef typename kerbal::type_traits::add_const_rvalue_reference<second_type>::type		second_type_const_rvalue_reference;
#		endif

				template <typename __Tp, typename __Up, int>
				friend struct __compressed_pair_impl;
		};

		template <typename Tp, typename Up>
		struct __compressed_pair_impl<Tp, Up, 0>
		{
			public:
				typedef Tp first_type;
				typedef Up second_type;

				typedef kerbal::type_traits::false_type is_first_compressed;
				typedef kerbal::type_traits::false_type is_second_compressed;

			private:
				typedef __compressed_pair_inner_typedef_helper<first_type, second_type> inner_typedef_helper;

			public:
				typedef typename inner_typedef_helper::first_type_reference				first_type_reference;
				typedef typename inner_typedef_helper::second_type_reference			second_type_reference;
				typedef typename inner_typedef_helper::first_type_const_reference		first_type_const_reference;
				typedef typename inner_typedef_helper::second_type_const_reference		second_type_const_reference;

#		if __cplusplus >= 201103L
				typedef typename inner_typedef_helper::first_type_rvalue_reference			first_type_rvalue_reference;
				typedef typename inner_typedef_helper::second_type_rvalue_reference			second_type_rvalue_reference;
				typedef typename inner_typedef_helper::first_type_const_rvalue_reference	first_type_const_rvalue_reference;
				typedef typename inner_typedef_helper::second_type_const_rvalue_reference	second_type_const_rvalue_reference;
#		endif

			private:
				first_type __first;
				second_type __second;

			protected:

				KERBAL_CONSTEXPR
				__compressed_pair_impl()
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_default_constructible<first_type>::value &&
												std::is_nothrow_default_constructible<second_type>::value
										) :
										__first(), __second()
				{
				}

#		if __cplusplus < 201103L

				KERBAL_CONSTEXPR
				__compressed_pair_impl(first_type_const_reference __first, second_type_const_reference __second) :
										__first(__first), __second(__second)
				{
				}

				KERBAL_CONSTEXPR
				__compressed_pair_impl(compressed_pair_default_construct_tag, second_type_const_reference __second) :
										__first(), __second(__second)
				{
				}

				KERBAL_CONSTEXPR
				__compressed_pair_impl(first_type_const_reference __first, compressed_pair_default_construct_tag) :
										__first(__first), __second()
				{
				}

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(const Tp2 & __first, const Up2 & __second) :
										__first(__first), __second(__second)
				{
				}

				template <typename Up2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(compressed_pair_default_construct_tag, const Up2 & __second) :
										__first(), __second(__second)
				{
				}

				template <typename Tp2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(const Tp2 & __first, compressed_pair_default_construct_tag) :
										__first(__first), __second()
				{
				}

#		else

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(Tp2&& __first, Up2&& __second)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<first_type, Tp2>::value) &&
												(std::is_nothrow_constructible<second_type, Up2>::value)
										) :
										__first(std::forward<Tp2>(__first)), __second(std::forward<Up2>(__second))
				{
				}

				template <typename Up2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(compressed_pair_default_construct_tag, Up2&& __second)
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_default_constructible<first_type>::value &&
												(std::is_nothrow_constructible<second_type, Up2>::value)
										) :
										__first(), __second(std::forward<Up2>(__second))
				{
				}

				template <typename Tp2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(Tp2&& __first, compressed_pair_default_construct_tag)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<first_type, Tp2>::value) &&
												std::is_nothrow_default_constructible<second_type>::value
										) :
										__first(std::forward<Tp2>(__first)), __second()
				{
				}


#		endif

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				explicit
				__compressed_pair_impl(const kerbal::utility::compressed_pair<Tp2, Up2> & pair)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<first_type, const Tp2 &>::value) &&
												(std::is_nothrow_constructible<second_type, const Up2 &>::value)
										) :
										__first(pair.first()), __second(pair.second())
				{
				}

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				explicit
				__compressed_pair_impl(const std::pair<Tp2, Up2> & pair)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<first_type, const Tp2 &>::value) &&
												(std::is_nothrow_constructible<second_type, const Up2 &>::value)
										) :
										__first(pair.first), __second(pair.second)
				{
				}


#		if __cplusplus >= 201103L

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				__compressed_pair_impl(kerbal::utility::compressed_pair<Tp2, Up2> && pair)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<first_type, Tp2 &&>::value) &&
												(std::is_nothrow_constructible<second_type, Up2 &&>::value)
										) :
										__first(std::forward<Tp2>(pair.first())), __second(std::forward<Up2>(pair.second()))
				{
				}

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				__compressed_pair_impl(std::pair<Tp2, Up2> && pair)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<first_type, Tp2 &&>::value) &&
												(std::is_nothrow_constructible<second_type, Up2 &&>::value)
										) :
										__first(std::forward<Tp2>(pair.first)), __second(std::forward<Up2>(pair.second))
				{
				}

#		endif

			public:

				KERBAL_CONSTEXPR14
				first_type_reference first() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->__first;
				}

				KERBAL_CONSTEXPR14
				first_type_const_reference first() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->__first;
				}

				KERBAL_CONSTEXPR14
				second_type_reference second() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->__second;
				}

				KERBAL_CONSTEXPR14
				second_type_const_reference second() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->__second;
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				first_type_rvalue_reference first() && KERBAL_NOEXCEPT
				{
					return kerbal::compatibility::move(this->__first);
				}

				KERBAL_CONSTEXPR14
				second_type_rvalue_reference second() && KERBAL_NOEXCEPT
				{
					return kerbal::compatibility::move(this->__second);
				}

				KERBAL_CONSTEXPR14
				first_type_const_rvalue_reference first() const && KERBAL_NOEXCEPT
				{
					return kerbal::compatibility::move(this->__first);
				}

				KERBAL_CONSTEXPR14
				second_type_const_rvalue_reference second() const && KERBAL_NOEXCEPT
				{
					return kerbal::compatibility::move(this->__second);
				}

#		endif

		};

		template <typename Tp, typename Up>
		struct __compressed_pair_impl<Tp, Up, 1> : private kerbal::type_traits::remove_cv<Up>::type
		{
			public:
				typedef Tp first_type;
				typedef Up second_type;

				typedef kerbal::type_traits::false_type is_first_compressed;
				typedef kerbal::type_traits::true_type  is_second_compressed;

			private:
				typedef __compressed_pair_inner_typedef_helper<first_type, second_type> inner_typedef_helper;

			public:
				typedef typename inner_typedef_helper::first_type_reference				first_type_reference;
				typedef typename inner_typedef_helper::second_type_reference			second_type_reference;
				typedef typename inner_typedef_helper::first_type_const_reference		first_type_const_reference;
				typedef typename inner_typedef_helper::second_type_const_reference		second_type_const_reference;

#		if __cplusplus >= 201103L
				typedef typename inner_typedef_helper::first_type_rvalue_reference			first_type_rvalue_reference;
				typedef typename inner_typedef_helper::second_type_rvalue_reference			second_type_rvalue_reference;
				typedef typename inner_typedef_helper::first_type_const_rvalue_reference	first_type_const_rvalue_reference;
				typedef typename inner_typedef_helper::second_type_const_rvalue_reference	second_type_const_rvalue_reference;
#		endif

			private:
				first_type __first;
				typedef typename kerbal::type_traits::remove_cv<Up>::type super2;

			protected:

				KERBAL_CONSTEXPR
				__compressed_pair_impl()
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_default_constructible<first_type>::value &&
												std::is_nothrow_default_constructible<super2>::value
										) :
										super2(), __first()
				{
				}


#		if __cplusplus < 201103L

				KERBAL_CONSTEXPR
				__compressed_pair_impl(first_type_const_reference __first, second_type_const_reference __second) :
										super2(__second), __first(__first)
				{
				}

				KERBAL_CONSTEXPR
				__compressed_pair_impl(compressed_pair_default_construct_tag, second_type_const_reference __second) :
										super2(__second), __first()
				{
				}

				KERBAL_CONSTEXPR
				__compressed_pair_impl(first_type_const_reference __first, compressed_pair_default_construct_tag) :
										super2(), __first(__first)
				{
				}

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(const Tp2 & __first, const Up2 & __second) :
										super2(__second), __first(__first)
				{
				}

				template <typename Up2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(compressed_pair_default_construct_tag, const Up2 & __second) :
										super2(__second), __first()
				{
				}

				template <typename Tp2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(const Tp2 & __first, compressed_pair_default_construct_tag) :
										super2(), __first(__first)
				{
				}

#		else

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(Tp2&& __first, Up2&& __second)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<first_type, Tp2>::value) &&
												(std::is_nothrow_constructible<super2, Up2>::value)
										) :
										super2(std::forward<Up2>(__second)), __first(std::forward<Tp2>(__first))
				{
				}

				template <typename Up2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(compressed_pair_default_construct_tag, Up2&& __second)
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_default_constructible<first_type>::value &&
												(std::is_nothrow_constructible<super2, Up2>::value)
										) :
										super2(std::forward<Up2>(__second)), __first()
				{
				}

				template <typename Tp2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(Tp2&& __first, compressed_pair_default_construct_tag)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<first_type, Tp2>::value) &&
												std::is_nothrow_default_constructible<super2>::value
										) :
										super2(), __first(std::forward<Tp2>(__first))
				{
				}

#		endif

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				explicit
				__compressed_pair_impl(const kerbal::utility::compressed_pair<Tp2, Up2> & pair)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<first_type, const Tp2 &>::value) &&
												(std::is_nothrow_constructible<super2, const Up2 &>::value)
										) :
										super2(pair.second()), __first(pair.first())
				{
				}

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				explicit
				__compressed_pair_impl(const std::pair<Tp2, Up2> & pair)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<first_type, const Tp2 &>::value) &&
												(std::is_nothrow_constructible<super2, const Up2 &>::value)
										) :
										super2(pair.second), __first(pair.first)
				{
				}


#		if __cplusplus >= 201103L

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				__compressed_pair_impl(kerbal::utility::compressed_pair<Tp2, Up2> && pair)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<first_type, Tp2 &&>::value) &&
												(std::is_nothrow_constructible<super2, Up2 &&>::value)
										) :
										super2(std::forward<Tp2>(pair.second())), __first(std::forward<Up2>(pair.first()))
				{
				}

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				__compressed_pair_impl(std::pair<Tp2, Up2> && pair)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<first_type, Tp2 &&>::value) &&
												(std::is_nothrow_constructible<super2, Up2 &&>::value)
										) :
										super2(std::forward<Tp2>(pair.second)), __first(std::forward<Up2>(pair.first))
				{
				}

#		endif

			public:

				KERBAL_CONSTEXPR14
				first_type_reference first() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->__first;
				}

				KERBAL_CONSTEXPR14
				first_type_const_reference first() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->__first;
				}

				KERBAL_CONSTEXPR14
				second_type_reference second() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return static_cast<second_type_reference>(*this);
				}

				KERBAL_CONSTEXPR14
				second_type_const_reference second() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return static_cast<second_type_const_reference>(*this);
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				first_type_rvalue_reference first() && KERBAL_NOEXCEPT
				{
					return kerbal::compatibility::move(this->__first);
				}

				KERBAL_CONSTEXPR14
				second_type_rvalue_reference second() && KERBAL_NOEXCEPT
				{
					return static_cast<second_type_rvalue_reference>(*this);
				}

				KERBAL_CONSTEXPR14
				first_type_const_rvalue_reference first() const && KERBAL_NOEXCEPT
				{
					return kerbal::compatibility::move(this->__first);
				}

				KERBAL_CONSTEXPR14
				second_type_const_rvalue_reference second() const && KERBAL_NOEXCEPT
				{
					return static_cast<second_type_const_rvalue_reference>(*this);
				}

#		endif

		};

		template <typename Tp, typename Up>
		struct __compressed_pair_impl<Tp, Up, 2> : private kerbal::type_traits::remove_cv<Tp>::type
		{
			public:
				typedef Tp first_type;
				typedef Up second_type;

				typedef kerbal::type_traits::true_type  is_first_compressed;
				typedef kerbal::type_traits::false_type is_second_compressed;

			private:
				typedef __compressed_pair_inner_typedef_helper<first_type, second_type> inner_typedef_helper;

			public:
				typedef typename inner_typedef_helper::first_type_reference				first_type_reference;
				typedef typename inner_typedef_helper::second_type_reference			second_type_reference;
				typedef typename inner_typedef_helper::first_type_const_reference		first_type_const_reference;
				typedef typename inner_typedef_helper::second_type_const_reference		second_type_const_reference;

#		if __cplusplus >= 201103L
				typedef typename inner_typedef_helper::first_type_rvalue_reference			first_type_rvalue_reference;
				typedef typename inner_typedef_helper::second_type_rvalue_reference			second_type_rvalue_reference;
				typedef typename inner_typedef_helper::first_type_const_rvalue_reference	first_type_const_rvalue_reference;
				typedef typename inner_typedef_helper::second_type_const_rvalue_reference	second_type_const_rvalue_reference;
#		endif

			private:
				typedef typename kerbal::type_traits::remove_cv<Tp>::type super1;
				second_type __second;

			protected:

				KERBAL_CONSTEXPR
				__compressed_pair_impl()
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_default_constructible<super1>::value &&
												std::is_nothrow_default_constructible<second_type>::value
										) :
										super1(), __second()
				{
				}

#		if __cplusplus < 201103L

				KERBAL_CONSTEXPR
				__compressed_pair_impl(first_type_const_reference __first, second_type_const_reference __second) :
										super1(__first), __second(__second)
				{
				}

				KERBAL_CONSTEXPR
				__compressed_pair_impl(compressed_pair_default_construct_tag, second_type_const_reference __second) :
										super1(), __second(__second)
				{
				}

				KERBAL_CONSTEXPR
				__compressed_pair_impl(first_type_const_reference __first, compressed_pair_default_construct_tag) :
										super1(__first), __second()
				{
				}

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(const Tp2 & __first, const Up2 & __second) :
										super1(__first), __second(__second)
				{
				}

				template <typename Up2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(compressed_pair_default_construct_tag, const Up2 & __second) :
										super1(), __second(__second)
				{
				}

				template <typename Tp2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(const Tp2 & __first, compressed_pair_default_construct_tag) :
										super1(__first), __second()
				{
				}

#		else

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(Tp2&& __first, Up2&& __second)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<super1, Tp2>::value) &&
												(std::is_nothrow_constructible<second_type, Up2>::value)
										) :
										super1(std::forward<Tp2>(__first)), __second(std::forward<Up2>(__second))
				{
				}

				template <typename Up2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(compressed_pair_default_construct_tag, Up2&& __second)
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_default_constructible<super1>::value &&
												(std::is_nothrow_constructible<second_type, Up2>::value)
										) :
										super1(), __second(std::forward<Up2>(__second))
				{
				}

				template <typename Tp2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(Tp2&& __first, compressed_pair_default_construct_tag)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<super1, Tp2>::value) &&
												std::is_nothrow_default_constructible<second_type>::value
										) :
										super1(std::forward<Tp2>(__first)), __second()
				{
				}


#		endif

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				explicit
				__compressed_pair_impl(const kerbal::utility::compressed_pair<Tp2, Up2> & pair)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<super1, const Tp2 &>::value) &&
												(std::is_nothrow_constructible<second_type, const Up2 &>::value)
										) :
										super1(pair.first()), __second(pair.second())
				{
				}

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				explicit
				__compressed_pair_impl(const std::pair<Tp2, Up2> & pair)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<super1, const Tp2 &>::value) &&
												(std::is_nothrow_constructible<second_type, const Up2 &>::value)
										) :
										super1(pair.first), __second(pair.second)
				{
				}


#		if __cplusplus >= 201103L

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				__compressed_pair_impl(kerbal::utility::compressed_pair<Tp2, Up2> && pair)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<super1, Tp2 &&>::value) &&
												(std::is_nothrow_constructible<second_type, Up2 &&>::value)
										) :
										super1(std::forward<Tp2>(pair.first())), __second(std::forward<Up2>(pair.second()))
				{
				}

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				__compressed_pair_impl(std::pair<Tp2, Up2> && pair)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<super1, Tp2 &&>::value) &&
												(std::is_nothrow_constructible<second_type, Up2 &&>::value)
										) :
										super1(std::forward<Tp2>(pair.first)), __second(std::forward<Up2>(pair.second))
				{
				}

#		endif

			public:

				KERBAL_CONSTEXPR14
				first_type_reference first() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return static_cast<first_type_reference>(*this);
				}

				KERBAL_CONSTEXPR14
				first_type_const_reference first() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return static_cast<first_type_const_reference>(*this);
				}

				KERBAL_CONSTEXPR14
				second_type_reference second() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->__second;
				}

				KERBAL_CONSTEXPR14
				second_type_const_reference second() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->__second;
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				first_type_rvalue_reference first() && KERBAL_NOEXCEPT
				{
					return static_cast<first_type_rvalue_reference>(*this);
				}

				KERBAL_CONSTEXPR14
				second_type_rvalue_reference second() && KERBAL_NOEXCEPT
				{
					return kerbal::compatibility::move(this->__second);
				}

				KERBAL_CONSTEXPR14
				first_type_const_rvalue_reference first() const && KERBAL_NOEXCEPT
				{
					return static_cast<first_type_const_rvalue_reference>(*this);
				}

				KERBAL_CONSTEXPR14
				second_type_const_rvalue_reference second() const && KERBAL_NOEXCEPT
				{
					return kerbal::compatibility::move(this->__second);
				}

#		endif

		};

		template <typename Tp, typename Up>
		struct __compressed_pair_impl<Tp, Up, 3> :
													private kerbal::type_traits::remove_cv<Tp>::type,
													private kerbal::type_traits::remove_cv<Up>::type
		{
			public:
				typedef Tp first_type;
				typedef Up second_type;

				typedef kerbal::type_traits::true_type is_first_compressed;
				typedef kerbal::type_traits::true_type is_second_compressed;

			private:
				typedef __compressed_pair_inner_typedef_helper<first_type, second_type> inner_typedef_helper;

			public:
				typedef typename inner_typedef_helper::first_type_reference				first_type_reference;
				typedef typename inner_typedef_helper::second_type_reference			second_type_reference;
				typedef typename inner_typedef_helper::first_type_const_reference		first_type_const_reference;
				typedef typename inner_typedef_helper::second_type_const_reference		second_type_const_reference;

#		if __cplusplus >= 201103L
				typedef typename inner_typedef_helper::first_type_rvalue_reference			first_type_rvalue_reference;
				typedef typename inner_typedef_helper::second_type_rvalue_reference			second_type_rvalue_reference;
				typedef typename inner_typedef_helper::first_type_const_rvalue_reference	first_type_const_rvalue_reference;
				typedef typename inner_typedef_helper::second_type_const_rvalue_reference	second_type_const_rvalue_reference;
#		endif

			private:
				typedef typename kerbal::type_traits::remove_cv<Tp>::type super1;
				typedef typename kerbal::type_traits::remove_cv<Up>::type super2;

			protected:

				KERBAL_CONSTEXPR
				__compressed_pair_impl()
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_default_constructible<super1>::value &&
												std::is_nothrow_default_constructible<super2>::value
										) :
										super1(), super2()
				{
				}

#		if __cplusplus < 201103L

				KERBAL_CONSTEXPR
				__compressed_pair_impl(first_type_const_reference __first, second_type_const_reference __second) :
										super1(__first), super2(__second)
				{
				}

				KERBAL_CONSTEXPR
				__compressed_pair_impl(compressed_pair_default_construct_tag, second_type_const_reference __second) :
										super1(), super2(__second)
				{
				}

				KERBAL_CONSTEXPR
				__compressed_pair_impl(first_type_const_reference __first, compressed_pair_default_construct_tag) :
										super1(__first), super2()
				{
				}

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(const Tp2 & __first, const Up2 & __second) :
										super1(__first), super2(__second)
				{
				}

				template <typename Up2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(compressed_pair_default_construct_tag, const Up2 & __second) :
										super1(), super2(__second)
				{
				}

				template <typename Tp2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(const Tp2 & __first, compressed_pair_default_construct_tag) :
										super1(__first), super2()
				{
				}

#		else

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(Tp2&& __first, Up2&& __second)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<super1, Tp2>::value) &&
												(std::is_nothrow_constructible<super2, Up2>::value)
										) :
										super1(std::forward<Tp2>(__first)), super2(std::forward<Up2>(__second))
				{
				}

				template <typename Up2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(compressed_pair_default_construct_tag, Up2&& __second)
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_default_constructible<super1>::value &&
												(std::is_nothrow_constructible<super2, Up2>::value)
										) :
										super1(), super2(std::forward<Up2>(__second))
				{
				}

				template <typename Tp2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(Tp2&& __first, compressed_pair_default_construct_tag)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<super1, Tp2>::value) &&
												std::is_nothrow_default_constructible<super2>::value
										) :
										super1(std::forward<Tp2>(__first)), super2()
				{
				}

#		endif

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				explicit
				__compressed_pair_impl(const kerbal::utility::compressed_pair<Tp2, Up2> & pair)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<super1, const Tp2 &>::value) &&
												(std::is_nothrow_constructible<super2, const Up2 &>::value)
										) :
										super1(pair.first()), super2(pair.second())
				{
				}

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				explicit
				__compressed_pair_impl(const std::pair<Tp2, Up2> & pair)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<super1, const Tp2 &>::value) &&
												(std::is_nothrow_constructible<super2, const Up2 &>::value)
										) :
										super1(pair.first), super2(pair.second)
				{
				}


#		if __cplusplus >= 201103L

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				__compressed_pair_impl(kerbal::utility::compressed_pair<Tp2, Up2> && pair)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<super1, Tp2 &&>::value) &&
												(std::is_nothrow_constructible<super2, Up2 &&>::value)
										) :
										super1(std::forward<Tp2>(pair.first())), super2(std::forward<Up2>(pair.second()))
				{
				}

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				__compressed_pair_impl(std::pair<Tp2, Up2> && pair)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<super1, Tp2 &&>::value) &&
												(std::is_nothrow_constructible<super2, Up2 &&>::value)
										) :
										super1(std::forward<Tp2>(pair.first)), super2(std::forward<Up2>(pair.second))
				{
				}

#		endif

			public:

				KERBAL_CONSTEXPR14
				first_type_reference first() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return static_cast<first_type_reference>(*this);
				}

				KERBAL_CONSTEXPR14
				first_type_const_reference first() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return static_cast<first_type_const_reference>(*this);
				}

				KERBAL_CONSTEXPR14
				second_type_reference second() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return static_cast<second_type_reference>(*this);
				}

				KERBAL_CONSTEXPR14
				second_type_const_reference second() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return static_cast<second_type_const_reference>(*this);
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				first_type_rvalue_reference first() && KERBAL_NOEXCEPT
				{
					return static_cast<first_type_rvalue_reference>(*this);
				}

				KERBAL_CONSTEXPR14
				second_type_rvalue_reference second() && KERBAL_NOEXCEPT
				{
					return static_cast<second_type_rvalue_reference>(*this);
				}

				KERBAL_CONSTEXPR14
				first_type_const_rvalue_reference first() const && KERBAL_NOEXCEPT
				{
					return static_cast<first_type_const_rvalue_reference>(*this);
				}

				KERBAL_CONSTEXPR14
				second_type_const_rvalue_reference second() const && KERBAL_NOEXCEPT
				{
					return static_cast<second_type_const_rvalue_reference>(*this);
				}

#		endif

		};

		template <typename Tp, typename Up, bool, bool>
		struct __compressed_pair_policy_switch_impl;

		template <typename Tp, typename Up>
		struct __compressed_pair_policy_switch_impl<Tp, Up, false, false> : kerbal::type_traits::integral_constant<int, 0>
		{
		};

		template <typename Tp, typename Up>
		struct __compressed_pair_policy_switch_impl<Tp, Up, false, true> : kerbal::type_traits::integral_constant<int, 1>
		{
		};

		template <typename Tp, typename Up>
		struct __compressed_pair_policy_switch_impl<Tp, Up, true, false> : kerbal::type_traits::integral_constant<int, 2>
		{
		};

		template <typename Tp>
		struct __compressed_pair_policy_switch_impl<Tp, Tp, true, true> : kerbal::type_traits::integral_constant<int, 2>
		{
		};

		template <typename Tp, typename Up>
		struct __compressed_pair_policy_switch_impl<Tp, Up, true, true> : kerbal::type_traits::integral_constant<int, 3>
		{
		};


		template <typename Tp, typename Up>
		struct __compressed_pair_policy_switch :
				kerbal::utility::__compressed_pair_policy_switch_impl<
					typename kerbal::type_traits::remove_cv<Tp>::type,
					typename kerbal::type_traits::remove_cv<Up>::type,
					kerbal::type_traits::can_be_empty_base<Tp>::value,
					kerbal::type_traits::can_be_empty_base<Up>::value
				>
		{
		};



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
		struct compressed_pair : public kerbal::utility::__compressed_pair_impl<Tp, Up, __compressed_pair_policy_switch<Tp, Up>::value >
		{
			public:
				typedef Tp first_type;
				typedef Up second_type;

			private:
				typedef kerbal::utility::__compressed_pair_impl<Tp, Up, __compressed_pair_policy_switch<Tp, Up>::value > super;

			public:
				typedef typename super::first_type_reference					first_type_reference;
				typedef typename super::second_type_reference					second_type_reference;
				typedef typename super::first_type_const_reference				first_type_const_reference;
				typedef typename super::second_type_const_reference				second_type_const_reference;

#		if __cplusplus >= 201103L
				typedef typename super::first_type_rvalue_reference				first_type_rvalue_reference;
				typedef typename super::second_type_rvalue_reference			second_type_rvalue_reference;
				typedef typename super::first_type_const_rvalue_reference		first_type_const_rvalue_reference;
				typedef typename super::second_type_const_rvalue_reference		second_type_const_rvalue_reference;
#		endif

			public:
				KERBAL_CONSTEXPR
				compressed_pair()
								KERBAL_CONDITIONAL_NOEXCEPT(
										std::is_nothrow_default_constructible<super>::value
								) :
								super()
				{
				}

#		if __cplusplus < 201103L

				KERBAL_CONSTEXPR
				compressed_pair(first_type_const_reference __first, second_type_const_reference __second) :
								super(__first, __second)
				{
				}

				KERBAL_CONSTEXPR
				compressed_pair(compressed_pair_default_construct_tag tag, second_type_const_reference __second) :
								super(tag, __second)
				{
				}

				KERBAL_CONSTEXPR
				compressed_pair(first_type_const_reference __first, compressed_pair_default_construct_tag tag) :
								super(__first, tag)
				{
				}

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR
				compressed_pair(const Tp2 & __first, const Up2 & __second) :
								super(__first, __second)
				{
				}

				template <typename Up2>
				KERBAL_CONSTEXPR
				compressed_pair(compressed_pair_default_construct_tag tag, const Up2 & __second) :
								super(tag, __second)
				{
				}

				template <typename Tp2>
				KERBAL_CONSTEXPR
				compressed_pair(const Tp2 & __first, compressed_pair_default_construct_tag tag) :
								super(__first, tag)
				{
				}

#		else

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR
				compressed_pair(Tp2&& __first, Up2&& __second)
								KERBAL_CONDITIONAL_NOEXCEPT(
										(std::is_nothrow_constructible<super, Tp2, Up2>::value)
								) :
								super(std::forward<Tp2>(__first), std::forward<Up2>(__second))
				{
				}

				template <typename Up2>
				KERBAL_CONSTEXPR
				compressed_pair(compressed_pair_default_construct_tag tag, Up2&& __second)
								KERBAL_CONDITIONAL_NOEXCEPT(
										(std::is_nothrow_constructible<super, compressed_pair_default_construct_tag, Up2>::value)
								) :
								super(tag, std::forward<Up2>(__second))
				{
				}

				template <typename Tp2>
				KERBAL_CONSTEXPR
				compressed_pair(Tp2&& __first, compressed_pair_default_construct_tag tag)
								KERBAL_CONDITIONAL_NOEXCEPT(
										(std::is_nothrow_constructible<super, Tp2, compressed_pair_default_construct_tag>::value)
								) :
								super(std::forward<Tp2>(__first), tag)
				{
				}

#		endif

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				explicit
				compressed_pair(const kerbal::utility::compressed_pair<Tp2, Up2> & pair)
								KERBAL_CONDITIONAL_NOEXCEPT(
										(std::is_nothrow_constructible<super, const kerbal::utility::compressed_pair<Tp2, Up2> &>::value)
								) :
								super(pair)
				{
				}

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				explicit
				compressed_pair(const std::pair<Tp2, Up2> & pair)
								KERBAL_CONDITIONAL_NOEXCEPT(
										(std::is_nothrow_constructible<super, const std::pair<Tp2, Up2> &>::value)
								) :
								super(pair)
				{
				}


#		if __cplusplus >= 201103L

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				compressed_pair(kerbal::utility::compressed_pair<Tp2, Up2> && pair)
								KERBAL_CONDITIONAL_NOEXCEPT(
										(std::is_nothrow_constructible<super, kerbal::utility::compressed_pair<Tp2, Up2> &&>::value)
								) :
								super(std::forward<kerbal::utility::compressed_pair<Tp2, Up2> >(pair))
				{
				}

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				compressed_pair(std::pair<Tp2, Up2> && pair)
								KERBAL_CONDITIONAL_NOEXCEPT(
										(std::is_nothrow_constructible<super, std::pair<Tp2, Up2> &&>::value)
								) :
								super(std::forward<std::pair<Tp2, Up2> >(pair))
				{
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
		{
			return static_cast<bool>(lhs.first == rhs.first) && static_cast<bool>(lhs.second == rhs.second);
		}

		template <typename Tp, typename Up>
		bool operator!=(const kerbal::utility::compressed_pair<Tp, Up>& lhs, const kerbal::utility::compressed_pair<Tp, Up>& rhs)
		{
			return static_cast<bool>(lhs.first != rhs.first) || static_cast<bool>(lhs.second != rhs.second);
		}

		template <typename Tp, typename Up>
		bool operator<(const kerbal::utility::compressed_pair<Tp, Up>& lhs, const kerbal::utility::compressed_pair<Tp, Up>& rhs)
		{
			return static_cast<bool>(lhs.first < rhs.first)
				|| (!static_cast<bool>(rhs.first < lhs.first) && static_cast<bool>(lhs.second < rhs.second));
		}

		template <typename Tp, typename Up>
		bool operator>(const kerbal::utility::compressed_pair<Tp, Up>& lhs, const kerbal::utility::compressed_pair<Tp, Up>& rhs)
		{
			return static_cast<bool>(rhs < lhs);
		}

		template <typename Tp, typename Up>
		bool operator<=(const kerbal::utility::compressed_pair<Tp, Up>& lhs, const kerbal::utility::compressed_pair<Tp, Up>& rhs)
		{
			return !static_cast<bool>((rhs < lhs));
		}

		template <typename Tp, typename Up>
		bool operator>=(const kerbal::utility::compressed_pair<Tp, Up>& lhs, const kerbal::utility::compressed_pair<Tp, Up>& rhs)
		{
			return !static_cast<bool>((lhs < rhs));
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

	template <typename Tp, typename Up>
	struct tuple_size<kerbal::utility::compressed_pair<Tp, Up> >
			: std::integral_constant<size_t, 2>
	{
	};

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
				return std::forward<Tp>(p.first());
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
				return std::forward<const Tp>(p.first());
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
				return std::forward<Up>(p.second());
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
				return std::forward<const Up>(p.second());
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

#endif // KERBAL_UTILITY_COMPRESSED_PAIR_HPP
