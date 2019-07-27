/**
 * @file       decay.hpp
 * @brief      
 * @date       2019-7-24
 * @author     peter
 * @copyright
 *      peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_DECAY_HPP_
#define KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_DECAY_HPP_

#include <kerbal/ts/modules_ts/modules_ts.hpp>

#include <kerbal/type_traits/type_traits_details/array_traits.hpp>
#include <kerbal/type_traits/type_traits_details/conditional.hpp>
#include <kerbal/type_traits/type_traits_details/cv_deduction.hpp>
#include <kerbal/type_traits/type_traits_details/is_function.hpp>
#include <kerbal/type_traits/type_traits_details/pointer_deduction.hpp>
#include <kerbal/type_traits/type_traits_details/reference_deduction.hpp>

namespace kerbal
{

	namespace type_traits
	{

		MODULE_EXPORT
		template <typename Tp>
		struct decay
		{
			private:
				typedef typename kerbal::type_traits::remove_reference<Tp>::type U;

			public:
				typedef typename kerbal::type_traits::conditional<
					kerbal::type_traits::is_array<U>::value,
					typename kerbal::type_traits::remove_extent<U>::type*,
					typename kerbal::type_traits::conditional<
						kerbal::type_traits::is_function<U>::value,
						typename kerbal::type_traits::add_pointer<U>::type,
						typename kerbal::type_traits::remove_cv<U>::type
					>::type
				>::type type;
		};
	}
}

#endif /* KERBAL_TYPE_TRAITS_TYPE_TRAITS_DETAILS_DECAY_HPP_ */
