/**
 * @file       copy.hpp
 * @brief
 * @date       2021-1-1
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_MODIFIER_COPY_HPP
#define KERBAL_ALGORITHM_MODIFIER_COPY_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/is_constant_evaluated.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/operators/generic_assign.hpp>

#include <iterator>

#ifndef KERBAL_COPY_ENABLE_MEMMOVE_OPTIMIZATION

#	if __cplusplus < 201103L
#		define KERBAL_COPY_ENABLE_MEMMOVE_OPTIMIZATION 1
#	else
#		if KERBAL_IS_CONSTANT_EVALUATED_SUPPORTED
#			define KERBAL_COPY_ENABLE_MEMMOVE_OPTIMIZATION 1
#		else
#			define KERBAL_COPY_ENABLE_MEMMOVE_OPTIMIZATION 0
#		endif
#	endif

#endif


#if KERBAL_COPY_ENABLE_MEMMOVE_OPTIMIZATION

#	include <kerbal/type_traits/const_deduction.hpp>
#	include <kerbal/type_traits/integral_constant.hpp>
#	include <kerbal/type_traits/is_same.hpp>
#	include <kerbal/type_traits/volatile_deduction.hpp>

#	include <cstring>

#	if __cplusplus < 201103L
#		include <kerbal/type_traits/fundamental_deduction.hpp>
#		include <kerbal/type_traits/member_pointer_deduction.hpp>
#		include <kerbal/type_traits/pointer_deduction.hpp>
#	else
#		include <type_traits>
#	endif

#endif


namespace kerbal
{

	namespace algorithm
	{

		namespace detail
		{

#if KERBAL_COPY_ENABLE_MEMMOVE_OPTIMIZATION

			template <typename ContiguousIterator, typename OutputIterator>
			struct memmove_optimizable_helper
			{
				private:
					typedef typename kerbal::iterator::iterator_traits<ContiguousIterator>::value_type value_type;
					typedef typename kerbal::iterator::iterator_traits<OutputIterator>::value_type output_value_type;

				public:
					typedef
					kerbal::type_traits::bool_constant<
						kerbal::iterator::is_contiguous_iterator<ContiguousIterator>::value &&
						!kerbal::type_traits::is_volatile<value_type>::value &&
#	if __cplusplus < 201103L
						(
							kerbal::type_traits::is_fundamental<value_type>::value ||
							kerbal::type_traits::is_member_pointer<value_type>::value ||
							kerbal::type_traits::is_pointer<value_type>::value
						) &&
#	else
						std::is_trivially_copyable<value_type>::value &&
#	endif
						kerbal::iterator::is_contiguous_iterator<OutputIterator>::value &&
						!kerbal::type_traits::is_volatile<output_value_type>::value &&
						kerbal::type_traits::is_same<
							typename kerbal::type_traits::remove_const<value_type>::type,
							output_value_type
						>::value
					>
					type;
			};


			template <typename ContiguousIterator, typename OutputIterator>
			struct memmove_optimizable:
					memmove_optimizable_helper<ContiguousIterator, OutputIterator>::type
			{
			};

#endif

		} // namespace detail


		namespace detail
		{

			template <typename RandomAccessIterator, typename OutputIterator>
			KERBAL_CONSTEXPR14
			OutputIterator
			memmove_optimized_copy(RandomAccessIterator first, RandomAccessIterator last, OutputIterator to,
									kerbal::type_traits::false_type)
			{
				typedef RandomAccessIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

#		define EACH() do { \
					kerbal::operators::generic_assign(*to, *first); /*  *to = *first; */ \
					++to; \
					++first; \
				} while(false)

				difference_type trip_count(kerbal::iterator::distance(first, last));
				difference_type remain(trip_count & 3);
				for (trip_count >>= 2; trip_count > 0; --trip_count) {
					EACH();
					EACH();
					EACH();
					EACH();
				}

				if (remain >= 2) {
					EACH();
					EACH();
					remain -= 2;
				}
				if (remain >= 1) {
					EACH();
				}

#		undef EACH

				return to;
			}

