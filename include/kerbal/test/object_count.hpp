/**
 * @file       object_count.hpp
 * @brief
 * @date       2018-9-6
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TEST_OBJECT_COUNT_HPP
#define KERBAL_TEST_OBJECT_COUNT_HPP

#include <cstddef>


namespace kerbal
{

	namespace test
	{

		template <typename ObjectType, typename CountingType = std::ptrdiff_t >
		class object_count
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

				object_count(const object_count&)
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

	} // namespace test

} // namespace kerbal

#endif // KERBAL_TEST_OBJECT_COUNT_HPP
