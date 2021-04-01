/**
 * @file       cxx98_allocator_base.hpp
 * @brief
 * @date       2021-03-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_DETAIL_CXX98_ALLOCATOR_BASE_HPP
#define KERBAL_MEMORY_ALLOCATOR_DETAIL_CXX98_ALLOCATOR_BASE_HPP

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory//uninitialized/construct_at.hpp>
#include <kerbal/memory/uninitialized/destroy.hpp>


namespace kerbal
{

	namespace memory
	{

		namespace detail
		{

			template <typename Tp>
			struct cxx98_allocator_base
			{

#		if __cplusplus < 201103L

				public:
					typedef Tp							value_type;
					typedef value_type*					pointer;

					void destroy(pointer p) KERBAL_NOEXCEPT
					{
						kerbal::algorithm::destroy_at(p);
					}


					void construct(Tp * p)
					{
						kerbal::algorithm::construct_at(p);
					}

					template <typename Arg0>
					void construct(Tp * p, const Arg0 & arg0)
					{
						kerbal::algorithm::construct_at(p, arg0);
					}

					template <typename Arg0, typename Arg1>
					void construct_at(Tp * p, const Arg0 & arg0, const Arg1 & arg1)
					{
						kerbal::algorithm::construct_at(p, arg0, arg1);
					}

					template <typename Arg0, typename Arg1, typename Arg2>
					void construct(Tp * p, const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2)
					{
						kerbal::algorithm::construct_at(p, arg0, arg1, arg2);
					}

#		endif

			};

		} // namespace detail

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_ALLOCATOR_DETAIL_CXX98_ALLOCATOR_BASE_HPP