#	if KERBAL_COPY_ENABLE_MEMMOVE_OPTIMIZATION

			template <typename ContiguousIterator, typename ContiguousOutputIterator>
			ContiguousOutputIterator
			memmove_optimized_copy(ContiguousIterator first, ContiguousIterator last, ContiguousOutputIterator to,
									kerbal::type_traits::true_type)
			{
				typedef ContiguousIterator iterator;
				typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

				size_t dist(last - first);
				std::memmove(&*to, &*first, dist * sizeof(value_type));
				return to + dist;
			}

#	endif

			template <typename InputIterator, typename OutputIterator>
			KERBAL_CONSTEXPR14
			OutputIterator
			_K_copy(InputIterator first, InputIterator last, OutputIterator to,
				   std::input_iterator_tag)
					KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(static_cast<bool>(first != last)) &&
							noexcept(kerbal::operators::generic_assign(*to, *first)) &&
							noexcept(++to) &&
							noexcept(++first)
					)
			{
				while (first != last) {
					kerbal::operators::generic_assign(*to, *first); // *to = *first;
					++to;
					++first;
				}
				return to;
			}

			template <typename RandomAccessIterator, typename OutputIterator>
			KERBAL_CONSTEXPR14
			OutputIterator
			_K_copy(RandomAccessIterator first, RandomAccessIterator last, OutputIterator to,
				   std::random_access_iterator_tag)
			{

#	if KERBAL_COPY_ENABLE_MEMMOVE_OPTIMIZATION

				typedef RandomAccessIterator iterator;
				typedef detail::memmove_optimizable<iterator, OutputIterator> memmove_optimizable;

#		if __cplusplus < 201103L

				return detail::memmove_optimized_copy(first, last, to, memmove_optimizable());

#		else

				return KERBAL_IS_CONSTANT_EVALUATED() ?
					   detail::memmove_optimized_copy(first, last, to, kerbal::type_traits::false_type()) :
					   detail::memmove_optimized_copy(first, last, to, memmove_optimizable());

#		endif

#	else
				return detail::memmove_optimized_copy(first, last, to, kerbal::type_traits::false_type());
#	endif

			}

		} // namespace detail

		template <typename InputIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		copy(InputIterator first, InputIterator last, OutputIterator to)
		{
			return kerbal::algorithm::detail::_K_copy(first, last, to, kerbal::iterator::iterator_category(first));
		}



		template <typename BidirectionalIterator, typename BidirectionalOutputIterator>
		KERBAL_CONSTEXPR14
		BidirectionalOutputIterator
		__copy_backward(BidirectionalIterator first, BidirectionalIterator last, BidirectionalOutputIterator to_last,
						std::bidirectional_iterator_tag)
				KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(static_cast<bool>(first != last)) &&
						noexcept(--last) &&
						noexcept(--to_last) &&
						noexcept(kerbal::operators::generic_assign(*to_last, *last))
				)
		{
			while (first != last) {
				--last;
				--to_last;
				kerbal::operators::generic_assign(*to_last, *last); // *to_last = *last;
			}
			return to_last;
		}

		template <typename RandomAccessIterator, typename BidirectionalOutputIterator>
		KERBAL_CONSTEXPR14
		BidirectionalOutputIterator
		__copy_backward_memmove_optimize(RandomAccessIterator first, RandomAccessIterator last, BidirectionalOutputIterator to_last,
										 kerbal::type_traits::false_type)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

#	define EACH() do { \
				--last; \
				--to_last; \
				kerbal::operators::generic_assign(*to_last, *last); /*  *to_last = *last; */ \
			} while (false)

			difference_type trip_count(kerbal::iterator::distance(first, last));
			difference_type remain(trip_count & 3);
			for (trip_count >>= 2; trip_count > 0; --trip_count) {
				EACH();
				EACH();
				EACH();
				EACH();
			}

			if (remain >= 2) {
				EACH();
				EACH();
				remain -= 2;
			}
			if (remain >= 1) {
				EACH();
			}

#	undef EACH

			return to_last;
		}

#	if KERBAL_COPY_ENABLE_MEMMOVE_OPTIMIZATION

		template <typename ContiguousIterator, typename ContiguousOutputIterator>
		KERBAL_CONSTEXPR14
		ContiguousOutputIterator
		__copy_backward_memmove_optimize(ContiguousIterator first, ContiguousIterator last, ContiguousOutputIterator to_last,
										 kerbal::type_traits::true_type)
		{
			typedef ContiguousIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;

			size_t dist(last - first);
			ContiguousOutputIterator to_first(to_last - dist);
			std::memmove(&*to_first, &*first, dist * sizeof(value_type));
			return to_first;
		}

