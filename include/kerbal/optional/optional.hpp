/**
 * @file       optional.hpp
 * @brief
 * @date       2018-10-4
 * @author     peter
 * @copyright
 *      peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OPTIONAL_OPTIONAL_HPP
#define KERBAL_OPTIONAL_OPTIONAL_HPP

#include <kerbal/optional/bad_optional_access.hpp>
#include <kerbal/optional/optional_type_traits.hpp>
#include <kerbal/optional/nullopt.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/data_struct/raw_storage.hpp>
#include <kerbal/type_traits/type_traits_details/enable_if.hpp>

namespace kerbal
{
	namespace optional
	{

		template <typename Type>
		class optional: protected kerbal::data_struct::raw_storage<Type>
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

			public:

				/**
				 * @~English
				 * @brief Default constructor.
				 *
				 * @~Chinese
				 * @brief 默认构造函数.
				 */
				KERBAL_CONSTEXPR optional() KERBAL_NOEXCEPT :
						initialized(false)
				{
				}

				template <typename NulloptType>
				explicit KERBAL_CONSTEXPR optional(const NulloptType &,
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
						initialized(false)
				{
					this->construct(src);
					this->initialized = true;
				}

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
				template <typename Up>
				explicit optional(const Up & src,
						typename kerbal::type_traits::enable_if<!is_optional<Up>::value && !is_nullopt<Up>::value, int>::type = 0) :
						initialized(false)
				{
					this->construct(src);
					this->initialized = true;
				}

				/**
				 * @~English
				 * @brief Copy from an instance of std::optional<...>, boost::optional<...> or
				 * 		  any other type Up which makes assert of is_optional<Up>::value is true .
				 * @param src value from
				 * @note The second parameter plays an role of concept traits.
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
					if (src) {
						this->construct(*src);
						this->initialized = true;
					}
				}

				/**
				 * @~English
				 * @brief Copy from an instance of optional.
				 * @param src value from
				 *
				 * @~Chinese
				 * @brief 从一个 optional 类型的实例拷贝构造.
				 * @param src 源值
				 */
				optional(const optional & src) :
						initialized(false)
				{
					if (src) {
						this->construct(src.ignored_get());
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
					if (src) {
						this->construct(src.ignored_get());
						this->initialized = true;
					}
				}

#	if __cplusplus >= 201103L

				explicit optional(value_type && src) :
						initialized(false)
				{
					this->construct(std::move(src));
					this->initialized = true;
				}

				template <typename Up>
				explicit optional(Up && src,
						typename kerbal::type_traits::enable_if<
							!is_optional<Up>::value && !is_nullopt<Up>::value, int>::type = 0) :
						initialized(false)
				{
					this->construct(src);
					this->initialized = true;
				}

				template <typename Up>
				optional(Up && src,
						typename kerbal::type_traits::enable_if<is_optional<Up>::value, int>::type = 0) :
						initialized(false)
				{
					if (src) {
						this->construct(*src);
						this->initialized = true;
					}
				}

				optional(optional<value_type> && src) :
						initialized(false)
				{
					if (src) {
						this->construct(src.raw_value());
						this->initialized = true;
					}
				}

				template <typename Up>
				optional(optional<Up> && src) :
						initialized(false)
				{
					if (src) {
						this->construct(src.ignored_get());
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
				KERBAL_CONSTEXPR bool has_value() const KERBAL_NOEXCEPT
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
				KERBAL_CONSTEXPR bool empty() const KERBAL_NOEXCEPT
				{
					return this->initialized == false;
				}

				explicit KERBAL_CONSTEXPR operator bool() const KERBAL_NOEXCEPT
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

				optional& operator=(const_reference src)
				{
					if (this->has_value()) {
						this->raw_value() = src;
					} else {
						this->construct(src);
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
					if (this->has_value()) {
						this->raw_value() = src;
					} else {
						this->construct(src);
						this->initialized = true;
					}
					return *this;
				}

				template <typename Up>
				typename kerbal::type_traits::enable_if<is_optional<Up>::value, optional&>::type
				operator=(const Up & src)
				{
					if (this->has_value() && static_cast<bool>(src)) {
						this->raw_value() = *src;
					} else if (this->has_value() && !static_cast<bool>(src)) {
						this->destroy();
						this->initialized = false;
					} else if (!this->has_value() && static_cast<bool>(src)) {
						this->construct(*src);
						this->initialized = true;
					}
					return *this;
				}

				optional& operator=(const optional<value_type> & src)
				{
					if (this->has_value() && src.has_value()) {
						this->raw_value() = src.ignored_get();
					} else if (this->has_value() && !src.has_value()) {
						this->destroy();
						this->initialized = false;
					} else if (!this->has_value() && src.has_value()) {
						this->construct(src.ignored_get());
						this->initialized = true;
					}
					return *this;
				}

				template <typename Up>
				optional& operator=(const optional<Up> & src)
				{
					if (this->has_value() && src.has_value()) {
						this->raw_value() = src.ignored_get();
					} else if (this->has_value() && !src.has_value()) {
						this->destroy();
						this->initialized = false;
					} else if (!this->has_value() && src.has_value()) {
						this->construct(src.ignored_get());
						this->initialized = true;
					}
					return *this;
				}

#	if __cplusplus >= 201103L

				optional& operator=(value_type && src)
				{
					if (this->has_value()) {
						this->raw_value() = std::move(src);
					} else {
						this->construct(std::move(src));
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
					if (this->has_value()) {
						this->raw_value() = std::forward<Up>(src);
					} else {
						this->construct(std::forward<Up>(src));
						this->initialized = true;
					}
					return *this;
				}

				template <typename Up>
				typename kerbal::type_traits::enable_if<is_optional<Up>::value, optional&>::type
				operator=(Up && src)
				{
					if (this->has_value() && static_cast<bool>(src)) {
						this->raw_value() = *src;
					} else if (this->has_value() && !static_cast<bool>(src)) {
						this->destroy();
						this->initialized = false;
					} else if (!this->has_value() && static_cast<bool>(src)) {
						this->construct(*src);
						this->initialized = true;
					}
					return *this;
				}

				optional& operator=(optional<value_type> && src)
				{
					if (this->has_value() && src.has_value()) {
						this->raw_value() = src.raw_value();
					} else if (this->has_value() && !src.has_value()) {
						this->destroy();
						this->initialized = false;
					} else if (!this->has_value() && src.has_value()) {
						this->construct(src.raw_value());
						this->initialized = true;
					}
					return *this;
				}

				template <typename Up>
				optional& operator=(optional<Up> && src)
				{
					if (this->has_value() && src.has_value()) {
						this->raw_value() = src.ignored_get();
					} else if (this->has_value() && !src.has_value()) {
						this->destroy();
						this->initialized = false;
					} else if (!this->has_value() && src.has_value()) {
						this->construct(src.ignored_get());
						this->initialized = true;
					}
					return *this;
				}

#	endif

#	if __cplusplus < 201103L

				optional& emplace()
				{
					clear();
					this->construct();
					this->initialized = true;
					return *this;
				}

				template <typename Arg0>
				optional& emplace(const Arg0 & arg0)
				{
					clear();
					this->construct(arg0);
					this->initialized = true;
					return *this;
				}

				template <typename Arg0, typename Arg1>
				optional& emplace(const Arg0 & arg0, const Arg1& arg1)
				{
					clear();
					this->construct(arg0, arg1);
					this->initialized = true;
					return *this;
				}

				template <typename Arg0, typename Arg1, typename Arg2>
				optional& emplace(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2)
				{
					clear();
					this->construct(arg0, arg1, arg2);
					this->initialized = true;
					return *this;
				}


				template <typename Arg0, typename Arg1, typename Arg2, typename Arg3>
				optional& emplace(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2, const Arg3& arg3)
				{
					clear();
					this->construct(arg0, arg1, arg2, arg3);
					this->initialized = true;
					return *this;
				}

				template <typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
				optional& emplace(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2, const Arg3& arg3, const Arg4 & arg4)
				{
					clear();
					this->construct(arg0, arg1, arg2, arg3, arg4);
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
					this->construct(std::forward<Args>(args)...);
					this->initialized = true;
					return *this;
				}

#	endif

				void clear()
				{
					if (this->has_value()) {
						this->destroy();
						this->initialized = false;
					}
				}

				reference value() KERBAL_REFERENCE_OVERLOAD_TAG
				{
					if (!this->has_value()) {
						bad_optional_access::throw_this_exception();
					}
					return ignored_get();
				}

				const_reference value() const KERBAL_REFERENCE_OVERLOAD_TAG
				{
					if (!this->has_value()) {
						bad_optional_access::throw_this_exception();
					}
					return ignored_get();
				}

				reference value_or(reference ano) KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					if (!this->has_value()) {
						return ano;
					}
					return ignored_get();
				}

				const_reference value_or(const_reference ano) const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					if (!this->has_value()) {
						return ano;
					}
					return ignored_get();
				}

				reference ignored_get() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->raw_value();
				}

				const_reference ignored_get() const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->raw_value();
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
					if (!this->has_value()) {
						throw bad_optional_access();
					}
					return std::move(ignored_get());
				}

				const_rvalue_reference value() const &&
				{
					if (!this->has_value()) {
						throw bad_optional_access();
					}
					return std::move(ignored_get());
				}

				rvalue_reference ignored_get() && noexcept
				{
					return std::move(this->raw_value());
				}

				const_rvalue_reference ignored_get() const && noexcept
				{
					return std::move(this->raw_value());
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
					if (!this->has_value()) {
						bad_optional_access::throw_this_exception();
					}
					return this->raw_pointer();
				}

				const_pointer get_pointer() const
				{
					if (!this->has_value()) {
						bad_optional_access::throw_this_exception();
					}
					return this->raw_pointer();
				}

				pointer ignored_get_pointer()
				{
					return this->raw_pointer();
				}

				const_pointer ignored_get_pointer() const
				{
					return this->raw_pointer();
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
					if (this->has_value() && with.has_value()) {
						std::swap(this->raw_value(), with.raw_value());
					} else if (this->has_value() && !with.has_value()) {
						with.construct(kerbal::compatibility::to_xvalue(this->raw_value()));
						with.initialized = true;
						this->destroy();
						this->initialized = false;
					} else if (!this->has_value() && with.has_value()) {
						this->construct(kerbal::compatibility::to_xvalue(with.raw_value()));
						this->initialized = true;
						with.destroy();
						with.initialized = false;
					}
				}
		};

	} /* namespace optional */

} /* namespace kerbal */

namespace std
{
	template <typename Type>
	void swap(kerbal::optional::optional<Type> & a, kerbal::optional::optional<Type> & b) KERBAL_NOEXCEPT
	{
		a.swap(b);
	}
}

#endif /* KERBAL_OPTIONAL_OPTIONAL_HPP */
