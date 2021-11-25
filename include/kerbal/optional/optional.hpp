/**
 * @file       optional.hpp
 * @brief
 * @date       2018-10-4
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OPTIONAL_OPTIONAL_HPP
#define KERBAL_OPTIONAL_OPTIONAL_HPP

#include <kerbal/optional/fwd/optional.fwd.hpp>

#include <kerbal/optional/bad_optional_access.hpp>
#include <kerbal/optional/is_optional.hpp>
#include <kerbal/optional/nullopt.hpp>
#include <kerbal/optional/detail/optional_hash_template.hpp>

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/method_overload_tag.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/namespace_std_scope.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/raw_storage.hpp>
#include <kerbal/operators/generic_assign.hpp>
#include <kerbal/type_traits/can_be_pseudo_destructible.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/is_same.hpp>
#include <kerbal/type_traits/reference_deduction.hpp>
#include <kerbal/utility/in_place.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

#include <cstddef>


namespace kerbal
{

	namespace optional
	{

		namespace detail
		{

			template <typename T, bool is_trivially_destructible =
					kerbal::type_traits::can_be_pseudo_destructible<T>::value>
			class optional_base;

			template <typename T>
			class optional_base<T, false>
			{
				public:
					typedef T			value_type;

				protected:
					typedef kerbal::memory::raw_storage<value_type> storage_type;

				protected:
					storage_type _K_storage;

					///@~English
					///@brief Mark whether the instance has value.
					///
					///@~Chinese
					///@brief 标记该实例是否含值.
					bool _K_has_value;

				protected:

					KERBAL_CONSTEXPR20
					optional_base() KERBAL_NOEXCEPT
#			if __cplusplus >= 201103L
							: _K_storage(), _K_has_value(false)
#			else
							: _K_has_value(false)
#			endif
					{
					}

#			if __cplusplus >= 201103L

					template <typename ... Args>
					KERBAL_CONSTEXPR20
					explicit optional_base(kerbal::utility::in_place_t in_place, Args&& ... args) :
							_K_storage(in_place, kerbal::utility::forward<Args>(args)...), _K_has_value(true)
					{
					}

#			else

#				define EMPTY
#				define LEFT_JOIN_COMMA(exp) , exp
#				define THEAD_NOT_EMPTY(exp) template <exp>
#				define TARGS_DECL(i) KERBAL_MACRO_CONCAT(typename Arg, i)
#				define ARGS_DECL(i) KERBAL_MACRO_CONCAT(const Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
					explicit optional_base(kerbal::utility::in_place_t in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) : \
							_K_storage(in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)), _K_has_value(true) \
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

#			endif

					KERBAL_CONSTEXPR20
					~optional_base() KERBAL_NOEXCEPT
					{
						if (this->_K_has_value) {
							this->_K_storage.destroy();
						}
					}

			};

			template <typename T>
			class optional_base<T, true>
			{
				public:
					typedef T			value_type;

				protected:
					typedef kerbal::memory::raw_storage<value_type> storage_type;

				protected:
					storage_type _K_storage;

					///@~English
					///@brief Mark whether the instance has value.
					///
					///@~Chinese
					///@brief 标记该实例是否含值.
					bool _K_has_value;

				protected:
					KERBAL_CONSTEXPR
					optional_base() KERBAL_NOEXCEPT
#			if __cplusplus >= 201103L
							: _K_storage(), _K_has_value(false)
#			else
							: _K_has_value(false)
#			endif
					{
					}

#			if __cplusplus >= 201103L

					template <typename ... Args>
					KERBAL_CONSTEXPR
					explicit optional_base(kerbal::utility::in_place_t in_place, Args&& ... args) :
							_K_storage(in_place, kerbal::utility::forward<Args>(args)...), _K_has_value(true)
					{
					}

#			else

#				define EMPTY
#				define LEFT_JOIN_COMMA(exp) , exp
#				define THEAD_NOT_EMPTY(exp) template <exp>
#				define TARGS_DECL(i) KERBAL_MACRO_CONCAT(typename Arg, i)
#				define ARGS_DECL(i) KERBAL_MACRO_CONCAT(const Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
					explicit optional_base(kerbal::utility::in_place_t in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) : \
							_K_storage(in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)), _K_has_value(true) \
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

#			endif

			};

		} // namespace detail

		template <typename T>
		class optional :
				protected kerbal::optional::detail::optional_base<T>
		{
			private:
				typedef kerbal::optional::detail::optional_base<T> super;

			public:
				typedef T						value_type;
				typedef value_type&				reference;
				typedef const value_type&		const_reference;
				typedef value_type*				pointer;
				typedef const value_type*		const_pointer;

#		if __cplusplus >= 201103L
				typedef value_type&&			rvalue_reference;
				typedef const value_type&&		const_rvalue_reference;
#		endif

			public:

			//===================
			// construct/copy/destroy

				/**
				 * @~English
				 * @brief Default constructor.
				 *
				 * @~Chinese
				 * @brief 默认构造函数.
				 */
				KERBAL_CONSTEXPR
				optional() KERBAL_NOEXCEPT :
						super()
				{
				}

				KERBAL_CONSTEXPR
				optional(const kerbal::optional::nullopt_t &) KERBAL_NOEXCEPT :
						super()
				{
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR
				explicit optional(kerbal::optional::nullopt_t &&) KERBAL_NOEXCEPT :
						super()
				{
				}

#		endif


				/**
				 * @~English
				 * @brief Copy from an instance of current type.
				 * @param src value from
				 *
				 * @~Chinese
				 * @brief 从当前类型的一个实例拷贝构造.
				 * @param src 源值
				 */
				KERBAL_CONSTEXPR
				explicit optional(const_reference src) :
						super(kerbal::utility::in_place_t(), src)
				{
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR
				explicit optional(rvalue_reference src) :
						super(kerbal::utility::in_place_t(), kerbal::compatibility::move(src))
				{
				}

#		endif


#		if __cplusplus < 201103L

				/**
				 * @~English
				 * @brief Copy from an instance of another type.
				 * @param src value from
				 * @note The second parameter plays an role of concept traits.
				 *
				 * @~Chinese
				 * @brief 从不同类型的一个实例拷贝构造.
				 * @param src 源值
				 * @note 第二个参数起到概念约束的作用, 无实义.
				 */
				template <typename U>
				KERBAL_CONSTEXPR
				explicit optional(const U & src) :
						super(kerbal::utility::in_place_t(), src)
				{
				}

#		else

				template <typename U, typename = typename kerbal::type_traits::enable_if<
						(
								!kerbal::optional::is_optional<typename kerbal::type_traits::remove_reference<U>::type>::value &&
								!kerbal::type_traits::is_same<typename kerbal::type_traits::remove_reference<U>::type, kerbal::optional::nullopt_t>::value
						),
						int
				>::type>
				KERBAL_CONSTEXPR
				explicit optional(U && src) :
						super(kerbal::utility::in_place_t(), kerbal::utility::forward<U>(src))
				{
				}

#		endif


				/**
				 * @~English
				 * @brief Copy from an instance of optional.
				 * @param src value from
				 *
				 * @~Chinese
				 * @brief 从一个 optional 类型的实例拷贝构造.
				 * @param src 源值
				 */
				KERBAL_CONSTEXPR14
				optional(const optional & src) :
						super()
				{
					if (src.has_value()) {
						this->_K_storage.construct(src.ignored_get());
						this->_K_has_value = true;
					}
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				optional(optional && src) :
						super()
				{
					if (src.has_value()) {
						this->_K_storage.construct(src.ignored_get());
						this->_K_has_value = true;
					}
				}

#		endif


				/**
				 * @brief Copy from an instance of optional which contains another type.
				 * @param src value from
				 */
				template <typename U>
				KERBAL_CONSTEXPR14
				explicit optional(const optional<U> & src) :
						super()
				{
					if (src.has_value()) {
						this->_K_storage.construct(src.ignored_get());
						this->_K_has_value = true;
					}
				}

#		if __cplusplus >= 201103L

				template <typename U>
				KERBAL_CONSTEXPR14
				optional(optional<U> && src) :
						super()
				{
					if (src.has_value()) {
						this->_K_storage.construct(src.ignored_get());
						this->_K_has_value = true;
					}
				}

#		endif


#		if __cplusplus >= 201103L

				template <typename ... Args>
				KERBAL_CONSTEXPR
				explicit optional(kerbal::utility::in_place_t in_place, Args&& ... args) :
						super(in_place, kerbal::utility::forward<Args>(args)...)
				{
				}

#		else

#			define EMPTY
#			define LEFT_JOIN_COMMA(exp) , exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) KERBAL_MACRO_CONCAT(typename Arg, i)
#			define ARGS_DECL(i) KERBAL_MACRO_CONCAT(const Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				explicit optional(kerbal::utility::in_place_t in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) : \
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

#		endif

			//===================
			// assign

				KERBAL_CONSTEXPR14
				optional& operator=(const kerbal::optional::nullopt_t &)
				{
					this->reset();
					return *this;
				}

#	if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				optional& operator=(kerbal::optional::nullopt_t &&)
				{
					this->reset();
					return *this;
				}

#		endif


				KERBAL_CONSTEXPR14
				optional& operator=(const_reference src)
				{
					if (this->has_value()) {
						kerbal::operators::generic_assign(this->_K_storage.raw_value(), src);
						// this->_K_storage.raw_value() = src
					} else {
						this->_K_storage.construct(src);
						this->_K_has_value = true;
					}
					return *this;
				}

#	if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				optional& operator=(rvalue_reference src)
				{
					if (this->has_value()) {
						kerbal::operators::generic_assign(this->_K_storage.raw_value(), kerbal::compatibility::move(src));
						// this->_K_storage.raw_value() = kerbal::compatibility::move(src);
					} else {
						this->_K_storage.construct(kerbal::compatibility::move(src));
						this->_K_has_value = true;
					}
					return *this;
				}

#		endif


#	if __cplusplus < 201103L

				template <typename U>
				KERBAL_CONSTEXPR14
				optional& operator=(const U & src)
				{
					if (this->has_value()) {
						kerbal::operators::generic_assign(this->_K_storage.raw_value(), src);
						// this->_K_storage.raw_value() = src;
					} else {
						this->_K_storage.construct(src);
						this->_K_has_value = true;
					}
					return *this;
				}

#	else

				template <typename U>
				KERBAL_CONSTEXPR14
				typename kerbal::type_traits::enable_if<
					(
						!kerbal::optional::is_optional<typename kerbal::type_traits::remove_reference<U>::type>::value &&
						!kerbal::type_traits::is_same<typename kerbal::type_traits::remove_reference<U>::type, kerbal::optional::nullopt_t>::value
					),
				optional&>::type
				operator=(U && src)
				{
					if (this->has_value()) {
						kerbal::operators::generic_assign(this->_K_storage.raw_value(), kerbal::utility::forward<U>(src));
						// this->_K_storage.raw_value() = kerbal::utility::forward<U>(src);
					} else {
						this->_K_storage.construct(kerbal::utility::forward<U>(src));
						this->_K_has_value = true;
					}
					return *this;
				}

#		endif


				KERBAL_CONSTEXPR14
				optional& operator=(const optional & src)
				{
					if (this->has_value()) {
						if (src.has_value()) {
							kerbal::operators::generic_assign(this->_K_storage.raw_value(), src.ignored_get());
							// this->_K_storage.raw_value() = src.ignored_get();
						} else {
							this->_K_storage.destroy();
							this->_K_has_value = false;
						}
					} else {
						if (src.has_value()) {
							this->_K_storage.construct(src.ignored_get());
							this->_K_has_value = true;
						}
					}
					return *this;
				}

#	if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				optional& operator=(optional && src)
				{
					if (this->has_value()) {
						if (src.has_value()) {
							kerbal::operators::generic_assign(this->_K_storage.raw_value(), kerbal::compatibility::move(src.ignored_get()));
							// this->_K_storage.raw_value() = kerbal::compatibility::move(src.ignored_get());
						} else {
							this->_K_storage.destroy();
							this->_K_has_value = false;
						}
					} else {
						if (src.has_value()) {
							this->_K_storage.construct(kerbal::compatibility::move(src.ignored_get()));
							this->_K_has_value = true;
						}
					}
					return *this;
				}

#		endif


				template <typename U>
				KERBAL_CONSTEXPR14
				optional& operator=(const optional<U> & src)
				{
					if (this->has_value()) {
						if (src.has_value()) {
							kerbal::operators::generic_assign(this->_K_storage.raw_value(), src.ignored_get());
							// this->_K_storage.raw_value() = src.ignored_get();
						} else {
							this->_K_storage.destroy();
							this->_K_has_value = false;
						}
					} else {
						if (src.has_value()) {
							this->_K_storage.construct(src.ignored_get());
							this->_K_has_value = true;
						}
					}
					return *this;
				}

#	if __cplusplus >= 201103L

				template <typename U>
				KERBAL_CONSTEXPR14
				optional& operator=(optional<U> && src)
				{
					if (this->has_value()) {
						if (src.has_value()) {
							kerbal::operators::generic_assign(this->_K_storage.raw_value(), kerbal::compatibility::move(src.ignored_get()));
							// this->_K_storage.raw_value() = kerbal::compatibility::move(src.ignored_get());
						} else {
							this->_K_storage.destroy();
							this->_K_has_value = false;
						}
					} else {
						if (src.has_value()) {
							this->_K_storage.construct(kerbal::compatibility::move(src.ignored_get()));
							this->_K_has_value = true;
						}
					}
					return *this;
				}

#	endif


			//===================
			// observer

				/**
				 * @~English
				 * @brief Test whether the instance has value.
				 * @return Return true if the instance has value.
				 *
				 * @~Chinese
				 * @brief 测试该实例是否含值.
				 * @return 若含值, 返回 true.
				 */
				KERBAL_CONSTEXPR
				bool has_value() const KERBAL_NOEXCEPT
				{
					return this->_K_has_value;
				}

				/**
				 * @~English
				 * @brief Test whether the instance doesn't have value.
				 * @return Return true if the instance doesn't have value.
				 *
				 * @~Chinese
				 * @brief 测试该实例是否不含值.
				 * @return 若不含值, 返回 true.
				 */
				KERBAL_CONSTEXPR
				bool empty() const KERBAL_NOEXCEPT
				{
					return !this->_K_has_value;
				}

				KERBAL_CONSTEXPR
				operator bool() const KERBAL_NOEXCEPT
				{
					return this->has_value();
				}

				KERBAL_CONSTEXPR20
				reference value() KERBAL_REFERENCE_OVERLOAD_TAG
				{
					if (this->empty()) {
						bad_optional_access::throw_this_exception();
					}
					return this->ignored_get();
				}

				KERBAL_CONSTEXPR20
				const_reference value() const KERBAL_REFERENCE_OVERLOAD_TAG
				{
					if (this->empty()) {
						bad_optional_access::throw_this_exception();
					}
					return this->ignored_get();
				}

				KERBAL_CONSTEXPR14
				reference ignored_get() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->_K_storage.raw_value();
				}

				KERBAL_CONSTEXPR
				const_reference ignored_get() const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->_K_storage.raw_value();
				}

				KERBAL_CONSTEXPR14
				reference operator*() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->ignored_get();
				}

				KERBAL_CONSTEXPR
				const_reference operator*() const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->ignored_get();
				}

