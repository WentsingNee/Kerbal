/**
 * @file       bad_function_cast.hpp
 * @brief
 * @date       2023-12-02
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_FUNCTION_BAD_FUNCTION_CAST_HPP
#define KERBAL_FUNCTION_BAD_FUNCTION_CAST_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <stdexcept>
#include <typeinfo>


namespace kerbal
{

	namespace function
	{

		KERBAL_MODULE_EXPORT
		class bad_function_cast :
			public std::runtime_error
		{
			public:
				bad_function_cast(const std::type_info & actual, const std::type_info & required) :
					std::runtime_error("bad function cast")
				{
				}
		};

	} // namespace function

} // namespace kerbal

#endif // KERBAL_FUNCTION_BAD_FUNCTION_CAST_HPP
