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

#include <kerbal/coroutine/config.hpp>

#if KERBAL_SUPPORT_COROUTINE

#include <kerbal/coroutine/detail/exp_compat.hpp>
#include <kerbal/coroutine/generator/generator.fwd.hpp>
#include <kerbal/coroutine/generator/detail/generator_iterator.decl.hpp>
#include <kerbal/coroutine/generator/detail/generator_promise_base.hpp>

#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/optional/optional.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/remove_cvref.hpp>
#include <kerbal/type_traits/remove_reference.hpp>
#include <kerbal/utility/forward.hpp>
#include <kerbal/utility/use_args.hpp>

#include <cstddef>


namespace kerbal
{

	namespace coroutine
	{

		template <typename T, typename Allocator>
		class generator
		{
			public:
				class promise_type;
				typedef kerbal::coroutine::detail::generator_iterator<T> iterator;
				friend class kerbal::coroutine::detail::generator_iterator<T>;

			private:
				typedef costd::coroutine_handle<promise_type> coroutine_handle;
				coroutine_handle k_handle;

			public:
				class promise_type :
					public kerbal::coroutine::detail::generator_promise_base
				{
						friend class generator;
						friend class kerbal::coroutine::detail::generator_iterator<T>;

						typedef kerbal::memory::allocator_traits<Allocator> allocator_traits;

					protected:
						kerbal::optional::optional<T> k_yielded;

					public:
						template <typename U>
						typename kerbal::type_traits::enable_if<
							!kerbal::utility::is_use_args_t<
								typename kerbal::type_traits::remove_cvref<U>::type
							>::value,
							costd::suspend_always
						>::type
						yield_value(U && arg)
						{
							this->k_yielded.emplace(kerbal::utility::forward<U>(arg));
							return {};
						}

						template <typename ... Args>
						costd::suspend_always
						yield_value(kerbal::utility::use_args_t<Args...> const & args)
						{
							this->k_yielded.emplace_use_args(args);
							return {};
						}

						template <typename ... Args>
						costd::suspend_always
						yield_value(kerbal::utility::use_args_t<Args...> && args)
						{
							this->k_yielded.emplace_use_args(kerbal::compatibility::move(args));
							return {};
						}

						void await_transform() = delete;

						generator
						get_return_object()
						{
							return generator(coroutine_handle::from_promise(*this));
						}

						void *
						operator new(std::size_t size)
						{
							Allocator alloc;
							return static_cast<void *>(
								allocator_traits::allocate(alloc, size)
							);
						}

						void
						operator delete(void * p, std::size_t size)
						{
							Allocator alloc;
							return allocator_traits::deallocate(
								alloc,
								static_cast<typename allocator_traits::value_type *>(p),
								size
							);
						}
				};

			private:
				explicit
				generator(coroutine_handle && handle) KERBAL_NOEXCEPT;

			public:
				generator() = default;

				generator(generator const &) = delete;

				generator(generator && src) KERBAL_NOEXCEPT;

				~generator();

				generator & operator=(generator const &) = delete;

				generator & operator=(generator && src) KERBAL_NOEXCEPT;

			protected:
				void empty_generator_check() const;

				void done_generator_check() const;

			public:
				T const & operator()();

				iterator begin();

				iterator end() KERBAL_NOEXCEPT;

				bool empty() const KERBAL_NOEXCEPT;

				bool done() const;

				void swap(generator & with) KERBAL_NOEXCEPT;

		};

	} // namespace coroutine

} // namespace kerbal

#endif

#endif // KERBAL_COROUTINE_GENERATOR_GENERATOR_DECL_HPP
