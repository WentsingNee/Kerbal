/**
 * @file       any.hpp
 * @brief      
 * @date       2019-7-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ANY_ANY_HPP
#define KERBAL_ANY_ANY_HPP

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compatibility/alignof.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/method_overload_tag.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/type_traits/aligned_storage.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/const_deduction.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_same.hpp>
#include <kerbal/type_traits/reference_deduction.hpp>
#include <kerbal/utility/declval.hpp>
#include <kerbal/utility/in_place.hpp>
#include <kerbal/utility/member_compress_helper.hpp>
#include <kerbal/utility/throw_this_exception.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#else
#	include <kerbal/type_traits/array_traits.hpp>
#	include <kerbal/type_traits/fundamental_deduction.hpp>
#	include <kerbal/type_traits/member_pointer_deduction.hpp>
#	include <kerbal/type_traits/pointer_deduction.hpp>
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


#include <kerbal/any/fwd/any.fwd.hpp>
#include <kerbal/any/bad_any_cast.hpp>


namespace kerbal
{

	namespace any
	{

#	if __cplusplus < 201103L

		namespace detail
		{

			template <typename T>
			struct any_can_be_nothrow_move_constructible_base :
					kerbal::type_traits::bool_constant<
						kerbal::type_traits::is_fundamental<T>::value ||
						kerbal::type_traits::is_member_pointer<T>::value ||
						kerbal::type_traits::is_pointer<T>::value
					>
			{
			};

			template <typename T>
			struct any_can_be_nothrow_move_constructible :
					any_can_be_nothrow_move_constructible_base<
						typename kerbal::type_traits::remove_all_extents<T>::type
					>
			{
			};

		} // namespace detail

#	endif

		template <typename T, std::size_t Size, std::size_t Align>
		struct is_any_internal_stored_type :
				kerbal::type_traits::bool_constant<
						sizeof(T) <= Size && KERBAL_ALIGNOF(T) <= Align
#	if __cplusplus >= 201103L
						&& std::is_nothrow_move_constructible<T>::value
#	else
						&& detail::any_can_be_nothrow_move_constructible<T>::value
#	endif
				>
		{
		};


		namespace detail
		{

			struct any_node_base
			{
			};

			template <typename T>
			struct any_node :
					public any_node_base
			{
					T value;

#		if __cplusplus >= 201103L

					template <typename ... Args>
					KERBAL_CONSTEXPR
					explicit any_node(kerbal::utility::in_place_t, Args&& ... args)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<T, Args&&...>::value)
										)
							: value(kerbal::utility::forward<Args>(args)...)
					{
					}

#		else

#				define EMPTY
#				define REMAINF(exp) exp
#				define LEFT_JOIN_COMMA(exp) , exp
#				define THEAD_NOT_EMPTY(exp) template <exp>
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
					explicit any_node(kerbal::utility::in_place_t KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
							: value(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i)) \
					{ \
					}

					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#				undef EMPTY
#				undef REMAINF
#				undef LEFT_JOIN_COMMA
#				undef THEAD_NOT_EMPTY
#				undef TARGS_DECL
#				undef ARGS_DECL
#				undef ARGS_USE
#				undef FBODY

#		endif

			};

			template <typename Allocator, std::size_t Size, std::size_t Align>
			struct any_manager_table
			{
					typedef kerbal::any::basic_any<Allocator, Size, Align> any;
					typedef void (*destroy_entry_type)(any &) KERBAL_NOEXCEPT17;
					typedef void (*clone_entry_type)(any &, const any &);
#	if __cplusplus >= 201103L
					typedef void (*xfer_entry_type)(any &, any &&) KERBAL_NOEXCEPT17;
#	endif
					typedef void (*swap_xfer_to_tmp_entry_type)(any &, typename any::storage &) KERBAL_NOEXCEPT17;
					typedef void (*swap_xfer_from_other_entry_type)(any &, any &) KERBAL_NOEXCEPT17;
					typedef void (*swap_xfer_from_tmp_entry_type)(any &, typename any::storage &) KERBAL_NOEXCEPT17;
					typedef const std::type_info & (*type_info_entry_type)() KERBAL_NOEXCEPT17;


					destroy_entry_type					destroy;
					clone_entry_type					clone;
#	if __cplusplus >= 201103L
					xfer_entry_type						xfer;
#	endif
					swap_xfer_to_tmp_entry_type			swap_xfer_to_tmp;
					swap_xfer_from_other_entry_type		swap_xfer_from_other;
					swap_xfer_from_tmp_entry_type		swap_xfer_from_tmp;
					type_info_entry_type				type_info;


					KERBAL_CONSTEXPR
					any_manager_table(
								  destroy_entry_type					destroy,
								  clone_entry_type						clone,
#	if __cplusplus >= 201103L
								  xfer_entry_type						xfer,
#	endif
								  swap_xfer_to_tmp_entry_type			swap_xfer_to_tmp,
								  swap_xfer_from_other_entry_type		swap_xfer_from_other,
								  swap_xfer_from_tmp_entry_type			swap_xfer_from_tmp,
								  type_info_entry_type					type_info
					) KERBAL_NOEXCEPT :
							destroy(destroy),
							clone(clone),
#	if __cplusplus >= 201103L
							xfer(xfer),
#	endif
							swap_xfer_to_tmp(swap_xfer_to_tmp),
							swap_xfer_from_other(swap_xfer_from_other),
							swap_xfer_from_tmp(swap_xfer_from_tmp),
							type_info(type_info)
					{
					}

			};

			template <typename T, typename Allocator, std::size_t Size, std::size_t Align>
			struct any_manager_collection;

			template <typename Allocator, std::size_t Size, std::size_t Align>
			struct any_manager_collection<void, Allocator, Size, Align>
			{
				private:
					typedef kerbal::any::basic_any<Allocator, Size, Align>					any;
					typedef typename any::void_allocator_type								void_allocator_type;
					typedef kerbal::memory::allocator_traits<void_allocator_type>			void_allocator_traits;
					typedef any_manager_table<Allocator, Size, Align>						manager_table;

					KERBAL_CONSTEXPR20
					static void destroy(any & /*self*/) KERBAL_NOEXCEPT
					{
					}

					KERBAL_CONSTEXPR20
					static void clone(any & /*self*/, const any & /*ano*/) KERBAL_NOEXCEPT
					{
					}

