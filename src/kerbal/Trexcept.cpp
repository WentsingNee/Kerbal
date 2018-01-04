/*
 * Trexcept.cpp
 *
 *  Created on: 2017Äê10ÔÂ25ÈÕ
 *      Author: Peter
 */

#include "Trexcept.hpp"

namespace kerbal
{
	namespace traceable
	{

		Tr_except::Tr_except(const std::string &_M_msg, const std::string &function_name, const std::string &file_name, int line) :
				_M_msg(_M_msg), trace_record()
		{
			trace_record.push_back(Trace(function_name, file_name, line));
		}

		Tr_except::~Tr_except() throw ()
		{

		}

		const char * Tr_except::what() const throw ()
		{
			return _M_msg.c_str();
		}

		void Tr_except::print_trace(std::ostream &out) const
		{
			out << "Exception " << _M_msg << std::endl;
			for (std::list<Trace>::iterator it = trace_record.begin(); it != trace_record.end(); ++it) {
				out << ("\tat " + it->func_name + " (" + it->file_name + ": ") << it->line << ")" << std::endl;
			}
		}

		void Tr_except::re_throw(const std::string &catch_function_name, const std::string &file_name, int line) const
		{
			trace_record.push_back(Trace(catch_function_name, file_name, line));
			throw *this;
		}

	} /* namespace traceable */

}/* namespace kerbal */
