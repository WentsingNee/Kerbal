/**
 * @file       static_vector_base.decl.hpp
 * @brief
 * @date       2022-03-21
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_DECL_STATIC_VECTOR_BASE_DECL_HPP
#define KERBAL_CONTAINER_DETAIL_DECL_STATIC_VECTOR_BASE_DECL_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/memory/raw_storage.hpp>
#include <kerbal/memory/raw_storage_uninitialized.hpp>
#include <kerbal/type_traits/can_be_pseudo_destructible.hpp>
#include <kerbal/type_traits/enable_if.hpp>

#include <cstddef>

#include <kerbal/container/detail/static_vector_iterator.hpp>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Tp, std::size_t N>
			class static_vector_base
			{
				public:
					typedef Tp						value_type;
					typedef const Tp				const_type;
					typedef value_type &			reference;
					typedef const value_type &		const_reference;
					typedef value_type*				pointer;
					typedef const value_type*		const_pointer;

#			if __cplusplus >= 201103L
					typedef value_type&&			rvalue_reference;
					typedef const value_type&&		const_rvalue_reference;
#			endif

					typedef std::size_t				size_type;
					typedef std::ptrdiff_t			difference_type;

					typedef detail::__stavec_iter<value_type>					iterator;
					typedef detail::__stavec_kiter<value_type>					const_iterator;

				protected:
					typedef kerbal::memory::raw_storage<value_type> storage_type;

				protected:
					size_type len;
					storage_type storage[N];

					KERBAL_CONSTEXPR
					static_vector_base() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					static_vector_base(const static_vector_base & src);

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					static_vector_base(static_vector_base && src);

#			endif

					KERBAL_CONSTEXPR14
					explicit static_vector_base(size_type n);

					KERBAL_CONSTEXPR14
					static_vector_base(size_type n, const_reference val);

				private:

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					void k_range_copy_cnstrctr(InputIterator first, InputIterator last,
											   std::input_iterator_tag);

					template <typename ForwardIterator>
					KERBAL_CONSTEXPR14
					void k_range_copy_cnstrctr(ForwardIterator first, ForwardIterator last,
											   std::forward_iterator_tag);

				protected:

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					static_vector_base(InputIterator first, InputIterator last,
							typename kerbal::type_traits::enable_if<
									kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
									int
							>::type = 0
					);

					KERBAL_CONSTEXPR14
					iterator begin() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					iterator end() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR
					const_iterator begin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR
					const_iterator end() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR
					const_iterator cbegin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR
					const_iterator cend() const KERBAL_NOEXCEPT;

			};

			template <typename Tp, std::size_t N, bool is_trivially_destructible =
					kerbal::type_traits::can_be_pseudo_destructible<Tp>::value>
			class sv_trivially_des_overload;

			template <typename Tp, std::size_t N>
			class sv_trivially_des_overload<Tp, N, false> :
					protected kerbal::container::detail::static_vector_base<Tp, N>
			{
				private:
					typedef kerbal::container::detail::static_vector_base<Tp, N> super;

				public:
					typedef typename super::value_type			value_type;
					typedef typename super::const_type			const_type;
					typedef typename super::reference			reference;
					typedef typename super::const_reference		const_reference;
					typedef typename super::pointer				pointer;
					typedef typename super::const_pointer		const_pointer;

#			if __cplusplus >= 201103L
					typedef typename super::rvalue_reference				rvalue_reference;
					typedef typename super::const_rvalue_reference			const_rvalue_reference;
#			endif

					typedef typename super::size_type			size_type;
					typedef typename super::difference_type		difference_type;

					KERBAL_CONSTEXPR20
					sv_trivially_des_overload() KERBAL_NOEXCEPT :
							super()
					{
					}

					KERBAL_CONSTEXPR20
					sv_trivially_des_overload(const sv_trivially_des_overload & src) :
							super(static_cast<const super &>(src))
					{
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR20
					sv_trivially_des_overload(sv_trivially_des_overload && src) :
							super(static_cast<super &&>(src))
					{
					}

#			endif

					KERBAL_CONSTEXPR20
					explicit sv_trivially_des_overload(size_type n) :
							super(n)
					{
					}

					KERBAL_CONSTEXPR20
					sv_trivially_des_overload(size_type n, const_reference val) :
							super(n, val)
					{
					}

					template <typename InputIterator>
					KERBAL_CONSTEXPR20
					sv_trivially_des_overload(InputIterator first, InputIterator last,
											  typename kerbal::type_traits::enable_if<
													  kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
													  int
											  >::type = 0
					) :
							super(first, last)
					{
					}

					KERBAL_CONSTEXPR20
					~sv_trivially_des_overload() KERBAL_NOEXCEPT
					{
						kerbal::memory::raw_storage_reverse_destroy(this->storage + 0, this->storage + this->len);
					}

			};

			template <typename Tp, std::size_t N>
			class sv_trivially_des_overload<Tp, N, true> :
					protected kerbal::container::detail::static_vector_base<Tp, N>
			{
				private:
					typedef kerbal::container::detail::static_vector_base<Tp, N> super;

				public:
					typedef typename super::value_type			value_type;
					typedef typename super::const_type			const_type;
					typedef typename super::reference			reference;
					typedef typename super::const_reference		const_reference;
					typedef typename super::pointer				pointer;
					typedef typename super::const_pointer		const_pointer;

#			if __cplusplus >= 201103L
					typedef typename super::rvalue_reference				rvalue_reference;
					typedef typename super::const_rvalue_reference			const_rvalue_reference;
#			endif

					typedef typename super::size_type			size_type;
					typedef typename super::difference_type		difference_type;

					KERBAL_CONSTEXPR
					sv_trivially_des_overload() KERBAL_NOEXCEPT :
							super()
					{
					}

					KERBAL_CONSTEXPR14
					sv_trivially_des_overload(const sv_trivially_des_overload & src) :
							super(static_cast<const super &>(src))
					{
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					sv_trivially_des_overload(sv_trivially_des_overload && src) :
							super(static_cast<super &&>(src))
					{
					}

#			endif

					KERBAL_CONSTEXPR14
					explicit sv_trivially_des_overload(size_type n) :
							super(n)
					{
					}

					KERBAL_CONSTEXPR14
					sv_trivially_des_overload(size_type n, const_reference val) :
							super(n, val)
					{
					}

					template <typename InputIterator>
					KERBAL_CONSTEXPR14
					sv_trivially_des_overload(InputIterator first, InputIterator last,
											  typename kerbal::type_traits::enable_if<
													  kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
													  int
											  >::type = 0
					) :
							super(first, last)
					{
					}

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal


#endif // KERBAL_CONTAINER_DETAIL_DECL_STATIC_VECTOR_BASE_DECL_HPP