#	if __cplusplus >= 201103L

					KERBAL_CONSTEXPR20
					static void xfer(any & /*self*/, any && /*ano*/) KERBAL_NOEXCEPT
					{
					}

#	endif

					KERBAL_CONSTEXPR20
					static void swap_xfer_to_tmp(any & /*self*/, typename any::storage & /*storage_temp*/) KERBAL_NOEXCEPT
					{
					}

					KERBAL_CONSTEXPR20
					static void swap_xfer_from_other(any & /*self*/, any & /*other*/) KERBAL_NOEXCEPT
					{
					}

					KERBAL_CONSTEXPR20
					static void swap_xfer_from_tmp(any & /*self*/, typename any::storage & /*storage_temp*/) KERBAL_NOEXCEPT
					{
					}

					KERBAL_CONSTEXPR20
					static const std::type_info & type_info() KERBAL_NOEXCEPT17
					{
						return typeid(void);
					}

				public:

#		if __cplusplus >= 201103L
					KERBAL_CONSTEXPR
#			if __cplusplus >= 201703L
					inline
#			endif
					static const manager_table mtable = manager_table(destroy, clone, xfer, swap_xfer_to_tmp, swap_xfer_from_other, swap_xfer_from_tmp, type_info);
#		else
					static const manager_table mtable;
#		endif

			};


#	if __cplusplus >= 201103L

#		if __cplusplus < 201703L
			template <typename Allocator, std::size_t Size, std::size_t Align>
			KERBAL_CONSTEXPR
			const typename any_manager_collection<void, Allocator, Size, Align>::manager_table
			any_manager_collection<void, Allocator, Size, Align>::mtable;
#		endif

#	else

			template <typename Allocator, std::size_t Size, std::size_t Align>
			const typename any_manager_collection<void, Allocator, Size, Align>::manager_table
			any_manager_collection<void, Allocator, Size, Align>::mtable(destroy, clone, swap_xfer_to_tmp, swap_xfer_from_other, swap_xfer_from_tmp, type_info);

