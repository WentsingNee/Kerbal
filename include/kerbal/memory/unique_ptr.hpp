/**
 * @file       unique_ptr.hpp
 * @brief
 * @date       2019-7-26
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_UNIQUE_PTR_HPP
#define KERBAL_MEMORY_UNIQUE_PTR_HPP

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/guard.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/compatibility/move.hpp>
#	include <kerbal/type_traits/enable_if.hpp>
#	include <kerbal/type_traits/integral_constant.hpp>
#	include <kerbal/type_traits/is_array.hpp>
#	include <kerbal/utility/declval.hpp>
#	include <kerbal/utility/forward.hpp>
#else
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/config/exceptions.hpp>

#	if KERBAL_HAS_EXCEPTIONS_SUPPORT
#		include <kerbal/type_traits/is_nothrow_constructible.hpp>
#		include <kerbal/type_traits/is_nothrow_default_constructible.hpp>
#		include <kerbal/type_traits/is_nothrow_move_assignable.hpp>
#		include <kerbal/type_traits/tribool_constant.hpp>
#	endif

#endif


namespace kerbal
{

	namespace memory
	{

		template <typename T, typename Deleter = kerbal::memory::default_delete<T> >
		class unique_ptr;

		template <typename T, typename Deleter>
		class unique_ptr :
			private kerbal::utility::noncopyable,
			protected kerbal::utility::member_compress_helper<Deleter>
		{
			private:
				typedef kerbal::utility::member_compress_helper<Deleter> deleter_compress_helper;

				template <typename U, typename UDeleter>
				friend class kerbal::memory::unique_ptr;

			public:
				typedef T element_type;
				typedef T * pointer;
				typedef Deleter deleter_type;

#		if __cplusplus >= 201103L && KERBAL_HAS_EXCEPTIONS_SUPPORT

				// forward declare to solve the problem of compile error under msvc
				struct is_nothrow_reset :
					kerbal::type_traits::bool_constant<
						noexcept(
							kerbal::utility::declval<deleter_type &>()(
								kerbal::utility::declval<pointer>()
							)
						)
					>
				{
				};

#		endif

			protected:
				pointer k_ptr;

			public:

#		if __cplusplus >= 201103L && KERBAL_HAS_EXCEPTIONS_SUPPORT

				struct try_test_is_nothrow_default_constructible :
					kerbal::type_traits::try_test_is_nothrow_default_constructible<deleter_compress_helper>
				{
				};

#		endif

				KERBAL_CONSTEXPR20
				unique_ptr()
					KERBAL_CONDITIONAL_NOEXCEPT(
						try_test_is_nothrow_default_constructible::IS_TRUE::value
					) :
					k_ptr(NULL)
				{
				}

#		if __cplusplus >= 201103L

#			if KERBAL_HAS_EXCEPTIONS_SUPPORT

				struct try_test_is_nothrow_constructible_from_nullptr :
					kerbal::type_traits::try_test_is_nothrow_default_constructible<deleter_compress_helper>
				{
				};

#			endif

				KERBAL_CONSTEXPR20
				unique_ptr(std::nullptr_t)
					KERBAL_CONDITIONAL_NOEXCEPT(
						try_test_is_nothrow_constructible_from_nullptr::IS_TRUE::value
					) :
					k_ptr(NULL)
				{
				}

#		endif


#		if __cplusplus >= 201103L && KERBAL_HAS_EXCEPTIONS_SUPPORT

				struct try_test_is_nothrow_constructible_from_ptr :
					kerbal::type_traits::try_test_is_nothrow_default_constructible<deleter_compress_helper>
				{
				};

#		endif

				KERBAL_CONSTEXPR20
				explicit unique_ptr(pointer ptr)
					KERBAL_CONDITIONAL_NOEXCEPT(
						try_test_is_nothrow_constructible_from_ptr::IS_TRUE::value
					) :
					k_ptr(ptr)
				{
				}

#		if __cplusplus >= 201103L && KERBAL_HAS_EXCEPTIONS_SUPPORT

				struct try_test_is_nothrow_constructible_from_ptr_and_copy_from_deleter :
					kerbal::type_traits::try_test_is_nothrow_constructible<
						deleter_compress_helper,
						kerbal::utility::in_place_t,
						const deleter_type &
					>
				{
				};

#		endif

				KERBAL_CONSTEXPR20
				unique_ptr(pointer ptr, const deleter_type & deleter)
					KERBAL_CONDITIONAL_NOEXCEPT(
						try_test_is_nothrow_constructible_from_ptr_and_copy_from_deleter::IS_TRUE::value
					) :
					deleter_compress_helper(kerbal::utility::in_place_t(), deleter),
					k_ptr(ptr)
				{
				}

#		if __cplusplus >= 201103L

#			if KERBAL_HAS_EXCEPTIONS_SUPPORT

				struct try_test_is_nothrow_constructible_from_ptr_and_move_from_deleter :
					kerbal::type_traits::try_test_is_nothrow_constructible<
						deleter_compress_helper,
						kerbal::utility::in_place_t,
						deleter_type &&
					>
				{
				};

#			endif

				KERBAL_CONSTEXPR20
				unique_ptr(pointer ptr, deleter_type && deleter)
					KERBAL_CONDITIONAL_NOEXCEPT(
						try_test_is_nothrow_constructible_from_ptr_and_move_from_deleter::IS_TRUE::value
					) :
					deleter_compress_helper(kerbal::utility::in_place_t(), kerbal::compatibility::move(deleter)),
					k_ptr(ptr)
				{
				}

#			if KERBAL_HAS_EXCEPTIONS_SUPPORT

				struct try_test_is_nothrow_move_constructible :
					kerbal::type_traits::try_test_is_nothrow_constructible<
						deleter_compress_helper,
						kerbal::utility::in_place_t,
						deleter_type &&
					>
				{
				};

#			endif

				KERBAL_CONSTEXPR20
				unique_ptr(unique_ptr && src)
					KERBAL_CONDITIONAL_NOEXCEPT(
						try_test_is_nothrow_move_constructible::IS_TRUE::value
					) :
					deleter_compress_helper(kerbal::utility::in_place_t(), kerbal::compatibility::move(src.get_deleter())),
					k_ptr(src.k_ptr)
				{
					src.k_ptr = nullptr;
				}

#			if KERBAL_HAS_EXCEPTIONS_SUPPORT

				template <typename U, typename UDeleter>
				struct try_test_is_nothrow_covariant_move_constructible :
					kerbal::type_traits::try_test_is_nothrow_constructible<
						deleter_compress_helper,
						kerbal::utility::in_place_t,
						typename unique_ptr<U, UDeleter>::deleter_type &&
					>
				{
				};

#			endif

				template <typename U, typename UDeleter>
				KERBAL_CONSTEXPR20
				unique_ptr(
					unique_ptr<U, UDeleter> && src,
					typename kerbal::type_traits::enable_if<!kerbal::type_traits::is_array<U>::value, int>::type = 0
				)
					KERBAL_CONDITIONAL_NOEXCEPT((
						try_test_is_nothrow_covariant_move_constructible<U, UDeleter>::IS_TRUE::value
					)) :
					deleter_compress_helper(
						kerbal::utility::in_place_t(),
						kerbal::compatibility::move(src.get_deleter())
					),
					k_ptr(src.k_ptr)
				{
					src.k_ptr = nullptr;
				}

#		endif

				KERBAL_CONSTEXPR20
				~unique_ptr()
				{
					if (this->k_ptr != NULL) {
						this->get_deleter()(this->k_ptr);
					}
				}

#		if __cplusplus >= 201103L

#			if KERBAL_HAS_EXCEPTIONS_SUPPORT

				struct try_test_is_nothrow_move_assignable :
					kerbal::type_traits::tribool_conjunction<
						is_nothrow_reset,
						kerbal::type_traits::try_test_is_nothrow_move_assignable<deleter_type>
					>::result
				{
				};

#			endif

				KERBAL_CONSTEXPR20
				unique_ptr & operator=(unique_ptr && src)
					KERBAL_CONDITIONAL_NOEXCEPT(
						try_test_is_nothrow_move_assignable::IS_TRUE::value
					)
				{
					this->reset();
					this->get_deleter() = kerbal::compatibility::move(src.get_deleter());
					this->k_ptr = src.k_ptr;
					src.k_ptr = nullptr;
					return *this;
				}

				KERBAL_CONSTEXPR20
				unique_ptr & operator=(std::nullptr_t)
					KERBAL_CONDITIONAL_NOEXCEPT(
						is_nothrow_reset::value
					)
				{
					this->reset();
					return *this;
				}

#		endif

				KERBAL_CONSTEXPR20
				void reset()
					KERBAL_CONDITIONAL_NOEXCEPT(
						is_nothrow_reset::value
					)
				{
					this->reset(NULL);
				}

				KERBAL_CONSTEXPR20
				void reset(pointer p)
					KERBAL_CONDITIONAL_NOEXCEPT(
						is_nothrow_reset::value
					)
				{
					if (this->k_ptr != NULL) {
						this->get_deleter()(this->k_ptr);
					}
					this->k_ptr = p;
				}

				KERBAL_CONSTEXPR20
				pointer release() KERBAL_NOEXCEPT
				{
					pointer ptr = this->k_ptr;
					this->k_ptr = NULL;
					return ptr;
				}

				KERBAL_CONSTEXPR20
				pointer get() const KERBAL_NOEXCEPT
				{
					return this->k_ptr;
				}

				KERBAL_CONSTEXPR20
#		if __cplusplus >= 201103L
				explicit
#		endif
				operator bool() const KERBAL_NOEXCEPT
				{
					return this->k_ptr != NULL;
				}

				KERBAL_CONSTEXPR20
				element_type & operator*() const KERBAL_NOEXCEPT
				{
					return *this->k_ptr;
				}

				KERBAL_CONSTEXPR20
				pointer operator->() const KERBAL_NOEXCEPT
				{
					return this->k_ptr;
				}

				KERBAL_CONSTEXPR14
				deleter_type & get_deleter() KERBAL_NOEXCEPT
				{
					return deleter_compress_helper::member();
				}

				KERBAL_CONSTEXPR
				const deleter_type & get_deleter() const KERBAL_NOEXCEPT
				{
					return deleter_compress_helper::member();
				}

				KERBAL_CONSTEXPR20
				void swap(unique_ptr & with)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(
							kerbal::algorithm::swap(
								kerbal::utility::declval<deleter_type &>(),
								kerbal::utility::declval<deleter_type &>()
							)
						) &&
						noexcept(
							kerbal::algorithm::swap(
								kerbal::utility::declval<deleter_type &>(),
								kerbal::utility::declval<deleter_type &>()
							)
						)
					)
				{
					kerbal::algorithm::swap(this->get_deleter(), with.get_deleter());
					kerbal::algorithm::swap(this->k_ptr, with.k_ptr);
				}

		};


		template <typename T, typename Deleter>
		class unique_ptr<T[], Deleter> :
			private kerbal::utility::noncopyable,
			protected kerbal::utility::member_compress_helper<Deleter>
		{
			private:
				typedef kerbal::utility::member_compress_helper<Deleter> deleter_compress_helper;

			public:
				typedef T element_type;
				typedef T * pointer;
				typedef Deleter deleter_type;

#		if __cplusplus >= 201103L && KERBAL_HAS_EXCEPTIONS_SUPPORT

				struct is_nothrow_reset :
					kerbal::type_traits::bool_constant<
						noexcept(
							kerbal::utility::declval<deleter_type &>()(
								kerbal::utility::declval<pointer>()
							)
						)
					>
				{
				};

#		endif

			protected:
				pointer k_ptr;

			public:

#		if __cplusplus >= 201103L && KERBAL_HAS_EXCEPTIONS_SUPPORT

				struct try_test_is_nothrow_default_constructible :
					kerbal::type_traits::try_test_is_nothrow_default_constructible<deleter_compress_helper>
				{
				};

#		endif

				unique_ptr()
					KERBAL_CONDITIONAL_NOEXCEPT(
						try_test_is_nothrow_default_constructible::IS_TRUE::value
					) :
					k_ptr(NULL)
				{
				}

#		if __cplusplus >= 201103L

#			if KERBAL_HAS_EXCEPTIONS_SUPPORT

				struct try_test_is_nothrow_constructible_from_nullptr :
					kerbal::type_traits::try_test_is_nothrow_default_constructible<deleter_compress_helper>
				{
				};

#			endif

				KERBAL_CONSTEXPR20
				unique_ptr(std::nullptr_t)
					KERBAL_CONDITIONAL_NOEXCEPT(
						try_test_is_nothrow_constructible_from_nullptr::IS_TRUE::value
					) :
					k_ptr(NULL)
				{
				}

#		endif


#		if __cplusplus >= 201103L && KERBAL_HAS_EXCEPTIONS_SUPPORT

				struct try_test_is_nothrow_constructible_from_ptr :
					kerbal::type_traits::try_test_is_nothrow_default_constructible<deleter_compress_helper>
				{
				};

#		endif

				KERBAL_CONSTEXPR20
				explicit unique_ptr(pointer ptr)
					KERBAL_CONDITIONAL_NOEXCEPT(
						try_test_is_nothrow_constructible_from_ptr::IS_TRUE::value
					) :
					k_ptr(ptr)
				{
				}

#		if __cplusplus >= 201103L && KERBAL_HAS_EXCEPTIONS_SUPPORT

				struct try_test_is_nothrow_constructible_from_ptr_and_copy_from_deleter :
					kerbal::type_traits::try_test_is_nothrow_constructible<
						deleter_compress_helper,
						kerbal::utility::in_place_t,
						const deleter_type &
					>
				{
				};

#		endif

				KERBAL_CONSTEXPR20
				unique_ptr(pointer ptr, const deleter_type & deleter)
					KERBAL_CONDITIONAL_NOEXCEPT(
						try_test_is_nothrow_constructible_from_ptr_and_copy_from_deleter::IS_TRUE::value
					) :
					deleter_compress_helper(kerbal::utility::in_place_t(), deleter),
					k_ptr(ptr)
				{
				}

#		if __cplusplus >= 201103L

#			if KERBAL_HAS_EXCEPTIONS_SUPPORT

				struct try_test_is_nothrow_constructible_from_ptr_and_move_from_deleter :
					kerbal::type_traits::try_test_is_nothrow_constructible<
						deleter_compress_helper,
						kerbal::utility::in_place_t,
						deleter_type &&
					>
				{
				};

#			endif

				KERBAL_CONSTEXPR20
				unique_ptr(pointer ptr, deleter_type && deleter)
					KERBAL_CONDITIONAL_NOEXCEPT(
						try_test_is_nothrow_constructible_from_ptr_and_move_from_deleter::IS_TRUE::value
					) :
					deleter_compress_helper(
						kerbal::utility::in_place_t(),
						kerbal::compatibility::move(deleter)
					),
					k_ptr(ptr)
				{
				}

#			if KERBAL_HAS_EXCEPTIONS_SUPPORT

				struct try_test_is_nothrow_move_constructible :
					kerbal::type_traits::try_test_is_nothrow_constructible<
						deleter_compress_helper,
						kerbal::utility::in_place_t,
						deleter_type &&
					>
				{
				};

#			endif

				KERBAL_CONSTEXPR20
				unique_ptr(unique_ptr && src)
					KERBAL_CONDITIONAL_NOEXCEPT(
						try_test_is_nothrow_move_constructible::IS_TRUE::value
					) :
					deleter_compress_helper(
						kerbal::utility::in_place_t(),
						kerbal::compatibility::move(src.get_deleter())
					),
					k_ptr(src.k_ptr)
				{
					src.k_ptr = nullptr;
				}

#		endif

				KERBAL_CONSTEXPR20
				~unique_ptr()
				{
					if (this->k_ptr != NULL) {
						this->get_deleter()(this->k_ptr);
					}
				}

#		if __cplusplus >= 201103L

#			if KERBAL_HAS_EXCEPTIONS_SUPPORT

				struct try_test_is_nothrow_move_assignable :
					kerbal::type_traits::tribool_conjunction<
						is_nothrow_reset,
						kerbal::type_traits::try_test_is_nothrow_move_assignable<deleter_type>
					>::result
				{
				};

#			endif

				KERBAL_CONSTEXPR20
				unique_ptr & operator=(unique_ptr && src)
					KERBAL_CONDITIONAL_NOEXCEPT(
						try_test_is_nothrow_move_assignable::IS_TRUE::value
					)
				{
					this->reset();
					this->get_deleter() = kerbal::compatibility::move(src.get_deleter());
					this->k_ptr = src.k_ptr;
					src.k_ptr = nullptr;
					return *this;
				}

				KERBAL_CONSTEXPR20
				unique_ptr & operator=(std::nullptr_t)
					KERBAL_CONDITIONAL_NOEXCEPT(
						is_nothrow_reset::value
					)
				{
					this->reset();
					return *this;
				}

#		endif

				KERBAL_CONSTEXPR20
				void reset()
					KERBAL_CONDITIONAL_NOEXCEPT(
						is_nothrow_reset::value
					)
				{
					this->reset(NULL);
				}

				KERBAL_CONSTEXPR20
				void reset(pointer p)
					KERBAL_CONDITIONAL_NOEXCEPT(
						is_nothrow_reset::value
					)
				{
					if (this->k_ptr != NULL) {
						this->get_deleter()(this->k_ptr);
					}
					this->k_ptr = p;
				}

				KERBAL_CONSTEXPR20
				pointer release() KERBAL_NOEXCEPT
				{
					pointer ptr = this->k_ptr;
					this->k_ptr = NULL;
					return ptr;
				}

				KERBAL_CONSTEXPR20
				pointer get() const KERBAL_NOEXCEPT
				{
					return this->k_ptr;
				}

				KERBAL_CONSTEXPR20
#		if __cplusplus >= 201103L
				explicit
#		endif
				operator bool() const KERBAL_NOEXCEPT
				{
					return this->k_ptr != NULL;
				}

				KERBAL_CONSTEXPR20
				element_type & operator[](std::size_t i) const KERBAL_NOEXCEPT
				{
					return this->k_ptr[i];
				}

				KERBAL_CONSTEXPR14
				deleter_type & get_deleter() KERBAL_NOEXCEPT
				{
					return deleter_compress_helper::member();
				}

				KERBAL_CONSTEXPR
				const deleter_type & get_deleter() const KERBAL_NOEXCEPT
				{
					return deleter_compress_helper::member();
				}

				KERBAL_CONSTEXPR20
				void swap(unique_ptr & with)
					KERBAL_CONDITIONAL_NOEXCEPT(
						noexcept(
							kerbal::algorithm::swap(
								kerbal::utility::declval<deleter_type &>(),
								kerbal::utility::declval<deleter_type &>()
							)
						) &&
						noexcept(
							kerbal::algorithm::swap(
								kerbal::utility::declval<deleter_type &>(),
								kerbal::utility::declval<deleter_type &>()
							)
						)
					)
				{
					kerbal::algorithm::swap(this->get_deleter(), with.get_deleter());
					kerbal::algorithm::swap(this->k_ptr, with.k_ptr);
				}

		};



#	if __cplusplus >= 201103L

		template <typename T, typename ... Args>
		KERBAL_CONSTEXPR20
		kerbal::memory::unique_ptr<T>
		make_unique(Args && ... args)
		{
			return kerbal::memory::unique_ptr<T>(new T(kerbal::utility::forward<Args>(args)...));
		}

#	else

#	define EMPTY
#	define REMAINF(exp) exp
#	define LEFT_JOIN_COMMA(exp) , exp
#	define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#	define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#	define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#	define FBODY(i) \
		template <typename T KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
		kerbal::memory::unique_ptr<T> \
		make_unique(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
		{ \
			return kerbal::memory::unique_ptr<T>(new T(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i))); \
		} \

		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
		KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#	undef EMPTY
#	undef REMAINF
#	undef LEFT_JOIN_COMMA
#	undef TARGS_DECL
#	undef ARGS_DECL
#	undef ARGS_USE
#	undef CONSTRUCT_EXTERNAL
#	undef FBODY

#	endif



		template <
			typename T1, typename Deleter1,
			typename T2, typename Deleter2
		>
		KERBAL_CONSTEXPR20
		bool operator==(
			const unique_ptr<T1, Deleter1> & x,
			const unique_ptr<T2, Deleter2> & y
		) KERBAL_NOEXCEPT
		{
			return x.get() == y.get();
		}

		template <
			typename T1, typename Deleter1,
			typename T2, typename Deleter2
		>
		KERBAL_CONSTEXPR20
		bool operator!=(
			const unique_ptr<T1, Deleter1> & x,
			const unique_ptr<T2, Deleter2> & y
		) KERBAL_NOEXCEPT
		{
			return x.get() != y.get();
		}

		template <
			typename T1, typename Deleter1,
			typename T2, typename Deleter2
		>
		KERBAL_CONSTEXPR20
		bool operator<(
			const unique_ptr<T1, Deleter1> & x,
			const unique_ptr<T2, Deleter2> & y
		) KERBAL_NOEXCEPT
		{
			return x.get() < y.get();
		}

		template <
			typename T1, typename Deleter1,
			typename T2, typename Deleter2
		>
		KERBAL_CONSTEXPR20
		bool operator>(
			const unique_ptr<T1, Deleter1> & x,
			const unique_ptr<T2, Deleter2> & y
		) KERBAL_NOEXCEPT
		{
			return x.get() > y.get();
		}

		template <
			typename T1, typename Deleter1,
			typename T2, typename Deleter2
		>
		KERBAL_CONSTEXPR20
		bool operator<=(
			const unique_ptr<T1, Deleter1> & x,
			const unique_ptr<T2, Deleter2> & y
		) KERBAL_NOEXCEPT
		{
			return x.get() <= y.get();
		}

		template <
			typename T1, typename Deleter1,
			typename T2, typename Deleter2
		>
		KERBAL_CONSTEXPR20
		bool operator>=(
			const unique_ptr<T1, Deleter1> & x,
			const unique_ptr<T2, Deleter2> & y
		) KERBAL_NOEXCEPT
		{
			return x.get() >= y.get();
		}

	} // namespace memory


	namespace algorithm
	{

		template <typename T, typename Deleter>
		KERBAL_CONSTEXPR20
		void swap(
			kerbal::memory::unique_ptr<T, Deleter> & lhs,
			kerbal::memory::unique_ptr<T, Deleter> & rhs
		)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs.swap(rhs)))
		{
			lhs.swap(rhs);
		}

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <typename T, typename Deleter>
	KERBAL_CONSTEXPR20
	void swap(
		kerbal::memory::unique_ptr<T, Deleter> & lhs,
		kerbal::memory::unique_ptr<T, Deleter> & rhs
	)
		KERBAL_CONDITIONAL_NOEXCEPT(noexcept(lhs.swap(rhs)))
	{
		lhs.swap(rhs);
	}

KERBAL_NAMESPACE_STD_END

#endif // KERBAL_MEMORY_UNIQUE_PTR_HPP
