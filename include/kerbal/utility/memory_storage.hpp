/*
 * memory_storage.hpp
 *
 *  Created on: 2018年6月18日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_UTILITY_MEMORY_STORAGE_HPP_
#define INCLUDE_KERBAL_UTILITY_MEMORY_STORAGE_HPP_

#include <ratio>

namespace kerbal
{
	namespace utility
	{
		template <typename Ratio>
		class Memory_storage
		{
			public:
				typedef unsigned long long size_type;

				size_type x;
				constexpr Memory_storage(size_type x = 0) :
						x(x)
				{
				}

				template <typename Ratio2>
				constexpr Memory_storage(const Memory_storage<Ratio2> & src) :
						x(src.x / (double(Ratio::num) / double(Ratio::den))
								* (double(Ratio2::num) / double(Ratio2::den)))
				{
				}

				constexpr size_type count() const
				{
					return x;
				}

				template <typename Ratio2>
				bool operator<(const Memory_storage<Ratio2> & with) const
				{
					return this->x < ((Memory_storage<Ratio> ) (with)).x;
				}

				template <typename Ratio2>
				bool operator<=(const Memory_storage<Ratio2> & with) const
				{
					return this->x <= ((Memory_storage<Ratio> ) (with)).x;
				}
				template <typename Ratio2>
				bool operator>(const Memory_storage<Ratio2> & with) const
				{
					return this->x > ((Memory_storage<Ratio> ) (with)).x;
				}

				template <typename Ratio2>
				bool operator>=(const Memory_storage<Ratio2> & with) const
				{
					return this->x >= ((Memory_storage<Ratio> ) (with)).x;
				}

				template <typename Ratio2>
				bool operator==(const Memory_storage<Ratio2> & with) const
				{
					return this->x == ((Memory_storage<Ratio> ) (with)).x;
				}

				template <typename Ratio2>
				bool operator!=(const Memory_storage<Ratio2> & with) const
				{
					return this->x != ((Memory_storage<Ratio> ) (with)).x;
				}
		};

		typedef Memory_storage<std::ratio<1, 1> > Byte;
		typedef Memory_storage<std::ratio<1024, 1> > KB;
		typedef Memory_storage<std::ratio<1024 * 1024, 1> > MB;
		typedef Memory_storage<std::ratio<1024 * 1024 * 1024, 1> > GB;

		constexpr KB operator""_KB(unsigned long long x)
		{
			return KB(x);
		}

		constexpr MB operator""_MB(unsigned long long x)
		{
			return MB(x);
		}

		constexpr GB operator""_GB(unsigned long long x)
		{
			return GB(x);
		}
	}
}



#endif /* INCLUDE_KERBAL_UTILITY_MEMORY_STORAGE_HPP_ */
