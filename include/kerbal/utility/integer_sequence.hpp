/**
 * @file       integer_sequence.hpp
 * @brief
 * @date       2020-6-6
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_INTEGER_SEQUENCE_HPP
#define KERBAL_UTILITY_INTEGER_SEQUENCE_HPP

#if __cplusplus < 201103L
#	error This file requires compiler and library support \
for the ISO C++ 2011 standard.
#endif

#include <kerbal/config/compiler_private.hpp>

#include <type_traits>

#include <cstddef>


namespace kerbal
{

	namespace utility
	{

		template <typename T, T ... Ints>
		struct integer_sequence
		{
				typedef T value_type;

				constexpr
				static std::size_t size() noexcept
				{
					return sizeof...(Ints);
				}
		};

		template <std::size_t ... Ints>
		using index_sequence = kerbal::utility::integer_sequence<std::size_t, Ints...>;



#define KERBAL_UTILITY_MAKE_INTEGER_SEQUENCE_IMPL_POLICY_DEFAULT					0
#define KERBAL_UTILITY_MAKE_INTEGER_SEQUENCE_IMPL_POLICY_GNU_INTEGER_PACK			1
#define KERBAL_UTILITY_MAKE_INTEGER_SEQUENCE_IMPL_POLICY_CLANG_MAKE_INTEGER_SEQ		2


#if KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_GNU

//	https://gcc.gnu.org/onlinedocs/gcc-8.1.0/gcc/Type-Traits.html#Type-Traits
#	if KERBAL_GNU_PRIVATE_HAS_BUILTIN(__integer_pack)
#		define KERBAL_UTILITY_MAKE_INTEGER_SEQUENCE_IMPL_POLICY			KERBAL_UTILITY_MAKE_INTEGER_SEQUENCE_IMPL_POLICY_GNU_INTEGER_PACK
#	endif

#elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_CLANG

#	if KERBAL_CLANG_PRIVATE_HAS_BUILTIN(__make_integer_seq)
#		define KERBAL_UTILITY_MAKE_INTEGER_SEQUENCE_IMPL_POLICY			KERBAL_UTILITY_MAKE_INTEGER_SEQUENCE_IMPL_POLICY_CLANG_MAKE_INTEGER_SEQ
#	endif

#elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC

//	https://www.cnblogs.com/yamboo/p/14030418.html
#	if KERBAL_MSVC_VERSION_MEETS(19, 0, 0) // MSVC++ 14.0  _MSC_VER == 1900 (Visual Studio 2015 version 14.0)
#		define KERBAL_UTILITY_MAKE_INTEGER_SEQUENCE_IMPL_POLICY			KERBAL_UTILITY_MAKE_INTEGER_SEQUENCE_IMPL_POLICY_CLANG_MAKE_INTEGER_SEQ
#	endif


#elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_ICC

#	if KERBAL_ICC_VERSION_MEETS(2021, 2, 0)
#		define KERBAL_UTILITY_MAKE_INTEGER_SEQUENCE_IMPL_POLICY			KERBAL_UTILITY_MAKE_INTEGER_SEQUENCE_IMPL_POLICY_GNU_INTEGER_PACK
#	endif

#else

#		define KERBAL_UTILITY_MAKE_INTEGER_SEQUENCE_IMPL_POLICY			KERBAL_UTILITY_MAKE_INTEGER_SEQUENCE_IMPL_POLICY_DEFAULT

#endif


#	if KERBAL_UTILITY_MAKE_INTEGER_SEQUENCE_IMPL_POLICY == KERBAL_UTILITY_MAKE_INTEGER_SEQUENCE_IMPL_POLICY_DEFAULT

		namespace detail
		{

			template <typename T, typename Seq, T i>
			struct concat_integer_sequence;

			template <typename T, T i, T ... Ints>
			struct concat_integer_sequence<T, integer_sequence<T, Ints...>, i>
			{
					typedef integer_sequence<T, Ints..., i> type;
			};

			template <typename T, T N>
			struct make_integer_sequence_helper;


			template <typename T, T N, bool end_of_loop>
			struct make_integer_sequence_helper_loop;

			template <typename T, T N>
			struct make_integer_sequence_helper_loop<T, N, false>
			{
					typedef typename concat_integer_sequence<
							T, typename make_integer_sequence_helper<T, N - 1>::type, N - 1
					>::type type;
			};

			template <typename T, T N>
			struct make_integer_sequence_helper_loop<T, N, true>
			{
					typedef integer_sequence<T> type;
			};

			template <typename T, T N>
			struct make_integer_sequence_helper: make_integer_sequence_helper_loop<T, N, N == 0>
			{
			};

		} // namespace detail

#	endif


		template <typename T, T N>
		using make_integer_sequence =
#	if   KERBAL_UTILITY_MAKE_INTEGER_SEQUENCE_IMPL_POLICY == KERBAL_UTILITY_MAKE_INTEGER_SEQUENCE_IMPL_POLICY_DEFAULT
				typename kerbal::utility::detail::make_integer_sequence_helper<T, N>::type;
#	elif KERBAL_UTILITY_MAKE_INTEGER_SEQUENCE_IMPL_POLICY == KERBAL_UTILITY_MAKE_INTEGER_SEQUENCE_IMPL_POLICY_GNU_INTEGER_PACK
				integer_sequence<T, __integer_pack(N)...>;
#	elif KERBAL_UTILITY_MAKE_INTEGER_SEQUENCE_IMPL_POLICY == KERBAL_UTILITY_MAKE_INTEGER_SEQUENCE_IMPL_POLICY_CLANG_MAKE_INTEGER_SEQ
				__make_integer_seq<integer_sequence, T, N>;
#	endif
		// kerbal::utility::integer_sequence<T, /* a sequence 0, 1, 2, ..., N-1 */ >;

		template <std::size_t N>
		using make_index_sequence = kerbal::utility::make_integer_sequence<std::size_t, N>;

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_UTILITY_INTEGER_SEQUENCE_HPP