#	endif

			template <typename T, typename Allocator, std::size_t Size, std::size_t Align>
			struct any_manager_collection
			{
				private:
					typedef kerbal::any::basic_any<Allocator, Size, Align>								any;
					typedef kerbal::any::detail::any_node<T>											any_node;
					typedef typename any::void_allocator_type											void_allocator_type;
					typedef kerbal::memory::allocator_traits<void_allocator_type>						void_allocator_traits;
					typedef typename void_allocator_traits::template rebind_alloc<any_node>::other		allocator_type;
					typedef kerbal::memory::allocator_traits<allocator_type>							allocator_traits;
					typedef is_any_internal_stored_type<T, Size, Align>									is_internal_stored_type;
					typedef any_manager_table<Allocator, Size, Align>									manager_table;

					KERBAL_STATIC_ASSERT(!kerbal::type_traits::is_const<T>::value, "T couldn't be const");
					KERBAL_STATIC_ASSERT(!kerbal::type_traits::is_reference<T>::value, "T couldn't be reference");

					KERBAL_CONSTEXPR20
					static void k_destroy(kerbal::type_traits::false_type, any & self) KERBAL_NOEXCEPT
					{
						any_node * stored_pos = self.template obj_pos<T>();
						allocator_type alloc(self.void_alloc());
						allocator_traits::destroy(alloc, stored_pos);
						allocator_traits::deallocate(alloc, stored_pos, 1);
					}

					KERBAL_CONSTEXPR20
					static void k_destroy(kerbal::type_traits::true_type, any & self) KERBAL_NOEXCEPT
					{
						any_node * stored_pos = self.template obj_pos<T>();
						allocator_type alloc(self.void_alloc());
						allocator_traits::destroy(alloc, stored_pos);
					}

					KERBAL_CONSTEXPR20
					static void destroy(any & self) KERBAL_NOEXCEPT
					{

#			if __cplusplus > 201703L
#				if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
						if (KERBAL_IS_CONSTANT_EVALUATED()) {
							k_destroy(kerbal::type_traits::false_type(), self);
							return;
						}
#				endif
#			endif

						k_destroy(is_internal_stored_type(), self);
					}



					KERBAL_CONSTEXPR20
					static void k_clone(kerbal::type_traits::false_type, any & self, const any & ano)
					{
						const any_node * anop = ano.template obj_pos<T>();
						allocator_type alloc(self.void_alloc());

						any_node * stored_pos = allocator_traits::allocate(alloc, 1);
#			if __cpp_exceptions
						try {
#			endif
							allocator_traits::construct(alloc, stored_pos, kerbal::utility::in_place_t(), anop->value);
#			if __cpp_exceptions
						} catch (...) {
							allocator_traits::deallocate(alloc, stored_pos, 1);
							throw;
						}
#			endif
						self.k_storage.ptr = stored_pos;
					}

					static void k_clone(kerbal::type_traits::true_type, any & self, const any & ano)
					{
						const any_node * anop = ano.template obj_pos<T>();
						allocator_type alloc(self.void_alloc());

						any_node * stored_pos = reinterpret_cast<any_node*>(&self.k_storage.buffer);
						allocator_traits::construct(alloc, stored_pos, kerbal::utility::in_place_t(), anop->value);
					}

					KERBAL_CONSTEXPR20
					static void clone(any & self, const any & ano)
					{

#			if __cplusplus > 201703L
#				if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
						if (KERBAL_IS_CONSTANT_EVALUATED()) {
							k_clone(kerbal::type_traits::false_type(), self, ano);
							return;
						}
#				endif
#			endif

						k_clone(is_internal_stored_type(), self, ano);
					}



#	if __cplusplus >= 201103L

					KERBAL_CONSTEXPR20
					static void k_xfer(kerbal::type_traits::false_type, any & self, any && ano) KERBAL_NOEXCEPT
					{
						any_node * anop = ano.template obj_pos<T>();
						self.k_storage.ptr = anop;
						ano.k_mtable = &detail::any_manager_collection<void, Allocator, Size, Align>::mtable;
					}

					static void k_xfer(kerbal::type_traits::true_type, any & self, any && ano) KERBAL_NOEXCEPT
					{
						KERBAL_STATIC_ASSERT(std::is_nothrow_move_constructible<T>::value, "Static check failed!");

						any_node * anop = ano.template obj_pos<T>();

						any_node * stored_pos = reinterpret_cast<any_node*>(&self.k_storage.buffer);
						{
							allocator_type alloc(self.void_alloc());
							allocator_traits::construct(alloc, stored_pos, kerbal::utility::in_place_t(), kerbal::compatibility::move(anop->value));
						}
						{
							allocator_type alloc(ano.void_alloc());
							allocator_traits::destroy(alloc, anop);
						}
						ano.k_mtable = &detail::any_manager_collection<void, Allocator, Size, Align>::mtable;
					}

					KERBAL_CONSTEXPR20
					static void xfer(any & self, any && ano) KERBAL_NOEXCEPT
					{

#			if __cplusplus > 201703L
#				if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
						if (KERBAL_IS_CONSTANT_EVALUATED()) {
							k_xfer(kerbal::type_traits::false_type(), self, kerbal::compatibility::move(ano));
							return;
						}
#				endif
#			endif

						k_xfer(is_internal_stored_type(), self, kerbal::compatibility::move(ano));
					}

#	endif



					KERBAL_CONSTEXPR20
					static void k_swap_xfer_to_tmp(kerbal::type_traits::false_type, any & self, typename any::storage & storage_temp) KERBAL_NOEXCEPT
					{
						storage_temp.ptr = self.template obj_pos<T>();
					}

					static void k_swap_xfer_to_tmp(kerbal::type_traits::true_type, any & self, typename any::storage & storage_temp) KERBAL_NOEXCEPT
					{

#	if __cplusplus >= 201103L
						KERBAL_STATIC_ASSERT(std::is_nothrow_move_constructible<T>::value, "Static check failed!");
#	else
						KERBAL_STATIC_ASSERT(detail::any_can_be_nothrow_move_constructible<T>::value, "Static check failed!");
#	endif

						allocator_type alloc(self.void_alloc());
						any_node * selfp = self.template obj_pos<T>();
						any_node * top = reinterpret_cast<any_node*>(&storage_temp.buffer);
						allocator_traits::construct(alloc, top, kerbal::utility::in_place_t(), kerbal::compatibility::to_xvalue(selfp->value));
						allocator_traits::destroy(alloc, selfp);
					}

					static void swap_xfer_to_tmp(any & self, typename any::storage & storage_temp) KERBAL_NOEXCEPT
					{

#			if __cplusplus > 201703L
#				if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
						if (KERBAL_IS_CONSTANT_EVALUATED()) {
							k_swap_xfer_to_tmp(kerbal::type_traits::false_type(), self, storage_temp);
							return;
						}
#				endif
#			endif

						k_swap_xfer_to_tmp(is_internal_stored_type(), self, storage_temp);
					}



					KERBAL_CONSTEXPR20
					static void k_swap_xfer_from_other(kerbal::type_traits::false_type, any & self, any & other) KERBAL_NOEXCEPT
					{
						self.k_storage.ptr = other.template obj_pos<T>();
					}

					static void k_swap_xfer_from_other(kerbal::type_traits::true_type, any & self, any & other) KERBAL_NOEXCEPT
					{

#	if __cplusplus >= 201103L
						KERBAL_STATIC_ASSERT(std::is_nothrow_move_constructible<T>::value, "Static check failed!");
#	else
						KERBAL_STATIC_ASSERT(detail::any_can_be_nothrow_move_constructible<T>::value, "Static check failed!");
#	endif

						allocator_type alloc(self.void_alloc());
						any_node * fromp = other.template obj_pos<T>();
						any_node * selfp = reinterpret_cast<any_node*>(&self.k_storage.buffer);
						allocator_traits::construct(alloc, selfp, kerbal::utility::in_place_t(), kerbal::compatibility::to_xvalue(fromp->value));
						allocator_traits::destroy(alloc, fromp);
					}

					static void swap_xfer_from_other(any & self, any & other) KERBAL_NOEXCEPT
					{

#			if __cplusplus > 201703L
#				if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
						if (KERBAL_IS_CONSTANT_EVALUATED()) {
							k_swap_xfer_from_other(kerbal::type_traits::false_type(), self, other);
							return;
						}
#				endif
#			endif

						k_swap_xfer_from_other(is_internal_stored_type(), self, other);
					}



					KERBAL_CONSTEXPR20
					static void k_swap_xfer_from_tmp(kerbal::type_traits::false_type, any & self, typename any::storage & storage_temp) KERBAL_NOEXCEPT
					{
						self.k_storage.ptr = storage_temp.ptr;
					}

					static void k_swap_xfer_from_tmp(kerbal::type_traits::true_type, any & self, typename any::storage & storage_temp) KERBAL_NOEXCEPT
					{

#	if __cplusplus >= 201103L
						KERBAL_STATIC_ASSERT(std::is_nothrow_move_constructible<T>::value, "Static check failed!");
#	else
						KERBAL_STATIC_ASSERT(detail::any_can_be_nothrow_move_constructible<T>::value, "Static check failed!");
#	endif

						allocator_type alloc(self.void_alloc());
						any_node * fromp = reinterpret_cast<any_node *>(&storage_temp.buffer);
						any_node * selfp = reinterpret_cast<any_node*>(&self.k_storage.buffer);
						allocator_traits::construct(alloc, selfp, kerbal::utility::in_place_t(), kerbal::compatibility::to_xvalue(fromp->value));
						allocator_traits::destroy(alloc, fromp);
					}

					static void swap_xfer_from_tmp(any & self, typename any::storage & storage_temp) KERBAL_NOEXCEPT
					{

#			if __cplusplus > 201703L
#				if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
						if (KERBAL_IS_CONSTANT_EVALUATED()) {
							k_swap_xfer_from_tmp(kerbal::type_traits::false_type(), self, storage_temp);
							return;
						}
#				endif
#			endif

						k_swap_xfer_from_tmp(is_internal_stored_type(), self, storage_temp);
					}

					KERBAL_CONSTEXPR20
					static const std::type_info & type_info() KERBAL_NOEXCEPT17
					{
						return typeid(T);
					}

				public:

#		if __cplusplus >= 201103L
					KERBAL_CONSTEXPR
#			if __cplusplus >= 201703L
					inline
#			endif
					static const manager_table mtable = manager_table(destroy, clone, xfer, swap_xfer_to_tmp, swap_xfer_from_other, swap_xfer_from_tmp, type_info);
#		else
					static const manager_table mtable;
#		endif

			};


