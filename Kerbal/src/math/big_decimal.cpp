/*
 * big_decimal.hpp
 *
 *  Created on: 2017年11月21日
 *      Author: Peter
 */

/*
#include <kerbal/math/big_decimal.hpp>
#include <cstring>
#include <cctype>

namespace kerbal
{
	namespace math
	{
		namespace big_decimal
		{

			Big_decimal::Big_decimal() :
					p(), sign(positive)
			{
				p.push_back('0');
			}

			namespace
			{
				void from_str(const char * src, Big_decimal::data_t & p, Big_decimal::sign_t & sign)
				{
					const char * it = src;

					for (; !isspace(*it) && *it; ++it) {
						if (isdigit(*it)) {
							p.push_back(*it);
						}
					}
				}
			}

			Big_decimal::Big_decimal(const std::string & src) :
					p(src.begin(), src.end()), sign(positive)
			{
				from_str(src.c_str(), p, sign);
			}

			Big_decimal::Big_decimal(const char * src) :
					p(), sign(positive)
			{
				from_str(src, p, sign);
			}

			const Big_decimal Big_decimal::operator+() const
			{
				return *this;
			}

			const Big_decimal Big_decimal::operator-() const
			{
				Big_decimal result(*this);
				switch (this->sign) {
					case positive:
						result.sign = negative;
						break;
					case negative:
						result.sign = positive;
						break;
				}
				return result;
			}

			const Big_decimal Big_decimal::abs_add(const Big_decimal & A, const Big_decimal & B)
			{
				Big_decimal result;
				result.p.resize(std::max(A.p.size(), B.p.size()));
				int jin = 0; //进位
				data_t::const_reverse_iterator i = A.p.rbegin(), j = B.p.rbegin();
				data_t::reverse_iterator k = result.p.rbegin();
				data_t::const_reverse_iterator end_a = A.p.rend(), end_b = B.p.rend();
				for (; i != end_a && j != end_b; ++i, ++j, ++k) {
					int bit = (*i - '0') + (*j - '0') + jin;
					jin = bit / 10;
					*k = bit % 10 + '0';
				}
				for (; j != end_b; ++j, ++k) {
					int bit = (*j - '0') + jin;
					jin = bit / 10;
					*k = bit % 10 + '0';
				}
				for (; i != end_a; ++i, ++k) {
					int bit = (*i - '0') + jin;
					jin = bit / 10;
					*k = bit % 10 + '0';
				}

				if (jin != 0) {
					result.p.push_front(jin + '0');
				}
				return result;
			}

			const Big_decimal operator+(const Big_decimal & A, const Big_decimal & B)
			{
				if (A.sign == B.sign) { //all positive or all negative
					Big_decimal result = Big_decimal::abs_add(A, B);
					if (A.sign == Big_decimal::negative) { //all negative
						result.sign = Big_decimal::negative;
					}
					return result;
				}

			}

			bool Big_decimal::abs_equal(const Big_decimal & A, const Big_decimal & B)
			{
				if (A.p.size() == B.p.size()) {
					data_t::const_iterator i = A.p.begin();
					data_t::const_iterator j = B.p.begin();
					data_t::const_iterator end = A.p.end();
					for (; i != end; ++i, ++j) {
						if (*i != *j) {
							return false;
						}
					}
					return true;
				}
				return false;
			}

			bool operator==(const Big_decimal & A, const Big_decimal & B)
			{
				return (A.sign == B.sign && Big_decimal::abs_equal(A, B));
			}

			bool Big_decimal::is_zero() const
			{
				return (this->p.size() == 1 && this->p.front() == '0');
			}
			bool Big_decimal::is_positive() const
			{
				return this->sign == positive;
			}
			bool Big_decimal::is_negative() const
			{
				return this->sign == negative;
			}
			int Big_decimal::sig() const
			{
				if (this->is_zero()) {
					return 0;
				} else if (this->is_positive()) {
					return 1;
				} else if (this->is_negative()) {
					return -1;
				}
				return 0xffffffff;
			}

			bool Big_decimal::is_inf() const
			{
				return this->p.empty();
			}
			bool Big_decimal::is_positive_inf() const
			{
				return (this->sign == positive && this->is_inf());
			}
			bool Big_decimal::is_negative_inf() const
			{
				return (this->sign == negative && this->is_inf());
			}

			std::ostream& operator<<(std::ostream& out, const Big_decimal & src)
			{
				if (src.sign == Big_decimal::negative) {
					out << '-';
				}

				if (src.is_inf()) {
					out << "inf";
					return out;
				}

				Big_decimal::data_t::const_iterator it = src.p.begin();
				Big_decimal::data_t::const_iterator end = src.p.end();

				for (; it != end; ++it) {
					out << *it;
				}
				return out;
			}

		}  namespace big_integer

	}
}
*/
