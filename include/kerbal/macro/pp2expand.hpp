/**
 * @file       pp2expand.hpp
 * @brief
 * @date       pp2expand.hpp
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MACRO_PP2EXPAND_HPP
#define KERBAL_MACRO_PP2EXPAND_HPP

#include <kerbal/macro/macro_concat.hpp>

#define KERBAL_PP2EXPAND_EMPTY_SEPARATOR

#define KERBAL_PP2EXPAND_0(ExpandFun, Separator) ExpandFun(0)
#define KERBAL_PP2EXPAND_1(ExpandFun, Separator) ExpandFun(1)
#define KERBAL_PP2EXPAND_2(ExpandFun, Separator) KERBAL_PP2EXPAND_1(ExpandFun, Separator) Separator ExpandFun(2)
#define KERBAL_PP2EXPAND_3(ExpandFun, Separator) KERBAL_PP2EXPAND_2(ExpandFun, Separator) Separator ExpandFun(3)
#define KERBAL_PP2EXPAND_4(ExpandFun, Separator) KERBAL_PP2EXPAND_3(ExpandFun, Separator) Separator ExpandFun(4)
#define KERBAL_PP2EXPAND_5(ExpandFun, Separator) KERBAL_PP2EXPAND_4(ExpandFun, Separator) Separator ExpandFun(5)
#define KERBAL_PP2EXPAND_6(ExpandFun, Separator) KERBAL_PP2EXPAND_5(ExpandFun, Separator) Separator ExpandFun(6)
#define KERBAL_PP2EXPAND_7(ExpandFun, Separator) KERBAL_PP2EXPAND_6(ExpandFun, Separator) Separator ExpandFun(7)
#define KERBAL_PP2EXPAND_8(ExpandFun, Separator) KERBAL_PP2EXPAND_7(ExpandFun, Separator) Separator ExpandFun(8)
#define KERBAL_PP2EXPAND_9(ExpandFun, Separator) KERBAL_PP2EXPAND_8(ExpandFun, Separator) Separator ExpandFun(9)
#define KERBAL_PP2EXPAND_10(ExpandFun, Separator) KERBAL_PP2EXPAND_9(ExpandFun, Separator) Separator ExpandFun(10)
#define KERBAL_PP2EXPAND_11(ExpandFun, Separator) KERBAL_PP2EXPAND_10(ExpandFun, Separator) Separator ExpandFun(11)
#define KERBAL_PP2EXPAND_12(ExpandFun, Separator) KERBAL_PP2EXPAND_11(ExpandFun, Separator) Separator ExpandFun(12)
#define KERBAL_PP2EXPAND_13(ExpandFun, Separator) KERBAL_PP2EXPAND_12(ExpandFun, Separator) Separator ExpandFun(13)
#define KERBAL_PP2EXPAND_14(ExpandFun, Separator) KERBAL_PP2EXPAND_13(ExpandFun, Separator) Separator ExpandFun(14)
#define KERBAL_PP2EXPAND_15(ExpandFun, Separator) KERBAL_PP2EXPAND_14(ExpandFun, Separator) Separator ExpandFun(15)
#define KERBAL_PP2EXPAND_16(ExpandFun, Separator) KERBAL_PP2EXPAND_15(ExpandFun, Separator) Separator ExpandFun(16)
#define KERBAL_PP2EXPAND_17(ExpandFun, Separator) KERBAL_PP2EXPAND_16(ExpandFun, Separator) Separator ExpandFun(17)
#define KERBAL_PP2EXPAND_18(ExpandFun, Separator) KERBAL_PP2EXPAND_17(ExpandFun, Separator) Separator ExpandFun(18)
#define KERBAL_PP2EXPAND_19(ExpandFun, Separator) KERBAL_PP2EXPAND_18(ExpandFun, Separator) Separator ExpandFun(19)
#define KERBAL_PP2EXPAND_20(ExpandFun, Separator) KERBAL_PP2EXPAND_19(ExpandFun, Separator) Separator ExpandFun(20)

#define KERBAL_PP2EXPAND_N(ExpandFun, Separator, N) KERBAL_MACRO_CONCAT(KERBAL_PP2EXPAND_, N)(ExpandFun, Separator)


#define KERBAL_PP2EXPAND_WITH_COMMA_0(ExpandFun) ExpandFun(0)
#define KERBAL_PP2EXPAND_WITH_COMMA_1(ExpandFun) ExpandFun(1)
#define KERBAL_PP2EXPAND_WITH_COMMA_2(ExpandFun) KERBAL_PP2EXPAND_WITH_COMMA_1(ExpandFun), ExpandFun(2)
#define KERBAL_PP2EXPAND_WITH_COMMA_3(ExpandFun) KERBAL_PP2EXPAND_WITH_COMMA_2(ExpandFun), ExpandFun(3)
#define KERBAL_PP2EXPAND_WITH_COMMA_4(ExpandFun) KERBAL_PP2EXPAND_WITH_COMMA_3(ExpandFun), ExpandFun(4)
#define KERBAL_PP2EXPAND_WITH_COMMA_5(ExpandFun) KERBAL_PP2EXPAND_WITH_COMMA_4(ExpandFun), ExpandFun(5)
#define KERBAL_PP2EXPAND_WITH_COMMA_6(ExpandFun) KERBAL_PP2EXPAND_WITH_COMMA_5(ExpandFun), ExpandFun(6)
#define KERBAL_PP2EXPAND_WITH_COMMA_7(ExpandFun) KERBAL_PP2EXPAND_WITH_COMMA_6(ExpandFun), ExpandFun(7)
#define KERBAL_PP2EXPAND_WITH_COMMA_8(ExpandFun) KERBAL_PP2EXPAND_WITH_COMMA_7(ExpandFun), ExpandFun(8)
#define KERBAL_PP2EXPAND_WITH_COMMA_9(ExpandFun) KERBAL_PP2EXPAND_WITH_COMMA_8(ExpandFun), ExpandFun(9)
#define KERBAL_PP2EXPAND_WITH_COMMA_10(ExpandFun) KERBAL_PP2EXPAND_WITH_COMMA_9(ExpandFun), ExpandFun(10)
#define KERBAL_PP2EXPAND_WITH_COMMA_11(ExpandFun) KERBAL_PP2EXPAND_WITH_COMMA_10(ExpandFun), ExpandFun(11)
#define KERBAL_PP2EXPAND_WITH_COMMA_12(ExpandFun) KERBAL_PP2EXPAND_WITH_COMMA_11(ExpandFun), ExpandFun(12)
#define KERBAL_PP2EXPAND_WITH_COMMA_13(ExpandFun) KERBAL_PP2EXPAND_WITH_COMMA_12(ExpandFun), ExpandFun(13)
#define KERBAL_PP2EXPAND_WITH_COMMA_14(ExpandFun) KERBAL_PP2EXPAND_WITH_COMMA_13(ExpandFun), ExpandFun(14)
#define KERBAL_PP2EXPAND_WITH_COMMA_15(ExpandFun) KERBAL_PP2EXPAND_WITH_COMMA_14(ExpandFun), ExpandFun(15)
#define KERBAL_PP2EXPAND_WITH_COMMA_16(ExpandFun) KERBAL_PP2EXPAND_WITH_COMMA_15(ExpandFun), ExpandFun(16)
#define KERBAL_PP2EXPAND_WITH_COMMA_17(ExpandFun) KERBAL_PP2EXPAND_WITH_COMMA_16(ExpandFun), ExpandFun(17)
#define KERBAL_PP2EXPAND_WITH_COMMA_18(ExpandFun) KERBAL_PP2EXPAND_WITH_COMMA_17(ExpandFun), ExpandFun(18)
#define KERBAL_PP2EXPAND_WITH_COMMA_19(ExpandFun) KERBAL_PP2EXPAND_WITH_COMMA_18(ExpandFun), ExpandFun(19)
#define KERBAL_PP2EXPAND_WITH_COMMA_20(ExpandFun) KERBAL_PP2EXPAND_WITH_COMMA_19(ExpandFun), ExpandFun(20)

#define KERBAL_PP2EXPAND_WITH_COMMA_N(ExpandFun, N) KERBAL_MACRO_CONCAT(KERBAL_PP2EXPAND_WITH_COMMA_, N)(ExpandFun)


#define KERBAL_OPT_PP2EXPAND_0(Opt, ExpandEmpty, ExpandFun, Separator) ExpandEmpty
#define KERBAL_OPT_PP2EXPAND_1(Opt, ExpandEmpty, ExpandFun, Separator) Opt(KERBAL_PP2EXPAND_1(ExpandFun, Separator))
#define KERBAL_OPT_PP2EXPAND_2(Opt, ExpandEmpty, ExpandFun, Separator) Opt(KERBAL_PP2EXPAND_2(ExpandFun, Separator))
#define KERBAL_OPT_PP2EXPAND_3(Opt, ExpandEmpty, ExpandFun, Separator) Opt(KERBAL_PP2EXPAND_3(ExpandFun, Separator))
#define KERBAL_OPT_PP2EXPAND_4(Opt, ExpandEmpty, ExpandFun, Separator) Opt(KERBAL_PP2EXPAND_4(ExpandFun, Separator))
#define KERBAL_OPT_PP2EXPAND_5(Opt, ExpandEmpty, ExpandFun, Separator) Opt(KERBAL_PP2EXPAND_5(ExpandFun, Separator))
#define KERBAL_OPT_PP2EXPAND_6(Opt, ExpandEmpty, ExpandFun, Separator) Opt(KERBAL_PP2EXPAND_6(ExpandFun, Separator))
#define KERBAL_OPT_PP2EXPAND_7(Opt, ExpandEmpty, ExpandFun, Separator) Opt(KERBAL_PP2EXPAND_7(ExpandFun, Separator))
#define KERBAL_OPT_PP2EXPAND_8(Opt, ExpandEmpty, ExpandFun, Separator) Opt(KERBAL_PP2EXPAND_8(ExpandFun, Separator))
#define KERBAL_OPT_PP2EXPAND_9(Opt, ExpandEmpty, ExpandFun, Separator) Opt(KERBAL_PP2EXPAND_9(ExpandFun, Separator))
#define KERBAL_OPT_PP2EXPAND_10(Opt, ExpandEmpty, ExpandFun, Separator) Opt(KERBAL_PP2EXPAND_10(ExpandFun, Separator))
#define KERBAL_OPT_PP2EXPAND_11(Opt, ExpandEmpty, ExpandFun, Separator) Opt(KERBAL_PP2EXPAND_11(ExpandFun, Separator))
#define KERBAL_OPT_PP2EXPAND_12(Opt, ExpandEmpty, ExpandFun, Separator) Opt(KERBAL_PP2EXPAND_12(ExpandFun, Separator))
#define KERBAL_OPT_PP2EXPAND_13(Opt, ExpandEmpty, ExpandFun, Separator) Opt(KERBAL_PP2EXPAND_13(ExpandFun, Separator))
#define KERBAL_OPT_PP2EXPAND_14(Opt, ExpandEmpty, ExpandFun, Separator) Opt(KERBAL_PP2EXPAND_14(ExpandFun, Separator))
#define KERBAL_OPT_PP2EXPAND_15(Opt, ExpandEmpty, ExpandFun, Separator) Opt(KERBAL_PP2EXPAND_15(ExpandFun, Separator))
#define KERBAL_OPT_PP2EXPAND_16(Opt, ExpandEmpty, ExpandFun, Separator) Opt(KERBAL_PP2EXPAND_16(ExpandFun, Separator))
#define KERBAL_OPT_PP2EXPAND_17(Opt, ExpandEmpty, ExpandFun, Separator) Opt(KERBAL_PP2EXPAND_17(ExpandFun, Separator))
#define KERBAL_OPT_PP2EXPAND_18(Opt, ExpandEmpty, ExpandFun, Separator) Opt(KERBAL_PP2EXPAND_18(ExpandFun, Separator))
#define KERBAL_OPT_PP2EXPAND_19(Opt, ExpandEmpty, ExpandFun, Separator) Opt(KERBAL_PP2EXPAND_19(ExpandFun, Separator))
#define KERBAL_OPT_PP2EXPAND_20(Opt, ExpandEmpty, ExpandFun, Separator) Opt(KERBAL_PP2EXPAND_20(ExpandFun, Separator))

#define KERBAL_OPT_PP2EXPAND_N(Opt, ExpandEmpty, ExpandFun, Separator, N) KERBAL_MACRO_CONCAT(KERBAL_OPT_PP2EXPAND_, N)(Opt, ExpandEmpty, ExpandFun, Separator)


#define KERBAL_OPT_PP2EXPAND_WITH_COMMA_0(Opt, ExpandEmpty, ExpandFun) ExpandEmpty
#define KERBAL_OPT_PP2EXPAND_WITH_COMMA_1(Opt, ExpandEmpty, ExpandFun) Opt(KERBAL_PP2EXPAND_WITH_COMMA_1(ExpandFun))
#define KERBAL_OPT_PP2EXPAND_WITH_COMMA_2(Opt, ExpandEmpty, ExpandFun) Opt(KERBAL_PP2EXPAND_WITH_COMMA_2(ExpandFun))
#define KERBAL_OPT_PP2EXPAND_WITH_COMMA_3(Opt, ExpandEmpty, ExpandFun) Opt(KERBAL_PP2EXPAND_WITH_COMMA_3(ExpandFun))
#define KERBAL_OPT_PP2EXPAND_WITH_COMMA_4(Opt, ExpandEmpty, ExpandFun) Opt(KERBAL_PP2EXPAND_WITH_COMMA_4(ExpandFun))
#define KERBAL_OPT_PP2EXPAND_WITH_COMMA_5(Opt, ExpandEmpty, ExpandFun) Opt(KERBAL_PP2EXPAND_WITH_COMMA_5(ExpandFun))
#define KERBAL_OPT_PP2EXPAND_WITH_COMMA_6(Opt, ExpandEmpty, ExpandFun) Opt(KERBAL_PP2EXPAND_WITH_COMMA_6(ExpandFun))
#define KERBAL_OPT_PP2EXPAND_WITH_COMMA_7(Opt, ExpandEmpty, ExpandFun) Opt(KERBAL_PP2EXPAND_WITH_COMMA_7(ExpandFun))
#define KERBAL_OPT_PP2EXPAND_WITH_COMMA_8(Opt, ExpandEmpty, ExpandFun) Opt(KERBAL_PP2EXPAND_WITH_COMMA_8(ExpandFun))
#define KERBAL_OPT_PP2EXPAND_WITH_COMMA_9(Opt, ExpandEmpty, ExpandFun) Opt(KERBAL_PP2EXPAND_WITH_COMMA_9(ExpandFun))
#define KERBAL_OPT_PP2EXPAND_WITH_COMMA_10(Opt, ExpandEmpty, ExpandFun) Opt(KERBAL_PP2EXPAND_WITH_COMMA_10(ExpandFun))
#define KERBAL_OPT_PP2EXPAND_WITH_COMMA_11(Opt, ExpandEmpty, ExpandFun) Opt(KERBAL_PP2EXPAND_WITH_COMMA_11(ExpandFun))
#define KERBAL_OPT_PP2EXPAND_WITH_COMMA_12(Opt, ExpandEmpty, ExpandFun) Opt(KERBAL_PP2EXPAND_WITH_COMMA_12(ExpandFun))
#define KERBAL_OPT_PP2EXPAND_WITH_COMMA_13(Opt, ExpandEmpty, ExpandFun) Opt(KERBAL_PP2EXPAND_WITH_COMMA_13(ExpandFun))
#define KERBAL_OPT_PP2EXPAND_WITH_COMMA_14(Opt, ExpandEmpty, ExpandFun) Opt(KERBAL_PP2EXPAND_WITH_COMMA_14(ExpandFun))
#define KERBAL_OPT_PP2EXPAND_WITH_COMMA_15(Opt, ExpandEmpty, ExpandFun) Opt(KERBAL_PP2EXPAND_WITH_COMMA_15(ExpandFun))
#define KERBAL_OPT_PP2EXPAND_WITH_COMMA_16(Opt, ExpandEmpty, ExpandFun) Opt(KERBAL_PP2EXPAND_WITH_COMMA_16(ExpandFun))
#define KERBAL_OPT_PP2EXPAND_WITH_COMMA_17(Opt, ExpandEmpty, ExpandFun) Opt(KERBAL_PP2EXPAND_WITH_COMMA_17(ExpandFun))
#define KERBAL_OPT_PP2EXPAND_WITH_COMMA_18(Opt, ExpandEmpty, ExpandFun) Opt(KERBAL_PP2EXPAND_WITH_COMMA_18(ExpandFun))
#define KERBAL_OPT_PP2EXPAND_WITH_COMMA_19(Opt, ExpandEmpty, ExpandFun) Opt(KERBAL_PP2EXPAND_WITH_COMMA_19(ExpandFun))
#define KERBAL_OPT_PP2EXPAND_WITH_COMMA_20(Opt, ExpandEmpty, ExpandFun) Opt(KERBAL_PP2EXPAND_WITH_COMMA_20(ExpandFun))

#define KERBAL_OPT_PP2EXPAND_WITH_COMMA_N(Opt, ExpandEmpty, ExpandFun, N) KERBAL_MACRO_CONCAT(KERBAL_OPT_PP2EXPAND_WITH_COMMA_, N)(Opt, ExpandEmpty, ExpandFun)

#endif // KERBAL_MACRO_PP2EXPAND_HPP
