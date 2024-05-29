/**
 * @file       general_back_inserter.hpp
 * @brief      
 * @date       2019-10-7
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ITERATOR_GENERAL_BACK_INSERTER_HPP
#define KERBAL_ITERATOR_GENERAL_BACK_INSERTER_HPP

#include <kerbal/compatibility/constexpr.hpp>

#include <cstddef>
#include <iterator>


namespace kerbal
{

	namespace iterator
	{

		template <typename Container>
		struct general_back_insert_iterator
		{
				typedef std::back_insert_iterator<Container> type;
		};

		template <typename T>
		struct general_back_insert_iterator<T[]>
		{
				typedef T* type;
		};

		template <typename T, std::size_t N>
		struct general_back_insert_iterator<T[N]>
		{
				typedef T* type;
		};

		template <typename Container>
		KERBAL_CONSTEXPR14
		typename general_back_insert_iterator<Container>::type
		general_inserter(Container & container)
		{
			typedef typename general_back_insert_iterator<Container>::type inserter;
			return inserter(container);
		}

	} // namespace iterator

} // namespace kerbal

#endif // KERBAL_ITERATOR_GENERAL_BACK_INSERTER_HPP
