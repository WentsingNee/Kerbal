/**
 * @file       guard.hpp
 * @brief      
 * @date       2019-7-26
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_GUARD_HPP
#define KERBAL_MEMORY_GUARD_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/default_delete.hpp>
#include <kerbal/utility/declval.hpp>
#include <kerbal/utility/member_compress_helper.hpp>
#include <kerbal/utility/noncopyable.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/compatibility/move.hpp>
#	include <kerbal/type_traits/is_nothrow_constructible.hpp>
#	include <kerbal/type_traits/is_nothrow_default_constructible.hpp>
#endif

#include <cstddef>


namespace kerbal
{

	namespace memory
	{

		template <typename T, typename Deleter = kerbal::memory::default_delete<T> >
		class guard;


		template <typename T, typename Deleter>
		class guard :
				private kerbal::utility::noncopyable,
				protected kerbal::utility::member_compress_helper<Deleter>
		{
			private:
				typedef kerbal::utility::member_compress_helper<Deleter> deleter_compress_helper;

			public:
				typedef T element_type;
				typedef T* pointer;
				typedef Deleter deleter_type;

			protected:
				pointer k_ptr;

			public:
				KERBAL_CONSTEXPR20
				guard(pointer ptr)
						KERBAL_CONDITIONAL_NOEXCEPT(
							kerbal::type_traits::try_test_is_nothrow_default_constructible<
								deleter_compress_helper
							>::IS_TRUE::value
						) :
						k_ptr(ptr)
				{
				}

				KERBAL_CONSTEXPR20
				guard(pointer ptr, const deleter_type & deleter)
						KERBAL_CONDITIONAL_NOEXCEPT((
							kerbal::type_traits::try_test_is_nothrow_constructible<
								deleter_compress_helper,
								kerbal::utility::in_place_t,
								const deleter_type &
							>::IS_TRUE::value
						)) :
						deleter_compress_helper(kerbal::utility::in_place_t(), deleter), k_ptr(ptr)
				{
				}

#			if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				guard(pointer ptr, deleter_type && deleter)
						KERBAL_CONDITIONAL_NOEXCEPT((
							kerbal::type_traits::try_test_is_nothrow_constructible<
								deleter_compress_helper,
								kerbal::utility::in_place_t,
								deleter_type &&
							>::IS_TRUE::value
						)) :
						deleter_compress_helper(kerbal::utility::in_place_t(), kerbal::compatibility::move(deleter)), k_ptr(ptr)
				{
				}

#			endif

				KERBAL_CONSTEXPR20
				~guard()
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(
								kerbal::utility::declthis<guard>()->get_deleter()(
									kerbal::utility::declthis<guard>()->k_ptr
								)
							)
						)
				{
					this->get_deleter()(this->k_ptr);
				}

				KERBAL_CONSTEXPR20
				pointer release() KERBAL_NOEXCEPT
				{
					pointer p = this->k_ptr;
					this->k_ptr = NULL;
					return p;
				}

				KERBAL_CONSTEXPR20
				void reset()
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(
								kerbal::utility::declthis<guard>()->get_deleter()(
									kerbal::utility::declthis<guard>()->k_ptr
								)
							)
						)
				{
					this->get_deleter(this->k_ptr);
					this->k_ptr = NULL;
				}

				KERBAL_CONSTEXPR20
				deleter_type & get_deleter() KERBAL_NOEXCEPT
				{
					return deleter_compress_helper::member();
				}

				KERBAL_CONSTEXPR20
				const deleter_type & get_deleter() const KERBAL_NOEXCEPT
				{
					return deleter_compress_helper::member();
				}

		};

		template <typename T, typename Deleter>
		class guard<T[], Deleter> :
				private kerbal::utility::noncopyable,
				protected kerbal::utility::member_compress_helper<Deleter>
		{
			private:
				typedef kerbal::utility::member_compress_helper<Deleter> deleter_compress_helper;

			public:
				typedef T element_type [];
				typedef T* pointer;
				typedef Deleter deleter_type;

			protected:
				pointer k_ptr;

			public:
				KERBAL_CONSTEXPR20
				guard(pointer ptr)
						KERBAL_CONDITIONAL_NOEXCEPT(
							kerbal::type_traits::try_test_is_nothrow_default_constructible<
								deleter_compress_helper
							>::IS_TRUE::value
						) :
						k_ptr(ptr)
				{
				}

				KERBAL_CONSTEXPR20
				guard(pointer ptr, const deleter_type & deleter)
						KERBAL_CONDITIONAL_NOEXCEPT((
							kerbal::type_traits::try_test_is_nothrow_constructible<
								deleter_compress_helper,
								kerbal::utility::in_place_t,
								const deleter_type &
							>::IS_TRUE::value
						)) :
						deleter_compress_helper(kerbal::utility::in_place_t(), deleter), k_ptr(ptr)
				{
				}

#			if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				guard(pointer ptr, deleter_type && deleter)
						KERBAL_CONDITIONAL_NOEXCEPT((
							kerbal::type_traits::try_test_is_nothrow_constructible<
								deleter_compress_helper,
								kerbal::utility::in_place_t,
								deleter_type &&
							>::IS_TRUE::value
						)) :
						deleter_compress_helper(kerbal::utility::in_place_t(), kerbal::compatibility::move(deleter)), k_ptr(ptr)
				{
				}

#			endif

				KERBAL_CONSTEXPR20
				~guard()
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(
								kerbal::utility::declthis<guard>()->get_deleter()(
									kerbal::utility::declthis<guard>()->k_ptr
								)
							)
						)
				{
					this->get_deleter()(this->k_ptr);
				}

				KERBAL_CONSTEXPR20
				pointer release() KERBAL_NOEXCEPT
				{
					pointer p = this->k_ptr;
					this->k_ptr = NULL;
					return p;
				}

				KERBAL_CONSTEXPR20
				void reset()
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(
								kerbal::utility::declthis<guard>()->get_deleter()(
									kerbal::utility::declthis<guard>()->k_ptr
								)
							)
						)
				{
					this->get_deleter(this->k_ptr);
					this->k_ptr = NULL;
				}

				KERBAL_CONSTEXPR20
				deleter_type & get_deleter() KERBAL_NOEXCEPT
				{
					return deleter_compress_helper::member();
				}

				KERBAL_CONSTEXPR20
				const deleter_type & get_deleter() const KERBAL_NOEXCEPT
				{
					return deleter_compress_helper::member();
				}

		};

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_GUARD_HPP
