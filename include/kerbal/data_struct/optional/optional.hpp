/*
 * optional.hpp
 *
 *  Created on: 2018年10月4日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_OPTIONAL_HPP
#define INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_OPTIONAL_HPP

#include <kerbal/data_struct/optional/bad_optional_access.hpp>
#include <kerbal/data_struct/optional/raw_optional.hpp>
#include <kerbal/data_struct/optional/optional_type_traits.hpp>
#include <kerbal/data_struct/optional/nullopt.hpp>
#include <kerbal/compatibility/compatibility_macro.hpp>
#include <kerbal/type_traits/type_traits_details/enable_if.hpp>

namespace kerbal
{
	namespace data_struct
	{

		template <typename Type>
		class optional: protected raw_optional<Type>
		{
			public:
				typedef Type value_type;
				typedef Type& reference;
				typedef const Type& const_reference;
				typedef Type* pointer;
				typedef const Type* const_pointer;

#	if __cplusplus >= 201103L
				typedef Type&& rvalue_reference;
				typedef const Type&& const_rvalue_reference;
#	endif

			protected:
				///@~English
				///@brief Mark whether the instance has value.
				///
				///@~Chinese
				///@brief 标记该实例是否含值.
				bool initialized;

				///@~English
				///@brief supper type
				///
				///@~Chinese
				///@brief 父类型
				typedef raw_optional <Type> supper_t;

			public:

				/**
				 * @~English
				 * @brief Default constructor.
				 *
				 * @~Chinese
				 * @brief 默认构造函数.
				 */
				optional() KERBAL_NOEXCEPT :
						initialized(false)
				{
				}

				template <typename NulloptType>
				explicit optional(const NulloptType &,
						typename kerbal::type_traits::enable_if<is_nullopt<NulloptType>::value, int>::type = 0) KERBAL_NOEXCEPT :
						initialized(false)
				{
				}

				/**
				 * @~English
				 * @brief Copy from an instance of current type.
				 * @param src value from
				 *
				 * @~Chinese
				 * @brief 从当前类型的一个实例拷贝构造.
				 * @param src 源值
				 */
				explicit optional(const value_type & src) :
						supper_t(src), initialized(true)
				{
				}

				/**
				 * @~English
				 * @brief Copy from an instance of another type.
				 * @param src value from
				 * @note The second parameter play an role of concept traits.
				 *
				 * @~Chinese
				 * @brief 从不同类型的一个实例拷贝构造.
				 * @param src 源值
				 * @note 第二个参数起到概念约束的作用, 无实义.
				 */
				template <typename Up>
				explicit optional(const Up & src,
						typename kerbal::type_traits::enable_if<!is_optional<Up>::value && !is_nullopt<Up>::value, int>::type = 0) :
						supper_t(src), initialized(true)
				{
				}

				/**
				 * @~English
				 * @brief Copy from an instance of std::optional<...>, boost::optional<...> or
				 * 		  any other type Up which makes assert of is_optional<Up>::value is true .
				 * @param src value from
				 * @note The second parameter play an role of concept traits.
				 *
				 * @~Chinese
				 * @brief 从一个 std::optional<...>, boost::optional<...> 或其他任何使 is_optional<Up>::value
				 * 		  断言为 true 的类型的实例拷贝构造.
				 * @param src 源值
				 * @note 第二个参数起到概念约束的作用, 无实义.
				 */
				template <typename Up>
				explicit optional(const Up & src,
						typename kerbal::type_traits::enable_if<is_optional<Up>::value, int>::type = 0) :
						initialized(false)
				{
					if ((bool)(src)) {
						supper_t::construct(*src);
						this->initialized = true;
					}
				}

				/**
				 * @~English
				 * @brief Copy from an instance of optional<value_type>.
				 * @param src value from
				 *
				 * @~Chinese
				 * @brief 从一个 optional<value_type> 类型的实例拷贝构造.
				 * @param src 源值
				 */
				optional(const optional<value_type> & src) :
						initialized(false)
				{
					if (src.initialized) {
						supper_t::construct(src.ignored_get());
						this->initialized = true;
					}
				}

				/**
				 * @brief Copy from an instance of optional which contains another type.
				 * @param src value from
				 */
				template <typename Up>
				explicit optional(const optional<Up> & src) :
						initialized(false)
				{
					if (src.has_value()) {
						supper_t::construct(src.ignored_get());
						this->initialized = true;
					}
				}

