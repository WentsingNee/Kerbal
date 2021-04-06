/**
 * @file       predicate.hpp
 * @brief
 * @date       2020-07-18
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_FUNCTION_PREDICATE_HPP
#define KERBAL_FUNCTION_PREDICATE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif

namespace kerbal
{

	namespace function
	{

//		template <typename Comp>
//		struct val_to_iter
//		{
//				Comp comp;
//
//				KERBAL_CONSTEXPR
//				val_to_iter(const Comp& comp) : comp(comp)
//				{
//				}
//
//				template <typename Tp, typename Iter>
//				KERBAL_CONSTEXPR
//				bool operator()(const Tp & val, const Iter & iter) const
//				{
//					return comp(val, *iter);
//				}
//		};
//
//		template <typename Comp>
//		KERBAL_CONSTEXPR
//		val_to_iter<Comp> make_val_to_iter(const Comp& comp)
//		{
//			return val_to_iter<Comp>(comp);
//		}
//
//		template <typename Comp>
//		struct iter_to_val
//		{
//				Comp comp;
//
//				KERBAL_CONSTEXPR
//				iter_to_val(const Comp& comp) : comp(comp)
//				{
//				}
//
//				template <typename Iter, typename Tp>
//				KERBAL_CONSTEXPR
//				bool operator()(const Iter & iter, const Tp & val) const
//				{
//					return comp(*iter, val);
//				}
//		};
//
//		template <typename Comp>
//		KERBAL_CONSTEXPR
//		iter_to_val<Comp> make_iter_to_val(const Comp& comp)
//		{
//			return iter_to_val<Comp>(comp);
//		}
//
//		template <typename Comp>
//		struct iter_to_iter
//		{
//				Comp comp;
//
//				KERBAL_CONSTEXPR
//				iter_to_iter(const Comp& comp) : comp(comp)
//				{
//				}
//
//				template <typename Iter, typename Iter2>
//				KERBAL_CONSTEXPR
//				bool operator()(const Iter & iter, const Iter2 & iter2) const
//				{
//					return comp(*iter, *iter2);
//				}
//		};
//
//		template <typename Comp>
//		KERBAL_CONSTEXPR
//		iter_to_iter<Comp> make_iter_to_iter(const Comp& comp)
//		{
//			return iter_to_iter<Comp>(comp);
//		}
//
//		struct generic_less
//		{
//				template <typename Tp, typename Up>
//				KERBAL_CONSTEXPR
//				bool operator()(const Tp & lhs, const Up & rhs) const
//				{
//					return lhs < rhs;
//				}
//		};

		template <typename Tp>
		struct less
		{
				KERBAL_CONSTEXPR
				bool operator()(const Tp & lhs, const Tp & rhs) const
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs < rhs))
				{
					return lhs < rhs;
				}
		};

#	if __cplusplus >= 201103L

		template <>
		struct less<void>
		{
				template <typename Tp, typename Up>
				KERBAL_CONSTEXPR
				auto operator()(Tp && lhs, Tp && rhs) const
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(kerbal::utility::forward<Tp>(lhs) < kerbal::utility::forward<Up>(rhs)))
							-> decltype(kerbal::utility::forward<Tp>(lhs) < kerbal::utility::forward<Up>(rhs))
				{
					return kerbal::utility::forward<Tp>(lhs) < kerbal::utility::forward<Up>(rhs);
				}
		};

#	endif

		template <typename Tp>
		struct less_equal
		{
				KERBAL_CONSTEXPR
				bool operator()(const Tp & lhs, const Tp & rhs) const
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs <= rhs))
				{
					return lhs <= rhs;
				}
		};

#	if __cplusplus >= 201103L

		template <>
		struct less_equal<void>
		{
				template <typename Tp, typename Up>
				KERBAL_CONSTEXPR
				auto operator()(Tp && lhs, Tp && rhs) const
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(kerbal::utility::forward<Tp>(lhs) <= kerbal::utility::forward<Up>(rhs)))
							-> decltype(kerbal::utility::forward<Tp>(lhs) <= kerbal::utility::forward<Up>(rhs))
				{
					return kerbal::utility::forward<Tp>(lhs) <= kerbal::utility::forward<Up>(rhs);
				}
		};

#	endif

		template <typename Tp>
		struct greater
		{
				KERBAL_CONSTEXPR
				bool operator()(const Tp & lhs, const Tp & rhs) const
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs > rhs))
				{
					return lhs > rhs;
				}
		};

#	if __cplusplus >= 201103L

		template <>
		struct greater<void>
		{
				template <typename Tp, typename Up>
				KERBAL_CONSTEXPR
				auto operator()(Tp && lhs, Tp && rhs) const
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(kerbal::utility::forward<Tp>(lhs) > kerbal::utility::forward<Up>(rhs)))
							-> decltype(kerbal::utility::forward<Tp>(lhs) > kerbal::utility::forward<Up>(rhs))
				{
					return kerbal::utility::forward<Tp>(lhs) > kerbal::utility::forward<Up>(rhs);
				}
		};

#	endif

		template <typename Tp>
		struct greater_equal
		{
				KERBAL_CONSTEXPR
				bool operator()(const Tp & lhs, const Tp & rhs) const
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs >= rhs))
				{
					return lhs >= rhs;
				}
		};

#	if __cplusplus >= 201103L

		template <>
		struct greater_equal<void>
		{
				template <typename Tp, typename Up>
				KERBAL_CONSTEXPR
				auto operator()(Tp && lhs, Tp && rhs) const
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(kerbal::utility::forward<Tp>(lhs) >= kerbal::utility::forward<Up>(rhs)))
							-> decltype(kerbal::utility::forward<Tp>(lhs) >= kerbal::utility::forward<Up>(rhs))
				{
					return kerbal::utility::forward<Tp>(lhs) >= kerbal::utility::forward<Up>(rhs);
				}
		};

#	endif

		template <typename Tp>
		struct equal_to
		{
				KERBAL_CONSTEXPR
				bool operator()(const Tp & lhs, const Tp & rhs) const
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs == rhs))
				{
					return lhs == rhs;
				}
		};

#	if __cplusplus >= 201103L

		template <>
		struct equal_to<void>
		{
				template <typename Tp, typename Up>
				KERBAL_CONSTEXPR
				auto operator()(Tp && lhs, Tp && rhs) const
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(kerbal::utility::forward<Tp>(lhs) == kerbal::utility::forward<Up>(rhs)))
							-> decltype(kerbal::utility::forward<Tp>(lhs) == kerbal::utility::forward<Up>(rhs))
				{
					return kerbal::utility::forward<Tp>(lhs) == kerbal::utility::forward<Up>(rhs);
				}
		};

#	endif

		template <typename Tp>
		struct not_equal_to
		{
				KERBAL_CONSTEXPR
				bool operator()(const Tp & lhs, const Tp & rhs) const
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs != rhs))
				{
					return lhs != rhs;
				}
		};

#	if __cplusplus >= 201103L

		template <>
		struct not_equal_to<void>
		{
				template <typename Tp, typename Up>
				KERBAL_CONSTEXPR
				auto operator()(Tp && lhs, Tp && rhs) const
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(kerbal::utility::forward<Tp>(lhs) != kerbal::utility::forward<Up>(rhs)))
							-> decltype(kerbal::utility::forward<Tp>(lhs) != kerbal::utility::forward<Up>(rhs))
				{
					return kerbal::utility::forward<Tp>(lhs) != kerbal::utility::forward<Up>(rhs);
				}
		};

#	endif



		struct generic_less
		{
				template <typename Tp>
				KERBAL_CONSTEXPR
				bool operator()(const Tp & lhs, const Tp & rhs) const
						KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs < rhs))
				{
					return lhs < rhs;
				}
		};

	}

}



#endif // KERBAL_FUNCTION_PREDICATE_HPP
