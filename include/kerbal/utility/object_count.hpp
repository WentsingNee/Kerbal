/*
 * object_count.hpp
 *
 *  Created on: 2018年9月6日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_UTILITY_OBJECT_COUNT_HPP_
#define INCLUDE_KERBAL_UTILITY_OBJECT_COUNT_HPP_

#include <cstddef>
#include <kerbal/utility/noncopyable.hpp>

namespace kerbal
{
	namespace utility
	{
		template <typename ObjectType, typename CountingType = size_t>
		struct object_count : public kerbal::utility::noncopyable
		{
			public:
				typedef CountingType counting_type;

				typedef class counting_type_wrapper
				{
					protected:
						friend class object_count;
						CountingType c;

					public:
						counting_type_wrapper() :
								c(0)
						{
						}

					protected:

						counting_type_wrapper& operator++()
						{
							++c;
							return *this;
						}

						counting_type_wrapper operator++(int)
						{
							counting_type_wrapper tmp(*this);
							++c;
							return tmp;
						}

						counting_type_wrapper& operator--()
						{
							--c;
							return *this;
						}

						counting_type_wrapper operator--(int)
						{
							counting_type_wrapper tmp(*this);
							--c;
							return tmp;
						}
				} counting_type_wrapper;

				static counting_type_wrapper count;

			protected:
				object_count()
				{
					++count;
				}

				~object_count()
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
		typename object_count<ObjectType, CountingType>::counting_type_wrapper
		object_count<ObjectType, CountingType>::count;

	} /* namespace utility */

} /* namespace kerbal */


#endif /* INCLUDE_KERBAL_UTILITY_OBJECT_COUNT_HPP_ */
