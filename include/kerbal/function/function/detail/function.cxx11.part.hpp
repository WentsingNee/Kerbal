/**
 * @file       function.cxx11.part.hpp
 * @brief
 * @date       2022-06-12
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_FUNCTION_FUNCTION_DETAIL_FUNCTION_CXX11_PART_HPP
#define KERBAL_FUNCTION_FUNCTION_DETAIL_FUNCTION_CXX11_PART_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/function/function/function.fwd.hpp>
#include <kerbal/function/bad_function_call.hpp>
#include <kerbal/function/bad_function_cast.hpp>

#include <kerbal/function/detail/is_function_embedded_stored_type.hpp>

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/method_overload_tag.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/config/compiler_id.hpp>
#include <kerbal/function/invoke.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/memory/any_storage.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/is_const.hpp>
#include <kerbal/type_traits/is_reference.hpp>
#include <kerbal/type_traits/is_same.hpp>
#include <kerbal/type_traits/remove_const.hpp>
#include <kerbal/type_traits/remove_reference.hpp>
#include <kerbal/utility/declval.hpp>
#include <kerbal/utility/in_place.hpp>
#include <kerbal/utility/member_compress_helper.hpp>
#include <kerbal/utility/throw_this_exception.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/is_lvalue_reference.hpp>
#	include <kerbal/type_traits/is_nothrow_constructible.hpp>
#	include <kerbal/utility/forward.hpp>
#endif

#include <cstddef>



#define KERBAL_FUNCTION_TYPE_POLICY_DISABLE 0
#define KERBAL_FUNCTION_TYPE_POLICY_POINTER 1
#define KERBAL_FUNCTION_TYPE_POLICY_FUNCTION 2

#ifndef KERBAL_FUNCTION_TYPE_POLICY

#	if !defined(__cpp_rtti) && !defined(__GXX_RTTI)
#		define KERBAL_FUNCTION_TYPE_POLICY KERBAL_FUNCTION_TYPE_POLICY_DISABLE
#	elif KERBAL_COMPILER_ID == KERBAL_COMPILER_ID_MSVC
#		define KERBAL_FUNCTION_TYPE_POLICY KERBAL_FUNCTION_TYPE_POLICY_FUNCTION
#	else
#		define KERBAL_FUNCTION_TYPE_POLICY KERBAL_FUNCTION_TYPE_POLICY_POINTER
#	endif

#endif

#if KERBAL_FUNCTION_TYPE_POLICY != KERBAL_FUNCTION_TYPE_POLICY_DISABLE
#	include <typeinfo>
#endif


namespace kerbal
{

	namespace function
	{

		namespace detail
		{

#	if KERBAL_FUNCTION_TYPE_POLICY == KERBAL_FUNCTION_TYPE_POLICY_POINTER
#		define KERBAL_FUNCTION_MANAGER_TABLE_TYPE_TYPEDEF	typedef const std::type_info * type_info_entry_type
#	elif KERBAL_FUNCTION_TYPE_POLICY == KERBAL_FUNCTION_TYPE_POLICY_FUNCTION
#		define KERBAL_FUNCTION_MANAGER_TABLE_TYPE_TYPEDEF	typedef const std::type_info & (*type_info_entry_type)() KERBAL_NOEXCEPT17
#	else
#		define KERBAL_FUNCTION_MANAGER_TABLE_TYPE_TYPEDEF
#	endif

#	if KERBAL_FUNCTION_TYPE_POLICY != KERBAL_FUNCTION_TYPE_POLICY_DISABLE
#		define KERBAL_FUNCTION_MANAGER_TABLE_TYPE_MEMDEF	type_info_entry_type				type_info
#	else
#		define KERBAL_FUNCTION_MANAGER_TABLE_TYPE_MEMDEF
#	endif

#	if KERBAL_FUNCTION_TYPE_POLICY != KERBAL_FUNCTION_TYPE_POLICY_DISABLE
#		define KERBAL_FUNCTION_MANAGER_TABLE_TYPE_CONSTRUCTOR_ARG	, type_info_entry_type					type_info
#	else
#		define KERBAL_FUNCTION_MANAGER_TABLE_TYPE_CONSTRUCTOR_ARG
#	endif

#	if KERBAL_FUNCTION_TYPE_POLICY != KERBAL_FUNCTION_TYPE_POLICY_DISABLE
#		define KERBAL_FUNCTION_MANAGER_TABLE_TYPE_ILIST	, type_info(type_info)
#	else
#		define KERBAL_FUNCTION_MANAGER_TABLE_TYPE_ILIST
#	endif


			template <std::size_t Size, std::size_t Align, typename Allocator, typename Ret, typename ... TArgs>
			struct function_manager_table
			{
					typedef kerbal::function::basic_function<Ret(TArgs...), Size, Align, Allocator> function;
					typedef Ret (*invoke_entry_type)(const function & self, TArgs...);
					typedef void (*destroy_entry_type)(function &) KERBAL_NOEXCEPT17;
					typedef void (*clone_entry_type)(function &, const function &);
#	if __cplusplus >= 201103L
					typedef void (*xfer_entry_type)(function &, function &&) KERBAL_NOEXCEPT17;
#	endif
					typedef void (*swap_out_entry_type)(function &, function &) KERBAL_NOEXCEPT17;
					typedef void (*swap_entry_type)(function &, function &) KERBAL_NOEXCEPT17;
					KERBAL_FUNCTION_MANAGER_TABLE_TYPE_TYPEDEF;


					invoke_entry_type					invoke;
					destroy_entry_type					destroy;
					clone_entry_type					clone;
#	if __cplusplus >= 201103L
					xfer_entry_type						xfer;
#	endif
					swap_out_entry_type					swap_out;
					swap_entry_type						swap;
					KERBAL_FUNCTION_MANAGER_TABLE_TYPE_MEMDEF;


					KERBAL_CONSTEXPR
					function_manager_table(
						  invoke_entry_type invoke
						, destroy_entry_type destroy
						, clone_entry_type clone
#	if __cplusplus >= 201103L
						, xfer_entry_type xfer
#	endif
						, swap_out_entry_type swap_out, swap_entry_type swap
						KERBAL_FUNCTION_MANAGER_TABLE_TYPE_CONSTRUCTOR_ARG
					) KERBAL_NOEXCEPT
						: invoke(invoke)
						, destroy(destroy)
						, clone(clone)
#	if __cplusplus >= 201103L
						, xfer(xfer)
#	endif
						, swap_out(swap_out)
						, swap(swap)
						KERBAL_FUNCTION_MANAGER_TABLE_TYPE_ILIST
					{
					}

			};

			template <
				typename T, std::size_t Size, std::size_t Align, typename Allocator,
				typename Ret, typename ... TArgs
			>
			struct function_manager_collection;

			template <std::size_t Size, std::size_t Align, typename Allocator, typename Ret, typename ... TArgs>
			struct function_manager_collection<void, Size, Align, Allocator, Ret, TArgs...>
			{
				private:
					typedef kerbal::function::basic_function<Ret(TArgs...), Size, Align, Allocator>		function;
					typedef typename function::void_allocator_type										void_allocator_type;
					typedef kerbal::memory::allocator_traits<void_allocator_type>						void_allocator_traits;
					typedef function_manager_table<Size, Align, Allocator, Ret, TArgs...>				manager_table;

					KERBAL_CONSTEXPR20
					static void destroy(function & /*self*/) KERBAL_NOEXCEPT
					{
					}

					KERBAL_CONSTEXPR20
					static void clone(function & /*self*/, const function & /*ano*/) KERBAL_NOEXCEPT
					{
					}