#			if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				rvalue_reference value() &&
				{
					if (this->empty()) {
						kerbal::optional::bad_optional_access::throw_this_exception();
					}
					return kerbal::compatibility::move(this->ignored_get());
				}

				KERBAL_CONSTEXPR20
				const_rvalue_reference value() const &&
				{
					if (this->empty()) {
						kerbal::optional::bad_optional_access::throw_this_exception();
					}
					return kerbal::compatibility::move(this->ignored_get());
				}

				KERBAL_CONSTEXPR14
				rvalue_reference ignored_get() && noexcept
				{
					return kerbal::compatibility::move(this->_K_storage.raw_value());
				}

				KERBAL_CONSTEXPR
				const_rvalue_reference ignored_get() const && noexcept
				{
					return kerbal::compatibility::move(this->_K_storage.raw_value());
				}

				KERBAL_CONSTEXPR14
				rvalue_reference operator*() && noexcept
				{
					return kerbal::compatibility::move(this->ignored_get());
				}

				KERBAL_CONSTEXPR
				const_rvalue_reference operator*() const && noexcept
				{
					return kerbal::compatibility::move(this->ignored_get());
				}

#			endif


				KERBAL_CONSTEXPR20
				pointer get_pointer()
				{
					if (this->empty()) {
						kerbal::optional::bad_optional_access::throw_this_exception();
					}
					return this->ignored_get_pointer();
				}

				KERBAL_CONSTEXPR20
				const_pointer get_pointer() const
				{
					if (this->empty()) {
						kerbal::optional::bad_optional_access::throw_this_exception();
					}
					return this->ignored_get_pointer();
				}

				KERBAL_CONSTEXPR14
				pointer ignored_get_pointer() KERBAL_NOEXCEPT
				{
					return this->_K_storage.raw_pointer();
				}

				KERBAL_CONSTEXPR
				const_pointer ignored_get_pointer() const KERBAL_NOEXCEPT
				{
					return this->_K_storage.raw_pointer();
				}

				KERBAL_CONSTEXPR14
				pointer operator->() KERBAL_NOEXCEPT
				{
					return this->ignored_get_pointer();
				}

				KERBAL_CONSTEXPR
				const_pointer operator->() const KERBAL_NOEXCEPT
				{
					return this->ignored_get_pointer();
				}

