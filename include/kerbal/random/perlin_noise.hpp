/**
 * @file       perlin_noise.hpp
 * @brief
 * @date       2020-06-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_PERLIN_NOISE_HPP
#define KERBAL_RANDOM_PERLIN_NOISE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/container/nonmember_container_access.hpp>
#include <kerbal/random/uniform_real_distribution.hpp>

#include <cmath>
#include <cstddef>


namespace kerbal
{

	namespace random
	{

		template <typename ResultType = double, std::size_t PERLIN_SIZE = 4096>
		class perlin_noise
		{
			public:
				typedef ResultType result_type;

			protected:
				result_type perlin[PERLIN_SIZE];

			public:
				/**
				 * default to medium smooth
				 * @require octaves > 0
				 */
				int octaves;

				/**
				 * reduction/octave
				 * @require amp_falloff > 0
				 */
				result_type amp_falloff;

			public:
				template <typename Engine>
				KERBAL_CONSTEXPR14
				void reset(Engine & eg)
				{
					kerbal::random::uniform_real_distribution<result_type> urdis(0.0, 1.0);
					for (std::size_t i = 0; i < kerbal::container::size(this->perlin); ++i) {
						this->perlin[i] = urdis(eg);
					}
				}

#		if __cplusplus >= 201402L

			public:
				template <typename Engine>
				KERBAL_CONSTEXPR14
				explicit
				perlin_noise(Engine & eg, int octaves = 4, result_type amp_falloff = 0.5f) :
					perlin(), octaves(octaves), amp_falloff(amp_falloff)
				{
					this->reset(eg);
				}

#		else

			public:
				template <typename Engine>
				explicit
				perlin_noise(Engine & eg, int octaves = 4, result_type amp_falloff = 0.5f) :
					octaves(octaves), amp_falloff(amp_falloff)
				{
					this->reset(eg);
				}

#		endif

				result_type operator()(result_type x) const KERBAL_NOEXCEPT
				{
					if (x < 0) {
						x = -x;
					}

					int xi = x;
					result_type xf = x - xi;

					result_type r = 0;
					result_type ampl = 0.5;

					for (int i = 0; i < this->octaves; ++i) {
						std::size_t of = xi;

						result_type rxf = noise_fsc(xf);

						result_type n1 = h(of, rxf);

						r += n1 * ampl;
						ampl *= this->amp_falloff;

						xi <<= 1;
						xf *= 2;

						if (xf >= 1.0) {
							xi++;
							xf--;
						}
					}
					return r;
				}

				result_type operator()(result_type x, result_type y) const KERBAL_NOEXCEPT
				{
					if (x < 0) {
						x = -x;
					}
					if (y < 0) {
						y = -y;
					}

					int xi = x, yi = y;
					result_type xf = x - xi;
					result_type yf = y - yi;

					result_type r = 0;
					result_type ampl = 0.5;

					const int YWRAPB = 4;
					const int YWRAP = 1 << YWRAPB;

					for (int i = 0; i < this->octaves; ++i) {
						std::size_t of = xi + (yi << YWRAPB);

						result_type rxf = noise_fsc(xf);
						result_type ryf = noise_fsc(yf);

						result_type n1 = h(of, rxf);
						result_type n2 = h(of + YWRAP, rxf);
						n1 = n1 + ryf * (n2 - n1);

						r += n1 * ampl;
						ampl *= this->amp_falloff;

						xi <<= 1;
						xf *= 2;

						yi <<= 1;
						yf *= 2;

						if (xf >= 1.0) {
							xi++;
							xf--;
						}
						if (yf >= 1.0) {
							yi++;
							yf--;
						}
					}
					return r;
				}

				result_type operator()(result_type x, result_type y, result_type z) const KERBAL_NOEXCEPT
				{
					if (x < 0) {
						x = -x;
					}
					if (y < 0) {
						y = -y;
					}
					if (z < 0) {
						z = -z;
					}

					int xi = x, yi = y, zi = z;
					result_type xf = x - xi;
					result_type yf = y - yi;
					result_type zf = z - zi;

					result_type r = 0;
					result_type ampl = 0.5;

					const int YWRAPB = 4;
					const int ZWRAPB = 8;
					const int YWRAP = 1 << YWRAPB;
					const int ZWRAP = 1 << ZWRAPB;

					for (int i = 0; i < this->octaves; ++i) {
						std::size_t of = xi + (yi << YWRAPB) + (zi << ZWRAPB);

						result_type rxf = noise_fsc(xf);
						result_type ryf = noise_fsc(yf);
						result_type rzf = noise_fsc(zf);

						result_type n1 = h(of, rxf);
						result_type n2 = h(of + YWRAP, rxf);
						n1 = n1 + ryf * (n2 - n1);

						of += ZWRAP;
						result_type n3 = h(of, rxf);
						result_type n4 = h(of + YWRAP, rxf);

						n3 = n3 + ryf * (n4 - n3);
						n1 = n1 + rzf * (n3 - n1);

						r += n1 * ampl;
						ampl *= this->amp_falloff;

						xi <<= 1;
						xf *= 2;

						yi <<= 1;
						yf *= 2;

						zi <<= 1;
						zf *= 2;

						if (xf >= 1.0) {
							xi++;
							xf--;
						}
						if (yf >= 1.0) {
							yi++;
							yf--;
						}
						if (zf >= 1.0) {
							zi++;
							zf--;
						}
					}
					return r;
				}

			private:
				KERBAL_CONSTEXPR14
				result_type h(std::size_t of, result_type rf) const KERBAL_NOEXCEPT
				{
					result_type n = perlin[of % PERLIN_SIZE];
					n += rf * (perlin[(of + 1) % PERLIN_SIZE] - n);
					return n;
				}

				static result_type noise_fsc(result_type i) KERBAL_NOEXCEPT
				{
//					const result_type PI = 3.1415926535897932384626;
//					return 0.5f * (1.0f - cos(i * PI));

					const result_type PI_2 = 1.5707963267948966;
					result_type t = sin(i * PI_2);
					return t * t;
				}

		};

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_PERLIN_NOISE_HPP