#	if __cplusplus >= 201103L

					KERBAL_CONSTEXPR20
					static void xfer(function & /*self*/, function && /*ano*/) KERBAL_NOEXCEPT
					{
					}

#	endif

					KERBAL_CONSTEXPR20
					static void swap_out(function & /*self*/, function & /*out*/) KERBAL_NOEXCEPT
					{
					}

					KERBAL_CONSTEXPR20
					static void swap(function & self, function & with) KERBAL_NOEXCEPT
					{
						// with -> self
						with.k_mtable->swap_out(with, self);
					}

#	if KERBAL_FUNCTION_TYPE_POLICY == KERBAL_FUNCTION_TYPE_POLICY_FUNCTION

					KERBAL_CONSTEXPR20
					static const std::type_info & type_info() KERBAL_NOEXCEPT
					{
						return typeid(void);
					}

#	endif

				public:

#	if KERBAL_FUNCTION_TYPE_POLICY == KERBAL_FUNCTION_TYPE_POLICY_DISABLE
#		define TYPE_INFO_ENTRY
#	elif KERBAL_FUNCTION_TYPE_POLICY == KERBAL_FUNCTION_TYPE_POLICY_POINTER
#		define TYPE_INFO_ENTRY , &typeid(void)
#	elif KERBAL_FUNCTION_TYPE_POLICY == KERBAL_FUNCTION_TYPE_POLICY_FUNCTION
#		define TYPE_INFO_ENTRY , type_info
#	endif