#		if __cplusplus < 201103L

				template <typename U>
				KERBAL_CONSTEXPR
				value_type value_or(U & default_value) const
				{
					return this->has_value() ?
						   this->ignored_get() :
						   static_cast<T>(default_value);
				}

#		else

				template <typename U>
				KERBAL_CONSTEXPR
				value_type value_or(U && default_value) const &
				{
					return this->has_value() ?
						   this->ignored_get() :
						   static_cast<T>(kerbal::utility::forward<U>(default_value));
				}

				template <typename U>
				KERBAL_CONSTEXPR14
				value_type value_or(U && default_value) &&
				{
					return this->has_value() ?
						   kerbal::compatibility::move(this->ignored_get()) :
						   static_cast<T>(kerbal::utility::forward<U>(default_value));
				}

#		endif

				KERBAL_CONSTEXPR14
				reference reference_or(reference default_value) KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->has_value() ?
						   this->ignored_get() :
						   default_value;
				}

				KERBAL_CONSTEXPR
				const_reference reference_or(const_reference default_value) const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->has_value() ?
						   this->ignored_get() :
						   default_value;
				}


			//===================
			// modifier

#	if __cplusplus >= 201103L

				/**
				 * @~English
				 * @brief Emplace-construct by parameters.
				 * @param args parameters
				 * @return This instance.
				 * @note Do reset option beforehand if the instance has value.
				 * @see reset().
				 *
				 * @~Chinese
				 * @brief 使用提供的若干参数, 原位构造.
				 * @param args 参数包
				 * @return 该实例.
				 * @note 若该实例持有值, 将先做清除操作.
				 * @see reset().
				 */
				template <typename ... Args>
				KERBAL_CONSTEXPR14
				optional& emplace(Args&& ... args)
				{
					this->reset();
					this->_K_storage.construct(kerbal::utility::forward<Args>(args)...);
					this->_K_has_value = true;
					return *this;
				}

