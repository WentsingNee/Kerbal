/**
 * @file       any.cppm
 * @brief
 * @date       2025-05-06
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

module;

#include <kerbal/any/any.hpp>

export module kerbal.any.any;

export
namespace kerbal
{

	namespace any
	{

		using kerbal::any::basic_any;
		using kerbal::any::any;
		using kerbal::any::any_cast;

	} // namespace any

	namespace algorithm
	{

		using kerbal::algorithm::swap;

	} // namespace container

} // namespace kerbal

KERBAL_NAMESPACE_STD_BEGIN

	using std::swap;

KERBAL_NAMESPACE_STD_END
