/**
 * @file       span.decl.hpp
 * @brief
 * @date       2024-10-16
 * @author     peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_SPAN_SPAN_DECL_HPP
#define KERBAL_CONTAINER_SPAN_SPAN_DECL_HPP

#include <kerbal/container/span/span.fwd.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>


namespace kerbal
{

	namespace container
	{

		template <typename T, typename Extent>
		class span
		{
			public:
				typedef T				value_type;
				typedef T &				reference;
				typedef const T &		const_reference;
				typedef T *				pointer;
				typedef const T *		const_pointer;
				typedef size_t			size_type;
				typedef ptrdiff_t		difference_type;

			private:
				pointer k_start;

			public:

				explicit
				KERBAL_CONSTEXPR14
				span(pointer start) :
					k_start(start)
				{
				}

		};

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_SPAN_SPAN_DECL_HPP