#	else

#			define EMPTY
#			define REMAINF(exp) exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) KERBAL_MACRO_CONCAT(typename Arg, i)
#			define ARGS_DECL(i) KERBAL_MACRO_CONCAT(const Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				optional& emplace(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
				{ \
					this->reset(); \
					this->_K_storage.construct(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i)); \
					this->_K_has_value = true; \
					return *this; \
				}

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#			undef EMPTY
#			undef REMAINF
#			undef THEAD_NOT_EMPTY
#			undef TARGS_DECL
#			undef ARGS_DECL
#			undef ARGS_USE
#			undef FBODY

#	endif

				KERBAL_CONSTEXPR14
				void reset()
				{
					if (this->has_value()) {
						this->_K_storage.destroy();
						this->_K_has_value = false;
					}
				}

				KERBAL_CONSTEXPR14
				void swap(optional & with)
				{
					if (this->has_value() && with.has_value()) {
						kerbal::algorithm::swap(this->ignored_get(), with.ignored_get());
					} else if (this->has_value() && !with.has_value()) {
						with._K_storage.construct(kerbal::compatibility::to_xvalue(this->ignored_get()));
						with._K_has_value = true;
						this->_K_storage.destroy();
						this->_K_has_value = false;
					} else if (!this->has_value() && with.has_value()) {
						this->_K_storage.construct(kerbal::compatibility::to_xvalue(with.ignored_get()));
						this->_K_has_value = true;
						with._K_storage.destroy();
						with._K_has_value = false;
					}
				}

		};


