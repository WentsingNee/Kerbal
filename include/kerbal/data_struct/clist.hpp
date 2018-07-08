/**
 * @file		clist.hpp
 * @brief
 * @date		2018年3月11日
 * @author		Peter
 * @copyright	Peter
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 */

#ifndef INCLUDE_KERBAL_DATA_STRUCT_CLIST_HPP_
#define INCLUDE_KERBAL_DATA_STRUCT_CLIST_HPP_

#include <vector>

template <typename type>
class clist
{
	protected:
		std::vector<type> v;
		std::vector<size_t> l;
		std::vector<size_t> r;

	public:
		clist() :
				v(), l(), r()
		{
		}

		size_t size() const
		{
			return v.size();
		}

		size_t capacity() const
		{
			return v.capacity();
		}

		bool empty() const
		{
			return v.empty();
		}

		void shrink_to_fit()
		{
			v.shrink_to_fit();
			l.shrink_to_fit();
			r.shrink_to_fit();
		}

		type& operator[](size_t index)
		{
			size_t py_index = 0;
			for (size_t i = 0; i < index; ++i) {
				py_index = r[py_index];
			}

			return v[py_index];
		}

		type& front()
		{
			return v.front();
		}

		const type& front() const
		{
			return v.front();
		}

		type& back()
		{
			return v.back();
		}

		const type& back() const
		{
			return v.back();
		}
};

#endif /* INCLUDE_KERBAL_DATA_STRUCT_CLIST_HPP_ */
