/**
 * @file		VarBigint.hpp
 * @brief
 * @date		2018年7月22日
 * @author		Peter
 * @copyright	Peter
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 */

#ifndef INCLUDE_KERBAL_MATH_VARBIGINT_HPP_
#define INCLUDE_KERBAL_MATH_VARBIGINT_HPP_

#include <iostream>
#include <deque>
#include <cstring>
#include <iomanip>
#include <iterator>

namespace kerbal
{

	namespace math
	{

		template <typename IsSigned>
		class VarBigInt;

		template <>
		class VarBigInt<unsigned>
		{
			protected:
				enum
				{
					max_limit = 10000, dlen = 4
				};

				struct Ignore
				{
				} static const ignore;

				typedef std::deque<unsigned int> container;

				container data;

			public:
				VarBigInt(Ignore) :
						data()
				{
				}

				VarBigInt(unsigned int src = 0)
				{
					while (src >= max_limit) {
						data.push_back(src % max_limit);
						src /= max_limit;
					}
					data.push_back(src);
				}

				VarBigInt(const char * src)
				{
					size_t L = strlen(src);

					typedef const char * const_iterator;
					const_iterator i = src + L - 1;
					for (; i != src + L % dlen - 1;) {
						unsigned int t = 0;
						for (unsigned int weight = 1; weight < max_limit; weight *= 10) {
							t += (*i - '0') * weight;
							--i;
						}
						data.push_back(t);
					}
					unsigned int t = 0;
					for (unsigned int weight = 1; i >= src; weight *= 10) {
						t += (*i - '0') * weight;
						--i;
					}
					if (t != 0 || this->data.empty()) {
						data.push_back(t);
					}
				}

				VarBigInt(const std::string & src)
				{
					std::string::const_reverse_iterator i = src.rbegin();
					std::string::const_reverse_iterator iend = src.rend();
					std::advance(iend, -(signed) (src.length() % dlen));
					for (; i != iend;) {
						unsigned int t = 0;
						for (unsigned int weight = 1; weight < max_limit; weight *= 10) {
							t += (*i - '0') * weight;
							++i;
						}
						data.push_back(t);
					}
					unsigned int t = 0;
					for (unsigned int weight = 1; i != src.rend(); weight *= 10) {
						t += (*i - '0') * weight;
						++i;
					}
					if (t != 0 || this->data.empty()) {
						data.push_back(t);
					}
				}

				VarBigInt(const VarBigInt & src) : data(src.data)
				{
				}

				VarBigInt & operator=(const VarBigInt & src)
				{
					data = src.data;
					return *this;
				}

# 			if __cplusplus >= 201103L

				VarBigInt(VarBigInt && src) : data(std::move(src.data))
				{
				}

				VarBigInt & operator=(VarBigInt && src)
				{
					data = std::move(src.data);
					return *this;
				}

#			endif

				VarBigInt operator+(const VarBigInt & with) const
				{
					VarBigInt ret(ignore);

					unsigned int up = 0;
					container::const_iterator i = this->data.begin(), j = with.data.begin();
					for (; i != this->data.end() && j != with.data.end(); ++i, ++j) {
						up += *i + *j;
						ret.data.push_back(up % max_limit);
						up /= max_limit;
					}
					bool flag = (i == this->data.end());
					const VarBigInt & Long = flag ? with : *this;
					container::const_iterator & Lit = flag ? j : i;
					for (; Lit != Long.data.end(); ++Lit) {
						up += *Lit;
						ret.data.push_back(up % max_limit);
						up /= max_limit;
					}
					if (up != 0) {
						ret.data.push_back(up);
					}
					return ret;
				}

				VarBigInt & operator+=(const VarBigInt & with)
				{
					unsigned int up = 0;
					container::iterator i = this->data.begin();
					container::const_iterator j = with.data.begin();
					for (; i != this->data.end() && j != with.data.end(); ++i, ++j) {
						up += *i + *j;
						*i = up % max_limit;
						up /= max_limit;
					}

					if (i == this->data.end()) {
						for (; j != with.data.end(); ++j) {
							up += *j;
							this->data.push_back(up % max_limit);
							up /= max_limit;
						}
					} else {
						for (; up != 0 && i != this->data.end(); ++i) {
							up += *i;
							*i = up % max_limit;
							up /= max_limit;
						}
					}
					if (up != 0) {
						this->data.push_back(up);
					}
					return *this;
				}

