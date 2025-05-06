/**
 * @file       list.cppm
 * @brief
 * @date       2025-05-06
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

module;

#include <kerbal/container/list.hpp>

export module kerbal.container.list;

export
namespace kerbal
{

	namespace container
	{

		using kerbal::container::list;
		using kerbal::container::operator==;
		using kerbal::container::operator!=;
		using kerbal::container::operator<;
		using kerbal::container::operator<=;
		using kerbal::container::operator>;
		using kerbal::container::operator>=;

	} // namespace container

} // namespace kerbal

KERBAL_NAMESPACE_STD_BEGIN

	using std::swap;

KERBAL_NAMESPACE_STD_END