#		if __cplusplus >= 201103L
					KERBAL_CONSTEXPR
#			if __cplusplus >= 201703L
					inline
#			endif
					static const manager_table mtable = manager_table(NULL, destroy, clone, xfer, swap_out, swap TYPE_INFO_ENTRY);
#		else
					static const manager_table mtable;
#		endif

			};


#	if __cplusplus >= 201103L

#		if __cplusplus < 201703L
			template <
				std::size_t Size, std::size_t Align, typename Allocator,
				typename Ret, typename ... TArgs
			>
			KERBAL_CONSTEXPR
			const typename function_manager_collection<void, Size, Align, Allocator, Ret, TArgs...>::manager_table
			function_manager_collection<void, Size, Align, Allocator, Ret, TArgs...>::mtable;
#		endif

#	else

			template <
				std::size_t Size, std::size_t Align, typename Allocator,
				typename Ret, typename ... TArgs
			>
			const typename function_manager_collection<void, Size, Align, Allocator, Ret, TArgs...>::manager_table
			function_manager_collection<void, Size, Align, Allocator, Ret, TArgs...>::mtable(NULL, destroy, clone, swap_out, swap TYPE_INFO_ENTRY);

#	endif

#	undef TYPE_INFO_ENTRY


			template <
				typename T, std::size_t Size, std::size_t Align, typename Allocator,
				typename Ret, typename ... TArgs
			>
			struct function_manager_collection
			{
				private:
					typedef kerbal::function::basic_function<Ret(TArgs...), Size, Align, Allocator>		function;
					typedef kerbal::memory::detail::any_node<T>											any_node;
					typedef typename function::void_allocator_type										void_allocator_type;
					typedef kerbal::memory::allocator_traits<void_allocator_type>						void_allocator_traits;
					typedef typename void_allocator_traits::template rebind_alloc<any_node>::other		allocator_type;
					typedef kerbal::memory::allocator_traits<allocator_type>							allocator_traits;
					typedef is_function_embedded_stored_type<T, Size, Align>							is_embedded_stored_type;
					typedef function_manager_table<Size, Align, Allocator, Ret, TArgs...>				manager_table;

					KERBAL_STATIC_ASSERT(!kerbal::type_traits::is_const<T>::value, "T couldn't be const");
					KERBAL_STATIC_ASSERT(!kerbal::type_traits::is_reference<T>::value, "T couldn't be reference");

					KERBAL_CONSTEXPR20
					static Ret invoke(const function & self, TArgs ... args)
					{
						return kerbal::function::invoke(
							const_cast<T &>(self.template ignored_get<const T &>()),
							static_cast<TArgs>(args)...
						);
					}

					KERBAL_CONSTEXPR20
					static void destroy(function & self) KERBAL_NOEXCEPT
					{
						self.k_storage.template destroy<T>(is_embedded_stored_type(), self.void_alloc());
					}

					KERBAL_CONSTEXPR20
					static void clone(function & self, const function & ano)
					{
						const any_node * p_to_src = ano.template obj_pos<T>();
						self.k_storage.template construct<T>(
							is_embedded_stored_type(),
							self.void_alloc(),
							p_to_src->member()
						);
					}

#	if __cplusplus >= 201103L

					KERBAL_CONSTEXPR20
					static void xfer(function & self, function && ano) KERBAL_NOEXCEPT
					{
						self.k_storage.template xfer<T>(
							is_embedded_stored_type(),
							self.void_alloc(),
							kerbal::compatibility::move(ano.k_storage),
							ano.void_alloc()
						);
					}

#	endif

					KERBAL_CONSTEXPR20
					static void swap_out(function & self, function & out) KERBAL_NOEXCEPT
					{
						out.k_storage.template xfer<T>(
							is_embedded_stored_type(),
							out.void_alloc(),
							kerbal::compatibility::to_xvalue(self.k_storage),
							self.void_alloc()
						);
					}

					KERBAL_CONSTEXPR20
					static void swap(function & self, function & with) KERBAL_NOEXCEPT
					{
						typename function::any_storage_type tmp;

						// self -> tmp
						tmp.template xfer<T>(
							is_embedded_stored_type(),
							self.void_alloc(),
							kerbal::compatibility::to_xvalue(self.k_storage),
							self.void_alloc()
						);

						// with -> self
						with.k_mtable->swap_out(with, self);

						// tmp -> with
						with.k_storage.template xfer<T>(
							is_embedded_stored_type(),
							with.void_alloc(),
							kerbal::compatibility::to_xvalue(tmp),
							with.void_alloc()
						);
					}

#	if KERBAL_FUNCTION_TYPE_POLICY == KERBAL_FUNCTION_TYPE_POLICY_FUNCTION

					KERBAL_CONSTEXPR20
					static const std::type_info & type_info() KERBAL_NOEXCEPT
					{
						return typeid(T);
					}

#	endif

				public:

#	if KERBAL_FUNCTION_TYPE_POLICY == KERBAL_FUNCTION_TYPE_POLICY_DISABLE
#		define TYPE_INFO_ENTRY
#	elif KERBAL_FUNCTION_TYPE_POLICY == KERBAL_FUNCTION_TYPE_POLICY_POINTER
#		define TYPE_INFO_ENTRY , &typeid(T)
#	elif KERBAL_FUNCTION_TYPE_POLICY == KERBAL_FUNCTION_TYPE_POLICY_FUNCTION
#		define TYPE_INFO_ENTRY , type_info
#	endif

#		if __cplusplus >= 201103L
					KERBAL_CONSTEXPR
#			if __cplusplus >= 201703L
					inline
#			endif
					static const manager_table mtable = manager_table(invoke, destroy, clone, xfer, swap_out, swap TYPE_INFO_ENTRY);
#		else
					static const manager_table mtable;
#		endif

			};


