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
#include <kerbal/compatibility/noexcept.hpp>
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
				typedef typename kerbal::type_traits::add_lvalue_reference<first_type>::type             __first_type_ref;
				typedef typename kerbal::type_traits::add_lvalue_reference<second_type>::type            __second_type_ref;
				typedef typename kerbal::type_traits::add_const_lvalue_reference<first_type>::type       __first_type_const_ref;
				typedef typename kerbal::type_traits::add_const_lvalue_reference<second_type>::type      __second_type_const_ref;

#		if __cplusplus >= 201103L
				typedef typename kerbal::type_traits::add_rvalue_reference<first_type>::type             __first_type_rref;
				typedef typename kerbal::type_traits::add_rvalue_reference<second_type>::type            __second_type_rref;
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
				first_type __first;
				second_type __second;

			private:
				typedef __compressed_pair_inner_typedef_helper<first_type, second_type> inner_typedef_helper;

			protected:
				typedef typename inner_typedef_helper::__first_type_ref             __first_type_ref;
				typedef typename inner_typedef_helper::__second_type_ref            __second_type_ref;
				typedef typename inner_typedef_helper::__first_type_const_ref       __first_type_const_ref;
				typedef typename inner_typedef_helper::__second_type_const_ref      __second_type_const_ref;

#		if __cplusplus >= 201103L
				typedef typename inner_typedef_helper::__first_type_rref             __first_type_rref;
				typedef typename inner_typedef_helper::__second_type_rref            __second_type_rref;
#		endif

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
				__first_type_ref first() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->__first;
				}

				KERBAL_CONSTEXPR14
				__first_type_const_ref first() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->__first;
				}

				KERBAL_CONSTEXPR14
				__second_type_ref second() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->__second;
				}

				KERBAL_CONSTEXPR14
				__second_type_const_ref second() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->__second;
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				__first_type_rref first() && KERBAL_NOEXCEPT
				{
					return std::move(this->__first);
				}

				KERBAL_CONSTEXPR14
				__second_type_rref second() && KERBAL_NOEXCEPT
				{
					return std::move(this->__second);
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
				first_type __first;
				typedef typename kerbal::type_traits::remove_cv<Up>::type super;

			private:
				typedef __compressed_pair_inner_typedef_helper<first_type, second_type> inner_typedef_helper;

			protected:
				typedef typename inner_typedef_helper::__first_type_ref             __first_type_ref;
				typedef typename inner_typedef_helper::__second_type_ref            __second_type_ref;
				typedef typename inner_typedef_helper::__first_type_const_ref       __first_type_const_ref;
				typedef typename inner_typedef_helper::__second_type_const_ref      __second_type_const_ref;

#		if __cplusplus >= 201103L
				typedef typename inner_typedef_helper::__first_type_rref             __first_type_rref;
				typedef typename inner_typedef_helper::__second_type_rref            __second_type_rref;
#		endif

			protected:
				KERBAL_CONSTEXPR
				__compressed_pair_impl()
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_default_constructible<first_type>::value &&
												std::is_nothrow_default_constructible<super>::value
										) :
										super(), __first()
				{
				}


#		if __cplusplus < 201103L

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(const Tp2 & __first, const Up2 & __second) :
										super(__second), __first(__first)
				{
				}

				template <typename Up2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(compressed_pair_default_construct_tag, const Up2 & __second) :
										super(__second), __first()
				{
				}

				template <typename Tp2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(const Tp2 & __first, compressed_pair_default_construct_tag) :
										super(), __first(__first)
				{
				}

