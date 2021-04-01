/**
 * @file       format.hpp
 * @brief
 * @date       2020-10-07
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_FMT_FORMAT_HPP
#define KERBAL_FMT_FORMAT_HPP

#include <kerbal/algorithm/modifier.hpp>
#include <kerbal/container/vector.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/fmt/formatter.hpp>
#include <kerbal/fmt/format_error.hpp>
#include <kerbal/type_traits/remove_reference.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

#include <iterator>

#include <cstddef>


namespace kerbal
{

	namespace fmt
	{

		struct formatter_and_value_pack
		{
				void (*v)(void * out_vp, void * first_vp, void * last_vp, void * arg_vp);
				void * value;
		};

		template <typename OutputIterator, typename ForwardIterator>
		class format_parse_context
		{
			protected:

				OutputIterator M_out;
				ForwardIterator M_current, M_last;
				bool use_var_id;

			public:

				format_parse_context(
					OutputIterator out, ForwardIterator fmt_first, ForwardIterator fmt_last
				) :
					M_out(out), M_current(fmt_first), M_last(fmt_last), use_var_id(false)
				{
				}

				std::size_t parse_arg_id()
				{
					if (*M_current == '0') {
						++M_current;
						return 0;
					}
					std::size_t r = 0;
					r = *M_current - '0';
					++M_current;
					while (M_current != M_last && *M_current >= '0' && *M_current <= '9') {
						r *= 10;
						r += *M_current - '0';
						++M_current;
					}
					return r;
				}

				void parse_brace(
					std::size_t arg_id,
					const kerbal::container::vector<formatter_and_value_pack> & pack
				)
				{
					if (*M_current >= '0' && *M_current <= '9') {
						// {0
						//  ^
						//  M_current
						if (arg_id == 0) {
							use_var_id = true;
						} else if (!use_var_id) {
							kerbal::fmt::format_error::throw_this_exception(
								+"the arg-ids in a format string must all be present or all be omitted"
							);
						}
						arg_id = parse_arg_id();
					}
					if (arg_id >= pack.size()) {
						kerbal::fmt::format_error::throw_this_exception(
							+"too few arguments"
						);
					}
					// {123.
					//     ^
					//     M_current
					if (M_current == M_last) {
						kerbal::fmt::format_error::throw_this_exception(
							+"no matched '}'"
						);
					}
					if (*M_current == ':') {
						++M_current;
						// {123:.
						//      ^
						//      M_current
						ForwardIterator fmt_start(M_current);
						while (M_current != M_last) {
							if (*M_current == '}') {
								pack[arg_id].v(&M_out, &fmt_start, &M_current, pack[arg_id].value);
								++M_current;
								return;
							}
							++M_current;
						}
						kerbal::fmt::format_error::throw_this_exception(
							+"no matched '}'"
						);
					} else if (*M_current == '}') {
						pack[arg_id].v(&M_out, &M_current, &M_current, pack[arg_id].value);
						++M_current;
						// {123}.
						//      ^cerr
						//      M_current
						return;
					} else {
						kerbal::fmt::format_error::throw_this_exception(
							+"invalid format string"
						);
					}
				}

				void parse(const kerbal::container::vector<formatter_and_value_pack> & pack)
				{
					std::size_t arg_id = 0;
					while (M_current != M_last) {
						if (*M_current == '{') {
							++M_current;
							// {.
							//  ^
							//  M_current
							if (M_current == M_last) {
								kerbal::fmt::format_error::throw_this_exception(
									+"no matched '}'"
								);
							}
							if (*M_current == '{') {
								// {{
								//  ^
								//  M_current
								*M_out = '{'; ++M_out; ++M_current;
								continue;
							}
							parse_brace(arg_id, pack);
							++arg_id;
						} else if (*M_current == '}') {
							++M_current;
							if (M_current == M_last || *M_current != '}') {
								kerbal::fmt::format_error::throw_this_exception(
									+"unmatched '}' in format string"
								);
							}
							// }}
							*M_out = '}'; ++M_out; ++M_current;
						} else {
							*M_out = *M_current; ++M_out; ++M_current;
						}
					}
				}

				OutputIterator out() const
				{
					return M_out;
				}
		};

		template <typename OutputIterator, typename ForwardIterator>
		OutputIterator
		_format_to(
			OutputIterator out, ForwardIterator fmt_first, ForwardIterator fmt_last,
			const kerbal::container::vector<formatter_and_value_pack> & pack
		)
		{
			kerbal::fmt::format_parse_context<OutputIterator, ForwardIterator> ctx(out, fmt_first, fmt_last);
			ctx.parse(pack);
			return ctx.out();
		}

		template <typename OutputIterator, typename ForwardIterator, typename Arg>
		void v(void * out_vp, void * fmt_first_vp, void * fmt_last_vp, void * arg_vp)
		{
			typedef typename kerbal::iterator::iterator_traits<ForwardIterator>::value_type CharT;
			OutputIterator & out = *static_cast<OutputIterator *>(out_vp);
			const ForwardIterator & fmt_first = *static_cast<ForwardIterator *>(fmt_first_vp);
			const ForwardIterator & fmt_last = *static_cast<ForwardIterator *>(fmt_last_vp);
			const Arg & arg = *static_cast<const Arg *>(arg_vp);

			kerbal::fmt::formatter<Arg, CharT> formatter;
			out = formatter.format(out, fmt_first, fmt_last, arg);
		}

		template <typename OutputIterator, typename ForwardIterator, typename ... Args>
		OutputIterator
		format_range_to(
			OutputIterator out,
			ForwardIterator fmt_first, ForwardIterator fmt_last,
			Args && ... args
		)
		{
			kerbal::container::vector<formatter_and_value_pack> pack = {
				formatter_and_value_pack{
					v<
						OutputIterator, ForwardIterator, typename kerbal::type_traits::remove_cvref<Args>::type
					>, (void *)(&args)
				}...
			};
			return kerbal::fmt::_format_to(out, fmt_first, fmt_last, pack);
		}

		template <typename ForwardIterator, typename ... Args>
		std::basic_string<
			typename kerbal::iterator::iterator_traits<ForwardIterator>::value_type
		>
		format_range(ForwardIterator fmt_first, ForwardIterator fmt_last, Args && ... args)
		{
			typedef typename kerbal::iterator::iterator_traits<ForwardIterator>::value_type CharT;
			std::basic_string<CharT> r;
			kerbal::fmt::format_range_to(
				std::back_inserter(r),
				fmt_first, fmt_last,
				kerbal::utility::forward<Args>(args)...
			);
			return r;
		}

		template <typename CharT, typename ... Args>
		std::basic_string<CharT> format(const CharT * fmt, Args && ... args)
		{
			return kerbal::fmt::format_range(
				fmt, fmt + std::char_traits<CharT>::length(fmt),
				kerbal::utility::forward<Args>(args)...
			);
		}

		template <typename CharT, typename ... Args>
		std::basic_string<CharT> format(const std::basic_string<CharT> & fmt, Args && ... args)
		{
			return kerbal::fmt::format_range(
				fmt.c_str(), fmt.c_str() + fmt.size(),
				kerbal::utility::forward<Args>(args)...
			);
		}

		template <typename Ostream, typename CharT, typename ... Args>
		Ostream& printf(Ostream & out, const CharT * fmt, Args && ... args)
		{
			kerbal::fmt::format_range_to(
				std::ostream_iterator<CharT, CharT>(out),
				fmt, fmt + std::char_traits<CharT>::length(fmt),
				kerbal::utility::forward<Args>(args)...
			);
			return out;
		}

		template <typename Ostream, typename CharT, typename ... Args>
		Ostream& printf(Ostream & out, const std::basic_string<CharT> & fmt, Args && ... args)
		{
			kerbal::fmt::format_range_to(
				std::ostream_iterator<CharT, CharT>(out),
				fmt.c_str(), fmt.c_str() + fmt.size(),
				kerbal::utility::forward<Args>(args)...
			);
			return out;
		}

	} // namespace fmt

} // namespace kerbal

#endif // KERBAL_FMT_FORMAT_HPP
