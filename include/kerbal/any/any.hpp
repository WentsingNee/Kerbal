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

#include <kerbal/any/fwd/any.fwd.hpp>

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compatibility/alignof.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/method_overload_tag.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/memory/any_storage.hpp>
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
		struct is_any_embedded_stored_type :
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

			template <std::size_t Size, std::size_t Align, typename Allocator>
			struct any_manager_table
			{
					typedef kerbal::any::basic_any<Size, Align, Allocator> any;
					typedef void (*destroy_entry_type)(any &) KERBAL_NOEXCEPT17;
					typedef void (*clone_entry_type)(any &, const any &);
#	if __cplusplus >= 201103L
					typedef void (*xfer_entry_type)(any &, any &&) KERBAL_NOEXCEPT17;
#	endif
					typedef void (*swap_out_entry_type)(any &, any &) KERBAL_NOEXCEPT17;
					typedef void (*swap_entry_type)(any &, any &) KERBAL_NOEXCEPT17;
					typedef const std::type_info & (*type_info_entry_type)() KERBAL_NOEXCEPT17;


					destroy_entry_type					destroy;
					clone_entry_type					clone;
#	if __cplusplus >= 201103L
					xfer_entry_type						xfer;
#	endif
					swap_out_entry_type					swap_out;
					swap_entry_type						swap;
					type_info_entry_type				type_info;


					KERBAL_CONSTEXPR
					any_manager_table(
								  destroy_entry_type					destroy,
								  clone_entry_type						clone,
#	if __cplusplus >= 201103L
								  xfer_entry_type						xfer,
#	endif
								  swap_out_entry_type					swap_out,
								  swap_entry_type						swap,
								  type_info_entry_type					type_info
					) KERBAL_NOEXCEPT :
							destroy(destroy),
							clone(clone),
#	if __cplusplus >= 201103L
							xfer(xfer),
#	endif
							swap_out(swap_out),
							swap(swap),
							type_info(type_info)
					{
					}

			};

			template <typename T, std::size_t Size, std::size_t Align, typename Allocator>
			struct any_manager_collection;

			template <std::size_t Size, std::size_t Align, typename Allocator>
			struct any_manager_collection<void, Size, Align, Allocator>
			{
				private:
					typedef kerbal::any::basic_any<Size, Align, Allocator>					any;
					typedef typename any::void_allocator_type								void_allocator_type;
					typedef kerbal::memory::allocator_traits<void_allocator_type>			void_allocator_traits;
					typedef any_manager_table<Size, Align, Allocator>						manager_table;

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
					static void swap_out(any & /*self*/, any & /*out*/) KERBAL_NOEXCEPT
					{
					}

					KERBAL_CONSTEXPR20
					static void swap(any & /*self*/, any & /*with*/) KERBAL_NOEXCEPT
					{
					}

					KERBAL_CONSTEXPR20
					static const std::type_info & type_info() KERBAL_NOEXCEPT
					{
						return typeid(void);
					}

				public:

#		if __cplusplus >= 201103L
					KERBAL_CONSTEXPR
#			if __cplusplus >= 201703L
					inline
#			endif
					static const manager_table mtable = manager_table(destroy, clone, xfer, swap_out, swap, type_info);
#		else
					static const manager_table mtable;
#		endif

			};


#	if __cplusplus >= 201103L

#		if __cplusplus < 201703L
			template <std::size_t Size, std::size_t Align, typename Allocator>
			KERBAL_CONSTEXPR
			const typename any_manager_collection<void, Size, Align, Allocator>::manager_table
			any_manager_collection<void, Size, Align, Allocator>::mtable;
#		endif

#	else

			template <std::size_t Size, std::size_t Align, typename Allocator>
			const typename any_manager_collection<void, Size, Align, Allocator>::manager_table
			any_manager_collection<void, Size, Align, Allocator>::mtable(destroy, clone, swap_out, swap, type_info);

