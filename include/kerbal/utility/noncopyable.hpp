/*
 * noncopyable.hpp
 *
 *  Created on: 2018年10月2日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_UTILITY_NONCOPYABLE_HPP_
#define INCLUDE_KERBAL_UTILITY_NONCOPYABLE_HPP_

namespace kerbal
{
	namespace utility
	{

#	if __cplusplus < 201103L

		class noncopyable
		{
			protected:
				noncopyable()
				{
				}

				~noncopyable()
				{
				}

				noncopyable(const noncopyable&);
		};

		class nonassignable
		{
			private:
				nonassignable& operator=(const nonassignable &);
		};

#	else

		class noncopyable
		{
			protected:
				noncopyable() noexcept = default;
				~noncopyable() noexcept = default;

			private:
				noncopyable(const noncopyable&) noexcept = delete;
		};

		class nonassignable
		{
			private:
				nonassignable& operator=(const nonassignable &) noexcept = delete;
		};

#	endif

	}/* namespace utility */

}/* namespace kerbal */
#endif /* INCLUDE_KERBAL_UTILITY_NONCOPYABLE_HPP_ */
