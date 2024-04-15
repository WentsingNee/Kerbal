/**
 * @file       big_integer.decl.hpp
 * @brief
 * @date       2024-04-15
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_BIG_BIG_INTEGER_BIG_INTEGER_DECL_HPP
#define KERBAL_BIG_BIG_INTEGER_BIG_INTEGER_DECL_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/container/vector.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_same.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>

#include <kerbal/container/vector/vector.decl.hpp>

#include <string>

#include <climits>
#include <cstddef>


namespace kerbal
{

	namespace big
	{

		namespace detail
		{

			struct empty_init_t
			{
			};

			template <std::size_t Size>
			struct big_integer_unit_traits;

			template <>
			struct big_integer_unit_traits<32>
			{
					typedef kerbal::type_traits::integral_constant<std::size_t, 4> DIGITS;
					typedef kerbal::type_traits::integral_constant<std::size_t, 9999> MAX;
					typedef kerbal::type_traits::integral_constant<std::size_t, 10000> MOD;
			};

			template <>
			struct big_integer_unit_traits<64>
			{
					typedef kerbal::type_traits::integral_constant<std::size_t, 9> DIGITS;
					typedef kerbal::type_traits::integral_constant<std::size_t, 999999999> MAX;
					typedef kerbal::type_traits::integral_constant<std::size_t, 1000000000> MOD;
			};

		} // namespace detail


		template <typename Unit, typename Container>
		class basic_big_integer
		{
			private:
				KERBAL_STATIC_ASSERT(kerbal::type_traits::is_unsigned<Unit>::value, "`Unit` should be unsigned type");
				KERBAL_STATIC_ASSERT((kerbal::type_traits::is_same<typename Container::value_type, Unit>::value), "Container should contains `Unit` type");

				typedef kerbal::big::detail::big_integer_unit_traits<sizeof(Unit) * CHAR_BIT> unit_traits;
				typedef typename unit_traits::DIGITS DIGITS;
				typedef typename unit_traits::MAX MAX;
				typedef typename unit_traits::MOD MOD;
				typedef typename Container::iterator data_iterator;
				typedef typename Container::const_iterator data_const_iterator;

				typedef Unit value_type;

			private:
				Container k_data;

			private:
				basic_big_integer(kerbal::big::detail::empty_init_t)
				{
				}

			public:
				basic_big_integer() :
						k_data(1, 0u)
				{
				}

				basic_big_integer(const std::string & src)
				{
					if (src.empty()) {
						throw 0;
					}

					std::size_t groups = src.size() / DIGITS::value;
					std::size_t base = src.size();
					for (std::size_t gid = 0; gid != groups; ++gid) {
						value_type unit = 0;
						base -= DIGITS::value;
						for (std::size_t i = 0; i < DIGITS::value; ++i) {
							unit *= 10;
							unit += src[base + i] - '0';
						}
						this->k_data.push_back(unit);
					}
					if (base != 0) {
						value_type unit = 0;
						for (std::size_t i = 0; i < base; ++i) {
							unit *= 10;
							unit += src[i] - '0';
						}
						this->k_data.push_back(unit);
					}
				}

			private:
				static
				void k_absolute_add_impl(basic_big_integer & out, const basic_big_integer & sht, const basic_big_integer & lng)
				{
					data_const_iterator sht_beg = sht.k_data.cbegin();
					data_const_iterator sht_end = sht.k_data.cend();
					data_const_iterator lng_beg = lng.k_data.cbegin();
					data_const_iterator lng_end = lng.k_data.cend();
					bool carry = false;

					while (sht_beg != sht_end) {
						value_type result = *sht_beg + *lng_beg + carry;
						if (result > MAX::value) {
							carry = true;
							result -= MOD::value;
						}
						out.k_data.push_back(result);
						++sht_beg;
						++lng_beg;
					}
					while (lng_beg != lng_end) {
						value_type result = *lng_beg + carry;
						if (result > MAX::value) {
							carry = true;
							result -= MOD::value;
						}
						out.k_data.push_back(result);
						++lng_beg;
					}
					if (carry) {
						out.k_data.push_back(1u);
					}
				}

			public:
				static
				basic_big_integer
				absolute_add(const basic_big_integer & lhs, const basic_big_integer & rhs)
				{
					basic_big_integer ret((kerbal::big::detail::empty_init_t()));
					if (lhs.k_data.size() < rhs.k_data.size()) {
						k_absolute_add_impl(ret, lhs, rhs);
					} else {
						k_absolute_add_impl(ret, rhs, lhs);
					}
					return ret;
				}

				std::string to_string() const
				{
					typedef typename Container::const_reverse_iterator data_const_reverse_iterator;

					std::string ret;

					data_const_reverse_iterator rbeg = this->k_data.crbegin();
					ret += std::to_string(*rbeg);
					++rbeg;
					data_const_reverse_iterator rend = this->k_data.crend();
					while (rbeg != rend) {
						value_type d = *rbeg;
						char group[DIGITS::value + 1] = {};
						for (std::size_t i = 0; i < DIGITS::value; ++i) {
							group[DIGITS::value - 1 - i] = d % 10 + '0';
							d /= 10;
						}
						ret += group;
						++rbeg;
					}
					return ret;
				}
		};

	} // namespace big

} // namespace kerbal

#endif // KERBAL_BIG_BIG_INTEGER_BIG_INTEGER_DECL_HPP
