/**
 * @file       static_queue.hpp
 * @brief
 * @date       2018-5-17
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_STATIC_QUEUE_HPP
#define KERBAL_CONTAINER_STATIC_QUEUE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

#include <cstddef>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif

#include <kerbal/container/detail/static_queue_base.hpp>

namespace kerbal
{

	namespace container
	{

		template <typename Tp, size_t N>
		class static_queue: protected kerbal::container::detail::static_queue_base<Tp, N>
		{
			private:
				typedef kerbal::container::detail::static_queue_base<Tp, N> super;

			public:
				typedef Tp						value_type;
				typedef const Tp				const_type;
				typedef Tp&						reference;
				typedef const Tp&				const_reference;

#		if __cplusplus >= 201103L
				typedef value_type&&			rvalue_reference;
				typedef const value_type&&		const_rvalue_reference;
#		endif

				typedef size_t					size_type;

			public:
				KERBAL_CONSTEXPR
				static_queue() KERBAL_NOEXCEPT
						: super()
				{
				}

				KERBAL_CONSTEXPR14
				static_queue(const static_queue & src)
						: super()
				{
					for (size_type j = src.ibegin; j != src.iend; j = src.next(j)) {
						this->push(src.storage[j].raw_value());
					}
				}

#			if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				static_queue(static_queue && src)
						: super()
				{
					for (size_type j = src.ibegin; j != src.iend; j = src.next(j)) {
						this->push(kerbal::compatibility::move(src.storage[j].raw_value()));
					}
				}

#			endif

				template <typename ForwardIterator>
				KERBAL_CONSTEXPR14
				static_queue(ForwardIterator first, ForwardIterator last)
						: super()
				{
					while (static_cast<bool>(first != last) && this->iend != N) {
						this->push(*first);
						++first;
					}
				}

#			if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				static_queue(std::initializer_list<value_type> src)
						: static_queue(src.begin(), src.end())
				{
				}

#			endif

				KERBAL_CONSTEXPR14
				static_queue& operator=(const static_queue & src)
				{
					this->assign(src);
					return *this;
				}

#			if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				static_queue& operator=(static_queue && src)
				{
					this->assign(kerbal::compatibility::move(src));
					return *this;
				}

#			endif

				KERBAL_CONSTEXPR14
				void assign(const static_queue & src)
				{
					this->clear();
					for (size_type j = src.ibegin; j != src.iend; j = src.next(j)) {
						this->push(this->storage[j].raw_value());
					}
				}

#			if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				void assign(static_queue && src)
				{
					this->clear();
					for (size_type j = src.ibegin; j != src.iend; j = src.next(j)) {
						this->push(kerbal::compatibility::move(this->storage[j].raw_value()));
					}
				}

#			endif

				KERBAL_CONSTEXPR14
				void push(const_reference val)
				{
					this->storage[this->iend].construct(val);
					this->iend = this->next(this->iend);
				}


#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				void push(rvalue_reference val)
				{
					this->storage[this->iend].construct(kerbal::compatibility::move(val));
					this->iend = this->next(this->iend);
				}

#		endif

#		if __cplusplus >= 201103L

				template <typename ... Args>
				KERBAL_CONSTEXPR14
				reference emplace(Args&& ... args)
				{
					this->storage[this->iend].construct(kerbal::utility::forward<Args>(args)...);
					size_type iback = this->iend;
					this->iend = this->next(this->iend);
					return this->storage[iback];
				}

#		else

				reference emplace()
				{
					this->storage[this->iend].construct();
					size_type iback = this->iend;
					this->iend = this->next(this->iend);
					return this->storage[iback];
				}

				template <typename Arg0>
				reference emplace(const Arg0& arg0)
				{
					this->storage[this->iend].construct(arg0);
					size_type iback = this->iend;
					this->iend = this->next(this->iend);
					return this->storage[iback];
				}

				template <typename Arg0, typename Arg1>
				reference emplace(const Arg0& arg0, const Arg1& arg1)
				{
					this->storage[this->iend].construct(arg0, arg1);
					size_type iback = this->iend;
					this->iend = this->next(this->iend);
					return this->storage[iback];
				}

				template <typename Arg0, typename Arg1, typename Arg2>
				reference emplace(const Arg0& arg0, const Arg1& arg1, const Arg2& arg2)
				{
					this->storage[this->iend].construct(arg0, arg1, arg2);
					size_type iback = this->iend;
					this->iend = this->next(this->iend);
					return this->storage[iback];
				}

#		endif

				KERBAL_CONSTEXPR14
				void pop()
				{
					this->storage[this->ibegin].destroy();
					this->ibegin = this->next(this->ibegin);
				}

				KERBAL_CONSTEXPR14
				void clear()
				{
					this->super::clear();
				}

				KERBAL_CONSTEXPR
				size_type size() const KERBAL_NOEXCEPT
				{
					return this->ibegin <= this->iend ?
							this->iend - this->ibegin :
							N + 1 - (this->ibegin - this->iend);
				}

				KERBAL_CONSTEXPR
				bool empty() const KERBAL_NOEXCEPT
				{
					return this->ibegin == this->iend;
				}

				KERBAL_CONSTEXPR
				bool full() const KERBAL_NOEXCEPT
				{
					return this->next(this->iend) == this->ibegin;
				}

				KERBAL_CONSTEXPR14
				const_reference front() const KERBAL_NOEXCEPT
				{
					return this->storage[this->ibegin].raw_value();
				}

				KERBAL_CONSTEXPR14
				reference back() KERBAL_NOEXCEPT
				{
					return this->storage[this->prev(this->iend)].raw_value();
				}

				KERBAL_CONSTEXPR14
				const_reference back() const KERBAL_NOEXCEPT
				{
					return this->storage[this->prev(this->iend)].raw_value();
				}

				void swap(static_queue& with);

		};

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_STATIC_QUEUE_HPP
