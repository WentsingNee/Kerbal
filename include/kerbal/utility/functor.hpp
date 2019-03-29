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

#ifndef INCLUDE_KERBAL_UTILITY_FUNCTOR_HPP_
#define INCLUDE_KERBAL_UTILITY_FUNCTOR_HPP_

#include <kerbal/utility/noncopyable.hpp>

namespace kerbal
{
	namespace utility
	{

		template <typename Type>
		class functor: public kerbal::utility::noncopyable
		{
			public:
				typedef Type return_type;

			private:
				return_type value;

			protected:

				functor(const Type & value) :
					value(value)
				{
				}

				typedef functor init;

			public:

				operator return_type()
				{
					return value;
				}
		};

		template <typename Type>
		class functor<const Type> : public kerbal::utility::noncopyable
		{
			public:
				typedef const Type return_type;

			private:
				return_type value;

			protected:

				functor(const Type & value) :
					value(value)
				{
				}

				typedef functor init;

			public:

				operator return_type()
				{
					return value;
				}
		};

		template <typename Type>
		class functor<Type &> : public kerbal::utility::noncopyable
		{
			public:
				typedef Type & return_type;

			protected:
				return_type value;

				functor(Type & value) :
					value(value)
				{
				}

				typedef functor init;

			public:

				operator return_type()
				{
					return value;
				}
		};

		template <>
		class functor<void> : public kerbal::utility::noncopyable
		{
			protected:

				typedef functor init;
		};

	}/* namespace utility */

}/* namespace kerbal */

#endif /* INCLUDE_KERBAL_UTILITY_FUNCTOR_HPP_ */
