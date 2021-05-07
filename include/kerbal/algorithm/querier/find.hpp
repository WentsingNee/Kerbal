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
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/type_traits/integral_constant.hpp>


#if defined(__AVX2__)
#	define KERBAL_ALGORITHM_FIND_ENABLE_AVX2     1
#elif defined(__SSE4_1__)
#	define KERBAL_ALGORITHM_FIND_ENABLE_SSE4_1   1
#endif



#if KERBAL_ALGORITHM_FIND_ENABLE_SSE4_1
#	include <emmintrin.h>
#	include <smmintrin.h>
#endif

#if KERBAL_ALGORITHM_FIND_ENABLE_AVX2
#	include <immintrin.h>
#endif


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

			template <typename InputIterator, typename SentinelIterator, typename T>
			KERBAL_CONSTEXPR14
			InputIterator _K_basic_find(InputIterator first, SentinelIterator last, const T & x)
			{
				while (first != last) {
					if (*first == x) {
						break;
					}
					++first;
				}
				return first;
			}

		} // namespace detail

//		namespace mmx
//		{
//
//			inline
//			const int8_t * find(const int8_t * first, const int8_t * last, const int8_t & x)
//			{
//				typedef kerbal::type_traits::integral_constant<std::size_t, sizeof(__m64) / sizeof(int8_t)> THROUGHPUT;
//
//				__m64 const mx = _mm_set1_pi8(x); // MMX
//				__m64 const mALL_ONE = _mm_set1_pi8(~0); // MMX
//				std::size_t loop = (last - first) / THROUGHPUT::value;
//				for (std::size_t i = 0; i < loop; ++i) {
//					const __m64 * const mpf = reinterpret_cast<const __m64 *>(first);
//					__m64 mrf = _mm_loadu_si128(mpf); // SSE2
//					mrf = _mm_cmpeq_epi8(mrf, mx); // SSE2
//
//					if (!_mm_test_all_zeros(mrf, mALL_ONE)) { // SSE4.1
//						break;
//					}
//					first += THROUGHPUT::value;
//				}
//				return kerbal::algorithm::detail::_K_basic_find(first, last, x);
//			}
//
//		} // namespace mmx



