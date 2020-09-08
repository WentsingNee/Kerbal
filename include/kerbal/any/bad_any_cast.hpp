/**
 * @file       bad_any_cast.hpp
 * @brief      
 * @date       2019-7-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ANY_BAD_ANY_CAST_HPP
#define KERBAL_ANY_BAD_ANY_CAST_HPP

#include <kerbal/compatibility/noexcept.hpp>

#include <stdexcept>
#include <typeinfo>


namespace kerbal
{

	namespace any
	{

		class bad_any_cast :
					public std::logic_error
		{
			public:
				bad_any_cast(const std::type_info & actual, const std::type_info & require) :
						std::logic_error("bad any_cast")
				{
				}

				virtual const char* what() const KERBAL_NOEXCEPT
				{
					return "bad any_cast";
				}
		};

	} // namespace any

} // namespace kerbal


#endif // KERBAL_ANY_BAD_ANY_CAST_HPP