#	endif

			template <typename T, std::size_t Size, std::size_t Align, typename Allocator>
			struct any_manager_collection
			{
				private:
					typedef kerbal::any::basic_any<Size, Align, Allocator>								any;
					typedef kerbal::memory::detail::any_node<T>											any_node;
					typedef typename any::void_allocator_type											void_allocator_type;
					typedef kerbal::memory::allocator_traits<void_allocator_type>						void_allocator_traits;
					typedef typename void_allocator_traits::template rebind_alloc<any_node>::other		allocator_type;
					typedef kerbal::memory::allocator_traits<allocator_type>							allocator_traits;
					typedef is_any_embedded_stored_type<T, Size, Align>									is_embedded_stored_type;
					typedef any_manager_table<Size, Align, Allocator>									manager_table;

					KERBAL_STATIC_ASSERT(!kerbal::type_traits::is_const<T>::value, "T couldn't be const");
					KERBAL_STATIC_ASSERT(!kerbal::type_traits::is_reference<T>::value, "T couldn't be reference");

					KERBAL_CONSTEXPR20
					static void destroy(any & self) KERBAL_NOEXCEPT
					{
						self.k_storage.template destroy<T>(is_embedded_stored_type(), self.void_alloc());
					}

					KERBAL_CONSTEXPR20
					static void clone(any & self, const any & ano)
					{
						const any_node * p_to_src = ano.template obj_pos<T>();
						self.k_storage.template construct<T>(is_embedded_stored_type(), self.void_alloc(), p_to_src->value);
					}

#	if __cplusplus >= 201103L

					KERBAL_CONSTEXPR20
					static void xfer(any & self, any && ano) KERBAL_NOEXCEPT
					{
						self.k_storage.template xfer<T>(is_embedded_stored_type(), self.void_alloc(), kerbal::compatibility::move(ano.k_storage), ano.void_alloc());
					}

#	endif

					KERBAL_CONSTEXPR20
					static void swap_out(any & self, any & out) KERBAL_NOEXCEPT
					{
						out.k_storage.template xfer<T>(is_embedded_stored_type(), out.void_alloc(), kerbal::compatibility::to_xvalue(self.k_storage), self.void_alloc());
					}

					KERBAL_CONSTEXPR20
					static void swap(any & self, any & with) KERBAL_NOEXCEPT
					{
						typename any::any_storage_type tmp;

						// self -> tmp
						tmp.template xfer<T>(is_embedded_stored_type(), self.void_alloc(), kerbal::compatibility::to_xvalue(self.k_storage), self.void_alloc());

						// with -> self
						with.k_mtable->swap_out(with, self);

						// tmp -> with
						with.k_storage.template xfer<T>(is_embedded_stored_type(), with.void_alloc(), kerbal::compatibility::to_xvalue(tmp), with.void_alloc());
					}

					KERBAL_CONSTEXPR20
					static const std::type_info & type_info() KERBAL_NOEXCEPT
					{
						return typeid(T);
					}

				public:

#		if __cplusplus >= 201103L
					KERBAL_CONSTEXPR
#			if __cplusplus >= 201703L
					inline
#			endif
					static const manager_table mtable = manager_table(destroy, clone, xfer, swap_out, swap, type_info);
#		else
					static const manager_table mtable;
#		endif

			};


#	if __cplusplus >= 201103L

#		if __cplusplus < 201703L
			template <typename T, std::size_t Size, std::size_t Align, typename Allocator>
			KERBAL_CONSTEXPR
			const typename any_manager_collection<T, Size, Align, Allocator>::manager_table
			any_manager_collection<T, Size, Align, Allocator>::mtable;
#		endif

#	else

			template <typename T, std::size_t Size, std::size_t Align, typename Allocator>
			const typename any_manager_collection<T, Size, Align, Allocator>::manager_table
			any_manager_collection<T, Size, Align, Allocator>::mtable(destroy, clone, swap_out, swap, type_info);

#	endif

		} // namespace detail


		template <std::size_t Size, std::size_t Align, typename Allocator>
		class basic_any :
				private kerbal::utility::member_compress_helper<Allocator>
		{
			private:

				friend struct detail::any_manager_table<Size, Align, Allocator>;

				template <typename T, std::size_t Size2, std::size_t Align2, typename Allocator2>
				friend struct kerbal::any::detail::any_manager_collection;

				template <typename T, std::size_t Size2, std::size_t Align2, typename Allocator2>
				KERBAL_CONSTEXPR20
				friend
				T* any_cast(basic_any<Size2, Align2, Allocator2> * operand) KERBAL_NOEXCEPT;

				template <typename T, std::size_t Size2, std::size_t Align2, typename Allocator2>
				KERBAL_CONSTEXPR20
				friend
				const T* any_cast(const basic_any<Size2, Align2, Allocator2> * operand) KERBAL_NOEXCEPT;

				template <typename T>
				struct is_embedded_stored_type :
						is_any_embedded_stored_type<T, Size, Align>
				{
				};

				typedef kerbal::memory::detail::any_node_base			any_node_base;

				template <typename T>
				struct get_any_node_type
				{
						typedef kerbal::memory::detail::any_node<T> type;
				};

				typedef const detail::any_manager_table<Size, Align, Allocator>		manager_table;
				typedef kerbal::utility::member_compress_helper<Allocator>			allocator_compress_helper;
				typedef kerbal::memory::any_storage<Size, Align>					any_storage_type;

			public:
				typedef Allocator void_allocator_type;

			private:

				any_storage_type k_storage;
				manager_table * k_mtable;

				template <typename T>
				KERBAL_CONSTEXPR20
				typename get_any_node_type<T>::type *
				obj_pos() KERBAL_NOEXCEPT
				{
					return this->k_storage.template obj_pos<T>(is_embedded_stored_type<T>());
				}

				template <typename T>
				KERBAL_CONSTEXPR20
				const typename get_any_node_type<T>::type *
				obj_pos() const KERBAL_NOEXCEPT
				{
					return this->k_storage.template obj_pos<T>(is_embedded_stored_type<T>());
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
					return &detail::any_manager_collection<T, Size, Align, Allocator>::mtable;
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
					src.k_mtable = mtable_of_type<void>();
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
					this->k_storage.template construct<value_type>(is_embedded_stored_type<value_type>(), this->void_alloc(), kerbal::utility::forward<T>(value));
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
					this->k_storage.template construct<value_type>(is_embedded_stored_type<value_type>(), this->void_alloc(), value);
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
					this->k_storage.template construct<value_type>(is_embedded_stored_type<value_type>(), this->void_alloc(), kerbal::utility::forward<Args>(args)...);
					this->k_mtable = mtable_of_type<value_type>();
				}

#	else

#			define EMPTY
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
					this->k_storage.template construct<value_type>(is_embedded_stored_type<value_type>(), this->void_alloc() KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
					this->k_mtable = mtable_of_type<value_type>(); \
				}

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#			undef EMPTY
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
					this->k_storage.template construct<value_type>(is_embedded_stored_type<value_type>(), this->void_alloc(), value);
					this->k_mtable = mtable_of_type<value_type>();
				}

