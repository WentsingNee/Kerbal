/**
 * @file       generator_iterator.decl.hpp
 * @brief
 * @date       2023-08-17
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COROUTINE_GENERATOR_DETAIL_GENERATOR_ITERATOR_DECL_HPP
#define KERBAL_COROUTINE_GENERATOR_DETAIL_GENERATOR_ITERATOR_DECL_HPP

#include <kerbal/coroutine/generator/generator.fwd.hpp>

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/operators/dereferenceable.hpp>
#include <kerbal/operators/equality_comparable.hpp>
#include <kerbal/type_traits/remove_reference.hpp>

#include <cstddef>


namespace kerbal
{

	namespace coroutine
	{

		namespace detail
		{

			template <typename T>
			class generator_iterator :
				public kerbal::operators::dereferenceable<
					generator_iterator<T>,
					typename kerbal::type_traits::remove_reference<T>::type *
				>, // it->
				public kerbal::operators::equality_comparable<generator_iterator<T> > // it != jt
			{
					friend class kerbal::coroutine::generator<T>;

				public:
					typedef std::input_iterator_tag		iterator_category;
					typedef typename kerbal::type_traits::remove_reference<T>::type
														value_type;
					typedef std::ptrdiff_t				difference_type;
					typedef value_type *				pointer;
					typedef value_type &				reference;

				protected:
					kerbal::coroutine::generator<T> * k_gen;

				protected:
					generator_iterator() KERBAL_NOEXCEPT;

					explicit generator_iterator(kerbal::coroutine::generator<T> * gen);

					bool k_is_end() const KERBAL_NOEXCEPT;

				public:
					bool operator==(generator_iterator const & with) const KERBAL_NOEXCEPT;

					generator_iterator & operator++();

					T const & operator*() const;

			};

		} // namespace detail

	} // namespace coroutine

} // namespace kerbal

#endif // KERBAL_COROUTINE_GENERATOR_DETAIL_GENERATOR_ITERATOR_DECL_HPP
