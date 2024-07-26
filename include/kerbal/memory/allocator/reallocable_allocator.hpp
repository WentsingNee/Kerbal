/**
 * @file       reallocable_allocator.hpp
 * @brief
 * @date       2020-08-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ALLOCATOR_REALLOCABLE_ALLOCATOR_HPP
#define KERBAL_MEMORY_ALLOCATOR_REALLOCABLE_ALLOCATOR_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/bad_alloc.hpp>
#include <kerbal/memory/bad_array_new_length.hpp>
#include <kerbal/numeric/numeric_limits.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_trivially_copyable.hpp>
#include <kerbal/utility/throw_this_exception.hpp>

#include <cstdlib>
#include <cstddef>


namespace kerbal
{

	namespace memory
	{

		KERBAL_MODULE_EXPORT
		template <typename T>
		struct is_trivially_reallocate_type :
			kerbal::type_traits::try_test_is_trivially_copyable<T>::IS_TRUE
		{
		};

		namespace detail
		{

			template <typename T, bool = is_trivially_reallocate_type<T>::value>
			class reallocable_allocator_realloc_overload_helper;

			template <typename T>
			class reallocable_allocator_realloc_overload_helper<T, true>
			{
				protected:
					typedef T					value_type;
					typedef value_type *		pointer;
					typedef std::size_t			size_type;

				public:
					typedef kerbal::type_traits::true_type SUPPORT_REALLOCATE;

				public:
					static pointer reallocate(pointer p, size_type /*n_old*/, size_type n_new)
					{
						p = static_cast<pointer>(::realloc(p, sizeof(value_type) * n_new));
						if (p == NULL) {
							kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
						}
						return p;
					}

			};

			template <typename T>
			class reallocable_allocator_realloc_overload_helper<T, false>
			{
				public:
					typedef kerbal::type_traits::false_type SUPPORT_REALLOCATE;
			};

		} // namespace detail

		KERBAL_MODULE_EXPORT
		template <typename T>
		class reallocable_allocator :
			public detail::reallocable_allocator_realloc_overload_helper<T>
		{
			public:
				typedef T							value_type;
				typedef value_type *				pointer;

				typedef std::size_t					size_type;
				typedef std::ptrdiff_t				difference_type;

				typedef kerbal::type_traits::true_type		propagate_on_container_move_assignment;
				typedef kerbal::type_traits::true_type		is_always_equal;

				static pointer allocate(size_type n)
				{
					typedef kerbal::type_traits::integral_constant<
						size_type,
						kerbal::numeric::numeric_limits<size_type>::MAX::value / sizeof(value_type)
					> MAX_SIZE;

					if (n > MAX_SIZE::value) {
						kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_array_new_length>::throw_this_exception();
					}

					pointer p = static_cast<pointer>(::malloc(sizeof(value_type) * n));
					if (p == NULL) {
						kerbal::utility::throw_this_exception_helper<kerbal::memory::bad_alloc>::throw_this_exception();
					}
					return p;
				}

				static void deallocate(pointer p, size_type /*n*/) KERBAL_NOEXCEPT
				{
					::free(p);
				}

		};

	} // namespace memory

} // namespace kerbal


#endif // KERBAL_MEMORY_ALLOCATOR_REALLOCABLE_ALLOCATOR_HPP
