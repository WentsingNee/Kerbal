/**
 * @file       nonmember_container_access.hpp
 * @brief      
 * @date       2019-10-6
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_NONMEMBER_CONTAINER_ACCESS_HPP_
#define KERBAL_CONTAINER_NONMEMBER_CONTAINER_ACCESS_HPP_

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/reverse_iterator.hpp>

#include <cstddef>

namespace kerbal
{

	namespace container
	{

#	if __cplusplus >= 201103L

		template <typename Container>
		KERBAL_CONSTEXPR
		auto begin(Container & container)
					KERBAL_CONDITIONAL_NOEXCEPT(noexcept(container.begin()))
					-> decltype(container.begin())
		{
			return container.begin();
		}

		template <typename Container>
		KERBAL_CONSTEXPR
		auto begin(const Container & container)
					KERBAL_CONDITIONAL_NOEXCEPT(noexcept(container.begin()))
					-> decltype(container.begin())
		{
			return container.begin();
		}

		template <typename Container>
		KERBAL_CONSTEXPR
		auto cbegin(const Container & container)
					KERBAL_CONDITIONAL_NOEXCEPT(noexcept(container.cbegin()))
					-> decltype(container.cbegin())
		{
			return container.cbegin();
		}

		template <typename Container>
		KERBAL_CONSTEXPR
		auto end(Container & container)
					KERBAL_CONDITIONAL_NOEXCEPT(noexcept(container.end()))
					-> decltype(container.end())
		{
			return container.end();
		}

		template <typename Container>
		KERBAL_CONSTEXPR
		auto end(const Container & container)
					KERBAL_CONDITIONAL_NOEXCEPT(noexcept(container.end()))
					-> decltype(container.end())
		{
			return container.end();
		}

		template <typename Container>
		KERBAL_CONSTEXPR
		auto cend(const Container & container)
					KERBAL_CONDITIONAL_NOEXCEPT(noexcept(container.cend()))
					-> decltype(container.cend())
		{
			return container.cend();
		}

		template <typename Container>
		KERBAL_CONSTEXPR
		auto rbegin(Container & container)
					KERBAL_CONDITIONAL_NOEXCEPT(noexcept(container.rbegin()))
					-> decltype(container.rbegin())
		{
			return container.rbegin();
		}

		template <typename Container>
		KERBAL_CONSTEXPR
		auto rbegin(const Container & container)
					KERBAL_CONDITIONAL_NOEXCEPT(noexcept(container.rbegin()))
					-> decltype(container.rbegin())
		{
			return container.rbegin();
		}

		template <typename Container>
		KERBAL_CONSTEXPR
		auto crbegin(const Container & container)
					KERBAL_CONDITIONAL_NOEXCEPT(noexcept(container.crbegin()))
					-> decltype(container.crbegin())
		{
			return container.crbegin();
		}

		template <typename Container>
		KERBAL_CONSTEXPR
		auto rend(Container & container)
					KERBAL_CONDITIONAL_NOEXCEPT(noexcept(container.rend()))
					-> decltype(container.rend())
		{
			return container.rend();
		}

		template <typename Container>
		KERBAL_CONSTEXPR
		auto rend(const Container & container)
					KERBAL_CONDITIONAL_NOEXCEPT(noexcept(container.rend()))
					-> decltype(container.rend())
		{
			return container.rend();
		}

		template <typename Container>
		KERBAL_CONSTEXPR
		auto crend(const Container & container)
					KERBAL_CONDITIONAL_NOEXCEPT(noexcept(container.crend()))
					-> decltype(container.crend())
		{
			return container.crend();
		}

		template <typename Container>
		KERBAL_CONSTEXPR
		auto size(const Container & container)
					KERBAL_CONDITIONAL_NOEXCEPT(noexcept(container.size()))
					-> decltype(container.size())
		{
			return container.size();
		}

		template <typename Container>
		KERBAL_CONSTEXPR
		auto empty(const Container & container)
					KERBAL_CONDITIONAL_NOEXCEPT(noexcept(container.empty()))
					-> decltype(container.empty())
		{
			return container.empty();
		}

#	else

		template <typename Container>
		typename Container::iterator
		begin(Container & container)
		{
			return container.begin();
		}

		template <typename Container>
		typename Container::const_iterator
		begin(const Container & container)
		{
			return container.begin();
		}

		template <typename Container>
		typename Container::const_iterator
		cbegin(const Container & container)
		{
			return container.begin();
		}

		template <typename Container>
		typename Container::iterator
		end(Container & container)
		{
			return container.end();
		}

		template <typename Container>
		typename Container::const_iterator
		end(const Container & container)
		{
			return container.end();
		}

		template <typename Container>
		typename Container::const_iterator
		cend(const Container & container)
		{
			return container.end();
		}

		template <typename Container>
		typename Container::reverse_iterator
		rbegin(Container & container)
		{
			return container.rbegin();
		}

		template <typename Container>
		typename Container::const_reverse_iterator
		rbegin(const Container & container)
		{
			return container.rbegin();
		}

		template <typename Container>
		typename Container::const_reverse_iterator
		crbegin(const Container & container)
		{
			return container.rbegin();
		}

		template <typename Container>
		typename Container::reverse_iterator
		rend(Container & container)
		{
			return container.rend();
		}

		template <typename Container>
		typename Container::const_reverse_iterator
		rend(const Container & container)
		{
			return container.rend();
		}

		template <typename Container>
		typename Container::const_reverse_iterator
		crend(const Container & container)
		{
			return container.rend();
		}

		template <typename Container>
		typename Container::size_type
		size(const Container & container)
		{
			return container.size();
		}

		template <typename Container>
		bool empty(const Container & container)
		{
			return container.empty();
		}

#	endif // __cplusplus >= 201103L

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR
		Tp* begin(Tp (&arr)[N]) KERBAL_NOEXCEPT
		{
			return arr;
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR
		const Tp* cbegin(Tp (&arr)[N]) KERBAL_NOEXCEPT
		{
			return arr;
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR
		Tp* end(Tp (&arr)[N]) KERBAL_NOEXCEPT
		{
			return arr + N;
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR
		const Tp* cend(Tp (&arr)[N]) KERBAL_NOEXCEPT
		{
			return arr + N;
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR
		kerbal::iterator::reverse_iterator<Tp*>
		rbegin(Tp (&arr)[N]) KERBAL_NOEXCEPT
		{
			return kerbal::iterator::reverse_iterator<Tp*>(arr + N);
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR
		kerbal::iterator::reverse_iterator<const Tp*>
		crbegin(Tp (&arr)[N]) KERBAL_NOEXCEPT
		{
			return kerbal::iterator::reverse_iterator<const Tp*>(arr + N);
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR
		kerbal::iterator::reverse_iterator<Tp*>
		rend(Tp (&arr)[N]) KERBAL_NOEXCEPT
		{
			return kerbal::iterator::reverse_iterator<Tp*>(arr);
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR
		kerbal::iterator::reverse_iterator<const Tp*>
		crend(Tp (&arr)[N]) KERBAL_NOEXCEPT
		{
			return kerbal::iterator::reverse_iterator<const Tp*>(arr);
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR
		size_t size(const Tp (&)[N]) KERBAL_NOEXCEPT
		{
			return N;
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR
		bool empty(const Tp (&)[N]) KERBAL_NOEXCEPT
		{
			return false;
		}

	} // namespace container

} // namespace kerbal

#endif /* KERBAL_CONTAINER_NONMEMBER_CONTAINER_ACCESS_HPP_ */
