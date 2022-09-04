/**
 * @file       default_construct.hpp
 * @brief
 * @date       2021-03-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_UNINITIALIZED_DEFAULT_CONSTRUCT_HPP
#define KERBAL_MEMORY_UNINITIALIZED_DEFAULT_CONSTRUCT_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/memory/uninitialized/destroy.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#if __cplusplus < 201103L
#	include <kerbal/type_traits/can_be_pseudo_destructible.hpp>
#else
#	include <kerbal/type_traits/array_traits.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

#if __cplusplus >= 201103L
#	include <type_traits>
#endif

#if __cplusplus > 201703L
#	include <memory>
#endif

#include <kerbal/memory/detail/can_be_nothrow_advance_iterator.hpp>


namespace kerbal
{

	namespace memory
	{

	//==================
	// forward declare

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void uninitialized_default_construct(ForwardIterator first, ForwardIterator last);



	//==================
	// default_construct_at

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0>		DFT_CNSTRCT_AT_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1>		DFT_CNSTRCT_AT_VER_TRIVIALLY;

#	if __cplusplus <= 201703L

			template <typename Tp>
			Tp * _K_default_construct_at(Tp * p, DFT_CNSTRCT_AT_VER_DEFAULT)
					KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(::new (const_cast<void*>(static_cast<const volatile void*>(p))) Tp)
					)
			{
				::new (const_cast<void*>(static_cast<const volatile void*>(p))) Tp;
				return p;
			}

#	else

			template <typename Tp>
			KERBAL_CONSTEXPR20
			Tp * _K_default_construct_at(Tp * p, DFT_CNSTRCT_AT_VER_DEFAULT)
					KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(std::construct_at(p))
					)
			{
				std::construct_at(p);
				return p;
			}

#	endif

			template <typename Tp, std::size_t N>
			KERBAL_CONSTEXPR20
			Tp (* _K_default_construct_at(Tp (*p) [N], DFT_CNSTRCT_AT_VER_DEFAULT)) [N]
			{
				kerbal::memory::uninitialized_default_construct(*p + 0, *p + N);
				return p;
			}

			template <typename Tp>
			KERBAL_CONSTEXPR14
			Tp * _K_default_construct_at(Tp * p, DFT_CNSTRCT_AT_VER_TRIVIALLY) KERBAL_NOEXCEPT
			{
				return p;
			}

		} // namespace detail

#	if __cplusplus < 201103L

		template <typename Tp>
		struct default_construct_at_overload_version :
				kerbal::type_traits::conditional<
					kerbal::type_traits::can_be_pseudo_destructible<Tp>::value,
					detail::DFT_CNSTRCT_AT_VER_TRIVIALLY,
					detail::DFT_CNSTRCT_AT_VER_DEFAULT
				>::type
		{
		};

#	else

		template <typename Tp>
		struct default_construct_at_overload_version :
				kerbal::type_traits::conditional<
					std::is_trivially_default_constructible<
						typename kerbal::type_traits::remove_all_extents<Tp>::type
					>::value,
					detail::DFT_CNSTRCT_AT_VER_TRIVIALLY,
					detail::DFT_CNSTRCT_AT_VER_DEFAULT
				>::type
		{
		};

#	endif

		template <typename Tp>
		KERBAL_CONSTEXPR14
		Tp * default_construct_at(Tp * p)
				KERBAL_CONDITIONAL_NOEXCEPT(
					noexcept(detail::_K_default_construct_at(p, default_construct_at_overload_version<Tp>()))
				)
		{
			return detail::_K_default_construct_at(p, default_construct_at_overload_version<Tp>());
		}



	//==================
	// uninitialized_default_construct

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> UI_DFT_CONSTRUCT_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> UI_DFT_CONSTRUCT_VER_NOTHROW_ITER_ADVANCE;
			typedef kerbal::type_traits::integral_constant<int, 2> UI_DFT_CONSTRUCT_VER_NO_CATCH;
			typedef kerbal::type_traits::integral_constant<int, 3> UI_DFT_CONSTRUCT_VER_TRIVIALLY;

#		if __cpp_exceptions

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR20
			void _K_uninitialized_default_construct(ForwardIterator first, ForwardIterator last, UI_DFT_CONSTRUCT_VER_DEFAULT)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				bool iter_move_next_exception_happen = false;
				try {
					while (current != last) {
						iterator remain(current);
						kerbal::memory::default_construct_at(&*current); // new (&*current) Tp;
						try {
							++current;
						} catch (...) {
							kerbal::memory::destroy_on(*remain);
							kerbal::memory::uninitialized_transaction_failed_destroy(first, remain);
							iter_move_next_exception_happen = true;
							throw;
						}
					}
				} catch (...) {
					if (!iter_move_next_exception_happen) {
						kerbal::memory::uninitialized_transaction_failed_destroy(first, current);
					}
					throw;
				}
			}

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR20
			void _K_uninitialized_default_construct(ForwardIterator first, ForwardIterator last, UI_DFT_CONSTRUCT_VER_NOTHROW_ITER_ADVANCE)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				try {
					while (current != last) {
						kerbal::memory::default_construct_at(&*current); // new (&*current) Tp;
						++current;
					}
				} catch (...) {
					kerbal::memory::uninitialized_transaction_failed_destroy(first, current);
					throw;
				}
			}

#		endif

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR14
			void _K_uninitialized_default_construct(ForwardIterator first, ForwardIterator last, UI_DFT_CONSTRUCT_VER_NO_CATCH)
			{
				while (first != last) {
					kerbal::memory::default_construct_at(&*first); // new (&*first) Tp;
					++first;
				}
			}

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR14
			void _K_uninitialized_default_construct(ForwardIterator /*first*/, ForwardIterator /*last*/, UI_DFT_CONSTRUCT_VER_TRIVIALLY)
			{
			}

		} // namespace detail

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void uninitialized_default_construct(ForwardIterator first, ForwardIterator last)
		{
#	if __cpp_exceptions || __cplusplus >= 201103L
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			typedef typename kerbal::type_traits::remove_all_extents<value_type>::type remove_all_extents_type; // compatible with gcc-5
#	endif

#	if __cpp_exceptions

#		if __cplusplus < 201103L

			typedef typename kerbal::type_traits::conditional<
					kerbal::type_traits::can_be_pseudo_destructible<remove_all_extents_type>::value,
					detail::UI_DFT_CONSTRUCT_VER_NO_CATCH,
					typename kerbal::type_traits::conditional<
						detail::can_be_nothrow_advance_iterator<iterator>::value,
						detail::UI_DFT_CONSTRUCT_VER_NOTHROW_ITER_ADVANCE,
						detail::UI_DFT_CONSTRUCT_VER_DEFAULT
					>::type
			>::type VER;

#		else

			typedef typename kerbal::type_traits::conditional<
					std::is_trivially_default_constructible<remove_all_extents_type>::value,
					detail::UI_DFT_CONSTRUCT_VER_TRIVIALLY,
					typename kerbal::type_traits::conditional<
						std::is_trivially_destructible<remove_all_extents_type>::value,
						detail::UI_DFT_CONSTRUCT_VER_NO_CATCH,
						typename kerbal::type_traits::conditional<
							detail::can_be_nothrow_advance_iterator<iterator>::value,
							detail::UI_DFT_CONSTRUCT_VER_NOTHROW_ITER_ADVANCE,
							detail::UI_DFT_CONSTRUCT_VER_DEFAULT
						>::type
					>::type
			>::type VER;

#		endif

#	else

#		if __cplusplus < 201103L

			typedef detail::UI_DFT_CONSTRUCT_VER_NO_CATCH VER;

#		else

			typedef typename kerbal::type_traits::conditional<
					std::is_trivially_default_constructible<remove_all_extents_type>::value,
					detail::UI_DFT_CONSTRUCT_VER_TRIVIALLY,
					detail::UI_DFT_CONSTRUCT_VER_NO_CATCH
			>::type VER;

#		endif

#	endif

			detail::_K_uninitialized_default_construct(first, last, VER());
		}



	//==================
	// uninitialized_default_construct_n

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> UI_DFT_CONSTRUCT_N_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> UI_DFT_CONSTRUCT_N_VER_NOTHROW_ITER_ADVANCE;
			typedef kerbal::type_traits::integral_constant<int, 2> UI_DFT_CONSTRUCT_N_VER_NO_CATCH;
			typedef kerbal::type_traits::integral_constant<int, 3> UI_DFT_CONSTRUCT_N_VER_TRIVIALLY;

