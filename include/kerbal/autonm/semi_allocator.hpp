/**
 * @file       semi_allocator.hpp
 * @brief
 * @date       2021-07-05
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_AUTONM_SEMI_ALLOCATOR_HPP
#define KERBAL_AUTONM_SEMI_ALLOCATOR_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#include <cstddef>


namespace kerbal
{

	namespace autonm
	{

		template <typename T>
		class semi_allocator_base
		{
			public:
				typedef T                    value_type;
				typedef value_type*          pointer;
				typedef std::size_t          size_type;

				KERBAL_CONSTEXPR14
				void destroy(pointer p) KERBAL_NOEXCEPT
				{
					// must be remained and keep empty, otherwise allocator_traits will
					// execute default destroy policy (aka kerbal::memory::destroy_at)
				}

		};


		template <typename T = void>
		class discard_deallocate_semi_allocator :
				public semi_allocator_base<T>
		{
			private:
				typedef semi_allocator_base<T> super;

			public:
				typedef typename super::value_type       value_type;
				typedef typename super::pointer          pointer;
				typedef typename super::size_type        size_type;

				KERBAL_CONSTEXPR14
				void deallocate(pointer, size_type) KERBAL_NOEXCEPT
				{
				}
		};


		template <typename T = void>
		class default_delete_semi_allocator :
				public semi_allocator_base<T>
		{
			private:
				typedef semi_allocator_base<T> super;

			public:
				typedef typename super::value_type       value_type;
				typedef typename super::pointer          pointer;
				typedef typename super::size_type        size_type;

				KERBAL_CONSTEXPR20
				void deallocate(pointer p, size_type) KERBAL_NOEXCEPT
				{
					delete p;
				}
		};

	} // namespace autonm

} // namespace kerbal

#endif // KERBAL_AUTONM_SEMI_ALLOCATOR_HPP
