/**
 * @file       associative_insert_unique_r.hpp
 * @brief
 * @date       2022-09-09
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_ASSOCIATIVE_CONTAINER_FACILITY_ASSOCIATIVE_INSERT_UNIQUE_R_HPP
#define KERBAL_CONTAINER_ASSOCIATIVE_CONTAINER_FACILITY_ASSOCIATIVE_INSERT_UNIQUE_R_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/utility/compressed_pair.hpp>


namespace kerbal
{

	namespace container
	{

		template <typename Iterator>
		class associative_insert_unique_r :
			public kerbal::utility::compressed_pair<Iterator, bool>
		{
			private:
				typedef kerbal::utility::compressed_pair<Iterator, bool> super;

			public:
				typedef Iterator iterator;

			public:
				template <typename UIterator>
				KERBAL_CONSTEXPR
				associative_insert_unique_r(const UIterator & pos, bool result) :
					super(pos, result)
				{
				}

				template <typename UIterator>
				KERBAL_CONSTEXPR
				associative_insert_unique_r(const associative_insert_unique_r<UIterator> & src) :
					super(src.position(), src.insert_happen())
				{
				}

				KERBAL_CONSTEXPR14
				iterator & position() KERBAL_NOEXCEPT
				{
					return super::first();
				}

				KERBAL_CONSTEXPR
				const iterator & position() const KERBAL_NOEXCEPT
				{
					return super::first();
				}

				KERBAL_CONSTEXPR
				bool insert_happen() const KERBAL_NOEXCEPT
				{
					return super::second();
				}
		};

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_ASSOCIATIVE_CONTAINER_FACILITY_ASSOCIATIVE_INSERT_UNIQUE_R_HPP
