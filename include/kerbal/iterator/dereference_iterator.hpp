/**
 * @file       dereference_iterator.hpp
 * @brief
 * @date       2020-02-22
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ITERATOR_DEREFERENCE_ITERATOR_HPP
#define KERBAL_ITERATOR_DEREFERENCE_ITERATOR_HPP

#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/operators/addable.hpp>
#include <kerbal/operators/dereferenceable.hpp>
#include <kerbal/operators/incr_decr.hpp>
#include <kerbal/operators/subtractable.hpp>


#if KERBAL_ENABLE_MODULES
import kerba.type_traits;
#else
#include <kerbal/type_traits/pointer_deduction.hpp>
#endif

namespace kerbal
{

	namespace iterator
	{

		template <typename Iter>
		class dereference_iterator;

		namespace detail
		{

			template <typename Iter>
			struct __dereference_iterator_typedef_helper
			{
				private:
					typedef kerbal::iterator::iterator_traits<Iter>				iterator_traits;

				public:
					typedef typename iterator_traits::iterator_category			iterator_category;
					typedef typename kerbal::type_traits::remove_pointer<
									typename iterator_traits::value_type
							>::type												value_type;
					typedef typename iterator_traits::difference_type			difference_type;
					typedef value_type*											pointer;
					typedef value_type&											reference;
			};

			template <typename Iter, typename Tag>
			class __dereference_iterator;

			template <typename Iter>
			class __dereference_iterator<Iter, std::input_iterator_tag>:
							public kerbal::operators::dereferenceable<
									kerbal::iterator::dereference_iterator<Iter>,
									typename kerbal::iterator::detail::__dereference_iterator_typedef_helper<Iter>::pointer
							>, // it->
							public kerbal::operators::incrementable<
									kerbal::iterator::dereference_iterator<Iter>
							> // it++
			{
				private:
					typedef kerbal::iterator::detail::__dereference_iterator_typedef_helper<Iter> typedef_helper;
					typedef kerbal::iterator::dereference_iterator<Iter> dereference_iterator;

				public:
					typedef std::input_iterator_tag							iterator_category;
					typedef typename typedef_helper::value_type				value_type;
					typedef typename typedef_helper::difference_type		difference_type;
					typedef typename typedef_helper::pointer				pointer;
					typedef typename typedef_helper::reference				reference;

				protected:
					Iter current;

				public:
					KERBAL_CONSTEXPR
					explicit __dereference_iterator(const Iter& current)
							: current(current)
					{
					}

					KERBAL_CONSTEXPR14
					reference operator*() const
					{
						return **current;
					}

					KERBAL_CONSTEXPR14
					dereference_iterator& operator++()
					{
						++this->current;
						return static_cast<dereference_iterator&>(*this);
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const dereference_iterator & lhs, const dereference_iterator & rhs)
					{
						return lhs.current == rhs.current;
					}

					friend KERBAL_CONSTEXPR
					bool operator!=(const dereference_iterator & lhs, const dereference_iterator & rhs)
					{
						return lhs.current != rhs.current;
					}
			};

			template <typename Iter>
			class __dereference_iterator<Iter, std::bidirectional_iterator_tag>:
							public __dereference_iterator<Iter, std::input_iterator_tag>,
							public kerbal::operators::decrementable<
									kerbal::iterator::dereference_iterator<Iter>
							> // it--
			{
				private:
					typedef __dereference_iterator<Iter, std::input_iterator_tag> super;
					typedef kerbal::iterator::dereference_iterator<Iter> dereference_iterator;
					typedef kerbal::iterator::detail::__dereference_iterator_typedef_helper<Iter> typedef_helper;

				public:
					typedef std::bidirectional_iterator_tag					iterator_category;
					typedef typename typedef_helper::value_type				value_type;
					typedef typename typedef_helper::difference_type		difference_type;
					typedef typename typedef_helper::pointer				pointer;
					typedef typename typedef_helper::reference				reference;


				public:
					KERBAL_CONSTEXPR
					explicit __dereference_iterator(const Iter& current)
							: super(current)
					{
					}

					KERBAL_CONSTEXPR14
					dereference_iterator& operator--()
					{
						--this->current;
						return static_cast<dereference_iterator&>(*this);
					}
			};

			template <typename Iter>
			class __dereference_iterator<Iter, std::random_access_iterator_tag>:
							public __dereference_iterator<Iter, std::bidirectional_iterator_tag>,
							public kerbal::operators::addable<
									kerbal::iterator::dereference_iterator<Iter>,
									typename kerbal::iterator::iterator_traits<Iter>::difference_type
							>, // it + N
							public kerbal::operators::addable_left<
									kerbal::iterator::dereference_iterator<Iter>,
									typename kerbal::iterator::iterator_traits<Iter>::difference_type
							>, // N + it
							public kerbal::operators::subtractable<
									kerbal::iterator::dereference_iterator<Iter>,
									typename kerbal::iterator::iterator_traits<Iter>::difference_type
							> // it - N
			{
				private:
					typedef __dereference_iterator<Iter, std::bidirectional_iterator_tag> super;
					typedef kerbal::iterator::dereference_iterator<Iter> dereference_iterator;
					typedef kerbal::iterator::detail::__dereference_iterator_typedef_helper<Iter> typedef_helper;

				public:
					typedef std::random_access_iterator_tag					iterator_category;
					typedef typename typedef_helper::value_type				value_type;
					typedef typename typedef_helper::difference_type		difference_type;
					typedef typename typedef_helper::pointer				pointer;
					typedef typename typedef_helper::reference				reference;


				public:
					KERBAL_CONSTEXPR
					explicit __dereference_iterator(const Iter& current)
							: super(current)
					{
					}

					friend KERBAL_CONSTEXPR
					difference_type
					operator-(const dereference_iterator & lhs, const dereference_iterator & rhs)
					{
						return lhs.current - rhs.current;
					}

					KERBAL_CONSTEXPR14
					dereference_iterator& operator+=(const difference_type & delta)
					{
						this->current += delta;
						return static_cast<dereference_iterator&>(*this);
					}

					KERBAL_CONSTEXPR14
					dereference_iterator& operator-=(const difference_type & delta)
					{
						this->current -= delta;
						return static_cast<dereference_iterator&>(*this);
					}

					KERBAL_CONSTEXPR14
					reference operator[](const difference_type & dist) const
					{
						return *(static_cast<const dereference_iterator&>(*this) + dist);
					}

					friend KERBAL_CONSTEXPR
					bool operator<(const dereference_iterator & lhs, const dereference_iterator & rhs)
					{
						return lhs.current < rhs.current;
					}

					friend KERBAL_CONSTEXPR
					bool operator<=(const dereference_iterator & lhs, const dereference_iterator & rhs)
					{
						return lhs.current <= rhs.current;
					}

					friend KERBAL_CONSTEXPR
					bool operator>(const dereference_iterator & lhs, const dereference_iterator & rhs)
					{
						return lhs.current > rhs.current;
					}

					friend KERBAL_CONSTEXPR
					bool operator>=(const dereference_iterator & lhs, const dereference_iterator & rhs)
					{
						return lhs.current >= rhs.current;
					}
			};

		} // namespace detail

		template <typename Iter>
		class dereference_iterator:
				public kerbal::iterator::detail::__dereference_iterator<Iter, typename kerbal::iterator::iterator_traits<Iter>::iterator_category>
		{
			private:
				typedef kerbal::iterator::detail::__dereference_iterator<Iter, typename kerbal::iterator::iterator_traits<Iter>::iterator_category> super;

			public:
				typedef typename super::iterator_category		iterator_category;
				typedef typename super::value_type				value_type;
				typedef typename super::difference_type			difference_type;
				typedef typename super::pointer					pointer;
				typedef typename super::reference				reference;

			public:
				KERBAL_CONSTEXPR
				explicit dereference_iterator(const Iter& current)
						: super(current)
				{
				}
		};

		template <typename IterToPointer>
		KERBAL_CONSTEXPR
		dereference_iterator<IterToPointer>
		make_dereference_iterator(const IterToPointer& iter)
		{
			KERBAL_STATIC_ASSERT(kerbal::iterator::is_iterator<IterToPointer>::value, "Iter is not iterator");
			KERBAL_STATIC_ASSERT(kerbal::type_traits::is_pointer<
						typename kerbal::iterator::iterator_traits<IterToPointer>::value_type
					>::value, "Iter is not iterator to pointer");
			return dereference_iterator<IterToPointer>(iter);
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR
		dereference_iterator<Tp**>
		make_dereference_iterator(Tp* (&arr)[N])
		{
			return dereference_iterator<Tp**>(arr + 0);
		}

		template <typename Tp, size_t N>
		KERBAL_CONSTEXPR
		dereference_iterator<Tp * const *>
		make_dereference_iterator(Tp* const (&arr)[N])
		{
			return dereference_iterator<Tp * const *>(arr + 0);
		}

#	if __cplusplus >= 201703L

		namespace detail
		{

			template <typename IterToPointer>
			struct __deduction_helper
			{
					typedef IterToPointer type;
			};

			template <typename Tp, size_t N>
			struct __deduction_helper<Tp* [N]>
			{
					typedef Tp** type;
			};

			template <typename Tp, size_t N>
			struct __deduction_helper<Tp* const [N]>
			{
					typedef Tp * const * type;
			};

		} // namespace detail

		template <typename Iter>
		dereference_iterator(const Iter&) -> dereference_iterator<typename detail::__deduction_helper<Iter>::type>;

#	endif

	} // namespace iterator

} // namespace kerbal

#endif // KERBAL_ITERATOR_DEREFERENCE_ITERATOR_HPP
