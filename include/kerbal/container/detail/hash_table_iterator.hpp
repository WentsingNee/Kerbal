/**
 * @file       hash_table_iterator.hpp
 * @brief
 * @date       2020-08-29
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_HASH_TABLE_ITERATOR_HPP
#define KERBAL_CONTAINER_DETAIL_HASH_TABLE_ITERATOR_HPP

#include <kerbal/container/fwd/forward_list.fwd.hpp>
#include <kerbal/container/fwd/hash_table.fwd.hpp>

#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/operators/dereferenceable.hpp>
#include <kerbal/operators/equality_comparable.hpp>
#include <kerbal/operators/incr_decr.hpp>

#include <iterator>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Entity>
			class hash_table_local_iter:
					protected kerbal::container::detail::fl_iter<Entity>,
					//forward iterator interface
					public kerbal::operators::dereferenceable<hash_table_local_iter<Entity>, Entity*>, // it->
					public kerbal::operators::equality_comparable<hash_table_local_iter<Entity> >, // it != jt
					public kerbal::operators::incrementable<hash_table_local_iter<Entity> > // it++
			{
				private:
					typedef kerbal::container::detail::fl_iter<Entity> super;

				private:
					template <typename Entity2,
							typename Extract,
							typename Hash,
							typename KeyEqual,
							typename NodeAllocatorBR,
							typename BucketAllocatorBR
					>
					friend class kerbal::container::hash_table;

					friend class kerbal::container::detail::hash_table_iter<Entity>;


				protected:
					typedef kerbal::container::detail::fl_allocator_unrelated<Entity> bucket_type;

				private:
					typedef kerbal::iterator::iterator_traits<Entity*>	iterator_traits;

				public:
					typedef std::forward_iterator_tag						iterator_category;
					typedef typename iterator_traits::value_type			value_type;
					typedef typename iterator_traits::difference_type		difference_type;
					typedef typename iterator_traits::pointer				pointer;
					typedef typename iterator_traits::reference				reference;

				protected:
					KERBAL_CONSTEXPR14
					explicit hash_table_local_iter(super super_iter) KERBAL_NOEXCEPT
							: super(super_iter)
					{
					}

				public:

				//===================
				// forward iterator interface

					KERBAL_CONSTEXPR14
					hash_table_local_iter& operator=(const super& super_iter) KERBAL_NOEXCEPT
					{
						super::operator=(super_iter);
						return *this;
					}

					KERBAL_CONSTEXPR14
					reference operator*() const KERBAL_NOEXCEPT
					{
						return super::operator*();
					}

					KERBAL_CONSTEXPR14
					hash_table_local_iter& operator++() KERBAL_NOEXCEPT
					{
						super::operator++();
						return *this;
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const hash_table_local_iter & lhs, const hash_table_local_iter & rhs) KERBAL_NOEXCEPT
					{
						return static_cast<const super&>(lhs) == static_cast<const super&>(rhs);
					}

			};

			template <typename Entity>
			class hash_table_local_kiter:
					protected kerbal::container::detail::fl_kiter<Entity>,
					//forward iterator interface
					public kerbal::operators::dereferenceable<hash_table_local_kiter<Entity>, Entity const*>, // it->
					public kerbal::operators::equality_comparable<hash_table_local_kiter<Entity> >, // it != jt
					public kerbal::operators::incrementable<hash_table_local_kiter<Entity> > // it++
			{
				private:
					typedef kerbal::container::detail::fl_kiter<Entity> super;

				private:
					template <typename Entity2,
							typename Extract,
							typename Hash,
							typename KeyEqual,
							typename NodeAllocatorBR,
							typename BucketAllocatorBR
					>
					friend class kerbal::container::hash_table;

					friend class kerbal::container::detail::hash_table_kiter<Entity>;


				protected:
					typedef kerbal::container::detail::fl_allocator_unrelated<Entity> bucket_type;

				private:
					typedef kerbal::iterator::iterator_traits<Entity const*>	iterator_traits;

				public:
					typedef std::forward_iterator_tag						iterator_category;
					typedef typename iterator_traits::value_type			value_type;
					typedef typename iterator_traits::difference_type		difference_type;
					typedef typename iterator_traits::pointer				pointer;
					typedef typename iterator_traits::reference				reference;

				protected:
					KERBAL_CONSTEXPR14
					explicit hash_table_local_kiter(super super_kiter) KERBAL_NOEXCEPT
							: super(super_kiter)
					{
					}

				public:

				//===================
				// forward iterator interface

					hash_table_local_kiter& operator=(const super& super_kiter)
					{
						super::operator=(super_kiter);
						return *this;
					}

					KERBAL_CONSTEXPR14
					reference operator*() const KERBAL_NOEXCEPT
					{
						return super::operator*();
					}

					KERBAL_CONSTEXPR14
					hash_table_local_kiter& operator++() KERBAL_NOEXCEPT
					{
						super::operator++();
						return *this;
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const hash_table_local_kiter & lhs, const hash_table_local_kiter & rhs) KERBAL_NOEXCEPT
					{
						return static_cast<const super&>(lhs) == static_cast<const super&>(rhs);
					}

			};

			template <typename Entity>
			class hash_table_iter:
					//forward iterator interface
					public kerbal::operators::dereferenceable<hash_table_iter<Entity>, Entity*>, // it->
					public kerbal::operators::equality_comparable<hash_table_iter<Entity> >, // it != jt
					public kerbal::operators::incrementable<hash_table_iter<Entity> > // it++
			{
				private:
					template <typename Entity2,
							typename Extract,
							typename Hash,
							typename KeyEqual,
							typename NodeAllocatorBR,
							typename BucketAllocatorBR
					>
					friend class kerbal::container::hash_table;

				protected:
					typedef kerbal::container::detail::fl_allocator_unrelated<Entity>	bucket_type;
					typedef kerbal::container::detail::hash_table_local_iter<Entity>	local_iter;

				private:
					typedef kerbal::iterator::iterator_traits<Entity*>	iterator_traits;

				public:
					typedef std::forward_iterator_tag						iterator_category;
					typedef typename iterator_traits::value_type			value_type;
					typedef typename iterator_traits::difference_type		difference_type;
					typedef typename iterator_traits::pointer				pointer;
					typedef typename iterator_traits::reference				reference;

				protected:
					bucket_type *			_K_bucket_current;
					const bucket_type *		_K_bucket_end;
					local_iter				_K_local_iter;

					KERBAL_CONSTEXPR14
					hash_table_iter(bucket_type * bucket_current, const bucket_type * bucket_end, local_iter local_iter) KERBAL_NOEXCEPT :
							_K_bucket_current(bucket_current), _K_bucket_end(bucket_end), _K_local_iter(local_iter)
					{
						if (this->_K_bucket_current == this->_K_bucket_end) {
							return;
						}
						while (this->_K_local_iter == this->_K_bucket_current->end()) {
							++this->_K_bucket_current;
							if (this->_K_bucket_current == this->_K_bucket_end) {
								return;
							} else {
								this->_K_local_iter = this->_K_bucket_current->begin();
							}
						}
					}

				public:

				//===================
				// forward iterator interface

					KERBAL_CONSTEXPR14
					reference operator*() const KERBAL_NOEXCEPT
					{
						return *this->_K_local_iter;
					}

					KERBAL_CONSTEXPR14
					hash_table_iter& operator++() KERBAL_NOEXCEPT
					{
						++this->_K_local_iter;

						while (this->_K_local_iter == this->_K_bucket_current->end()) {
							++this->_K_bucket_current;
							if (this->_K_bucket_current == this->_K_bucket_end) {
								return *this;
							} else {
								this->_K_local_iter =this-> _K_bucket_current->begin();
							}
						}
						return *this;
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const hash_table_iter & lhs, const hash_table_iter & rhs) KERBAL_NOEXCEPT
					{
						return lhs._K_local_iter == rhs._K_local_iter;
					}

			};

			template <typename Entity>
			class hash_table_kiter:
					//forward iterator interface
					public kerbal::operators::dereferenceable<hash_table_kiter<Entity>, Entity const *>, // it->
					public kerbal::operators::equality_comparable<hash_table_kiter<Entity> >, // it != jt
					public kerbal::operators::incrementable<hash_table_kiter<Entity> > // it++
			{
				private:
					template <typename Entity2,
							typename Extract,
							typename Hash,
							typename KeyEqual,
							typename NodeAllocatorBR,
							typename BucketAllocatorBR
					>
					friend class kerbal::container::hash_table;

				protected:
					typedef kerbal::container::detail::fl_allocator_unrelated<Entity>	bucket_type;
					typedef kerbal::container::detail::hash_table_local_kiter<Entity>	const_local_iter;

				private:
					typedef kerbal::iterator::iterator_traits<Entity const *>	iterator_traits;

				public:
					typedef std::forward_iterator_tag						iterator_category;
					typedef typename iterator_traits::value_type			value_type;
					typedef typename iterator_traits::difference_type		difference_type;
					typedef typename iterator_traits::pointer				pointer;
					typedef typename iterator_traits::reference				reference;

				protected:
					const bucket_type *		_K_bucket_current;
					const bucket_type *		_K_bucket_end;
					const_local_iter		_K_local_iter;

					KERBAL_CONSTEXPR14
					hash_table_kiter(const bucket_type * bucket_current, const bucket_type * bucket_end, const_local_iter local_iter) KERBAL_NOEXCEPT :
							_K_bucket_current(bucket_current), _K_bucket_end(bucket_end), _K_local_iter(local_iter)
					{
						if (this->_K_bucket_current == this->_K_bucket_end) {
							return;
						}
						while (this->_K_local_iter == this->_K_bucket_current->end()) {
							++this->_K_bucket_current;
							if (this->_K_bucket_current == this->_K_bucket_end) {
								return;
							} else {
								this->_K_local_iter = this->_K_bucket_current->begin();
							}
						}
					}

				public:

				//===================
				// forward iterator interface

					KERBAL_CONSTEXPR14
					reference operator*() const KERBAL_NOEXCEPT
					{
						return *this->_K_local_iter;
					}

					KERBAL_CONSTEXPR14
					hash_table_kiter& operator++() KERBAL_NOEXCEPT
					{
						++this->_K_local_iter;

						while (this->_K_local_iter == this->_K_bucket_current->end()) {
							++this->_K_bucket_current;
							if (this->_K_bucket_current == this->_K_bucket_end) {
								return *this;
							} else {
								this->_K_local_iter = this->_K_bucket_current->begin();
							}
						}
						return *this;
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const hash_table_kiter & lhs, const hash_table_kiter & rhs) KERBAL_NOEXCEPT
					{
						return lhs._K_local_iter == rhs._K_local_iter;
					}

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_HASH_TABLE_ITERATOR_HPP