#	if __cplusplus >= 201103L

#		if __cplusplus < 201703L
			template <typename T, typename Allocator, std::size_t Size, std::size_t Align>
			KERBAL_CONSTEXPR
			const typename any_manager_collection<T, Allocator, Size, Align>::manager_table
			any_manager_collection<T, Allocator, Size, Align>::mtable;
#		endif

#	else

			template <typename T, typename Allocator, std::size_t Size, std::size_t Align>
			const typename any_manager_collection<T, Allocator, Size, Align>::manager_table
			any_manager_collection<T, Allocator, Size, Align>::mtable(destroy, clone, swap_xfer_to_tmp, swap_xfer_from_other, swap_xfer_from_tmp, type_info);

#	endif

		} // namespace detail


		template <typename Allocator, std::size_t Size, std::size_t Align>
		class basic_any :
				private kerbal::utility::member_compress_helper<Allocator>
		{
			private:

				friend struct detail::any_manager_table<Allocator, Size, Align>;

				template <typename T, typename Allocator2, std::size_t Size2, std::size_t Align2>
				friend struct kerbal::any::detail::any_manager_collection;

				template <typename T, typename Allocator2, std::size_t Size2, std::size_t Align2>
				KERBAL_CONSTEXPR20
				friend
				T* any_cast(basic_any<Allocator2, Size2, Align2> * operand) KERBAL_NOEXCEPT;

				template <typename T, typename Allocator2, std::size_t Size2, std::size_t Align2>
				KERBAL_CONSTEXPR20
				friend
				const T* any_cast(const basic_any<Allocator2, Size2, Align2> * operand) KERBAL_NOEXCEPT;

				template <typename T>
				struct is_internal_stored_type :
						is_any_internal_stored_type<T, Size, Align>
				{
				};

				typedef kerbal::any::detail::any_node_base			any_node_base;

				template <typename T>
				struct get_any_node_type
				{
						typedef kerbal::any::detail::any_node<T> type;
				};

				typedef const detail::any_manager_table<Allocator, Size, Align>				manager_table;
				typedef kerbal::utility::member_compress_helper<Allocator>					allocator_compress_helper;
				typedef typename kerbal::type_traits::aligned_storage<Size, Align>::type	aligned_storage_type;

			public:
				typedef Allocator void_allocator_type;

			private:

				manager_table * k_mtable;

				union storage
				{
						any_node_base * ptr;
						aligned_storage_type buffer;
				} k_storage;

				template <typename T>
				KERBAL_CONSTEXPR20
				typename get_any_node_type<T>::type *
				k_obj_pos(kerbal::type_traits::false_type) KERBAL_NOEXCEPT
				{
					typedef typename get_any_node_type<T>::type any_node;
					return static_cast<any_node *>(this->k_storage.ptr);
				}

				template <typename T>
				typename get_any_node_type<T>::type *
				k_obj_pos(kerbal::type_traits::true_type) KERBAL_NOEXCEPT
				{
					typedef typename get_any_node_type<T>::type any_node;
					return reinterpret_cast<any_node *>(&this->k_storage.buffer);
				}

				template <typename T>
				KERBAL_CONSTEXPR20
				typename get_any_node_type<T>::type *
				obj_pos() KERBAL_NOEXCEPT
				{

#			if __cplusplus > 201703L
#				if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
					if (KERBAL_IS_CONSTANT_EVALUATED()) {
						return this->k_obj_pos<T>(kerbal::type_traits::false_type());
					}
#				endif
#			endif

					return this->k_obj_pos<T>(is_internal_stored_type<T>());
				}

				template <typename T>
				KERBAL_CONSTEXPR20
				const typename get_any_node_type<T>::type *
				k_obj_pos(kerbal::type_traits::false_type) const KERBAL_NOEXCEPT
				{
					typedef typename get_any_node_type<T>::type any_node;
					return static_cast<const any_node *>(this->k_storage.ptr);
				}

				template <typename T>
				const typename get_any_node_type<T>::type *
				k_obj_pos(kerbal::type_traits::true_type) const KERBAL_NOEXCEPT
				{
					typedef typename get_any_node_type<T>::type any_node;
					return reinterpret_cast<const any_node *>(&this->k_storage.buffer);
				}

				template <typename T>
				KERBAL_CONSTEXPR20
				const typename get_any_node_type<T>::type *
				obj_pos() const KERBAL_NOEXCEPT
				{

#			if __cplusplus > 201703L
#				if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
					if (KERBAL_IS_CONSTANT_EVALUATED()) {
						return this->k_obj_pos<T>(kerbal::type_traits::false_type());
					}
#				endif
#			endif

					return this->k_obj_pos<T>(is_internal_stored_type<T>());
				}

				KERBAL_CONSTEXPR20
				void_allocator_type & void_alloc() KERBAL_NOEXCEPT
				{
					return allocator_compress_helper::member();
				}

				KERBAL_CONSTEXPR20
				const void_allocator_type & void_alloc() const KERBAL_NOEXCEPT
				{
					return allocator_compress_helper::member();
				}

				template <typename T>
				KERBAL_CONSTEXPR20
				static manager_table * mtable_of_type() KERBAL_NOEXCEPT
				{
					return &detail::any_manager_collection<T, Allocator, Size, Align>::mtable;
				}

			public:

				KERBAL_CONSTEXPR20
				basic_any() KERBAL_NOEXCEPT :
						k_mtable(mtable_of_type<void>())
				{
				}

				KERBAL_CONSTEXPR20
				basic_any(const basic_any & src) :
						allocator_compress_helper(kerbal::utility::in_place_t(), src.void_alloc()),
						k_mtable(src.k_mtable)
				{
					this->k_mtable->clone(*this, src);
				}

#	if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				basic_any(basic_any && src)
						KERBAL_CONDITIONAL_NOEXCEPT((
								std::is_nothrow_constructible<
										allocator_compress_helper,
										kerbal::utility::in_place_t,
										void_allocator_type &&
								>::value
						)) :
						allocator_compress_helper(kerbal::utility::in_place_t(), kerbal::compatibility::move(src.void_alloc())),
						k_mtable(src.k_mtable)
				{
					this->k_mtable->xfer(*this, kerbal::compatibility::move(src));
				}

#	endif


#	if __cplusplus >= 201103L

				template <typename T, typename = typename kerbal::type_traits::enable_if<
						!kerbal::type_traits::is_same<
								typename kerbal::type_traits::remove_reference<T>::type,
								basic_any
						>::value
				>::type>
				KERBAL_CONSTEXPR20
				explicit basic_any(T && value) :
						k_mtable(NULL)
				{
					typedef typename kerbal::type_traits::remove_reference<T>::type remove_reference;
					typedef typename kerbal::type_traits::remove_const<remove_reference>::type value_type;
					this->k_construct<value_type>(kerbal::utility::forward<T>(value));
					this->k_mtable = mtable_of_type<value_type>();
				}

#	else

				template <typename T>
				KERBAL_CONSTEXPR20
				explicit basic_any(const T & value,
							typename kerbal::type_traits::enable_if<
									!kerbal::type_traits::is_same<T, basic_any>::value,
									int
							>::type = 0
				) :
						k_mtable(NULL)
				{
					typedef T value_type;
					this->k_construct<value_type>(value);
					this->k_mtable = mtable_of_type<value_type>();
				}

#	endif


#	if __cplusplus >= 201103L

				template <typename T, typename ... Args>
				KERBAL_CONSTEXPR20
				explicit basic_any(kerbal::utility::in_place_type_t<T>, Args&& ... args) :
						k_mtable(NULL)
				{
					typedef typename kerbal::type_traits::remove_reference<T>::type remove_reference;
					typedef typename kerbal::type_traits::remove_const<remove_reference>::type value_type;
					this->k_construct<value_type>(kerbal::utility::forward<Args>(args)...);
					this->k_mtable = mtable_of_type<value_type>();
				}

#	else

#			define EMPTY
#			define REMAINF(exp) exp
#			define LEFT_JOIN_COMMA(exp) , exp
#			define TARGS_DECL(i) KERBAL_MACRO_CONCAT(typename Arg, i)
#			define ARGS_DECL(i) KERBAL_MACRO_CONCAT(const Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				template <typename T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
				explicit basic_any(kerbal::utility::in_place_type_t<T> KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) : \
						k_mtable(NULL) \
				{ \
					typedef typename kerbal::type_traits::remove_reference<T>::type remove_reference; \
					typedef typename kerbal::type_traits::remove_const<remove_reference>::type value_type; \
					this->k_construct<value_type>(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i)); \
					this->k_mtable = mtable_of_type<value_type>(); \
				}

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#			undef EMPTY
#			undef REMAINF
#			undef LEFT_JOIN_COMMA
#			undef TARGS_DECL
#			undef ARGS_DECL
#			undef ARGS_USE
#			undef FBODY

