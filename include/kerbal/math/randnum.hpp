#ifndef _RANDNUM_HPP_
#define _RANDNUM_HPP_

#include <kerbal/utility/functor.hpp>
#include <utility>
#include <time.h>
#include <fstream>
#include <limits>

namespace kerbal
{
	namespace math
	{

		template <typename ReturnType, ReturnType a, ReturnType c, ReturnType m>
		class linear_congruential_engine
		{
			public:
				typedef ReturnType result_type;

			private:
				result_type state_value;

			public:

				explicit linear_congruential_engine(const result_type & seed = 0u) noexcept :
						state_value(seed % m == 0u ? 1u : seed)
				{
				}

				result_type operator()() noexcept
				{
					state_value = (a * state_value + c) % m;
					return state_value;
				}

				void discard(unsigned long long times) noexcept
				{
					for (; times != 0ULL; --times) {
						state_value = (a * state_value + c) % m;
					}
				}

				void seed(const result_type & seed = 0u)
				{
					state_value = (seed % m == 0u ? 1u : seed);
				}

				static constexpr result_type min() noexcept
				{
					return c == 0u ? 1u : 0u;
				}

				static constexpr result_type max() noexcept
				{
					return m - 1u;
				}
		};

		typedef linear_congruential_engine<size_t, 16807UL, 0UL, 2147483647UL> default_linear_congruential_engine;

		template <typename ReturnType>
		class dev_random_engine
		{
			public:
				typedef ReturnType result_type;

			private:
				std::ifstream fin;

			public:

				explicit dev_random_engine(const std::string & fpath) :
						fin(fpath)
				{
					if (!fin) {
						throw std::runtime_error("random device open failed");
					}
				}

				result_type operator()()
				{
					result_type ret;
					fin.read(reinterpret_cast<char*>(&ret), sizeof(result_type));

					return ret;
				}

				void discard(unsigned long long times)
				{
					for (; times != 0ULL; --times) {
						fin.ignore(sizeof(result_type));
					}
				}

				static constexpr result_type min() noexcept
				{
					return std::numeric_limits<result_type>::min();
				}

				static constexpr result_type max() noexcept
				{
					return std::numeric_limits<result_type>::max();
				}
		};

		namespace randnum
		{

			unsigned int seed();
//			time_t seed();

			double _0_1_rand();

			std::pair<double, double> std_normdist_rand_pair();

			double std_normdist_rand();

			inline double rand_between(double min, double max)
			{
				return (max - min) * _0_1_rand() + min;
			}

			template <typename type = double>
			struct rand_type_between: public kerbal::utility::functor<type>
			{
				private:
					static type get(const type & min, const type & max)
					{
						type val;
						do {
							val = (type) rand_between(min, max);
						} while (val == max);
						return val;
					}
				public:	
					rand_type_between(const type & min, const type & max) :
							kerbal::utility::functor<type>(get(min, max))
					{
					}
			};

			template <>
			struct rand_type_between<double> : public kerbal::utility::functor<double>
			{
					rand_type_between(double min, double max) :
							init(rand_between(min, max))
					{
					}
			};

			inline bool rand_true(double probability)
			{
				return _0_1_rand() <= probability ? true : false;
			}

			inline std::pair<double, double> normdist_rand_pair(double sigma = 1, double miu = 0)
			{
				std::pair<double, double> std_rand_pair(std_normdist_rand_pair());
				std_rand_pair.first = std_rand_pair.first * sigma + miu;
				std_rand_pair.second = std_rand_pair.second * sigma + miu;
				return std_rand_pair;
			}

			inline double normdist_rand(double sigma = 1, double miu = 0) //miu=ave,sigma=expect
			{
				return std_normdist_rand() * sigma + miu;
			}

		} /* end namesapce randnum */

	} /* end namesapce math */

} /* end namesapce kerbal */

#endif	/* End _RANDNUM_HPP_ */
