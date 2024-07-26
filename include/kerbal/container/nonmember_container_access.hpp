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

#ifndef KERBAL_CONTAINER_NONMEMBER_CONTAINER_ACCESS_HPP
#define KERBAL_CONTAINER_NONMEMBER_CONTAINER_ACCESS_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/reverse_iterator.hpp>

#include <cstddef>


namespace kerbal
{

	namespace container
	{

		// begin

		KERBAL_MODULE_EXPORT
		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR
		T * begin(T (&arr)[N]) KERBAL_NOEXCEPT
		{
			return arr;
		}

#	if __cplusplus >= 201103L

		KERBAL_MODULE_EXPORT
		template <typename Container>
		KERBAL_CONSTEXPR
		auto begin(Container & container)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(container.begin()))
			-> decltype(container.begin())
		{
			return container.begin();
		}

		KERBAL_MODULE_EXPORT
		template <typename Container>
		KERBAL_CONSTEXPR
		auto begin(const Container & container)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(container.begin()))
			-> decltype(container.begin())
		{
			return container.begin();
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

#	endif // __cplusplus >= 201103L



		// cbegin

#	if __cplusplus >= 201103L

		KERBAL_MODULE_EXPORT
		template <typename Container>
		KERBAL_CONSTEXPR
		auto cbegin(const Container & container)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(kerbal::container::begin(container)))
			-> decltype(kerbal::container::begin(container))
		{
			return kerbal::container::begin(container);
		}

#	else

		template <typename T, std::size_t N>
		const T * cbegin(T (&arr)[N]) KERBAL_NOEXCEPT
		{
			return arr;
		}

		template <typename Container>
		typename Container::const_iterator
		cbegin(const Container & container)
		{
			return container.begin();
		}

#	endif // __cplusplus >= 201103L



		// end

		KERBAL_MODULE_EXPORT
		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR
		T * end(T (&arr)[N]) KERBAL_NOEXCEPT
		{
			return arr + N;
		}

#	if __cplusplus >= 201103L

		KERBAL_MODULE_EXPORT
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

#	else

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

#	endif // __cplusplus >= 201103L



		// cend

#	if __cplusplus >= 201103L

		KERBAL_MODULE_EXPORT
		template <typename Container>
		KERBAL_CONSTEXPR
		auto cend(const Container & container)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(kerbal::container::end(container)))
			-> decltype(kerbal::container::end(container))
		{
			return kerbal::container::end(container);
		}

#	else

		template <typename T, std::size_t N>
		const T * cend(T (&arr)[N]) KERBAL_NOEXCEPT
		{
			return arr + N;
		}

		template <typename Container>
		typename Container::const_iterator
		cend(const Container & container)
		{
			return container.end();
		}

#	endif // __cplusplus >= 201103L



		// rbegin

		KERBAL_MODULE_EXPORT
		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR
		kerbal::iterator::reverse_iterator<T *, false>
		rbegin(T (&arr)[N]) KERBAL_NOEXCEPT
		{
			return kerbal::iterator::reverse_iterator<T *, false>(arr + N);
		}

#	if __cplusplus >= 201103L

		KERBAL_MODULE_EXPORT
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

#	else

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

#	endif // __cplusplus >= 201103L



		// crbegin

#	if __cplusplus >= 201103L

		KERBAL_MODULE_EXPORT
		template <typename Container>
		KERBAL_CONSTEXPR
		auto crbegin(const Container & container)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(kerbal::container::rbegin(container)))
			-> decltype(kerbal::container::rbegin(container))
		{
			return kerbal::container::rbegin(container);
		}

#	else

		template <typename T, std::size_t N>
		kerbal::iterator::reverse_iterator<const T *, false>
		crbegin(T (&arr)[N]) KERBAL_NOEXCEPT
		{
			return kerbal::iterator::reverse_iterator<const T *, false>(arr + N);
		}

		template <typename Container>
		typename Container::const_reverse_iterator
		crbegin(const Container & container)
		{
			return container.rbegin();
		}

#	endif // __cplusplus >= 201103L



		// rend

		KERBAL_MODULE_EXPORT
		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR
		kerbal::iterator::reverse_iterator<T *, false>
		rend(T (&arr)[N]) KERBAL_NOEXCEPT
		{
			return kerbal::iterator::reverse_iterator<T *, false>(arr);
		}

#	if __cplusplus >= 201103L

		KERBAL_MODULE_EXPORT
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

#	else

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

#	endif // __cplusplus >= 201103L



		// crend

#	if __cplusplus >= 201103L

		KERBAL_MODULE_EXPORT
		template <typename Container>
		KERBAL_CONSTEXPR
		auto crend(const Container & container)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(kerbal::container::rend(container)))
			-> decltype(kerbal::container::rend(container))
		{
			return kerbal::container::rend(container);
		}

