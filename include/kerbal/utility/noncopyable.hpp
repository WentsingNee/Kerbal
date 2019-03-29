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

		class noncopyconstuctible
		{
			protected:
				noncopyconstuctible()
				{
				}

				~noncopyconstuctible()
				{
				}

				noncopyconstuctible(const noncopyconstuctible&);
		};

		class nonassignable
		{
			private:
				nonassignable& operator=(const nonassignable &);
		};

#	else

		class noncopyconstuctible
		{
			protected:
				noncopyconstuctible() noexcept = default;
				~noncopyconstuctible() noexcept = default;

			private:
				noncopyconstuctible(const noncopyconstuctible&) noexcept = delete;
		};

		class nonassignable
		{
			private:
				nonassignable& operator=(const nonassignable &) noexcept = delete;
		};

#	endif

		class noncopyable : public noncopyconstuctible, public nonassignable
		{
		};

	}/* namespace utility */

}/* namespace kerbal */
#endif /* INCLUDE_KERBAL_UTILITY_NONCOPYABLE_HPP_ */
