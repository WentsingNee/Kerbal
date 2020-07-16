/**
 * @file       concept_constraint.hpp
 * @brief
 * @date       2020-03-09
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ITERATOR_CONCEPT_CONSTRAINT_HPP
#define KERBAL_ITERATOR_CONCEPT_CONSTRAINT_HPP

#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/iterator/iterator_traits.hpp>

#ifndef KERBAL_INPUT_ITERATOR_CONSTRAINT
#	define KERBAL_INPUT_ITERATOR_CONSTRAINT(iterator_type) \
		KERBAL_STATIC_ASSERT( \
			kerbal::iterator::is_input_compatible_iterator<iterator_type>::value, \
			"Instantiation of type '"#iterator_type"' doesn't satisfy input iterator constraints" \
		)
#endif

#ifndef KERBAL_FORWARD_ITERATOR_CONSTRAINT
#	define KERBAL_FORWARD_ITERATOR_CONSTRAINT(iterator_type) \
		KERBAL_STATIC_ASSERT( \
			kerbal::iterator::is_forward_compatible_iterator<iterator_type>::value, \
			"Instantiation of type '"#iterator_type"' doesn't satisfy forward iterator constraints" \
		)
#endif

#ifndef KERBAL_BIDIRECTIONAL_ITERATOR_CONSTRAINT
#	define KERBAL_BIDIRECTIONAL_ITERATOR_CONSTRAINT(iterator_type) \
		KERBAL_STATIC_ASSERT( \
			kerbal::iterator::is_bidirectional_compatible_iterator<iterator_type>::value, \
			"Instantiation of type '"#iterator_type"' doesn't satisfy bidirectional iterator constraints" \
		)
#endif

#ifndef KERBAL_RANDOM_ACCESS_ITERATOR_CONSTRAINT
#	define KERBAL_RANDOM_ACCESS_ITERATOR_CONSTRAINT(iterator_type) \
		KERBAL_STATIC_ASSERT( \
			kerbal::iterator::is_random_access_compatible_iterator<iterator_type>::value, \
			"Instantiation of type '"#iterator_type"' doesn't satisfy random access iterator constraints" \
		)
#endif



#endif // KERBAL_ITERATOR_CONCEPT_CONSTRAINT_HPP