				VarBigInt & operator++()
				{
					unsigned int up = 1;
					container::iterator i = this->data.begin();

					for (; up != 0 && i != this->data.end(); ++i) {
						up += *i;
						*i = up % max_limit;
						up /= max_limit;
					}
					if (up != 0) {
						this->data.push_back(up);
					}
					return *this;
				}

				VarBigInt operator-(const VarBigInt & with) const
				{
					bool flag = (with < *this);
					const VarBigInt & a = flag ? *this : with;
					const VarBigInt & b = flag ? with : *this; // a - b;

					VarBigInt ret(ignore);

					container::const_iterator i = a.data.begin(), j = b.data.begin();
					unsigned int down = 0;
					for (; j != b.data.end(); ++i, ++j) {
						if (*i < *j + down) {
							ret.data.push_back(*i + max_limit - *j - down);
							down = 1;
						} else {
							ret.data.push_back(*i - *j - down);
							down = 0;
						}
					}
					for (; i != a.data.end(); ++i) {
						if (*i < down) {
							ret.data.push_back(*i + max_limit - down);
							down = 1;
						} else {
							ret.data.push_back(*i - down);
							down = 0;
						}
					}
					return ret;
				}

				VarBigInt operator*(const VarBigInt & with) const
				{
					VarBigInt ret(ignore);

					container::const_iterator j = with.data.begin();
					container::size_type rb = 0;
					for (; j != with.data.end(); ++j, ++rb) {
						unsigned int up = 0;
						container::const_iterator i = this->data.begin();
						container::iterator r = ret.data.begin() + rb;
						for (; i != this->data.end() && r != ret.data.end(); ++i, ++r) {
							up += *i * *j + *r;
							*r = up % max_limit;
							up /= max_limit;
						}

						for (; i != this->data.end(); ++i) {
							up += *i * *j;
							ret.data.push_back(up % max_limit);
							up /= max_limit;
						}

						if (up != 0) {
							ret.data.push_back(up);
						}
					}

					return ret;
				}

				VarBigInt operator/(unsigned int with) const
				{
					VarBigInt ret(ignore);
					unsigned int down = 0;
					for (container::const_reverse_iterator i = this->data.rbegin();
						 i != this->data.rend(); ++i) {
						unsigned int t = *i + down * max_limit;
						ret.data.push_front(t / with);
						down = t % with;
					}
					while (ret.data.back() == 0) {
						ret.data.pop_back();
					}
					return ret;
				}

				unsigned int operator%(unsigned int with) const
				{
					unsigned int ret = 0;
					for (container::const_reverse_iterator i = this->data.rbegin();
						 i != this->data.rend(); ++i) {
						ret = ((ret * max_limit) % with + *i) % with;
					}
					return ret;
				}

				VarBigInt operator^(unsigned int m) const
				{
					if (m == 0) {
						return 1;
					}
					if (m == 1) {
						return *this;
					}
					VarBigInt t, ret(1);
					while (m > 1) {
						t = *this;
						unsigned int i = 1;
						for (; (i * 2) <= m; i *= 2)
							t = t * t;
						m -= i;
						ret = ret * t;
						if (m == 1) {
							ret = ret * (*this);
						}
					}
					return ret;
				}

				bool operator<(const VarBigInt & with) const
				{
					size_t x = this->data.size(), y = with.data.size();
					if (x < y) {
						return true;
					} else if (x > y) {
						return false;
					} else {
						for (container::const_reverse_iterator i = this->data.rbegin(), j =
								with.data.rbegin(); i != this->data.rend(); ++i, ++j) {
							if (*i < *j) {
								return true;
							} else if (*i > *j) {
								return false;
							}
						}
						return false;
					}
				}

				bool operator>(const VarBigInt & with) const
				{
					size_t x = this->data.size(), y = with.data.size();
					if (x > y) {
						return true;
					} else if (x < y) {
						return false;
					} else {
						for (container::const_reverse_iterator i = this->data.rbegin(), j =
								with.data.rbegin(); i != this->data.rend(); ++i, ++j) {
							if (*i > *j) {
								return true;
							} else if (*i < *j) {
								return false;
							}
						}
						return false;
					}
				}

				bool operator==(const VarBigInt & with) const
				{
					return this->data == with.data;
				}

				bool operator<=(const VarBigInt & with) const
				{
					return !(this->data > with.data);
				}

				bool operator>=(const VarBigInt & with) const
				{
					return !(this->data < with.data);
				}

