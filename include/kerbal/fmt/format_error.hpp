/**
 * @file       format_error.hpp
 * @brief
 * @date       2020-10-08
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */


#ifndef KERBAL_FMT_FORMAT_ERROR_HPP
#define KERBAL_FMT_FORMAT_ERROR_HPP

#include <kerbal/utility/throw_this_exception.hpp>

#include <stdexcept>


namespace kerbal
{

	namespace fmt
	{

		class format_error :
			public std::runtime_error,
			public kerbal::utility::throw_this_exception_helper<format_error>
		{
			public:
				explicit
				format_error(const std::string & arg) :
					std::runtime_error(arg)
				{
				}
		};

	} // namespace fmt

} // namespace kerbal


#endif // KERBAL_FMT_FORMAT_ERROR_HPP
