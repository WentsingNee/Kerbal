/**
 * @file       raw_storage.hpp
 * @brief
 * @date       2019-4-19
 * @author     peter
 * @copyright
 *      peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_RAW_STORAGE_HPP
#define KERBAL_MEMORY_RAW_STORAGE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/method_overload_tag.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/uninitialized.hpp>
#include <kerbal/memory/uninitialized_using_allocator.hpp>
#include <kerbal/utility/declval.hpp>
#include <kerbal/utility/in_place.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

#include <cstddef>

#if __cplusplus >= 201103L
#	include <kerbal/memory/detail/raw_storage/raw_storage_base.cxx11.hpp>
#else
#	include <kerbal/memory/detail/raw_storage/raw_storage_base.cxx98.hpp>
#endif


namespace kerbal
{

	namespace memory
	{



		template <typename T>
		class _K_rawst_agent;

		template <typename T>
		class _K_rawst_agent:
				public kerbal::memory::detail::_K_rawst_base<T>
		{
			private:
				typedef _K_rawst_agent this_type;
				typedef kerbal::memory::detail::_K_rawst_base<T> super;

			protected:
				typedef typename super::value_type					value_type;
				typedef typename super::const_type					const_type;
				typedef typename super::reference					reference;
				typedef typename super::const_reference				const_reference;
				typedef typename super::pointer						pointer;
				typedef typename super::const_pointer				const_pointer;

#		if __cplusplus >= 201103L
				typedef typename super::rvalue_reference			rvalue_reference;
				typedef typename super::const_rvalue_reference		const_rvalue_reference;
#		endif

			protected:

#		if __cplusplus < 201103L

#			define EMPTY
#			define LEFT_JOIN_COMMA(exp) , exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#			define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				explicit _K_rawst_agent(kerbal::utility::in_place_t in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) : \
						super(in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)) \
				{ \
				}

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#			undef EMPTY
#			undef LEFT_JOIN_COMMA
#			undef THEAD_NOT_EMPTY
#			undef TARGS_DECL
#			undef ARGS_DECL
#			undef ARGS_USE
#			undef FBODY

#		else
				using super::super;
#		endif

				KERBAL_CONSTEXPR
				_K_rawst_agent() KERBAL_NOEXCEPT
				{
				}

			public:

#		if __cplusplus < 201103L

#			define EMPTY
#			define REMAINF(exp) exp
#			define LEFT_JOIN_COMMA(exp) , exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#			define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				void construct(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
				{ \
					kerbal::memory::construct_at(this->raw_pointer() KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				}

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#			undef EMPTY
#			undef REMAINF
#			undef LEFT_JOIN_COMMA
#			undef THEAD_NOT_EMPTY
#			undef TARGS_DECL
#			undef ARGS_DECL
#			undef ARGS_USE
#			undef FBODY

#		else

				template <typename ... Args>
				KERBAL_CONSTEXPR14
				void construct(Args&& ... args)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(
								kerbal::memory::construct_at(
									kerbal::utility::declthis<this_type>()->raw_pointer(),
									kerbal::utility::forward<Args>(args)...
								)
							)
						)
				{
					kerbal::memory::construct_at(this->raw_pointer(), kerbal::utility::forward<Args>(args)...);
				}

#		endif


#		if __cplusplus < 201103L

#			define EMPTY
#			define LEFT_JOIN_COMMA(exp) , exp
#			define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#			define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				template <typename Alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
				void construct_using_allocator(Alloc & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
				{ \
					kerbal::memory::construct_at_using_allocator(alloc, this->raw_pointer() KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				}

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#			undef EMPTY
#			undef LEFT_JOIN_COMMA
#			undef TARGS_DECL
#			undef ARGS_DECL
#			undef ARGS_USE
#			undef FBODY

#		else

				template <typename Alloc, typename ... Args>
				KERBAL_CONSTEXPR14
				void construct_using_allocator(Alloc & alloc, Args&& ... args)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(
								kerbal::memory::construct_at_using_allocator(
									alloc,
									kerbal::utility::declthis<this_type>()->raw_pointer(),
									kerbal::utility::forward<Args>(args)...
								)
							)
						)
				{
					kerbal::memory::construct_at_using_allocator(alloc, this->raw_pointer(), kerbal::utility::forward<Args>(args)...);
				}

#		endif

		};

/*
		template <typename T, std::size_t N>
		class _K_rawst_agent<T[N]>:
				public kerbal::memory::detail::_K_rawst_base<T[N]>
		{
			private:
				typedef _K_rawst_agent this_type;
				typedef kerbal::memory::detail::_K_rawst_base<T[N]> super;

			protected:
				typedef typename super::value_type					value_type;
				typedef typename super::const_type					const_type;
				typedef typename super::reference					reference;
				typedef typename super::const_reference				const_reference;
				typedef typename super::pointer						pointer;
				typedef typename super::const_pointer				const_pointer;

#		if __cplusplus >= 201103L
				typedef typename super::rvalue_reference			rvalue_reference;
				typedef typename super::const_rvalue_reference		const_rvalue_reference;
#		endif

			protected:

#		if __cplusplus < 201103L

				explicit _K_rawst_agent(kerbal::utility::in_place_t in_place) :
						super(in_place)
				{
				}

				explicit _K_rawst_agent(kerbal::utility::in_place_t in_place, const_reference src) :
						super(in_place, src)
				{
				}

				template <typename Up>
				explicit _K_rawst_agent(kerbal::utility::in_place_t in_place, const Up (&src)[N]) :
						super(in_place, src)
				{
				}

#		else
				using super::super;
#		endif

				KERBAL_CONSTEXPR
				_K_rawst_agent() KERBAL_NOEXCEPT
				{
				}

			public:

				KERBAL_CONSTEXPR14
				void construct()
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::construct_at(kerbal::utility::declthis<this_type>()->raw_pointer()))
						)
				{
					kerbal::memory::construct_at(this->raw_pointer());
				}

				template <typename Alloc>
				KERBAL_CONSTEXPR14
				void construct_using_allocator(Alloc & alloc)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::construct_at_using_allocator(alloc, kerbal::utility::declthis<this_type>()->raw_pointer()))
						)
				{
					kerbal::memory::construct_at_using_allocator(alloc, this->raw_pointer());
				}

				KERBAL_CONSTEXPR14
				void construct(const_reference src)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::construct_at(kerbal::utility::declthis<this_type>()->raw_pointer(), src))
						)
				{
					kerbal::memory::construct_at(this->raw_pointer(), src);
				}

				template <typename Alloc>
				KERBAL_CONSTEXPR14
				void construct_using_allocator(Alloc & alloc, const_reference src)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::construct_at_using_allocator(alloc, kerbal::utility::declthis<this_type>()->raw_pointer(), src))
						)
				{
					kerbal::memory::construct_at_using_allocator(alloc, this->raw_pointer(), src);
				}

				template <typename Up>
				KERBAL_CONSTEXPR14
				void construct(const Up (&src)[N])
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::construct_at(kerbal::utility::declthis<this_type>()->raw_pointer(), src))
						)
				{
					kerbal::memory::construct_at(this->raw_pointer(), src);
				}

				template <typename Alloc, typename Up>
				KERBAL_CONSTEXPR14
				void construct_using_allocator(Alloc & alloc, const Up (&src)[N])
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::construct_at_using_allocator(alloc, kerbal::utility::declthis<this_type>()->raw_pointer(), src))
						)
				{
					kerbal::memory::construct_at_using_allocator(alloc, this->raw_pointer(), src);
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				void construct(rvalue_reference src)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::construct_at(
								kerbal::utility::declthis<this_type>()->raw_pointer(),
								kerbal::compatibility::move(src)
							))
						)
				{
					kerbal::memory::construct_at(this->raw_pointer(), kerbal::compatibility::move(src));
				}

				template <typename Alloc>
				KERBAL_CONSTEXPR14
				void construct_using_allocator(Alloc & alloc, rvalue_reference src)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::construct_at_using_allocator(
								alloc,
								kerbal::utility::declthis<this_type>()->raw_pointer(),
								kerbal::compatibility::move(src)
							))
						)
				{
					kerbal::memory::construct_at_using_allocator(alloc, this->raw_pointer(), kerbal::compatibility::move(src));
				}

				template <typename Up>
				KERBAL_CONSTEXPR14
				void construct(Up (&&src)[N])
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::construct_at(
								kerbal::utility::declthis<this_type>()->raw_pointer(),
								kerbal::compatibility::move(src)
							))
						)
				{
					kerbal::memory::construct_at(this->raw_pointer(), kerbal::compatibility::move(src));
				}

				template <typename Alloc, typename Up>
				KERBAL_CONSTEXPR14
				void construct_using_allocator(Alloc & alloc, Up (&&src)[N])
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::construct_at_using_allocator(
								alloc,
								kerbal::utility::declthis<this_type>()->raw_pointer(),
								kerbal::compatibility::move(src)
							))
						)
				{
					kerbal::memory::construct_at_using_allocator(alloc, this->raw_pointer(), kerbal::compatibility::move(src));
				}

#		endif

		};
*/


		template <typename T>
		class raw_storage: public kerbal::memory::_K_rawst_agent<T>
		{
			private:
				typedef raw_storage this_type;
				typedef kerbal::memory::_K_rawst_agent<T> super;

			public:
				typedef typename super::value_type					value_type;
				typedef typename super::const_type					const_type;
				typedef typename super::reference					reference;
				typedef typename super::const_reference				const_reference;
				typedef typename super::pointer						pointer;
				typedef typename super::const_pointer				const_pointer;

#		if __cplusplus >= 201103L
				typedef typename super::rvalue_reference			rvalue_reference;
				typedef typename super::const_rvalue_reference		const_rvalue_reference;
#		endif

			public:

#		if __cplusplus < 201103L

#			define EMPTY
#			define REMAINF(exp) exp
#			define LEFT_JOIN_COMMA(exp) , exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#			define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				explicit raw_storage(kerbal::utility::in_place_t in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) : \
						super(in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)) \
				{ \
				}

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#			undef EMPTY
#			undef REMAINF
#			undef LEFT_JOIN_COMMA
#			undef THEAD_NOT_EMPTY
#			undef TARGS_DECL
#			undef ARGS_DECL
#			undef ARGS_USE
#			undef FBODY

#		else
				using super::super;
#		endif

				KERBAL_CONSTEXPR
				raw_storage() KERBAL_NOEXCEPT
				{
				}

				KERBAL_CONSTEXPR14
				void default_construct()
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::default_construct_at(kerbal::utility::declthis<this_type>()->raw_pointer()))
						)
				{
					kerbal::memory::default_construct_at(this->raw_pointer());
				}

				template <typename Alloc>
				KERBAL_CONSTEXPR14
				void destroy_using_allocator(Alloc & alloc)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::destroy_at_using_allocator(alloc, kerbal::utility::declthis<this_type>()->raw_pointer()))
						)
				{
					kerbal::memory::destroy_at_using_allocator(alloc, this->raw_pointer());
				}

		};

	} // namespace memory

} // namespace kerbal


#endif // KERBAL_MEMORY_RAW_STORAGE_HPP