#	if KERBAL_ALGORITHM_FIND_ENABLE_SSE4_1

		namespace sse4_1
		{

			inline
			const char* find(const char * first, const char * last, const char & x) KERBAL_NOEXCEPT
			{
				typedef kerbal::type_traits::integral_constant<std::size_t, sizeof(__m128i) / sizeof(char)> THROUGHPUT;

				__m128i const mx = _mm_set1_epi8(x); // SSE2
				__m128i const mALL_ONE = _mm_set1_epi8(~0); // SSE2
				std::size_t loop = (last - first) / THROUGHPUT::value;
				for (std::size_t i = 0; i < loop; ++i) {
					const __m128i * const mpf = reinterpret_cast<const __m128i *>(first);
					__m128i mrf = _mm_loadu_si128(mpf); // SSE2
					mrf = _mm_cmpeq_epi8(mrf, mx); // SSE2

					if (!_mm_testz_si128(mrf, mALL_ONE)) { // SSE4.1
						break;
					}
					first += THROUGHPUT::value;
				}
				return kerbal::algorithm::detail::_K_basic_find(first, last, x);
			}

			inline
			const kerbal::compatibility::int16_t* find(const kerbal::compatibility::int16_t * first, const kerbal::compatibility::int16_t * last, const kerbal::compatibility::int16_t & x) KERBAL_NOEXCEPT
			{
				typedef kerbal::type_traits::integral_constant<std::size_t, sizeof(__m128i) / sizeof(kerbal::compatibility::int16_t)> THROUGHPUT;

				__m128i const mx = _mm_set1_epi16(x); // SSE2
				__m128i const mALL_ONE = _mm_set1_epi16(~0); // SSE2
				std::size_t loop = (last - first) / THROUGHPUT::value;
				for (std::size_t i = 0; i < loop; ++i) {
					const __m128i * const mpf = reinterpret_cast<const __m128i *>(first);
					__m128i mrf = _mm_loadu_si128(mpf); // SSE2
					mrf = _mm_cmpeq_epi16(mrf, mx); // SSE2

					if (!_mm_testz_si128(mrf, mALL_ONE)) { // SSE4.1
						break;
					}
					first += THROUGHPUT::value;
				}
				return kerbal::algorithm::detail::_K_basic_find(first, last, x);
			}

			inline
			const kerbal::compatibility::int32_t* find(const kerbal::compatibility::int32_t * first, const kerbal::compatibility::int32_t * last, const kerbal::compatibility::int32_t & x) KERBAL_NOEXCEPT
			{
				typedef kerbal::type_traits::integral_constant<std::size_t, sizeof(__m128i) / sizeof(kerbal::compatibility::int32_t)> THROUGHPUT;

				__m128i const mx = _mm_set1_epi32(x); // SSE2
				__m128i const mALL_ONE = _mm_set1_epi32(~0); // SSE2
				std::size_t loop = (last - first) / THROUGHPUT::value;
				for (std::size_t i = 0; i < loop; ++i) {
					const __m128i * const mpf = reinterpret_cast<const __m128i *>(first);
					__m128i mrf = _mm_loadu_si128(mpf); // SSE2
					mrf = _mm_cmpeq_epi32(mrf, mx); // SSE2

					if (!_mm_testz_si128(mrf, mALL_ONE)) { // SSE4.1
						break;
					}
					first += THROUGHPUT::value;
				}
				return kerbal::algorithm::detail::_K_basic_find(first, last, x);
			}

			inline
			const kerbal::compatibility::int64_t* find(const kerbal::compatibility::int64_t * first, const kerbal::compatibility::int64_t * last, const kerbal::compatibility::int64_t & x) KERBAL_NOEXCEPT
			{
				typedef kerbal::type_traits::integral_constant<std::size_t, sizeof(__m128i) / sizeof(kerbal::compatibility::int64_t)> THROUGHPUT;

				__m128i const mx = _mm_set1_epi64x(x); // SSE2
				__m128i const mALL_ONE = _mm_set1_epi64x(~0); // SSE2
				std::size_t loop = (last - first) / THROUGHPUT::value;
				for (std::size_t i = 0; i < loop; ++i) {
					const __m128i * const mpf = reinterpret_cast<const __m128i *>(first);
					__m128i mrf = _mm_loadu_si128(mpf); // SSE2
					mrf = _mm_cmpeq_epi64(mrf, mx); // SSE4.1!!!

					if (!_mm_testz_si128(mrf, mALL_ONE)) { // SSE4.1
						break;
					}
					first += THROUGHPUT::value;
				}
				return kerbal::algorithm::detail::_K_basic_find(first, last, x);
			}

		} // namespace sse4_1

#	endif



