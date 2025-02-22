/**
 * @file       pointer_alignment.hpp
 * @brief
 * @date       2023-04-06
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_POINTER_ALIGNMENT_HPP
#define KERBAL_MEMORY_POINTER_ALIGNMENT_HPP

#include <kerbal/compatibility/alignof.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#include <cstddef>


namespace kerbal
{

	namespace memory
	{

#ifdef __STDCPP_DEFAULT_NEW_ALIGNMENT__
		typedef kerbal::type_traits::integral_constant<std::size_t, __STDCPP_DEFAULT_NEW_ALIGNMENT__> DEFAULT_ALIGNMENT;
#else
		typedef kerbal::type_traits::integral_constant<std::size_t, sizeof(void *)> DEFAULT_ALIGNMENT;
#endif


		struct align_val_t
		{
				std::size_t val;

				KERBAL_CONSTEXPR
				align_val_t(std::size_t val = kerbal::memory::DEFAULT_ALIGNMENT::value) KERBAL_NOEXCEPT :
					val(val)
				{
				}

				KERBAL_CONSTEXPR
				operator std::size_t() const KERBAL_NOEXCEPT
				{
					return val;
				}
		};


		KERBAL_CONSTEXPR
		inline
		std::size_t align_ceil(std::size_t p, std::size_t align) KERBAL_NOEXCEPT
		{
			return (p + (align - 1)) & ~(align - 1);
		}

		KERBAL_CONSTEXPR
		inline
		std::size_t align_floor(std::size_t p, std::size_t align) KERBAL_NOEXCEPT
		{
			return p & ~(align - 1);
		}

		template <typename T>
		T * align_ceil(T * p, std::size_t align) KERBAL_NOEXCEPT
		{
			return reinterpret_cast<T *>(align_ceil(reinterpret_cast<std::size_t>(p), align));
		}

		template <typename T>
		T * align_floor(T * p, std::size_t align) KERBAL_NOEXCEPT
		{
			return reinterpret_cast<T *>(align_floor(reinterpret_cast<std::size_t>(p), align));
		}

		namespace detail
		{

			template <typename T = void>
			struct alignment_maximum_offset_helper;

			template <typename T>
			struct alignment_maximum_offset_helper
			{
					KERBAL_CONSTEXPR
					static std::size_t alignment_maximum_offset(std::size_t align, std::size_t basic_align) KERBAL_NOEXCEPT
					{
						return align <= basic_align ? 0 : (align - basic_align);
					}

					KERBAL_CONSTEXPR
					static std::size_t alignment_maximum_offset(std::size_t align) KERBAL_NOEXCEPT
					{
						return alignment_maximum_offset(
							align,
							KERBAL_ALIGNOF(T) >= kerbal::memory::DEFAULT_ALIGNMENT::value ?
							KERBAL_ALIGNOF(T) :
							kerbal::memory::DEFAULT_ALIGNMENT::value
						);
					}
			};

			template <>
			struct alignment_maximum_offset_helper<void>
			{
					KERBAL_CONSTEXPR
					static std::size_t alignment_maximum_offset(std::size_t align, std::size_t basic_align) KERBAL_NOEXCEPT
					{
						return align <= basic_align ? 0 : (align - basic_align);
					}

					KERBAL_CONSTEXPR
					static std::size_t alignment_maximum_offset(std::size_t align) KERBAL_NOEXCEPT
					{
						return alignment_maximum_offset(align, kerbal::memory::DEFAULT_ALIGNMENT::value);
					}
			};

		} // namespace detail

		inline
		KERBAL_CONSTEXPR
		std::size_t alignment_maximum_offset(std::size_t align, std::size_t basic_align) KERBAL_NOEXCEPT
		{
			return kerbal::memory::detail::alignment_maximum_offset_helper<>::alignment_maximum_offset(align, basic_align);
		}

		template <typename T>
		KERBAL_CONSTEXPR
		std::size_t alignment_maximum_offset(std::size_t align) KERBAL_NOEXCEPT
		{
			return kerbal::memory::detail::alignment_maximum_offset_helper<T>::alignment_maximum_offset(align);
		}

	} // namespace memory

} // namespace kerbal


#endif // KERBAL_MEMORY_POINTER_ALIGNMENT_HPP