#	if __cplusplus >= 201103L

				explicit optional(value_type && src) :
						supper_t(std::forward<value_type>(src)), initialized(true)
				{
				}

				template <typename Up>
				explicit optional(Up && src,
						typename kerbal::type_traits::enable_if<
							!is_optional<Up>::value && !is_nullopt<Up>::value, int>::type = 0) :
						supper_t(std::forward<Up>(src)), initialized(true)
				{
				}

				template <typename Up>
				optional(Up && src,
						typename kerbal::type_traits::enable_if<is_optional<Up>::value, int>::type = 0) :
						initialized(false)
				{
					if ((bool)(src)) {
						supper_t::construct(std::forward<decltype(*src)>(*src));
						this->initialized = true;
					}
				}

				optional(optional<value_type> && src) :
						initialized(false)
				{
					if (src.initialized) {
						supper_t::construct(std::forward<value_type>(src.raw_value()));
						this->initialized = true;
					}
				}

				template <typename Up>
				optional(optional<Up> && src) :
						initialized(false)
				{
					if (src.has_value()) {
						supper_t::construct(std::forward<Up>(src.ignored_get()));
						this->initialized = true;
					}
				}
#	endif

				/**
				 * @~English
				 * @brief Destructor.
				 *
				 * @~Chinese
				 * @brief 析构函数.
				 */
				~optional()
				{
					clear();
				}

				/**
				 * @~English
				 * @brief Test whether the instance has value.
				 * @return Return true if the instance has value.
				 *
				 * @~Chinese
				 * @brief 测试该实例是否含值.
				 * @return 若含值, 返回 true.
				 */
				bool has_value() const KERBAL_NOEXCEPT
				{
					return this->initialized;
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
				bool empty() const KERBAL_NOEXCEPT
				{
					return this->initialized == false;
				}

				explicit operator bool() const KERBAL_NOEXCEPT
				{
					return this->has_value();
				}

				template <typename NulloptType>
				typename kerbal::type_traits::enable_if<
						is_nullopt<NulloptType>::value,
				optional&>::type
				operator=(const NulloptType &)
				{
					clear();
					return *this;
				}

				optional& operator=(const value_type & src)
				{
					if (this->initialized) {
						supper_t::raw_value() = src;
					} else {
						supper_t::construct(src);
						this->initialized = true;
					}
					return *this;
				}

				template <typename Up>
				typename kerbal::type_traits::enable_if<
					!is_optional<Up>::value && !is_nullopt<Up>::value,
				optional&>::type
				operator=(const Up & src)
				{
					if (this->initialized) {
						supper_t::raw_value() = src;
					} else {
						supper_t::construct(src);
						this->initialized = true;
					}
					return *this;
				}

				template <typename Up>
				typename kerbal::type_traits::enable_if<is_optional<Up>::value, optional&>::type
				operator=(const Up & src)
				{
					if (this->initialized && (bool) (src)) {
						supper_t::raw_value() = *src;
					} else if (this->initialized && !(bool) (src)) {
						supper_t::destroy();
						this->initialized = false;
					} else if (!this->initialized && (bool) (src)) {
						supper_t::construct(*src);
						this->initialized = true;
					}
					return *this;
				}

				optional& operator=(const optional<value_type> & src)
				{
					if (this->initialized && src.initialized) {
						supper_t::raw_value() = src.supper_t::raw_value();
					} else if (this->initialized && !src.initialized) {
						supper_t::destroy();
						this->initialized = false;
					} else if (!this->initialized && src.initialized) {
						supper_t::construct(src.supper_t::raw_value());
						this->initialized = true;
					}
					return *this;
				}

				template <typename Up>
				optional& operator=(const optional<Up> & src)
				{
					if (this->initialized && src.has_value()) {
						supper_t::raw_value() = src.ignored_get();
					} else if (this->initialized && !src.has_value()) {
						supper_t::destroy();
						this->initialized = false;
					} else if (!this->initialized && src.has_value()) {
						supper_t::construct(src.ignored_get());
						this->initialized = true;
					}
					return *this;
				}

#	if __cplusplus >= 201103L

				optional& operator=(value_type && src)
				{
					if (this->initialized) {
						supper_t::raw_value() = std::forward<value_type>(src);
					} else {
						supper_t::construct(std::forward<value_type>(src));
						this->initialized = true;
					}
					return *this;
				}

				template <typename Up>
				typename kerbal::type_traits::enable_if<
						!is_optional<Up>::value && !is_nullopt<Up>::value,
				optional&>::type
				operator=(Up && src)
				{
					if (this->initialized) {
						supper_t::raw_value() = std::forward<Up>(src);
					} else {
						supper_t::construct(std::forward<Up>(src));
						this->initialized = true;
					}
					return *this;
				}

				template <typename Up>
				typename kerbal::type_traits::enable_if<is_optional<Up>::value, optional&>::type
				operator=(Up && src)
				{
					if (this->initialized && (bool)(src)) {
						supper_t::raw_value() = std::forward<decltype(*src)>(*src);
					} else if (this->initialized && !(bool)(src)) {
						supper_t::destroy();
						this->initialized = false;
					} else if (!this->initialized && (bool)(src)) {
						supper_t::construct(std::forward<decltype(*src)>(*src));
						this->initialized = true;
					}
					return *this;
				}

				optional& operator=(optional<value_type> && src)
				{
					if (this->initialized && src.initialized) {
						supper_t::raw_value() = std::forward<value_type>(src.raw_value());
					} else if (this->initialized && !src.initialized) {
						supper_t::destroy();
						this->initialized = false;
					} else if (!this->initialized && src.initialized) {
						supper_t::construct(std::forward<value_type>(src.raw_value()));
						this->initialized = true;
					}
					return *this;
				}

				template <typename Up>
				optional& operator=(optional<Up> && src)
				{
					if (this->initialized && src.has_value()) {
						supper_t::raw_value() = std::forward<Up>(src.ignored_get());
					} else if (this->initialized && !src.has_value()) {
						supper_t::destroy();
						this->initialized = false;
					} else if (!this->initialized && src.has_value()) {
						supper_t::construct(std::forward<Up>(src.ignored_get()));
						this->initialized = true;
					}
					return *this;
				}

#	endif

#	if __cplusplus < 201103L

				optional& emplace()
				{
					clear();
					supper_t::construct();
					this->initialized = true;
					return *this;
				}

				template <typename Arg0>
				optional& emplace(const Arg0 & arg0)
				{
					clear();
					supper_t::construct(arg0);
					this->initialized = true;
					return *this;
				}

				template <typename Arg0, typename Arg1>
				optional& emplace(const Arg0 & arg0, const Arg1& arg1)
				{
					clear();
					supper_t::construct(arg0, arg1);
					this->initialized = true;
					return *this;
				}

				template <typename Arg0, typename Arg1, typename Arg2>
				optional& emplace(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2)
				{
					clear();
					supper_t::construct(arg0, arg1, arg2);
					this->initialized = true;
					return *this;
				}


				template <typename Arg0, typename Arg1, typename Arg2, typename Arg3>
				optional& emplace(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2, const Arg3& arg3)
				{
					clear();
					supper_t::construct(arg0, arg1, arg2, arg3);
					this->initialized = true;
					return *this;
				}

				template <typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
				optional& emplace(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2, const Arg3& arg3, const Arg4 & arg4)
				{
					clear();
					supper_t::construct(arg0, arg1, arg2, arg3, arg4);
					this->initialized = true;
					return *this;
				}


#	else

				/**
				 * @~English
				 * @brief Emplace-construct by parameters.
				 * @param args parameters
				 * @return This instance.
				 * @note Do clear option beforehand if the instance has value.
				 * @see clear().
				 *
				 * @~Chinese
				 * @brief 使用提供的若干参数, 原位构造.
				 * @param args 参数包
				 * @return 该实例.
				 * @note 若该实例持有值, 将先做清除操作.
				 * @see clear().
				 */
				template <typename ... Args>
				optional& emplace(Args && ... args)
				{
					clear();
					supper_t::construct(std::forward<Args>(args)...);
					this->initialized = true;
					return *this;
				}

#	endif

				void clear()
				{
					if (this->initialized) {
						supper_t::destroy();
						this->initialized = false;
					}
				}

				reference value() KERBAL_REFERENCE_OVERLOAD_TAG
				{
					if (!initialized) {
						throw bad_optional_access();
					}
					return ignored_get();
				}

				const_reference value() const KERBAL_REFERENCE_OVERLOAD_TAG
				{
					if (!initialized) {
						throw bad_optional_access();
					}
					return ignored_get();
				}

				reference value_or(reference ano) KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					if (!initialized) {
						return ano;
					}
					return ignored_get();
				}

				const_reference value_or(const_reference ano) const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					if (!initialized) {
						return ano;
					}
					return ignored_get();
				}

				reference ignored_get() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return supper_t::raw_value();
				}

				const_reference ignored_get() const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return supper_t::raw_value();
				}

				reference operator*() KERBAL_REFERENCE_OVERLOAD_TAG
				{
					return this->value();
				}

				const_reference operator*() const KERBAL_REFERENCE_OVERLOAD_TAG
				{
					return this->value();
				}

