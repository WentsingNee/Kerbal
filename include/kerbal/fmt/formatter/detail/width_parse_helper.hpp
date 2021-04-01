/**
 * @file       width_parse_helper.hpp
 * @brief
 * @date       2024-08-03
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_FMT_FORMATTER_DETAIL_WIDTH_PARSE_HELPER_HPP
#define KERBAL_FMT_FORMATTER_DETAIL_WIDTH_PARSE_HELPER_HPP

#include <cstddef>


namespace kerbal
{

	namespace fmt
	{

		namespace detail
		{

			template <typename CharT>
			struct width_parse_helper
			{
				protected:
					std::size_t width;

					width_parse_helper(std::size_t default_width):
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

		} // namespace detail

	} // namespace fmt

} // namespace kerbal

#endif // KERBAL_FMT_FORMATTER_DETAIL_WIDTH_PARSE_HELPER_HPP