#	endif


				KERBAL_CONSTEXPR20
				~basic_any()
				{
					this->k_mtable->destroy(*this);
				}

#	if __cplusplus >= 201103L

				template <typename T>
				KERBAL_CONSTEXPR20
				basic_any& operator=(T && value)
				{
					this->assign(kerbal::utility::forward<T>(value));
					return *this;
				}

#	else

				template <typename T>
				KERBAL_CONSTEXPR20
				basic_any& operator=(const T & value)
				{
					this->assign(value);
					return *this;
				}

#	endif

				KERBAL_CONSTEXPR20
				basic_any& operator=(const basic_any & src)
				{
					this->assign(src);
					return *this;
				}

#	if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				basic_any& operator=(basic_any && src)
						KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(
									kerbal::utility::declthis<basic_any>()->assign(
										kerbal::utility::declval<basic_any&&>()
									)
								)
						)
				{
					this->assign(kerbal::compatibility::move(src));
					return *this;
				}

#	endif


#	if __cplusplus >= 201103L

				template <typename T>
				KERBAL_CONSTEXPR20
				typename kerbal::type_traits::enable_if<
						!kerbal::type_traits::is_same<
							typename kerbal::type_traits::remove_reference<T>::type,
							basic_any
						>::value
				>::type
				assign(T && value)
				{
					typedef typename kerbal::type_traits::remove_reference<T>::type remove_reference;
					typedef typename kerbal::type_traits::remove_const<remove_reference>::type value_type;
					this->k_mtable->destroy(*this);
					this->k_construct<value_type>(value);
					this->k_mtable = mtable_of_type<value_type>();
				}

