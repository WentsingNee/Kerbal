/**
 * @file       raw_storage_base.cxx11.hpp
 * @brief
 * @date       2022-08-26
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_DETAIL_RAW_STORAGE_RAW_STORAGE_BASE_CXX11_HPP
#define KERBAL_MEMORY_DETAIL_RAW_STORAGE_RAW_STORAGE_BASE_CXX11_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/method_overload_tag.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/uninitialized.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_trivially_default_constructible.hpp>
#include <kerbal/type_traits/is_trivially_destructible.hpp>
#include <kerbal/type_traits/tribool_constant.hpp>
#include <kerbal/utility/forward.hpp>
#include <kerbal/utility/in_place.hpp>
#include <kerbal/utility/integer_sequence.hpp>
#include <kerbal/utility/noncopyable.hpp>

#include <initializer_list>
#include <cstddef>


namespace kerbal
{

	namespace memory
	{

		namespace detail
		{

			template <typename T>
			struct rawst_base_selector:
					kerbal::type_traits::conditional<
						kerbal::type_traits::tribool_is_true<
							kerbal::type_traits::try_test_is_trivially_destructible<T>
						>::value,
						typename kerbal::type_traits::conditional<
							kerbal::type_traits::tribool_is_true<
								kerbal::type_traits::try_test_is_trivially_default_constructible<T>
							>::value,
							kerbal::type_traits::integral_constant<int, 1>,
							kerbal::type_traits::integral_constant<int, 2>
						>::type,
						kerbal::type_traits::integral_constant<int, 0>
					>::type
			{
			};


			template <typename T, int = rawst_base_selector<T>::value>
			class _K_rawst_base;

			template <typename T>
			class _K_rawst_base<T, 0>:
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

					typedef union storage_type
					{
							value_type _K_val;

							KERBAL_CONSTEXPR20
							storage_type() KERBAL_NOEXCEPT
							{
							}

							template <typename ... Args>
							KERBAL_CONSTEXPR20
							explicit storage_type(kerbal::utility::in_place_t, Args&& ... args) :
									_K_val(kerbal::utility::forward<Args>(args)...)
							{
							}

							KERBAL_CONSTEXPR20
							~storage_type() KERBAL_NOEXCEPT
							{
							}

					} storage_type;

					storage_type _K_storage;

				public:

					KERBAL_CONSTEXPR20
					_K_rawst_base() KERBAL_NOEXCEPT
					{
					}

					template <typename ... Args>
					KERBAL_CONSTEXPR20
					explicit _K_rawst_base(kerbal::utility::in_place_t in_place, Args&& ... args) :
						_K_storage(in_place, kerbal::utility::forward<Args>(args)...)
					{
					}

				public:

					KERBAL_CONSTEXPR20
					reference raw_value() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return this->_K_storage._K_val;
					}

					KERBAL_CONSTEXPR20
					const_reference raw_value() const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return this->_K_storage._K_val;
					}

#		if __cplusplus >= 201103L

					KERBAL_CONSTEXPR20
					rvalue_reference raw_value() && noexcept
					{
						return static_cast<rvalue_reference>(this->_K_storage._K_val);
					}

					KERBAL_CONSTEXPR20
					const_rvalue_reference raw_value() const && noexcept
					{
						return static_cast<const_rvalue_reference>(this->_K_storage._K_val);
					}

#		endif

					KERBAL_CONSTEXPR20
					pointer raw_pointer() KERBAL_NOEXCEPT
					{
						return &(this->_K_storage._K_val);
					}

					KERBAL_CONSTEXPR20
					const_pointer raw_pointer() const KERBAL_NOEXCEPT
					{
						return &(this->_K_storage._K_val);
					}

					KERBAL_CONSTEXPR20
					void destroy() KERBAL_NOEXCEPT
					{
						kerbal::memory::destroy_at(this->raw_pointer());
					}

			};


			template <typename T, std::size_t N>
			class _K_rawst_base<T[N], 0>:
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

					typedef union storage_type
					{
							value_type _K_val;

							KERBAL_CONSTEXPR20
							storage_type() KERBAL_NOEXCEPT
							{
							}

							template <std::size_t ... I, typename U>
							KERBAL_CONSTEXPR20
							explicit storage_type(kerbal::utility::in_place_t, kerbal::utility::index_sequence<I...>, std::initializer_list<U> ilist) :
									_K_val{*(ilist.begin() + I)...}
							{
							}

							template <std::size_t ... I, typename U>
							KERBAL_CONSTEXPR20
							explicit storage_type(kerbal::utility::in_place_t, kerbal::utility::index_sequence<I...>, U (&src) [N]) :
									_K_val{src[I]...}
							{
							}

							template <std::size_t ... I, typename U>
							KERBAL_CONSTEXPR20
							explicit storage_type(kerbal::utility::in_place_t, kerbal::utility::index_sequence<I...>, U (&&src) [N]) :
									_K_val{kerbal::compatibility::move(src)[I]...}
							{
							}

							template <typename ... Args>
							KERBAL_CONSTEXPR20
							explicit storage_type(kerbal::utility::in_place_t, Args&& ... args) :
									_K_val{kerbal::utility::forward<Args>(args)...}
							{
							}

							KERBAL_CONSTEXPR20
							~storage_type() KERBAL_NOEXCEPT
							{
							}

					} storage_type;

					storage_type _K_storage;

				public:

					KERBAL_CONSTEXPR20
					_K_rawst_base() KERBAL_NOEXCEPT
					{
					}

					template <typename U>
					KERBAL_CONSTEXPR20
					explicit _K_rawst_base(kerbal::utility::in_place_t in_place, std::initializer_list<U> ilist) :
						_K_storage(in_place, kerbal::utility::make_index_sequence<N>(), ilist)
					{
					}

					template <typename U>
					KERBAL_CONSTEXPR20
					explicit _K_rawst_base(kerbal::utility::in_place_t in_place, U (&src) [N]) :
						_K_storage(in_place, kerbal::utility::make_index_sequence<N>(), src)
					{
					}

					template <typename U>
					KERBAL_CONSTEXPR20
					explicit _K_rawst_base(kerbal::utility::in_place_t in_place, U (&&src) [N]) :
						_K_storage(in_place, kerbal::utility::make_index_sequence<N>(), kerbal::compatibility::move(src))
					{
					}

					template <typename ... Args>
					KERBAL_CONSTEXPR20
					explicit _K_rawst_base(kerbal::utility::in_place_t in_place, Args&& ... args) :
						_K_storage(in_place, kerbal::utility::forward<Args>(args)...)
					{
					}

				public:

					KERBAL_CONSTEXPR20
					reference raw_value() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return this->_K_storage._K_val;
					}

					KERBAL_CONSTEXPR20
					const_reference raw_value() const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return this->_K_storage._K_val;
					}

#		if __cplusplus >= 201103L

					KERBAL_CONSTEXPR20
					rvalue_reference raw_value() && noexcept
					{
						return static_cast<rvalue_reference>(this->_K_storage._K_val);
					}

					KERBAL_CONSTEXPR20
					const_rvalue_reference raw_value() const && noexcept
					{
						return static_cast<const_rvalue_reference>(this->_K_storage._K_val);
					}

#		endif

					KERBAL_CONSTEXPR20
					pointer raw_pointer() KERBAL_NOEXCEPT
					{
						return &(this->_K_storage._K_val);
					}

					KERBAL_CONSTEXPR20
					const_pointer raw_pointer() const KERBAL_NOEXCEPT
					{
						return &(this->_K_storage._K_val);
					}

					KERBAL_CONSTEXPR20
					void destroy() KERBAL_NOEXCEPT
					{
						kerbal::memory::destroy_at(this->raw_pointer());
					}

			};


			template <typename T>
			class _K_rawst_base<T, 1>:
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

					typedef union storage_type
					{
							value_type _K_val;

							KERBAL_CONSTEXPR
							storage_type() KERBAL_NOEXCEPT:
									_K_val()
							{
							}

							template <typename ... Args>
							KERBAL_CONSTEXPR
							explicit storage_type(kerbal::utility::in_place_t, Args&& ... args) :
									_K_val(kerbal::utility::forward<Args>(args)...)
							{
							}

					} storage_type;

					storage_type _K_storage;

				public:

					KERBAL_CONSTEXPR
					_K_rawst_base() KERBAL_NOEXCEPT
					{
					}

					template <typename ... Args>
					KERBAL_CONSTEXPR
					explicit _K_rawst_base(kerbal::utility::in_place_t in_place, Args&& ... args) :
						_K_storage(in_place, kerbal::utility::forward<Args>(args)...)
					{
					}

				public:

					KERBAL_CONSTEXPR14
					reference raw_value() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return this->_K_storage._K_val;
					}

					KERBAL_CONSTEXPR
					const_reference raw_value() const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return this->_K_storage._K_val;
					}

#		if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					rvalue_reference raw_value() && noexcept
					{
						return static_cast<rvalue_reference>(this->_K_storage._K_val);
					}

					KERBAL_CONSTEXPR
					const_rvalue_reference raw_value() const && noexcept
					{
						return static_cast<const_rvalue_reference>(this->_K_storage._K_val);
					}

#		endif

					KERBAL_CONSTEXPR14
					pointer raw_pointer() KERBAL_NOEXCEPT
					{
						return &(this->_K_storage._K_val);
					}

					KERBAL_CONSTEXPR
					const_pointer raw_pointer() const KERBAL_NOEXCEPT
					{
						return &(this->_K_storage._K_val);
					}

					KERBAL_CONSTEXPR14
					void destroy() KERBAL_NOEXCEPT
					{
					}

			};


			template <typename T, std::size_t N>
			class _K_rawst_base<T[N], 1>:
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

					typedef union storage_type
					{
							value_type _K_val;

							KERBAL_CONSTEXPR
							storage_type() KERBAL_NOEXCEPT:
									_K_val{}
							{
							}

							template <std::size_t ... I, typename U>
							KERBAL_CONSTEXPR
							explicit storage_type(kerbal::utility::in_place_t, kerbal::utility::index_sequence<I...>, std::initializer_list<U> ilist) :
									_K_val{*(ilist.begin() + I)...}
							{
							}

							template <std::size_t ... I, typename U>
							KERBAL_CONSTEXPR
							explicit storage_type(kerbal::utility::in_place_t, kerbal::utility::index_sequence<I...>, U (&src) [N]) :
									_K_val{src[I]...}
							{
							}

							template <std::size_t ... I, typename U>
							KERBAL_CONSTEXPR
							explicit storage_type(kerbal::utility::in_place_t, kerbal::utility::index_sequence<I...>, U (&&src) [N]) :
									_K_val{kerbal::compatibility::move(src)[I]...}
							{
							}

							template <typename ... Args>
							KERBAL_CONSTEXPR
							explicit storage_type(kerbal::utility::in_place_t, Args&& ... args) :
									_K_val{kerbal::utility::forward<Args>(args)...}
							{
							}

					} storage_type;

					storage_type _K_storage;

				public:

					KERBAL_CONSTEXPR
					_K_rawst_base() KERBAL_NOEXCEPT
					{
					}

					template <typename U>
					KERBAL_CONSTEXPR
					explicit _K_rawst_base(kerbal::utility::in_place_t in_place, std::initializer_list<U> ilist) :
						_K_storage(in_place, kerbal::utility::make_index_sequence<N>(), ilist)
					{
					}

					template <typename U>
					KERBAL_CONSTEXPR
					explicit _K_rawst_base(kerbal::utility::in_place_t in_place, U (&src) [N]) :
						_K_storage(in_place, kerbal::utility::make_index_sequence<N>(), src)
					{
					}

					template <typename U>
					KERBAL_CONSTEXPR
					explicit _K_rawst_base(kerbal::utility::in_place_t in_place, U (&&src) [N]) :
						_K_storage(in_place, kerbal::utility::make_index_sequence<N>(), kerbal::compatibility::move(src))
					{
					}

					template <typename ... Args>
					KERBAL_CONSTEXPR
					explicit _K_rawst_base(kerbal::utility::in_place_t in_place, Args&& ... args) :
						_K_storage(in_place, kerbal::utility::forward<Args>(args)...)
					{
					}

				public:

					KERBAL_CONSTEXPR14
					reference raw_value() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return this->_K_storage._K_val;
					}

					KERBAL_CONSTEXPR
					const_reference raw_value() const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return this->_K_storage._K_val;
					}

#		if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					rvalue_reference raw_value() && noexcept
					{
						return static_cast<rvalue_reference>(this->_K_storage._K_val);
					}

					KERBAL_CONSTEXPR
					const_rvalue_reference raw_value() const && noexcept
					{
						return static_cast<const_rvalue_reference>(this->_K_storage._K_val);
					}

#		endif

					KERBAL_CONSTEXPR14
					pointer raw_pointer() KERBAL_NOEXCEPT
					{
						return &(this->_K_storage._K_val);
					}

					KERBAL_CONSTEXPR
					const_pointer raw_pointer() const KERBAL_NOEXCEPT
					{
						return &(this->_K_storage._K_val);
					}

					KERBAL_CONSTEXPR14
					void destroy() KERBAL_NOEXCEPT
					{
					}

			};


			template <typename T>
			class _K_rawst_base<T, 2>:
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

					struct empty {};

					typedef union storage_type
					{
							value_type _K_val;
							empty _K_empty;

							KERBAL_CONSTEXPR
							storage_type() KERBAL_NOEXCEPT:
									_K_empty()
							{
							}

							template <typename ... Args>
							KERBAL_CONSTEXPR
							explicit storage_type(kerbal::utility::in_place_t, Args&& ... args) :
									_K_val(kerbal::utility::forward<Args>(args)...)
							{
							}

					} storage_type;

					storage_type _K_storage;

				public:

					KERBAL_CONSTEXPR
					_K_rawst_base() KERBAL_NOEXCEPT
					{
					}

					template <typename ... Args>
					KERBAL_CONSTEXPR
					explicit _K_rawst_base(kerbal::utility::in_place_t in_place, Args&& ... args) :
						_K_storage(in_place, kerbal::utility::forward<Args>(args)...)
					{
					}

				public:

					KERBAL_CONSTEXPR14
					reference raw_value() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return this->_K_storage._K_val;
					}

					KERBAL_CONSTEXPR
					const_reference raw_value() const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return this->_K_storage._K_val;
					}

#		if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					rvalue_reference raw_value() && noexcept
					{
						return static_cast<rvalue_reference>(this->_K_storage._K_val);
					}

					KERBAL_CONSTEXPR
					const_rvalue_reference raw_value() const && noexcept
					{
						return static_cast<const_rvalue_reference>(this->_K_storage._K_val);
					}

#		endif

					KERBAL_CONSTEXPR14
					pointer raw_pointer() KERBAL_NOEXCEPT
					{
						return &(this->_K_storage._K_val);
					}

					KERBAL_CONSTEXPR
					const_pointer raw_pointer() const KERBAL_NOEXCEPT
					{
						return &(this->_K_storage._K_val);
					}

					KERBAL_CONSTEXPR14
					void destroy() KERBAL_NOEXCEPT
					{
					}

			};


			template <typename T, std::size_t N>
			class _K_rawst_base<T[N], 2>:
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

					struct empty {};

					typedef union storage_type
					{
							value_type _K_val;
							empty _K_empty;

							KERBAL_CONSTEXPR
							storage_type() KERBAL_NOEXCEPT:
									_K_empty()
							{
							}

							template <std::size_t ... I, typename U>
							KERBAL_CONSTEXPR
							explicit storage_type(kerbal::utility::in_place_t, kerbal::utility::index_sequence<I...>, std::initializer_list<U> ilist) :
									_K_val{*(ilist.begin() + I)...}
							{
							}

							template <std::size_t ... I, typename U>
							KERBAL_CONSTEXPR
							explicit storage_type(kerbal::utility::in_place_t, kerbal::utility::index_sequence<I...>, U (&src) [N]) :
									_K_val{src[I]...}
							{
							}

							template <std::size_t ... I, typename U>
							KERBAL_CONSTEXPR
							explicit storage_type(kerbal::utility::in_place_t, kerbal::utility::index_sequence<I...>, U (&&src) [N]) :
									_K_val{kerbal::compatibility::move(src)[I]...}
							{
							}

							template <typename ... Args>
							KERBAL_CONSTEXPR
							explicit storage_type(kerbal::utility::in_place_t, Args&& ... args) :
									_K_val{kerbal::utility::forward<Args>(args)...}
							{
							}

					} storage_type;

					storage_type _K_storage;

				public:

					KERBAL_CONSTEXPR
					_K_rawst_base() KERBAL_NOEXCEPT
					{
					}

					template <typename U>
					KERBAL_CONSTEXPR
					explicit _K_rawst_base(kerbal::utility::in_place_t in_place, std::initializer_list<U> ilist) :
						_K_storage(in_place, kerbal::utility::make_index_sequence<N>(), ilist)
					{
					}

					template <typename U>
					KERBAL_CONSTEXPR
					explicit _K_rawst_base(kerbal::utility::in_place_t in_place, U (&src) [N]) :
						_K_storage(in_place, kerbal::utility::make_index_sequence<N>(), src)
					{
					}

					template <typename U>
					KERBAL_CONSTEXPR
					explicit _K_rawst_base(kerbal::utility::in_place_t in_place, U (&&src) [N]) :
						_K_storage(in_place, kerbal::utility::make_index_sequence<N>(), kerbal::compatibility::move(src))
					{
					}

					template <typename ... Args>
					KERBAL_CONSTEXPR
					explicit _K_rawst_base(kerbal::utility::in_place_t in_place, Args&& ... args) :
						_K_storage(in_place, kerbal::utility::forward<Args>(args)...)
					{
					}

				public:

					KERBAL_CONSTEXPR14
					reference raw_value() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return this->_K_storage._K_val;
					}

					KERBAL_CONSTEXPR
					const_reference raw_value() const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return this->_K_storage._K_val;
					}

#		if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					rvalue_reference raw_value() && noexcept
					{
						return static_cast<rvalue_reference>(this->_K_storage._K_val);
					}

					KERBAL_CONSTEXPR
					const_rvalue_reference raw_value() const && noexcept
					{
						return static_cast<const_rvalue_reference>(this->_K_storage._K_val);
					}

#		endif

					KERBAL_CONSTEXPR14
					pointer raw_pointer() KERBAL_NOEXCEPT
					{
						return &(this->_K_storage._K_val);
					}

					KERBAL_CONSTEXPR
					const_pointer raw_pointer() const KERBAL_NOEXCEPT
					{
						return &(this->_K_storage._K_val);
					}

					KERBAL_CONSTEXPR14
					void destroy() KERBAL_NOEXCEPT
					{
					}

			};

		} // namespace detail

	} // namespace memory

} // namespace kerbal

#endif // KERBAL_MEMORY_DETAIL_RAW_STORAGE_RAW_STORAGE_BASE_CXX11_HPP
