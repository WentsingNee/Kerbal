/**
 * @file       test3.cpp
 * @brief
 * @date       2023-04-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

import kerbal.type_traits.add_const;
import kerbal.type_traits.is_same;
import kerbal.type_traits.remove_const;

#include <iostream>

using namespace std;

int main()
{
	typedef typename kerbal::type_traits::add_const<int>::type T;
	typedef typename kerbal::type_traits::remove_const<T>::type U;
	std::cout << kerbal::type_traits::is_same<U, int>::value << std::endl;
}
