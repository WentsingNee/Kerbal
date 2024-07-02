/**
 * @file       construct.hpp
 * @brief
 * @date       2022-01-07
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_RAW_STORAGE_UNINITIALIZED_CONSTRUCT_HPP
#define KERBAL_MEMORY_RAW_STORAGE_UNINITIALIZED_CONSTRUCT_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/config/exceptions.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/memory/raw_storage_uninitialized/destroy.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_trivially_destructible.hpp>

#include <kerbal/memory/detail/can_be_nothrow_advance_iterator.hpp>


namespace kerbal
{

	namespace memory
	{

	//==================
	// raw_storage_uninitialized_value_construct

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> RAWST_UI_VAL_CONSTRUCT_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> RAWST_UI_VAL_CONSTRUCT_VER_NOTHROW_ITER_ADVANCE;
			typedef kerbal::type_traits::integral_constant<int, 2> RAWST_UI_VAL_CONSTRUCT_VER_NO_CATCH;

#		if KERBAL_HAS_EXCEPTIONS_SUPPORT

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR20
			void raw_storage_uninitialized_value_construct(ForwardIterator first, ForwardIterator last, RAWST_UI_VAL_CONSTRUCT_VER_DEFAULT)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				bool iter_move_next_exception_happen = false;
				try {
					while (current != last) {
						iterator remain(current);
						current->construct();
						try {
							++current;
						} catch (...) {
							remain->destroy();
							kerbal::memory::raw_storage_transaction_failed_destroy(first, remain);
							iter_move_next_exception_happen = true;
							throw;
						}
					}
				} catch (...) {
					if (!iter_move_next_exception_happen) {
						kerbal::memory::raw_storage_transaction_failed_destroy(first, current);
					}
					throw;
				}
			}

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR20
			void raw_storage_uninitialized_value_construct(ForwardIterator first, ForwardIterator last, RAWST_UI_VAL_CONSTRUCT_VER_NOTHROW_ITER_ADVANCE)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				try {
					while (current != last) {
						current->construct();
						++current;
					}
				} catch (...) {
					kerbal::memory::raw_storage_transaction_failed_destroy(first, current);
					throw;
				}
			}

#		endif

			template <typename ForwardIterator>
			KERBAL_CONSTEXPR14
			void raw_storage_uninitialized_value_construct(ForwardIterator first, ForwardIterator last, RAWST_UI_VAL_CONSTRUCT_VER_NO_CATCH)
			{
				while (first != last) {
					first->construct();
					++first;
				}
			}

		} // namespace detail

		template <typename ForwardIterator>
		KERBAL_CONSTEXPR14
		void raw_storage_uninitialized_value_construct(ForwardIterator first, ForwardIterator last)
		{

#	if KERBAL_HAS_EXCEPTIONS_SUPPORT

			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type raw_storage;
			typedef typename raw_storage::value_type value_type;

			typedef typename kerbal::type_traits::conditional<
					kerbal::type_traits::try_test_is_trivially_destructible<value_type>::IS_TRUE::value,
					detail::RAWST_UI_VAL_CONSTRUCT_VER_NO_CATCH,
					typename kerbal::type_traits::conditional<
							detail::can_be_nothrow_advance_iterator<iterator>::value,
							detail::RAWST_UI_VAL_CONSTRUCT_VER_NOTHROW_ITER_ADVANCE,
							detail::RAWST_UI_VAL_CONSTRUCT_VER_DEFAULT
					>::type
			>::type VER;

#	else

			typedef detail::RAWST_UI_VAL_CONSTRUCT_VER_NO_CATCH VER;

#	endif

			detail::raw_storage_uninitialized_value_construct(first, last, VER());
		}



	//==================
	// raw_storage_uninitialized_value_construct_n

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> RAWST_UI_VAL_CONSTRUCT_N_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> RAWST_UI_VAL_CONSTRUCT_N_VER_NOTHROW_ITER_ADVANCE;
			typedef kerbal::type_traits::integral_constant<int, 2> RAWST_UI_VAL_CONSTRUCT_N_VER_NO_CATCH;

#		if KERBAL_HAS_EXCEPTIONS_SUPPORT

			template <typename ForwardIterator, typename SizeType>
			KERBAL_CONSTEXPR20
			ForwardIterator raw_storage_uninitialized_value_construct_n(ForwardIterator first, SizeType n, RAWST_UI_VAL_CONSTRUCT_N_VER_DEFAULT)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				bool iter_move_next_exception_happen = false;
				try {
					while (n > 0) {
						--n;
						iterator remain(current);
						current->construct();
						try {
							++current;
						} catch (...) {
							remain->destroy();
							kerbal::memory::raw_storage_transaction_failed_destroy(first, remain);
							iter_move_next_exception_happen = true;
							throw;
						}
					}
					return current;
				} catch (...) {
					if (!iter_move_next_exception_happen) {
						kerbal::memory::raw_storage_transaction_failed_destroy(first, current);
					}
					throw;
				}
			}

			template <typename ForwardIterator, typename SizeType>
			KERBAL_CONSTEXPR20
			ForwardIterator raw_storage_uninitialized_value_construct_n(ForwardIterator first, SizeType n, RAWST_UI_VAL_CONSTRUCT_N_VER_NOTHROW_ITER_ADVANCE)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				try {
					while (n > 0) {
						--n;
						current->construct();
						++current;
					}
					return current;
				} catch (...) {
					kerbal::memory::raw_storage_transaction_failed_destroy(first, current);
					throw;
				}
			}

#		endif

			template <typename ForwardIterator, typename SizeType>
			KERBAL_CONSTEXPR14
			ForwardIterator raw_storage_uninitialized_value_construct_n(ForwardIterator first, SizeType n, RAWST_UI_VAL_CONSTRUCT_N_VER_NO_CATCH)
			{
				while (n > 0) {
					--n;
					first->construct();
					++first;
				}
				return first;
			}

		} // namespace detail

		template <typename ForwardIterator, typename SizeType>
		KERBAL_CONSTEXPR14
		ForwardIterator raw_storage_uninitialized_value_construct_n(ForwardIterator first, SizeType n)
		{

#	if KERBAL_HAS_EXCEPTIONS_SUPPORT

			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type raw_storage;
			typedef typename raw_storage::value_type value_type;

			typedef typename kerbal::type_traits::conditional<
					kerbal::type_traits::try_test_is_trivially_destructible<value_type>::IS_TRUE::value,
					detail::RAWST_UI_VAL_CONSTRUCT_N_VER_NO_CATCH,
					typename kerbal::type_traits::conditional<
							detail::can_be_nothrow_advance_iterator<iterator>::value,
							detail::RAWST_UI_VAL_CONSTRUCT_N_VER_NOTHROW_ITER_ADVANCE,
							detail::RAWST_UI_VAL_CONSTRUCT_N_VER_DEFAULT
					>::type
			>::type VER;

#	else

			typedef detail::RAWST_UI_VAL_CONSTRUCT_N_VER_NO_CATCH VER;

#	endif

			return detail::raw_storage_uninitialized_value_construct_n(first, n, VER());
		}



	//==================
	// raw_storage_uninitialized_copy

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> RAWST_UICPY_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> RAWST_UICPY_VER_NOTHROW_ITER_ADVANCE;
			typedef kerbal::type_traits::integral_constant<int, 2> RAWST_UICPY_VER_NO_CATCH;

#		if KERBAL_HAS_EXCEPTIONS_SUPPORT

			template <typename InputIterator, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator raw_storage_uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator to, RAWST_UICPY_VER_DEFAULT)
			{
				typedef ForwardIterator iterator;
				iterator current(to);
				bool iter_move_next_exception_happen = false;
				try {
					while (first != last) {
						iterator remain(current);
						current->construct(*first);
						try {
							++current;
						} catch (...) {
							remain->destroy();
							kerbal::memory::raw_storage_transaction_failed_destroy(to, remain);
							iter_move_next_exception_happen = true;
							throw;
						}
						++first;
					}
					return current;
				} catch (...) {
					if (!iter_move_next_exception_happen) {
						kerbal::memory::raw_storage_transaction_failed_destroy(to, current);
					}
					throw;
				}
			}

			template <typename InputIterator, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator raw_storage_uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator to, RAWST_UICPY_VER_NOTHROW_ITER_ADVANCE)
			{
				typedef ForwardIterator iterator;
				iterator current(to);
				try {
					while (first != last) {
						current->construct(*first);
						++current;
						++first;
					}
					return current;
				} catch (...) {
					kerbal::memory::raw_storage_transaction_failed_destroy(to, current);
					throw;
				}
			}

#		endif

			template <typename InputIterator, typename ForwardIterator>
			KERBAL_CONSTEXPR14
			ForwardIterator raw_storage_uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator to, RAWST_UICPY_VER_NO_CATCH)
			{
				while (first != last) {
					to->construct(*first);
					++to;
					++first;
				}
				return to;
			}

		} // namespace detail

		template <typename InputIterator, typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator raw_storage_uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator to)
		{

#	if KERBAL_HAS_EXCEPTIONS_SUPPORT

			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type raw_storage;
			typedef typename raw_storage::value_type value_type;

			typedef typename kerbal::type_traits::conditional<
					kerbal::type_traits::try_test_is_trivially_destructible<value_type>::IS_TRUE::value,
					detail::RAWST_UICPY_VER_NO_CATCH,
					typename kerbal::type_traits::conditional<
							detail::can_be_nothrow_advance_iterator<iterator>::value,
							detail::RAWST_UICPY_VER_NOTHROW_ITER_ADVANCE,
							detail::RAWST_UICPY_VER_DEFAULT
					>::type
			>::type VER;

#	else

			typedef detail::RAWST_UICPY_VER_NO_CATCH VER;

#	endif

			return detail::raw_storage_uninitialized_copy(first, last, to, VER());
		}



	//==================
	// raw_storage_uninitialized_copy_n

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> RAWST_UICPY_N_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> RAWST_UICPY_N_VER_NOTHROW_ITER_ADVANCE;
			typedef kerbal::type_traits::integral_constant<int, 2> RAWST_UICPY_N_VER_NO_CATCH;

#		if KERBAL_HAS_EXCEPTIONS_SUPPORT

			template <typename InputIterator, typename SizeType, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator raw_storage_uninitialized_copy_n(InputIterator first, SizeType n, ForwardIterator to, RAWST_UICPY_N_VER_DEFAULT)
			{
				typedef ForwardIterator iterator;
				iterator current(to);
				bool iter_move_next_exception_happen = false;
				try {
					while (n > 0) {
						--n;
						iterator remain(current);
						current->construct(*first);
						try {
							++current;
						} catch (...) {
							remain->destroy();
							kerbal::memory::raw_storage_transaction_failed_destroy(to, remain);
							iter_move_next_exception_happen = true;
							throw;
						}
						++first;
					}
					return current;
				} catch (...) {
					if (!iter_move_next_exception_happen) {
						kerbal::memory::raw_storage_transaction_failed_destroy(to, current);
					}
					throw;
				}
			}

			template <typename InputIterator, typename SizeType, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator raw_storage_uninitialized_copy_n(InputIterator first, SizeType n, ForwardIterator to, RAWST_UICPY_N_VER_NOTHROW_ITER_ADVANCE)
			{
				typedef ForwardIterator iterator;
				iterator current(to);
				try {
					while (n > 0) {
						--n;
						current->construct(*first);
						++current;
						++first;
					}
					return current;
				} catch (...) {
					kerbal::memory::raw_storage_transaction_failed_destroy(to, current);
					throw;
				}
			}

#		endif

			template <typename InputIterator, typename SizeType, typename ForwardIterator>
			KERBAL_CONSTEXPR14
			ForwardIterator raw_storage_uninitialized_copy_n(InputIterator first, SizeType n, ForwardIterator to, RAWST_UICPY_N_VER_NO_CATCH)
			{
				while (n > 0) {
					--n;
					to->construct(*first);
					++to;
					++first;
				}
				return to;
			}

		} // namespace detail

		template <typename InputIterator, typename SizeType, typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator raw_storage_uninitialized_copy_n(InputIterator first, SizeType n, ForwardIterator to)
		{

#	if KERBAL_HAS_EXCEPTIONS_SUPPORT

			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type raw_storage;
			typedef typename raw_storage::value_type value_type;

			typedef typename kerbal::type_traits::conditional<
					kerbal::type_traits::try_test_is_trivially_destructible<value_type>::IS_TRUE::value,
					detail::RAWST_UICPY_N_VER_NO_CATCH,
					typename kerbal::type_traits::conditional<
							detail::can_be_nothrow_advance_iterator<iterator>::value,
							detail::RAWST_UICPY_N_VER_NOTHROW_ITER_ADVANCE,
							detail::RAWST_UICPY_N_VER_DEFAULT
					>::type
			>::type VER;

#	else

			typedef detail::RAWST_UICPY_N_VER_NO_CATCH VER;

#	endif

			return detail::raw_storage_uninitialized_copy_n(first, n, to, VER());
		}



	//==================
	// raw_storage_uninitialized_move

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> RAWST_UIMOV_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> RAWST_UIMOV_VER_NOTHROW_ITER_ADVANCE;
			typedef kerbal::type_traits::integral_constant<int, 2> RAWST_UIMOV_VER_NO_CATCH;

#		if KERBAL_HAS_EXCEPTIONS_SUPPORT

			template <typename InputIterator, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator raw_storage_uninitialized_move(InputIterator first, InputIterator last, ForwardIterator to, RAWST_UIMOV_VER_DEFAULT)
			{
				typedef ForwardIterator iterator;
				iterator current(to);
				bool iter_move_next_exception_happen = false;
				try {
					while (first != last) {
						iterator remain(current);
						current->construct(kerbal::compatibility::to_xvalue(*first));
						try {
							++current;
						} catch (...) {
							remain->destroy();
							kerbal::memory::raw_storage_transaction_failed_destroy(to, remain);
							iter_move_next_exception_happen = true;
							throw;
						}
						++first;
					}
					return current;
				} catch (...) {
					if (!iter_move_next_exception_happen) {
						kerbal::memory::raw_storage_transaction_failed_destroy(to, current);
					}
					throw;
				}
			}

			template <typename InputIterator, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator raw_storage_uninitialized_move(InputIterator first, InputIterator last, ForwardIterator to, RAWST_UIMOV_VER_NOTHROW_ITER_ADVANCE)
			{
				typedef ForwardIterator iterator;
				iterator current(to);
				try {
					while (first != last) {
						current->construct(kerbal::compatibility::to_xvalue(*first));
						++current;
						++first;
					}
					return current;
				} catch (...) {
					kerbal::memory::raw_storage_transaction_failed_destroy(to, current);
					throw;
				}
			}

#		endif

			template <typename InputIterator, typename ForwardIterator>
			KERBAL_CONSTEXPR14
			ForwardIterator raw_storage_uninitialized_move(InputIterator first, InputIterator last, ForwardIterator to, RAWST_UIMOV_VER_NO_CATCH)
			{
				while (first != last) {
					to->construct(kerbal::compatibility::to_xvalue(*first));
					++to;
					++first;
				}
				return to;
			}

		} // namespace detail

		template <typename InputIterator, typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator raw_storage_uninitialized_move(InputIterator first, InputIterator last, ForwardIterator to)
		{

#	if KERBAL_HAS_EXCEPTIONS_SUPPORT

			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type raw_storage;
			typedef typename raw_storage::value_type value_type;

			typedef typename kerbal::type_traits::conditional<
					kerbal::type_traits::try_test_is_trivially_destructible<value_type>::IS_TRUE::value,
					detail::RAWST_UIMOV_VER_NO_CATCH,
					typename kerbal::type_traits::conditional<
							detail::can_be_nothrow_advance_iterator<iterator>::value,
							detail::RAWST_UIMOV_VER_NOTHROW_ITER_ADVANCE,
							detail::RAWST_UIMOV_VER_DEFAULT
					>::type
			>::type VER;

#	else

			typedef detail::RAWST_UIMOV_VER_NO_CATCH VER;

#	endif

			return detail::raw_storage_uninitialized_move(first, last, to, VER());
		}



	//==================
	// raw_storage_uninitialized_move_n

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> RAWST_UIMOV_N_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> RAWST_UIMOV_N_VER_NOTHROW_ITER_ADVANCE;
			typedef kerbal::type_traits::integral_constant<int, 2> RAWST_UIMOV_N_VER_NO_CATCH;

#		if KERBAL_HAS_EXCEPTIONS_SUPPORT

			template <typename InputIterator, typename SizeType, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator raw_storage_uninitialized_move_n(InputIterator first, SizeType n, ForwardIterator to, RAWST_UIMOV_N_VER_DEFAULT)
			{
				typedef ForwardIterator iterator;
				iterator current(to);
				bool iter_move_next_exception_happen = false;
				try {
					while (n > 0) {
						--n;
						iterator remain(current);
						current->construct(kerbal::compatibility::to_xvalue(*first));
						try {
							++current;
						} catch (...) {
							remain->destroy();
							kerbal::memory::raw_storage_transaction_failed_destroy(to, remain);
							iter_move_next_exception_happen = true;
							throw;
						}
						++first;
					}
					return current;
				} catch (...) {
					if (!iter_move_next_exception_happen) {
						kerbal::memory::raw_storage_transaction_failed_destroy(to, current);
					}
					throw;
				}
			}

			template <typename InputIterator, typename SizeType, typename ForwardIterator>
			KERBAL_CONSTEXPR20
			ForwardIterator raw_storage_uninitialized_move_n(InputIterator first, SizeType n, ForwardIterator to, RAWST_UIMOV_N_VER_NOTHROW_ITER_ADVANCE)
			{
				typedef ForwardIterator iterator;
				iterator current(to);
				try {
					while (n > 0) {
						--n;
						current->construct(kerbal::compatibility::to_xvalue(*first));
						++current;
						++first;
					}
					return current;
				} catch (...) {
					kerbal::memory::raw_storage_transaction_failed_destroy(to, current);
					throw;
				}
			}

#		endif

			template <typename InputIterator, typename SizeType, typename ForwardIterator>
			KERBAL_CONSTEXPR14
			ForwardIterator raw_storage_uninitialized_move_n(InputIterator first, SizeType n, ForwardIterator to, RAWST_UIMOV_N_VER_NO_CATCH)
			{
				while (n > 0) {
					--n;
					to->construct(kerbal::compatibility::to_xvalue(*first));
					++to;
					++first;
				}
				return to;
			}

		} // namespace detail

		template <typename InputIterator, typename SizeType, typename ForwardIterator>
		KERBAL_CONSTEXPR14
		ForwardIterator raw_storage_uninitialized_move_n(InputIterator first, SizeType n, ForwardIterator to)
		{

#	if KERBAL_HAS_EXCEPTIONS_SUPPORT

			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type raw_storage;
			typedef typename raw_storage::value_type value_type;

			typedef typename kerbal::type_traits::conditional<
					kerbal::type_traits::try_test_is_trivially_destructible<value_type>::IS_TRUE::value,
					detail::RAWST_UIMOV_N_VER_NO_CATCH,
					typename kerbal::type_traits::conditional<
							detail::can_be_nothrow_advance_iterator<iterator>::value,
							detail::RAWST_UIMOV_N_VER_NOTHROW_ITER_ADVANCE,
							detail::RAWST_UIMOV_N_VER_DEFAULT
					>::type
			>::type VER;

#	else

			typedef detail::RAWST_UIMOV_N_VER_NO_CATCH VER;

#	endif

			return detail::raw_storage_uninitialized_move_n(first, n, to, VER());
		}



	//==================
	// raw_storage_uninitialized_fill

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> RAWST_UIFILL_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> RAWST_UIFILL_VER_NOTHROW_ITER_ADVANCE;
			typedef kerbal::type_traits::integral_constant<int, 2> RAWST_UIFILL_VER_NO_CATCH;

#		if KERBAL_HAS_EXCEPTIONS_SUPPORT

			template <typename ForwardIterator, typename T>
			KERBAL_CONSTEXPR20
			void raw_storage_uninitialized_fill(ForwardIterator first, ForwardIterator last, const T & value, RAWST_UIFILL_VER_DEFAULT)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				bool iter_move_next_exception_happen = false;
				try {
					while (current != last) {
						iterator remain(current);
						current->construct(value);
						try {
							++current;
						} catch (...) {
							remain->destroy();
							kerbal::memory::raw_storage_transaction_failed_destroy(first, remain);
							iter_move_next_exception_happen = true;
							throw;
						}
					}
				} catch (...) {
					if (!iter_move_next_exception_happen) {
						kerbal::memory::raw_storage_transaction_failed_destroy(first, current);
					}
					throw;
				}
			}

			template <typename ForwardIterator, typename T>
			KERBAL_CONSTEXPR20
			void raw_storage_uninitialized_fill(ForwardIterator first, ForwardIterator last, const T & value, RAWST_UIFILL_VER_NOTHROW_ITER_ADVANCE)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				try {
					while (current != last) {
						current->construct(value);
						++current;
					}
				} catch (...) {
					kerbal::memory::raw_storage_transaction_failed_destroy(first, current);
					throw;
				}
			}

#		endif

			template <typename ForwardIterator, typename T>
			KERBAL_CONSTEXPR14
			void raw_storage_uninitialized_fill(ForwardIterator first, ForwardIterator last, const T & value, RAWST_UIFILL_VER_NO_CATCH)
			{
				while (first != last) {
					first->construct(value);
					++first;
				}
			}

		} // namespace detail

		template <typename ForwardIterator, typename T>
		KERBAL_CONSTEXPR14
		void raw_storage_uninitialized_fill(ForwardIterator first, ForwardIterator last, const T & value)
		{

#	if KERBAL_HAS_EXCEPTIONS_SUPPORT

			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type raw_storage;
			typedef typename raw_storage::value_type value_type;

			typedef typename kerbal::type_traits::conditional<
					kerbal::type_traits::try_test_is_trivially_destructible<value_type>::IS_TRUE::value,
					detail::RAWST_UIFILL_VER_NO_CATCH,
					typename kerbal::type_traits::conditional<
							detail::can_be_nothrow_advance_iterator<iterator>::value,
							detail::RAWST_UIFILL_VER_NOTHROW_ITER_ADVANCE,
							detail::RAWST_UIFILL_VER_DEFAULT
					>::type
			>::type VER;

#	else

			typedef detail::RAWST_UIFILL_VER_NO_CATCH VER;

#	endif

			detail::raw_storage_uninitialized_fill(first, last, value, VER());
		}



	//==================
	// raw_storage_uninitialized_fill_n

		namespace detail
		{

			typedef kerbal::type_traits::integral_constant<int, 0> RAWST_UIFILL_N_VER_DEFAULT;
			typedef kerbal::type_traits::integral_constant<int, 1> RAWST_UIFILL_N_VER_NOTHROW_ITER_ADVANCE;
			typedef kerbal::type_traits::integral_constant<int, 2> RAWST_UIFILL_N_VER_NO_CATCH;

#		if KERBAL_HAS_EXCEPTIONS_SUPPORT

			template <typename ForwardIterator, typename SizeType, typename T>
			KERBAL_CONSTEXPR20
			ForwardIterator raw_storage_uninitialized_fill_n(ForwardIterator first, SizeType n, const T & value, RAWST_UIFILL_N_VER_DEFAULT)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				bool iter_move_next_exception_happen = false;
				try {
					while (n > 0) {
						--n;
						iterator remain(current);
						current->construct(value);
						try {
							++current;
						} catch (...) {
							remain->destroy();
							kerbal::memory::raw_storage_transaction_failed_destroy(first, remain);
							iter_move_next_exception_happen = true;
							throw;
						}
					}
					return current;
				} catch (...) {
					if (!iter_move_next_exception_happen) {
						kerbal::memory::raw_storage_transaction_failed_destroy(first, current);
					}
					throw;
				}
			}

			template <typename ForwardIterator, typename SizeType, typename T>
			KERBAL_CONSTEXPR20
			ForwardIterator raw_storage_uninitialized_fill_n(ForwardIterator first, SizeType n, const T & value, RAWST_UIFILL_N_VER_NOTHROW_ITER_ADVANCE)
			{
				typedef ForwardIterator iterator;
				iterator current(first);
				try {
					while (n > 0) {
						--n;
						current->construct(value);
						++current;
					}
					return current;
				} catch (...) {
					kerbal::memory::raw_storage_transaction_failed_destroy(first, current);
					throw;
				}
			}

#		endif

			template <typename ForwardIterator, typename SizeType, typename T>
			KERBAL_CONSTEXPR14
			ForwardIterator raw_storage_uninitialized_fill_n(ForwardIterator first, SizeType n, const T & value, RAWST_UIFILL_N_VER_NO_CATCH)
			{
				while (n > 0) {
					--n;
					first->construct(value);
					++first;
				}
				return first;
			}

		} // namespace detail

		template <typename ForwardIterator, typename SizeType, typename T>
		KERBAL_CONSTEXPR14
		ForwardIterator raw_storage_uninitialized_fill_n(ForwardIterator first, SizeType n, const T & value)
		{

#	if KERBAL_HAS_EXCEPTIONS_SUPPORT

			typedef ForwardIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type raw_storage;
			typedef typename raw_storage::value_type value_type;

			typedef typename kerbal::type_traits::conditional<
					kerbal::type_traits::try_test_is_trivially_destructible<value_type>::IS_TRUE::value,
					detail::RAWST_UIFILL_N_VER_NO_CATCH,
					typename kerbal::type_traits::conditional<
							detail::can_be_nothrow_advance_iterator<iterator>::value,
							detail::RAWST_UIFILL_N_VER_NOTHROW_ITER_ADVANCE,
							detail::RAWST_UIFILL_N_VER_DEFAULT
					>::type
			>::type VER;

#	else

			typedef detail::RAWST_UIFILL_N_VER_NO_CATCH VER;

#	endif

			return detail::raw_storage_uninitialized_fill_n(first, n, value, VER());
		}

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_RAW_STORAGE_UNINITIALIZED_CONSTRUCT_HPP
