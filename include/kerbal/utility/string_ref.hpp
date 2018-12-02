/*
 * string_ref.hpp
 *
 *  Created on: 2018年10月22日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_UTILITY_STRING_REF_HPP_
#define INCLUDE_KERBAL_UTILITY_STRING_REF_HPP_

#include <kerbal/compatibility/compatibility_macro.hpp>

namespace kerbal
{

	namespace utility
	{

		template <typename CharT, typename CharTraits>
		class basic_string_ref
		{
			public:
				typedef CharT char_type;
				typedef char_type * pointer;
				typedef const char_type * const_pointer;
				typedef CharTraits char_traits;
				typedef std::basic_string<char_type, char_traits> string_type;

			private:
				union
				{
						const_pointer s;
						const string_type* str;
				};

				enum
				{
					c_style, string_style
				} status;

			public:
				basic_string_ref(const_pointer s) KERBAL_NOEXCEPT : s(s), status(c_style)
				{
				}

				basic_string_ref(const string_type & s) KERBAL_NOEXCEPT : str(&s), status(string_style)
				{
				}

				operator string_type() const
				{
					switch (status) {
						case c_style:
							return s;
						case string_style:
							return *str;
					}
				}

				basic_string_ref& operator=(const_pointer s) KERBAL_NOEXCEPT
				{
					this->s = s;
					this->status = c_style;
					return *this;
				}

				basic_string_ref& operator=(const string_type & s) KERBAL_NOEXCEPT
				{
					this->str = &s;
					this->status = string_style;
					return *this;
				}

				const_pointer c_str() const
				{
					switch (status) {
						case c_style:
							return s;
						case string_style:
							return str->c_str();
					}
				}

				size_t length() const
				{
					switch (status) {
						case c_style:
							return CharTraits::length(s);
						case string_style:
							return CharTraits::length(str->c_str());
					}
				}

				friend std::ostream& operator<<(std::ostream& out, const basic_string_ref & str_ref)
				{
					switch (str_ref.status) {
						case c_style:
							return out << str_ref.s;
						case string_style:
							return out << str_ref.str;
					}
				}
		};

		typedef basic_string_ref<char, std::char_traits<char> > string_ref;

	} /* namespace utility */

} /* namespace kerbal */



#endif /* INCLUDE_KERBAL_UTILITY_STRING_REF_HPP_ */
