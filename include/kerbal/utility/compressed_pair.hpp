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
#include <kerbal/type_traits/type_traits_details/logical.hpp>

#if __cplusplus >= 201103L
# include <type_traits>
#endif

namespace kerbal
{
	namespace utility
	{

#	if __cplusplus >= 201403L

		template <typename Tp>
		struct can_be_compressed_pair_base : kerbal::type_traits::conjunction<
											kerbal::type_traits::negation<std::is_final<Tp> >,
											std::is_empty<Tp>
										>
		{
		};

#	else

		template <typename Tp>
		struct can_be_compressed_pair_base : kerbal::type_traits::false_type
		{
		};

#	endif

		template <typename Tp, typename Up, bool, bool>
		struct __compressed_pair_impl;

		template <typename Tp, typename Up>
		struct __compressed_pair_impl<Tp, Up, false, false>
		{
			public:
				typedef Tp first_type;
				typedef Up second_type;

			private:
				first_type __first;
				second_type __second;

			public:
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
				__compressed_pair_impl(const first_type & __first, const second_type & __second)
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_copy_constructible<first_type>::value &&
												std::is_nothrow_copy_constructible<second_type>::value
										) :
								__first(__first), __second(__second)
				{
				}

				KERBAL_CONSTEXPR14
				first_type& first() KERBAL_NOEXCEPT
				{
					return this->__first;
				}

				KERBAL_CONSTEXPR14
				const first_type& first() const KERBAL_NOEXCEPT
				{
					return this->__first;
				}

				KERBAL_CONSTEXPR14
				second_type& second() KERBAL_NOEXCEPT
				{
					return this->__second;
				}

				KERBAL_CONSTEXPR14
				const second_type& second() const KERBAL_NOEXCEPT
				{
					return this->__second;
				}
		};

		template <typename Tp, typename Up>
		struct __compressed_pair_impl<Tp, Up, false, true> : private Up
		{
			public:
				typedef Tp first_type;
				typedef Up second_type;

			private:
				first_type __first;

			public:
				KERBAL_CONSTEXPR
				__compressed_pair_impl()
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_default_constructible<first_type>::value &&
												std::is_nothrow_default_constructible<second_type>::value
										) :
								Up(), __first()
				{
				}

