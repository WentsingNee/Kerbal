/**
 * @file       unique_ptr.hpp
 * @brief      
 * @date       2019-7-26
 * @author     peter
 * @copyright
 *      peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_UNIQUE_PTR_HPP
#define KERBAL_MEMORY_UNIQUE_PTR_HPP

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/guard.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/compatibility/move.hpp>
#	include <kerbal/utility/forward.hpp>
#endif

#if __cplusplus >= 201103L
#	include <type_traits>
#endif

namespace kerbal
{

	namespace memory
	{

		template <typename Tp, typename Deleter = kerbal::memory::default_delete<Tp> >
		class unique_ptr: public kerbal::memory::guard<Tp, Deleter>
		{
			private:
				typedef kerbal::memory::guard<Tp, Deleter> guard;

			public:
				typedef typename guard::element_type element_type;
				typedef typename guard::pointer pointer;
				typedef typename guard::deleter_type deleter_type;

			public:
				unique_ptr() :
					guard(NULL)
				{
				}

#			if __cplusplus >= 201103L

				unique_ptr(std::nullptr_t) :
					guard(nullptr)
				{
				}

#			endif

				explicit unique_ptr(pointer ptr) :
					guard(ptr)
				{
				}

				unique_ptr(pointer ptr, const deleter_type& deleter) :
					guard(ptr, deleter)
				{
				}

#			if __cplusplus >= 201103L

				unique_ptr(pointer ptr, deleter_type&& deleter) :
					guard(ptr, kerbal::compatibility::move(deleter))
				{
				}

				unique_ptr(unique_ptr&& src) noexcept :
					guard(src.ptr)
				{
					src.ptr = nullptr;
				}

				unique_ptr& operator=(unique_ptr&& src) noexcept
				{
					this->reset();
					this->ptr = src.ptr;
					src.ptr = nullptr;
					return *this;
				}

				unique_ptr& operator=(std::nullptr_t) noexcept
				{
					this->reset();
					return *this;
				}

#			endif

				void reset() KERBAL_NOEXCEPT
				{
					this->guard::reset();
				}

				void reset(pointer p) KERBAL_NOEXCEPT
				{
					this->reset();
					this->ptr = p;
				}

				void swap(unique_ptr & with) KERBAL_NOEXCEPT
				{
					kerbal::algorithm::swap(this->ptr, with.ptr);
				}

				pointer get() const KERBAL_NOEXCEPT
				{
					return this->ptr;
				}

				operator bool() const KERBAL_NOEXCEPT
				{
					return this->ptr != NULL;
				}
				
				element_type& operator*() const KERBAL_NOEXCEPT
				{
					return *this->get();
				}

				pointer operator->() const KERBAL_NOEXCEPT
				{
					return this->get();
				}

		};
		
#	if __cplusplus < 201103L

		template <typename Tp, typename Arg0>
		kerbal::memory::unique_ptr<Tp>
		make_unique(const Arg0& arg0)
		{
			return kerbal::memory::unique_ptr<Tp>(new Tp(arg0)); 
		}

		template <typename Tp, typename Arg0, typename Arg1>
		kerbal::memory::unique_ptr<Tp>
		make_unique(const Arg0& arg0, const Arg1& arg1)
		{
			return kerbal::memory::unique_ptr<Tp>(new Tp(arg0, arg1)); 
		}

		template <typename Tp, typename Arg0, typename Arg1, typename Arg2>
		kerbal::memory::unique_ptr<Tp>
		make_unique(const Arg0& arg0, const Arg1& arg1, const Arg2& arg2)
		{
			return kerbal::memory::unique_ptr<Tp>(new Tp(arg0, arg1, arg2)); 
		}
		
		template <typename Tp, typename Arg0, typename Arg1, typename Arg2, typename Arg3>
		kerbal::memory::unique_ptr<Tp>
		make_unique(const Arg0& arg0, const Arg1& arg1, const Arg2& arg2, const Arg3& arg3)
		{
			return kerbal::memory::unique_ptr<Tp>(new Tp(arg0, arg1, arg2, arg3)); 
		}

		template <typename Tp, typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
		kerbal::memory::unique_ptr<Tp>
		make_unique(const Arg0& arg0, const Arg1& arg1, const Arg2& arg2, const Arg3& arg3, const Arg4& arg4)
		{
			return kerbal::memory::unique_ptr<Tp>(new Tp(arg0, arg1, arg2, arg3, arg4)); 
		}

#	else

		template <typename Tp, typename ... Args>
		kerbal::memory::unique_ptr<Tp>
		make_unique(Args&& ... args)
		{
			return kerbal::memory::unique_ptr<Tp>(new Tp(kerbal::utility::forward<Args>(args)...));
		}

#	endif

//		template <typename Tp, typename Deleter>
//		class guard<Tp[], Deleter>: kerbal::utility::noncopyable
//		{
//			public:
//				typedef Tp element_type [];
//				typedef Tp* pointer;
//				typedef Deleter deleter_type;
//
//			protected:
//				pointer ptr;
//				Deleter deleter;
//
//			public:
//				guard(pointer ptr) KERBAL_CONDITIONAL_NOEXCEPT(std::is_trivially_default_constructible<deleter_type>::value) :
//					ptr(ptr), deleter()
//				{
//				}
//
//				guard(pointer ptr, const deleter_type& deleter) KERBAL_CONDITIONAL_NOEXCEPT(std::is_trivially_copy_constructible<deleter_type>::value) :
//					ptr(ptr), deleter(deleter)
//				{
//				}
//
//#			if __cplusplus >= 201103L
//
//				guard(pointer ptr, deleter_type&& deleter) KERBAL_CONDITIONAL_NOEXCEPT(std::is_trivially_move_constructible<deleter_type>::value) :
//					ptr(ptr), deleter(kerbal::compatibility::move(deleter))
//				{
//				}
//
//#			endif
//
//				~guard() KERBAL_CONDITIONAL_NOEXCEPT(noexcept(this->reset()))
//				{
//					this->reset();
//				}
//
//				pointer release() KERBAL_NOEXCEPT
//				{
//					pointer p = this->ptr;
//					this->ptr = NULL;
//					return p;
//				}
//
//				void reset() KERBAL_CONDITIONAL_NOEXCEPT(noexcept(this->deleter(this->ptr)))
//				{
//					this->deleter(this->ptr);
//					this->ptr = NULL;
//				}
//
//		};

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_UNIQUE_PTR_HPP