#	if KERBAL_ALGORITHM_FIND_ENABLE_AVX2

		namespace avx2
		{

			inline
			const char* find(const char * first, const char * last, const char & x) KERBAL_NOEXCEPT
			{
				typedef kerbal::type_traits::integral_constant<std::size_t, sizeof(__m256i) / sizeof(char)> THROUGHPUT;

				__m256i const mx = _mm256_set1_epi8(x); // AVX
				__m256i const mALL_ONE = _mm256_set1_epi8(~0); // AVX
				std::size_t loop = (last - first) / THROUGHPUT::value;
				for (std::size_t i = 0; i < loop; ++i) {
					const __m256i * const mpf = reinterpret_cast<const __m256i *>(first);
					__m256i mrf = _mm256_loadu_si256(mpf); // AVX
					mrf = _mm256_cmpeq_epi8(mrf, mx); // AVX2

					if (!_mm256_testz_si256(mrf, mALL_ONE)) { // AVX
						break;
					}
					first += THROUGHPUT::value;
				}
				return kerbal::algorithm::detail::_K_basic_find(first, last, x);
			}

			inline
			const kerbal::compatibility::int16_t* find(const kerbal::compatibility::int16_t * first, const kerbal::compatibility::int16_t * last, const kerbal::compatibility::int16_t & x) KERBAL_NOEXCEPT
			{
				typedef kerbal::type_traits::integral_constant<std::size_t, sizeof(__m256i) / sizeof(kerbal::compatibility::int16_t)> THROUGHPUT;

				__m256i const mx = _mm256_set1_epi16(x); // AVX
				__m256i const mALL_ONE = _mm256_set1_epi16(~0); // AVX
				std::size_t loop = (last - first) / THROUGHPUT::value;
				for (std::size_t i = 0; i < loop; ++i) {
					const __m256i * const mpf = reinterpret_cast<const __m256i *>(first);
					__m256i mrf = _mm256_loadu_si256(mpf); // AVX
					mrf = _mm256_cmpeq_epi16(mrf, mx); // AVX2

					if (!_mm256_testz_si256(mrf, mALL_ONE)) { // AVX
						break;
					}
					first += THROUGHPUT::value;
				}
				return kerbal::algorithm::detail::_K_basic_find(first, last, x);
			}

			inline
			const kerbal::compatibility::int32_t* find(const kerbal::compatibility::int32_t * first, const kerbal::compatibility::int32_t * last, const kerbal::compatibility::int32_t & x) KERBAL_NOEXCEPT
			{
				typedef kerbal::type_traits::integral_constant<std::size_t, sizeof(__m256i) / sizeof(kerbal::compatibility::int32_t)> THROUGHPUT;

				__m256i const mx = _mm256_set1_epi32(x); // AVX
				__m256i const mALL_ONE = _mm256_set1_epi32(~0); // AVX
				std::size_t loop = (last - first) / THROUGHPUT::value;
				for (std::size_t i = 0; i < loop; ++i) {
					const __m256i * const mpf = reinterpret_cast<const __m256i *>(first);
					__m256i mrf = _mm256_loadu_si256(mpf); // AVX
					mrf = _mm256_cmpeq_epi32(mrf, mx); // AVX2

					if (!_mm256_testz_si256(mrf, mALL_ONE)) { // AVX
						break;
					}
					first += THROUGHPUT::value;
				}
				return kerbal::algorithm::detail::_K_basic_find(first, last, x);
			}

			inline
			const kerbal::compatibility::int64_t* find(const kerbal::compatibility::int64_t * first, const kerbal::compatibility::int64_t * last, const kerbal::compatibility::int64_t & x) KERBAL_NOEXCEPT
			{
				typedef kerbal::type_traits::integral_constant<std::size_t, sizeof(__m256i) / sizeof(kerbal::compatibility::int64_t)> THROUGHPUT;

				__m256i const mx = _mm256_set1_epi64x(x); // AVX
				__m256i const mALL_ONE = _mm256_set1_epi64x(~0); // AVX
				std::size_t loop = (last - first) / THROUGHPUT::value;
				for (std::size_t i = 0; i < loop; ++i) {
					const __m256i * const mpf = reinterpret_cast<const __m256i *>(first);
					__m256i mrf = _mm256_loadu_si256(mpf); // AVX
					mrf = _mm256_cmpeq_epi64(mrf, mx); // AVX2

					if (!_mm256_testz_si256(mrf, mALL_ONE)) { // AVX
						break;
					}
					first += THROUGHPUT::value;
				}
				return kerbal::algorithm::detail::_K_basic_find(first, last, x);
			}

		} // namespace avx2

