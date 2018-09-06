/*
 * object_count.hpp
 *
 *  Created on: 2018年9月6日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_UTILITY_OBJECT_COUNT_HPP_
#define INCLUDE_KERBAL_UTILITY_OBJECT_COUNT_HPP_

#include <cstddef>

namespace kerbal
{
	namespace utility
	{
		template <typename ObjectType, typename CountingType = size_t>
		struct Object_count
		{
			public:
				typedef CountingType counting_type;

				typedef class CountingTypePackage
				{
					protected:
						friend class Object_count;
						CountingType c;

					public:
						CountingTypePackage() :
								c(0)
						{
						}

					protected:

#					if __cplusplus >= 201103L
						CountingTypePackage(const CountingTypePackage&) = delete;
						CountingTypePackage& operator=(const CountingTypePackage&) = delete;
#					else
						CountingTypePackage(const CountingTypePackage&);
						CountingTypePackage& operator=(const CountingTypePackage&);
#					endif

						CountingTypePackage& operator++()
						{
							++c;
							return *this;
						}

						CountingTypePackage operator++(int)
						{
							CountingTypePackage tmp(*this);
							++c;
							return tmp;
						}

						CountingTypePackage& operator--()
						{
							--c;
							return *this;
						}

						CountingTypePackage operator--(int)
						{
							CountingTypePackage tmp(*this);
							--c;
							return tmp;
						}
				} CountingTypePackage;

				static CountingTypePackage count;

			protected:
				Object_count()
				{
					++count;
				}

				~Object_count()
				{
					--count;
				}

			public:
				static counting_type get_count()
				{
					return count.c;
				}
		};

		template <typename ObjectType, typename CountingType>
		extern
		typename Object_count<ObjectType, CountingType>::CountingTypePackage
		Object_count<ObjectType, CountingType>::count;

	} /* namespace utility */

} /* namespace kerbal */


#endif /* INCLUDE_KERBAL_UTILITY_OBJECT_COUNT_HPP_ */