#	else

		template <typename T, std::size_t N>
		kerbal::iterator::reverse_iterator<const T *, false>
		crend(T (&arr)[N]) KERBAL_NOEXCEPT
		{
			return kerbal::iterator::reverse_iterator<const T *, false>(arr);
		}

		template <typename Container>
		typename Container::const_reverse_iterator
		crend(const Container & container)
		{
			return container.rend();
		}

#	endif // __cplusplus >= 201103L



		// size

		KERBAL_MODULE_EXPORT
		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR
		std::size_t size(const T (&)[N]) KERBAL_NOEXCEPT
		{
			return N;
		}

#	if __cplusplus >= 201103L

		KERBAL_MODULE_EXPORT
		template <typename Container>
		KERBAL_CONSTEXPR
		auto size(const Container & container)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(container.size()))
			-> decltype(container.size())
		{
			return container.size();
		}

#	else

		template <typename Container>
		typename Container::size_type
		size(const Container & container)
		{
			return container.size();
		}

#	endif // __cplusplus >= 201103L



		// empty

		KERBAL_MODULE_EXPORT
		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR
		bool empty(const T (&)[N]) KERBAL_NOEXCEPT
		{
			return false;
		}

#	if __cplusplus >= 201103L

		KERBAL_MODULE_EXPORT
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
		bool empty(const Container & container)
		{
			return container.empty();
		}

#	endif // __cplusplus >= 201103L



		// nth

		KERBAL_MODULE_EXPORT
		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR14
		T * nth(T (& arr)[N], std::size_t index) KERBAL_NOEXCEPT
		{
			return arr + index;
		}

#	if __cplusplus >= 201103L

		KERBAL_MODULE_EXPORT
		template <typename Container>
		KERBAL_CONSTEXPR14
		auto nth(Container & container, typename Container::size_type index)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(kerbal::iterator::next(kerbal::container::begin(container), index)))
			-> decltype(kerbal::iterator::next(kerbal::container::begin(container), index))
		{
			return kerbal::iterator::next(kerbal::container::begin(container), index);
		}

		KERBAL_MODULE_EXPORT
		template <typename Container>
		KERBAL_CONSTEXPR14
		auto nth(const Container & container, typename Container::size_type index)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(kerbal::iterator::next(kerbal::container::cbegin(container), index)))
			-> decltype(kerbal::iterator::next(kerbal::container::cbegin(container), index))
		{
			return kerbal::iterator::next(kerbal::container::cbegin(container), index);
		}

#	else

		template <typename Container>
		typename Container::iterator
		nth(Container & container, typename Container::size_type index)
		{
			return kerbal::iterator::next(kerbal::container::begin(container), index);
		}

		template <typename Container>
		typename Container::const_iterator
		nth(const Container & container, typename Container::size_type index)
		{
			return kerbal::iterator::next(kerbal::container::cbegin(container), index);
		}

#	endif // __cplusplus >= 201103L



		// index_of

		KERBAL_MODULE_EXPORT
		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR14
		std::size_t index_of(T (&arr)[N], T * it) KERBAL_NOEXCEPT
		{
			return it - arr;
		}

		KERBAL_MODULE_EXPORT
		template <typename T, std::size_t N>
		KERBAL_CONSTEXPR14
		std::size_t index_of(const T (&arr)[N], const T * it) KERBAL_NOEXCEPT
		{
			return it - arr;
		}

#	if __cplusplus >= 201103L

		KERBAL_MODULE_EXPORT
		template <typename Container>
		KERBAL_CONSTEXPR14
		auto index_of(Container & container, typename Container::iterator it)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(kerbal::iterator::distance(kerbal::container::begin(container), it)))
			-> decltype(kerbal::iterator::distance(kerbal::container::begin(container), it))
		{
			return kerbal::iterator::distance(kerbal::container::begin(container), it);
		}

		KERBAL_MODULE_EXPORT
		template <typename Container>
		KERBAL_CONSTEXPR14
		auto index_of(const Container & container, typename Container::const_iterator it)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(kerbal::iterator::distance(kerbal::container::cbegin(container), it)))
			-> decltype(kerbal::iterator::distance(kerbal::container::cbegin(container), it))
		{
			return kerbal::iterator::distance(kerbal::container::cbegin(container), it);
		}

#	else

		template <typename Container>
		typename Container::size_type
		index_of(Container & container, typename Container::iterator it)
		{
			return kerbal::iterator::distance(kerbal::container::begin(container), it);
		}

		template <typename Container>
		typename Container::size_type
		index_of(const Container & container, typename Container::const_iterator it)
		{
			return kerbal::iterator::distance(kerbal::container::cbegin(container), it);
		}

#	endif // __cplusplus >= 201103L

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_NONMEMBER_CONTAINER_ACCESS_HPP
