/**
 * @file       dereferenceable.hpp
 * @brief      
 * @date       2019-7-14
 * @author     peter
 * @copyright
 *      peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OPERATORS_DEREFERENCEABLE_HPP_
#define KERBAL_OPERATORS_DEREFERENCEABLE_HPP_

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/utility/addressof.hpp>

namespace kerbal
{
	namespace operators
	{
		template <typename Tp, typename Ptr>
		struct dereferenceable
		{
				Ptr operator->() const
						KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(kerbal::utility::addressof(*static_cast<const Tp&>(*this)))
						)
				{
					return kerbal::utility::addressof(*static_cast<const Tp&>(*this));
				}
		};

	} // namespace operators

} // namespace kerbal

#endif /* KERBAL_OPERATORS_DEREFERENCEABLE_HPP_ */
