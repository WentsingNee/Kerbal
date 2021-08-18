/**
 * @file       assign_list.hpp
 * @brief
 * @date       2019-8-2
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ASSIGN_ASSIGN_LIST_HPP
#define KERBAL_ASSIGN_ASSIGN_LIST_HPP

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/detail/vector_base.hpp>
#include <kerbal/utility/member_compress_helper.hpp>

#include <memory>


namespace kerbal
{

	namespace assign
	{

		template <typename Tp>
		class assign_list :
				private kerbal::utility::member_compress_helper<std::allocator<Tp> >
		{
			private:
				typedef kerbal::utility::member_compress_helper<std::allocator<Tp> > super;
				typedef kerbal::container::detail::vector_allocator_unrelated<Tp> c;

			public:
				typedef Tp									value_type;
				typedef Tp&									reference;
				typedef const Tp&							const_reference;
				typedef typename c::iterator				iterator;
				typedef typename c::const_iterator			const_iterator;
				typedef std::allocator<Tp>					allocator_type;

			private:
				c v;

				allocator_type & alloc() KERBAL_NOEXCEPT
				{
					return super::member();
				}

			public:
				assign_list()
				{
					v.reserve_using_allocator(this->alloc(), 20);
				}

				~assign_list() KERBAL_NOEXCEPT
				{
					v.template destroy_using_allocator(this->alloc());
				}

				assign_list& operator,(const_reference val)
				{
					v.push_back_using_allocator(this->alloc(), val);
					return *this;
				}

				iterator begin()
				{
					return v.begin();
				}

				iterator end()
				{
					return v.end();
				}

				const_iterator begin() const
				{
					return v.begin();
				}

				const_iterator end() const
				{
					return v.end();
				}

				const_iterator cbegin() const
				{
					return v.begin();
				}

				const_iterator cend() const
				{
					return v.end();
				}
		};

		template <>
		class assign_list<void>
		{
			public:

				template <typename Tp>
				assign_list<Tp> operator,(const Tp & val)
				{
					assign_list<Tp> list;
					list, val;
					return list;
				}

		};

		inline
		assign_list<void>
		make_assign_list()
		{
			return assign_list<void>();
		};

	} // namespace assign

} // namespace kerbal

#endif // KERBAL_ASSIGN_ASSIGN_LIST_HPP