#		if __cpp_exceptions

			template <typename ForwardIterator, typename SizeType>
			KERBAL_CONSTEXPR20
			ForwardIterator _K_uninitialized_default_construct_n(ForwardIterator first, SizeType n, UI_DFT_CONSTRUCT_N_VER_DEFAULT)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				bool iter_move_next_exception_happen = false;
				try {
					while (n > 0) {
						--n;
						iterator remain(current);
						kerbal::memory::default_construct_at(&*current); // new (&*current) Tp;
						try {
							++current;
						} catch (...) {
							kerbal::memory::destroy_on(*remain);
							kerbal::memory::uninitialized_transaction_failed_destroy(first, remain);
							iter_move_next_exception_happen = true;
							throw;
						}
					}
					return current;
				} catch (...) {
					if (!iter_move_next_exception_happen) {
						kerbal::memory::uninitialized_transaction_failed_destroy(first, current);
					}
					throw;
				}
			}

			template <typename ForwardIterator, typename SizeType>
			KERBAL_CONSTEXPR20
			ForwardIterator _K_uninitialized_default_construct_n(ForwardIterator first, SizeType n, UI_DFT_CONSTRUCT_N_VER_NOTHROW_ITER_ADVANCE)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				try {
					while (n > 0) {
						--n;
						kerbal::memory::default_construct_at(&*current); // new (&*current) Tp;
						++current;
					}
					return current;
				} catch (...) {
					kerbal::memory::uninitialized_transaction_failed_destroy(first, current);
					throw;
				}
			}