#			if __cplusplus >= 201103L

				rvalue_reference value() &&
				{
					if (!initialized) {
						throw bad_optional_access();
					}
					return std::move(ignored_get());
				}

				const_rvalue_reference value() const &&
				{
					if (!initialized) {
						throw bad_optional_access();
					}
					return std::move(ignored_get());
				}

				rvalue_reference ignored_get() && noexcept
				{
					return std::move(supper_t::raw_value());
				}

				const_rvalue_reference ignored_get() const && noexcept
				{
					return std::move(supper_t::raw_value());
				}

				rvalue_reference operator*() &&
				{
					return std::move(this->value());
				}

				const_rvalue_reference operator*() const &&
				{
					return std::move(this->value());
				}

#			endif


				pointer get_pointer()
				{
					if (!initialized) {
						throw bad_optional_access();
					}
					return supper_t::raw_pointer();
				}

				const_pointer get_pointer() const
				{
					if (!initialized) {
						throw bad_optional_access();
					}
					return supper_t::raw_pointer();
				}

				pointer ignored_get_pointer()
				{
					return supper_t::raw_pointer();
				}

				const_pointer ignored_get_pointer() const
				{
					return supper_t::raw_pointer();
				}

				pointer operator->()
				{
					return this->get_pointer();
				}

				const_pointer operator->() const
				{
					return this->get_pointer();
				}

				void swap(optional & with)
				{
					if (this->initialized && with.initialized) {
						std::swap(this->supper_t::raw_value(), with.supper_t::raw_value());
					} else if (this->initialized && !with.initialized) {

#		if __cplusplus < 201103L
						with.construct(this->raw_value());
#		else
						with.construct(std::move(this->raw_value()));
#		endif
						with.initialized = true;
						this->destroy();
						this->initialized = false;
					} else if (!this->initialized && with.initialized) {

#		if __cplusplus < 201103L
						this->construct(with.raw_value());
#		else
						this->construct(std::move(with.raw_value()));
#		endif
						this->initialized = true;
						with.destroy();
						with.initialized = false;
					}
				}
		};

	} /* namespace data_struct */

} /* namespace kerbal */

namespace std
{
	template <typename Type>
	void swap(kerbal::data_struct::optional<Type> & a, kerbal::data_struct::optional<Type> & b) KERBAL_NOEXCEPT
	{
		a.swap(b);
	}
}

#endif /* INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_OPTIONAL_HPP */
