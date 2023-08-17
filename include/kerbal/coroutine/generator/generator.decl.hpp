/**
 * @file       generator.decl.hpp
 * @brief
 * @date       2021-08-16
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COROUTINE_GENERATOR_GENERATOR_DECL_HPP
#define KERBAL_COROUTINE_GENERATOR_GENERATOR_DECL_HPP

#include <kerbal/coroutine/detail/config.hpp>
#include <kerbal/coroutine/generator/generator.fwd.hpp>

#include <kerbal/coroutine/done_coroutine.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/operators/dereferenceable.hpp>
#include <kerbal/operators/equality_comparable.hpp>
#include <kerbal/optional/optional.hpp>
#include <kerbal/type_traits/remove_reference.hpp>
#include <kerbal/utility/forward.hpp>

#include <cstddef>


namespace kerbal
{

	namespace coroutine
	{

		class bad_generator :
				public std::runtime_error
		{
				typedef std::runtime_error super;

			public:
				bad_generator() :
						super("bad generator")
				{
				}

			protected:
				explicit bad_generator(const char * msg) :
						super(msg)
				{
				}
		};


		namespace detail
		{

			class generator_promise_base
			{
				public:
					static costd::suspend_always initial_suspend() KERBAL_NOEXCEPT
					{
						return {};
					}

					static costd::suspend_always final_suspend() KERBAL_NOEXCEPT
					{
						return {};
					}

					static void unhandled_exception()
					{
						throw;
					}

					static void return_void() KERBAL_NOEXCEPT
					{
					}

			};



			template <typename T>
			class generator_iterator :
					public kerbal::operators::dereferenceable<
						generator_iterator<T>, typename kerbal::type_traits::remove_reference<T>::type *
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
					kerbal::coroutine::generator<T> * gen;

				protected:
					generator_iterator() KERBAL_NOEXCEPT;

					explicit generator_iterator(kerbal::coroutine::generator<T> * gen);

					bool k_is_end() const KERBAL_NOEXCEPT;

				public:
					bool operator==(const generator_iterator & with) const KERBAL_NOEXCEPT;

					generator_iterator & operator++();

					const T & operator*() const;

			};

		} // namespace detail



		template <typename T>
		class generator
		{
			public:
				class promise_type;
				typedef detail::generator_iterator<T> iterator;
				friend class detail::generator_iterator<T>;

			private:
				typedef costd::coroutine_handle<promise_type> coroutine_handle;
				coroutine_handle k_handle;

			public:
				class promise_type : public detail::generator_promise_base
				{
						friend class generator;
						friend class detail::generator_iterator<T>;

					protected:
						kerbal::optional::optional<T> k_yielded;

					public:
						template <typename U>
						costd::suspend_always yield_value(U && arg)
						{
							k_yielded.emplace(kerbal::utility::forward<U>(arg));
							return {};
						}

						generator get_return_object()
						{
							return generator(coroutine_handle::from_promise(*this));
						}
				};

			private:
				explicit
				generator(coroutine_handle && handle) KERBAL_NOEXCEPT;

			public:
				generator() = default;

				generator(const generator &) = delete;

				generator(generator && src) KERBAL_NOEXCEPT;

				~generator() KERBAL_NOEXCEPT;

				generator & operator=(const generator &) = delete;

				generator & operator=(generator && src) KERBAL_NOEXCEPT;

			protected:
				void empty_generator_check() const;

				void done_generator_check() const;

			public:
				const T & operator()();

				iterator begin();

				iterator end() KERBAL_NOEXCEPT;

				void swap(generator & with) KERBAL_NOEXCEPT;

		};


	} // namespace coroutine

} // namespace kerbal

#endif // KERBAL_COROUTINE_GENERATOR_GENERATOR_DECL_HPP