#	else

				template <typename T>
				KERBAL_CONSTEXPR20
				void assign(const T & value)
				{
					typedef T value_type;
					this->k_mtable->destroy(*this);
					this->k_construct<value_type>(value);
					this->k_mtable = mtable_of_type<value_type>();
				}

#	endif


				KERBAL_CONSTEXPR20
				void assign(const basic_any & src)
				{
					this->k_mtable->destroy(*this);
					this->k_mtable = src.k_mtable;
					this->k_mtable->clone(*this, src);
				}

#	if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void assign(basic_any && src) KERBAL_NOEXCEPT
				{
					this->k_mtable->destroy(*this);
					this->k_mtable = src.k_mtable;
					this->k_mtable->xfer(*this, kerbal::compatibility::move(src));
				}

#	endif


#	if __cplusplus >= 201103L

				template <typename T, typename ... Args>
				KERBAL_CONSTEXPR20
				void emplace(Args&& ... args)
				{
					typedef typename kerbal::type_traits::remove_reference<T>::type remove_reference;
					typedef typename kerbal::type_traits::remove_const<remove_reference>::type value_type;
					this->k_mtable->destroy(*this);
					this->k_construct<value_type>(kerbal::utility::forward<Args>(args)...);
					this->k_mtable = mtable_of_type<value_type>();
				}

#	else

#			define EMPTY
#			define REMAINF(exp) exp
#			define LEFT_JOIN_COMMA(exp) , exp
#			define TARGS_DECL(i) KERBAL_MACRO_CONCAT(typename Arg, i)
#			define ARGS_DECL(i) KERBAL_MACRO_CONCAT(const Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				template <typename T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
				void emplace(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
				{ \
					typedef typename kerbal::type_traits::remove_reference<T>::type remove_reference; \
					typedef typename kerbal::type_traits::remove_const<remove_reference>::type value_type; \
					this->k_mtable->destroy(*this); \
					this->k_construct<value_type>(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i)); \
					this->k_mtable = mtable_of_type<value_type>(); \
				}

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#			undef EMPTY
#			undef REMAINF
#			undef LEFT_JOIN_COMMA
#			undef TARGS_DECL
#			undef ARGS_DECL
#			undef ARGS_USE
#			undef FBODY