#	endif

		template <typename RandomAccessIterator, typename BidirectionalOutputIterator>
		KERBAL_CONSTEXPR14
		BidirectionalOutputIterator
		__copy_backward(RandomAccessIterator first, RandomAccessIterator last, BidirectionalOutputIterator to_last,
						std::random_access_iterator_tag)
		{

#	if KERBAL_COPY_ENABLE_MEMMOVE_OPTIMIZATION

#		if __cplusplus < 201103L

			typedef RandomAccessIterator iterator;
			typedef detail::memmove_optimizable<iterator, BidirectionalOutputIterator> memmove_optimizable;
			return __copy_backward_memmove_optimize(first, last, to_last, memmove_optimizable());

#		else

			typedef RandomAccessIterator iterator;
			typedef detail::memmove_optimizable<iterator, BidirectionalOutputIterator> memmove_optimizable;

			return KERBAL_IS_CONSTANT_EVALUATED() ?
					__copy_backward_memmove_optimize(first, last, to_last, kerbal::type_traits::false_type()) :
					__copy_backward_memmove_optimize(first, last, to_last, memmove_optimizable());

#		endif

#	else
			return __copy_backward_memmove_optimize(first, last, to_last, kerbal::type_traits::false_type());
#	endif

		}

		template <typename BidirectionalIterator, typename BidirectionalOutputIterator>
		KERBAL_CONSTEXPR14
		BidirectionalOutputIterator
		copy_backward(BidirectionalIterator first, BidirectionalIterator last, BidirectionalOutputIterator to_last)
		{
			return kerbal::algorithm::__copy_backward(first, last, to_last, kerbal::iterator::iterator_category(first));
		}



		template <typename InputIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		__move(InputIterator first, InputIterator last, OutputIterator to, std::input_iterator_tag)
		{
			while (first != last) {
				kerbal::operators::generic_assign(*to, kerbal::compatibility::to_xvalue(*first));
				// *to = kerbal::compatibility::to_xvalue(*first);
				++to;
				++first;
			}
			return to;
		}

		template <typename RandomAccessIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		__move_memmove_optimize(RandomAccessIterator first, RandomAccessIterator last, OutputIterator to,
								kerbal::type_traits::false_type)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

#	define EACH() do { \
				kerbal::operators::generic_assign(*to, kerbal::compatibility::to_xvalue(*first)); \
				/*  *to = kerbal::compatibility::to_xvalue(*first); */ \
				++to; \
				++first; \
			} while(false)

			difference_type trip_count(kerbal::iterator::distance(first, last));
			difference_type remain(trip_count & 3);
			for (trip_count >>= 2; trip_count > 0; --trip_count) {
				EACH();
				EACH();
				EACH();
				EACH();
			}

			if (remain >= 2) {
				EACH();
				EACH();
				remain -= 2;
			}
			if (remain >= 1) {
				EACH();
			}

#	undef EACH

			return to;
		}


#	if KERBAL_COPY_ENABLE_MEMMOVE_OPTIMIZATION

		template <typename ContiguousIterator, typename ContiguousOutputIterator>
		ContiguousOutputIterator
		__move_memmove_optimize(ContiguousIterator first, ContiguousIterator last, ContiguousOutputIterator to,
								kerbal::type_traits::true_type)
		{
			return kerbal::algorithm::detail::memmove_optimized_copy(first, last, to, kerbal::type_traits::true_type());
		}

