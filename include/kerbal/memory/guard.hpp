/**
 * @file       guard.hpp
 * @brief      
 * @date       2019-7-26
 * @author     peter
 * @copyright
 *      peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_GUARD_HPP_
#define KERBAL_MEMORY_GUARD_HPP_

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/default_delete.hpp>
#include <kerbal/utility/declval.hpp>
#include <kerbal/utility/noncopyable.hpp>

#include <cstddef>
#if __cplusplus >= 201103L
# include <type_traits>
# include <kerbal/compatibility/move.hpp>
#endif

namespace kerbal
{
	namespace memory
	{
		template <typename Tp, typename Deleter = kerbal::memory::default_delete<Tp> >
		class guard: kerbal::utility::noncopyable
		{
			public:
				typedef Tp element_type;
				typedef Tp* pointer;
				typedef Deleter deleter_type;

			protected:
				pointer ptr;
				Deleter deleter;

			public:
				guard(pointer ptr) KERBAL_CONDITIONAL_NOEXCEPT(std::is_trivially_default_constructible<deleter_type>::value) :
					ptr(ptr), deleter()
				{
				}

				guard(pointer ptr, const deleter_type& deleter) KERBAL_CONDITIONAL_NOEXCEPT(std::is_trivially_copy_constructible<deleter_type>::value) :
					ptr(ptr), deleter(deleter)
				{
				}

#			if __cplusplus >= 201103L

				guard(pointer ptr, deleter_type&& deleter) KERBAL_CONDITIONAL_NOEXCEPT(std::is_trivially_move_constructible<deleter_type>::value) :
					ptr(ptr), deleter(kerbal::compatibility::move(deleter))
				{
				}

#			endif

				~guard() KERBAL_CONDITIONAL_NOEXCEPT(noexcept(kerbal::utility::declthis<guard>()->reset()))
				{
					this->reset();
				}

				pointer release() KERBAL_NOEXCEPT
				{
					pointer p = this->ptr;
					this->ptr = NULL;
					return p;
				}

				void reset() KERBAL_CONDITIONAL_NOEXCEPT(noexcept(
						kerbal::utility::declthis<guard>()->deleter(kerbal::utility::declthis<guard>()->ptr)))
				{
					this->deleter(this->ptr);
					this->ptr = NULL;
				}

		};

		template <typename Tp, typename Deleter>
		class guard<Tp[], Deleter>: kerbal::utility::noncopyable
		{
			public:
				typedef Tp element_type [];
				typedef Tp* pointer;
				typedef Deleter deleter_type;

			protected:
				pointer ptr;
				Deleter deleter;

			public:
				guard(pointer ptr) KERBAL_CONDITIONAL_NOEXCEPT(std::is_trivially_default_constructible<deleter_type>::value) :
					ptr(ptr), deleter()
				{
				}

				guard(pointer ptr, const deleter_type& deleter) KERBAL_CONDITIONAL_NOEXCEPT(std::is_trivially_copy_constructible<deleter_type>::value) :
					ptr(ptr), deleter(deleter)
				{
				}

#			if __cplusplus >= 201103L

				guard(pointer ptr, deleter_type&& deleter) KERBAL_CONDITIONAL_NOEXCEPT(std::is_trivially_move_constructible<deleter_type>::value) :
					ptr(ptr), deleter(kerbal::compatibility::move(deleter))
				{
				}

#			endif

				~guard() KERBAL_CONDITIONAL_NOEXCEPT(noexcept(kerbal::utility::declthis<guard>()->reset()))
				{
					this->reset();
				}

				pointer release() KERBAL_NOEXCEPT
				{
					pointer p = this->ptr;
					this->ptr = NULL;
					return p;
				}

				void reset() KERBAL_CONDITIONAL_NOEXCEPT(noexcept(
						kerbal::utility::declthis<guard>()->deleter(kerbal::utility::declthis<guard>()->ptr)))
				{
					this->deleter(this->ptr);
					this->ptr = NULL;
				}

		};

	} // namespace memory

} // namespace kerbal

#endif /* KERBAL_MEMORY_GUARD_HPP_ */
