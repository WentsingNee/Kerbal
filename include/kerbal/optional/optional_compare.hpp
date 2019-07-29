/**
 * @file       optional_compare.hpp
 * @brief      
 * @date       2019年5月14日
 * @author     peter
 * @copyright
 *      peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */
#ifndef INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_OPTIONAL_COMPARE_HPP_
#define INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_OPTIONAL_COMPARE_HPP_

#include <kerbal/data_struct/optional/optional.hpp>

namespace kerbal
{
	namespace data_struct
	{

		/**
		 * @defgroup optional_compare
		 * Compare with kerbal::data_struct::optional
		 * @{
		 */
		template <typename Tp, typename Up>
		bool operator==(const optional<Tp> & lhs, const optional<Up> & rhs)
		{
			return (bool(lhs) && bool(rhs)) ?
					(lhs.ignored_get() == rhs.ignored_get()) :
					bool(lhs) == bool(rhs);
		}

		template <typename Tp, typename Up>
		bool operator<(const optional<Tp> & lhs, const optional<Up> & rhs)
		{
			return (bool(lhs) && bool(rhs)) ?
					(lhs.ignored_get() < rhs.ignored_get()) :
					(!bool(lhs) && bool(rhs) ? true : false);
		}

		template <typename Tp, typename Up>
		bool operator!=(const optional<Tp> & lhs, const optional<Up> & rhs)
		{
			return !(lhs == rhs);
		}

		template <typename Tp, typename Up>
		bool operator<=(const optional<Tp> & lhs, const optional<Up> & rhs)
		{
			return !(rhs < lhs);
		}

		template <typename Tp, typename Up>
		bool operator>(const optional<Tp> & lhs, const optional<Up> & rhs)
		{
			return rhs < lhs;
		}

		template <typename Tp, typename Up>
		bool operator>=(const optional<Tp> & lhs, const optional<Up> & rhs)
		{
			return !(lhs < rhs);
		}
		/**
		 * @}
		 */


		/**
		 * @defgroup optional_compare
		 * Compare with std::nullopt, kerbal::data_struct::nullopt
		 * @{
		 */
		template <typename Tp, typename NulloptType>
		typename kerbal::type_traits::enable_if<is_nullopt<NulloptType>::value, bool>::type
		operator==(const optional<Tp> & opt, const NulloptType &)
		{
			return bool(opt) == false;
		}

		template <typename Tp, typename NulloptType>
		KERBAL_CONSTEXPR
		typename kerbal::type_traits::enable_if<is_nullopt<NulloptType>::value, bool>::type
		operator<(const optional<Tp> &, const NulloptType &)
		{
			return false;
		}

		template <typename Tp, typename NulloptType>
		typename kerbal::type_traits::enable_if<is_nullopt<NulloptType>::value, bool>::type
		operator!=(const optional<Tp> & opt, const NulloptType & nullopt)
		{
			return !(opt == nullopt);
		}

		template <typename Tp, typename NulloptType>
		typename kerbal::type_traits::enable_if<is_nullopt<NulloptType>::value, bool>::type
		operator<=(const optional<Tp> & opt, const NulloptType & /*nullopt*/)
		{
//			return opt < nullopt || opt == nullopt;
			return !(bool(opt));
		}

		template <typename Tp, typename NulloptType>
		typename kerbal::type_traits::enable_if<is_nullopt<NulloptType>::value, bool>::type
		operator>(const optional<Tp> & opt, const NulloptType & /*nullopt*/)
		{
//			return !(opt <= nullopt);
			return bool(opt);
		}

		template <typename Tp, typename NulloptType>
		KERBAL_CONSTEXPR
		typename kerbal::type_traits::enable_if<is_nullopt<NulloptType>::value, bool>::type
		operator>=(const optional<Tp> & /*opt*/, const NulloptType & /*nullopt*/)
		{
//			return !(opt < nullopt);
			return true;
		}

		template <typename Tp, typename NulloptType>
		typename kerbal::type_traits::enable_if<is_nullopt<NulloptType>::value, bool>::type
		operator==(const NulloptType & nullopt, const optional<Tp> & opt)
		{
			return opt == nullopt;
		}

		template <typename Tp, typename NulloptType>
		typename kerbal::type_traits::enable_if<is_nullopt<NulloptType>::value, bool>::type
		operator<(const NulloptType & nullopt, const optional<Tp> & opt)
		{
			return opt > nullopt;
		}

		template <typename Tp, typename NulloptType>
		typename kerbal::type_traits::enable_if<is_nullopt<NulloptType>::value, bool>::type
		operator!=(const NulloptType & nullopt, const optional<Tp> & opt)
		{
			return !(opt == nullopt);
		}

