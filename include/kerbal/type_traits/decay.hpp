/**
 * @file       decay.hpp
 * @brief
 * @date       2019-7-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_DECAY_HPP
#define KERBAL_TYPE_TRAITS_DECAY_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/cv_deduction.hpp>
#include <kerbal/type_traits/function_deduction.hpp>
#include <kerbal/type_traits/is_array.hpp>
#include <kerbal/type_traits/pointer_deduction.hpp>
#include <kerbal/type_traits/remove_extent.hpp>
#include <kerbal/type_traits/remove_reference.hpp>


namespace kerbal
{

	namespace type_traits
	{

		template <typename _Up,
				bool _IsArray = kerbal::type_traits::is_array<_Up>::value,
				bool _IsFunction = kerbal::type_traits::is_function<_Up>::value>
		struct __decay_selector;

		template <typename _Up>
		struct __decay_selector<_Up, false, false>
		{
			typedef typename kerbal::type_traits::remove_cv<_Up>::type type;
		};

		template <typename _Up>
		struct __decay_selector<_Up, true, false>
		{
			typedef typename kerbal::type_traits::remove_extent<_Up>::type *type;
		};

		template <typename _Up>
		struct __decay_selector<_Up, false, true>
		{
			typedef typename kerbal::type_traits::add_pointer<_Up>::type type;
		};

		MODULE_EXPORT
		template <typename Tp>
		struct decay
		{
			private:
				typedef typename kerbal::type_traits::remove_reference<Tp>::type U;

			public:
				typedef typename __decay_selector<U>::type type;
		};

	} // namespace type_traits

} // namespace kerbal

#endif // KERBAL_TYPE_TRAITS_DECAY_HPP