#		else

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(Tp2&& __first, Up2&& __second)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<first_type, Tp2>::value) &&
												(std::is_nothrow_constructible<super, Up2>::value)
										) :
										super(std::forward<Up2>(__second)), __first(std::forward<Tp2>(__first))
				{
				}

				template <typename Up2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(compressed_pair_default_construct_tag, Up2&& __second)
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_default_constructible<first_type>::value &&
												(std::is_nothrow_constructible<super, Up2>::value)
										) :
										super(std::forward<Up2>(__second)), __first()
				{
				}

				template <typename Tp2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(Tp2&& __first, compressed_pair_default_construct_tag)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<first_type, Tp2>::value) &&
												std::is_nothrow_default_constructible<super>::value
										) :
										super(), __first(std::forward<Tp2>(__first))
				{
				}

#		endif

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				__compressed_pair_impl(const kerbal::utility::compressed_pair<Tp2, Up2> & pair)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<first_type, const Tp2 &>::value) &&
												(std::is_nothrow_constructible<super, const Up2 &>::value)
										) :
										super(pair.second()), __first(pair.first())
				{
				}

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				__compressed_pair_impl(const std::pair<Tp2, Up2> & pair)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<first_type, const Tp2 &>::value) &&
												(std::is_nothrow_constructible<super, const Up2 &>::value)
										) :
										super(pair.second), __first(pair.first)
				{
				}


#		if __cplusplus >= 201103L

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				__compressed_pair_impl(kerbal::utility::compressed_pair<Tp2, Up2> && pair)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<first_type, Tp2 &&>::value) &&
												(std::is_nothrow_constructible<super, Up2 &&>::value)
										) :
										super(std::forward<Tp2>(pair.second())), __first(std::forward<Up2>(pair.first()))
				{
				}

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				__compressed_pair_impl(std::pair<Tp2, Up2> && pair)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<first_type, Tp2 &&>::value) &&
												(std::is_nothrow_constructible<super, Up2 &&>::value)
										) :
										super(std::forward<Tp2>(pair.second)), __first(std::forward<Up2>(pair.first))
				{
				}

#		endif

			public:

				KERBAL_CONSTEXPR14
				__first_type_ref first() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->__first;
				}

				KERBAL_CONSTEXPR14
				__first_type_const_ref first() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->__first;
				}

				KERBAL_CONSTEXPR14
				__second_type_ref second() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return static_cast<__second_type_ref>(*this);
				}

				KERBAL_CONSTEXPR14
				__second_type_const_ref second() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return static_cast<__second_type_const_ref>(*this);
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				__first_type_rref first() && KERBAL_NOEXCEPT
				{
					return std::move(this->__first);
				}

				KERBAL_CONSTEXPR14
				__second_type_rref second() && KERBAL_NOEXCEPT
				{
					return static_cast<__second_type_rref>(*this);
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
				typedef typename kerbal::type_traits::remove_cv<Tp>::type super;
				second_type __second;

			private:
				typedef __compressed_pair_inner_typedef_helper<first_type, second_type> inner_typedef_helper;

			protected:
				typedef typename inner_typedef_helper::__first_type_ref             __first_type_ref;
				typedef typename inner_typedef_helper::__second_type_ref            __second_type_ref;
				typedef typename inner_typedef_helper::__first_type_const_ref       __first_type_const_ref;
				typedef typename inner_typedef_helper::__second_type_const_ref      __second_type_const_ref;

#		if __cplusplus >= 201103L
				typedef typename inner_typedef_helper::__first_type_rref             __first_type_rref;
				typedef typename inner_typedef_helper::__second_type_rref            __second_type_rref;
#		endif

			protected:
				KERBAL_CONSTEXPR
				__compressed_pair_impl()
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_default_constructible<super>::value &&
												std::is_nothrow_default_constructible<second_type>::value
										) :
										super(), __second()
				{
				}

#		if __cplusplus < 201103L

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(const Tp2 & __first, const Up2 & __second) :
										super(__first), __second(__second)
				{
				}

				template <typename Up2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(compressed_pair_default_construct_tag, const Up2 & __second) :
										super(), __second(__second)
				{
				}

				template <typename Tp2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(const Tp2 & __first, compressed_pair_default_construct_tag) :
										super(__first), __second()
				{
				}

