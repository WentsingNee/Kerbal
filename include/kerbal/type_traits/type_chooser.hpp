/**
 * @file       type_chooser.hpp
 * @brief
 * @date       2019-5-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_TYPE_CHOOSER_HPP
#define KERBAL_TYPE_TRAITS_TYPE_CHOOSER_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#if __cplusplus < 201103L
#	include <kerbal/compatibility/static_assert.hpp>
#	include <kerbal/type_traits/is_same.hpp>
#endif

#include <cstddef>

namespace kerbal
{

	namespace type_traits
	{

#	if __cplusplus < 201103L


		namespace detail
		{

			struct type_chooser_void_helper
			{
			};

			template <bool, size_t Index, typename T0 = kerbal::type_traits::detail::type_chooser_void_helper, typename T1 = kerbal::type_traits::detail::type_chooser_void_helper, typename T2 = kerbal::type_traits::detail::type_chooser_void_helper, typename T3 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T4 = kerbal::type_traits::detail::type_chooser_void_helper, typename T5 = kerbal::type_traits::detail::type_chooser_void_helper, typename T6 = kerbal::type_traits::detail::type_chooser_void_helper, typename T7 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T8 = kerbal::type_traits::detail::type_chooser_void_helper, typename T9 = kerbal::type_traits::detail::type_chooser_void_helper, typename T10 = kerbal::type_traits::detail::type_chooser_void_helper, typename T11 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T12 = kerbal::type_traits::detail::type_chooser_void_helper, typename T13 = kerbal::type_traits::detail::type_chooser_void_helper, typename T14 = kerbal::type_traits::detail::type_chooser_void_helper, typename T15 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T16 = kerbal::type_traits::detail::type_chooser_void_helper, typename T17 = kerbal::type_traits::detail::type_chooser_void_helper, typename T18 = kerbal::type_traits::detail::type_chooser_void_helper, typename T19 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T20 = kerbal::type_traits::detail::type_chooser_void_helper, typename T21 = kerbal::type_traits::detail::type_chooser_void_helper, typename T22 = kerbal::type_traits::detail::type_chooser_void_helper, typename T23 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T24 = kerbal::type_traits::detail::type_chooser_void_helper, typename T25 = kerbal::type_traits::detail::type_chooser_void_helper, typename T26 = kerbal::type_traits::detail::type_chooser_void_helper, typename T27 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T28 = kerbal::type_traits::detail::type_chooser_void_helper, typename T29 = kerbal::type_traits::detail::type_chooser_void_helper, typename T30 = kerbal::type_traits::detail::type_chooser_void_helper, typename T31 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T32 = kerbal::type_traits::detail::type_chooser_void_helper, typename T33 = kerbal::type_traits::detail::type_chooser_void_helper, typename T34 = kerbal::type_traits::detail::type_chooser_void_helper, typename T35 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T36 = kerbal::type_traits::detail::type_chooser_void_helper, typename T37 = kerbal::type_traits::detail::type_chooser_void_helper, typename T38 = kerbal::type_traits::detail::type_chooser_void_helper, typename T39 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T40 = kerbal::type_traits::detail::type_chooser_void_helper, typename T41 = kerbal::type_traits::detail::type_chooser_void_helper, typename T42 = kerbal::type_traits::detail::type_chooser_void_helper, typename T43 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T44 = kerbal::type_traits::detail::type_chooser_void_helper, typename T45 = kerbal::type_traits::detail::type_chooser_void_helper, typename T46 = kerbal::type_traits::detail::type_chooser_void_helper, typename T47 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T48 = kerbal::type_traits::detail::type_chooser_void_helper, typename T49 = kerbal::type_traits::detail::type_chooser_void_helper, typename T50 = kerbal::type_traits::detail::type_chooser_void_helper, typename T51 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T52 = kerbal::type_traits::detail::type_chooser_void_helper, typename T53 = kerbal::type_traits::detail::type_chooser_void_helper, typename T54 = kerbal::type_traits::detail::type_chooser_void_helper, typename T55 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T56 = kerbal::type_traits::detail::type_chooser_void_helper, typename T57 = kerbal::type_traits::detail::type_chooser_void_helper, typename T58 = kerbal::type_traits::detail::type_chooser_void_helper, typename T59 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T60 = kerbal::type_traits::detail::type_chooser_void_helper, typename T61 = kerbal::type_traits::detail::type_chooser_void_helper, typename T62 = kerbal::type_traits::detail::type_chooser_void_helper, typename T63 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T64 = kerbal::type_traits::detail::type_chooser_void_helper, typename T65 = kerbal::type_traits::detail::type_chooser_void_helper, typename T66 = kerbal::type_traits::detail::type_chooser_void_helper, typename T67 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T68 = kerbal::type_traits::detail::type_chooser_void_helper, typename T69 = kerbal::type_traits::detail::type_chooser_void_helper, typename T70 = kerbal::type_traits::detail::type_chooser_void_helper, typename T71 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T72 = kerbal::type_traits::detail::type_chooser_void_helper, typename T73 = kerbal::type_traits::detail::type_chooser_void_helper, typename T74 = kerbal::type_traits::detail::type_chooser_void_helper, typename T75 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T76 = kerbal::type_traits::detail::type_chooser_void_helper, typename T77 = kerbal::type_traits::detail::type_chooser_void_helper, typename T78 = kerbal::type_traits::detail::type_chooser_void_helper, typename T79 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T80 = kerbal::type_traits::detail::type_chooser_void_helper, typename T81 = kerbal::type_traits::detail::type_chooser_void_helper, typename T82 = kerbal::type_traits::detail::type_chooser_void_helper, typename T83 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T84 = kerbal::type_traits::detail::type_chooser_void_helper, typename T85 = kerbal::type_traits::detail::type_chooser_void_helper, typename T86 = kerbal::type_traits::detail::type_chooser_void_helper, typename T87 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T88 = kerbal::type_traits::detail::type_chooser_void_helper, typename T89 = kerbal::type_traits::detail::type_chooser_void_helper, typename T90 = kerbal::type_traits::detail::type_chooser_void_helper, typename T91 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T92 = kerbal::type_traits::detail::type_chooser_void_helper, typename T93 = kerbal::type_traits::detail::type_chooser_void_helper, typename T94 = kerbal::type_traits::detail::type_chooser_void_helper, typename T95 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T96 = kerbal::type_traits::detail::type_chooser_void_helper, typename T97 = kerbal::type_traits::detail::type_chooser_void_helper, typename T98 = kerbal::type_traits::detail::type_chooser_void_helper, typename T99 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T100 = kerbal::type_traits::detail::type_chooser_void_helper, typename T101 = kerbal::type_traits::detail::type_chooser_void_helper, typename T102 = kerbal::type_traits::detail::type_chooser_void_helper, typename T103 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T104 = kerbal::type_traits::detail::type_chooser_void_helper, typename T105 = kerbal::type_traits::detail::type_chooser_void_helper, typename T106 = kerbal::type_traits::detail::type_chooser_void_helper, typename T107 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T108 = kerbal::type_traits::detail::type_chooser_void_helper, typename T109 = kerbal::type_traits::detail::type_chooser_void_helper, typename T110 = kerbal::type_traits::detail::type_chooser_void_helper, typename T111 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T112 = kerbal::type_traits::detail::type_chooser_void_helper, typename T113 = kerbal::type_traits::detail::type_chooser_void_helper, typename T114 = kerbal::type_traits::detail::type_chooser_void_helper, typename T115 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T116 = kerbal::type_traits::detail::type_chooser_void_helper, typename T117 = kerbal::type_traits::detail::type_chooser_void_helper, typename T118 = kerbal::type_traits::detail::type_chooser_void_helper, typename T119 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T120 = kerbal::type_traits::detail::type_chooser_void_helper, typename T121 = kerbal::type_traits::detail::type_chooser_void_helper, typename T122 = kerbal::type_traits::detail::type_chooser_void_helper, typename T123 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T124 = kerbal::type_traits::detail::type_chooser_void_helper, typename T125 = kerbal::type_traits::detail::type_chooser_void_helper, typename T126 = kerbal::type_traits::detail::type_chooser_void_helper, typename T127 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T128 = kerbal::type_traits::detail::type_chooser_void_helper, typename T129 = kerbal::type_traits::detail::type_chooser_void_helper, typename T130 = kerbal::type_traits::detail::type_chooser_void_helper, typename T131 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T132 = kerbal::type_traits::detail::type_chooser_void_helper, typename T133 = kerbal::type_traits::detail::type_chooser_void_helper, typename T134 = kerbal::type_traits::detail::type_chooser_void_helper, typename T135 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T136 = kerbal::type_traits::detail::type_chooser_void_helper, typename T137 = kerbal::type_traits::detail::type_chooser_void_helper, typename T138 = kerbal::type_traits::detail::type_chooser_void_helper, typename T139 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T140 = kerbal::type_traits::detail::type_chooser_void_helper, typename T141 = kerbal::type_traits::detail::type_chooser_void_helper, typename T142 = kerbal::type_traits::detail::type_chooser_void_helper, typename T143 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T144 = kerbal::type_traits::detail::type_chooser_void_helper, typename T145 = kerbal::type_traits::detail::type_chooser_void_helper, typename T146 = kerbal::type_traits::detail::type_chooser_void_helper, typename T147 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T148 = kerbal::type_traits::detail::type_chooser_void_helper, typename T149 = kerbal::type_traits::detail::type_chooser_void_helper, typename T150 = kerbal::type_traits::detail::type_chooser_void_helper, typename T151 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T152 = kerbal::type_traits::detail::type_chooser_void_helper, typename T153 = kerbal::type_traits::detail::type_chooser_void_helper, typename T154 = kerbal::type_traits::detail::type_chooser_void_helper, typename T155 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T156 = kerbal::type_traits::detail::type_chooser_void_helper, typename T157 = kerbal::type_traits::detail::type_chooser_void_helper, typename T158 = kerbal::type_traits::detail::type_chooser_void_helper, typename T159 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T160 = kerbal::type_traits::detail::type_chooser_void_helper, typename T161 = kerbal::type_traits::detail::type_chooser_void_helper, typename T162 = kerbal::type_traits::detail::type_chooser_void_helper, typename T163 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T164 = kerbal::type_traits::detail::type_chooser_void_helper, typename T165 = kerbal::type_traits::detail::type_chooser_void_helper, typename T166 = kerbal::type_traits::detail::type_chooser_void_helper, typename T167 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T168 = kerbal::type_traits::detail::type_chooser_void_helper, typename T169 = kerbal::type_traits::detail::type_chooser_void_helper, typename T170 = kerbal::type_traits::detail::type_chooser_void_helper, typename T171 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T172 = kerbal::type_traits::detail::type_chooser_void_helper, typename T173 = kerbal::type_traits::detail::type_chooser_void_helper, typename T174 = kerbal::type_traits::detail::type_chooser_void_helper, typename T175 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T176 = kerbal::type_traits::detail::type_chooser_void_helper, typename T177 = kerbal::type_traits::detail::type_chooser_void_helper, typename T178 = kerbal::type_traits::detail::type_chooser_void_helper, typename T179 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T180 = kerbal::type_traits::detail::type_chooser_void_helper, typename T181 = kerbal::type_traits::detail::type_chooser_void_helper, typename T182 = kerbal::type_traits::detail::type_chooser_void_helper, typename T183 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T184 = kerbal::type_traits::detail::type_chooser_void_helper, typename T185 = kerbal::type_traits::detail::type_chooser_void_helper, typename T186 = kerbal::type_traits::detail::type_chooser_void_helper, typename T187 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T188 = kerbal::type_traits::detail::type_chooser_void_helper, typename T189 = kerbal::type_traits::detail::type_chooser_void_helper, typename T190 = kerbal::type_traits::detail::type_chooser_void_helper, typename T191 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T192 = kerbal::type_traits::detail::type_chooser_void_helper, typename T193 = kerbal::type_traits::detail::type_chooser_void_helper, typename T194 = kerbal::type_traits::detail::type_chooser_void_helper, typename T195 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T196 = kerbal::type_traits::detail::type_chooser_void_helper, typename T197 = kerbal::type_traits::detail::type_chooser_void_helper, typename T198 = kerbal::type_traits::detail::type_chooser_void_helper, typename T199 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T200 = kerbal::type_traits::detail::type_chooser_void_helper, typename T201 = kerbal::type_traits::detail::type_chooser_void_helper, typename T202 = kerbal::type_traits::detail::type_chooser_void_helper, typename T203 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T204 = kerbal::type_traits::detail::type_chooser_void_helper, typename T205 = kerbal::type_traits::detail::type_chooser_void_helper, typename T206 = kerbal::type_traits::detail::type_chooser_void_helper, typename T207 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T208 = kerbal::type_traits::detail::type_chooser_void_helper, typename T209 = kerbal::type_traits::detail::type_chooser_void_helper, typename T210 = kerbal::type_traits::detail::type_chooser_void_helper, typename T211 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T212 = kerbal::type_traits::detail::type_chooser_void_helper, typename T213 = kerbal::type_traits::detail::type_chooser_void_helper, typename T214 = kerbal::type_traits::detail::type_chooser_void_helper, typename T215 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T216 = kerbal::type_traits::detail::type_chooser_void_helper, typename T217 = kerbal::type_traits::detail::type_chooser_void_helper, typename T218 = kerbal::type_traits::detail::type_chooser_void_helper, typename T219 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T220 = kerbal::type_traits::detail::type_chooser_void_helper, typename T221 = kerbal::type_traits::detail::type_chooser_void_helper, typename T222 = kerbal::type_traits::detail::type_chooser_void_helper, typename T223 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T224 = kerbal::type_traits::detail::type_chooser_void_helper, typename T225 = kerbal::type_traits::detail::type_chooser_void_helper, typename T226 = kerbal::type_traits::detail::type_chooser_void_helper, typename T227 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T228 = kerbal::type_traits::detail::type_chooser_void_helper, typename T229 = kerbal::type_traits::detail::type_chooser_void_helper, typename T230 = kerbal::type_traits::detail::type_chooser_void_helper, typename T231 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T232 = kerbal::type_traits::detail::type_chooser_void_helper, typename T233 = kerbal::type_traits::detail::type_chooser_void_helper, typename T234 = kerbal::type_traits::detail::type_chooser_void_helper, typename T235 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T236 = kerbal::type_traits::detail::type_chooser_void_helper, typename T237 = kerbal::type_traits::detail::type_chooser_void_helper, typename T238 = kerbal::type_traits::detail::type_chooser_void_helper, typename T239 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T240 = kerbal::type_traits::detail::type_chooser_void_helper, typename T241 = kerbal::type_traits::detail::type_chooser_void_helper, typename T242 = kerbal::type_traits::detail::type_chooser_void_helper, typename T243 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T244 = kerbal::type_traits::detail::type_chooser_void_helper, typename T245 = kerbal::type_traits::detail::type_chooser_void_helper, typename T246 = kerbal::type_traits::detail::type_chooser_void_helper, typename T247 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T248 = kerbal::type_traits::detail::type_chooser_void_helper, typename T249 = kerbal::type_traits::detail::type_chooser_void_helper, typename T250 = kerbal::type_traits::detail::type_chooser_void_helper, typename T251 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T252 = kerbal::type_traits::detail::type_chooser_void_helper, typename T253 = kerbal::type_traits::detail::type_chooser_void_helper, typename T254 = kerbal::type_traits::detail::type_chooser_void_helper>
			struct type_chooser_helper;

			template <size_t Index, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, 
				typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, 
				typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, 
				typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, 
				typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, 
				typename T50, typename T51, typename T52, typename T53, typename T54, typename T55, typename T56, typename T57, typename T58, typename T59, 
				typename T60, typename T61, typename T62, typename T63, typename T64, typename T65, typename T66, typename T67, typename T68, typename T69, 
				typename T70, typename T71, typename T72, typename T73, typename T74, typename T75, typename T76, typename T77, typename T78, typename T79, 
				typename T80, typename T81, typename T82, typename T83, typename T84, typename T85, typename T86, typename T87, typename T88, typename T89, 
				typename T90, typename T91, typename T92, typename T93, typename T94, typename T95, typename T96, typename T97, typename T98, typename T99, 
				typename T100, typename T101, typename T102, typename T103, typename T104, typename T105, typename T106, typename T107, typename T108, typename T109, 
				typename T110, typename T111, typename T112, typename T113, typename T114, typename T115, typename T116, typename T117, typename T118, typename T119, 
				typename T120, typename T121, typename T122, typename T123, typename T124, typename T125, typename T126, typename T127, typename T128, typename T129, 
				typename T130, typename T131, typename T132, typename T133, typename T134, typename T135, typename T136, typename T137, typename T138, typename T139, 
				typename T140, typename T141, typename T142, typename T143, typename T144, typename T145, typename T146, typename T147, typename T148, typename T149, 
				typename T150, typename T151, typename T152, typename T153, typename T154, typename T155, typename T156, typename T157, typename T158, typename T159, 
				typename T160, typename T161, typename T162, typename T163, typename T164, typename T165, typename T166, typename T167, typename T168, typename T169, 
				typename T170, typename T171, typename T172, typename T173, typename T174, typename T175, typename T176, typename T177, typename T178, typename T179, 
				typename T180, typename T181, typename T182, typename T183, typename T184, typename T185, typename T186, typename T187, typename T188, typename T189, 
				typename T190, typename T191, typename T192, typename T193, typename T194, typename T195, typename T196, typename T197, typename T198, typename T199, 
				typename T200, typename T201, typename T202, typename T203, typename T204, typename T205, typename T206, typename T207, typename T208, typename T209, 
				typename T210, typename T211, typename T212, typename T213, typename T214, typename T215, typename T216, typename T217, typename T218, typename T219, 
				typename T220, typename T221, typename T222, typename T223, typename T224, typename T225, typename T226, typename T227, typename T228, typename T229, 
				typename T230, typename T231, typename T232, typename T233, typename T234, typename T235, typename T236, typename T237, typename T238, typename T239, 
				typename T240, typename T241, typename T242, typename T243, typename T244, typename T245, typename T246, typename T247, typename T248, typename T249, 
				typename T250, typename T251, typename T252, typename T253, typename T254>
			struct type_chooser_helper<true, Index, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, 
				T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, 
				T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, 
				T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, 
				T40, T41, T42, T43, T44, T45, T46, T47, T48, T49, 
				T50, T51, T52, T53, T54, T55, T56, T57, T58, T59, 
				T60, T61, T62, T63, T64, T65, T66, T67, T68, T69, 
				T70, T71, T72, T73, T74, T75, T76, T77, T78, T79, 
				T80, T81, T82, T83, T84, T85, T86, T87, T88, T89, 
				T90, T91, T92, T93, T94, T95, T96, T97, T98, T99, 
				T100, T101, T102, T103, T104, T105, T106, T107, T108, T109, 
				T110, T111, T112, T113, T114, T115, T116, T117, T118, T119, 
				T120, T121, T122, T123, T124, T125, T126, T127, T128, T129, 
				T130, T131, T132, T133, T134, T135, T136, T137, T138, T139, 
				T140, T141, T142, T143, T144, T145, T146, T147, T148, T149, 
				T150, T151, T152, T153, T154, T155, T156, T157, T158, T159, 
				T160, T161, T162, T163, T164, T165, T166, T167, T168, T169, 
				T170, T171, T172, T173, T174, T175, T176, T177, T178, T179, 
				T180, T181, T182, T183, T184, T185, T186, T187, T188, T189, 
				T190, T191, T192, T193, T194, T195, T196, T197, T198, T199, 
				T200, T201, T202, T203, T204, T205, T206, T207, T208, T209, 
				T210, T211, T212, T213, T214, T215, T216, T217, T218, T219, 
				T220, T221, T222, T223, T224, T225, T226, T227, T228, T229, 
				T230, T231, T232, T233, T234, T235, T236, T237, T238, T239, 
				T240, T241, T242, T243, T244, T245, T246, T247, T248, T249, 
				T250, T251, T252, T253, T254>: type_chooser_helper<true, Index - 1, T1, T2, T3, T4, T5, T6, T7, T8, T9, 
				T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, 
				T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, 
				T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, 
				T40, T41, T42, T43, T44, T45, T46, T47, T48, T49, 
				T50, T51, T52, T53, T54, T55, T56, T57, T58, T59, 
				T60, T61, T62, T63, T64, T65, T66, T67, T68, T69, 
				T70, T71, T72, T73, T74, T75, T76, T77, T78, T79, 
				T80, T81, T82, T83, T84, T85, T86, T87, T88, T89, 
				T90, T91, T92, T93, T94, T95, T96, T97, T98, T99, 
				T100, T101, T102, T103, T104, T105, T106, T107, T108, T109, 
				T110, T111, T112, T113, T114, T115, T116, T117, T118, T119, 
				T120, T121, T122, T123, T124, T125, T126, T127, T128, T129, 
				T130, T131, T132, T133, T134, T135, T136, T137, T138, T139, 
				T140, T141, T142, T143, T144, T145, T146, T147, T148, T149, 
				T150, T151, T152, T153, T154, T155, T156, T157, T158, T159, 
				T160, T161, T162, T163, T164, T165, T166, T167, T168, T169, 
				T170, T171, T172, T173, T174, T175, T176, T177, T178, T179, 
				T180, T181, T182, T183, T184, T185, T186, T187, T188, T189, 
				T190, T191, T192, T193, T194, T195, T196, T197, T198, T199, 
				T200, T201, T202, T203, T204, T205, T206, T207, T208, T209, 
				T210, T211, T212, T213, T214, T215, T216, T217, T218, T219, 
				T220, T221, T222, T223, T224, T225, T226, T227, T228, T229, 
				T230, T231, T232, T233, T234, T235, T236, T237, T238, T239, 
				T240, T241, T242, T243, T244, T245, T246, T247, T248, T249, 
				T250, T251, T252, T253, T254>
			{
			};

			template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, 
				typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, 
				typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, 
				typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39, 
				typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49, 
				typename T50, typename T51, typename T52, typename T53, typename T54, typename T55, typename T56, typename T57, typename T58, typename T59, 
				typename T60, typename T61, typename T62, typename T63, typename T64, typename T65, typename T66, typename T67, typename T68, typename T69, 
				typename T70, typename T71, typename T72, typename T73, typename T74, typename T75, typename T76, typename T77, typename T78, typename T79, 
				typename T80, typename T81, typename T82, typename T83, typename T84, typename T85, typename T86, typename T87, typename T88, typename T89, 
				typename T90, typename T91, typename T92, typename T93, typename T94, typename T95, typename T96, typename T97, typename T98, typename T99, 
				typename T100, typename T101, typename T102, typename T103, typename T104, typename T105, typename T106, typename T107, typename T108, typename T109, 
				typename T110, typename T111, typename T112, typename T113, typename T114, typename T115, typename T116, typename T117, typename T118, typename T119, 
				typename T120, typename T121, typename T122, typename T123, typename T124, typename T125, typename T126, typename T127, typename T128, typename T129, 
				typename T130, typename T131, typename T132, typename T133, typename T134, typename T135, typename T136, typename T137, typename T138, typename T139, 
				typename T140, typename T141, typename T142, typename T143, typename T144, typename T145, typename T146, typename T147, typename T148, typename T149, 
				typename T150, typename T151, typename T152, typename T153, typename T154, typename T155, typename T156, typename T157, typename T158, typename T159, 
				typename T160, typename T161, typename T162, typename T163, typename T164, typename T165, typename T166, typename T167, typename T168, typename T169, 
				typename T170, typename T171, typename T172, typename T173, typename T174, typename T175, typename T176, typename T177, typename T178, typename T179, 
				typename T180, typename T181, typename T182, typename T183, typename T184, typename T185, typename T186, typename T187, typename T188, typename T189, 
				typename T190, typename T191, typename T192, typename T193, typename T194, typename T195, typename T196, typename T197, typename T198, typename T199, 
				typename T200, typename T201, typename T202, typename T203, typename T204, typename T205, typename T206, typename T207, typename T208, typename T209, 
				typename T210, typename T211, typename T212, typename T213, typename T214, typename T215, typename T216, typename T217, typename T218, typename T219, 
				typename T220, typename T221, typename T222, typename T223, typename T224, typename T225, typename T226, typename T227, typename T228, typename T229, 
				typename T230, typename T231, typename T232, typename T233, typename T234, typename T235, typename T236, typename T237, typename T238, typename T239, 
				typename T240, typename T241, typename T242, typename T243, typename T244, typename T245, typename T246, typename T247, typename T248, typename T249, 
				typename T250, typename T251, typename T252, typename T253, typename T254>
			struct type_chooser_helper<true, 0, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, 
				T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, 
				T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, 
				T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, 
				T40, T41, T42, T43, T44, T45, T46, T47, T48, T49, 
				T50, T51, T52, T53, T54, T55, T56, T57, T58, T59, 
				T60, T61, T62, T63, T64, T65, T66, T67, T68, T69, 
				T70, T71, T72, T73, T74, T75, T76, T77, T78, T79, 
				T80, T81, T82, T83, T84, T85, T86, T87, T88, T89, 
				T90, T91, T92, T93, T94, T95, T96, T97, T98, T99, 
				T100, T101, T102, T103, T104, T105, T106, T107, T108, T109, 
				T110, T111, T112, T113, T114, T115, T116, T117, T118, T119, 
				T120, T121, T122, T123, T124, T125, T126, T127, T128, T129, 
				T130, T131, T132, T133, T134, T135, T136, T137, T138, T139, 
				T140, T141, T142, T143, T144, T145, T146, T147, T148, T149, 
				T150, T151, T152, T153, T154, T155, T156, T157, T158, T159, 
				T160, T161, T162, T163, T164, T165, T166, T167, T168, T169, 
				T170, T171, T172, T173, T174, T175, T176, T177, T178, T179, 
				T180, T181, T182, T183, T184, T185, T186, T187, T188, T189, 
				T190, T191, T192, T193, T194, T195, T196, T197, T198, T199, 
				T200, T201, T202, T203, T204, T205, T206, T207, T208, T209, 
				T210, T211, T212, T213, T214, T215, T216, T217, T218, T219, 
				T220, T221, T222, T223, T224, T225, T226, T227, T228, T229, 
				T230, T231, T232, T233, T234, T235, T236, T237, T238, T239, 
				T240, T241, T242, T243, T244, T245, T246, T247, T248, T249, 
				T250, T251, T252, T253, T254>
			{
				public:
					typedef T0 type;

				private:
					typedef kerbal::type_traits::is_same<type, kerbal::type_traits::detail::type_chooser_void_helper> index_out_of_bound;
					KERBAL_STATIC_ASSERT(!index_out_of_bound::value, "Index is out of bound");
			};

		} // namespace detail


		MODULE_EXPORT
		template <size_t Index, typename T0 = kerbal::type_traits::detail::type_chooser_void_helper, typename T1 = kerbal::type_traits::detail::type_chooser_void_helper, typename T2 = kerbal::type_traits::detail::type_chooser_void_helper, typename T3 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T4 = kerbal::type_traits::detail::type_chooser_void_helper, typename T5 = kerbal::type_traits::detail::type_chooser_void_helper, typename T6 = kerbal::type_traits::detail::type_chooser_void_helper, typename T7 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T8 = kerbal::type_traits::detail::type_chooser_void_helper, typename T9 = kerbal::type_traits::detail::type_chooser_void_helper, typename T10 = kerbal::type_traits::detail::type_chooser_void_helper, typename T11 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T12 = kerbal::type_traits::detail::type_chooser_void_helper, typename T13 = kerbal::type_traits::detail::type_chooser_void_helper, typename T14 = kerbal::type_traits::detail::type_chooser_void_helper, typename T15 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T16 = kerbal::type_traits::detail::type_chooser_void_helper, typename T17 = kerbal::type_traits::detail::type_chooser_void_helper, typename T18 = kerbal::type_traits::detail::type_chooser_void_helper, typename T19 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T20 = kerbal::type_traits::detail::type_chooser_void_helper, typename T21 = kerbal::type_traits::detail::type_chooser_void_helper, typename T22 = kerbal::type_traits::detail::type_chooser_void_helper, typename T23 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T24 = kerbal::type_traits::detail::type_chooser_void_helper, typename T25 = kerbal::type_traits::detail::type_chooser_void_helper, typename T26 = kerbal::type_traits::detail::type_chooser_void_helper, typename T27 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T28 = kerbal::type_traits::detail::type_chooser_void_helper, typename T29 = kerbal::type_traits::detail::type_chooser_void_helper, typename T30 = kerbal::type_traits::detail::type_chooser_void_helper, typename T31 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T32 = kerbal::type_traits::detail::type_chooser_void_helper, typename T33 = kerbal::type_traits::detail::type_chooser_void_helper, typename T34 = kerbal::type_traits::detail::type_chooser_void_helper, typename T35 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T36 = kerbal::type_traits::detail::type_chooser_void_helper, typename T37 = kerbal::type_traits::detail::type_chooser_void_helper, typename T38 = kerbal::type_traits::detail::type_chooser_void_helper, typename T39 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T40 = kerbal::type_traits::detail::type_chooser_void_helper, typename T41 = kerbal::type_traits::detail::type_chooser_void_helper, typename T42 = kerbal::type_traits::detail::type_chooser_void_helper, typename T43 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T44 = kerbal::type_traits::detail::type_chooser_void_helper, typename T45 = kerbal::type_traits::detail::type_chooser_void_helper, typename T46 = kerbal::type_traits::detail::type_chooser_void_helper, typename T47 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T48 = kerbal::type_traits::detail::type_chooser_void_helper, typename T49 = kerbal::type_traits::detail::type_chooser_void_helper, typename T50 = kerbal::type_traits::detail::type_chooser_void_helper, typename T51 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T52 = kerbal::type_traits::detail::type_chooser_void_helper, typename T53 = kerbal::type_traits::detail::type_chooser_void_helper, typename T54 = kerbal::type_traits::detail::type_chooser_void_helper, typename T55 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T56 = kerbal::type_traits::detail::type_chooser_void_helper, typename T57 = kerbal::type_traits::detail::type_chooser_void_helper, typename T58 = kerbal::type_traits::detail::type_chooser_void_helper, typename T59 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T60 = kerbal::type_traits::detail::type_chooser_void_helper, typename T61 = kerbal::type_traits::detail::type_chooser_void_helper, typename T62 = kerbal::type_traits::detail::type_chooser_void_helper, typename T63 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T64 = kerbal::type_traits::detail::type_chooser_void_helper, typename T65 = kerbal::type_traits::detail::type_chooser_void_helper, typename T66 = kerbal::type_traits::detail::type_chooser_void_helper, typename T67 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T68 = kerbal::type_traits::detail::type_chooser_void_helper, typename T69 = kerbal::type_traits::detail::type_chooser_void_helper, typename T70 = kerbal::type_traits::detail::type_chooser_void_helper, typename T71 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T72 = kerbal::type_traits::detail::type_chooser_void_helper, typename T73 = kerbal::type_traits::detail::type_chooser_void_helper, typename T74 = kerbal::type_traits::detail::type_chooser_void_helper, typename T75 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T76 = kerbal::type_traits::detail::type_chooser_void_helper, typename T77 = kerbal::type_traits::detail::type_chooser_void_helper, typename T78 = kerbal::type_traits::detail::type_chooser_void_helper, typename T79 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T80 = kerbal::type_traits::detail::type_chooser_void_helper, typename T81 = kerbal::type_traits::detail::type_chooser_void_helper, typename T82 = kerbal::type_traits::detail::type_chooser_void_helper, typename T83 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T84 = kerbal::type_traits::detail::type_chooser_void_helper, typename T85 = kerbal::type_traits::detail::type_chooser_void_helper, typename T86 = kerbal::type_traits::detail::type_chooser_void_helper, typename T87 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T88 = kerbal::type_traits::detail::type_chooser_void_helper, typename T89 = kerbal::type_traits::detail::type_chooser_void_helper, typename T90 = kerbal::type_traits::detail::type_chooser_void_helper, typename T91 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T92 = kerbal::type_traits::detail::type_chooser_void_helper, typename T93 = kerbal::type_traits::detail::type_chooser_void_helper, typename T94 = kerbal::type_traits::detail::type_chooser_void_helper, typename T95 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T96 = kerbal::type_traits::detail::type_chooser_void_helper, typename T97 = kerbal::type_traits::detail::type_chooser_void_helper, typename T98 = kerbal::type_traits::detail::type_chooser_void_helper, typename T99 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T100 = kerbal::type_traits::detail::type_chooser_void_helper, typename T101 = kerbal::type_traits::detail::type_chooser_void_helper, typename T102 = kerbal::type_traits::detail::type_chooser_void_helper, typename T103 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T104 = kerbal::type_traits::detail::type_chooser_void_helper, typename T105 = kerbal::type_traits::detail::type_chooser_void_helper, typename T106 = kerbal::type_traits::detail::type_chooser_void_helper, typename T107 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T108 = kerbal::type_traits::detail::type_chooser_void_helper, typename T109 = kerbal::type_traits::detail::type_chooser_void_helper, typename T110 = kerbal::type_traits::detail::type_chooser_void_helper, typename T111 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T112 = kerbal::type_traits::detail::type_chooser_void_helper, typename T113 = kerbal::type_traits::detail::type_chooser_void_helper, typename T114 = kerbal::type_traits::detail::type_chooser_void_helper, typename T115 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T116 = kerbal::type_traits::detail::type_chooser_void_helper, typename T117 = kerbal::type_traits::detail::type_chooser_void_helper, typename T118 = kerbal::type_traits::detail::type_chooser_void_helper, typename T119 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T120 = kerbal::type_traits::detail::type_chooser_void_helper, typename T121 = kerbal::type_traits::detail::type_chooser_void_helper, typename T122 = kerbal::type_traits::detail::type_chooser_void_helper, typename T123 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T124 = kerbal::type_traits::detail::type_chooser_void_helper, typename T125 = kerbal::type_traits::detail::type_chooser_void_helper, typename T126 = kerbal::type_traits::detail::type_chooser_void_helper, typename T127 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T128 = kerbal::type_traits::detail::type_chooser_void_helper, typename T129 = kerbal::type_traits::detail::type_chooser_void_helper, typename T130 = kerbal::type_traits::detail::type_chooser_void_helper, typename T131 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T132 = kerbal::type_traits::detail::type_chooser_void_helper, typename T133 = kerbal::type_traits::detail::type_chooser_void_helper, typename T134 = kerbal::type_traits::detail::type_chooser_void_helper, typename T135 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T136 = kerbal::type_traits::detail::type_chooser_void_helper, typename T137 = kerbal::type_traits::detail::type_chooser_void_helper, typename T138 = kerbal::type_traits::detail::type_chooser_void_helper, typename T139 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T140 = kerbal::type_traits::detail::type_chooser_void_helper, typename T141 = kerbal::type_traits::detail::type_chooser_void_helper, typename T142 = kerbal::type_traits::detail::type_chooser_void_helper, typename T143 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T144 = kerbal::type_traits::detail::type_chooser_void_helper, typename T145 = kerbal::type_traits::detail::type_chooser_void_helper, typename T146 = kerbal::type_traits::detail::type_chooser_void_helper, typename T147 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T148 = kerbal::type_traits::detail::type_chooser_void_helper, typename T149 = kerbal::type_traits::detail::type_chooser_void_helper, typename T150 = kerbal::type_traits::detail::type_chooser_void_helper, typename T151 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T152 = kerbal::type_traits::detail::type_chooser_void_helper, typename T153 = kerbal::type_traits::detail::type_chooser_void_helper, typename T154 = kerbal::type_traits::detail::type_chooser_void_helper, typename T155 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T156 = kerbal::type_traits::detail::type_chooser_void_helper, typename T157 = kerbal::type_traits::detail::type_chooser_void_helper, typename T158 = kerbal::type_traits::detail::type_chooser_void_helper, typename T159 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T160 = kerbal::type_traits::detail::type_chooser_void_helper, typename T161 = kerbal::type_traits::detail::type_chooser_void_helper, typename T162 = kerbal::type_traits::detail::type_chooser_void_helper, typename T163 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T164 = kerbal::type_traits::detail::type_chooser_void_helper, typename T165 = kerbal::type_traits::detail::type_chooser_void_helper, typename T166 = kerbal::type_traits::detail::type_chooser_void_helper, typename T167 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T168 = kerbal::type_traits::detail::type_chooser_void_helper, typename T169 = kerbal::type_traits::detail::type_chooser_void_helper, typename T170 = kerbal::type_traits::detail::type_chooser_void_helper, typename T171 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T172 = kerbal::type_traits::detail::type_chooser_void_helper, typename T173 = kerbal::type_traits::detail::type_chooser_void_helper, typename T174 = kerbal::type_traits::detail::type_chooser_void_helper, typename T175 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T176 = kerbal::type_traits::detail::type_chooser_void_helper, typename T177 = kerbal::type_traits::detail::type_chooser_void_helper, typename T178 = kerbal::type_traits::detail::type_chooser_void_helper, typename T179 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T180 = kerbal::type_traits::detail::type_chooser_void_helper, typename T181 = kerbal::type_traits::detail::type_chooser_void_helper, typename T182 = kerbal::type_traits::detail::type_chooser_void_helper, typename T183 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T184 = kerbal::type_traits::detail::type_chooser_void_helper, typename T185 = kerbal::type_traits::detail::type_chooser_void_helper, typename T186 = kerbal::type_traits::detail::type_chooser_void_helper, typename T187 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T188 = kerbal::type_traits::detail::type_chooser_void_helper, typename T189 = kerbal::type_traits::detail::type_chooser_void_helper, typename T190 = kerbal::type_traits::detail::type_chooser_void_helper, typename T191 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T192 = kerbal::type_traits::detail::type_chooser_void_helper, typename T193 = kerbal::type_traits::detail::type_chooser_void_helper, typename T194 = kerbal::type_traits::detail::type_chooser_void_helper, typename T195 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T196 = kerbal::type_traits::detail::type_chooser_void_helper, typename T197 = kerbal::type_traits::detail::type_chooser_void_helper, typename T198 = kerbal::type_traits::detail::type_chooser_void_helper, typename T199 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T200 = kerbal::type_traits::detail::type_chooser_void_helper, typename T201 = kerbal::type_traits::detail::type_chooser_void_helper, typename T202 = kerbal::type_traits::detail::type_chooser_void_helper, typename T203 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T204 = kerbal::type_traits::detail::type_chooser_void_helper, typename T205 = kerbal::type_traits::detail::type_chooser_void_helper, typename T206 = kerbal::type_traits::detail::type_chooser_void_helper, typename T207 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T208 = kerbal::type_traits::detail::type_chooser_void_helper, typename T209 = kerbal::type_traits::detail::type_chooser_void_helper, typename T210 = kerbal::type_traits::detail::type_chooser_void_helper, typename T211 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T212 = kerbal::type_traits::detail::type_chooser_void_helper, typename T213 = kerbal::type_traits::detail::type_chooser_void_helper, typename T214 = kerbal::type_traits::detail::type_chooser_void_helper, typename T215 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T216 = kerbal::type_traits::detail::type_chooser_void_helper, typename T217 = kerbal::type_traits::detail::type_chooser_void_helper, typename T218 = kerbal::type_traits::detail::type_chooser_void_helper, typename T219 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T220 = kerbal::type_traits::detail::type_chooser_void_helper, typename T221 = kerbal::type_traits::detail::type_chooser_void_helper, typename T222 = kerbal::type_traits::detail::type_chooser_void_helper, typename T223 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T224 = kerbal::type_traits::detail::type_chooser_void_helper, typename T225 = kerbal::type_traits::detail::type_chooser_void_helper, typename T226 = kerbal::type_traits::detail::type_chooser_void_helper, typename T227 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T228 = kerbal::type_traits::detail::type_chooser_void_helper, typename T229 = kerbal::type_traits::detail::type_chooser_void_helper, typename T230 = kerbal::type_traits::detail::type_chooser_void_helper, typename T231 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T232 = kerbal::type_traits::detail::type_chooser_void_helper, typename T233 = kerbal::type_traits::detail::type_chooser_void_helper, typename T234 = kerbal::type_traits::detail::type_chooser_void_helper, typename T235 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T236 = kerbal::type_traits::detail::type_chooser_void_helper, typename T237 = kerbal::type_traits::detail::type_chooser_void_helper, typename T238 = kerbal::type_traits::detail::type_chooser_void_helper, typename T239 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T240 = kerbal::type_traits::detail::type_chooser_void_helper, typename T241 = kerbal::type_traits::detail::type_chooser_void_helper, typename T242 = kerbal::type_traits::detail::type_chooser_void_helper, typename T243 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T244 = kerbal::type_traits::detail::type_chooser_void_helper, typename T245 = kerbal::type_traits::detail::type_chooser_void_helper, typename T246 = kerbal::type_traits::detail::type_chooser_void_helper, typename T247 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T248 = kerbal::type_traits::detail::type_chooser_void_helper, typename T249 = kerbal::type_traits::detail::type_chooser_void_helper, typename T250 = kerbal::type_traits::detail::type_chooser_void_helper, typename T251 = kerbal::type_traits::detail::type_chooser_void_helper, 
				typename T252 = kerbal::type_traits::detail::type_chooser_void_helper, typename T253 = kerbal::type_traits::detail::type_chooser_void_helper, typename T254 = kerbal::type_traits::detail::type_chooser_void_helper>
		struct type_chooser: kerbal::type_traits::detail::type_chooser_helper<Index < 255, Index, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, 
				T10, T11, T12, T13, T14, T15, T16, T17, T18, T19, 
				T20, T21, T22, T23, T24, T25, T26, T27, T28, T29, 
				T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, 
				T40, T41, T42, T43, T44, T45, T46, T47, T48, T49, 
				T50, T51, T52, T53, T54, T55, T56, T57, T58, T59, 
				T60, T61, T62, T63, T64, T65, T66, T67, T68, T69, 
				T70, T71, T72, T73, T74, T75, T76, T77, T78, T79, 
				T80, T81, T82, T83, T84, T85, T86, T87, T88, T89, 
				T90, T91, T92, T93, T94, T95, T96, T97, T98, T99, 
				T100, T101, T102, T103, T104, T105, T106, T107, T108, T109, 
				T110, T111, T112, T113, T114, T115, T116, T117, T118, T119, 
				T120, T121, T122, T123, T124, T125, T126, T127, T128, T129, 
				T130, T131, T132, T133, T134, T135, T136, T137, T138, T139, 
				T140, T141, T142, T143, T144, T145, T146, T147, T148, T149, 
				T150, T151, T152, T153, T154, T155, T156, T157, T158, T159, 
				T160, T161, T162, T163, T164, T165, T166, T167, T168, T169, 
				T170, T171, T172, T173, T174, T175, T176, T177, T178, T179, 
				T180, T181, T182, T183, T184, T185, T186, T187, T188, T189, 
				T190, T191, T192, T193, T194, T195, T196, T197, T198, T199, 
				T200, T201, T202, T203, T204, T205, T206, T207, T208, T209, 
				T210, T211, T212, T213, T214, T215, T216, T217, T218, T219, 
				T220, T221, T222, T223, T224, T225, T226, T227, T228, T229, 
				T230, T231, T232, T233, T234, T235, T236, T237, T238, T239, 
				T240, T241, T242, T243, T244, T245, T246, T247, T248, T249, 
				T250, T251, T252, T253, T254>
		{
			private:
				KERBAL_STATIC_ASSERT(Index < 255, "Index is larger than the maximum figure supported");
		};

#	else

		MODULE_EXPORT
		template <size_t Index, typename T0, typename ... Args>
		struct type_chooser;

		MODULE_EXPORT
		template <typename T0, typename ... Args>
		struct type_chooser<0, T0, Args...>
		{
				typedef T0 type;
		};

		MODULE_EXPORT
		template <size_t Index, typename T0, typename ... Args>
		struct type_chooser
		{
				static_assert(Index <= sizeof...(Args), "Index is out of bound");
				typedef typename type_chooser<Index - 1, Args...>::type type;
		};

#	endif

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_TYPE_CHOOSER_HPP
