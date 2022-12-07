/**
 * @file       any_storage.hpp
 * @brief
 * @date       2022-05-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_ANY_STORAGE_HPP
#define KERBAL_MEMORY_ANY_STORAGE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/type_traits/aligned_storage.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/remove_const.hpp>
#include <kerbal/utility/in_place.hpp>
#include <kerbal/utility/member_compress_helper.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus > 201703L
#	include <kerbal/compatibility/is_constant_evaluated.hpp>

#	if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
#		include <memory>
#	endif
#endif

#include <cstddef>

#if __cplusplus >= 201103L
#	include <type_traits>
#endif


namespace kerbal
{

	namespace memory
	{

		namespace detail
		{

			struct any_node_base
			{
			};

			template <typename T>
			struct any_node :
					public any_node_base,
					private kerbal::utility::member_compress_helper<T>
			{
				private:
					typedef kerbal::utility::member_compress_helper<T> member_compress_helper;

				public:

#		if __cplusplus >= 201103L

					template <typename ... Args>
					KERBAL_CONSTEXPR
					explicit any_node(kerbal::utility::in_place_t in_place, Args&& ... args)
							: member_compress_helper(in_place, kerbal::utility::forward<Args>(args)...)
					{
					}

#		else

#				define EMPTY
#				define LEFT_JOIN_COMMA(exp) , exp
#				define THEAD_NOT_EMPTY(exp) template <exp>
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
					explicit any_node(kerbal::utility::in_place_t in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
							: member_compress_helper(in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)) \
					{ \
					}

					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#				undef EMPTY
#				undef LEFT_JOIN_COMMA
#				undef THEAD_NOT_EMPTY
#				undef TARGS_DECL
#				undef ARGS_DECL
#				undef ARGS_USE
#				undef FBODY

#		endif

				using member_compress_helper::member;

			};



		} // namespace detail



		template <std::size_t Size, std::size_t Align>
		class any_storage
		{

			public:

				typedef typename kerbal::type_traits::aligned_storage<Size, Align>::type	aligned_storage_type;

				union storage
				{
						kerbal::memory::detail::any_node_base * ptr;
						aligned_storage_type buffer;
				} k_storage;

			private:

				template <typename T>
				KERBAL_CONSTEXPR20
				typename kerbal::memory::detail::any_node<T> *
				k_obj_pos_impl(kerbal::type_traits::false_type) KERBAL_NOEXCEPT
				{
					typedef typename kerbal::memory::detail::any_node<T> any_node;
					return static_cast<any_node *>(this->k_storage.ptr);
				}

				template <typename T>
				typename kerbal::memory::detail::any_node<T> *
				k_obj_pos_impl(kerbal::type_traits::true_type) KERBAL_NOEXCEPT
				{
					typedef typename kerbal::memory::detail::any_node<T> any_node;
					return reinterpret_cast<any_node *>(&this->k_storage.buffer);
				}

			public:

				template <typename T>
				KERBAL_CONSTEXPR20
				typename kerbal::memory::detail::any_node<T> *
				obj_pos(kerbal::type_traits::false_type embedded) KERBAL_NOEXCEPT
				{
					return this->k_obj_pos_impl<T>(embedded);
				}

				template <typename T>
				KERBAL_CONSTEXPR20
				typename kerbal::memory::detail::any_node<T> *
				obj_pos(kerbal::type_traits::true_type embedded) KERBAL_NOEXCEPT
				{

#			if __cplusplus > 201703L
#				if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
					if (KERBAL_IS_CONSTANT_EVALUATED()) {
						return this->k_obj_pos_impl<T>(kerbal::type_traits::false_type());
					}
#				endif
#			endif

					return this->k_obj_pos_impl<T>(embedded);
				}


			private:

				template <typename T>
				KERBAL_CONSTEXPR20
				const typename kerbal::memory::detail::any_node<T> *
				k_obj_pos_impl(kerbal::type_traits::false_type) const KERBAL_NOEXCEPT
				{
					typedef typename kerbal::memory::detail::any_node<T> any_node;
					return static_cast<const any_node *>(this->k_storage.ptr);
				}

				template <typename T>
				const typename kerbal::memory::detail::any_node<T> *
				k_obj_pos_impl(kerbal::type_traits::true_type) const KERBAL_NOEXCEPT
				{
					typedef typename kerbal::memory::detail::any_node<T> any_node;
					return reinterpret_cast<const any_node *>(&this->k_storage.buffer);
				}

			public:

				template <typename T>
				KERBAL_CONSTEXPR20
				const typename kerbal::memory::detail::any_node<T> *
				obj_pos(kerbal::type_traits::false_type embedded) const KERBAL_NOEXCEPT
				{
					return this->k_obj_pos_impl<T>(embedded);
				}

				template <typename T>
				KERBAL_CONSTEXPR20
				const typename kerbal::memory::detail::any_node<T> *
				obj_pos(kerbal::type_traits::true_type embedded) const KERBAL_NOEXCEPT
				{

#			if __cplusplus > 201703L
#				if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
					if (KERBAL_IS_CONSTANT_EVALUATED()) {
						return this->k_obj_pos_impl<T>(kerbal::type_traits::false_type());
					}
#				endif
#			endif

					return this->k_obj_pos_impl<T>(embedded);
				}


			private:

				template <typename T, typename AnyNodeAllocator>
				KERBAL_CONSTEXPR20
				void k_destroy_impl(kerbal::type_traits::false_type embedded, AnyNodeAllocator & any_node_alloc) KERBAL_NOEXCEPT
				{
					typedef typename kerbal::memory::detail::any_node<T> any_node;
					typedef kerbal::memory::allocator_traits<AnyNodeAllocator> allocator_traits;

					any_node * stored_pos = this->obj_pos<T>(embedded);
					allocator_traits::destroy(any_node_alloc, stored_pos);
					allocator_traits::deallocate(any_node_alloc, stored_pos, 1);
				}

				template <typename T, typename AnyNodeAllocator>
				KERBAL_CONSTEXPR20
				void k_destroy_impl(kerbal::type_traits::true_type embedded, AnyNodeAllocator & any_node_alloc) KERBAL_NOEXCEPT
				{
					typedef typename kerbal::memory::detail::any_node<T> any_node;
					typedef kerbal::memory::allocator_traits<AnyNodeAllocator> allocator_traits;

					any_node * stored_pos = this->obj_pos<T>(embedded);
					allocator_traits::destroy(any_node_alloc, stored_pos);
				}

			public:

				template <typename T, typename Allocator>
				KERBAL_CONSTEXPR20
				void destroy(kerbal::type_traits::false_type embedded, Allocator & alloc) KERBAL_NOEXCEPT
				{
					typedef kerbal::memory::allocator_traits<Allocator>								allocator_traits;
					typedef kerbal::memory::detail::any_node<T>										any_node;
					typedef typename allocator_traits::template rebind_alloc<any_node>::other		any_node_allocator_type;

					any_node_allocator_type any_node_alloc(alloc);
					this->k_destroy_impl<T>(embedded, any_node_alloc);
				}

				template <typename T, typename Allocator>
				KERBAL_CONSTEXPR20
				void destroy(kerbal::type_traits::true_type embedded, Allocator & alloc) KERBAL_NOEXCEPT
				{
					typedef kerbal::memory::allocator_traits<Allocator>								allocator_traits;
					typedef kerbal::memory::detail::any_node<T>										any_node;
					typedef typename allocator_traits::template rebind_alloc<any_node>::other		any_node_allocator_type;

					any_node_allocator_type any_node_alloc(alloc);

#			if __cplusplus > 201703L
#				if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
					if (KERBAL_IS_CONSTANT_EVALUATED()) {
						this->k_destroy_impl<T>(kerbal::type_traits::false_type(), any_node_alloc);
						return;
					}
#				endif
#			endif

					this->k_destroy_impl<T>(embedded, any_node_alloc);
				}


#	if __cplusplus >= 201103L

			private:

				template <typename T, typename AnyNodeAllocator, typename ... Args>
				KERBAL_CONSTEXPR20
				void k_construct_impl(kerbal::type_traits::false_type /*embedded*/, AnyNodeAllocator & any_node_alloc, Args&& ... args)
				{
					typedef T value_type;
					typedef typename kerbal::memory::detail::any_node<value_type> any_node;
					typedef kerbal::memory::allocator_traits<AnyNodeAllocator> allocator_traits;

					any_node * stored_pos = allocator_traits::allocate(any_node_alloc, 1);
#			if __cpp_exceptions
					try {
#			endif
						allocator_traits::construct(any_node_alloc, stored_pos, kerbal::utility::in_place_t(), kerbal::utility::forward<Args>(args)...);
#			if __cpp_exceptions
					} catch (...) {
						allocator_traits::deallocate(any_node_alloc, stored_pos, 1);
						throw;
					}
#			endif
					this->k_storage.ptr = static_cast<kerbal::memory::detail::any_node_base *>(stored_pos);
				}

				template <typename T, typename AnyNodeAllocator, typename ... Args>
				void k_construct_impl(kerbal::type_traits::true_type /*embedded*/, AnyNodeAllocator & any_node_alloc, Args&& ... args)
				{
					typedef T value_type;
					typedef typename kerbal::memory::detail::any_node<value_type> any_node;
					typedef kerbal::memory::allocator_traits<AnyNodeAllocator> allocator_traits;

					any_node * stored_pos = reinterpret_cast<any_node *>(&this->k_storage.buffer);
					allocator_traits::construct(any_node_alloc, stored_pos, kerbal::utility::in_place_t(), kerbal::utility::forward<Args>(args)...);
				}

			public:

				template <typename T, typename Allocator, typename ... Args>
				KERBAL_CONSTEXPR20
				void construct(kerbal::type_traits::false_type embedded, Allocator & alloc, Args&& ... args)
				{
					typedef typename kerbal::type_traits::remove_const<T>::type value_type;
					typedef kerbal::memory::allocator_traits<Allocator>								allocator_traits;
					typedef kerbal::memory::detail::any_node<value_type>							any_node;
					typedef typename allocator_traits::template rebind_alloc<any_node>::other		any_node_allocator_type;

					any_node_allocator_type any_node_alloc(alloc);

					this->k_construct_impl<value_type>(embedded, any_node_alloc, kerbal::utility::forward<Args>(args)...);
				}

				template <typename T, typename Allocator, typename ... Args>
				KERBAL_CONSTEXPR20
				void construct(kerbal::type_traits::true_type embedded, Allocator & alloc, Args&& ... args)
				{
					typedef typename kerbal::type_traits::remove_const<T>::type value_type;
					typedef kerbal::memory::allocator_traits<Allocator>								allocator_traits;
					typedef kerbal::memory::detail::any_node<value_type>							any_node;
					typedef typename allocator_traits::template rebind_alloc<any_node>::other		any_node_allocator_type;

					any_node_allocator_type any_node_alloc(alloc);

#			if __cplusplus > 201703L
#				if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
					if (KERBAL_IS_CONSTANT_EVALUATED()) {
						this->k_construct_impl<value_type>(kerbal::type_traits::false_type(), any_node_alloc, kerbal::utility::forward<Args>(args)...);
						return;
					}
#				endif
#			endif

					this->k_construct_impl<value_type>(embedded, any_node_alloc, kerbal::utility::forward<Args>(args)...);
				}