#		else

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(Tp2&& __first, Up2&& __second)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<super, Tp2>::value) &&
												(std::is_nothrow_constructible<second_type, Up2>::value)
										) :
										super(std::forward<Tp2>(__first)), __second(std::forward<Up2>(__second))
				{
				}

				template <typename Up2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(compressed_pair_default_construct_tag, Up2&& __second)
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_default_constructible<super>::value &&
												(std::is_nothrow_constructible<second_type, Up2>::value)
										) :
										super(), __second(std::forward<Up2>(__second))
				{
				}

				template <typename Tp2>
				KERBAL_CONSTEXPR
				__compressed_pair_impl(Tp2&& __first, compressed_pair_default_construct_tag)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<super, Tp2>::value) &&
												std::is_nothrow_default_constructible<second_type>::value
										) :
										super(std::forward<Tp2>(__first)), __second()
				{
				}


#		endif

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				__compressed_pair_impl(const kerbal::utility::compressed_pair<Tp2, Up2> & pair)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<super, const Tp2 &>::value) &&
												(std::is_nothrow_constructible<second_type, const Up2 &>::value)
										) :
										super(pair.first()), __second(pair.second())
				{
				}

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				__compressed_pair_impl(const std::pair<Tp2, Up2> & pair)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<super, const Tp2 &>::value) &&
												(std::is_nothrow_constructible<second_type, const Up2 &>::value)
										) :
										super(pair.first), __second(pair.second)
				{
				}


#		if __cplusplus >= 201103L

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				__compressed_pair_impl(kerbal::utility::compressed_pair<Tp2, Up2> && pair)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<super, Tp2 &&>::value) &&
												(std::is_nothrow_constructible<second_type, Up2 &&>::value)
										) :
										super(std::forward<Tp2>(pair.first())), __second(std::forward<Up2>(pair.second()))
				{
				}

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
				__compressed_pair_impl(std::pair<Tp2, Up2> && pair)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<super, Tp2 &&>::value) &&
												(std::is_nothrow_constructible<second_type, Up2 &&>::value)
										) :
										super(std::forward<Tp2>(pair.first)), __second(std::forward<Up2>(pair.second))
				{
				}

