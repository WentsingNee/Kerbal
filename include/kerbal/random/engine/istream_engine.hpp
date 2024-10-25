/**
 * @file       istream_engine.hpp
 * @brief
 * @date       2019-11-23
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_RANDOM_ENGINE_ISTREAM_ENGINE_HPP
#define KERBAL_RANDOM_ENGINE_ISTREAM_ENGINE_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/utility/reference_wrapper.hpp>

#include <istream>
#include <limits>


namespace kerbal
{

	namespace random
	{

		template <typename ResultType>
		class istream_engine
		{
			public:
				typedef ResultType result_type;

			private:
				kerbal::utility::reference_wrapper<std::istream> fin;

			public:

				explicit istream_engine(std::istream & fin) :
					fin(fin)
				{
				}

				result_type operator()()
				{
					result_type ret;
					fin.get().read(reinterpret_cast<char *>(&ret), sizeof(result_type));

					return ret;
				}

				void discard(unsigned long long times)
				{
					for (; times != 0ULL; --times) {
						fin.get().ignore(sizeof(result_type));
					}
				}


				KERBAL_CONSTEXPR
				static
				result_type min() KERBAL_NOEXCEPT
				{
					return std::numeric_limits<result_type>::min();
				}

				KERBAL_CONSTEXPR
				static
				result_type max() KERBAL_NOEXCEPT
				{
					return std::numeric_limits<result_type>::max();
				}

				KERBAL_CONSTEXPR
				bool operator==(const istream_engine & /*rhs*/) const
				{
					return false;
				}

				KERBAL_CONSTEXPR14
				bool operator!=(const istream_engine & /*rhs*/) const
				{
					return true;
				}

		};

	} // namespace random

} // namespace kerbal

#endif // KERBAL_RANDOM_ENGINE_ISTREAM_ENGINE_HPP