#	if __cplusplus >= 201103L

		template <typename T>
		KERBAL_CONSTEXPR
		kerbal::optional::optional<
			typename kerbal::type_traits::remove_reference<T>::type
		>
		make_optional(T && value)
		{
			return kerbal::optional::optional<
						typename kerbal::type_traits::remove_reference<T>::type
					>(kerbal::utility::forward<T>(value));
		}

#	else

		template <typename T>
		KERBAL_CONSTEXPR
		kerbal::optional::optional<T>
		make_optional(const T & value)
		{
			return kerbal::optional::optional<T>(value);
		}

#	endif


#	if __cplusplus >= 201103L

		template <typename T, typename ... Args>
		KERBAL_CONSTEXPR
		kerbal::optional::optional<T>
		make_optional(Args && ... args)
		{
			return kerbal::optional::optional<T>(kerbal::utility::in_place_t(), kerbal::utility::forward<Args>(args)...);
		}

#	else

#	define EMPTY
#	define REMAINF(exp) exp
#	define LEFT_JOIN_COMMA(exp) , exp
#	define TARGS_DECL(i) KERBAL_MACRO_CONCAT(typename Arg, i)
#	define ARGS_DECL(i) KERBAL_MACRO_CONCAT(const Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#	define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#	define FBODY(i) \
		template <typename T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
		kerbal::optional::optional<T> \
		make_optional(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
		{ \
			return kerbal::optional::optional<T>(kerbal::utility::in_place_t() KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
		}

		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#	undef EMPTY
#	undef REMAINF
#	undef LEFT_JOIN_COMMA
#	undef TARGS_DECL
#	undef ARGS_DECL
#	undef ARGS_USE
#	undef FBODY

#	endif


#	if __cplusplus >= 201703L

		template <typename T>
		optional(const T &) -> optional<T>;

#	endif

	} // namespace optional


	namespace algorithm
	{

		template <typename T>
		KERBAL_CONSTEXPR14
		void swap(kerbal::optional::optional<T> & a, kerbal::optional::optional<T> & b)
				KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
		{
			a.swap(b);
		}

	} // namespace algorithm


	namespace hash
	{

		template <typename T>
		struct hash<kerbal::optional::optional<T> > :
				public kerbal::optional::optional_hash_template<
						kerbal::optional::optional<T>,
						kerbal::hash::hash<T>,
						static_cast<std::size_t>(-3333)
				>
		{
		};

	} // namespace hash

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN
	template <typename T>
	KERBAL_CONSTEXPR14
	void swap(kerbal::optional::optional<T> & a, kerbal::optional::optional<T> & b)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}
KERBAL_NAMESPACE_STD_END


#include <kerbal/optional/detail/optional_compare.hpp>

#endif // KERBAL_OPTIONAL_OPTIONAL_HPP
