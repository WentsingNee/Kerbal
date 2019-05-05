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

namespace kerbal
{

	namespace data_struct
	{

		template <typename Type, typename AlignedStoragePolicy = kerbal::type_traits::aligned_storage<sizeof(Type), KERBAL_ALIGNOF(Type)> >
		class raw_storage_impl: kerbal::utility::noncopyable
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
				raw_storage_impl() KERBAL_NOEXCEPT
				{
				}

		# if __cplusplus < 201103L

				void construct()
				{
					new (raw_pointer()) value_type();
				}

				template <typename Arg0>
				void construct(const Arg0 & arg0)
				{
					new (raw_pointer()) value_type(arg0);
				}

				template <typename Arg0, typename Arg1>
				void construct(const Arg0 & arg0, const Arg1& arg1)
				{
					new (raw_pointer()) value_type(arg0, arg1);
				}

				template <typename Arg0, typename Arg1, typename Arg2>
				void construct(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2)
				{
					new (raw_pointer()) value_type(arg0, arg1, arg2);
				}

				template <typename Arg0, typename Arg1, typename Arg2, typename Arg3>
				void construct(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2, const Arg3& arg3)
				{
					new (raw_pointer()) value_type(arg0, arg1, arg2, arg3);
				}

				template <typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
				void construct(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2, const Arg3& arg3, const Arg4 & arg4)
				{
					new (raw_pointer()) value_type(arg0, arg1, arg2, arg3, arg4);
				}

		# else

				template <typename ... Args>
				void construct(Args&&... args)
				{
					new (raw_pointer()) value_type(std::forward<Args>(args)...);
				}

		# endif

				void destroy()
				{
					raw_pointer()->~Type();
				}

				reference raw_value() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return *raw_pointer();
				}

				const_reference raw_value() const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return *raw_pointer();
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

		template <typename Type, std::size_t ArrayLength, typename AlignedStoragePolicy =
				kerbal::type_traits::aligned_storage<sizeof(Type[ArrayLength]), KERBAL_ALIGNOF(Type[ArrayLength])> >
		class raw_array_storage_impl: kerbal::utility::noncopyable
		{
			public:
				typedef Type (value_type)[ArrayLength];
				typedef value_type& reference;
				typedef const value_type& const_reference;
				typedef value_type* pointer;
				typedef const value_type* const_pointer;
				typedef typename AlignedStoragePolicy::type aligned_storage_type;

		#	if __cplusplus >= 201103L
				typedef value_type&& rvalue_reference;
				typedef const value_type&& const_rvalue_reference;
		#	endif

			struct element
			{
						typedef Type value_type;
						typedef value_type& reference;
						typedef const value_type& const_reference;
						typedef value_type* pointer;
						typedef const value_type* const_pointer;

				#	if __cplusplus >= 201103L
						typedef value_type&& rvalue_reference;
						typedef const value_type&& const_rvalue_reference;
				#	endif
			};

			protected:
				aligned_storage_type storage;

			public:
				raw_array_storage_impl() KERBAL_NOEXCEPT
				{
				}

				reference raw_value() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return *raw_pointer();
				}

				const_reference raw_value() const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return *raw_pointer();
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
//					return reinterpret_cast<pointer>(&(this->storage));
					return reinterpret_cast<pointer>(this->storage.__data);
				}

				const_pointer raw_pointer() const KERBAL_NOEXCEPT
				{
//					return reinterpret_cast<const_pointer>(&(this->storage));
					return reinterpret_cast<const_pointer>(this->storage.__data);
				}


		# if __cplusplus < 201103L

				void construct_at(size_t index)
				{
					new (raw_pointer_at(index)) typename element::value_type();
				}

				template <typename Arg0>
				void construct_at(size_t index, const Arg0 & arg0)
				{
					new (raw_pointer_at(index)) typename element::value_type(arg0);
				}

				template <typename Arg0, typename Arg1>
				void construct_at(size_t index, const Arg0 & arg0, const Arg1& arg1)
				{
					new (raw_pointer_at(index)) typename element::value_type(arg0, arg1);
				}

				template <typename Arg0, typename Arg1, typename Arg2>
				void construct_at(size_t index, const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2)
				{
					new (raw_pointer_at(index)) typename element::value_type(arg0, arg1, arg2);
				}

				template <typename Arg0, typename Arg1, typename Arg2, typename Arg3>
				void construct_at(size_t index, const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2, const Arg3& arg3)
				{
					new (raw_pointer_at(index)) typename element::value_type(arg0, arg1, arg2, arg3);
				}

				template <typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
				void construct_at(size_t index, const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2, const Arg3& arg3, const Arg4 & arg4)
				{
					new (raw_pointer_at(index)) typename element::value_type(arg0, arg1, arg2, arg3, arg4);
				}

		# else

				template <typename ... Args>
				void construct_at(std::size_t index, Args&&... args)
				{
					new (raw_pointer_at(index)) typename element::value_type(std::forward<Args>(args)...);
				}

		# endif

				void destroy_at(std::size_t index)
				{
					raw_pointer_at(index)->~Type();
				}

				typename element::reference raw_value_at(std::size_t index) KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return *raw_pointer_at(index);
				}

				typename element::const_reference raw_value_at(std::size_t index) const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return *raw_pointer_at(index);
				}

		# if __cplusplus >= 201103L

				typename element::rvalue_reference raw_value_at(std::size_t index) && noexcept
				{
					return static_cast<typename element::rvalue_reference>(*raw_pointer_at(index));
				}

				typename element::const_rvalue_reference raw_value_at(std::size_t index) const && noexcept
				{
					return static_cast<typename element::const_rvalue_reference>(*raw_pointer_at(index));
				}

		# endif

				typename element::pointer raw_pointer_at(std::size_t index) KERBAL_NOEXCEPT
				{
					return *raw_pointer() + index;
				}

				typename element::const_pointer raw_pointer_at(std::size_t index) const KERBAL_NOEXCEPT
				{
					return *raw_pointer() + index;
				}

		};


		template <typename Type, typename AlignedStoragePolicy = kerbal::type_traits::aligned_storage<sizeof(Type), KERBAL_ALIGNOF(Type)> >
		class raw_storage: public raw_storage_impl<Type, AlignedStoragePolicy>
		{
		};


		template <typename Type, std::size_t ArrayLength >
		class raw_storage<Type[ArrayLength]>:
						public raw_array_storage_impl<Type, ArrayLength,
							kerbal::type_traits::aligned_storage<sizeof(Type[ArrayLength]), KERBAL_ALIGNOF(Type[ArrayLength])> >
		{
		};

	} // namespace data_struct

} // namespace kerbal


#endif /* INCLUDE_KERBAL_DATA_STRUCT_RAW_STORAGE_HPP_ */
