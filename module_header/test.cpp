/**
 * @file       test.cpp
 * @brief
 * @date       2022-11-25
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#if MOH

module;

#include <iostream>

export module test;

import <kerbal/container/vector.hpp>;
import <kerbal/random/mersenne_twister_engine.hpp>;

#else

#include <iostream>
#include <kerbal/container/vector.hpp>
#include <kerbal/random/mersenne_twister_engine.hpp>

#endif

int main()
{
	kerbal::container::vector<int> v(10);
	kerbal::random::mt19937 eg;

	for (auto & e : v) {
		e = eg() % 10;
	}

	for (auto & e : v) {
		std::cout << e << std::endl;
	}
}
