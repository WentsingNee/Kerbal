/**
 * @file       conditional.hpp
 * @brief
 * @date       2019-4-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_CONDITIONAL_HPP
#define KERBAL_TYPE_TRAITS_CONDITIONAL_HPP



namespace kerbal
{

	namespace type_traits
	{

		template <bool Condition, typename TrueType, typename FalseType>
		struct conditional
		{
				typedef TrueType type;
		};

		template <typename TrueType, typename FalseType>
		struct conditional<false, TrueType, FalseType>
		{
				typedef FalseType type;
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_CONDITIONAL_HPP