#		endif


			public:

				KERBAL_CONSTEXPR14
				__first_type_ref first() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return static_cast<__first_type_ref>(*this);
				}

				KERBAL_CONSTEXPR14
				__first_type_const_ref first() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return static_cast<__first_type_const_ref>(*this);
				}

				KERBAL_CONSTEXPR14
				__second_type_ref second() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->__second;
				}

				KERBAL_CONSTEXPR14
				__second_type_const_ref second() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->__second;
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				__first_type_rref first() && KERBAL_NOEXCEPT
				{
					return static_cast<__first_type_rref>(*this);
				}

				KERBAL_CONSTEXPR14
				__second_type_rref second() && KERBAL_NOEXCEPT
				{
					return std::move(this->__second);
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
				typedef typename kerbal::type_traits::remove_cv<Tp>::type super1;
				typedef typename kerbal::type_traits::remove_cv<Up>::type super2;

			private:
				typedef __compressed_pair_inner_typedef_helper<first_type, second_type> inner_typedef_helper;

			protected:
				typedef typename inner_typedef_helper::__first_type_ref             __first_type_ref;
				typedef typename inner_typedef_helper::__second_type_ref            __second_type_ref;
				typedef typename inner_typedef_helper::__first_type_const_ref       __first_type_const_ref;
				typedef typename inner_typedef_helper::__second_type_const_ref      __second_type_const_ref;

#		if __cplusplus >= 201103L
				typedef typename inner_typedef_helper::__first_type_rref             __first_type_rref;
				typedef typename inner_typedef_helper::__second_type_rref            __second_type_rref;
#		endif

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
				__first_type_ref first() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return static_cast<__first_type_ref>(*this);
				}

				KERBAL_CONSTEXPR14
				__first_type_const_ref first() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return static_cast<__first_type_const_ref>(*this);
				}

				KERBAL_CONSTEXPR14
				__second_type_ref second() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return static_cast<__second_type_ref>(*this);
				}

				KERBAL_CONSTEXPR14
				__second_type_const_ref second() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return static_cast<__second_type_const_ref>(*this);
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				__first_type_rref first() && KERBAL_NOEXCEPT
				{
					return static_cast<__first_type_rref>(*this);
				}

				KERBAL_CONSTEXPR14
				__second_type_rref second() && KERBAL_NOEXCEPT
				{
					return static_cast<__second_type_rref>(*this);
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


#	if __cplusplus >= 201402L

		template <typename Tp>
		struct can_be_compressed_pair_base : kerbal::type_traits::conditional_boolean<
												!std::is_final<Tp>::value && std::is_empty<Tp>::value
											>
		{
		};

#	else

		template <typename Tp>
		struct can_be_compressed_pair_base : kerbal::type_traits::false_type
		{
		};

#	endif


		template <typename Tp, typename Up>
		struct __compressed_pair_policy_switch :
				kerbal::utility::__compressed_pair_policy_switch_impl<
					typename kerbal::type_traits::remove_cv<Tp>::type,
					typename kerbal::type_traits::remove_cv<Up>::type,
					kerbal::utility::can_be_compressed_pair_base<Tp>::value,
					kerbal::utility::can_be_compressed_pair_base<Up>::value
				>
		{
		};

		template <typename Tp, typename Up>
		struct compressed_pair : public kerbal::utility::__compressed_pair_impl<Tp, Up, __compressed_pair_policy_switch<Tp, Up>::value >
		{
			public:
				typedef Tp first_type;
				typedef Up second_type;

			private:
				typedef kerbal::utility::__compressed_pair_impl<Tp, Up, __compressed_pair_policy_switch<Tp, Up>::value > super;

			protected:
				typedef typename super::__first_type_ref             __first_type_ref;
				typedef typename super::__second_type_ref            __second_type_ref;
				typedef typename super::__first_type_const_ref       __first_type_const_ref;
				typedef typename super::__second_type_const_ref      __second_type_const_ref;

#		if __cplusplus >= 201103L
				typedef typename super::__first_type_rref             __first_type_rref;
				typedef typename super::__second_type_rref            __second_type_rref;
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
				compressed_pair(const kerbal::utility::compressed_pair<Tp2, Up2> & pair)
								KERBAL_CONDITIONAL_NOEXCEPT(
										(std::is_nothrow_constructible<super, const kerbal::utility::compressed_pair<Tp2, Up2> &>::value)
								) :
								super(pair)
				{
				}

				template <typename Tp2, typename Up2>
				KERBAL_CONSTEXPR14
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

		};

		template <typename Tp, typename Up>
		bool operator==(const kerbal::utility::compressed_pair<Tp, Up>& lhs, const kerbal::utility::compressed_pair<Tp, Up>& rhs)
		{
			return lhs.first == rhs.first && lhs.second == rhs.second;
		}

		template <typename Tp, typename Up>
		bool operator!=(const kerbal::utility::compressed_pair<Tp, Up>& lhs, const kerbal::utility::compressed_pair<Tp, Up>& rhs)
		{
			return lhs.first != rhs.first || lhs.second != rhs.second;
		}

		template <typename Tp, typename Up>
		bool operator<(const kerbal::utility::compressed_pair<Tp, Up>& lhs, const kerbal::utility::compressed_pair<Tp, Up>& rhs)
		{
			return lhs.first < rhs.first
				|| (!(rhs.first < lhs.first) && lhs.second < rhs.second);
		}

		template <typename Tp, typename Up>
		bool operator>(const kerbal::utility::compressed_pair<Tp, Up>& lhs, const kerbal::utility::compressed_pair<Tp, Up>& rhs)
		{
			return rhs < lhs;
		}

		template <typename Tp, typename Up>
		bool operator<=(const kerbal::utility::compressed_pair<Tp, Up>& lhs, const kerbal::utility::compressed_pair<Tp, Up>& rhs)
		{
			return !(rhs < lhs);
		}

		template <typename Tp, typename Up>
		bool operator>=(const kerbal::utility::compressed_pair<Tp, Up>& lhs, const kerbal::utility::compressed_pair<Tp, Up>& rhs)
		{
			return !(lhs < rhs);
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

	template <std::size_t, typename>
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

	template <std::size_t _Int>
	struct __kerbal_compressed_pair_get;

	template <>
	struct __kerbal_compressed_pair_get<0>
	{
			template <typename Tp, typename Up>
			static constexpr Tp&
			__get(kerbal::utility::compressed_pair<Tp, Up>& __pair) noexcept
			{
				return __pair.first();
			}

			template <typename Tp, typename Up>
			static constexpr Tp&&
			__move_get(kerbal::utility::compressed_pair<Tp, Up>&& __pair) noexcept
			{
				return std::forward<Tp>(__pair.first());
			}

			template <typename Tp, typename Up>
			static constexpr const Tp&
			__const_get(const kerbal::utility::compressed_pair<Tp, Up>& __pair) noexcept
			{
				return __pair.first();
			}

			template <typename Tp, typename Up>
			static constexpr const Tp&&
			__const_move_get(const kerbal::utility::compressed_pair<Tp, Up>&& __pair) noexcept
			{
				return std::forward<const Tp>(__pair.first());
			}
	};

	template <>
	struct __kerbal_compressed_pair_get<1>
	{
			template <typename Tp, typename Up>
			static constexpr Up&
			__get(kerbal::utility::compressed_pair<Tp, Up>& __pair) noexcept
			{
				return __pair.second();
			}

			template <typename Tp, typename Up>
			static constexpr Up&&
			__move_get(kerbal::utility::compressed_pair<Tp, Up>&& __pair) noexcept
			{
				return std::forward<Up>(__pair.second());
			}

			template <typename Tp, typename Up>
			static constexpr const Up&
			__const_get(const kerbal::utility::compressed_pair<Tp, Up>& __pair) noexcept
			{
				return __pair.second();
			}

			template <typename Tp, typename Up>
			static constexpr const Up&&
			__const_move_get(const kerbal::utility::compressed_pair<Tp, Up>&& __pair) noexcept
			{
				return std::forward<const Up>(__pair.second());
			}
	};

	template <std::size_t _Int, typename Tp, typename Up>
	constexpr
	auto&
	get(kerbal::utility::compressed_pair<Tp, Up>& pair) noexcept
	{
		return __kerbal_compressed_pair_get<_Int>::__get(pair);
	}

	template <std::size_t _Int, typename Tp, typename Up>
	constexpr
	auto&&
	get(kerbal::utility::compressed_pair<Tp, Up>&& pair) noexcept
	{
		return __kerbal_compressed_pair_get<_Int>::__move_get(std::move(pair));
	}

	template <std::size_t _Int, typename Tp, typename Up>
	constexpr
	const auto&
	get(const kerbal::utility::compressed_pair<Tp, Up>& pair) noexcept
	{
		return __kerbal_compressed_pair_get<_Int>::__const_get(pair);
	}

	template <std::size_t _Int, typename Tp, typename Up>
	constexpr
	const auto&&
	get(const kerbal::utility::compressed_pair<Tp, Up>&& pair) noexcept
	{
		return __kerbal_compressed_pair_get<_Int>::__const_move_get(std::move(pair));
	}

} // namespace std

#endif

#endif // KERBAL_UTILITY_COMPRESSED_PAIR_HPP