#	endif

				KERBAL_CONSTEXPR20
				void reset() KERBAL_NOEXCEPT
				{
					this->k_mtable->destroy(*this);
					this->k_mtable = mtable_of_type<void>();
				}

				KERBAL_CONSTEXPR20
				void swap(basic_any & with) KERBAL_NOEXCEPT
				{
					union storage temp_storage;
					this->k_mtable->swap_xfer_to_tmp(*this, temp_storage);
					manager_table * mtable_tmp = this->k_mtable;

					this->k_mtable = with.k_mtable;
					this->k_mtable->swap_xfer_from_other(*this, with);

					with.k_mtable = mtable_tmp;
					with.k_mtable->swap_xfer_from_tmp(with, temp_storage);
				}

				KERBAL_CONSTEXPR20
				const std::type_info & type() const KERBAL_NOEXCEPT
				{
					return this->k_mtable->type_info();
				}

				template <typename T>
				KERBAL_CONSTEXPR20
				bool contains_type() const KERBAL_NOEXCEPT
				{
					return this->k_mtable == mtable_of_type<T>();
				}

				KERBAL_CONSTEXPR20
				bool has_value() const KERBAL_NOEXCEPT
				{
					return !this->contains_type<void>();
				}

				template <typename T>
				KERBAL_CONSTEXPR20
				T* ignored_get_pointer() KERBAL_NOEXCEPT
				{
					typedef typename kerbal::type_traits::remove_const<T>::type value_type;
					return &(this->template obj_pos<value_type>()->value);
				}

				template <typename T>
				KERBAL_CONSTEXPR20
				const T* ignored_get_pointer() const KERBAL_NOEXCEPT
				{
					typedef typename kerbal::type_traits::remove_const<T>::type value_type;
					return &(this->template obj_pos<value_type>()->value);
				}

				template <typename T>
				KERBAL_CONSTEXPR20
				T* get_pointer() KERBAL_NOEXCEPT
				{
					typedef typename kerbal::type_traits::remove_const<T>::type value_type;

					return this->template contains_type<value_type>() ?
						   &(this->template obj_pos<value_type>()->value) :
						   NULL;
				}

				template <typename T>
				KERBAL_CONSTEXPR20
				const T* get_pointer() const KERBAL_NOEXCEPT
				{
					typedef typename kerbal::type_traits::remove_const<T>::type value_type;

					return this->template contains_type<value_type>() ?
						   &(this->template obj_pos<value_type>()->value) :
						   NULL;
				}

				template <typename T>
				KERBAL_CONSTEXPR20
				T ignored_get() KERBAL_REFERENCE_OVERLOAD_TAG
				{
					typedef typename kerbal::type_traits::remove_reference<T>::type remove_reference;
					typedef typename kerbal::type_traits::remove_const<remove_reference>::type value_type;

					return this->template obj_pos<value_type>()->value;
				}

				template <typename T>
				KERBAL_CONSTEXPR20
				typename kerbal::type_traits::conditional<
					kerbal::type_traits::is_reference<T>::value,
					const T,
					T
				>::type
				ignored_get() KERBAL_CONST_REFERENCE_OVERLOAD_TAG
				{
					typedef typename kerbal::type_traits::remove_reference<T>::type remove_reference;
					typedef typename kerbal::type_traits::remove_const<remove_reference>::type value_type;

					return this->template obj_pos<value_type>()->value;
				}

				template <typename T>
				KERBAL_CONSTEXPR20
				T get() KERBAL_REFERENCE_OVERLOAD_TAG
				{
					typedef typename kerbal::type_traits::remove_reference<T>::type remove_reference;
					typedef typename kerbal::type_traits::remove_const<remove_reference>::type value_type;

					if (!this->template contains_type<value_type>()) {
						kerbal::utility::throw_this_exception_helper<kerbal::any::bad_any_cast>::throw_this_exception(this->type(), typeid(value_type));
					}
					return this->template obj_pos<value_type>()->value;
				}

				template <typename T>
				KERBAL_CONSTEXPR20
				typename kerbal::type_traits::conditional<
					kerbal::type_traits::is_reference<T>::value,
					const T,
					T
				>::type
				get() KERBAL_CONST_REFERENCE_OVERLOAD_TAG
				{
					typedef typename kerbal::type_traits::remove_reference<T>::type remove_reference;
					typedef typename kerbal::type_traits::remove_const<remove_reference>::type value_type;

					if (!this->template contains_type<value_type>()) {
						kerbal::utility::throw_this_exception_helper<kerbal::any::bad_any_cast>::throw_this_exception(this->type(), typeid(value_type));
					}
					return this->template obj_pos<value_type>()->value;
				}

#	if __cplusplus >= 201103L

				template <typename T>
				KERBAL_CONSTEXPR20
				T ignored_get() &&
				{
					KERBAL_STATIC_ASSERT(!kerbal::type_traits::is_lvalue_reference<T>::value, "T shouldn't be lvalue reference");

					typedef typename kerbal::type_traits::remove_reference<T>::type remove_reference;
					typedef typename kerbal::type_traits::remove_const<remove_reference>::type value_type;

					return kerbal::compatibility::move(this->template obj_pos<value_type>()->value);
				}

				template <typename T>
				KERBAL_CONSTEXPR20
				T get() &&
				{
					KERBAL_STATIC_ASSERT(!kerbal::type_traits::is_lvalue_reference<T>::value, "T shouldn't be lvalue reference");

					typedef typename kerbal::type_traits::remove_reference<T>::type remove_reference;
					typedef typename kerbal::type_traits::remove_const<remove_reference>::type value_type;

					if (!this->template contains_type<value_type>()) {
						kerbal::utility::throw_this_exception_helper<kerbal::any::bad_any_cast>::throw_this_exception(this->type(), typeid(value_type));
					}
					return kerbal::compatibility::move(this->template obj_pos<value_type>()->value);
				}

#	endif

			private:

#	if __cplusplus >= 201103L

				template <typename T, typename ... Args>
				KERBAL_CONSTEXPR20
				void k_construct_impl(kerbal::type_traits::false_type, Args&& ... args)
				{
					typedef T value_type;
					typedef typename get_any_node_type<value_type>::type any_node;
					typedef typename kerbal::memory::allocator_traits<void_allocator_type>::template rebind_alloc<any_node>::other allocator;
					typedef kerbal::memory::allocator_traits<allocator> allocator_traits;
					allocator alloc(this->void_alloc());
					any_node * stored_pos = allocator_traits::allocate(alloc, 1);
#			if __cpp_exceptions
					try {
#			endif
						allocator_traits::construct(alloc, stored_pos, kerbal::utility::in_place_t(), kerbal::utility::forward<Args>(args)...);
#			if __cpp_exceptions
					} catch (...) {
						allocator_traits::deallocate(alloc, stored_pos, 1);
						throw;
					}
#			endif
					this->k_storage.ptr = static_cast<any_node_base *>(stored_pos);
				}

				template <typename T, typename ... Args>
				void k_construct_impl(kerbal::type_traits::true_type, Args&& ... args)
				{
					typedef T value_type;
					typedef typename get_any_node_type<value_type>::type any_node;
					typedef typename kerbal::memory::allocator_traits<void_allocator_type>::template rebind_alloc<any_node>::other allocator;
					typedef kerbal::memory::allocator_traits<allocator> allocator_traits;
					allocator alloc(this->void_alloc());

					any_node * stored_pos = reinterpret_cast<any_node *>(&this->k_storage.buffer);
					allocator_traits::construct(alloc, stored_pos, kerbal::utility::in_place_t(), kerbal::utility::forward<Args>(args)...);
				}

				template <typename T, typename ... Args>
				KERBAL_CONSTEXPR20
				void k_construct(Args&& ... args)
				{
					typedef typename kerbal::type_traits::remove_const<T>::type value_type;

#			if __cplusplus > 201703L
#				if KERBAL_HAS_IS_CONSTANT_EVALUATED_SUPPORT
					if (KERBAL_IS_CONSTANT_EVALUATED()) {
						this->k_construct_impl<value_type>(kerbal::type_traits::false_type(), kerbal::utility::forward<Args>(args)...);
						return;
					}
#				endif
#			endif

					this->k_construct_impl<value_type>(is_internal_stored_type<value_type>(), kerbal::utility::forward<Args>(args)...);
				}

