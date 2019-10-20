/*
 * object_count.hpp
 *
 *  Created on: 2018-9-6
 *      Author: peter
 */

#ifndef KERBAL_TEST_OBJECT_COUNT_HPP_
#define KERBAL_TEST_OBJECT_COUNT_HPP_

#include <cstddef>
#include <kerbal/utility/noncopyable.hpp>

namespace kerbal
{
	namespace test
	{
		template <typename ObjectType, typename CountingType = size_t>
		class object_count: kerbal::utility::noncopyable
		{
			public:
				typedef CountingType counting_type;

			private:
				static counting_type& ref()
				{
					static counting_type counter(0);
					return counter;
				}

			protected:
				object_count()
				{
					++ref();
				}

				~object_count()
				{
					--ref();
				}

			public:
				static const counting_type& get_count()
				{
					return ref();
				}
		};

	} /* namespace test */

} /* namespace kerbal */


#endif /* KERBAL_TEST_OBJECT_COUNT_HPP_ */