		template <typename Tp, typename NulloptType>
		KERBAL_CONSTEXPR
		typename kerbal::type_traits::enable_if<is_nullopt<NulloptType>::value, bool>::type
		operator<=(const NulloptType & nullopt, const optional<Tp> & opt)
		{
//			return !(opt < nullopt);
			return true;
		}

		template <typename Tp, typename NulloptType>
		KERBAL_CONSTEXPR
		typename kerbal::type_traits::enable_if<is_nullopt<NulloptType>::value, bool>::type
		operator>(const NulloptType & nullopt, const optional<Tp> & opt)
		{
//			return opt < nullopt;
			return false;
		}

		template <typename Tp, typename NulloptType>
		typename kerbal::type_traits::enable_if<is_nullopt<NulloptType>::value, bool>::type
		operator>=(const NulloptType & nullopt, const optional<Tp> & opt)
		{
			return !(opt > nullopt);
		}

		/**
		 * @}
		 */

		/**
		 * @addtogroup optional_compare
		 * Compare with value type
		 * @{
		 */
		template <typename Tp, typename Up>
		typename kerbal::type_traits::enable_if<!is_optional<Up>::value && !is_nullopt<Up>::value, bool>::type
		operator==(const optional<Tp> & opt, const Up & value)
		{
			return (bool(opt)) ?
					(opt.ignored_get() == value) :
					false;
		}

		template <typename Tp, typename Up>
		typename kerbal::type_traits::enable_if<!is_optional<Up>::value && !is_nullopt<Up>::value, bool>::type
		operator<(const optional<Tp> & opt, const Up & value)
		{
			return (bool(opt)) ?
					(opt.ignored_get() < value) :
					true;
		}

		template <typename Tp, typename Up>
		typename kerbal::type_traits::enable_if<!is_optional<Up>::value && !is_nullopt<Up>::value, bool>::type
		operator!=(const optional<Tp> & opt, const Up & value)
		{
			return !(opt == value);
		}

		template <typename Tp, typename Up>
		typename kerbal::type_traits::enable_if<!is_optional<Up>::value && !is_nullopt<Up>::value, bool>::type
		operator<=(const optional<Tp> & opt, const Up & value)
		{
			return (opt < value || opt == value);
		}

		template <typename Tp, typename Up>
		typename kerbal::type_traits::enable_if<!is_optional<Up>::value && !is_nullopt<Up>::value, bool>::type
		operator>(const optional<Tp> & opt, const Up & value)
		{
			return !(opt <= value);
		}

		template <typename Tp, typename Up>
		typename kerbal::type_traits::enable_if<!is_optional<Up>::value && !is_nullopt<Up>::value, bool>::type
		operator>=(const optional<Tp> & opt, const Up & value)
		{
			return !(opt < value);
		}


		template <typename Up, typename Tp>
		typename kerbal::type_traits::enable_if<!is_optional<Up>::value && !is_nullopt<Up>::value, bool>::type
		operator==(const Up & value, const optional<Tp> & opt)
		{
			return opt == value;
		}

		template <typename Up, typename Tp>
		typename kerbal::type_traits::enable_if<!is_optional<Up>::value && !is_nullopt<Up>::value, bool>::type
		operator<(const Up & value, const optional<Tp> & opt)
		{
			return opt > value;
		}

		template <typename Up, typename Tp>
		typename kerbal::type_traits::enable_if<!is_optional<Up>::value && !is_nullopt<Up>::value, bool>::type
		operator!=(const Up & value, const optional<Tp> & opt)
		{
			return opt != value;
		}

		template <typename Up, typename Tp>
		typename kerbal::type_traits::enable_if<!is_optional<Up>::value && !is_nullopt<Up>::value, bool>::type
		operator<=(const Up & value, const optional<Tp> & opt)
		{
			return opt >= value;
		}

		template <typename Up, typename Tp>
		typename kerbal::type_traits::enable_if<!is_optional<Up>::value && !is_nullopt<Up>::value, bool>::type
		operator>(const Up & value, const optional<Tp> & opt)
		{
			return opt < value;
		}

		template <typename Up, typename Tp>
		typename kerbal::type_traits::enable_if<!is_optional<Up>::value && !is_nullopt<Up>::value, bool>::type
		operator>=(const Up & value, const optional<Tp> & opt)
		{
			return opt <= value;
		}
		/**
		 * @}
		 */

	} /* namespace data_struct */

} /* namespace kerbal */



#endif /* INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_OPTIONAL_COMPARE_HPP_ */