#	endif


		namespace detail
		{

			template <typename T>
			const T * _K_find_simd_size_handler(const T * first, const T * last, const T & x, kerbal::type_traits::integral_constant<std::size_t, 8>) KERBAL_NOEXCEPT
			{
#			if KERBAL_ALGORITHM_FIND_ENABLE_AVX2
				const char * _first = reinterpret_cast<const char *>(first);
				const char * _last = reinterpret_cast<const char *>(last);
				return reinterpret_cast<const T*>(avx2::find(_first, _last, x));
#			elif KERBAL_ALGORITHM_FIND_ENABLE_SSE4_1
				const char * _first = reinterpret_cast<const char *>(first);
				const char * _last = reinterpret_cast<const char *>(last);
				return reinterpret_cast<const T*>(sse4_1::find(_first, _last, x));
#			else
				return _K_basic_find(first, last, x);
#			endif
			}

			template <typename T>
			const T * _K_find_simd_size_handler(const T * first, const T * last, const T & x, kerbal::type_traits::integral_constant<std::size_t, 16>) KERBAL_NOEXCEPT
			{
#			if KERBAL_ALGORITHM_FIND_ENABLE_AVX2
				const kerbal::compatibility::int16_t * _first = reinterpret_cast<const kerbal::compatibility::int16_t *>(first);
				const kerbal::compatibility::int16_t * _last = reinterpret_cast<const kerbal::compatibility::int16_t *>(last);
				return reinterpret_cast<const T*>(avx2::find(_first, _last, x));
#			elif KERBAL_ALGORITHM_FIND_ENABLE_SSE4_1
				const kerbal::compatibility::int16_t * _first = reinterpret_cast<const kerbal::compatibility::int16_t *>(first);
				const kerbal::compatibility::int16_t * _last = reinterpret_cast<const kerbal::compatibility::int16_t *>(last);
				return reinterpret_cast<const T*>(sse4_1::find(_first, _last, x));
#			else
				return _K_basic_find(first, last, x);
#			endif
			}

			template <typename T>
			const T * _K_find_simd_size_handler(const T * first, const T * last, const T & x, kerbal::type_traits::integral_constant<std::size_t, 32>) KERBAL_NOEXCEPT
			{
#			if KERBAL_ALGORITHM_FIND_ENABLE_AVX2
				const kerbal::compatibility::int32_t * _first = reinterpret_cast<const kerbal::compatibility::int32_t *>(first);
				const kerbal::compatibility::int32_t * _last = reinterpret_cast<const kerbal::compatibility::int32_t *>(last);
				return reinterpret_cast<const T*>(avx2::find(_first, _last, x));
#			elif KERBAL_ALGORITHM_FIND_ENABLE_SSE4_1
				const kerbal::compatibility::int32_t * _first = reinterpret_cast<const kerbal::compatibility::int32_t *>(first);
				const kerbal::compatibility::int32_t * _last = reinterpret_cast<const kerbal::compatibility::int32_t *>(last);
				return reinterpret_cast<const T*>(sse4_1::find(_first, _last, x));
#			else
				return _K_basic_find(first, last, x);
#			endif
			}

			template <typename T>
			const T * _K_find_simd_size_handler(const T * first, const T * last, const T & x, kerbal::type_traits::integral_constant<std::size_t, 64>) KERBAL_NOEXCEPT
			{
#			if KERBAL_ALGORITHM_FIND_ENABLE_AVX2
				const kerbal::compatibility::int64_t * _first = reinterpret_cast<const kerbal::compatibility::int64_t *>(first);
				const kerbal::compatibility::int64_t * _last = reinterpret_cast<const kerbal::compatibility::int64_t *>(last);
				return reinterpret_cast<const T*>(avx2::find(_first, _last, x));
#			elif KERBAL_ALGORITHM_FIND_ENABLE_SSE4_1
				const kerbal::compatibility::int64_t * _first = reinterpret_cast<const kerbal::compatibility::int64_t *>(first);
				const kerbal::compatibility::int64_t * _last = reinterpret_cast<const kerbal::compatibility::int64_t *>(last);
				return reinterpret_cast<const T*>(sse4_1::find(_first, _last, x));
#			else
				return _K_basic_find(first, last, x);
#			endif
			}

			inline
			const char * _K_find_simd_handler(const char * first, const char * last, const char & x) KERBAL_NOEXCEPT
			{
				return _K_find_simd_size_handler(first, last, x, kerbal::type_traits::integral_constant<std::size_t, sizeof(x) * CHAR_BIT>());
			}

			inline
			const signed char * _K_find_simd_handler(const signed char * first, const signed char * last, const signed char & x) KERBAL_NOEXCEPT
			{
				return _K_find_simd_size_handler(first, last, x, kerbal::type_traits::integral_constant<std::size_t, sizeof(x) * CHAR_BIT>());
			}

			inline
			const wchar_t * _K_find_simd_handler(const wchar_t * first, const wchar_t * last, const wchar_t & x) KERBAL_NOEXCEPT
			{
				return _K_find_simd_size_handler(first, last, x, kerbal::type_traits::integral_constant<std::size_t, sizeof(x) * CHAR_BIT>());
			}

#		if __cplusplus >= 201103L

			inline
			const char16_t * _K_find_simd_handler(const char16_t * first, const char16_t * last, const char16_t & x) KERBAL_NOEXCEPT
			{
				return _K_find_simd_size_handler(first, last, x, kerbal::type_traits::integral_constant<std::size_t, sizeof(x) * CHAR_BIT>());
			}

			inline
			const char32_t * _K_find_simd_handler(const char32_t * first, const char32_t * last, const char32_t & x) KERBAL_NOEXCEPT
			{
				return _K_find_simd_size_handler(first, last, x, kerbal::type_traits::integral_constant<std::size_t, sizeof(x) * CHAR_BIT>());
			}

#		endif

#		if __cplusplus > 201703L

			inline
			const char8_t * _K_find_simd_handler(const char8_t * first, const char8_t * last, const char8_t & x) KERBAL_NOEXCEPT
			{
				return _K_find_simd_size_handler(first, last, x, kerbal::type_traits::integral_constant<std::size_t, sizeof(x) * CHAR_BIT>());
			}

#		endif

			inline
			const short * _K_find_simd_handler(const short * first, const short * last, const short & x) KERBAL_NOEXCEPT
			{
				return _K_find_simd_size_handler(first, last, x, kerbal::type_traits::integral_constant<std::size_t, sizeof(x) * CHAR_BIT>());
			}

			inline
			const int * _K_find_simd_handler(const int * first, const int * last, const int & x) KERBAL_NOEXCEPT
			{
				return _K_find_simd_size_handler(first, last, x, kerbal::type_traits::integral_constant<std::size_t, sizeof(x) * CHAR_BIT>());
			}

			inline
			const long * _K_find_simd_handler(const long * first, const long * last, const long & x) KERBAL_NOEXCEPT
			{
				return _K_find_simd_size_handler(first, last, x, kerbal::type_traits::integral_constant<std::size_t, sizeof(x) * CHAR_BIT>());
			}

			inline
			const long long * _K_find_simd_handler(const long long * first, const long long * last, const long long & x) KERBAL_NOEXCEPT
			{
				return _K_find_simd_size_handler(first, last, x, kerbal::type_traits::integral_constant<std::size_t, sizeof(x) * CHAR_BIT>());
			}

			template <typename T, typename U>
			const T * _K_find_simd_handler(const T * first, const T * last, const U & x)
			{
				return _K_basic_find(first, last, x);
			}

			template <typename T, typename U>
			T * _K_find_simd_handler(T * first, T * last, const U & x)
			{
				return const_cast<T*>(_K_find_simd_handler(static_cast<const T*>(first), static_cast<const T*>(last), x));
			}



			template <typename ContiguouslIterator, typename T>
			KERBAL_CONSTEXPR14
			ContiguouslIterator _K_find_is_constant_evaluated_handler(ContiguouslIterator first, ContiguouslIterator last, const T & x)
			{

#	if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
				if (KERBAL_IS_CONSTANT_EVALUATED()) {
					return _K_basic_find(first, last, x);
				}
				return first + (_K_find_simd_handler(&*first, &*last, x) - &*first);
#	else
#		if __cplusplus < 201103L
				return first + (_K_find_simd_handler(&*first, &*last, x) - &*first);
#		else
				return _K_basic_find(first, last, x);
#		endif
#	endif

			}



			template <typename RandomAccesslIterator, typename T>
			KERBAL_CONSTEXPR14
			RandomAccesslIterator _K_find_contiguous_iterator_handler(RandomAccesslIterator first, RandomAccesslIterator last, const T & x, kerbal::type_traits::false_type)
			{
				return detail::_K_basic_find(first, last, x);
			}

			template <typename ContiguouslIterator, typename T>
			KERBAL_CONSTEXPR14
			ContiguouslIterator _K_find_contiguous_iterator_handler(ContiguouslIterator first, ContiguouslIterator last, const T & x, kerbal::type_traits::true_type)
			{
				return detail::_K_find_is_constant_evaluated_handler(first, last, x);
			}



			template <typename InputIterator, typename SentinelIterator, typename T>
			KERBAL_CONSTEXPR14
			InputIterator _K_find_iterator_handler(InputIterator first, SentinelIterator last, const T & x, std::input_iterator_tag)
			{
				return detail::_K_basic_find(first, last, x);
			}

			template <typename RandomAccesslIterator, typename T>
			KERBAL_CONSTEXPR14
			RandomAccesslIterator _K_find_iterator_handler(RandomAccesslIterator first, RandomAccesslIterator last, const T & x, std::random_access_iterator_tag)
			{
				return detail::_K_find_contiguous_iterator_handler(first, last, x, kerbal::iterator::is_contiguous_iterator<RandomAccesslIterator>());
			}


		} // namespace detail

		template <typename InputIterator, typename SentinelIterator, typename T>
		KERBAL_CONSTEXPR14
		InputIterator find(InputIterator first, SentinelIterator last, const T & x)
		{
			return detail::_K_find_iterator_handler(first, last, x, kerbal::iterator::iterator_category(first));
		}

		template <typename T, std::size_t N, typename U>
		KERBAL_CONSTEXPR14
		T * find(T (&arr) [N], const U & x)
		{
			return detail::_K_find_contiguous_iterator_handler(arr + 0, arr + N, x, kerbal::type_traits::true_type());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_QUERIER_FIND_HPP
