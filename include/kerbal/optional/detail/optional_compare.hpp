/**
 * @file       optional_compare.hpp
 * @brief
 * @date       2019-5-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OPTIONAL_DETAIL_OPTIONAL_COMPARE_HPP
#define KERBAL_OPTIONAL_DETAIL_OPTIONAL_COMPARE_HPP

#include <kerbal/optional/fwd/optional.fwd.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/optional/nullopt.hpp>


namespace kerbal
{

	namespace optional
	{

		/**
		 * @defgroup optional_compare
		 * Compare with kerbal::optional::optional
		 * @{
		 */
		template <typename T, typename U>
		KERBAL_CONSTEXPR
		bool operator==(const optional<T> & lhs, const optional<U> & rhs)
		{
			/*
			 * match (lhs.has_value(), rhs.has_value()) {
			 *     case true, true:
			 *         lhs == rhs
			 *     case true, false:
			 *         false
			 *     case false, true:
			 *         false
			 *     case false, false:
			 *         true
			 * }
			 */
			return (lhs.has_value() && rhs.has_value()) ?
				   (lhs.ignored_get() == rhs.ignored_get()) :
				   lhs.has_value() == rhs.has_value();
		}

		template <typename T, typename U>
		KERBAL_CONSTEXPR
		bool operator!=(const optional<T> & lhs, const optional<U> & rhs)
		{
			/*
			 * match (lhs.has_value(), rhs.has_value()) {
			 *     case true, true:
			 *         lhs != rhs
			 *     case true, false:
			 *         true
			 *     case false, true:
			 *         true
			 *     case false, false:
			 *         false
			 * }
			 */
			return (lhs.has_value() && rhs.has_value()) ?
				   (lhs.ignored_get() != rhs.ignored_get()) :
				   lhs.has_value() != rhs.has_value();
		}

		template <typename T, typename U>
		KERBAL_CONSTEXPR
		bool operator<(const optional<T> & lhs, const optional<U> & rhs)
		{
			/*
			 * match (lhs.has_value(), rhs.has_value()) {
			 *     case true, true:
			 *         lhs < rhs
			 *     case true, false:
			 *         false
			 *     case false, true:
			 *         true
			 *     case false, false:
			 *         false
			 * }
			 */
			return (lhs.has_value() && rhs.has_value()) ?
				   (lhs.ignored_get() < rhs.ignored_get()) :
				   rhs.has_value();
		}

		template <typename T, typename U>
		KERBAL_CONSTEXPR
		bool operator<=(const optional<T> & lhs, const optional<U> & rhs)
		{
			/*
			 * match (lhs.has_value(), rhs.has_value()) {
			 *     case true, true:
			 *         lhs <= rhs
			 *     case true, false:
			 *         false
			 *     case false, true:
			 *         true
			 *     case false, false:
			 *         true
			 * }
			 */
			return (lhs.has_value() && rhs.has_value()) ?
				   (lhs.ignored_get() <= rhs.ignored_get()) :
				   !lhs.has_value();
		}

		template <typename T, typename U>
		KERBAL_CONSTEXPR
		bool operator>(const optional<T> & lhs, const optional<U> & rhs)
		{
			/*
			 * match (lhs.has_value(), rhs.has_value()) {
			 *     case true, true:
			 *         lhs > rhs
			 *     case true, false:
			 *         true
			 *     case false, true:
			 *         false
			 *     case false, false:
			 *         false
			 * }
			 */
			return (lhs.has_value() && rhs.has_value()) ?
				   (lhs.ignored_get() > rhs.ignored_get()) :
				   lhs.has_value();
		}

		template <typename T, typename U>
		KERBAL_CONSTEXPR
		bool operator>=(const optional<T> & lhs, const optional<U> & rhs)
		{
			/*
			 * match (lhs.has_value(), rhs.has_value()) {
			 *     case true, true:
			 *         lhs >= rhs
			 *     case true, false:
			 *         true
			 *     case false, true:
			 *         false
			 *     case false, false:
			 *         true
			 * }
			 */
			return (lhs.has_value() && rhs.has_value()) ?
				   (lhs.ignored_get() >= rhs.ignored_get()) :
				   !rhs.has_value();
		}
		/**
		 * @}
		 */


		/**
		 * @defgroup optional_compare
		 * Compare with kerbal::optional::nullopt
		 * @{
		 */
		template <typename T>
		KERBAL_CONSTEXPR
		bool operator==(const optional<T> & opt, const nullopt_t &) KERBAL_NOEXCEPT
		{
			return !opt.has_value();
		}

		template <typename T>
		KERBAL_CONSTEXPR
		bool operator!=(const optional<T> & opt, const nullopt_t &) KERBAL_NOEXCEPT
		{
			return opt.has_value();
		}

		template <typename T>
		KERBAL_CONSTEXPR
		bool operator<(const optional<T> &, const nullopt_t &) KERBAL_NOEXCEPT
		{
//			return opt.has_value() < false;
			return false;
		}

		template <typename T>
		KERBAL_CONSTEXPR
		bool operator<=(const optional<T> & opt, const nullopt_t &) KERBAL_NOEXCEPT
		{
//			return opt.has_value() <= false;
			return !opt.has_value();
		}

		template <typename T>
		KERBAL_CONSTEXPR
		bool operator>(const optional<T> & opt, const nullopt_t &) KERBAL_NOEXCEPT
		{
//			return opt.has_value() > false;
			return opt.has_value();
		}

		template <typename T>
		KERBAL_CONSTEXPR
		bool operator>=(const optional<T> & /*opt*/, const nullopt_t &) KERBAL_NOEXCEPT
		{
//			return opt.has_value() >= false;
			return true;
		}



		template <typename T>
		KERBAL_CONSTEXPR
		bool operator==(const nullopt_t &, const optional<T> & opt) KERBAL_NOEXCEPT
		{
			return !opt.has_value();
		}

		template <typename T>
		KERBAL_CONSTEXPR
		bool operator!=(const nullopt_t &, const optional<T> & opt) KERBAL_NOEXCEPT
		{
			return opt.has_value();
		}

		template <typename T>
		KERBAL_CONSTEXPR
		bool operator<(const nullopt_t &, const optional<T> & opt)
		{
//			return false < opt.has_value();
			return opt.has_value();
		}

		template <typename T>
		KERBAL_CONSTEXPR
		bool operator<=(const nullopt_t &, const optional<T> & opt)
		{
//			return false < opt.has_value();
			return true;
		}

		template <typename T>
		KERBAL_CONSTEXPR
		bool operator>(const nullopt_t &, const optional<T> & opt)
		{
//			return false > opt.has_value();
			return false;
		}

		template <typename T>
		KERBAL_CONSTEXPR
		bool operator>=(const nullopt_t & nullopt, const optional<T> & opt)
		{
//			return false >= opt.has_value();
			return !opt.has_value();
		}

		/**
		 * @}
		 */

		/**
		 * @addtogroup optional_compare
		 * Compare with value type
		 * @{
		 */
		template <typename T, typename U>
		KERBAL_CONSTEXPR
		bool operator==(const optional<T> & opt, const U & value)
		{
			/*
			 * if opt.has_value()
			 *     *opt == value
			 * else
			 *     false == true => false
			 */
			return opt.has_value() && (opt.ignored_get() == value);
		}

		template <typename T, typename U>
		KERBAL_CONSTEXPR
		bool operator!=(const optional<T> & opt, const U & value)
		{
			/*
			 * if opt.has_value()
			 *     *opt != value
			 * else
			 *     false != true => true
			 */
			return !opt.has_value() || (opt.ignored_get() != value);
		}

		template <typename T, typename U>
		KERBAL_CONSTEXPR
		bool operator<(const optional<T> & opt, const U & value)
		{
			/*
			 * if opt.has_value()
			 *     *opt < value
			 * else
			 *     false < true => true
			 */
			return !opt.has_value() || (opt.ignored_get() < value);
		}

		template <typename T, typename U>
		KERBAL_CONSTEXPR
		bool operator<=(const optional<T> & opt, const U & value)
		{
			/*
			 * if opt.has_value()
			 *     *opt <= value
			 * else
			 *     false <= true => true
			 */
			return !opt.has_value() || (opt.ignored_get() <= value);
		}

		template <typename T, typename U>
		KERBAL_CONSTEXPR
		bool operator>(const optional<T> & opt, const U & value)
		{
			/*
			 * if opt.has_value()
			 *     *opt > value
			 * else
			 *     false > true => false
			 */
			return opt.has_value() && (opt.ignored_get() > value);
		}

		template <typename T, typename U>
		KERBAL_CONSTEXPR
		bool operator>=(const optional<T> & opt, const U & value)
		{
			/*
			 * if opt.has_value()
			 *     *opt >= value
			 * else
			 *     false >= true => false
			 */
			return opt.has_value() && (opt.ignored_get() >= value);
		}


		template <typename U, typename T>
		KERBAL_CONSTEXPR
		bool operator==(const U & value, const optional<T> & opt)
		{
			/*
			 * if opt.has_value()
			 *     value == *opt
			 * else
			 *     true == false => false
			 */
			return opt.has_value() && (value == opt.ignored_get());
		}

		template <typename U, typename T>
		KERBAL_CONSTEXPR
		bool operator!=(const U & value, const optional<T> & opt)
		{
			/*
			 * if opt.has_value()
			 *     value != *opt
			 * else
			 *     true != false => true
			 */
			return !opt.has_value() || (value != opt.ignored_get());
		}

		template <typename U, typename T>
		KERBAL_CONSTEXPR
		bool operator<(const U & value, const optional<T> & opt)
		{
			/*
			 * if opt.has_value()
			 *     value < *opt
			 * else
			 *     true < false => false
			 */
			return opt.has_value() && (value < opt.ignored_get());
		}

		template <typename U, typename T>
		KERBAL_CONSTEXPR
		bool operator<=(const U & value, const optional<T> & opt)
		{
			/*
			 * if opt.has_value()
			 *     value <= *opt
			 * else
			 *     true <= false => false
			 */
			return opt.has_value() && (value <= opt.ignored_get());
		}

		template <typename U, typename T>
		KERBAL_CONSTEXPR
		bool operator>(const U & value, const optional<T> & opt)
		{
			/*
			 * if opt.has_value()
			 *     value > *opt
			 * else
			 *     true > false => true
			 */
			return !opt.has_value() || (value > opt.ignored_get());
		}

		template <typename U, typename T>
		KERBAL_CONSTEXPR
		bool operator>=(const U & value, const optional<T> & opt)
		{
			/*
			 * if opt.has_value()
			 *     value >= *opt
			 * else
			 *     true >= false => true
			 */
			return !opt.has_value() || (value >= opt.ignored_get());
		}
		/**
		 * @}
		 */

	} // namespace optional

} // namespace kerbal

#endif // KERBAL_OPTIONAL_DETAIL_OPTIONAL_COMPARE_HPP
