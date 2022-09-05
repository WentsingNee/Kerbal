/*
 * modules_ts.hpp
 *
 *  Created on: 2018年12月10日
 *      Author: peter
 */

#ifndef KERBAL_TS_MODULES_TS_MODULES_TS_HPP
#define KERBAL_TS_MODULES_TS_MODULES_TS_HPP

#ifdef __cpp_modules
#	define KERBAL_ENABLE_CLANGPP_MODULES
#	define MODULE_EXPORT export
#else
#	define MODULE_EXPORT
#endif



#endif // KERBAL_TS_MODULES_TS_MODULES_TS_HPP