				bool operator!=(const VarBigInt & with) const
				{
					return this->data != with.data;
				}

				operator bool() const
				{
					return this->data.front() != 0 || this->data.size() != 1;
				}

				friend std::ostream & operator<<(std::ostream & out, const VarBigInt & src)
				{
					container::const_reverse_iterator it = src.data.rbegin();
					out << *it;
					++it;
					out << std::setfill('0');
					for (; it != src.data.rend(); ++it) {
						out << std::setw(dlen) << *it;
					}
					return out;
				}

				friend std::istream & operator>>(std::istream & in, VarBigInt & to)
				{
					std::string src;
					in >> src;
					to = VarBigInt(src);
					return in;
				}
		};


		template <>
		class VarBigInt<signed> : VarBigInt<unsigned>
		{
			protected:
				typedef VarBigInt<unsigned> abs;
				bool sign;

			public:
				VarBigInt(Ignore) :
						abs(VarBigInt<unsigned>::ignore), sign(false)
				{
				}

				VarBigInt(int src = 0) : abs(src > 0 ? src : -src), sign(src < 0)
				{
				}

				VarBigInt(const char * src)
				{
					size_t L = strlen(src);

					typedef const char * const_iterator;
					const_iterator i = src + L - 1;
					for (; i != src + L % dlen - 1;) {
						unsigned int t = 0;
						for (unsigned int weight = 1; weight < max_limit; weight *= 10) {
							t += (*i - '0') * weight;
							--i;
						}
						data.push_back(t);
					}
					unsigned int t = 0;
					for (unsigned int weight = 1; i >= src; weight *= 10) {
						t += (*i - '0') * weight;
						--i;
					}
					if (t != 0 || this->data.empty()) {
						data.push_back(t);
					}
				}

				VarBigInt(const std::string & src)
				{
					std::string::const_reverse_iterator i = src.rbegin();
					std::string::const_reverse_iterator iend = src.rend();
					std::advance(iend, -(signed) (src.length() % dlen));
					for (; i != iend;) {
						unsigned int t = 0;
						for (unsigned int weight = 1; weight < max_limit; weight *= 10) {
							t += (*i - '0') * weight;
							++i;
						}
						data.push_back(t);
					}
					unsigned int t = 0;
					for (unsigned int weight = 1; i != src.rend(); weight *= 10) {
						t += (*i - '0') * weight;
						++i;
					}
					if (t != 0 || this->data.empty()) {
						data.push_back(t);
					}
				}

				VarBigInt(const VarBigInt<unsigned> & src) : abs(src), sign(false)
				{
				}

				VarBigInt(const VarBigInt & src) : abs(src), sign(src.sign)
				{
				}

				VarBigInt & operator=(const VarBigInt & src)
				{
					abs::operator=(src);
					this->sign = src.sign;
					return *this;
				}

# 			if __cplusplus >= 201103L

				VarBigInt(VarBigInt && src) : abs(std::move(src))
				{
				}

				VarBigInt & operator=(VarBigInt && src)
				{
					abs::operator=(std::move(src));
					this->sign = src.sign;
					return *this;
				}

#			endif

				VarBigInt operator+(const VarBigInt & with) const
				{
					VarBigInt ret(
							this->sign == with.sign ?
							(VarBigInt<unsigned> &) (*this) + (VarBigInt<unsigned> &) (with) :
							(VarBigInt<unsigned> &) (*this) - (VarBigInt<unsigned> &) (with));
					return ret;
				}

				VarBigInt & operator+=(const VarBigInt & with)
				{
					*this = *this + with;
					return *this;
				}

				VarBigInt & operator++()
				{
					unsigned int up = 1;
					container::iterator i = this->data.begin();

					for (; up != 0 && i != this->data.end(); ++i) {
						up += *i;
						*i = up % max_limit;
						up /= max_limit;
					}
					if (up != 0) {
						this->data.push_back(up);
					}
					return *this;
				}

				VarBigInt operator-(const VarBigInt & with) const
				{
					bool flag = (with < *this);
					const VarBigInt & a = flag ? *this : with;
					const VarBigInt & b = flag ? with : *this; // a - b;

					VarBigInt ret(ignore);

					container::const_iterator i = a.data.begin(), j = b.data.begin();
					unsigned int down = 0;
					for (; j != b.data.end(); ++i, ++j) {
						if (*i < *j + down) {
							ret.data.push_back(*i + max_limit - *j - down);
							down = 1;
						} else {
							ret.data.push_back(*i - *j - down);
							down = 0;
						}
					}
					for (; i != a.data.end(); ++i) {
						if (*i < down) {
							ret.data.push_back(*i + max_limit - down);
							down = 1;
						} else {
							ret.data.push_back(*i - down);
							down = 0;
						}
					}
					return ret;
				}

