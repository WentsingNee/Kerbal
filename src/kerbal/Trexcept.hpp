/*
 * Trexcept.hpp
 *
 *  Created on: 2017Äê10ÔÂ25ÈÕ
 *      Author: Peter
 */

#ifndef TR_EXCEPT_TREXCEPT_HPP_
#define TR_EXCEPT_TREXCEPT_HPP_

#include <stdexcept>
#include <iostream>
#include <list>

#if __cplusplus >= 201103L //C++0x
#	define TRACE(_M_msg,FUNCTION_NAME) (std::string(_M_msg)+"\n\tat "+std::string(FUNCTION_NAME)+" ("+std::string(__FILE__)+": "+std::to_string(__LINE__)+")")
#else
#	define TRACE(_M_msg,FUNCTION_NAME) (std::string(_M_msg)+"\n\tat "+std::string(FUNCTION_NAME)+" ("+std::string(__FILE__)+": "+kerbal::string_serve::to_string(__LINE__)+")")
#endif //C++0x

#if __cplusplus >= 201103L //C++0x
#	define RE_THROW(e,FUNCTION_NAME)\
	{\
		auto tmp = (e);\
		throw decltype(tmp)(TRACE((e).what(), FUNCTION_NAME));\
	}
#else
#	define RE_THROW(e,FUNCTION_NAME)\
	{\
		throw e;\
	}
#endif //C++0x

namespace kerbal
{
	
	namespace traceable
	{

		class Tr_except: public std::exception
		{
			protected:
				struct Trace
				{
					public:
						std::string func_name;
						std::string file_name;
						int line;

						Trace(std::string func_name = "Unknown Function", std::string file_name = "Unknown File", int line =
								0) :
								func_name(func_name), file_name(file_name), line(line)
						{
						}
				};
				std::string _M_msg;
				mutable std::list<Trace> trace_record;

			public:
				Tr_except(const std::string &_M_msg = "", const std::string &function_name = "Unknown Function", const std::string &file_name =
						"Unknown File", int line = 0);

				virtual ~Tr_except() throw ();
				virtual const char * what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT;
				virtual void print_trace(std::ostream &out = std::cerr) const;
				virtual void re_throw(const std::string &catch_function_name = "Unknown Function", const std::string &file_name =
						"Unknown File", int line = 0) const;

		};

	} /* namespace traceable */

}/* namespace kerbal */

#endif /* TR_EXCEPT_TREXCEPT_HPP_ */
