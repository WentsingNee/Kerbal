///**
// * @file       x.hpp
// * @brief
// * @date       2024-08-12
// * @author     Peter
// * @copyright
// *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
// *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
// *   all rights reserved
// */
//
//#ifndef KERBAL_X_HPP
//#define KERBAL_X_HPP
//
//#include <kerbal/iterator/iterator_traits.hpp>
//#include <kerbal/type_traits/is_array.hpp>
//#include <kerbal/type_traits/is_same.hpp>
//#include <kerbal/type_traits/integral_constant.hpp>
//#include <kerbal/type_traits/logical.hpp>
//
//#include <iterator>
//
//#include <cstddef>
//
//
//template <typename T, typename U>
//void generic_assign(T & lhs, const U & rhs);
//
//template <typename T, typename U, std::size_t N>
//void generic_assign(T (& lhs)[N], const U (& rhs)[N]);
//
//template <typename OutputIterator, typename InputIterator>
//void basic_generic_copy(
//	OutputIterator out,
//	InputIterator first, InputIterator last
//);
//
//
//
//template <typename T, typename U>
//void basic_generic_copy(T & lhs, const U & rhs)
//{
//	lhs = rhs;
//}
//
//template <typename OutputIterator, typename InputIterator>
//void basic_generic_copy(
//	OutputIterator out,
//	InputIterator first, InputIterator last,
//	kerbal::type_traits::false_type
//)
//{
//	while (first != last) {
//		generic_assign(*out, *first);
//		++first;
//		++out;
//	}
//}
//
//template <typename OutputIterator, typename InputIterator>
//void basic_generic_copy(
//	OutputIterator out,
//	InputIterator first, InputIterator last,
//	kerbal::type_traits::true_type
//)
//{
//	typedef std::iterator_traits<OutputIterator> output_iterator_traits;
//	typedef std::iterator_traits<InputIterator> input_iterator_traits;
//
////	typedef typename output_iterator_traits::pointer output_pointer;
////	typedef typename input_iterator_traits::pointer input_pointer;
//
//	basic_generic_copy(&*out[0], &*first[0], &*last[0]);
//}
//
//template <typename OutputIterator, typename InputIterator>
//void basic_generic_copy(
//	OutputIterator out,
//	InputIterator first, InputIterator last
//)
//{
//	typedef std::iterator_traits<InputIterator> input_iterator_traits;
//
//	basic_generic_copy(
//		out,
//		first, last,
//		kerbal::type_traits::conjunction<
//			kerbal::type_traits::is_same<
//				typename input_iterator_traits::iterator_concept,
//				std::contiguous_iterator_tag
//			>,
//			kerbal::type_traits::is_array<
//				typename input_iterator_traits::value_type
//			>
//		>()
//	);
//}
//
//template <typename T, typename U>
//void generic_assign(T & lhs, const U & rhs)
//{
//	basic_generic_copy(lhs, rhs);
//}
//
//template <typename T, typename U, std::size_t N>
//void generic_assign(T (& lhs)[N], const U (& rhs)[N])
//{
//	basic_generic_copy(lhs, rhs, rhs + N);
//}
//
//#endif // KERBAL_X_HPP
