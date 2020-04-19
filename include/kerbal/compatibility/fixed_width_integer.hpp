/**
 * @file       fixed_width_integer.hpp
 * @brief
 * @date       2020-02-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COMPATIBILITY_FIXED_WIDTH_INTEGER_HPP
#define KERBAL_COMPATIBILITY_FIXED_WIDTH_INTEGER_HPP

#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/is_same.hpp>

#include <climits>

namespace kerbal
{

	namespace compatibility
	{

		template <int width>
		struct __fixed_width_interger_helper
		{
				typedef
				typename kerbal::type_traits::conditional<
					sizeof(signed char) * CHAR_BIT == width,
					signed char,
					typename kerbal::type_traits::conditional<
						sizeof(short) * CHAR_BIT == width,
						short,
						typename kerbal::type_traits::conditional<
							sizeof(int) * CHAR_BIT == width,
							int,
							typename kerbal::type_traits::conditional<
								sizeof(long) * CHAR_BIT == width,
								long,
								typename kerbal::type_traits::conditional<
									sizeof(long long) * CHAR_BIT == width,
									long long,
									void
								>::type
							>::type
						>::type
					>::type
				>::type type;

				KERBAL_STATIC_ASSERT(!(kerbal::type_traits::is_same<type, void>::value), "doesn't support this width");
		};

		template <int width>
		struct __fixed_width_unsigned_interger_helper
		{
				typedef
				typename kerbal::type_traits::conditional<
					sizeof(unsigned char) * CHAR_BIT == width,
					unsigned char,
					typename kerbal::type_traits::conditional<
						sizeof(unsigned short) * CHAR_BIT == width,
						unsigned short,
						typename kerbal::type_traits::conditional<
							sizeof(unsigned int) * CHAR_BIT == width,
							unsigned int,
							typename kerbal::type_traits::conditional<
								sizeof(unsigned long) * CHAR_BIT == width,
								unsigned long,
								typename kerbal::type_traits::conditional<
									sizeof(unsigned long long) * CHAR_BIT == width,
									unsigned long long,
									void
								>::type
							>::type
						>::type
					>::type
				>::type type;

				KERBAL_STATIC_ASSERT(!(kerbal::type_traits::is_same<type, void>::value), "doesn't support this width");
		};

		typedef typename __fixed_width_interger_helper<8>::type    int8_t;
		typedef typename __fixed_width_interger_helper<16>::type   int16_t;
		typedef typename __fixed_width_interger_helper<32>::type   int32_t;
		typedef typename __fixed_width_interger_helper<64>::type   int64_t;

		typedef typename __fixed_width_unsigned_interger_helper<8>::type    uint8_t;
		typedef typename __fixed_width_unsigned_interger_helper<16>::type   uint16_t;
		typedef typename __fixed_width_unsigned_interger_helper<32>::type   uint32_t;
		typedef typename __fixed_width_unsigned_interger_helper<64>::type   uint64_t;


	}
}

#endif //KERBAL_COMPATIBILITY_FIXED_WIDTH_INTEGER_HPP