#	if __cplusplus >= 201103L

#		if __cplusplus < 201703L
			template <
				typename T, std::size_t Size, std::size_t Align, typename Allocator,
				typename Ret, typename ... TArgs
			>
			KERBAL_CONSTEXPR
			const typename function_manager_collection<T, Size, Align, Allocator, Ret, TArgs...>::manager_table
			function_manager_collection<T, Size, Align, Allocator, Ret, TArgs...>::mtable;
#		endif

#	else

			template <
				typename T, std::size_t Size, std::size_t Align, typename Allocator,
				typename Ret, typename ... TArgs
			>
			const typename function_manager_collection<T, Size, Align, Allocator, Ret, TArgs...>::manager_table
			function_manager_collection<T, Size, Align, Allocator, Ret, TArgs...>::mtable(invoke, destroy, clone, swap_out, swap TYPE_INFO_ENTRY);

#	endif

#	undef TYPE_INFO_ENTRY

		} // namespace detail


		/*KERBAL_MODULE_EXPORT*/
		template <
			std::size_t Size, std::size_t Align, typename Allocator,
			typename Ret, typename ... TArgs
		>
		class basic_function<Ret(TArgs...), Size, Align, Allocator> :
			private kerbal::utility::member_compress_helper<Allocator>
		{
			private:

				friend struct detail::function_manager_table<Size, Align, Allocator, Ret, TArgs...>;

				template <
					typename T, std::size_t Size2, std::size_t Align2, typename Allocator2,
					typename Ret2, typename ... TArgs2
				>
				friend struct kerbal::function::detail::function_manager_collection;

				template <typename T>
				struct is_embedded_stored_type :
					is_function_embedded_stored_type<T, Size, Align>
				{
				};

				typedef kerbal::memory::detail::any_node_base			any_node_base;

				template <typename T>
				struct get_any_node_type
				{
						typedef kerbal::memory::detail::any_node<T> type;
				};

				typedef const detail::function_manager_table<Size, Align, Allocator, Ret, TArgs...>		manager_table;
				typedef kerbal::utility::member_compress_helper<Allocator>								allocator_compress_helper;
				typedef kerbal::memory::any_storage<Size, Align>										any_storage_type;

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
					return &detail::function_manager_collection<T, Size, Align, Allocator, Ret, TArgs...>::mtable;
				}

			public:

				KERBAL_CONSTEXPR20
				basic_function() KERBAL_NOEXCEPT :
					k_mtable(mtable_of_type<void>())
				{
				}

