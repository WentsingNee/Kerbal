/**
 * @file       raw_storage_base.cxx98.hpp
 * @brief
 * @date       2022-08-26
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_DETAIL_RAW_STORAGE_RAW_STORAGE_BASE_CXX98_HPP
#define KERBAL_MEMORY_DETAIL_RAW_STORAGE_RAW_STORAGE_BASE_CXX98_HPP

#include <kerbal/compatibility/alignof.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/method_overload_tag.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/uninitialized.hpp>
#include <kerbal/type_traits/aligned_storage.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/remove_all_extents.hpp>
#include <kerbal/utility/in_place.hpp>
#include <kerbal/utility/noncopyable.hpp>

#include <kerbal/macro/macro_concat.hpp>
#include <kerbal/macro/ppexpand.hpp>

#if __cplusplus >= 201103L
#	include <type_traits>
#else
#	include <kerbal/type_traits/is_fundamental.hpp>
#	include <kerbal/type_traits/is_pointer.hpp>
#	include <kerbal/type_traits/member_pointer_deduction.hpp>
#endif

#include <cstddef>


namespace kerbal
{

	namespace memory
	{

		namespace detail
		{

			template <typename T>
			struct is_trivial_stored_type;

#	if __cplusplus >= 201103L

			template <typename T>
			struct is_trivial_stored_type:
					kerbal::type_traits::bool_constant<
						std::is_trivially_default_constructible<typename kerbal::type_traits::remove_all_extents<T>::type>::value &&
						std::is_trivially_destructible<typename kerbal::type_traits::remove_all_extents<T>::type>::value
					>
			{
			};

#	else

			template <typename T>
			struct is_trivial_stored_type:
					kerbal::type_traits::bool_constant<
						kerbal::type_traits::is_fundamental<typename kerbal::type_traits::remove_all_extents<T>::type>::value ||
						kerbal::type_traits::is_member_pointer<typename kerbal::type_traits::remove_all_extents<T>::type>::value ||
						kerbal::type_traits::is_pointer<typename kerbal::type_traits::remove_all_extents<T>::type>::value
					>
			{
			};

#	endif



			template <typename T, bool is_trivally_stored = is_trivial_stored_type<T>::value>
			class _K_rawst_base;

			template <typename T>
			class _K_rawst_base<T, true>:
					private kerbal::utility::noncopyable
			{
				protected:
					typedef T						value_type;
					typedef const value_type		const_type;
					typedef value_type&				reference;
					typedef const value_type&		const_reference;
					typedef value_type*				pointer;
					typedef const value_type*		const_pointer;

#		if __cplusplus >= 201103L
					typedef value_type&&			rvalue_reference;
					typedef const value_type&&		const_rvalue_reference;
#		endif

					typedef value_type				storage_type;

					storage_type _K_storage;

				protected:

#		if __cplusplus < 201103L
					_K_rawst_base() KERBAL_NOEXCEPT {}
#		else
					_K_rawst_base() = default;
#		endif

#			define EMPTY
#			define REMAINF(exp) exp
#			define LEFT_JOIN_COMMA(exp) , exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#			define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
					KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
					explicit _K_rawst_base(kerbal::utility::in_place_t KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) : \
							_K_storage(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i)) \
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

				public:

					KERBAL_CONSTEXPR14 // note: mustn't be constexpr11 otherwise the compile can't distinguish this method with the const version
					reference raw_value() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return this->_K_storage;
					}

					KERBAL_CONSTEXPR14
					const_reference raw_value() const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return this->_K_storage;
					}

#		if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					rvalue_reference raw_value() && noexcept
					{
						return static_cast<rvalue_reference>(this->_K_storage);
					}

					KERBAL_CONSTEXPR14
					const_rvalue_reference raw_value() const && noexcept
					{
						return static_cast<const_rvalue_reference>(this->_K_storage);
					}

#		endif

					KERBAL_CONSTEXPR14
					pointer raw_pointer() KERBAL_NOEXCEPT
					{
						return &(this->_K_storage);
					}

					KERBAL_CONSTEXPR14
					const_pointer raw_pointer() const KERBAL_NOEXCEPT
					{
						return &(this->_K_storage);
					}

					KERBAL_CONSTEXPR14
					void destroy() KERBAL_NOEXCEPT
					{
					}

			};


			template <typename T, std::size_t N>
			class _K_rawst_base<T[N], true>:
					private kerbal::utility::noncopyable
			{
				protected:
					typedef T						value_type [N];
					typedef const value_type		const_type;
					typedef value_type&				reference;
					typedef const value_type&		const_reference;
					typedef value_type*				pointer;
					typedef const value_type*		const_pointer;

#		if __cplusplus >= 201103L
					typedef value_type&&			rvalue_reference;
					typedef const value_type&&		const_rvalue_reference;
#		endif

					typedef value_type				storage_type;

					storage_type _K_storage;

				protected:

#		if __cplusplus < 201103L
					_K_rawst_base() KERBAL_NOEXCEPT {}
#		else
					_K_rawst_base() = default;
#		endif

					template <typename U>
					KERBAL_CONSTEXPR20
					explicit _K_rawst_base(kerbal::utility::in_place_t, const U (&src) [N])
					{
						for (std::size_t i = 0; i < N; ++i) {
							this->_K_storage[i] = src[i];
						}
					}

#			define EMPTY
#			define REMAINF(exp) exp
#			define LEFT_JOIN_COMMA(exp) , exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#			define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define ARGS_USE(i) (this->_K_storage[i] = KERBAL_MACRO_CONCAT(arg, i), 0)
#			define FBODY(i) \
					KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
					explicit _K_rawst_base(kerbal::utility::in_place_t KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
					{ \
						KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i); \
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

				public:

					KERBAL_CONSTEXPR14 // note: mustn't be constexpr11 otherwise the compile can't distinguish this method with the const version
					reference raw_value() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return this->_K_storage;
					}

					KERBAL_CONSTEXPR14
					const_reference raw_value() const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return this->_K_storage;
					}

#		if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					rvalue_reference raw_value() && noexcept
					{
						return static_cast<rvalue_reference>(this->_K_storage);
					}

					KERBAL_CONSTEXPR14
					const_rvalue_reference raw_value() const && noexcept
					{
						return static_cast<const_rvalue_reference>(this->_K_storage);
					}

#		endif

					KERBAL_CONSTEXPR14
					pointer raw_pointer() KERBAL_NOEXCEPT
					{
						return &(this->_K_storage);
					}

					KERBAL_CONSTEXPR14
					const_pointer raw_pointer() const KERBAL_NOEXCEPT
					{
						return &(this->_K_storage);
					}

					KERBAL_CONSTEXPR14
					void destroy() KERBAL_NOEXCEPT
					{
					}

			};


			template <typename T>
			class _K_rawst_base<T, false>:
					private kerbal::utility::noncopyable
			{
				protected:
					typedef T						value_type;
					typedef const value_type		const_type;
					typedef value_type&				reference;
					typedef const value_type&		const_reference;
					typedef value_type*				pointer;
					typedef const value_type*		const_pointer;

#		if __cplusplus >= 201103L
					typedef value_type&&			rvalue_reference;
					typedef const value_type&&		const_rvalue_reference;
#		endif

					typedef
						typename kerbal::type_traits::aligned_storage<sizeof(value_type), KERBAL_ALIGNOF(value_type)>::type
					storage_type;

					storage_type _K_storage;

				protected:

#		if __cplusplus < 201103L
					_K_rawst_base() KERBAL_NOEXCEPT {}
#		else
					_K_rawst_base() = default;
#		endif

#			define EMPTY
#			define LEFT_JOIN_COMMA(exp) , exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#			define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
					KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
					explicit _K_rawst_base(kerbal::utility::in_place_t KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
					{ \
						kerbal::memory::construct_at(this->raw_pointer() KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
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

				public:

					reference raw_value() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return *this->raw_pointer();
					}

					const_reference raw_value() const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return *this->raw_pointer();
					}

#		if __cplusplus >= 201103L

					rvalue_reference raw_value() && noexcept
					{
						return static_cast<rvalue_reference>(*this->raw_pointer());
					}

					const_rvalue_reference raw_value() const && noexcept
					{
						return static_cast<const_rvalue_reference>(*this->raw_pointer());
					}

#		endif

					pointer raw_pointer() KERBAL_NOEXCEPT
					{
						return reinterpret_cast<pointer>(&(this->_K_storage));
					}

					const_pointer raw_pointer() const KERBAL_NOEXCEPT
					{
						return reinterpret_cast<const_pointer>(&(this->_K_storage));
					}

					void destroy() KERBAL_NOEXCEPT
					{
						kerbal::memory::destroy_at(this->raw_pointer());
					}

			};

		} // namespace detail

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_DETAIL_RAW_STORAGE_RAW_STORAGE_BASE_CXX98_HPP
