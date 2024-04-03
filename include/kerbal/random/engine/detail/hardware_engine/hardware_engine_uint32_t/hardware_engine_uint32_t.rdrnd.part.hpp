/**
 * @file       hardware_engine_uint32_t.rdrnd.part.hpp
 * @brief
 * @date       2024-04-04
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_ENGINE_DETAIL_HARDWARE_ENGINE_HARDWARE_ENGINE_UINT32_T_HARDWARE_ENGINE_UINT32_T_RDRND_PART_HPP
#define KERBAL_RANDOM_ENGINE_DETAIL_HARDWARE_ENGINE_HARDWARE_ENGINE_UINT32_T_HARDWARE_ENGINE_UINT32_T_RDRND_PART_HPP

#ifndef KERBAL_HAS_SUPPORT_OF_RANDOM_HARDWARE_ENGINE_UINT32_T

#if __RDRND__
#	define KERBAL_HAS_SUPPORT_OF_RANDOM_HARDWARE_ENGINE_UINT32_T 1
#else

#	include <kerbal/config/compiler_id.hpp>
#	if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC

#		include <kerbal/config/compiler_private.hpp>
#		if KERBAL_MSVC_VERSION_MEETS(19, 0, 0) // msvc2015

#			include <kerbal/config/architecture.hpp>
#			if KERBAL_ARCHITECTURE == KERBAL_ARCHITECTURE_AMD64 || \
			   KERBAL_ARCHITECTURE == KERBAL_ARCHITECTURE_X86
#				define KERBAL_HAS_SUPPORT_OF_RANDOM_HARDWARE_ENGINE_UINT32_T 1
#			endif
#		endif
#	endif

#endif



#if KERBAL_HAS_SUPPORT_OF_RANDOM_HARDWARE_ENGINE_UINT32_T

#include <kerbal/random/engine/hardware_engine/hardware_engine.fwd.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/numeric/numeric_limits.hpp>
#include <kerbal/utility/throw_this_exception.hpp>

#include <kerbal/random/engine/hardware_engine/hardware_engine_failure.hpp>

#include <immintrin.h>


namespace kerbal
{

	namespace random
	{

		template <>
		class hardware_engine<kerbal::compatibility::uint32_t>
		{
			private:
				typedef unsigned int					k_native_result_type;

			public:
				typedef kerbal::compatibility::uint32_t result_type;

			public:

#		if __cplusplus >= 201103L
				hardware_engine() = default;
#		else
				hardware_engine() {}
#		endif

				hardware_engine(result_type /*seed*/) KERBAL_NOEXCEPT
				{
				}

				void seed(result_type /*seed*/) KERBAL_NOEXCEPT
				{
				}

				result_type operator()()
				{
					k_native_result_type result;
					if (_rdrand32_step(&result) == 0) {
						kerbal::utility::throw_this_exception_helper<kerbal::random::hardware_engine_failure>::throw_this_exception();
					}
					return static_cast<result_type>(result);
				}

				void discard(unsigned long long times) KERBAL_NOEXCEPT
				{
					while (times != 0) {
						--times;
						(*this)();
					}
				}

				template <typename OutputIterator>
				void generate(OutputIterator first, OutputIterator last)
				{
					while (first != last) {
						*first = (*this)();
						++first;
					}
				}

				template <typename OutputIterator>
				OutputIterator
				generate_n(
					OutputIterator first,
					typename kerbal::iterator::iterator_traits<OutputIterator>::difference_type n
				)
				{
					while (n != 0) {
						--n;
						*first = (*this)();
						++first;
					}
					return first;
				}

				KERBAL_CONSTEXPR
				static
				result_type min() KERBAL_NOEXCEPT
				{
					return kerbal::numeric::numeric_limits<result_type>::MIN::value;
				}

				KERBAL_CONSTEXPR
				static
				result_type max() KERBAL_NOEXCEPT
				{
					return kerbal::numeric::numeric_limits<result_type>::MAX::value;
				}

				KERBAL_CONSTEXPR
				bool operator==(const hardware_engine & /*rhs*/) const KERBAL_NOEXCEPT
				{
					return false;
				}

				KERBAL_CONSTEXPR
				bool operator!=(const hardware_engine & /*rhs*/) const KERBAL_NOEXCEPT
				{
					return true;
				}

		};

	} // namespace random

} // namespace kerbal

#endif // #if KERBAL_HAS_SUPPORT_OF_RANDOM_HARDWARE_ENGINE_UINT32_T

#endif // #ifndef KERBAL_HAS_SUPPORT_OF_RANDOM_HARDWARE_ENGINE_UINT32_T

#endif // KERBAL_RANDOM_ENGINE_DETAIL_HARDWARE_ENGINE_HARDWARE_ENGINE_UINT32_T_HARDWARE_ENGINE_UINT32_T_RDRND_PART_HPP