#	if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				basic_function(std::nullptr_t) KERBAL_NOEXCEPT :
					k_mtable(mtable_of_type<void>())
				{
				}

#	endif

				KERBAL_CONSTEXPR20
				basic_function(const basic_function & src) :
					allocator_compress_helper(kerbal::utility::in_place_t(), src.void_alloc()),
					k_mtable(src.k_mtable)
				{
					this->k_mtable->clone(*this, src);
				}

#	if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				basic_function(basic_function && src)
					KERBAL_CONDITIONAL_NOEXCEPT((
						kerbal::type_traits::try_test_is_nothrow_constructible<
							allocator_compress_helper,
							kerbal::utility::in_place_t,
							void_allocator_type &&
						>::IS_TRUE::value
					)) :
					allocator_compress_helper(
						kerbal::utility::in_place_t(),
						kerbal::compatibility::move(src.void_alloc())
					),
					k_mtable(src.k_mtable)
				{
					this->k_mtable->xfer(*this, kerbal::compatibility::move(src));
					src.k_mtable = mtable_of_type<void>();
				}

#	endif


				template <typename URet, typename ... Args>
				KERBAL_CONSTEXPR20
				basic_function(URet (*value)(Args...)) :
					k_mtable(NULL)
				{
					typedef URet (*value_type)(Args...);
					this->k_storage.template construct<value_type>(
						is_embedded_stored_type<value_type>(),
						this->void_alloc(),
						value
					);
					this->k_mtable = mtable_of_type<value_type>();
				}

				template <typename URet, typename ... Args>
				KERBAL_CONSTEXPR20
				basic_function(URet (*value)(Args..., ...)) :
					k_mtable(NULL)
				{
					typedef URet (*value_type)(Args..., ...);
					this->k_storage.template construct<value_type>(
						is_embedded_stored_type<value_type>(),
						this->void_alloc(),
						value
					);
					this->k_mtable = mtable_of_type<value_type>();
				}

#	if __cplusplus >= 201703L

				template <typename URet, typename ... Args>
				KERBAL_CONSTEXPR20
				basic_function(URet (*value)(Args...) noexcept) :
					k_mtable(NULL)
				{
					typedef URet (*value_type)(Args...) noexcept;
					this->k_storage.template construct<value_type>(
						is_embedded_stored_type<value_type>(),
						this->void_alloc(),
						value
					);
					this->k_mtable = mtable_of_type<value_type>();
				}

				template <typename URet, typename ... Args>
				KERBAL_CONSTEXPR20
				basic_function(URet (*value)(Args..., ...) noexcept) :
					k_mtable(NULL)
				{
					typedef URet (*value_type)(Args..., ...) noexcept;
					this->k_storage.template construct<value_type>(
						is_embedded_stored_type<value_type>(),
						this->void_alloc(),
						value
					);
					this->k_mtable = mtable_of_type<value_type>();
				}

#	endif

#	if __cplusplus >= 201103L

				template <
					typename T,
					typename =
						typename kerbal::type_traits::enable_if<
							!kerbal::type_traits::is_same<
								typename kerbal::type_traits::remove_reference<T>::type,
								basic_function
							>::value
						>::type
				>
				KERBAL_CONSTEXPR20
				basic_function(T && value) :
					k_mtable(NULL)
				{
					typedef typename kerbal::type_traits::remove_reference<T>::type remove_reference;
					typedef typename kerbal::type_traits::remove_const<remove_reference>::type value_type;
					this->k_storage.template construct<value_type>(
						is_embedded_stored_type<value_type>(),
						this->void_alloc(),
						kerbal::utility::forward<T>(value)
					);
					this->k_mtable = mtable_of_type<value_type>();
				}

#	else

				template <typename T>
				KERBAL_CONSTEXPR20
				basic_function(
					const T & value,
					typename kerbal::type_traits::enable_if<
						!kerbal::type_traits::is_same<T, basic_function>::value,
						int
					>::type = 0
				) :
					k_mtable(NULL)
				{
					typedef T value_type;
					this->k_storage.template construct<value_type>(
						is_embedded_stored_type<value_type>(),
						this->void_alloc(),
						value
					);
					this->k_mtable = mtable_of_type<value_type>();
				}

