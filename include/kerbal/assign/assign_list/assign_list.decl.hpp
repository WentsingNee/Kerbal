/**
 * @file       assign_list.decl.hpp
 * @brief
 * @date       2019-8-2
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ASSIGN_ASSIGN_LIST_ASSIGN_LIST_DECL_HPP
#define KERBAL_ASSIGN_ASSIGN_LIST_ASSIGN_LIST_DECL_HPP

#include <kerbal/assign/assign_list/assign_list.fwd.hpp>
#include <kerbal/container/detail/vector_base/vector_base.decl.hpp>

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/utility/member_compress_helper.hpp>

#include <memory>


namespace kerbal
{

	namespace assign
	{

		template <typename T>
		class assign_list :
			private kerbal::utility::member_compress_helper<std::allocator<T> >
		{
			private:
				typedef kerbal::utility::member_compress_helper<std::allocator<T> > super;
				typedef kerbal::container::detail::vector_type_only<T> c;

			public:
				typedef T									value_type;
				typedef T &									reference;
				typedef const T &							const_reference;
				typedef typename c::iterator				iterator;
				typedef typename c::const_iterator			const_iterator;
				typedef std::allocator<T>					allocator_type;

			private:
				c v;

				allocator_type & alloc() KERBAL_NOEXCEPT
				{
					return super::member();
				}

			public:
				assign_list();

				~assign_list() KERBAL_NOEXCEPT;

				assign_list & operator,(const_reference val);

				iterator begin();

				iterator end();

				const_iterator begin() const;

				const_iterator end() const;

				const_iterator cbegin() const;

				const_iterator cend() const;
		};

		template <>
		class assign_list<void>
		{
			public:

				template <typename T>
				assign_list<T> operator,(const T & val)
				{
					assign_list<T> list;
					list, val;
					return list;
				}

		};

		inline
		assign_list<void>
		make_assign_list()
		{
			return assign_list<void>();
		}

	} // namespace assign

} // namespace kerbal

#endif // KERBAL_ASSIGN_ASSIGN_LIST_ASSIGN_LIST_DECL_HPP
