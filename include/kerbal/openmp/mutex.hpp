/**
 * @file       mutex.hpp
 * @brief
 * @date       2020-07-21
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OPENMP_MUTEX_HPP
#define KERBAL_OPENMP_MUTEX_HPP

#include <kerbal/openmp/disable_warning.hpp>

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/utility/noncopyable.hpp>

#include <omp.h>


namespace kerbal
{

	namespace openmp
	{

		class mutex : private kerbal::utility::noncopyable
		{
			private:
				::omp_lock_t omp_lock;

			public:
				mutex() KERBAL_NOEXCEPT :
					omp_lock()
				{
					::omp_init_lock(&omp_lock);
				}

				~mutex() KERBAL_NOEXCEPT
				{
					::omp_destroy_lock(&omp_lock);
				}

				void lock() KERBAL_NOEXCEPT
				{
					::omp_set_lock(&omp_lock);
				}

				bool try_lock() KERBAL_NOEXCEPT
				{
					return ::omp_test_lock(&omp_lock);
				}

				void unlock() KERBAL_NOEXCEPT
				{
					::omp_unset_lock(&omp_lock);
				}

		};

		class nest_mutex : private kerbal::utility::noncopyable
		{
			private:
				::omp_nest_lock_t omp_lock;

			public:
				nest_mutex() KERBAL_NOEXCEPT :
					omp_lock()
				{
					::omp_init_nest_lock(&omp_lock);
				}

				~nest_mutex() KERBAL_NOEXCEPT
				{
					::omp_destroy_nest_lock(&omp_lock);
				}

				void lock() KERBAL_NOEXCEPT
				{
					::omp_set_nest_lock(&omp_lock);
				}

				bool try_lock() KERBAL_NOEXCEPT
				{
					return ::omp_test_nest_lock(&omp_lock);
				}

				void unlock() KERBAL_NOEXCEPT
				{
					::omp_unset_nest_lock(&omp_lock);
				}

		};

	} // namespace openmp

} // namespace kerbal

#endif // KERBAL_OPENMP_MUTEX_HPP