#	endif

				template <typename T, typename ... Args>
				KERBAL_CONSTEXPR20
				explicit basic_function(kerbal::utility::in_place_type_t<T>, Args && ... args) :
					k_mtable(NULL)
				{
					typedef typename kerbal::type_traits::remove_reference<T>::type remove_reference;
					typedef typename kerbal::type_traits::remove_const<remove_reference>::type value_type;
					this->k_storage.template construct<value_type>(
						is_embedded_stored_type<value_type>(),
						this->void_alloc(),
						kerbal::utility::forward<Args>(args)...
					);
					this->k_mtable = mtable_of_type<value_type>();
				}

				KERBAL_CONSTEXPR20
				~basic_function()
				{
					this->k_mtable->destroy(*this);
				}

#	if __cplusplus >= 201103L

				template <typename T>
				KERBAL_CONSTEXPR20
				basic_function & operator=(T && value)
				{
					this->assign(kerbal::utility::forward<T>(value));
					return *this;
				}

#	else

				template <typename T>
				KERBAL_CONSTEXPR20
				basic_function & operator=(const T & value)
				{
					this->assign(value);
					return *this;
				}

#	endif

				KERBAL_CONSTEXPR20
				basic_function & operator=(const basic_function & src)
				{
					this->assign(src);
					return *this;
				}

