/*
 * optional.hpp
 *
 *  Created on: 2018年10月4日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_HPP_
#define INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_HPP_

#include <stdexcept>
#include <kerbal/type_traits/type_traits.hpp>

namespace kerbal
{
	namespace data_struct
	{
		class bad_optional_access : public std::logic_error
		{
			public:
				bad_optional_access() :
						std::logic_error("bad optional access")
				{
				}
		};

		template <typename Type>
		struct is_kerbal_optional;

		template <typename Type>
		class optional
		{
			public:
				typedef Type value_type;
				typedef Type& reference;
				typedef const Type& const_reference;
				typedef Type* pointer;
				typedef const Type* const_pointer;

			private:
				union
				{
						Type val;
				};

				bool initialized;

			public:
				optional() :
						initialized(false)
				{
				}

				optional(const value_type & val) :
						val(val), initialized(true)
				{
				}

				template <typename Up, typename =
						typename kerbal::type_traits::enable_if<!is_kerbal_optional<Up>::value >::type>
				optional(const Up & val) :
						val(val), initialized(true)
				{
				}

				optional(const optional<value_type> & src) :
						initialized(false)
				{
					if (src.initialized) {
						new (&val) value_type(src.val);
						this->initialized = true;
					}
				}

				template <typename Up>
				optional(const optional<Up> & src) :
						initialized(false)
				{
					if (src.initialized) {
						new (&val) value_type(src.val);
						this->initialized = true;
					}
				}

#	if __cplusplus >= 201103L

				optional(value_type && val) :
						val(std::move(val)), initialized(true)
				{
				}

				template <typename Up, typename =
						typename kerbal::type_traits::enable_if<!is_kerbal_optional<Up>::value >::type>
				optional(Up && val) :
						val(std::move(val)), initialized(true)
				{
				}

				optional(optional && src) :
						initialized(false)
				{
					if (src.initialized) {
						new (&val) value_type(std::move(src.val));
						this->initialized = true;
						src.initialized = false;
					}
				}

				template <typename Up>
				optional(optional<Up> && src) :
						initialized(false)
				{
					if (src.initialized) {
						new (&val) value_type(std::move(src.val));
						this->initialized = true;
						src.initialized = false;
					}
				}
#	endif

				~optional()
				{
					clear();
				}

				bool has_value() const
				{
					return this->initialized;
				}

				operator bool() const
				{
					return this->has_value();
				}

				optional& operator=(const value_type & src)
				{
					if (this->initialized) {
						this->val = src;
					} else {
						new (&val) value_type(src);
						this->initialized = true;
					}
					return *this;
				}

				template <typename Up, typename =
						typename kerbal::type_traits::enable_if<!is_kerbal_optional<Up>::value >::type>
				optional& operator=(const Up & src)
				{
					if (this->initialized) {
						this->val = src;
					} else {
						new (&val) value_type(src);
						this->initialized = true;
					}
					return *this;
				}

				optional& operator=(const optional & src)
				{
					if (this->initialized && src.initialized) {
						this->val = src.val;
					} else if (this->initialized && !src.initialized) {
						(&val)->~value_type();
						this->initialized = false;
					} else if (!this->initialized && src.initialized) {
						new (&val) value_type(src.val);
						this->initialized = true;
					}
					return *this;
				}

#	if __cplusplus >= 201103L

				optional& operator=(value_type && src)
				{
					if (this->initialized) {
						this->val = std::move(src);
					} else {
						new (&val) value_type(std::move(src));
						this->initialized = true;
					}
					return *this;
				}

				template <typename Up, typename =
						typename kerbal::type_traits::enable_if<!is_kerbal_optional<Up>::value >::type>
				optional& operator=(Up && src)
				{
					if (this->initialized) {
						this->val = std::move(src);
					} else {
						new (&val) value_type(std::move(src));
						this->initialized = true;
					}
					return *this;
				}

				optional& operator=(optional && src)
				{
					if (this->initialized && src.initialized) {
						this->val = std::move(src.val);
						src.initialized = false;
					} else if (this->initialized && !src.initialized) {
						(&val)->~value_type();
						this->initialized = false;
					} else if (!this->initialized && src.initialized) {
						new (&val) value_type(std::move(src.val));
						this->initialized = true;
						src.initialized = false;
					}
					return *this;
				}

#	endif

				void clear()
				{
					if (this->initialized) {
						(&val)->~value_type();
					}
				}

				reference get()
				{
					if (!initialized) {
						throw bad_optional_access();
					}
					return val;
				}

				const_reference get() const
				{
					if (!initialized) {
						throw bad_optional_access();
					}
					return val;
				}

				reference operator*()
				{
					return this->get();
				}

				const_reference operator*() const
				{
					return this->get();
				}

				pointer get_pointer()
				{
					if (!initialized) {
						throw bad_optional_access();
					}
					return &val;
				}

				const_pointer get_pointer() const
				{
					if (!initialized) {
						throw bad_optional_access();
					}
					return &val;
				}

				pointer operator->()
				{
					return this->get_pointer();
				}

				const_pointer operator->() const
				{
					return this->get_pointer();
				}
		};

		template <typename Type>
		struct is_kerbal_optional: kerbal::type_traits::false_type
		{
		};

		template <typename Type>
		struct is_kerbal_optional<kerbal::data_struct::optional<Type> >: kerbal::type_traits::true_type
		{
		};

		template <typename Type>
		struct is_kerbal_optional<kerbal::data_struct::optional<Type>& >: kerbal::type_traits::true_type
		{
		};

		template <typename Type>
		struct is_kerbal_optional<const kerbal::data_struct::optional<Type>& >: kerbal::type_traits::true_type
		{
		};

#	if __cplusplus >= 201103L
		template <typename Type>
		struct is_kerbal_optional<kerbal::data_struct::optional<Type>&& >: kerbal::type_traits::true_type
		{
		};
#	endif

	}
}



#endif /* INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_HPP_ */
