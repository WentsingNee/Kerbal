/**
 * @file		real_functor.hpp
 * @brief
 * @date		2018年3月12日
 * @author		Peter
 * @copyright	Peter
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 */

#ifndef INCLUDE_KERBAL_UTILITY_REAL_FUNCTOR_HPP_
#define INCLUDE_KERBAL_UTILITY_REAL_FUNCTOR_HPP_

#include <kerbal/utility/delete_cpy_and_assign.hpp>

namespace kerbal
{
	namespace utility
	{

		template <typename Return_type>
		class Functor: virtual public Delete_cpy_and_assign<Functor<Return_type> >
		{
			protected:
				Return_type value;

				Functor() :
						value()
				{
				}

				Functor(const Return_type & value) :
						value(value)
				{
				}

				typedef Functor init;

			public:
				operator Return_type()
				{
					return value;
				}
		};

		template <typename Return_type>
		class Functor<const Return_type> : virtual public Delete_cpy_and_assign<
				Functor<const Return_type> >
		{
			protected:
				Return_type value;

				Functor() :
						value()
				{
				}

				Functor(const Return_type & value) :
						value(value)
				{
				}

				typedef Functor init;

			public:
				operator const Return_type()
				{
					return value;
				}
		};

		template <typename Return_type>
		class Functor<Return_type &> : virtual public Delete_cpy_and_assign<Functor<Return_type &> >
		{
			protected:
				Return_type & value;

				Functor(Return_type & value) :
						value(value)
				{
				}

				typedef Functor init;

			public:
				operator Return_type &()
				{
					return value;
				}
		};

		template <>
		class Functor<void> : virtual public Delete_cpy_and_assign<Functor<void> >
		{
			protected:
				Functor()
				{
				}
		};

	}/* namespace utility */

}/* namespace kerbal */

#endif /* INCLUDE_KERBAL_UTILITY_REAL_FUNCTOR_HPP_ */
