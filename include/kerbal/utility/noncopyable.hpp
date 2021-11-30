/**
 * @file       noncopyable.hpp
 * @brief
 * @date       2018-10-2
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_NONCOPYABLE_HPP
#define KERBAL_UTILITY_NONCOPYABLE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>


namespace kerbal
{

	namespace utility
	{

#	if __cplusplus < 201103L

		class noncopyconstructible
		{
			protected:

				noncopyconstructible() KERBAL_NOEXCEPT
				{
				}

				~noncopyconstructible() KERBAL_NOEXCEPT
				{
				}

			private:
				noncopyconstructible(const noncopyconstructible &) KERBAL_NOEXCEPT;
		};

#	else

		class noncopyconstructible
		{
			protected:

				KERBAL_CONSTEXPR
				noncopyconstructible() KERBAL_NOEXCEPT = default;

				~noncopyconstructible() KERBAL_NOEXCEPT = default;

			private:
				noncopyconstructible(const noncopyconstructible &) = delete;
		};

#	endif


#	if __cplusplus < 201103L

		class noncopyassignable
		{
			protected:

				noncopyassignable() KERBAL_NOEXCEPT
				{
				}

				~noncopyassignable() KERBAL_NOEXCEPT
				{
				}

			private:
				noncopyassignable& operator=(const noncopyassignable &) KERBAL_NOEXCEPT;
		};

#	else

		class noncopyassignable
		{
			protected:

				KERBAL_CONSTEXPR
				noncopyassignable() KERBAL_NOEXCEPT = default;

				~noncopyassignable() KERBAL_NOEXCEPT = default;

			private:
				noncopyassignable& operator=(const noncopyassignable &) = delete;
		};

#	endif

		class noncopyable :
				protected kerbal::utility::noncopyconstructible,
				protected kerbal::utility::noncopyassignable
		{

#	if __cplusplus >= 201103L

			protected:

				KERBAL_CONSTEXPR
				noncopyable() KERBAL_NOEXCEPT = default;

				~noncopyable() KERBAL_NOEXCEPT = default;

#	endif

		};

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_UTILITY_NONCOPYABLE_HPP
