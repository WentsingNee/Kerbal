/**
 * @file       seed_seq.decl.hpp
 * @brief
 * @date       2025-01-09
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_SEED_SEQ_SEED_SEQ_DECL_HPP
#define KERBAL_RANDOM_SEED_SEQ_SEED_SEQ_DECL_HPP

#include <kerbal/random/seed_seq/seed_seq.fwd.hpp>

#include <kerbal/algorithm/modifier/fill.hpp>
#include <kerbal/assign/ilist.hpp>
#include <kerbal/compare/minmax.hpp>
#include <kerbal/compatibility/fixed_width_integer.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/container/vector.hpp>
#include <kerbal/iterator/iterator.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/smath/add_mod_sm.hpp>
#include <kerbal/smath/xmod.hpp>
#include <kerbal/type_traits/integral_constant.hpp>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif


namespace kerbal
{
	namespace random
	{

		class seed_seq
		{
			private:
				typedef std::uint32_t element_type;
				typedef kerbal::container::vector<element_type> seed_vector_type;
				seed_vector_type k_seed;

			public:

#		if __cplusplus >= 201103L
				seed_seq() = default;
#		else

				seed_seq()
				{
				}

#		endif


			private:

				template <typename Integer>
				KERBAL_CONSTEXPR
				static
				element_type
				k_mod_seed(Integer s) KERBAL_NOEXCEPT
				{
					typedef kerbal::smath::xmod<element_type, 0> xmod;
					return xmod::f(s);
				}

				template <typename InputIterator>
				void
				k_constrct_by_range(
					std::input_iterator_tag,
					InputIterator first, InputIterator last
				)
				{
					while (first != last) {
						this->k_seed.push_back(k_mod_seed(*first));
						++first;
					}
				}

				template <typename InputIterator>
				void
				k_constrct_by_range(
					std::random_access_iterator_tag,
					InputIterator first, InputIterator last
				)
				{
					this->k_seed.resize(
						kerbal::iterator::distance(first, last)
					);
					seed_vector_type::size_type i = 0;
					while (first != last) {
						this->k_seed[i] = k_modseed(*first);
						++first;
						++i;
					}
				}

			public:

				template <typename InputIterator>
				seed_seq(InputIterator first, InputIterator last)
				{
					this->k_constrct_by_range(
						kerbal::iterator::iterator_category(first),
						first, last
					);
				}

#		if __cplusplus >= 201103L

				template <typename T>
				seed_seq(std::initializer_list<T> ilist) :
					seed_seq(ilist.begin(), ilist.end())
				{
				}

#		else

				template <typename T>
				seed_seq(kerbal::assign::assign_list<T> const & ilist)
				{
					this->k_constrct_by_range(ilist.cbegin(), ilist.cend());
				}

#		endif

			private:

				template <typename Integer>
				KERBAL_CONSTEXPR
				static
				Integer
				k_generate_T(Integer x) KERBAL_NOEXCEPT
				{
					return x ^ (x >> 27);
				}

			public:

				template <typename RandomAccessIterator>
				void generate(
					RandomAccessIterator first,
					RandomAccessIterator last
				)
				{
					typedef kerbal::iterator::iterator_traits<RandomAccessIterator> iterator_traits;
					typedef typename iterator_traits::difference_type difference_type;
					typedef typename iterator_traits::value_type value_type;

					if (first == last) {
						return;
					}

					kerbal::algorithm::fill(first, last, 0x8b8b8b8b);

					std::size_t z = this->k_seed.size();
					std::size_t n = kerbal::iterator::distance(first, last);
					std::size_t m = kerbal::compare::max(z + 1, n);

					std::size_t t =
						(n >= 623) ? 11 :
						(n >= 68) ? 7 :
						(n >= 39) ? 5 :
						(n >= 7) ? 3 :
						(n - 1) / 2
					;
					std::size_t p = (n - t) / 2;
					std::size_t q = p + t;

					typedef kerbal::smath::xmod<kerbal::compatibility::uint32_t, 0> mod_2_pow_32;
					typedef kerbal::smath::add_mod_sm<kerbal::compatibility::uint32_t, 0> add_mod_2_pow_32;

					for (std::size_t k = 0; k < m; ++k) {
						value_type & s_k = first[k % n];
						value_type & s_kpp = first[(k + p) % n];
						value_type s_km1 = first[(k + n - 1) % n];
						element_type r1 =
							1664525 * k_generate_T(s_k ^ s_kpp ^ s_km1)
						;
						element_type j =
							(k == 0) ? z :
							(k <= z) ? (k % n) + this->k_seed[k - 1] :
							(k % n)
						;
						element_type r2 = r1 + j;
						s_kpp = add_mod_2_pow_32::f(s_kpp, r1);
						value_type & s_kpq = first[(k + q) % n];
						s_kpq = add_mod_2_pow_32::f(s_kpq, r2);
						s_k = mod_2_pow_32::f(r2);
					}

					for (std::size_t k = m; k < m + n; ++k) {
						value_type & s_k = first[k % n];
						value_type & s_kpp = first[(k + p) % n];
						value_type s_km1 = first[(k + n - 1) % n];

						element_type r3 = 1566083941 * k_generate_T(
							s_k + s_kpp + s_km1
						);

						element_type r4 = r3 - (k % n);
						s_kpp = mod_2_pow_32::f(s_kpp ^ r3);
						value_type & s_kpq = first[(k + q) % n];
						s_kpq = mod_2_pow_32::f(s_kpq ^ r4);
						s_k = mod_2_pow_32::f(r4);
					}

				}

		};

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_SEED_SEQ_SEED_SEQ_DECL_HPP
