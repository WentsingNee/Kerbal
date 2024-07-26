/**
 * @file       generator.fwd.hpp
 * @brief
 * @date       2021-08-16
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COROUTINE_GENERATOR_GENERATOR_FWD_HPP
#define KERBAL_COROUTINE_GENERATOR_GENERATOR_FWD_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/coroutine/config.hpp>

#if KERBAL_SUPPORT_COROUTINE

#include <kerbal/memory/allocator/std_allocator/std_allocator.fwd.hpp>


namespace kerbal
{

	namespace coroutine
	{

		KERBAL_MODULE_EXPORT
		template <typename T, typename Allocator = std::allocator<char> >
		class generator;

		KERBAL_MODULE_EXPORT
		class bad_generator;

	} // namespace coroutine

} // namespace kerbal

#endif

#endif // KERBAL_COROUTINE_GENERATOR_GENERATOR_FWD_HPP
