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
		typename static_array<Tp, N>::reference
		static_array<Tp, N>::iterator::operator*() const
		{
			return current->raw_value();
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::pointer
		static_array<Tp, N>::iterator::operator->() const
		{
			return current->raw_pointer();
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
		typename static_array<Tp, N>::const_reference
		static_array<Tp, N>::const_iterator::operator*() const
		{
			return current->raw_value();
		}

		template <typename Tp, size_t N>
		typename static_array<Tp, N>::const_pointer
		static_array<Tp, N>::const_iterator::operator->() const
		{
			return current->raw_pointer();
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
	}
}

#endif /* INCLUDE_KERBAL_DATA_STRUCT_STATIC_CONTAINER_BASE_STATIC_ARRAY_ITERATOR_HPP_ */
