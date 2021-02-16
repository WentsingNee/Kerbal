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

			private:
				noncopyconstructible(const noncopyconstructible &);
		};

#	else

		class noncopyconstructible
		{
			protected:
				noncopyconstructible() noexcept = default;
				~noncopyconstructible() noexcept = default;

			private:
				noncopyconstructible(const noncopyconstructible &) noexcept = delete;
		};

#	endif


#	if __cplusplus < 201103L

		class noncopyassignable
		{
			protected:
				noncopyassignable()
				{
				}

				~noncopyassignable()
				{
				}

			private:
				noncopyassignable& operator=(const noncopyassignable &);
		};

#	else

		class noncopyassignable
		{
			protected:
				noncopyassignable() noexcept = default;
				~noncopyassignable() noexcept = default;

			private:
				noncopyassignable& operator=(const noncopyassignable &) noexcept = delete;
		};

#	endif

		class noncopyable :
				protected kerbal::utility::noncopyconstructible,
				protected kerbal::utility::noncopyassignable
		{
		};

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_UTILITY_NONCOPYABLE_HPP
