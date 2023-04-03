/**
 * @file       vector.hpp
 * @brief
 * @date       2020-6-12
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_VECTOR_HPP
#define KERBAL_CONTAINER_VECTOR_HPP


#include <kerbal/config/modules/modules.hpp>

#if KERBAL_ENABLE_MODULES
module;
#endif


#if KERBAL_ENABLE_MODULES
export module kerbal.container.vector;
#endif


#if KERBAL_ENABLE_MODULES
export import kerbal.container.vector.fwd;
export import kerbal.container.vector.decl;
export import kerbal.container.vector.impl;
#else
#include <kerbal/container/vector/vector.fwd.hpp>
#include <kerbal/container/vector/vector.decl.hpp>
#include <kerbal/container/vector/vector.impl.hpp>
#endif

#endif // KERBAL_CONTAINER_VECTOR_HPP
