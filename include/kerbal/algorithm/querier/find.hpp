/**
 * @file       find.hpp
 * @brief
 * @date       2021-05-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_QUERIER_FIND_HPP
#define KERBAL_ALGORITHM_QUERIER_FIND_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/is_constant_evaluated.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>


#include <kerbal/algorithm/querier/detail/find/find.plain.part.hpp>


#if 0
	// pass
#elif defined(__AVX2__)
#	define KERBAL_ALGORITHM_FIND_ENABLE_AVX2     1
#elif defined(__SSE4_1__)
#	define KERBAL_ALGORITHM_FIND_ENABLE_SSE4_1   1
#endif


#if KERBAL_ALGORITHM_FIND_ENABLE_AVX2
#	include <kerbal/algorithm/querier/detail/find/find.avx2.part.hpp>
#endif

#if KERBAL_ALGORITHM_FIND_ENABLE_SSE4_1
#	include <kerbal/algorithm/querier/detail/find/find.sse41.part.hpp>
#endif

// #include <kerbal/algorithm/querier/detail/find/find.mmx.part.hpp>



namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename T>
			const T *
			k_find_simd_size_handler(
				const T * first,
				const T * last,
				const T & x,
				kerbal::type_traits::integral_constant<std::size_t, 8>
			) KERBAL_NOEXCEPT
			{
				const char * r_first = reinterpret_cast<const char *>(first);
				const char * r_last = reinterpret_cast<const char *>(last);

#		if 0
				// pass
#		elif KERBAL_ALGORITHM_FIND_ENABLE_AVX2
				return reinterpret_cast<const T*>(avx2::find(r_first, r_last, x));
#		elif KERBAL_ALGORITHM_FIND_ENABLE_SSE4_1
				return reinterpret_cast<const T*>(sse41::find(r_first, r_last, x));
#		else
				return reinterpret_cast<const T*>(plain::find(r_first, r_last, x));
#		endif

			}

			template <typename T>
			const T *
			k_find_simd_size_handler(
				const T * first,
				const T * last,
				const T & x,
				kerbal::type_traits::integral_constant<std::size_t, 16>
			) KERBAL_NOEXCEPT
			{
				const kerbal::compatibility::int16_t * r_first = reinterpret_cast<const kerbal::compatibility::int16_t *>(first);
				const kerbal::compatibility::int16_t * r_last = reinterpret_cast<const kerbal::compatibility::int16_t *>(last);

#		if 0
				// pass
#		elif KERBAL_ALGORITHM_FIND_ENABLE_AVX2
				return reinterpret_cast<const T*>(avx2::find(r_first, r_last, x));
#		elif KERBAL_ALGORITHM_FIND_ENABLE_SSE4_1
				return reinterpret_cast<const T*>(sse41::find(r_first, r_last, x));
#		else
				return reinterpret_cast<const T*>(plain::find(r_first, r_last, x));
#		endif

			}

			template <typename T>
			const T * k_find_simd_size_handler(const T * first, const T * last, const T & x, kerbal::type_traits::integral_constant<std::size_t, 32>) KERBAL_NOEXCEPT
			{
				const kerbal::compatibility::int32_t * r_first = reinterpret_cast<const kerbal::compatibility::int32_t *>(first);
				const kerbal::compatibility::int32_t * r_last = reinterpret_cast<const kerbal::compatibility::int32_t *>(last);

#		if 0
				// pass
#		elif KERBAL_ALGORITHM_FIND_ENABLE_AVX2
				return reinterpret_cast<const T*>(avx2::find(r_first, r_last, x));
#		elif KERBAL_ALGORITHM_FIND_ENABLE_SSE4_1
				return reinterpret_cast<const T*>(sse41::find(r_first, r_last, x));
#		else
				return reinterpret_cast<const T*>(plain::find(r_first, r_last, x));
#		endif

			}

			template <typename T>
			const T * k_find_simd_size_handler(const T * first, const T * last, const T & x, kerbal::type_traits::integral_constant<std::size_t, 64>) KERBAL_NOEXCEPT
			{
				const kerbal::compatibility::int64_t * r_first = reinterpret_cast<const kerbal::compatibility::int64_t *>(first);
				const kerbal::compatibility::int64_t * r_last = reinterpret_cast<const kerbal::compatibility::int64_t *>(last);

#		if 0
				// pass
#		elif KERBAL_ALGORITHM_FIND_ENABLE_AVX2
				return reinterpret_cast<const T*>(avx2::find(r_first, r_last, x));
#		elif KERBAL_ALGORITHM_FIND_ENABLE_SSE4_1
				return reinterpret_cast<const T*>(sse41::find(r_first, r_last, x));
#		else
				return reinterpret_cast<const T*>(plain::find(r_first, r_last, x));
#		endif

			}

			inline
			const char * k_find_simd_handler(const char * first, const char * last, const char & x) KERBAL_NOEXCEPT
			{
				return k_find_simd_size_handler(first, last, x, kerbal::type_traits::integral_constant<std::size_t, sizeof(x) * CHAR_BIT>());
			}

			inline
			const signed char * k_find_simd_handler(const signed char * first, const signed char * last, const signed char & x) KERBAL_NOEXCEPT
			{
				return k_find_simd_size_handler(first, last, x, kerbal::type_traits::integral_constant<std::size_t, sizeof(x) * CHAR_BIT>());
			}

			inline
			const wchar_t * k_find_simd_handler(const wchar_t * first, const wchar_t * last, const wchar_t & x) KERBAL_NOEXCEPT
			{
				return k_find_simd_size_handler(first, last, x, kerbal::type_traits::integral_constant<std::size_t, sizeof(x) * CHAR_BIT>());
			}

#		if __cplusplus >= 201103L

			inline
			const char16_t * k_find_simd_handler(const char16_t * first, const char16_t * last, const char16_t & x) KERBAL_NOEXCEPT
			{
				return k_find_simd_size_handler(first, last, x, kerbal::type_traits::integral_constant<std::size_t, sizeof(x) * CHAR_BIT>());
			}

			inline
			const char32_t * k_find_simd_handler(const char32_t * first, const char32_t * last, const char32_t & x) KERBAL_NOEXCEPT
			{
				return k_find_simd_size_handler(first, last, x, kerbal::type_traits::integral_constant<std::size_t, sizeof(x) * CHAR_BIT>());
			}

#		endif

#		if __cplusplus > 201703L

			inline
			const char8_t * k_find_simd_handler(const char8_t * first, const char8_t * last, const char8_t & x) KERBAL_NOEXCEPT
			{
				return k_find_simd_size_handler(first, last, x, kerbal::type_traits::integral_constant<std::size_t, sizeof(x) * CHAR_BIT>());
			}

#		endif

			inline
			const short * k_find_simd_handler(const short * first, const short * last, const short & x) KERBAL_NOEXCEPT
			{
				return k_find_simd_size_handler(first, last, x, kerbal::type_traits::integral_constant<std::size_t, sizeof(x) * CHAR_BIT>());
			}

			inline
			const int * k_find_simd_handler(const int * first, const int * last, const int & x) KERBAL_NOEXCEPT
			{
				return k_find_simd_size_handler(first, last, x, kerbal::type_traits::integral_constant<std::size_t, sizeof(x) * CHAR_BIT>());
			}

			inline
			const long * k_find_simd_handler(const long * first, const long * last, const long & x) KERBAL_NOEXCEPT
			{
				return k_find_simd_size_handler(first, last, x, kerbal::type_traits::integral_constant<std::size_t, sizeof(x) * CHAR_BIT>());
			}

			inline
			const long long * k_find_simd_handler(const long long * first, const long long * last, const long long & x) KERBAL_NOEXCEPT
			{
				return k_find_simd_size_handler(first, last, x, kerbal::type_traits::integral_constant<std::size_t, sizeof(x) * CHAR_BIT>());
			}

			template <typename T, typename U>
			const T * k_find_simd_handler(const T * first, const T * last, const U & x)
			{
				return plain::find(first, last, x);
			}

			template <typename T, typename U>
			T * k_find_simd_handler(T * first, T * last, const U & x)
			{
				return const_cast<T*>(k_find_simd_handler(static_cast<const T*>(first), static_cast<const T*>(last), x));
			}



			template <typename ContiguouslIterator, typename T>
			KERBAL_CONSTEXPR14
			ContiguouslIterator k_find_is_constant_evaluated_handler(ContiguouslIterator first, ContiguouslIterator last, const T & x)
			{

#	if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
				if (KERBAL_IS_CONSTANT_EVALUATED()) {
					return plain::find(first, last, x);
				}
				return first + (k_find_simd_handler(&*first, &*last, x) - &*first);
#	else
#		if __cplusplus < 201103L
				return first + (k_find_simd_handler(&*first, &*last, x) - &*first);
#		else
				return plain::find(first, last, x);
#		endif
#	endif

			}



			template <typename RandomAccesslIterator, typename T>
			KERBAL_CONSTEXPR14
			RandomAccesslIterator k_find_contiguous_iterator_handler(RandomAccesslIterator first, RandomAccesslIterator last, const T & x, kerbal::type_traits::false_type)
			{
				return detail::plain::find(first, last, x);
			}

			template <typename ContiguouslIterator, typename T>
			KERBAL_CONSTEXPR14
			ContiguouslIterator k_find_contiguous_iterator_handler(ContiguouslIterator first, ContiguouslIterator last, const T & x, kerbal::type_traits::true_type)
			{
				return detail::k_find_is_constant_evaluated_handler(first, last, x);
			}



			template <typename InputIterator, typename SentinelIterator, typename T>
			KERBAL_CONSTEXPR14
			InputIterator k_find_iterator_handler(InputIterator first, SentinelIterator last, const T & x, std::input_iterator_tag)
			{
				return detail::plain::find(first, last, x);
			}

			template <typename RandomAccesslIterator, typename T>
			KERBAL_CONSTEXPR14
			RandomAccesslIterator k_find_iterator_handler(RandomAccesslIterator first, RandomAccesslIterator last, const T & x, std::random_access_iterator_tag)
			{
				return detail::k_find_contiguous_iterator_handler(first, last, x, kerbal::iterator::is_contiguous_iterator<RandomAccesslIterator>());
			}


		} // namespace detail

		template <typename InputIterator, typename SentinelIterator, typename T>
		KERBAL_CONSTEXPR14
		InputIterator find(InputIterator first, SentinelIterator last, const T & x)
		{
			return detail::k_find_iterator_handler(first, last, x, kerbal::iterator::iterator_category(first));
		}

		template <typename T, std::size_t N, typename U>
		KERBAL_CONSTEXPR14
		T * find(T (&arr) [N], const U & x)
		{
			return detail::k_find_contiguous_iterator_handler(arr + 0, arr + N, x, kerbal::type_traits::true_type());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_QUERIER_FIND_HPP
