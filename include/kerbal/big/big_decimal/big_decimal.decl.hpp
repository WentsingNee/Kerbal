/**
 * @file       big_decimal.decl.hpp
 * @brief
 * @date       2024-04-15
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_BIG_BIG_DECIMAL_BIG_DECIMAL_DECL_HPP
#define KERBAL_BIG_BIG_DECIMAL_BIG_DECIMAL_DECL_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/container/nonmember_container_access.hpp>
#include <kerbal/container/vector.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/type_traits/is_same.hpp>
#include <kerbal/type_traits/sign_deduction.hpp>

#include <kerbal/container/vector/vector.decl.hpp>

#include <string>

#include <climits>
#include <cstddef>

#include <kerbal/debug/debug_ostream.hpp>


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
			struct big_decimal_unit_traits;

			template <>
			struct big_decimal_unit_traits<32>
			{
					typedef kerbal::type_traits::integral_constant<std::size_t, 4> DIGITS;
					typedef kerbal::type_traits::integral_constant<std::size_t, 9999> MAX;
					typedef kerbal::type_traits::integral_constant<std::size_t, 10000> MOD;
			};

			template <>
			struct big_decimal_unit_traits<64>
			{
					typedef kerbal::type_traits::integral_constant<std::size_t, 9> DIGITS;
					typedef kerbal::type_traits::integral_constant<std::size_t, 999999999> MAX;
					typedef kerbal::type_traits::integral_constant<std::size_t, 1000000000> MOD;
			};

		} // namespace detail


		template <typename Unit, typename Container>
		class basic_big_decimal
		{
			private:
				KERBAL_STATIC_ASSERT(kerbal::type_traits::is_unsigned<Unit>::value, "`Unit` should be unsigned type");
				KERBAL_STATIC_ASSERT((kerbal::type_traits::is_same<typename Container::value_type, Unit>::value), "Container should contains `Unit` type");

				typedef kerbal::big::detail::big_decimal_unit_traits<sizeof(Unit) * CHAR_BIT> unit_traits;
				typedef typename unit_traits::DIGITS DIGITS;
				typedef typename unit_traits::MAX MAX;
				typedef typename unit_traits::MOD MOD;
				typedef typename Container::iterator data_iterator;
				typedef typename Container::const_iterator data_const_iterator;

				typedef Unit value_type;

			private:
				Container k_data;

			private:
				basic_big_decimal(kerbal::big::detail::empty_init_t)
				{
				}

			public:
				basic_big_decimal() :
						k_data(1, 0u)
				{
				}

				basic_big_decimal(int src)
				{
					this->k_data.push_back(src % MOD::value);
					src /= MOD::value;
					while (src != 0) {
						this->k_data.push_back(src % MOD::value);
						src /= MOD::value;
					}
				}

				basic_big_decimal(const std::string & src)
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
				void k_absolute_add_impl(
						basic_big_decimal & out,
						const basic_big_decimal & sht, data_const_iterator sht_beg, data_const_iterator sht_end,
						const basic_big_decimal & lng, data_const_iterator lng_beg, data_const_iterator lng_end
				)
				{
					out.k_data.reserve(lng_end - lng_beg);
					bool carry = false;

					while (sht_beg != sht_end) {
						value_type result = *lng_beg + *sht_beg + carry;
						carry = result > MAX::value;
						if (carry) {
							result -= MOD::value;
						}
						out.k_data.push_back(result);
						++sht_beg;
						++lng_beg;
					}
					while (lng_beg != lng_end) {
						value_type result = *lng_beg + carry;
						carry = result > MAX::value;
						if (carry) {
							result -= MOD::value;
						}
						out.k_data.push_back(result);
						++lng_beg;
					}
					if (carry) {
						out.k_data.push_back(1u);
					}
				}

				static
				void k_absolute_add_impl(basic_big_decimal & out, const basic_big_decimal & sht, const basic_big_decimal & lng)
				{
					data_const_iterator sht_beg = sht.k_data.cbegin();
					data_const_iterator sht_end = sht.k_data.cend();
					data_const_iterator lng_beg = lng.k_data.cbegin();
					data_const_iterator lng_end = lng.k_data.cend();

					k_absolute_add_impl(
							out,
							sht, sht_beg, sht_end,
							lng, lng_beg, lng_end
					);
				}

			public:

				static
				basic_big_decimal
				absolute_add(const basic_big_decimal & lhs, const basic_big_decimal & rhs)
				{
					basic_big_decimal ret((kerbal::big::detail::empty_init_t()));
					if (lhs.k_data.size() < rhs.k_data.size()) {
						k_absolute_add_impl(ret, lhs, rhs);
					} else {
						k_absolute_add_impl(ret, rhs, lhs);
					}
					return ret;
				}

			private:

				static
				void k_absolute_subtract_impl(
						basic_big_decimal & out,
						const basic_big_decimal & lng, data_const_iterator lng_beg, data_const_iterator lng_end,
						const basic_big_decimal & sht, data_const_iterator sht_beg, data_const_iterator sht_end
				)
				{
					bool carry = false;

					while (sht_beg != sht_end) {
						value_type subtract = *sht_beg + carry;
						value_type result = 0;
						carry = subtract > *lng_beg;
						if (carry) {
							result = MOD::value + *lng_beg - subtract;
						} else {
							result = *lng_beg - subtract;
						}
						out.k_data.push_back(result);
						++sht_beg;
						++lng_beg;
					}
					while (lng_beg != lng_end) {
						value_type subtract = carry;
						value_type result = 0;
						carry = subtract > *lng_beg;
						if (carry) {
							result = MOD::value + *lng_beg - subtract;
						} else {
							result = *lng_beg - subtract;
						}
						out.k_data.push_back(result);
						++lng_beg;
					}
					while (out.k_data.size() > 1 && out.k_data.back() == 0) {
						out.k_data.pop_back();
					}
				}

				static
				void k_absolute_subtract_impl(
						basic_big_decimal & out, const basic_big_decimal & lng, const basic_big_decimal & sht)
				{
					data_const_iterator sht_beg = sht.k_data.cbegin();
					data_const_iterator sht_end = sht.k_data.cend();
					data_const_iterator lng_beg = lng.k_data.cbegin();
					data_const_iterator lng_end = lng.k_data.cend();
					k_absolute_subtract_impl(
							out,
							lng, lng_beg, lng_end,
							sht, sht_beg, sht_end
					);
				}

			public:

				static
				basic_big_decimal
				absolute_subtract(const basic_big_decimal & lhs, const basic_big_decimal & rhs)
				{
					basic_big_decimal ret((kerbal::big::detail::empty_init_t()));
					k_absolute_subtract_impl(ret, lhs, rhs);
					return ret;
				}

			private:

				void add_base(std::size_t base)
				{
					this->k_data.insert(this->k_data.cbegin(), base, 0);
				}

				static
				void k_absolute_multiply_impl(
						basic_big_decimal & out,
						const basic_big_decimal & sht, std::size_t sht_beg, std::size_t sht_end,
						const basic_big_decimal & lng, std::size_t lng_beg, std::size_t lng_end
				)
				{
					kerbal::debug::debug_ostream_context ctx(kerbal::debug::dout);

					std::size_t sht_len = sht_end - sht_beg;
					std::size_t base = sht_len / 2;

					if (sht_len == 1) {
						value_type carry = 0;
						value_type rhs = sht.k_data[sht_beg];
						for (std::size_t i = lng_beg; i < lng_end; ++i) {
							value_type lhs = lng.k_data[i];
							value_type result = lhs * rhs + carry;
							carry = result / MOD::value;
							result %= MOD::value;
							out.k_data.push_back(result);
						}
						if (carry) {
							out.k_data.push_back(carry);
						}
//						kerbal::debug::dout << "out: " << out.to_string() << std::endl;
						return;
					}

//					kerbal::debug::dout << sht.to_string(sht_beg, sht_end) << std::endl;
//					kerbal::debug::dout << lng.to_string(lng_beg, lng_end) << std::endl;

					basic_big_decimal high((detail::empty_init_t())); // high = sht_high * lng_high
//					kerbal::debug::dout << "[" << base << ", " << sht_end << ")" << std::endl;
					k_absolute_multiply_impl(
							high,
							sht, sht_beg + base, sht_end,
							lng, lng_beg + base, lng_end
					);
//					kerbal::debug::dout << "high: " << high.to_string() << std::endl;

					basic_big_decimal low((detail::empty_init_t())); // low = sht_low * sht_high
					k_absolute_multiply_impl(
							low,
							sht, sht_beg, sht_beg + base,
							lng, lng_beg, lng_beg + base
					);
//					kerbal::debug::dout << "low: " << low.to_string() << std::endl;

					basic_big_decimal sht_mix((detail::empty_init_t())); // sht_mix = sht_low + sht_high
					data_const_iterator sht_mid(kerbal::container::nth(sht.k_data, sht_beg + base));
					k_absolute_add_impl(
							sht_mix,
							sht, kerbal::container::nth(sht.k_data, sht_beg), sht_mid,
							sht, sht_mid, kerbal::container::nth(sht.k_data, sht_end)
					);
//					kerbal::debug::dout << "sht_mix: " << sht_mix.to_string() << std::endl;

					basic_big_decimal lng_mix((detail::empty_init_t())); // lng_mix = lng_low + lng_high
					data_const_iterator lng_mid(kerbal::container::nth(lng.k_data, lng_beg + base));
					k_absolute_add_impl(
							lng_mix,
							lng, lng.k_data.cbegin() + lng_beg, lng_mid,
							lng, lng_mid, lng.k_data.cbegin() + lng_end
					);

//					kerbal::debug::dout << "lng_mix: " << lng_mix.to_string() << std::endl;

					basic_big_decimal mid1 = absolute_multiply(sht_mix, lng_mix);
//					kerbal::debug::dout << "mid1: " << mid1.to_string() << std::endl;

					basic_big_decimal mid2((detail::empty_init_t()));
//					kerbal::debug::dout << mid1.to_string() << " - " << high.to_string() << std::endl;
					k_absolute_subtract_impl(mid2, mid1, high);

					basic_big_decimal mid3((detail::empty_init_t()));
					k_absolute_subtract_impl(mid3, mid2, low);
//					kerbal::debug::dout << "mid: " << mid3.to_string() << std::endl;

					high.add_base(2 * base);
					mid3.add_base(base);

					basic_big_decimal ret1((detail::empty_init_t()));
					k_absolute_add_impl(ret1, low, mid3);

//					k_absolute_add_impl(out, ret1, high);
					out = absolute_add(ret1, high);
//					kerbal::debug::dout << "out: " << out.to_string() << std::endl;

				}

			public:

				static
				basic_big_decimal
				absolute_multiply(const basic_big_decimal & lhs, const basic_big_decimal & rhs)
				{
					basic_big_decimal ret((kerbal::big::detail::empty_init_t()));
					if (lhs.k_data.size() < rhs.k_data.size()) {
						k_absolute_multiply_impl(
								ret,
								lhs, 0, lhs.k_data.size(),
								rhs, 0, rhs.k_data.size()
						);
					} else {
						k_absolute_multiply_impl(
								ret,
								rhs, 0, rhs.k_data.size(),
								lhs, 0, lhs.k_data.size()
						);
					}
					return ret;
				}

				std::string to_string(std::size_t beg, std::size_t end) const
				{
					typedef typename Container::const_reverse_iterator data_const_reverse_iterator;

					std::string ret;

					data_const_reverse_iterator rbeg(this->k_data.cbegin() + end);
					ret += std::to_string(*rbeg);
					++rbeg;
					data_const_reverse_iterator rend(this->k_data.cbegin() + beg);
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

#endif // KERBAL_BIG_BIG_DECIMAL_BIG_DECIMAL_DECL_HPP