				VarBigInt operator*(const VarBigInt & with) const
				{
					VarBigInt ret(ignore);

					container::const_iterator j = with.data.begin();
					container::size_type rb = 0;
					for (; j != with.data.end(); ++j, ++rb) {
						unsigned int up = 0;
						container::const_iterator i = this->data.begin();
						container::iterator r = ret.data.begin() + rb;
						for (; i != this->data.end() && r != ret.data.end(); ++i, ++r) {
							up += *i * *j + *r;
							*r = up % max_limit;
							up /= max_limit;
						}

						for (; i != this->data.end(); ++i) {
							up += *i * *j;
							ret.data.push_back(up % max_limit);
							up /= max_limit;
						}

						if (up != 0) {
							ret.data.push_back(up);
						}
					}

					return ret;
				}

				VarBigInt operator/(unsigned int with) const
				{
					VarBigInt ret(ignore);
					unsigned int down = 0;
					for (container::const_reverse_iterator i = this->data.rbegin();
						 i != this->data.rend(); ++i) {
						unsigned int t = *i + down * max_limit;
						ret.data.push_front(t / with);
						down = t % with;
					}
					while (ret.data.back() == 0) {
						ret.data.pop_back();
					}
					return ret;
				}

				unsigned int operator%(unsigned int with) const
				{
					unsigned int ret = 0;
					for (container::const_reverse_iterator i = this->data.rbegin();
						 i != this->data.rend(); ++i) {
						ret = ((ret * max_limit) % with + *i) % with;
					}
					return ret;
				}

				VarBigInt operator^(unsigned int m) const
				{
					if (m == 0) {
						return 1;
					}
					if (m == 1) {
						return *this;
					}
					VarBigInt t, ret(1);
					while (m > 1) {
						t = *this;
						unsigned int i = 1;
						for (; (i * 2) <= m; i *= 2)
							t = t * t;
						m -= i;
						ret = ret * t;
						if (m == 1) {
							ret = ret * (*this);
						}
					}
					return ret;
				}

				bool operator<(const VarBigInt & with) const
				{
					size_t x = this->data.size(), y = with.data.size();
					if (x < y) {
						return true;
					} else if (x > y) {
						return false;
					} else {
						for (container::const_reverse_iterator i = this->data.rbegin(), j =
								with.data.rbegin(); i != this->data.rend(); ++i, ++j) {
							if (*i < *j) {
								return true;
							} else if (*i > *j) {
								return false;
							}
						}
						return false;
					}
				}

				bool operator>(const VarBigInt & with) const
				{
					size_t x = this->data.size(), y = with.data.size();
					if (x > y) {
						return true;
					} else if (x < y) {
						return false;
					} else {
						for (container::const_reverse_iterator i = this->data.rbegin(), j =
								with.data.rbegin(); i != this->data.rend(); ++i, ++j) {
							if (*i > *j) {
								return true;
							} else if (*i < *j) {
								return false;
							}
						}
						return false;
					}
				}

				bool operator==(const VarBigInt & with) const
				{
					return this->data == with.data;
				}

				bool operator<=(const VarBigInt & with) const
				{
					return !(this->data > with.data);
				}

				bool operator>=(const VarBigInt & with) const
				{
					return !(this->data < with.data);
				}

				bool operator!=(const VarBigInt & with) const
				{
					return this->data != with.data;
				}

				operator bool() const
				{
					return this->data.front() != 0 || this->data.size() != 1;
				}

				friend std::ostream & operator<<(std::ostream & out, const VarBigInt & src)
				{
					if (src.sign == true) {
						out << '-';
					}
					container::const_reverse_iterator it = src.data.rbegin();
					out << *it;
					++it;
					out << std::setfill('0');
					for (; it != src.data.rend(); ++it) {
						out << std::setw(dlen) << *it;
					}
					return out;
				}

				friend std::istream & operator>>(std::istream & in, VarBigInt & to)
				{
					std::string src;
					in >> src;
					to = VarBigInt(src);
					return in;
				}
		};
	}
}


#endif /* INCLUDE_KERBAL_MATH_VARBIGINT_HPP_ */
