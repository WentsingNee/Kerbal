/**
 * @file       avl_set.cppm
 * @brief
 * @date       2025-05-06
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

module;

#include <kerbal/container/avl_set.hpp>

export module kerbal.container.avl_set;

export
namespace kerbal
{

	namespace container
	{

		using kerbal::container::avl_set;
		using kerbal::container::operator==;
		using kerbal::container::operator!=;
		using kerbal::container::operator<;
		using kerbal::container::operator<=;
		using kerbal::container::operator>;
		using kerbal::container::operator>=;

	} // namespace container

	namespace algorithm
	{

		using kerbal::algorithm::swap;

	} // namespace container

} // namespace kerbal

KERBAL_NAMESPACE_STD_BEGIN

	using std::swap;

KERBAL_NAMESPACE_STD_END
