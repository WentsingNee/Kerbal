/**
 * @file       fill_and_align_parse_helper.hpp
 * @brief
 * @date       2024-08-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_FMT_FORMATTER_DETAIL_FILL_AND_ALIGN_PARSE_HELPER_HPP
#define KERBAL_FMT_FORMATTER_DETAIL_FILL_AND_ALIGN_PARSE_HELPER_HPP

namespace kerbal
{

	namespace fmt
	{

		namespace detail
		{

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

		} // namespace detail

	} // namespace fmt

} // namespace kerbal

#endif // KERBAL_FMT_FORMATTER_DETAIL_FILL_AND_ALIGN_PARSE_HELPER_HPP
