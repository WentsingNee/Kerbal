/**
 * @file       type_identity.hpp
 * @brief
 * @date       2020-04-08
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_TYPE_IDENTITY_HPP
#define KERBAL_TYPE_TRAITS_TYPE_IDENTITY_HPP


namespace kerbal
{

	namespace type_traits
	{

		template <typename T>
		struct type_identity
		{
				typedef T type;
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_TYPE_IDENTITY_HPP