#		endif

			template <typename ForwardIterator, typename SizeType>
			KERBAL_CONSTEXPR14
			ForwardIterator _K_uninitialized_default_construct_n(ForwardIterator first, SizeType n, UI_DFT_CONSTRUCT_N_VER_NO_CATCH)
			{
				while (n > 0) {
					--n;
					kerbal::memory::default_construct_at(&*first); // new (&*first) Tp;
					++first;
				}
				return first;
			}

			template <typename ForwardIterator, typename SizeType>
			KERBAL_CONSTEXPR14
			ForwardIterator _K_uninitialized_default_construct_n(ForwardIterator first, SizeType n, UI_DFT_CONSTRUCT_N_VER_TRIVIALLY)
			{
				return kerbal::iterator::next(first, n);
			}

		} // namespace detail

		template <typename ForwardIterator, typename SizeType>
		KERBAL_CONSTEXPR14
		ForwardIterator uninitialized_default_construct_n(ForwardIterator first, SizeType n)
		{
#	if __cpp_exceptions || __cplusplus >= 201103L
			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
			typedef typename kerbal::type_traits::remove_all_extents<value_type>::type remove_all_extents_type; // compatible with gcc-5
#	endif

#	if __cpp_exceptions

#		if __cplusplus < 201103L

			typedef typename kerbal::type_traits::conditional<
					kerbal::type_traits::can_be_pseudo_destructible<remove_all_extents_type>::value,
					detail::UI_DFT_CONSTRUCT_N_VER_NO_CATCH,
					typename kerbal::type_traits::conditional<
						detail::can_be_nothrow_advance_iterator<iterator>::value,
						detail::UI_DFT_CONSTRUCT_N_VER_NOTHROW_ITER_ADVANCE,
						detail::UI_DFT_CONSTRUCT_N_VER_DEFAULT
					>::type
			>::type VER;

#		else

			typedef typename kerbal::type_traits::conditional<
				std::is_trivially_default_constructible<remove_all_extents_type>::value,
				detail::UI_DFT_CONSTRUCT_N_VER_TRIVIALLY,
				typename kerbal::type_traits::conditional<
					std::is_trivially_destructible<remove_all_extents_type>::value,
					detail::UI_DFT_CONSTRUCT_N_VER_NO_CATCH,
					typename kerbal::type_traits::conditional<
						detail::can_be_nothrow_advance_iterator<iterator>::value,
						detail::UI_DFT_CONSTRUCT_N_VER_NOTHROW_ITER_ADVANCE,
						detail::UI_DFT_CONSTRUCT_N_VER_DEFAULT
					>::type
				>::type
			>::type VER;

#		endif

#	else

#		if __cplusplus < 201103L

			typedef detail::UI_DFT_CONSTRUCT_N_VER_NO_CATCH VER;

#		else

			typedef typename kerbal::type_traits::conditional<
				std::is_trivially_default_constructible<remove_all_extents_type>::value,
				detail::UI_DFT_CONSTRUCT_N_VER_TRIVIALLY,
				detail::UI_DFT_CONSTRUCT_N_VER_NO_CATCH
			>::type VER;

#		endif

#	endif

			return detail::_K_uninitialized_default_construct_n(first, n, VER());
		}


	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_UNINITIALIZED_DEFAULT_CONSTRUCT_HPP
