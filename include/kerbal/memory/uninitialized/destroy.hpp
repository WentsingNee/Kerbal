/**
 * @file       destroy.hpp
 * @brief
 * @date       2021-03-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_UNINITIALIZED_DESTROY_HPP
#define KERBAL_MEMORY_UNINITIALIZED_DESTROY_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/type_traits/can_be_pseudo_destructible.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#if __cplusplus > 201703L
#	include <memory>
#endif


namespace kerbal
{

	namespace memory
	{

	//==================
	// forward declare

		template <typename Tp>
		KERBAL_CONSTEXPR14
		void destroy_on(Tp & plc);

		template <typename Tp>
		KERBAL_CONSTEXPR14
		void destroy_at(Tp * p);

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void destroy(ForwardIterator first, ForwardIterator last) KERBAL_NOEXCEPT;

		template <typename ForwardIterator, typename SizeType>
		KERBAL_CONSTEXPR14
		ForwardIterator destroy_n(ForwardIterator first, SizeType n) KERBAL_NOEXCEPT;

		template <typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		void reverse_destroy(BidirectionalIterator first, BidirectionalIterator last) KERBAL_NOEXCEPT;

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void uninitialized_transaction_failed_destroy(ForwardIterator first, ForwardIterator last) KERBAL_NOEXCEPT;



	//==================
	// destroy_on, destroy at

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0>		DESTROY_ON_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1>		DESTROY_ON_VER_TRIVIALLY;

			template <typename Tp>
			KERBAL_CONSTEXPR20
			void _K_destroy_on(Tp & plc, DESTROY_ON_VER_DEFAULT)
					KERBAL_CONDITIONAL_NOEXCEPT(
							std::is_nothrow_destructible<Tp>::value
					)
			{
				plc.~Tp();
			}

			template <typename Tp, std::size_t N>
			KERBAL_CONSTEXPR20
			void _K_destroy_on(Tp (& plc) [N], DESTROY_ON_VER_DEFAULT) KERBAL_NOEXCEPT
			{
				kerbal::memory::reverse_destroy(plc + 0, plc + N);
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			void _K_destroy_on(Tp & /*plc*/, DESTROY_ON_VER_TRIVIALLY) KERBAL_NOEXCEPT
			{
			}

		} // namespace detail

		template <typename Tp>
		struct destroy_on_overload_version :
				kerbal::type_traits::conditional<
						kerbal::type_traits::can_be_pseudo_destructible<Tp>::value,
						detail::DESTROY_ON_VER_TRIVIALLY,
						detail::DESTROY_ON_VER_DEFAULT
				>::type
		{
		};

		template <typename Tp>
		KERBAL_CONSTEXPR14
		void destroy_on(Tp & plc)
		{
			detail::_K_destroy_on(plc, destroy_on_overload_version<Tp>());
		}

		template <typename Tp>
		KERBAL_CONSTEXPR14
		void destroy_at(Tp * p)
		{
			kerbal::memory::destroy_on(*p);
		}



	//==================
	// destroy

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0>		DESTROY_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1>		DESTROY_VER_TRIVIALLY;

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR20
			void _K_destroy(ForwardIterator first, ForwardIterator last, DESTROY_VER_DEFAULT) KERBAL_NOEXCEPT
			{
				while (first != last) {
					kerbal::memory::destroy_on(*first);
					++first;
				}
			}

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR14
			void _K_destroy(ForwardIterator /*first*/, ForwardIterator /*last*/, DESTROY_VER_TRIVIALLY) KERBAL_NOEXCEPT
			{
			}

		} // namespace detail

		template <typename Tp>
		struct destroy_overload_version:
				kerbal::type_traits::conditional<
						kerbal::type_traits::can_be_pseudo_destructible<Tp>::value,
						detail::DESTROY_VER_TRIVIALLY,
						detail::DESTROY_VER_DEFAULT
				>::type
		{
		};

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void destroy(ForwardIterator first, ForwardIterator last) KERBAL_NOEXCEPT
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			detail::_K_destroy(first, last, destroy_overload_version<value_type>());
		}



	//==================
	// destroy_n

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0>		DESTROY_N_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1>		DESTROY_N_VER_TRIVIALLY;

			template <typename ForwardIterator, typename SizeType>
			KERBAL_CONSTEXPR20
			ForwardIterator _K_destroy_n(ForwardIterator first, SizeType n, DESTROY_N_VER_DEFAULT) KERBAL_NOEXCEPT
			{
				while (n > 0) {
					--n;
					kerbal::memory::destroy_on(*first);
					++first;
				}
				return first;
			}

			template <typename ForwardIterator, typename SizeType>
			KERBAL_CONSTEXPR14
			ForwardIterator _K_destroy_n(ForwardIterator first, SizeType n, DESTROY_N_VER_TRIVIALLY) KERBAL_NOEXCEPT
			{
				return kerbal::iterator::next(first, n);
			}

		} // namespace detail

		template <typename Tp>
		struct destroy_n_overload_version:
				kerbal::type_traits::conditional<
						kerbal::type_traits::can_be_pseudo_destructible<Tp>::value,
						detail::DESTROY_N_VER_TRIVIALLY,
						detail::DESTROY_N_VER_DEFAULT
				>::type
		{
		};

		template <typename ForwardIterator, typename SizeType>
		KERBAL_CONSTEXPR14
		ForwardIterator destroy_n(ForwardIterator first, SizeType n) KERBAL_NOEXCEPT
		{
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			return detail::_K_destroy_n(first, n, destroy_n_overload_version<value_type>());
		}



	//==================
	// reverse_destroy

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0>		RE_DESTROY_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1>		RE_DESTROY_VER_TRIVIALLY;

			template <typename BidirectionalIterator>
			KERBAL_CONSTEXPR20
			void _K_reverse_destroy(BidirectionalIterator first, BidirectionalIterator last, RE_DESTROY_VER_DEFAULT) KERBAL_NOEXCEPT
			{
				while (first != last) {
					--last;
					kerbal::memory::destroy_on(*last);
				}
			}

			template <typename BidirectionalIterator>
			KERBAL_CONSTEXPR14
			void _K_reverse_destroy(BidirectionalIterator /*first*/, BidirectionalIterator /*last*/, RE_DESTROY_VER_TRIVIALLY) KERBAL_NOEXCEPT
			{
			}

		} // namespace detail

		template <typename Tp>
		struct reverse_destroy_overload_version:
				kerbal::type_traits::conditional<
						kerbal::type_traits::can_be_pseudo_destructible<Tp>::value,
						detail::RE_DESTROY_VER_TRIVIALLY,
						detail::RE_DESTROY_VER_DEFAULT
				>::type
		{
		};

		template <typename BidirectionalIterator>
		KERBAL_CONSTEXPR14
		void reverse_destroy(BidirectionalIterator first, BidirectionalIterator last) KERBAL_NOEXCEPT
		{
			typedef BidirectionalIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			detail::_K_reverse_destroy(first, last, reverse_destroy_overload_version<value_type>());
		}



	//==================
	// uninitialized_transaction_failed_destroy

		namespace detail
		{

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR14
			void uninitialized_transaction_failed_destroy(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag) KERBAL_NOEXCEPT
			{
				kerbal::memory::destroy(first, last);
			}

			template <typename BidirectionalIterator>
			KERBAL_CONSTEXPR14
			void uninitialized_transaction_failed_destroy(BidirectionalIterator first, BidirectionalIterator last, std::bidirectional_iterator_tag) KERBAL_NOEXCEPT
			{
				kerbal::memory::reverse_destroy(first, last);
			}

		} // namespace detail

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void uninitialized_transaction_failed_destroy(ForwardIterator first, ForwardIterator last) KERBAL_NOEXCEPT
		{
			detail::uninitialized_transaction_failed_destroy(first, last, kerbal::iterator::iterator_category(first));
		}

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_UNINITIALIZED_DESTROY_HPP