#	if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				basic_function & operator=(basic_function && src)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(
							kerbal::utility::declthis<basic_function>()->assign(
								kerbal::utility::declval<basic_function &&>()
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
						basic_function
					>::value
				>::type
				assign(T && value)
				{
					typedef typename kerbal::type_traits::remove_reference<T>::type remove_reference;
					typedef typename kerbal::type_traits::remove_const<remove_reference>::type value_type;
					this->k_mtable->destroy(*this);
					this->k_storage.template construct<value_type>(
						is_embedded_stored_type<value_type>(),
						this->void_alloc(),
						value
					);
					this->k_mtable = mtable_of_type<value_type>();
				}

#	else

				template <typename T>
				KERBAL_CONSTEXPR20
				void assign(const T & value)
				{
					typedef T value_type;
					this->k_mtable->destroy(*this);
					this->k_storage.template construct<value_type>(
						is_embedded_stored_type<value_type>(),
						this->void_alloc(),
						value
					);
					this->k_mtable = mtable_of_type<value_type>();
				}

#	endif


				KERBAL_CONSTEXPR20
				void assign(const basic_function & src)
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
				void assign(basic_function && src) KERBAL_NOEXCEPT
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


				template <typename T, typename ... Args>
				KERBAL_CONSTEXPR20
				void emplace(Args && ... args)
				{
					typedef typename kerbal::type_traits::remove_reference<T>::type remove_reference;
					typedef typename kerbal::type_traits::remove_const<remove_reference>::type value_type;
					this->k_mtable->destroy(*this);
					this->k_storage.template construct<value_type>(
						is_embedded_stored_type<value_type>(),
						this->void_alloc(),
						kerbal::utility::forward<Args>(args)...
					);
					this->k_mtable = mtable_of_type<value_type>();
				}

				KERBAL_CONSTEXPR20
				void reset() KERBAL_NOEXCEPT
				{
					this->k_mtable->destroy(*this);
					this->k_mtable = mtable_of_type<void>();
				}

				KERBAL_CONSTEXPR20
				void swap(basic_function & with) KERBAL_NOEXCEPT
				{
					this->k_mtable->swap(*this, with);
					kerbal::algorithm::swap(this->k_mtable, with.k_mtable);
				}

#	if KERBAL_FUNCTION_TYPE_POLICY == KERBAL_FUNCTION_TYPE_POLICY_POINTER

				KERBAL_CONSTEXPR20
				const std::type_info & type() const KERBAL_NOEXCEPT
				{
					return *this->k_mtable->type_info;
				}

#	elif KERBAL_FUNCTION_TYPE_POLICY == KERBAL_FUNCTION_TYPE_POLICY_FUNCTION

				KERBAL_CONSTEXPR20
				const std::type_info & type() const KERBAL_NOEXCEPT
				{
					return this->k_mtable->type_info();
				}

#	endif

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

				KERBAL_CONSTEXPR20
				operator bool() const KERBAL_NOEXCEPT
				{
					return this->has_value();
				}

				template <typename T>
				KERBAL_CONSTEXPR20
				T * ignored_get_pointer() KERBAL_NOEXCEPT
				{
					typedef typename kerbal::type_traits::remove_const<T>::type value_type;
					return &(this->template obj_pos<value_type>()->member());
				}

				template <typename T>
				KERBAL_CONSTEXPR20
				const T * ignored_get_pointer() const KERBAL_NOEXCEPT
				{
					typedef typename kerbal::type_traits::remove_const<T>::type value_type;
					return &(this->template obj_pos<value_type>()->member());
				}

				template <typename T>
				KERBAL_CONSTEXPR20
				T * get_pointer() KERBAL_NOEXCEPT
				{
					typedef typename kerbal::type_traits::remove_const<T>::type value_type;

					return
						this->template contains_type<value_type>() ?
						&(this->template obj_pos<value_type>()->member()) :
						NULL;
				}

				template <typename T>
				KERBAL_CONSTEXPR20
				const T * get_pointer() const KERBAL_NOEXCEPT
				{
					typedef typename kerbal::type_traits::remove_const<T>::type value_type;

					return
						this->template contains_type<value_type>() ?
						&(this->template obj_pos<value_type>()->member()) :
						NULL;
				}

				template <typename T>
				KERBAL_CONSTEXPR20
				T ignored_get() KERBAL_REFERENCE_OVERLOAD_TAG
				{
					typedef typename kerbal::type_traits::remove_reference<T>::type remove_reference;
					typedef typename kerbal::type_traits::remove_const<remove_reference>::type value_type;

					return this->template obj_pos<value_type>()->member();
				}

				template <typename T>
				KERBAL_CONSTEXPR20
				T ignored_get() KERBAL_CONST_REFERENCE_OVERLOAD_TAG
				{
					typedef typename kerbal::type_traits::remove_reference<T>::type remove_reference;
					typedef typename kerbal::type_traits::remove_const<remove_reference>::type value_type;
					KERBAL_STATIC_ASSERT(
						!(
							kerbal::type_traits::is_reference<T>::value &&
							!kerbal::type_traits::is_const<remove_reference>::value
						),
						"can not bind non-const reference to value from const function"
					);

					return this->template obj_pos<value_type>()->member();
				}

				template <typename T>
				KERBAL_CONSTEXPR20
				T get() KERBAL_REFERENCE_OVERLOAD_TAG
				{
					typedef typename kerbal::type_traits::remove_reference<T>::type remove_reference;
					typedef typename kerbal::type_traits::remove_const<remove_reference>::type value_type;

					if (!this->template contains_type<value_type>()) {
						kerbal::utility::throw_this_exception_helper<kerbal::function::bad_function_cast>::throw_this_exception(
							this->type(), typeid(value_type)
						);
					}
					return this->template obj_pos<value_type>()->member();
				}

				template <typename T>
				KERBAL_CONSTEXPR20
				T get() KERBAL_CONST_REFERENCE_OVERLOAD_TAG
				{
					typedef typename kerbal::type_traits::remove_reference<T>::type remove_reference;
					typedef typename kerbal::type_traits::remove_const<remove_reference>::type value_type;
					KERBAL_STATIC_ASSERT(
						!(
							kerbal::type_traits::is_reference<T>::value &&
							!kerbal::type_traits::is_const<remove_reference>::value
						),
						"can not bind non-const reference to value from const function"
					);

					if (!this->template contains_type<value_type>()) {
						kerbal::utility::throw_this_exception_helper<kerbal::function::bad_function_cast>::throw_this_exception(
							this->type(), typeid(value_type)
						);
					}
					return this->template obj_pos<value_type>()->member();
				}

#	if __cplusplus >= 201103L

				template <typename T>
				KERBAL_CONSTEXPR20
				T ignored_get() &&
				{
					KERBAL_STATIC_ASSERT(
						!kerbal::type_traits::is_lvalue_reference<T>::value,
						"T shouldn't be lvalue reference"
					);

					typedef typename kerbal::type_traits::remove_reference<T>::type remove_reference;
					typedef typename kerbal::type_traits::remove_const<remove_reference>::type value_type;

					return kerbal::compatibility::move(this->template obj_pos<value_type>()->member());
				}

				template <typename T>
				KERBAL_CONSTEXPR20
				T get() &&
				{
					KERBAL_STATIC_ASSERT(
						!kerbal::type_traits::is_lvalue_reference<T>::value,
						"T shouldn't be lvalue reference"
					);

					typedef typename kerbal::type_traits::remove_reference<T>::type remove_reference;
					typedef typename kerbal::type_traits::remove_const<remove_reference>::type value_type;

					if (!this->template contains_type<value_type>()) {
						kerbal::utility::throw_this_exception_helper<kerbal::function::bad_function_cast>::throw_this_exception();
					}
					return kerbal::compatibility::move(this->template obj_pos<value_type>()->member());
				}

#	endif

				template <typename ... UArgs>
				KERBAL_CONSTEXPR20
				Ret ignored_invoke(UArgs && ... uargs) const
				{
					return this->k_mtable->invoke(*this, kerbal::utility::forward<UArgs>(uargs)...);
				}

				template <typename ... UArgs>
				KERBAL_CONSTEXPR20
				Ret operator()(UArgs && ... uargs) const
				{
					if (this->k_mtable->invoke == NULL) {
						kerbal::utility::throw_this_exception_helper<kerbal::function::bad_function_call>::throw_this_exception();
					}
					return this->k_mtable->invoke(*this, kerbal::utility::forward<UArgs>(uargs)...);
				}

		};


		KERBAL_MODULE_EXPORT
		template <typename T, typename Fun, std::size_t Size, std::size_t Align, typename Allocator>
		KERBAL_CONSTEXPR20
		T * function_cast(basic_function<Fun, Size, Align, Allocator> * operand) KERBAL_NOEXCEPT
		{
			return operand->template get_pointer<T>();
		}

		KERBAL_MODULE_EXPORT
		template <typename T, typename Fun, std::size_t Size, std::size_t Align, typename Allocator>
		KERBAL_CONSTEXPR20
		const T * function_cast(const basic_function<Fun, Size, Align, Allocator> * operand) KERBAL_NOEXCEPT
		{
			return operand->template get_pointer<T>();
		}

		KERBAL_MODULE_EXPORT
		template <typename T, typename Fun, std::size_t Size, std::size_t Align, typename Allocator>
		KERBAL_CONSTEXPR20
		T function_cast(basic_function<Fun, Size, Align, Allocator> & operand)
		{
			return operand.template get<T>();
		}

		KERBAL_MODULE_EXPORT
		template <typename T, typename Fun, std::size_t Size, std::size_t Align, typename Allocator>
		KERBAL_CONSTEXPR20
		const T function_cast(const basic_function<Fun, Size, Align, Allocator> & operand)
		{
			return operand.template get<T>();
		}

