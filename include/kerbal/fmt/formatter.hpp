/**
 * @file       formatter.hpp
 * @brief
 * @date       2020-10-07
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_FMT_FORMATTER_HPP
#define KERBAL_FMT_FORMATTER_HPP

#include <kerbal/type_traits/sign_deduction.hpp>

#include <climits>
#include <string>

namespace kerbal
{

	namespace fmt
	{

		template <typename T, typename CharT = char>
		struct formatter;


//		template <typename T, typename CharT>
//		struct formatter
//		{
//				template <typename OutputIterator, typename ForwardIterator>
//				OutputIterator format(OutputIterator out, ForwardIterator fmt_first, ForwardIterator fmt_last, const T & value)
//				{
//					std::basic_string<CharT> formatted_str(value);
//					return kerbal::algorithm::copy(formatted_str.cbegin(), formatted_str.cend(), out);
//				}
//		};

		template <typename CharT>
		struct fill_and_align_parse_helper
		{
			protected:
				CharT fill_c;
				CharT align_c;

				fill_and_align_parse_helper(CharT default_fill_c, CharT default_align_c):
						fill_c(default_fill_c), align_c(default_align_c)
				{
				}

				template <typename ForwardIterator>
				void parse_fill_and_align(ForwardIterator & fmt_first, ForwardIterator & fmt_last)
				{
					if (fmt_first == fmt_last) {
						return;
					}
					if (*fmt_first == '<' || *fmt_first == '^' || *fmt_first == '>') {
						align_c = *fmt_first;
						++fmt_first;
					} else {
						CharT t = *fmt_first;
						ForwardIterator it = fmt_first;
						++it;
						if (it == fmt_last) {
							return;
						}
						if (*it == '<' || *it == '^' || *it == '>') {
							fill_c = t;
							align_c = *it;
							fmt_first = it;
							++fmt_first;
						}
					}
				}

		};

		template <typename CharT>
		struct sign_parse_helper
		{
			protected:
				CharT sign_c;

				sign_parse_helper(CharT default_sign_c):
						sign_c(default_sign_c)
				{
				}

				template <typename ForwardIterator>
				void parse_sign(ForwardIterator & fmt_first, ForwardIterator & fmt_last)
				{
					if (fmt_first == fmt_last) {
						return;
					}
					if (*fmt_first == '+' || *fmt_first == '-' || *fmt_first == ' ') {
						sign_c = *fmt_first;
						++fmt_first;
					}
				}

		};

		template <typename CharT>
		struct width_parse_helper
		{
			protected:
				size_t width;

				width_parse_helper(size_t default_width):
						width(default_width)
				{
				}

				template <typename ForwardIterator>
				void parse_width(ForwardIterator & fmt_first, ForwardIterator & fmt_last)
				{
					if (fmt_first == fmt_last) {
						return;
					}
					if (*fmt_first >= '0' && *fmt_first <= '9') {
						width = *fmt_first - '0';
						++fmt_first;
					}
					while (fmt_first != fmt_last && *fmt_first >= '0' && *fmt_first <= '9') {
						width *= 10;
						width += *fmt_first - '0';
						++fmt_first;
					}
				}

		};

		template <typename CharT>
		struct formatter<bool, CharT>:
				fill_and_align_parse_helper<CharT>,
				width_parse_helper<CharT>
		{
				formatter():
						fill_and_align_parse_helper<CharT>(' ', '<'),
						width_parse_helper<CharT>(0)
				{
				}

				template <typename OutputIterator, typename ForwardIterator>
				OutputIterator format(OutputIterator out, ForwardIterator fmt_first, ForwardIterator fmt_last, const bool & value)
				{
					this->parse_fill_and_align(fmt_first, fmt_last);
					this->parse_width(fmt_first, fmt_last);

					std::basic_string<CharT> formatted_str;

					if (value) {
						formatted_str = {'t', 'r', 'u', 'e'};
					} else {
						formatted_str = {'f', 'a', 'l', 's', 'e'};
					}

					if (this->width > formatted_str.size()) {
						switch (this->align_c) {
							case '<': {
								kerbal::algorithm::copy(formatted_str.cbegin(), formatted_str.cend(), out);
								size_t n = this->width - formatted_str.size();
								while (n != 0) {
									--n;
									*out = this->fill_c; ++out;
								}
								break;
							}
							case '^': {
								size_t n = this->width - formatted_str.size();
								size_t left = n / 2;
								size_t right = n - left;
								for (size_t i = 0; i < left; ++i) {
									*out = this->fill_c; ++out;
								}
								kerbal::algorithm::copy(formatted_str.cbegin(), formatted_str.cend(), out);
								for (size_t i = 0; i < right; ++i) {
									*out = this->fill_c; ++out;
								}
								break;
							}
							case '>': {
								size_t n = this->width - formatted_str.size();
								while (n != 0) {
									--n;
									*out = this->fill_c; ++out;
								}
								kerbal::algorithm::copy(formatted_str.cbegin(), formatted_str.cend(), out);
								break;
							}
						}
					} else {
						kerbal::algorithm::copy(formatted_str.cbegin(), formatted_str.cend(), out);
					}
					return out;
				}
		};



		template <typename CharTs, typename CharT>
		struct char_formatter
		{
				template <typename OutputIterator, typename ForwardIterator>
				OutputIterator format(OutputIterator out, ForwardIterator fmt_first, ForwardIterator fmt_last, const CharTs & value)
				{
					*out = value; ++out;
					return out;
				}
		};

		template <typename CharT>
		struct formatter<char, CharT>: char_formatter<char, CharT> {};

		template <typename CharT>
		struct formatter<wchar_t, CharT>: char_formatter<wchar_t, CharT> {};


		template <typename CharTs, typename CharT>
		struct plain_string_formatter
		{
				template <typename OutputIterator, typename ForwardIterator>
				OutputIterator format(OutputIterator out, ForwardIterator fmt_first, ForwardIterator fmt_last, CharTs * const & value)
				{
					CharTs * p = value;
					while (*p != CharTs()) {
						*out = *p;
						++out;
						++p;
					}
					return out;
				}
		};

		template <typename CharT>
		struct formatter<char*, CharT>: plain_string_formatter<const char, CharT> {};

		template <typename CharT>
		struct formatter<const char*, CharT>: plain_string_formatter<const char, CharT> {};

		template <typename CharT>
		struct formatter<wchar_t*, CharT>: plain_string_formatter<const wchar_t, CharT> {};

		template <typename CharT>
		struct formatter<const wchar_t*, CharT>: plain_string_formatter<const wchar_t, CharT> {};


		template <size_t N, typename CharT>
		struct formatter<char[N], CharT>: plain_string_formatter<const char, CharT> {};

		template <size_t N, typename CharT>
		struct formatter<const char[N], CharT>: plain_string_formatter<const char, CharT> {};

		template <size_t N, typename CharT>
		struct formatter<wchar_t[N], CharT>: plain_string_formatter<const wchar_t, CharT> {};

		template <size_t N, typename CharT>
		struct formatter<const wchar_t[N], CharT>: plain_string_formatter<const wchar_t, CharT> {};


		template <typename CharTs, typename CharT>
		struct formatter<std::basic_string<CharTs>, CharT>
		{
				template <typename OutputIterator, typename ForwardIterator>
				OutputIterator format(OutputIterator out, ForwardIterator fmt_first, ForwardIterator fmt_last, const std::basic_string<CharTs> & value)
				{
					return kerbal::algorithm::copy(value.begin(), value.end(), out);
				}
		};

		template <typename Integral, typename CharT, bool is_signed = kerbal::type_traits::is_signed<Integral>::value>
		struct integral_formatter: fill_and_align_parse_helper<CharT>, sign_parse_helper<CharT>, width_parse_helper<CharT>
		{
				integral_formatter():
						fill_and_align_parse_helper<CharT>(' ', '>'),
						sign_parse_helper<CharT>('-'),
						width_parse_helper<CharT>(0)
				{
				}

				template <typename OutputIterator, typename ForwardIterator>
				OutputIterator
				format(OutputIterator out, ForwardIterator fmt_first, ForwardIterator fmt_last, const Integral & value)
				{
//					std::cout << "args: " << std::string(fmt_first, fmt_last) << std::endl;

					this->parse_fill_and_align(fmt_first, fmt_last);
					this->parse_sign(fmt_first, fmt_last);
					this->parse_width(fmt_first, fmt_last);

					CharT type_c = 'd';

					std::basic_string<CharT> formatted_str; {
						Integral d = value;
						if (d < 0) {
							d = -d;
						}
						switch (type_c) {
							case 'b': {
								while (d != 0) {
									formatted_str += d % 2 + '0';
									d /= 2;
								}
								if (value == 0) {
									formatted_str += '0';
								}
								formatted_str += 'b';
								formatted_str += '0';
								break;
							}
							case 'B': {
								while (d != 0) {
									formatted_str += d % 2 + '0';
									d /= 2;
								}
								if (value == 0) {
									formatted_str += '0';
								}
								formatted_str += 'B';
								formatted_str += '0';
								break;
							}
							case 'd': {
								while (d != 0) {
									formatted_str += d % 10 + '0';
									d /= 10;
								}
								if (value == 0) {
									formatted_str += '0';
								}
								break;
							}
							case 'o': {
								while (d != 0) {
									formatted_str += d % 8 + '0';
									d /= 8;
								}
								formatted_str += '0';
								break;
							}
							case 'x': {
								while (d != 0) {
									int t = d % 16;
									formatted_str += t > 9 ? t - 10 + 'a' : t + '0';
									d /= 16;
								}
								if (value == 0) {
									formatted_str += '0';
								}
								formatted_str += 'x';
								formatted_str += '0';
								break;
							}
							case 'X': {
								while (d != 0) {
									int t = d % 16;
									formatted_str += t > 9 ? t - 10 + 'A' : t + '0';
									d /= 16;
								}
								if (value == 0) {
									formatted_str += '0';
								}
								formatted_str += 'X';
								formatted_str += '0';
								break;
							}
						}
					}

					switch (this->sign_c) {
						case '-': {
							if (value < 0) {
								formatted_str += '-';
							}
							break;
						}
						case '+':
						case ' ': {
							if (value < 0) {
								formatted_str += '-';
							} else {
								formatted_str += this->sign_c;
							}
							break;
						}
					}

					kerbal::algorithm::reverse(formatted_str.begin(), formatted_str.end());

					if (this->width > formatted_str.size()) {
						switch (this->align_c) {
							case '<': {
								kerbal::algorithm::copy(formatted_str.cbegin(), formatted_str.cend(), out);
								size_t n = this->width - formatted_str.size();
								while (n != 0) {
									--n;
									*out = this->fill_c; ++out;
								}
								break;
							}
							case '^': {
								size_t n = this->width - formatted_str.size();
								size_t left = n / 2;
								size_t right = n - left;
								for (size_t i = 0; i < left; ++i) {
									*out = this->fill_c; ++out;
								}
								kerbal::algorithm::copy(formatted_str.cbegin(), formatted_str.cend(), out);
								for (size_t i = 0; i < right; ++i) {
									*out = this->fill_c; ++out;
								}
								break;
							}
							case '>': {
								size_t n = this->width - formatted_str.size();
								while (n != 0) {
									--n;
									*out = this->fill_c; ++out;
								}
								kerbal::algorithm::copy(formatted_str.cbegin(), formatted_str.cend(), out);
								break;
							}
						}
					} else {
						kerbal::algorithm::copy(formatted_str.cbegin(), formatted_str.cend(), out);
					}
					return out;

				}
		};

		template <typename Integral, typename CharT>
		struct integral_formatter<Integral, CharT, false>: fill_and_align_parse_helper<CharT>, sign_parse_helper<CharT>, width_parse_helper<CharT>
		{
				integral_formatter():
						fill_and_align_parse_helper<CharT>(' ', '>'),
						sign_parse_helper<CharT>('-'),
						width_parse_helper<CharT>(0)
				{
				}

				template <typename OutputIterator, typename ForwardIterator>
				OutputIterator
				format(OutputIterator out, ForwardIterator fmt_first, ForwardIterator fmt_last, const Integral & value)
				{
					this->parse_fill_and_align(fmt_first, fmt_last);
					this->parse_sign(fmt_first, fmt_last);
					this->parse_width(fmt_first, fmt_last);

					std::basic_string<CharT> formatted_str; {
						Integral d = value;
						while (d != 0) {
							formatted_str += d % 10 + '0';
							d /= 10;
						}
					}

					return kerbal::algorithm::copy(formatted_str.crbegin(), formatted_str.crend(), out);
				}
		};

		template <typename CharT>
		struct formatter<short, CharT>: integral_formatter<short, CharT> {};

		template <typename CharT>
		struct formatter<unsigned short, CharT>: integral_formatter<unsigned short, CharT> {};

		template <typename CharT>
		struct formatter<int, CharT>: integral_formatter<int, CharT> {};

		template <typename CharT>
		struct formatter<unsigned int, CharT>: integral_formatter<unsigned int, CharT> {};

		template <typename CharT>
		struct formatter<long, CharT>: integral_formatter<long, CharT> {};

		template <typename CharT>
		struct formatter<unsigned long, CharT>: integral_formatter<unsigned long, CharT> {};

		template <typename CharT>
		struct formatter<long long, CharT>: integral_formatter<long long, CharT> {};

		template <typename CharT>
		struct formatter<unsigned long long, CharT>: integral_formatter<unsigned long long, CharT> {};



		template <typename T, typename CharT>
		struct tmp_formatter
		{
				template <typename OutputIterator, typename ForwardIterator>
				OutputIterator
				format(OutputIterator out, ForwardIterator fmt_first, ForwardIterator fmt_last, const T & value)
				{
					std::basic_string<CharT> formatted_str(std::to_string(value));
					return kerbal::algorithm::copy(formatted_str.cbegin(), formatted_str.cend(), out);
				}
		};

		template <typename CharT>
		struct formatter<float, CharT>: tmp_formatter<float, CharT> {};

		template <typename CharT>
		struct formatter<double, CharT>: tmp_formatter<double, CharT> {};

		template <typename T, typename CharT>
		struct formatter<T*, CharT>
		{
				template <typename OutputIterator, typename ForwardIterator>
				OutputIterator format(OutputIterator out, ForwardIterator fmt_first, ForwardIterator fmt_last, T* const & value)
				{
					*out = '0'; ++out;
					*out = 'x'; ++out;
					size_t d = reinterpret_cast<size_t>(value);

					size_t i = sizeof(void*) * 2;
					--i;
					while (i != 0 && (d >> i * 4) % 16 == 0) {
						--i;
					}
					if (i == 0) {
						*out = '0'; ++out;
					} else {
						while (i != 0) {
							--i;
							int m = (d >> i * 4) % 16;
							if (m < 10) {
								*out = m + '0';
							} else {
								*out = m - 10 + 'a';
							}
							++out;
						}
					}
					return out;
				}
		};

#	if __cplusplus >= 201103L

		template <typename CharT>
		struct formatter<std::nullptr_t, CharT>
		{
				template <typename OutputIterator, typename ForwardIterator>
				OutputIterator format(OutputIterator out, ForwardIterator fmt_first, ForwardIterator fmt_last, std::nullptr_t const & value)
				{
					constexpr const char formatted_str [] = {'n', 'u', 'l', 'l', 'p', 't', 'r'};
					return kerbal::algorithm::copy(formatted_str, formatted_str + 7, out);
				}
		};

#	endif

	} // namespace fmt

} // namespace kerbal

#endif // KERBAL_FMT_FORMATTER_HPP
