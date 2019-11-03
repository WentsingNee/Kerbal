/**
 * @file       static_container_exception.hpp
 * @brief
 * @date       2019-4-20
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_STATIC_CONTAINER_EXCEPTION_HPP_
#define KERBAL_CONTAINER_STATIC_CONTAINER_EXCEPTION_HPP_

#include <kerbal/utility/throw_this_exception.hpp>

#include <stdexcept>

namespace kerbal
{
	namespace container
	{

		class static_container_empty_exception:
				public kerbal::utility::throw_this_exception_helper<static_container_empty_exception>,
				public std::logic_error
		{
			public:
				static_container_empty_exception() :
						std::logic_error("the static container is empty")
				{
				}
		};

		class static_container_full_exception:
				public kerbal::utility::throw_this_exception_helper<static_container_full_exception>,
				public std::logic_error
		{
			public:
				static_container_full_exception() :
						std::logic_error("the static container is full")
				{
				}

				explicit static_container_full_exception(std::size_t max_capacity) :
						std::logic_error("the static container is full")
				{
				}
		};

	} // namespace container

} // namespace kerbal

#endif /* KERBAL_CONTAINER_STATIC_CONTAINER_EXCEPTION_HPP_ */
