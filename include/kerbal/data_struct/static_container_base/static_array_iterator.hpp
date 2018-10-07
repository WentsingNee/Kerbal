/**
 * @file		static_array_iterator.hpp
 * @brief
 * @date		2018年5月16日
 * @author		Peter
 * @copyright	Peter
 * @copyright
 <a href="http://thinkspirit.org/">ThinkSpirit Laboratory</a>
 of
 <a href="http://www.nuist.edu.cn/">Nanjing University of Information Science & Technology</a>
 */

#ifndef INCLUDE_KERBAL_DATA_STRUCT_STATIC_CONTAINER_BASE_STATIC_ARRAY_ITERATOR_HPP_
#define INCLUDE_KERBAL_DATA_STRUCT_STATIC_CONTAINER_BASE_STATIC_ARRAY_ITERATOR_HPP_


namespace kerbal
{
	namespace data_struct
	{
		/*
		 * iterator
		 */

		template <typename Tp, size_t N>
		static_array<Tp, N>::iterator::iterator(pointer current) :
				current(current)
		{
		}

		template <typename Tp, size_t N>
		static_array<Tp, N>::iterator::operator const_iterator()
		{
			return const_iterator(current);
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::reference
		static_array<Tp, N>::iterator::operator*() const
		{
			return *current;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::pointer
		static_array<Tp, N>::iterator::operator->() const
		{
			return current;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::iterator&
		static_array<Tp, N>::iterator::operator++()
		{
			++current;
			return *this;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::iterator
		static_array<Tp, N>::iterator::operator++(int)
		{
			iterator bakup(*this);
			++current;
			return bakup;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::iterator&
		static_array<Tp, N>::iterator::operator--()
		{
			--current;
			return *this;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::iterator
		static_array<Tp, N>::iterator::operator--(int)
		{
			iterator bakup(*this);
			--current;
			return bakup;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::iterator
		static_array<Tp, N>::iterator::operator+(const typename iterator::difference_type & delta) const
		{
			return iterator(current + delta);
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::iterator
		static_array<Tp, N>::iterator::operator-(const typename iterator::difference_type & delta) const
		{
			return iterator(current - delta);
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::iterator::difference_type
		static_array<Tp, N>::iterator::operator-(const iterator & with) const
		{
			return this->current - with.current;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::iterator&
		static_array<Tp, N>::iterator::operator+=(const typename iterator::difference_type & delta)
		{
			this->current += delta;
			return *this;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::iterator&
		static_array<Tp, N>::iterator::operator-=(const typename iterator::difference_type & delta)
		{
			this->current -= delta;
			return *this;
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::iterator::operator==(const iterator & with) const
		{
			return current == with.current;
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::iterator::operator!=(const iterator & with) const
		{
			return current != with.current;
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::iterator::operator<(const iterator & with) const
		{
			return current < with.current;
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::iterator::operator<=(const iterator & with) const
		{
			return current <= with.current;
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::iterator::operator>(const iterator & with) const
		{
			return current > with.current;
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::iterator::operator>=(const iterator & with) const
		{
			return current >= with.current;
		}


		/*
		 * const_iterator
		 */

		template <typename Tp, size_t N>
		static_array<Tp, N>::const_iterator::const_iterator(const_pointer current) :
				current(current)
		{
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_reference
		static_array<Tp, N>::const_iterator::operator*() const
		{
			return *current;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_pointer
		static_array<Tp, N>::const_iterator::operator->() const
		{
			return current;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_iterator&
		static_array<Tp, N>::const_iterator::operator++()
		{
			++current;
			return *this;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_iterator
		static_array<Tp, N>::const_iterator::operator++(int)
		{
			const_iterator bakup(*this);
			++current;
			return bakup;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_iterator&
		static_array<Tp, N>::const_iterator::operator--()
		{
			--current;
			return *this;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_iterator
		static_array<Tp, N>::const_iterator::operator--(int)
		{
			const_iterator bakup(*this);
			--current;
			return bakup;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_iterator
		static_array<Tp, N>::const_iterator::operator+(const typename const_iterator::difference_type & delta) const
		{
			return const_iterator(current + delta);
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_iterator
		static_array<Tp, N>::const_iterator::operator-(const typename const_iterator::difference_type & delta) const
		{
			return const_iterator(current - delta);
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_iterator::difference_type
		static_array<Tp, N>::const_iterator::operator-(const const_iterator & with) const
		{
			return this->current - with.current;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_iterator&
		static_array<Tp, N>::const_iterator::operator+=(const typename const_iterator::difference_type & delta)
		{
			this->current += delta;
			return *this;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_iterator&
		static_array<Tp, N>::const_iterator::operator-=(const typename const_iterator::difference_type & delta)
		{
			this->current -= delta;
			return *this;
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::const_iterator::operator==(const const_iterator & with) const
		{
			return current == with.current;
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::const_iterator::operator!=(const const_iterator & with) const
		{
			return current != with.current;
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::const_iterator::operator<(const const_iterator & with) const
		{
			return current < with.current;
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::const_iterator::operator<=(const const_iterator & with) const
		{
			return current <= with.current;
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::const_iterator::operator>(const const_iterator & with) const
		{
			return current > with.current;
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::const_iterator::operator>=(const const_iterator & with) const
		{
			return current >= with.current;
		}


		/*
		 * reverse_iterator
		 */

		template <typename Tp, size_t N>
		static_array<Tp, N>::reverse_iterator::reverse_iterator(pointer current) :
				current(current)
		{
		}

		template <typename Tp, size_t N>
		static_array<Tp, N>::reverse_iterator::operator typename static_array::const_reverse_iterator()
		{
			return const_reverse_iterator(current);
		}


		template <typename Tp, size_t N>
		typename static_array<Tp, N>::reference
		static_array<Tp, N>::reverse_iterator::operator*() const
		{
			return *current;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::pointer
		static_array<Tp, N>::reverse_iterator::operator->() const
		{
			return current;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::reverse_iterator&
		static_array<Tp, N>::reverse_iterator::operator++()
		{
			--current;
			return *this;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::reverse_iterator
		static_array<Tp, N>::reverse_iterator::operator++(int)
		{
			reverse_iterator bakup(*this);
			--current;
			return bakup;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::reverse_iterator&
		static_array<Tp, N>::reverse_iterator::operator--()
		{
			++current;
			return *this;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::reverse_iterator
		static_array<Tp, N>::reverse_iterator::operator--(int)
		{
			reverse_iterator bakup(*this);
			++current;
			return bakup;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::reverse_iterator
		static_array<Tp, N>::reverse_iterator::operator+(int delta)
		{
			return reverse_iterator(current - delta);
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::reverse_iterator
		static_array<Tp, N>::reverse_iterator::operator-(int delta)
		{
			return reverse_iterator(current + delta);
		}

		template <typename Tp, size_t N>
		const typename static_array<Tp, N>::reverse_iterator
		static_array<Tp, N>::reverse_iterator::operator+(int delta) const
		{
			return reverse_iterator(current - delta);
		}

		template <typename Tp, size_t N>
		const typename static_array<Tp, N>::reverse_iterator
		static_array<Tp, N>::reverse_iterator::operator-(int delta) const
		{
			return reverse_iterator(current + delta);
		}


		template <typename Tp, size_t N>
		bool static_array<Tp, N>::reverse_iterator::operator==(const reverse_iterator & with) const
		{
			return current == with.current;
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::reverse_iterator::operator!=(const reverse_iterator & with) const
		{
			return current != with.current;
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::reverse_iterator::operator<(const reverse_iterator & with) const
		{
			return current > with.current;
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::reverse_iterator::operator<=(const reverse_iterator & with) const
		{
			return current >= with.current;
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::reverse_iterator::operator>(const reverse_iterator & with) const
		{
			return current < with.current;
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::reverse_iterator::operator>=(const reverse_iterator & with) const
		{
			return current <= with.current;
		}

		/*
		 * const_reverse_iterator
		 */

		template <typename Tp, size_t N>
		static_array<Tp, N>::const_reverse_iterator::const_reverse_iterator(const_pointer current) :
				current(current)
		{
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_reference
		static_array<Tp, N>::const_reverse_iterator::operator*() const
		{
			return *current;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_pointer
		static_array<Tp, N>::const_reverse_iterator::operator->() const
		{
			return current;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_reverse_iterator&
		static_array<Tp, N>::const_reverse_iterator::operator++()
		{
			--current;
			return *this;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_reverse_iterator
		static_array<Tp, N>::const_reverse_iterator::operator++(int)
		{
			const_reverse_iterator bakup(*this);
			--current;
			return bakup;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_reverse_iterator&
		static_array<Tp, N>::const_reverse_iterator::operator--()
		{
			++current;
			return *this;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_reverse_iterator
		static_array<Tp, N>::const_reverse_iterator::operator--(int)
		{
			const_reverse_iterator bakup(*this);
			++current;
			return bakup;
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_reverse_iterator
		static_array<Tp, N>::const_reverse_iterator::operator+(int delta)
		{
			return const_reverse_iterator(current - delta);
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_reverse_iterator
		static_array<Tp, N>::const_reverse_iterator::operator-(int delta)
		{
			return const_reverse_iterator(current + delta);
		}

		template <typename Tp, size_t N>
		const typename static_array<Tp, N>::const_reverse_iterator
		static_array<Tp, N>::const_reverse_iterator::operator+(int delta) const
		{
			return const_reverse_iterator(current - delta);
		}

		template <typename Tp, size_t N>
		const typename static_array<Tp, N>::const_reverse_iterator
		static_array<Tp, N>::const_reverse_iterator::operator-(int delta) const
		{
			return const_reverse_iterator(current + delta);
		}


		template <typename Tp, size_t N>
		bool static_array<Tp, N>::const_reverse_iterator::operator==(const const_reverse_iterator & with) const
		{
			return current == with.current;
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::const_reverse_iterator::operator!=(const const_reverse_iterator & with) const
		{
			return current != with.current;
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::const_reverse_iterator::operator<(const const_reverse_iterator & with) const
		{
			return current > with.current;
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::const_reverse_iterator::operator<=(const const_reverse_iterator & with) const
		{
			return current >= with.current;
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::const_reverse_iterator::operator>(const const_reverse_iterator & with) const
		{
			return current < with.current;
		}

		template <typename Tp, size_t N>
		bool static_array<Tp, N>::const_reverse_iterator::operator>=(const const_reverse_iterator & with) const
		{
			return current <= with.current;
		}

	}
}

#endif /* INCLUDE_KERBAL_DATA_STRUCT_STATIC_CONTAINER_BASE_STATIC_ARRAY_ITERATOR_HPP_ */
