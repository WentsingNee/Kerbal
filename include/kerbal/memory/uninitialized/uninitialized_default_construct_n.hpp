/**
 * @file       uninitialized_default_construct_n.hpp
 * @brief
 * @date       2023-08-31
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_UNINITIALIZED_UNINITIALIZED_DEFAULT_CONSTRUCT_N_HPP
#define KERBAL_MEMORY_UNINITIALIZED_UNINITIALIZED_DEFAULT_CONSTRUCT_N_HPP

#include <kerbal/memory/detail/can_be_nothrow_advance_iterator.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/config/exceptions.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/memory/uninitialized/default_construct_at.hpp>
#include <kerbal/memory/uninitialized/uninitialized_transaction_failed_destroy.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_trivially_default_constructible.hpp>
#include <kerbal/type_traits/is_trivially_destructible.hpp>
#include <kerbal/type_traits/tribool_constant.hpp>


namespace kerbal
{

	namespace memory
	{

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> UI_DFT_CONSTRUCT_N_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> UI_DFT_CONSTRUCT_N_VER_NOTHROW_ITER_ADVANCE;
			typedef kerbal::type_traits::integral_constant<int, 2> UI_DFT_CONSTRUCT_N_VER_NO_CATCH;
			typedef kerbal::type_traits::integral_constant<int, 3> UI_DFT_CONSTRUCT_N_VER_TRIVIALLY;

#		if KERBAL_HAS_EXCEPTIONS_SUPPORT

			template <typename ForwardIterator, typename SizeType>
			KERBAL_CONSTEXPR20
			ForwardIterator k_uninitialized_default_construct_n(ForwardIterator first, SizeType n, UI_DFT_CONSTRUCT_N_VER_DEFAULT)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				bool iter_move_next_exception_happen = false;
				try {
					while (n > 0) {
						--n;
						iterator remain(current);
						kerbal::memory::default_construct_at(&*current); // new (&*current) T;
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
			ForwardIterator k_uninitialized_default_construct_n(ForwardIterator first, SizeType n, UI_DFT_CONSTRUCT_N_VER_NOTHROW_ITER_ADVANCE)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				try {
					while (n > 0) {
						--n;
						kerbal::memory::default_construct_at(&*current); // new (&*current) T;
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
			ForwardIterator k_uninitialized_default_construct_n(ForwardIterator first, SizeType n, UI_DFT_CONSTRUCT_N_VER_NO_CATCH)
			{
				while (n > 0) {
					--n;
					kerbal::memory::default_construct_at(&*first); // new (&*first) T;
					++first;
				}
				return first;
			}

			template <typename ForwardIterator, typename SizeType>
			KERBAL_CONSTEXPR14
			ForwardIterator k_uninitialized_default_construct_n(ForwardIterator first, SizeType n, UI_DFT_CONSTRUCT_N_VER_TRIVIALLY)
			{
				return kerbal::iterator::next(first, n);
			}


			template <typename ForwardIterator>
			struct un_default_construct_n_overload_version_impl
			{
				private:
					typedef ForwardIterator iterator;
					typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

				public:

#	if KERBAL_HAS_EXCEPTIONS_SUPPORT

					typedef typename kerbal::type_traits::conditional<
						kerbal::type_traits::try_test_is_trivially_default_constructible<value_type>::IS_TRUE::value,
						UI_DFT_CONSTRUCT_N_VER_TRIVIALLY,
						typename kerbal::type_traits::conditional<
							kerbal::type_traits::try_test_is_trivially_destructible<value_type>::IS_TRUE::value,
							UI_DFT_CONSTRUCT_N_VER_NO_CATCH,
							typename kerbal::type_traits::conditional<
								kerbal::memory::detail::can_be_nothrow_advance_iterator<iterator>::value,
								UI_DFT_CONSTRUCT_N_VER_NOTHROW_ITER_ADVANCE,
								UI_DFT_CONSTRUCT_N_VER_DEFAULT
							>::type
						>::type
					>::type type;

#	else

					typedef typename kerbal::type_traits::conditional<
						kerbal::type_traits::try_test_is_trivially_default_constructible<value_type>::IS_TRUE::value,
						UI_DFT_CONSTRUCT_N_VER_TRIVIALLY,
						UI_DFT_CONSTRUCT_N_VER_NO_CATCH
					>::type type;

#	endif

			};

			template <typename ForwardIterator>
			struct un_default_construct_n_overload_version :
					un_default_construct_n_overload_version_impl<ForwardIterator>::type
			{
			};

		} // namespace detail

		template <typename ForwardIterator, typename SizeType>
		KERBAL_CONSTEXPR14
		ForwardIterator uninitialized_default_construct_n(ForwardIterator first, SizeType n)
		{
			typedef ForwardIterator iterator;
			typedef kerbal::memory::detail::un_default_construct_n_overload_version<iterator> VER;
			return kerbal::memory::detail::k_uninitialized_default_construct_n(first, n, VER());
		}

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_UNINITIALIZED_UNINITIALIZED_DEFAULT_CONSTRUCT_N_HPP
