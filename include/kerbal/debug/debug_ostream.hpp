/**
 * @file       debug_ostream.hpp
 * @brief
 * @date       2024-04-15
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_DEBUG_DEBUG_OSTREAM_HPP
#define KERBAL_DEBUG_DEBUG_OSTREAM_HPP

#include <kerbal/utility/noncopyable.hpp>

#include <ostream>
#include <iostream>


namespace kerbal
{

	namespace debug
	{

		struct debug_ostream
		{
				std::size_t k_indent;
				std::ostream & k_ostream;

				debug_ostream(std::ostream & out) :
					k_indent(0),
					k_ostream(out)
				{
				}

				void increase_indent()
				{
					++this->k_indent;
				};

				void decrease_indent()
				{
					--this->k_indent;
				};

				template <typename T>
				friend
				std::ostream & operator<<(debug_ostream & out, const T & src)
				{
					for (std::size_t i = 0; i < out.k_indent; ++i) {
						out.k_ostream << "    ";
					}
					return out.k_ostream << src;
				}
		};

		inline debug_ostream dout(std::cout);

		struct debug_ostream_context : kerbal::utility::noncopyable
		{
			private:
				debug_ostream & k_debug_os;

			public:
				debug_ostream_context(debug_ostream & debug_os) :
					k_debug_os(debug_os)
				{
					this->k_debug_os.increase_indent();
				}

				~debug_ostream_context()
				{
					this->k_debug_os.decrease_indent();
				}
		};

	} // namespace debug

} // namespace kerbal

#endif // KERBAL_DEBUG_DEBUG_OSTREAM_HPP
