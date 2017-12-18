#ifndef _RANDNUM_HPP_
#define _RANDNUM_HPP_

unsigned int seed();

double ave_rand(bool if_include_0, bool if_include_1);
inline double rand_between(double min, double max);
inline bool rand_true(double probability);
double normdist_rand(double sigma = 1, double miu = 0);
double normdist_noise(double former, double sigma, double miu);

inline double rand_between(double min, double max)
{
	return (max - min) * ave_rand(true, false) + min;
}

inline bool rand_true(double probability)
{
	return ave_rand(true, true) <= probability ? true : false;
}

#endif	/* End _RANDNUM_HPP_ */
