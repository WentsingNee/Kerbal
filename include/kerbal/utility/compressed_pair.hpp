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

#ifndef KERBAL_UTILITY_COMPRESSED_PAIR_HPP_
#define KERBAL_UTILITY_COMPRESSED_PAIR_HPP_

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/type_traits_details/cv_deduction.hpp>
#include <kerbal/type_traits/type_traits_details/integral_constant.hpp>
#include <kerbal/type_traits/type_traits_details/logical.hpp>

#if __cplusplus >= 201103L
# include <type_traits>
# include <utility>
#endif

namespace kerbal
{
	namespace utility
	{

		struct compressed_pair_default_construct_tag
		{
		};

		template <typename Tp, typename Up, int>
		struct __compressed_pair_impl;

		template <typename Tp, typename Up>
		struct __compressed_pair_impl<Tp, Up, 0>
		{
			public:
				typedef Tp first_type;
				typedef Up second_type;

			private:
				first_type __first;
				second_type __second;

			protected:
				typedef typename kerbal::type_traits::add_lvalue_reference<first_type>::type             __first_type_ref;
				typedef typename kerbal::type_traits::add_lvalue_reference<second_type>::type            __second_type_ref;
				typedef typename kerbal::type_traits::add_const_lvalue_reference<first_type>::type       __first_type_const_ref;
				typedef typename kerbal::type_traits::add_const_lvalue_reference<second_type>::type      __second_type_const_ref;

				KERBAL_CONSTEXPR
				__compressed_pair_impl()
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_default_constructible<first_type>::value &&
												std::is_nothrow_default_constructible<second_type>::value
										) :
										__first(), __second()
				{
				}

				KERBAL_CONSTEXPR
				__compressed_pair_impl(compressed_pair_default_construct_tag, __second_type_const_ref __second)
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_default_constructible<first_type>::value &&
												std::is_nothrow_copy_constructible<second_type>::value
										) :
										__first(), __second(__second)
				{
				}

