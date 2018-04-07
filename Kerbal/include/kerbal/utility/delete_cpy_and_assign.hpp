/**
 * @file		delete_cpy_and_assign.hpp
 * @brief
 * @date		2018年3月12日
 * @author		Peter
 * @copyright	Peter
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 */

#ifndef INCLUDE_KERBAL_UTILITY_DELETE_CPY_AND_ASSIGN_HPP_
#define INCLUDE_KERBAL_UTILITY_DELETE_CPY_AND_ASSIGN_HPP_

namespace kerbal
{
	namespace utility
	{

#	if __cplusplus < 201103L

		template <typename _Tp>
		class Delete_cpy_and_assign
		{
			protected:
			Delete_cpy_and_assign()
			{
			}
			private:
			Delete_cpy_and_assign(const Delete_cpy_and_assign&);
			Delete_cpy_and_assign& operator=(const Delete_cpy_and_assign&);
		};

#	else

		template <typename _Tp>
		class Delete_cpy_and_assign
		{
			protected:
				Delete_cpy_and_assign()
				{
				}
			private:
				Delete_cpy_and_assign(const Delete_cpy_and_assign&) = delete;
				Delete_cpy_and_assign& operator=(const Delete_cpy_and_assign&) = delete;
		};

#	endif

	}/* namespace utility */

}/* namespace kerbal */

#endif /* INCLUDE_KERBAL_UTILITY_DELETE_CPY_AND_ASSIGN_HPP_ */
