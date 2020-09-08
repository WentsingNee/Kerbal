/**
 * @file       comparable_any.hpp
 * @brief      
 * @date       2019-7-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ANY_COMPARABLE_ANY_HPP
#define KERBAL_ANY_COMPARABLE_ANY_HPP

#include <kerbal/any/equality_comparable_any.hpp>

namespace kerbal
{

	namespace any
	{

		class comparable_any: public kerbal::any::equality_comparable_any
		{
			private:
				class control_block_base: public equality_comparable_any::control_block_base
				{
					virtual bool operator<(const control_block_base & with) const = 0;
					virtual bool operator>(const control_block_base & with) const = 0;
					virtual bool operator<=(const control_block_base & with) const = 0;
					virtual bool operator>=(const control_block_base & with) const = 0;
				};

				template <typename Tp>
				struct control_block: comparable_any::control_block_base
				{
						Tp value;

						KERBAL_CONSTEXPR explicit control_block(const Tp & value):
							value(value)
						{
						}

						virtual bool operator<(const control_block_base & with) const
						{
							return this->value < static_cast<const control_block&>(with).value;
						}

						virtual bool operator>(const control_block_base & with) const
						{
							return this->value > static_cast<const control_block&>(with).value;
						}

						virtual bool operator<=(const control_block_base & with) const
						{
							return this->value <= static_cast<const control_block&>(with).value;
						}

						virtual bool operator>=(const control_block_base & with) const
						{
							return this->value >= static_cast<const control_block&>(with).value;
						}
				};

		};

	} // namespace any

} // namespace kerbal

#endif // KERBAL_ANY_COMPARABLE_ANY_HPP
