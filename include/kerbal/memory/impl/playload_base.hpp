/**
 * @file       playload_base.hpp
 * @brief
 * @date       2020-01-08
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_PLAYLOAD_BASE_HPP
#define KERBAL_PLAYLOAD_BASE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/method_overload_tag.hpp>
#include <kerbal/type_traits/const_deduction.hpp>
#include <kerbal/utility/in_place.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

#include <optional>

#if __cplusplus >= 201103L
#  include <initializer_list>
#  include <type_traits>
#endif

namespace kerbal
{

	namespace memory
	{

		namespace detail
		{

			struct playload_storage_empty
			{
			};

			template <typename Tp, bool = std::is_trivially_destructible<Tp>::value>
			union playload_storage;

			template <typename Tp>
			union playload_storage<Tp, true>
			{
					playload_storage_empty empty;
					Tp value;

					KERBAL_CONSTEXPR playload_storage() KERBAL_NOEXCEPT
							: empty()
					{
					}

					template <typename ... Args>
					KERBAL_CONSTEXPR playload_storage(kerbal::utility::in_place_t, Args&& ... args)
														KERBAL_CONDITIONAL_NOEXCEPT(
																(std::is_nothrow_constructible<Tp, Args...>::value)
														)
							: value(kerbal::utility::forward<Args>(args)...)
					{
					}

			};

			template <typename Tp, size_t N>
			union playload_storage<Tp[N], true>
			{
					playload_storage_empty empty;
					Tp value;

					KERBAL_CONSTEXPR
					playload_storage() KERBAL_NOEXCEPT
							: empty()
					{
					}

					KERBAL_CONSTEXPR
					playload_storage(kerbal::utility::in_place_t)
														KERBAL_CONDITIONAL_NOEXCEPT(
																(std::is_nothrow_default_constructible<Tp>::value)
														)
							: value()
					{
					}


					KERBAL_CONSTEXPR
					playload_storage(kerbal::utility::in_place_t, std::initializer_list<Tp> list)
														KERBAL_CONDITIONAL_NOEXCEPT(
																(std::is_nothrow_copy_constructible<Tp>::value)
														)
							: value(list)
					{
					}


			};

			template <typename Tp>
			union playload_storage<Tp, false>
			{
					playload_storage_empty empty;
					Tp value;

					KERBAL_CONSTEXPR
					playload_storage() KERBAL_NOEXCEPT
							: empty()
					{
					}

					template <typename ... Args>
					KERBAL_CONSTEXPR
					playload_storage(kerbal::utility::in_place_t, Args&& ... args)
														KERBAL_CONDITIONAL_NOEXCEPT(
																(std::is_nothrow_constructible<Tp, Args...>::value)
														)
							: value(kerbal::utility::forward<Args>(args)...)
					{
					}

					~playload_storage()
														KERBAL_CONDITIONAL_NOEXCEPT(
																std::is_nothrow_destructible<Tp>::value
														)
					{
						this->value.~Tp();
					}
			};

			template <typename Tp, size_t N>
			union playload_storage<Tp[N], false>
			{
					playload_storage_empty empty;
					Tp value;

					KERBAL_CONSTEXPR
					playload_storage() KERBAL_NOEXCEPT
							: empty()
					{
					}

					KERBAL_CONSTEXPR
					playload_storage(kerbal::utility::in_place_t)
														KERBAL_CONDITIONAL_NOEXCEPT(
																(std::is_nothrow_default_constructible<Tp>::value)
														)
							: value()
					{
					}


					KERBAL_CONSTEXPR
					playload_storage(kerbal::utility::in_place_t, std::initializer_list<Tp> list)
														KERBAL_CONDITIONAL_NOEXCEPT(
																(std::is_nothrow_copy_constructible<Tp>::value)
														)
							: value(list)
					{
					}

					~playload_storage()
														KERBAL_CONDITIONAL_NOEXCEPT(
																std::is_nothrow_destructible<Tp>::value
														)
					{
						for (size_t i = N; (i--) != 0;) {
							this->value[i].~Tp();
						}
					}
			};

			template <typename Tp>
			class __playload_raw_pv
			{
				public:
					typedef typename kerbal::type_traits::remove_const<Tp>::type remove_const_t;

					typedef Tp						value_type;
					typedef const value_type		const_type;
					typedef value_type&				reference;
					typedef const value_type&		const_reference;
					typedef value_type*				pointer;
					typedef const value_type*		const_pointer;

#			if __cplusplus >= 201103L
					typedef value_type&&			rvalue_reference;
					typedef const value_type&&		const_rvalue_reference;
#			endif

				protected:
					kerbal::memory::detail::playload_storage<remove_const_t> storage;

					KERBAL_CONSTEXPR
					__playload_raw_pv() KERBAL_NOEXCEPT
							: storage()
					{
					}

					template <typename ... Args>
					KERBAL_CONSTEXPR
					__playload_raw_pv(kerbal::utility::in_place_t in_place_tag, Args&& ... args)
														KERBAL_CONDITIONAL_NOEXCEPT(
																(std::is_nothrow_constructible<Tp, Args...>::value)
														)
							: storage(in_place_tag, kerbal::utility::forward<Args>(args)...)
					{
					}

					KERBAL_CONSTEXPR14 // note: mustn't be constexpr11 otherwise the compile can't distinguish this method with the const version
					remove_const_t& __stored_value() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return this->storage.value;
					}

					KERBAL_CONSTEXPR14 // note: mustn't be constexpr11 otherwise the compile can't distinguish this method with the const version
					const remove_const_t&__stored_value() const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return this->storage.value;
					}


				public:

					KERBAL_CONSTEXPR14 // note: mustn't be constexpr11 otherwise the compile can't distinguish this method with the const version
					reference raw_value() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return this->storage.value;
					}

					KERBAL_CONSTEXPR14
					const_reference raw_value() const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return this->storage.value;
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					rvalue_reference raw_value() && noexcept
					{
						return static_cast<rvalue_reference>(this->storage.value);
					}

					KERBAL_CONSTEXPR14
					const_rvalue_reference raw_value() const && noexcept
					{
						return static_cast<const_rvalue_reference>(this->storage.value);
					}

#			endif

					KERBAL_CONSTEXPR14
					pointer raw_pointer() KERBAL_NOEXCEPT
					{
						return &(this->storage.value);
					}

					KERBAL_CONSTEXPR14
					const_pointer raw_pointer() const KERBAL_NOEXCEPT
					{
						return &(this->storage.value);
					}

			};

			template <typename Tp, bool = std::is_trivially_destructible<Tp>::value>
			class __playload_construct_destroy;


			template <typename Tp>
			class __playload_construct_destroy<Tp, true> : public __playload_raw_pv<Tp>
			{
				private:
					typedef __playload_raw_pv<Tp> super;

				protected:
					typedef Tp value_type;
					typedef value_type& reference;


#			if __cplusplus >= 201103L
					__playload_construct_destroy() noexcept = default;
#			else
					__playload_agent() KERBAL_NOEXCEPT
							: super()
					{
					}
#			endif

					template <typename ... Args>
					KERBAL_CONSTEXPR
					__playload_construct_destroy(kerbal::utility::in_place_t in_place_tag, Args&& ... args)
													KERBAL_CONDITIONAL_NOEXCEPT(
															(std::is_nothrow_constructible<Tp, Args...>::value)
													)
							: super(in_place_tag, kerbal::utility::forward<Args>(args)...)
					{
					}

				public:

#			if __cplusplus < 201103L

#			else

					template <typename ... Args>
					KERBAL_CONSTEXPR14
					reference construct(Args&&... args)
													KERBAL_CONDITIONAL_NOEXCEPT(
															(std::is_nothrow_constructible<value_type, Args...>::value)
													)
					{
						this->__stored_value() = value_type(kerbal::utility::forward<Args>(args)...);
						return this->raw_value();
					}

#			endif

					KERBAL_CONSTEXPR14
					void destroy() KERBAL_NOEXCEPT
					{
					}

			};


			template <typename Tp, size_t N>
			class __playload_construct_destroy<Tp[N], true> : public __playload_raw_pv<Tp[N]>
			{
				private:
					typedef __playload_raw_pv<Tp> super;

				protected:
					typedef Tp value_type;
					typedef value_type& reference;


#			if __cplusplus >= 201103L
					__playload_construct_destroy() noexcept = default;
#			else
					__playload_agent() KERBAL_NOEXCEPT
							: super()
					{
					}
#			endif

					KERBAL_CONSTEXPR
					__playload_construct_destroy(kerbal::utility::in_place_t in_place_tag)
													KERBAL_CONDITIONAL_NOEXCEPT(
															std::is_nothrow_default_constructible<Tp>::value
													)
							: super(in_place_tag)
					{
					}

					template <typename ... Args>
					KERBAL_CONSTEXPR
					__playload_construct_destroy(kerbal::utility::in_place_t in_place_tag, Args&& ... args)
													KERBAL_CONDITIONAL_NOEXCEPT(
															(std::is_nothrow_constructible<Tp, Args...>::value)
													)
							: super(in_place_tag, kerbal::utility::forward<Args>(args)...)
					{
					}

				public:

					KERBAL_CONSTEXPR14
					reference construct() KERBAL_NOEXCEPT
					{
						return this->storage.raw_value();
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					reference construct(std::initializer_list<Tp> list) KERBAL_NOEXCEPT
					{
						for (int i = 0; i < N; ++i) {
							this->__stored_value() = list[i];
						}
						return this->raw_value();
					}

#			endif

					KERBAL_CONSTEXPR14
					void destroy() KERBAL_NOEXCEPT
					{
					}

			};

			template <typename Tp>
			class __playload_construct_destroy<Tp, false> : public __playload_raw_pv<Tp>
			{
				private:
					typedef __playload_raw_pv<Tp> super;

				protected:
					typedef Tp value_type;
					typedef value_type& reference;


#			if __cplusplus >= 201103L
					__playload_construct_destroy() noexcept = default;
#			else
					__playload_agent() KERBAL_NOEXCEPT
							: super()
					{
					}
#			endif

					template <typename ... Args>
					KERBAL_CONSTEXPR
					__playload_construct_destroy(kerbal::utility::in_place_t in_place_tag, Args&& ... args)
														KERBAL_CONDITIONAL_NOEXCEPT(
																(std::is_nothrow_constructible<Tp, Args...>::value)
														)
							: super(in_place_tag, kerbal::utility::forward<Args>(args)...)
					{
					}

				public:

#			if __cplusplus < 201103L

#			else

					template <typename ... Args>
					KERBAL_CONSTEXPR14
					reference construct(Args&&... args)
														KERBAL_CONDITIONAL_NOEXCEPT(
																(std::is_nothrow_constructible<value_type, Args...>::value)
														)
					{
						this->__stored_value() = value_type(kerbal::utility::forward<Args>(args)...);
						return this->raw_value();
					}

#			endif

					KERBAL_CONSTEXPR14
					void destroy() KERBAL_NOEXCEPT
					{
					}

			};

		} // namespace detail

	} // namespace memory

} // namespace kerbal

#endif //KERBAL_PLAYLOAD_BASE_HPP