#	else

#			define EMPTY
#			define LEFT_JOIN_COMMA(exp) , exp
#			define TARGS_DECL(i) KERBAL_MACRO_CONCAT(typename Arg, i)
#			define ARGS_DECL(i) KERBAL_MACRO_CONCAT(const Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)

#		if __cpp_exceptions

#			define CONSTRUCT_IMPL_NOT_EMBEDDED(i) \
				template <typename T, typename AnyNodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
				void k_construct_impl(kerbal::type_traits::false_type, AnyNodeAllocator & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
				{ \
					typedef T value_type; \
					typedef kerbal::memory::detail::any_node<value_type> any_node; \
					typedef kerbal::memory::allocator_traits<AnyNodeAllocator> allocator_traits; \
 \
					any_node * stored_pos = allocator_traits::allocate(alloc, 1); \
					try { \
						allocator_traits::construct(alloc, stored_pos, kerbal::utility::in_place_t() KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
					} catch (...) { \
						allocator_traits::deallocate(alloc, stored_pos, 1); \
						throw; \
					} \
					this->k_storage.ptr = static_cast<kerbal::memory::detail::any_node_base *>(stored_pos); \
				}

#		else

#			define CONSTRUCT_IMPL_NOT_EMBEDDED(i) \
				template <typename T, typename AnyNodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
				void k_construct_impl(kerbal::type_traits::false_type, AnyNodeAllocator & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
				{ \
					typedef T value_type; \
					typedef kerbal::memory::detail::any_node<value_type> any_node; \
					typedef kerbal::memory::allocator_traits<AnyNodeAllocator> allocator_traits; \
 \
					any_node * stored_pos = allocator_traits::allocate(alloc, 1); \
					allocator_traits::construct(alloc, stored_pos, kerbal::utility::in_place_t() KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
					this->k_storage.ptr = static_cast<kerbal::memory::detail::any_node_base *>(stored_pos); \
				}

#		endif


#			define FBODY(i) \
			private: \
				CONSTRUCT_IMPL_NOT_EMBEDDED(i) \
 \
				template <typename T, typename AnyNodeAllocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
				void k_construct_impl(kerbal::type_traits::true_type, AnyNodeAllocator & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
				{ \
					typedef T value_type; \
					typedef kerbal::memory::detail::any_node<value_type> any_node; \
					typedef kerbal::memory::allocator_traits<AnyNodeAllocator> allocator_traits; \
 \
					any_node * stored_pos = reinterpret_cast<any_node *>(&this->k_storage.buffer); \
					allocator_traits::construct(alloc, stored_pos, kerbal::utility::in_place_t() KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				} \
 \
			public: \
				template <typename T, typename Allocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
				void construct(kerbal::type_traits::false_type embedded, Allocator & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
				{ \
					typedef typename kerbal::type_traits::remove_const<T>::type value_type; \
					typedef kerbal::memory::allocator_traits<Allocator>								allocator_traits; \
					typedef kerbal::memory::detail::any_node<value_type>							any_node; \
					typedef typename allocator_traits::template rebind_alloc<any_node>::other		any_node_allocator_type; \
 \
					any_node_allocator_type any_node_alloc(alloc); \
					this->k_construct_impl<value_type>(embedded, any_node_alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				} \
 \
				template <typename T, typename Allocator KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
				void construct(kerbal::type_traits::true_type embedded, Allocator & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
				{ \
					typedef typename kerbal::type_traits::remove_const<T>::type value_type; \
					typedef kerbal::memory::allocator_traits<Allocator>								allocator_traits; \
					typedef kerbal::memory::detail::any_node<value_type>							any_node; \
					typedef typename allocator_traits::template rebind_alloc<any_node>::other		any_node_allocator_type; \
 \
					any_node_allocator_type any_node_alloc(alloc); \
					this->k_construct_impl<value_type>(embedded, any_node_alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				}


				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#			undef EMPTY
#			undef LEFT_JOIN_COMMA
#			undef TARGS_DECL
#			undef ARGS_DECL
#			undef ARGS_USE
#			undef CONSTRUCT_IMPL_NOT_EMBEDDED
#			undef FBODY

#	endif



#	if __cplusplus >= 201103L
#		define ANY_STORAGE_XFER_TYPE any_storage &&
#	else
#		define ANY_STORAGE_XFER_TYPE any_storage &
#	endif

				KERBAL_CONSTEXPR20
				void k_xfer_impl(kerbal::type_traits::false_type, ANY_STORAGE_XFER_TYPE ano) KERBAL_NOEXCEPT
				{
					this->k_storage.ptr = ano.k_storage.ptr;
				}

				template <typename T, typename SelfAnyNodeAlloctor, typename AnoAnyNodeAllocator>
				void k_xfer_impl(kerbal::type_traits::true_type embedded, SelfAnyNodeAlloctor & self_alloc, ANY_STORAGE_XFER_TYPE ano, AnoAnyNodeAllocator & ano_alloc) KERBAL_NOEXCEPT
				{

#	if __cplusplus >= 201103L
					KERBAL_STATIC_ASSERT(std::is_nothrow_move_constructible<T>::value, "Static check failed!");
#	endif

					typedef T value_type;
					typedef typename kerbal::memory::detail::any_node<value_type> any_node;

					any_node * anop = ano.template k_obj_pos_impl<value_type>(embedded);
					any_node * stored_pos = reinterpret_cast<any_node*>(&this->k_storage.buffer);

					typedef kerbal::memory::allocator_traits<SelfAnyNodeAlloctor> self_allocator_traits;
					self_allocator_traits::construct(self_alloc, stored_pos, kerbal::utility::in_place_t(), kerbal::compatibility::to_xvalue(anop->member()));

					typedef kerbal::memory::allocator_traits<AnoAnyNodeAllocator> ano_allocator_traits;
					ano_allocator_traits::destroy(ano_alloc, anop);
				}

				template <typename T, typename SelfAlloctor, typename AnoAllocator>
				KERBAL_CONSTEXPR20
				void xfer(kerbal::type_traits::false_type embedded, SelfAlloctor & /*self_alloc*/, ANY_STORAGE_XFER_TYPE ano, AnoAllocator & /*ano_alloc*/) KERBAL_NOEXCEPT
				{
					this->k_xfer_impl(embedded, kerbal::compatibility::to_xvalue(ano));
				}

				template <typename T, typename SelfAlloctor, typename AnoAllocator>
				KERBAL_CONSTEXPR20
				void xfer(kerbal::type_traits::true_type embedded, SelfAlloctor & self_alloc, ANY_STORAGE_XFER_TYPE ano, AnoAllocator & ano_alloc) KERBAL_NOEXCEPT
				{

#			if __cplusplus > 201703L
#				if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
					if (KERBAL_IS_CONSTANT_EVALUATED()) {
						this->k_xfer_impl(kerbal::type_traits::false_type(), kerbal::compatibility::move(ano));
						return;
					}
#				endif
#			endif

					typedef kerbal::memory::detail::any_node<T>											any_node;
					typedef kerbal::memory::allocator_traits<SelfAlloctor>								self_allocator_traits;
					typedef typename self_allocator_traits::template rebind_alloc<any_node>::other		self_any_node_allocator_type;
					typedef kerbal::memory::allocator_traits<AnoAllocator>								ano_allocator_traits;
					typedef typename ano_allocator_traits::template rebind_alloc<any_node>::other		ano_any_node_allocator_type;

					self_any_node_allocator_type self_any_node_alloc(self_alloc);
					ano_any_node_allocator_type ano_any_node_alloc(ano_alloc);
					this->k_xfer_impl<T>(embedded, self_any_node_alloc, kerbal::compatibility::to_xvalue(ano), ano_any_node_alloc);
				}

#	undef ANY_STORAGE_XFER_TYPE

		};

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_ANY_STORAGE_HPP