#	endif

		template <typename RandomAccessIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		__move(RandomAccessIterator first, RandomAccessIterator last, OutputIterator to,
			   std::random_access_iterator_tag)
		{

#	if KERBAL_COPY_ENABLE_MEMMOVE_OPTIMIZATION

			typedef RandomAccessIterator iterator;
			typedef detail::memmove_optimizable<iterator, OutputIterator> memmove_optimizable;

#		if __cplusplus < 201103L

			return __move_memmove_optimize(first, last, to, memmove_optimizable());

#		else

			return KERBAL_IS_CONSTANT_EVALUATED() ?
					__move_memmove_optimize(first, last, to, kerbal::type_traits::false_type()) :
					__move_memmove_optimize(first, last, to, memmove_optimizable());

#		endif

#	else
			return __move_memmove_optimize(first, last, to, kerbal::type_traits::false_type());
#	endif

		}

		template <typename InputIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		move(InputIterator first, InputIterator last, OutputIterator to)
		{
			return kerbal::algorithm::__move(first, last, to, kerbal::iterator::iterator_category(first));
		}



		template <typename BidirectionalIterator, typename BidirectionalOutputIterator>
		KERBAL_CONSTEXPR14
		BidirectionalOutputIterator
		__move_backward(BidirectionalIterator first, BidirectionalIterator last, BidirectionalOutputIterator to_last,
						std::bidirectional_iterator_tag)
		{
			while (first != last) {
				--last;
				--to_last;
				kerbal::operators::generic_assign(*to_last, kerbal::compatibility::to_xvalue(*last));
				// *to_last = kerbal::compatibility::to_xvalue(*last);
			}
			return to_last;
		}

		template <typename RandomAccessIterator, typename BidirectionalOutputIterator>
		KERBAL_CONSTEXPR14
		BidirectionalOutputIterator
		__move_backward_memmove_optimize(RandomAccessIterator first, RandomAccessIterator last, BidirectionalOutputIterator to_last,
										 kerbal::type_traits::false_type)
		{
			typedef RandomAccessIterator iterator;
			typedef typename kerbal::iterator::iterator_traits<iterator>::difference_type difference_type;

#	define EACH() do { \
				--last; \
				--to_last; \
				kerbal::operators::generic_assign(*to_last, kerbal::compatibility::to_xvalue(*last)); \
				/*  *to_last = kerbal::compatibility::to_xvalue(*last); */ \
			} while (false)

			difference_type trip_count(kerbal::iterator::distance(first, last));
			difference_type remain(trip_count & 3);
			for (trip_count >>= 2; trip_count > 0; --trip_count) {
				EACH();
				EACH();
				EACH();
				EACH();
			}

			if (remain >= 2) {
				EACH();
				EACH();
				remain -= 2;
			}
			if (remain >= 1) {
				EACH();
			}

#	undef EACH

			return to_last;
		}


#	if KERBAL_COPY_ENABLE_MEMMOVE_OPTIMIZATION

		template <typename ContiguousIterator, typename ContiguousOutputIterator>
		KERBAL_CONSTEXPR14
		ContiguousOutputIterator
		__move_backward_memmove_optimize(ContiguousIterator first, ContiguousIterator last, ContiguousOutputIterator to_last,
										 kerbal::type_traits::true_type)
		{
			return kerbal::algorithm::__copy_backward_memmove_optimize(first, last, to_last, kerbal::type_traits::true_type());
		}

#	endif


		template <typename RandomAccessIterator, typename BidirectionalOutputIterator>
		KERBAL_CONSTEXPR14
		BidirectionalOutputIterator
		__move_backward(RandomAccessIterator first, RandomAccessIterator last, BidirectionalOutputIterator to_last,
						std::random_access_iterator_tag)
		{

#	if KERBAL_COPY_ENABLE_MEMMOVE_OPTIMIZATION

			typedef RandomAccessIterator iterator;
			typedef detail::memmove_optimizable<iterator, BidirectionalOutputIterator> memmove_optimizable;

#		if __cplusplus < 201103L

			return __move_backward_memmove_optimize(first, last, to_last, memmove_optimizable());

#		else

			return KERBAL_IS_CONSTANT_EVALUATED() ?
					__move_backward_memmove_optimize(first, last, to_last, kerbal::type_traits::false_type()) :
					__move_backward_memmove_optimize(first, last, to_last, memmove_optimizable());

#		endif

#	else
			return __move_backward_memmove_optimize(first, last, to_last, kerbal::type_traits::false_type());
#	endif

		}

		template <typename BidirectionalIterator, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator
		move_backward(BidirectionalIterator first, BidirectionalIterator last, OutputIterator to_last)
		{
			return kerbal::algorithm::__move_backward(first, last, to_last, kerbal::iterator::iterator_category(first));
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_MODIFIER_COPY_HPP