#	else

				template <typename T>
				KERBAL_CONSTEXPR20
				void assign(const T & value)
				{
					typedef T value_type;
					this->k_mtable->destroy(*this);
					this->k_storage.template construct<value_type>(is_embedded_stored_type<value_type>(), this->void_alloc(), value);
					this->k_mtable = mtable_of_type<value_type>();
				}

#	endif


				KERBAL_CONSTEXPR20
				void assign(const basic_any & src)
				{
					if (this == &src) {
						return;
					}
					this->k_mtable->destroy(*this);
					this->k_mtable = src.k_mtable;
					this->k_mtable->clone(*this, src);
				}

#	if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void assign(basic_any && src) KERBAL_NOEXCEPT
				{
					if (this == &src) {
						return;
					}
					this->k_mtable->destroy(*this);
					this->k_mtable = src.k_mtable;
					this->k_mtable->xfer(*this, kerbal::compatibility::move(src));
					src.k_mtable = mtable_of_type<void>();
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
					this->k_storage.template construct<value_type>(is_embedded_stored_type<value_type>(), this->void_alloc(), kerbal::utility::forward<Args>(args)...);
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
					this->k_storage.template construct<value_type>(is_embedded_stored_type<value_type>(), this->void_alloc() KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
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
					this->k_mtable->swap(*this, with);
					kerbal::algorithm::swap(this->k_mtable, with.k_mtable);
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

		};

		template <typename T, std::size_t Size, std::size_t Align, typename Allocator>
		KERBAL_CONSTEXPR20
		T* any_cast(basic_any<Size, Align, Allocator> * operand) KERBAL_NOEXCEPT
		{
			return operand->template get_pointer<T>();
		}

		template <typename T, std::size_t Size, std::size_t Align, typename Allocator>
		KERBAL_CONSTEXPR20
		const T* any_cast(const basic_any<Size, Align, Allocator> * operand) KERBAL_NOEXCEPT
		{
			return operand->template get_pointer<T>();
		}

		template <typename T, std::size_t Size, std::size_t Align, typename Allocator>
		KERBAL_CONSTEXPR20
		T any_cast(basic_any<Size, Align, Allocator> & operand)
		{
			return operand.template get<T>();
		}

		template <typename T, std::size_t Size, std::size_t Align, typename Allocator>
		KERBAL_CONSTEXPR20
		const T any_cast(const basic_any<Size, Align, Allocator> & operand)
		{
			return operand.template get<T>();
		}

#	if __cplusplus >= 201103L

		template <typename T, std::size_t Size, std::size_t Align, typename Allocator>
		KERBAL_CONSTEXPR20
		T any_cast(basic_any<Size, Align, Allocator> && operand)
		{
			return kerbal::compatibility::move(operand).template get<T>();
		}

#	endif

	} // namespace any

	namespace algorithm
	{

		template <std::size_t Size, std::size_t Align, typename Allocator>
		KERBAL_CONSTEXPR20
		void swap(kerbal::any::basic_any<Size, Align, Allocator> & a, kerbal::any::basic_any<Size, Align, Allocator> & b)
				KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
		{
			a.swap(b);
		}

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <std::size_t Size, std::size_t Align, typename Allocator>
	KERBAL_CONSTEXPR20
	void swap(kerbal::any::basic_any<Size, Align, Allocator> & a, kerbal::any::basic_any<Size, Align, Allocator> & b)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END

#endif // KERBAL_ANY_ANY_HPP