#	if __cplusplus >= 201103L

		KERBAL_MODULE_EXPORT
		template <typename T, typename Fun, std::size_t Size, std::size_t Align, typename Allocator>
		KERBAL_CONSTEXPR20
		T function_cast(basic_function<Fun, Size, Align, Allocator> && operand)
		{
			return kerbal::compatibility::move(operand).template get<T>();
		}

#	endif

	} // namespace function

	namespace algorithm
	{

		KERBAL_MODULE_EXPORT
		template <std::size_t Size, std::size_t Align, typename Allocator, typename Ret, typename ... TArgs>
		KERBAL_CONSTEXPR20
		void swap(
			kerbal::function::basic_function<Ret(TArgs...), Size, Align, Allocator> & a,
			kerbal::function::basic_function<Ret(TArgs...), Size, Align, Allocator> & b
		)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
		{
			a.swap(b);
		}

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	KERBAL_MODULE_EXPORT
	template <std::size_t Size, std::size_t Align, typename Allocator, typename Ret, typename ... TArgs>
	KERBAL_CONSTEXPR20
	void swap(
		kerbal::function::basic_function<Ret(TArgs...), Size, Align, Allocator> & a,
		kerbal::function::basic_function<Ret(TArgs...), Size, Align, Allocator> & b
	)
		KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END

#endif // KERBAL_FUNCTION_FUNCTION_DETAIL_FUNCTION_CXX11_PART_HPP