#	else

#			define EMPTY
#			define REMAINF(exp) exp
#			define LEFT_JOIN_COMMA(exp) , exp
#			define TARGS_DECL(i) KERBAL_MACRO_CONCAT(typename Arg, i)
#			define ARGS_DECL(i) KERBAL_MACRO_CONCAT(const Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)

#		if __cpp_exceptions

#			define CONSTRUCT_EXTERNAL(i) \
				template <typename T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
				void k_construct_impl(kerbal::type_traits::false_type KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
				{ \
					typedef T value_type; \
					typedef typename get_any_node_type<value_type>::type any_node; \
					typedef typename kerbal::memory::allocator_traits<void_allocator_type>::template rebind_alloc<any_node>::other allocator; \
					typedef kerbal::memory::allocator_traits<allocator> allocator_traits; \
					allocator alloc(this->void_alloc()); \
 \
					any_node * stored_pos = allocator_traits::allocate(alloc, 1); \
					try { \
						allocator_traits::construct(alloc, stored_pos, kerbal::utility::in_place_t() KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
					} catch (...) { \
						allocator_traits::deallocate(alloc, stored_pos, 1); \
						throw; \
					} \
					this->k_storage.ptr = static_cast<any_node_base *>(stored_pos); \
				}

#		else

#			define CONSTRUCT_EXTERNAL(i) \
				template <typename T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
				void k_construct_impl(kerbal::type_traits::false_type KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
				{ \
					typedef T value_type; \
					typedef typename get_any_node_type<value_type>::type any_node; \
					typedef typename kerbal::memory::allocator_traits<void_allocator_type>::template rebind_alloc<any_node>::other allocator; \
					typedef kerbal::memory::allocator_traits<allocator> allocator_traits; \
					allocator alloc(this->void_alloc()); \
 \
					any_node * stored_pos = allocator_traits::allocate(alloc, 1); \
					allocator_traits::construct(alloc, stored_pos, kerbal::utility::in_place_t() KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
					this->k_storage.ptr = static_cast<any_node_base *>(stored_pos); \
				}

#		endif


#			define FBODY(i) \
				CONSTRUCT_EXTERNAL(i) \
 \
				template <typename T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
				void k_construct_impl(kerbal::type_traits::true_type KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
				{ \
					typedef T value_type; \
					typedef typename get_any_node_type<value_type>::type any_node; \
					typedef typename kerbal::memory::allocator_traits<void_allocator_type>::template rebind_alloc<any_node>::other allocator; \
					typedef kerbal::memory::allocator_traits<allocator> allocator_traits; \
					allocator alloc(this->void_alloc()); \
 \
					any_node * stored_pos = reinterpret_cast<any_node *>(&this->k_storage.buffer); \
					allocator_traits::construct(alloc, stored_pos, kerbal::utility::in_place_t() KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				} \
 \
				template <typename T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
				void k_construct(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
				{ \
					typedef T value_type; \
					this->k_construct_impl<value_type>(is_internal_stored_type<value_type>() KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				}


				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#			undef EMPTY
#			undef REMAINF
#			undef LEFT_JOIN_COMMA
#			undef TARGS_DECL
#			undef ARGS_DECL
#			undef ARGS_USE
#			undef CONSTRUCT_EXTERNAL
#			undef FBODY

#	endif

		};

		template <typename T, typename Allocator, std::size_t Size, std::size_t Align>
		KERBAL_CONSTEXPR20
		T* any_cast(basic_any<Allocator, Size, Align> * operand) KERBAL_NOEXCEPT
		{
			return operand->template get_pointer<T>();
		}

		template <typename T, typename Allocator, std::size_t Size, std::size_t Align>
		KERBAL_CONSTEXPR20
		const T* any_cast(const basic_any<Allocator, Size, Align> * operand) KERBAL_NOEXCEPT
		{
			return operand->template get_pointer<T>();
		}

		template <typename T, typename Allocator, std::size_t Size, std::size_t Align>
		KERBAL_CONSTEXPR20
		T any_cast(basic_any<Allocator, Size, Align> & operand)
		{
			return operand.template get<T>();
		}

		template <typename T, typename Allocator, std::size_t Size, std::size_t Align>
		KERBAL_CONSTEXPR20
		const T any_cast(const basic_any<Allocator, Size, Align> & operand)
		{
			return operand.template get<T>();
		}

#	if __cplusplus >= 201103L

		template <typename T, typename Allocator, std::size_t Size, std::size_t Align>
		KERBAL_CONSTEXPR20
		T any_cast(basic_any<Allocator, Size, Align> && operand)
		{
			return kerbal::compatibility::move(operand).template get<T>();
		}

#	endif

	} // namespace any

	namespace algorithm
	{

		template <typename Allocator, std::size_t Size, std::size_t Align>
		KERBAL_CONSTEXPR20
		void swap(kerbal::any::basic_any<Allocator, Size, Align> & a, kerbal::any::basic_any<Allocator, Size, Align> & b)
				KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
		{
			a.swap(b);
		}

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <typename Allocator, std::size_t Size, std::size_t Align>
	KERBAL_CONSTEXPR20
	void swap(kerbal::any::basic_any<Allocator, Size, Align> & a, kerbal::any::basic_any<Allocator, Size, Align> & b)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END

#endif // KERBAL_ANY_ANY_HPP
