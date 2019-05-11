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

		class noncopyconstructible
		{
			protected:
				noncopyconstructible()
				{
				}

				~noncopyconstructible()
				{
				}

				noncopyconstructible(const noncopyconstructible&);
		};

		class nonassignable
		{
			private:
				nonassignable& operator=(const nonassignable &);
		};

#	else

		class noncopyconstructible
		{
			protected:
				noncopyconstructible() noexcept = default;
				~noncopyconstructible() noexcept = default;

			private:
				noncopyconstructible(const noncopyconstructible&) noexcept = delete;
		};

		class nonassignable
		{
			private:
				nonassignable& operator=(const nonassignable &) noexcept = delete;
				nonassignable& operator=(nonassignable &&) noexcept = delete;
		};

#	endif

		class noncopyable : public noncopyconstructible, public nonassignable
		{
		};

	}/* namespace utility */

}/* namespace kerbal */
#endif /* INCLUDE_KERBAL_UTILITY_NONCOPYABLE_HPP_ */
