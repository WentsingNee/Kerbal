/*
 * variable.hpp
 *
 *  Created on: 2018年6月1日
 *      Author: peter
 */

#ifndef SRC_REDIS_REDISDATASTRUCT_VARIABLE_HPP_
#define SRC_REDIS_REDISDATASTRUCT_VARIABLE_HPP_

#include <iostream>
#include <type_traits>

namespace kerbal
{
	namespace redis
	{

		template <typename Type>
		class Variable: public Reference<Type>
		{
			protected:
				typedef Reference<Type> supper_t;

			public:
				Variable(const Context & conn, const char key[]) :
						supper_t(conn, key)
				{
				}

				Variable(const Context & conn, const std::string & key) :
						supper_t(conn, key)
				{
				}

				Variable& operator=(const Type & src)
				{
					supper_t::operator=(src);
					return *this;
				}
		};

		template <typename Type>
		class ConstVariable: public ConstReference<Type>
		{
			protected:
				typedef ConstReference<Type> supper_t;

			public:
				ConstVariable(const Context & conn, const std::string & key) :
						supper_t(conn, key)
				{
				}
		};

	}
}


#endif /* SRC_REDIS_REDISDATASTRUCT_VARIABLE_HPP_ */