				KERBAL_CONSTEXPR
				__compressed_pair_impl(const first_type & __first, const second_type & __second)
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_copy_constructible<first_type>::value &&
												std::is_nothrow_copy_constructible<second_type>::value
										) :
								Up(__second), __first(__first)
				{
				}

				KERBAL_CONSTEXPR14
				first_type& first() KERBAL_NOEXCEPT
				{
					return this->__first;
				}

				KERBAL_CONSTEXPR14
				const first_type& first() const KERBAL_NOEXCEPT
				{
					return this->__first;
				}

				KERBAL_CONSTEXPR14
				second_type& second() KERBAL_NOEXCEPT
				{
					return static_cast<second_type&>(*this);
				}

				KERBAL_CONSTEXPR14
				const second_type& second() const KERBAL_NOEXCEPT
				{
					return static_cast<const second_type&>(*this);
				}
		};

		template <typename Tp, typename Up>
		struct __compressed_pair_impl<Tp, Up, true, false> : private Tp
		{
			public:
				typedef Tp first_type;
				typedef Up second_type;

			private:
				second_type __second;

			public:
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
				__compressed_pair_impl(const first_type & __first, const second_type & __second)
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_copy_constructible<first_type>::value &&
												std::is_nothrow_copy_constructible<second_type>::value
										) :
								Tp(__first), __second(__second)
				{
				}

				KERBAL_CONSTEXPR14
				first_type& first() KERBAL_NOEXCEPT
				{
					return static_cast<first_type&>(*this);
				}

				KERBAL_CONSTEXPR14
				const first_type& first() const KERBAL_NOEXCEPT
				{
					return static_cast<const first_type&>(*this);
				}

				KERBAL_CONSTEXPR14
				second_type& second() KERBAL_NOEXCEPT
				{
					return this->__second;
				}

				KERBAL_CONSTEXPR14
				const second_type& second() const KERBAL_NOEXCEPT
				{
					return this->__second;
				}
		};

		template <typename Tp>
		struct __compressed_pair_impl<Tp, Tp, true, true> : private Tp
		{
			public:
				typedef Tp first_type;
				typedef Tp second_type;

			private:
				second_type __second;

			public:
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
				__compressed_pair_impl(const first_type & __first, const second_type & __second)
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_copy_constructible<first_type>::value &&
												std::is_nothrow_copy_constructible<second_type>::value
										) :
								Tp(__first), __second(__second)
				{
				}

				KERBAL_CONSTEXPR14
				first_type& first() KERBAL_NOEXCEPT
				{
					return static_cast<first_type&>(*this);
				}

				KERBAL_CONSTEXPR14
				const first_type& first() const KERBAL_NOEXCEPT
				{
					return static_cast<const first_type&>(*this);
				}

				KERBAL_CONSTEXPR14
				second_type& second() KERBAL_NOEXCEPT
				{
					return this->__second;
				}

				KERBAL_CONSTEXPR14
				const second_type& second() const KERBAL_NOEXCEPT
				{
					return this->__second;
				}
		};

		template <typename Tp, typename Up>
		struct __compressed_pair_impl<Tp, Up, true, true> : private Tp, private Up
		{
			public:
				typedef Tp first_type;
				typedef Up second_type;

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
				__compressed_pair_impl(const first_type & __first, const second_type & __second)
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_copy_constructible<first_type>::value &&
												std::is_nothrow_copy_constructible<second_type>::value
										) :
								Tp(__first), Up(__second)
				{
				}

				KERBAL_CONSTEXPR14
				first_type& first() KERBAL_NOEXCEPT
				{
					return static_cast<first_type&>(*this);
				}

				KERBAL_CONSTEXPR14
				const first_type& first() const KERBAL_NOEXCEPT
				{
					return static_cast<const first_type&>(*this);
				}

				KERBAL_CONSTEXPR14
				second_type& second() KERBAL_NOEXCEPT
				{
					return static_cast<second_type&>(*this);
				}

				KERBAL_CONSTEXPR14
				const second_type& second() const KERBAL_NOEXCEPT
				{
					return static_cast<const second_type&>(*this);
				}
		};

		template <typename Tp, typename Up>
		struct compressed_pair : public __compressed_pair_impl<Tp, Up, can_be_compressed_pair_base<Tp>::value, can_be_compressed_pair_base<Up>::value >
		{
			private:
				typedef __compressed_pair_impl<Tp, Up, can_be_compressed_pair_base<Tp>::value, can_be_compressed_pair_base<Up>::value > supper_t;

			public:
				typedef Tp first_type;
				typedef Up second_type;

				KERBAL_CONSTEXPR
				compressed_pair()
								KERBAL_CONDITIONAL_NOEXCEPT(
										std::is_nothrow_default_constructible<first_type>::value &&
										std::is_nothrow_default_constructible<second_type>::value
								) :
								supper_t()
				{
				}

				KERBAL_CONSTEXPR
				compressed_pair(const first_type & __first, const second_type & __second)
								KERBAL_CONDITIONAL_NOEXCEPT(
										std::is_nothrow_copy_constructible<first_type>::value &&
										std::is_nothrow_copy_constructible<second_type>::value
								) :
								supper_t(__first, __second)
				{
				}

		};

		template <typename Tp, typename Up>
		compressed_pair<Tp, Up>
		make_compressed_pair(const Tp & first, const Up & second)
										KERBAL_CONDITIONAL_NOEXCEPT(
												std::is_nothrow_copy_constructible<Tp>::value &&
												std::is_nothrow_copy_constructible<Up>::value
										)
		{
			return compressed_pair<Tp, Up>(first, second);
		}

	} // namespace utility

} // namespace kerbal

#endif /* KERBAL_UTILITY_COMPRESSED_PAIR_HPP_ */
