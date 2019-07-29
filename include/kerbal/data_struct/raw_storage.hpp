/*
 * raw_storage.hpp
 *
 *  Created on: 2019年4月19日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_DATA_STRUCT_RAW_STORAGE_HPP_
#define INCLUDE_KERBAL_DATA_STRUCT_RAW_STORAGE_HPP_

#include <utility>
#include <kerbal/utility/noncopyable.hpp>
#include <kerbal/type_traits/aligned_storage.hpp>
#include <kerbal/compatibility/compatibility_macro.hpp>
#include <kerbal/type_traits/type_traits_details/array_traits.hpp>
#include <kerbal/type_traits/type_traits_details/enable_if.hpp>

#if __cplusplus >= 201103L
# include <type_traits>
#else
# include <kerbal/type_traits/type_traits_details/fundamental_deduction.hpp>
#endif

namespace kerbal
{

	namespace data_struct
	{

		template <typename Type>
		struct as_trivial;

#	if __cplusplus >= 201103L

		template <typename Type>
		struct as_trivial: std::is_pod<typename kerbal::type_traits::remove_all_extents<Type> >
		{
		};

#	else

		template <typename Type>
		struct as_trivial:
				kerbal::type_traits::bool_constant<
					kerbal::type_traits::is_fundamental<typename kerbal::type_traits::remove_all_extents<Type> >::value ||
					kerbal::type_traits::is_pointer<typename kerbal::type_traits::remove_all_extents<Type> >::value
				>
		{
		};

#	endif

		template <typename Type, typename AlignedStoragePolicy = kerbal::type_traits::aligned_storage<sizeof(Type), KERBAL_ALIGNOF(Type)>,
				bool is_trival = as_trivial<Type>::value>
		class raw_storage;


		template <typename Type, typename AlignedStoragePolicy>
		class raw_storage<Type, AlignedStoragePolicy, true>: kerbal::utility::noncopyable
		{
			public:
				typedef Type value_type;
				typedef value_type& reference;
				typedef const value_type& const_reference;
				typedef value_type* pointer;
				typedef const value_type* const_pointer;

#	if __cplusplus >= 201103L
				typedef value_type&& rvalue_reference;
				typedef const value_type&& const_rvalue_reference;
#	endif

			protected:
				value_type storage;

			public:
				KERBAL_CONSTEXPR raw_storage() KERBAL_NOEXCEPT
				{
				}

# if __cplusplus < 201103L

				reference construct() KERBAL_NOEXCEPT
				{
					return this->raw_value() = value_type();
				}

				template <typename Arg0>
				reference construct(const Arg0 & arg0) KERBAL_NOEXCEPT
				{
					return this->raw_value() = value_type(arg0);
				}

				template <typename Arg0, typename Arg1>
				reference construct(const Arg0 & arg0, const Arg1& arg1) KERBAL_NOEXCEPT
				{
					return this->raw_value() = value_type(arg0, arg1);
				}

				template <typename Arg0, typename Arg1, typename Arg2>
				reference construct(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2) KERBAL_NOEXCEPT
				{
					return this->raw_value() = value_type(arg0, arg1, arg2);
				}

				template <typename Arg0, typename Arg1, typename Arg2, typename Arg3>
				reference construct(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2, const Arg3& arg3) KERBAL_NOEXCEPT
				{
					return this->raw_value() = value_type(arg0, arg1, arg2, arg3);
				}

				template <typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
				reference construct(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2, const Arg3& arg3, const Arg4 & arg4) KERBAL_NOEXCEPT
				{
					return this->raw_value() = value_type(arg0, arg1, arg2, arg3, arg4);
				}

# else

				template <typename ... Args>
				constexpr
				typename kerbal::type_traits::enable_if<!kerbal::type_traits::is_array<value_type>::value, reference>::type
				construct(Args&&... args) noexcept
				{
					return this->raw_value() = value_type(std::forward<Args>(args)...);
				}

# endif

				KERBAL_CONSTEXPR14 void destroy() KERBAL_NOEXCEPT
				{
				}

				KERBAL_CONSTEXPR reference raw_value() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return *this->raw_pointer();
				}

				KERBAL_CONSTEXPR const_reference raw_value() const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return *this->raw_pointer();
				}

# if __cplusplus >= 201103L

				constexpr rvalue_reference raw_value() && noexcept
				{
					return static_cast<rvalue_reference>(*raw_pointer());
				}

				constexpr const_rvalue_reference raw_value() const && noexcept
				{
					return static_cast<const_rvalue_reference>(*raw_pointer());
				}

# endif

				KERBAL_CONSTEXPR pointer raw_pointer() KERBAL_NOEXCEPT
				{
					return reinterpret_cast<pointer>(&(this->storage));
				}

				KERBAL_CONSTEXPR const_pointer raw_pointer() const KERBAL_NOEXCEPT
				{
					return reinterpret_cast<const_pointer>(&(this->storage));
				}

		};



		template <typename Type, typename AlignedStoragePolicy, size_t N>
		class raw_storage<Type[N], AlignedStoragePolicy, true>: kerbal::utility::noncopyable
		{
			public:
				typedef Type value_type [N];
				typedef value_type& reference;
				typedef const value_type& const_reference;
				typedef value_type* pointer;
				typedef const value_type* const_pointer;

#	if __cplusplus >= 201103L
				typedef value_type&& rvalue_reference;
				typedef const value_type&& const_rvalue_reference;
#	endif

			protected:
				value_type storage;

			public:
				KERBAL_CONSTEXPR raw_storage() KERBAL_NOEXCEPT
				{
				}

				reference construct() KERBAL_NOEXCEPT
				{
					size_t i = 0;
					while (i != N) {
						new (this->storage + i) Type();
						++i;
					}
					return this->raw_value();
				}

				KERBAL_CONSTEXPR14 void destroy() KERBAL_NOEXCEPT
				{
				}

				KERBAL_CONSTEXPR reference raw_value() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return *this->raw_pointer();
				}

				KERBAL_CONSTEXPR const_reference raw_value() const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return *this->raw_pointer();
				}

# if __cplusplus >= 201103L

				constexpr rvalue_reference raw_value() && noexcept
				{
					return static_cast<rvalue_reference>(*raw_pointer());
				}

				constexpr const_rvalue_reference raw_value() const && noexcept
				{
					return static_cast<const_rvalue_reference>(*raw_pointer());
				}

# endif

				KERBAL_CONSTEXPR pointer raw_pointer() KERBAL_NOEXCEPT
				{
					return reinterpret_cast<pointer>(&(this->storage));
				}

				KERBAL_CONSTEXPR const_pointer raw_pointer() const KERBAL_NOEXCEPT
				{
					return reinterpret_cast<const_pointer>(&(this->storage));
				}

		};


		template <typename Type, typename AlignedStoragePolicy>
		class raw_storage<Type, AlignedStoragePolicy, false>: kerbal::utility::noncopyable
		{
			public:
				typedef Type value_type;
				typedef value_type& reference;
				typedef const value_type& const_reference;
				typedef value_type* pointer;
				typedef const value_type* const_pointer;
				typedef typename AlignedStoragePolicy::type aligned_storage_type;

		#	if __cplusplus >= 201103L
				typedef value_type&& rvalue_reference;
				typedef const value_type&& const_rvalue_reference;
		#	endif

			protected:
				aligned_storage_type storage;

			public:
				raw_storage() KERBAL_NOEXCEPT
				{
				}

		# if __cplusplus < 201103L

				reference construct()
				{
					new (raw_pointer()) value_type();
					return this->raw_value();
				}

				template <typename Arg0>
				reference construct(const Arg0 & arg0)
				{
					new (raw_pointer()) value_type(arg0);
					return this->raw_value();
				}

				template <typename Arg0, typename Arg1>
				reference construct(const Arg0 & arg0, const Arg1& arg1)
				{
					new (raw_pointer()) value_type(arg0, arg1);
					return this->raw_value();
				}

				template <typename Arg0, typename Arg1, typename Arg2>
				reference construct(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2)
				{
					new (raw_pointer()) value_type(arg0, arg1, arg2);
					return this->raw_value();
				}

				template <typename Arg0, typename Arg1, typename Arg2, typename Arg3>
				reference construct(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2, const Arg3& arg3)
				{
					new (raw_pointer()) value_type(arg0, arg1, arg2, arg3);
					return this->raw_value();
				}

				template <typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
				reference construct(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2, const Arg3& arg3, const Arg4 & arg4)
				{
					new (raw_pointer()) value_type(arg0, arg1, arg2, arg3, arg4);
					return this->raw_value();
				}

		# else

				template <typename ... Args>
				reference construct(Args&&... args)
				{
					new (raw_pointer()) value_type(std::forward<Args>(args)...);
					return this->raw_value();
				}

		# endif

				void destroy()
				{
					raw_pointer()->~Type();
				}

				reference raw_value() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return *this->raw_pointer();
				}

				const_reference raw_value() const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return *this->raw_pointer();
				}

# if __cplusplus >= 201103L

				rvalue_reference raw_value() && noexcept
				{
					return static_cast<rvalue_reference>(*raw_pointer());
				}

				const_rvalue_reference raw_value() const && noexcept
				{
					return static_cast<const_rvalue_reference>(*raw_pointer());
				}

# endif

				pointer raw_pointer() KERBAL_NOEXCEPT
				{
					return reinterpret_cast<pointer>(&(this->storage));
				}

				const_pointer raw_pointer() const KERBAL_NOEXCEPT
				{
					return reinterpret_cast<const_pointer>(&(this->storage));
				}

		};

		template <typename Type, typename AlignedStoragePolicy, size_t N>
		class raw_storage<Type[N], AlignedStoragePolicy, false>: kerbal::utility::noncopyable
		{
			public:
				typedef Type value_type [N];
				typedef value_type& reference;
				typedef const value_type& const_reference;
				typedef value_type* pointer;
				typedef const value_type* const_pointer;
				typedef typename AlignedStoragePolicy::type aligned_storage_type;

		#	if __cplusplus >= 201103L
				typedef value_type&& rvalue_reference;
				typedef const value_type&& const_rvalue_reference;
		#	endif

			protected:
				aligned_storage_type storage;

			public:
				raw_storage() KERBAL_NOEXCEPT
				{
				}

				reference construct()
				{
					size_t i = 0;
					while (i != N) {
						new (raw_pointer()[i]) Type();
						++i;
					}
					return this->raw_value();
				}

				void destroy()
				{
					size_t i = N;
					while (i != 0) {
						--i;
						raw_pointer()[i]->~Type();
					}
				}

				reference raw_value() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return *this->raw_pointer();
				}

				const_reference raw_value() const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return *this->raw_pointer();
				}

#		if __cplusplus >= 201103L

				rvalue_reference raw_value() && noexcept
				{
					return static_cast<rvalue_reference>(*raw_pointer());
				}

				const_rvalue_reference raw_value() const && noexcept
				{
					return static_cast<const_rvalue_reference>(*raw_pointer());
				}

#		endif

				pointer raw_pointer() KERBAL_NOEXCEPT
				{
					return reinterpret_cast<pointer>(&(this->storage));
				}

				const_pointer raw_pointer() const KERBAL_NOEXCEPT
				{
					return reinterpret_cast<const_pointer>(&(this->storage));
				}

		};

	} // namespace data_struct

} // namespace kerbal


#endif /* INCLUDE_KERBAL_DATA_STRUCT_RAW_STORAGE_HPP_ */
