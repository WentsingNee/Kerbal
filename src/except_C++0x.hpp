/*
 * except_C++0x.hpp
 *
 *  Created on: 2017Äê8ÔÂ9ÈÕ
 *      Author: Peter
 */

#ifndef EXCEPT_C__0X_HPP_
#define EXCEPT_C__0X_HPP_

#include <stdexcept>

#if __cplusplus >= 201103L //C++0x
#	ifdef __GNUC__
#		pragma GCC diagnostic ignored "-Wdeprecated"
#	endif
#endif //C++0x

#define instanceof(p_to_vir,classname) (dynamic_cast<classname*>(p_to_vir)==NULL?false:true)

#define TRACE(txt,func) (std::string(txt)+"\n\tat "+std::string(func)+" ("+std::string(__FILE__)+": "+to_string(__LINE__)+")")
#define RE_THROW(e,func)\
{\
	auto tmp = (e);\
	decltype(tmp) new_e(TRACE((e).what(), "void main"));\
	throw new_e;\
}

#endif /* EXCEPT_C__0X_HPP_ */
