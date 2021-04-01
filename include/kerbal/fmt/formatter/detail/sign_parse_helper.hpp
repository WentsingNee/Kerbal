/**
 * @file       sign_parse_helper.hpp
 * @brief
 * @date       2024-08-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_FMT_FORMATTER_DETAIL_SIGN_PARSE_HELPER_HPP
#define KERBAL_FMT_FORMATTER_DETAIL_SIGN_PARSE_HELPER_HPP

namespace kerbal
{

	namespace fmt
	{

		namespace detail
		{

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

		} // namespace detail

	} // namespace fmt

} // namespace kerbal

#endif // KERBAL_FMT_FORMATTER_DETAIL_SIGN_PARSE_HELPER_HPP