				KERBAL_CONSTEXPR
				__compressed_pair_impl(__first_type_const_ref __first, compressed_pair_default_construct_tag)
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_copy_constructible<first_type>::value &&
												std::is_nothrow_default_constructible<second_type>::value
										) :
										__first(__first), __second()
				{
				}

				KERBAL_CONSTEXPR
				__compressed_pair_impl(__first_type_const_ref __first, __second_type_const_ref __second)
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_copy_constructible<first_type>::value &&
												std::is_nothrow_copy_constructible<second_type>::value
										) :
										__first(__first), __second(__second)
				{
				}

			public:
				KERBAL_CONSTEXPR14
				__first_type_ref first() KERBAL_NOEXCEPT
				{
					return this->__first;
				}

				KERBAL_CONSTEXPR14
				__first_type_const_ref first() const KERBAL_NOEXCEPT
				{
					return this->__first;
				}

				KERBAL_CONSTEXPR14
				__second_type_ref second() KERBAL_NOEXCEPT
				{
					return this->__second;
				}

				KERBAL_CONSTEXPR14
				__second_type_const_ref second() const KERBAL_NOEXCEPT
				{
					return this->__second;
				}
		};

		template <typename Tp, typename Up>
		struct __compressed_pair_impl<Tp, Up, 1> : private kerbal::type_traits::remove_cv<Up>::type
		{
			public:
				typedef Tp first_type;
				typedef Up second_type;

			private:
				first_type __first;
				typedef typename kerbal::type_traits::remove_cv<Up>::type super;

				typedef typename kerbal::type_traits::add_lvalue_reference<first_type>::type             __first_type_ref;
				typedef typename kerbal::type_traits::add_lvalue_reference<second_type>::type            __second_type_ref;
				typedef typename kerbal::type_traits::add_const_lvalue_reference<first_type>::type       __first_type_const_ref;
				typedef typename kerbal::type_traits::add_const_lvalue_reference<second_type>::type      __second_type_const_ref;

			protected:
				KERBAL_CONSTEXPR
				__compressed_pair_impl()
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_default_constructible<first_type>::value &&
												std::is_nothrow_default_constructible<second_type>::value
										) :
										super(), __first()
				{
				}

				KERBAL_CONSTEXPR
				__compressed_pair_impl(compressed_pair_default_construct_tag, __second_type_const_ref __second)
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_default_constructible<first_type>::value &&
												std::is_nothrow_copy_constructible<second_type>::value
										) :
										super(__second), __first()
				{
				}

				KERBAL_CONSTEXPR
				__compressed_pair_impl(__first_type_const_ref __first, compressed_pair_default_construct_tag)
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_copy_constructible<first_type>::value &&
												std::is_nothrow_default_constructible<second_type>::value
										) :
										super(), __first(__first)
				{
				}

				KERBAL_CONSTEXPR
				__compressed_pair_impl(__first_type_const_ref __first, __second_type_const_ref __second)
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_copy_constructible<first_type>::value &&
												std::is_nothrow_copy_constructible<second_type>::value
										) :
										super(__second), __first(__first)
				{
				}

			public:
				KERBAL_CONSTEXPR14
				__first_type_ref first() KERBAL_NOEXCEPT
				{
					return this->__first;
				}

				KERBAL_CONSTEXPR14
				__first_type_const_ref first() const KERBAL_NOEXCEPT
				{
					return this->__first;
				}

				KERBAL_CONSTEXPR14
				__second_type_ref second() KERBAL_NOEXCEPT
				{
					return static_cast<__second_type_ref>(*this);
				}

				KERBAL_CONSTEXPR14
				__second_type_const_ref second() const KERBAL_NOEXCEPT
				{
					return static_cast<__second_type_const_ref>(*this);
				}
		};

		template <typename Tp, typename Up>
		struct __compressed_pair_impl<Tp, Up, 2> : private kerbal::type_traits::remove_cv<Tp>::type
		{
			public:
				typedef Tp first_type;
				typedef Up second_type;

			private:
				second_type __second;

				typedef typename kerbal::type_traits::add_lvalue_reference<first_type>::type             __first_type_ref;
				typedef typename kerbal::type_traits::add_lvalue_reference<second_type>::type            __second_type_ref;
				typedef typename kerbal::type_traits::add_const_lvalue_reference<first_type>::type       __first_type_const_ref;
				typedef typename kerbal::type_traits::add_const_lvalue_reference<second_type>::type      __second_type_const_ref;

			protected:
				KERBAL_CONSTEXPR
				__compressed_pair_impl()
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_default_constructible<first_type>::value &&
												std::is_nothrow_default_constructible<second_type>::value
										) :
								Tp(), __second()
				{
				}

				KERBAL_CONSTEXPR
				__compressed_pair_impl(compressed_pair_default_construct_tag, __second_type_const_ref __second)
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_default_constructible<first_type>::value &&
												std::is_nothrow_copy_constructible<second_type>::value
										) :
								Tp(), __second(__second)
				{
				}

				KERBAL_CONSTEXPR
				__compressed_pair_impl(__first_type_const_ref __first, compressed_pair_default_construct_tag)
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_copy_constructible<first_type>::value &&
												std::is_nothrow_default_constructible<second_type>::value
										) :
								Tp(__first), __second()
				{
				}

				KERBAL_CONSTEXPR
				__compressed_pair_impl(__first_type_const_ref __first, __second_type_const_ref __second)
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_copy_constructible<first_type>::value &&
												std::is_nothrow_copy_constructible<second_type>::value
										) :
								Tp(__first), __second(__second)
				{
				}

			public:
				KERBAL_CONSTEXPR14
				__first_type_ref first() KERBAL_NOEXCEPT
				{
					return static_cast<__first_type_ref>(*this);
				}

				KERBAL_CONSTEXPR14
				__first_type_const_ref first() const KERBAL_NOEXCEPT
				{
					return static_cast<__first_type_const_ref>(*this);
				}

				KERBAL_CONSTEXPR14
				__second_type_ref second() KERBAL_NOEXCEPT
				{
					return this->__second;
				}

				KERBAL_CONSTEXPR14
				__second_type_const_ref second() const KERBAL_NOEXCEPT
				{
					return this->__second;
				}
		};

		template <typename Tp, typename Up>
		struct __compressed_pair_impl<Tp, Up, 3> :
													private kerbal::type_traits::remove_cv<Tp>::type,
													private kerbal::type_traits::remove_cv<Up>::type
		{
			public:
				typedef Tp first_type;
				typedef Up second_type;

			private:
				typedef typename kerbal::type_traits::add_lvalue_reference<first_type>::type             __first_type_ref;
				typedef typename kerbal::type_traits::add_lvalue_reference<second_type>::type            __second_type_ref;
				typedef typename kerbal::type_traits::add_const_lvalue_reference<first_type>::type       __first_type_const_ref;
				typedef typename kerbal::type_traits::add_const_lvalue_reference<second_type>::type      __second_type_const_ref;

			protected:
				KERBAL_CONSTEXPR
				__compressed_pair_impl()
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_default_constructible<first_type>::value &&
												std::is_nothrow_default_constructible<second_type>::value
										) :
								Tp(), Up()
				{
				}

				KERBAL_CONSTEXPR
				__compressed_pair_impl(compressed_pair_default_construct_tag, __second_type_const_ref __second)
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_default_constructible<first_type>::value &&
												std::is_nothrow_copy_constructible<second_type>::value
										) :
								Tp(), Up(__second)
				{
				}

				KERBAL_CONSTEXPR
				__compressed_pair_impl(__first_type_const_ref __first, compressed_pair_default_construct_tag)
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_copy_constructible<first_type>::value &&
												std::is_nothrow_default_constructible<second_type>::value
										) :
								Tp(__first), Up()
				{
				}

				KERBAL_CONSTEXPR
				__compressed_pair_impl(__first_type_const_ref __first, __second_type_const_ref __second)
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_copy_constructible<first_type>::value &&
												std::is_nothrow_copy_constructible<second_type>::value
										) :
								Tp(__first), Up(__second)
				{
				}

			public:
				KERBAL_CONSTEXPR14
				__first_type_ref first() KERBAL_NOEXCEPT
				{
					return static_cast<__first_type_ref>(*this);
				}

				KERBAL_CONSTEXPR14
				__first_type_const_ref first() const KERBAL_NOEXCEPT
				{
					return static_cast<__first_type_const_ref>(*this);
				}

				KERBAL_CONSTEXPR14
				__second_type_ref second() KERBAL_NOEXCEPT
				{
					return static_cast<__second_type_ref>(*this);
				}

				KERBAL_CONSTEXPR14
				__second_type_const_ref second() const KERBAL_NOEXCEPT
				{
					return static_cast<__second_type_const_ref>(*this);
				}
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

				typedef typename kerbal::type_traits::add_const_lvalue_reference<first_type>::type       __first_type_const_ref;
				typedef typename kerbal::type_traits::add_const_lvalue_reference<second_type>::type      __second_type_const_ref;

			public:
				KERBAL_CONSTEXPR
				compressed_pair()
								KERBAL_CONDITIONAL_NOEXCEPT(
										std::is_nothrow_default_constructible<first_type>::value &&
										std::is_nothrow_default_constructible<second_type>::value
								) :
								super()
				{
				}

				KERBAL_CONSTEXPR
				compressed_pair(compressed_pair_default_construct_tag tag, __second_type_const_ref __second)
								KERBAL_CONDITIONAL_NOEXCEPT(
										std::is_nothrow_default_constructible<first_type>::value &&
										std::is_nothrow_copy_constructible<second_type>::value
								) :
								super(tag, __second)
				{
				}

				KERBAL_CONSTEXPR
				compressed_pair(__first_type_const_ref __first, compressed_pair_default_construct_tag tag)
								KERBAL_CONDITIONAL_NOEXCEPT(
										std::is_nothrow_copy_constructible<first_type>::value &&
										std::is_nothrow_default_constructible<second_type>::value
								) :
								super(__first, tag)
				{
				}

				KERBAL_CONSTEXPR
				compressed_pair(__first_type_const_ref __first, __second_type_const_ref __second)
								KERBAL_CONDITIONAL_NOEXCEPT(
										std::is_nothrow_copy_constructible<first_type>::value &&
										std::is_nothrow_copy_constructible<second_type>::value
								) :
								super(__first, __second)
				{
				}

		};

		template <typename Tp, typename Up>
		kerbal::utility::compressed_pair<Tp, Up>
		make_compressed_pair(const Tp & first, const Up & second)
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_copy_constructible<Tp>::value &&
												std::is_nothrow_copy_constructible<Up>::value
										)
		{
			return kerbal::utility::compressed_pair<Tp, Up>(first, second);
		}

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
			template <typename _Tp1, typename _Tp2>
			static constexpr _Tp1&
			__get(kerbal::utility::compressed_pair<_Tp1, _Tp2>& __pair) noexcept
			{
				return __pair.first();
			}

			template <typename _Tp1, typename _Tp2>
			static constexpr _Tp1&&
			__move_get(kerbal::utility::compressed_pair<_Tp1, _Tp2>&& __pair) noexcept
			{
				return std::forward<_Tp1>(__pair.first());
			}

			template <typename _Tp1, typename _Tp2>
			static constexpr const _Tp1&
			__const_get(const kerbal::utility::compressed_pair<_Tp1, _Tp2>& __pair) noexcept
			{
				return __pair.first();
			}

			template <typename _Tp1, typename _Tp2>
			static constexpr const _Tp1&&
			__const_move_get(const kerbal::utility::compressed_pair<_Tp1, _Tp2>&& __pair) noexcept
			{
				return std::forward<const _Tp1>(__pair.first());
			}
	};

	template <>
	struct __kerbal_compressed_pair_get<1>
	{
			template <typename _Tp1, typename _Tp2>
			static constexpr _Tp2&
			__get(kerbal::utility::compressed_pair<_Tp1, _Tp2>& __pair) noexcept
			{
				return __pair.second();
			}

			template <typename _Tp1, typename _Tp2>
			static constexpr _Tp2&&
			__move_get(kerbal::utility::compressed_pair<_Tp1, _Tp2>&& __pair) noexcept
			{
				return std::forward<_Tp2>(__pair.second());
			}

			template <typename _Tp1, typename _Tp2>
			static constexpr const _Tp2&
			__const_get(const kerbal::utility::compressed_pair<_Tp1, _Tp2>& __pair) noexcept
			{
				return __pair.second();
			}

			template <typename _Tp1, typename _Tp2>
			static constexpr const _Tp2&&
			__const_move_get(const kerbal::utility::compressed_pair<_Tp1, _Tp2>&& __pair) noexcept
			{
				return std::forward<const _Tp2>(__pair.second());
			}
	};

	template <std::size_t _Int, class _Tp1, class _Tp2>
	constexpr
	auto&
	get(kerbal::utility::compressed_pair<_Tp1, _Tp2>& __in) noexcept
	{
		return __kerbal_compressed_pair_get<_Int>::__get(__in);
	}

	template <std::size_t _Int, class _Tp1, class _Tp2>
	constexpr
	auto&&
	get(kerbal::utility::compressed_pair<_Tp1, _Tp2>&& __in) noexcept
	{
		return __kerbal_compressed_pair_get<_Int>::__move_get(std::move(__in));
	}

	template <std::size_t _Int, class _Tp1, class _Tp2>
	constexpr
	const auto&
	get(const kerbal::utility::compressed_pair<_Tp1, _Tp2>& __in) noexcept
	{
		return __kerbal_compressed_pair_get<_Int>::__const_get(__in);
	}

	template <std::size_t _Int, class _Tp1, class _Tp2>
	constexpr
	const auto&&
	get(const kerbal::utility::compressed_pair<_Tp1, _Tp2>&& __in) noexcept
	{
		return __kerbal_compressed_pair_get<_Int>::__const_move_get(std::move(__in));
	}

}

#endif

#endif /* KERBAL_UTILITY_COMPRESSED_PAIR_HPP_ */
