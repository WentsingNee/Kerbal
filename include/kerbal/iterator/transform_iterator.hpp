/**
 * @file       transform_iterator.hpp
 * @brief
 * @date       2020-6-9
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ITERATOR_TRANSFORM_ITERATOR_HPP
#define KERBAL_ITERATOR_TRANSFORM_ITERATOR_HPP

#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/operators/addable.hpp>
#include <kerbal/operators/dereferenceable.hpp>
#include <kerbal/operators/incr_decr.hpp>
#include <kerbal/operators/subtractable.hpp>
#include <kerbal/type_traits/type_identity.hpp>

namespace kerbal
{

	namespace iterator
	{

		template <typename Iter, typename UnaryFunction, typename Reference>
		class transform_iterator;

		namespace detail
		{

			template <typename Iter, typename Reference>
			struct __transform_iterator_typedef_helper
			{
				private:
					typedef kerbal::iterator::iterator_traits<Iter>				iterator_traits;

				public:
					typedef typename iterator_traits::iterator_category			iterator_category;
					typedef typename iterator_traits::difference_type			difference_type;
					typedef Reference											reference;
					typedef typename kerbal::type_traits::remove_cv<
							typename kerbal::type_traits::remove_reference<reference>::type
					>::type														value_type;
					typedef value_type*											pointer;
			};

			template <typename Iter, typename UnaryFunction, typename Reference, typename Tag>
			class __transform_iterator;

			template <typename Iter, typename UnaryFunction, typename Reference>
			class __transform_iterator<Iter, UnaryFunction, Reference, std::input_iterator_tag>:
							public kerbal::operators::dereferenceable<
									kerbal::iterator::transform_iterator<Iter, UnaryFunction, Reference>,
									typename kerbal::iterator::detail::__transform_iterator_typedef_helper<Iter, Reference>::pointer
							>, // it->
							public kerbal::operators::incrementable<
									kerbal::iterator::transform_iterator<Iter, UnaryFunction, Reference>
							> // it++
			{
				private:
					typedef kerbal::iterator::transform_iterator<Iter, UnaryFunction, Reference> transform_iterator;
					typedef kerbal::iterator::detail::__transform_iterator_typedef_helper<Iter, Reference> typedef_helper;

				public:
					typedef std::input_iterator_tag							iterator_category;
					typedef typename typedef_helper::value_type				value_type;
					typedef typename typedef_helper::difference_type		difference_type;
					typedef typename typedef_helper::pointer				pointer;
					typedef typename typedef_helper::reference				reference;

				protected:
					Iter current;
					UnaryFunction tf;

				public:
					KERBAL_CONSTEXPR
					explicit __transform_iterator(const Iter& current)
							: current(current), tf()
					{
					}

					KERBAL_CONSTEXPR
					explicit __transform_iterator(const Iter& current, UnaryFunction tf)
							: current(current), tf(tf)
					{
					}

					KERBAL_CONSTEXPR14
					reference operator*() const
					{
						return tf(*current);
					}

					KERBAL_CONSTEXPR14
					transform_iterator& operator++()
					{
						++this->current;
						return static_cast<transform_iterator&>(*this);
					}

					friend KERBAL_CONSTEXPR
					bool operator==(const transform_iterator & lhs, const transform_iterator & rhs)
					{
						return lhs.current == rhs.current;
					}

					friend KERBAL_CONSTEXPR
					bool operator!=(const transform_iterator & lhs, const transform_iterator & rhs)
					{
						return lhs.current != rhs.current;
					}
			};

			template <typename Iter, typename UnaryFunction, typename Reference>
			class __transform_iterator<Iter, UnaryFunction, Reference, std::bidirectional_iterator_tag>:
							public __transform_iterator<Iter, UnaryFunction, Reference, std::input_iterator_tag>,
							public kerbal::operators::decrementable<
									transform_iterator<Iter, UnaryFunction, Reference>
							> // it--
			{
				private:
					typedef __transform_iterator<Iter, UnaryFunction, Reference, std::input_iterator_tag> super;
					typedef kerbal::iterator::transform_iterator<Iter, UnaryFunction, Reference> transform_iterator;
					typedef kerbal::iterator::detail::__transform_iterator_typedef_helper<Iter, Reference> typedef_helper;

				public:
					typedef std::bidirectional_iterator_tag					iterator_category;
					typedef typename typedef_helper::value_type				value_type;
					typedef typename typedef_helper::difference_type		difference_type;
					typedef typename typedef_helper::pointer				pointer;
					typedef typename typedef_helper::reference				reference;


				public:
					KERBAL_CONSTEXPR
					explicit __transform_iterator(const Iter& current)
							: super(current)
					{
					}

					KERBAL_CONSTEXPR
					explicit __transform_iterator(const Iter& current, UnaryFunction tf)
							: super(current, tf)
					{
					}

					KERBAL_CONSTEXPR14
					transform_iterator& operator--()
					{
						--this->current;
						return static_cast<transform_iterator&>(*this);
					}
			};

			template <typename Iter, typename UnaryFunction, typename Reference>
			class __transform_iterator<Iter, UnaryFunction, Reference, std::random_access_iterator_tag>:
							public __transform_iterator<Iter, UnaryFunction, Reference, std::bidirectional_iterator_tag>,
							public kerbal::operators::addable<
									kerbal::iterator::transform_iterator<Iter, UnaryFunction, Reference>,
									typename kerbal::iterator::iterator_traits<Iter>::difference_type
							>, // it + N
							public kerbal::operators::addable_left<
									kerbal::iterator::transform_iterator<Iter, UnaryFunction, Reference>,
									typename kerbal::iterator::iterator_traits<Iter>::difference_type
							>, // N + it
							public kerbal::operators::subtractable<
									kerbal::iterator::transform_iterator<Iter, UnaryFunction, Reference>,
									typename kerbal::iterator::iterator_traits<Iter>::difference_type
							> // it - N
			{
				private:
					typedef __transform_iterator<Iter, UnaryFunction, Reference, std::bidirectional_iterator_tag> super;
					typedef kerbal::iterator::transform_iterator<Iter, UnaryFunction, Reference> transform_iterator;
					typedef kerbal::iterator::detail::__transform_iterator_typedef_helper<Iter, Reference> typedef_helper;

				public:
					typedef std::random_access_iterator_tag					iterator_category;
					typedef typename typedef_helper::value_type				value_type;
					typedef typename typedef_helper::difference_type		difference_type;
					typedef typename typedef_helper::pointer				pointer;
					typedef typename typedef_helper::reference				reference;


				public:
					KERBAL_CONSTEXPR
					explicit __transform_iterator(const Iter& current)
							: super(current)
					{
					}

					KERBAL_CONSTEXPR
					explicit __transform_iterator(const Iter& current, UnaryFunction tf)
							: super(current, tf)
					{
					}

					friend KERBAL_CONSTEXPR
					difference_type
					operator-(const transform_iterator & lhs, const transform_iterator & rhs)
					{
						return lhs.current - rhs.current;
					}

					KERBAL_CONSTEXPR14
					transform_iterator& operator+=(const difference_type & delta)
					{
						this->current += delta;
						return static_cast<transform_iterator&>(*this);
					}

					KERBAL_CONSTEXPR14
					transform_iterator& operator-=(const difference_type & delta)
					{
						this->current -= delta;
						return static_cast<transform_iterator&>(*this);
					}

					KERBAL_CONSTEXPR14
					reference operator[](const difference_type & dist) const
					{
						return *(static_cast<const transform_iterator&>(*this) + dist);
					}

					friend KERBAL_CONSTEXPR
					bool operator<(const transform_iterator & lhs, const transform_iterator & rhs)
					{
						return lhs.current < rhs.current;
					}

					friend KERBAL_CONSTEXPR
					bool operator<=(const transform_iterator & lhs, const transform_iterator & rhs)
					{
						return lhs.current <= rhs.current;
					}

					friend KERBAL_CONSTEXPR
					bool operator>(const transform_iterator & lhs, const transform_iterator & rhs)
					{
						return lhs.current > rhs.current;
					}

					friend KERBAL_CONSTEXPR
					bool operator>=(const transform_iterator & lhs, const transform_iterator & rhs)
					{
						return lhs.current >= rhs.current;
					}
			};

		} // namespace detail

		template <typename Iter, typename UnaryFunction, typename Reference>
		class transform_iterator:
				public kerbal::iterator::detail::__transform_iterator<Iter, UnaryFunction, Reference, typename kerbal::iterator::iterator_traits<Iter>::iterator_category>
		{
			private:
				typedef kerbal::iterator::detail::__transform_iterator<Iter, UnaryFunction, Reference, typename kerbal::iterator::iterator_traits<Iter>::iterator_category> super;

			public:
				typedef typename super::iterator_category		iterator_category;
				typedef typename super::value_type				value_type;
				typedef typename super::difference_type			difference_type;
				typedef typename super::pointer					pointer;
				typedef typename super::reference				reference;

			public:
				KERBAL_CONSTEXPR
				explicit transform_iterator(const Iter& current)
						: super(current)
				{
				}

				KERBAL_CONSTEXPR
				explicit transform_iterator(const Iter& current, UnaryFunction tf)
						: super(current, tf)
				{
				}

		};

		template <typename IterToPointer, typename UnaryFunction, typename Reference>
		KERBAL_CONSTEXPR
		transform_iterator<IterToPointer, UnaryFunction, Reference>
		make_transform_iterator(const IterToPointer& iter, UnaryFunction tf, kerbal::type_traits::type_identity<Reference>)
		{
			KERBAL_STATIC_ASSERT(kerbal::iterator::is_iterator<IterToPointer>::value, "Iter is not iterator");
			return transform_iterator<IterToPointer, UnaryFunction, Reference>(iter, tf);
		}

		template <typename Tp, size_t N, typename UnaryFunction, typename Reference>
		KERBAL_CONSTEXPR
		transform_iterator<Tp*, UnaryFunction, Reference>
		make_transform_iterator(Tp (&arr)[N], UnaryFunction tf, kerbal::type_traits::type_identity<Reference>)
		{
			return transform_iterator<Tp*, UnaryFunction, Reference>(arr + 0, tf);
		}

	} // namespace iterator

} // namespace kerbal

#endif // KERBAL_ITERATOR_TRANSFORM_ITERATOR_HPP
