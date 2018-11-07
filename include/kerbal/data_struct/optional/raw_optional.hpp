/*
 * raw_optional.hpp
 *
 *  Created on: 2018年10月26日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_BASE_RAW_OPTIONAL_HPP_
#define INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_BASE_RAW_OPTIONAL_HPP_

#include <utility>

#include <kerbal/utility/noncopyable.hpp>
#include <kerbal/compatibility/compatibility_macro.hpp>


namespace kerbal
{
	namespace data_struct
	{

		template <typename Type>
		struct raw_optional: kerbal::utility::nonassignable
		{
				typedef Type value_type;
				typedef value_type& reference;
				typedef const value_type& const_reference;
				typedef value_type* pointer;
				typedef const value_type* const_pointer;

#	if __cplusplus >= 201103L
				typedef Type&& rvalue_reference;
				typedef const Type&& const_rvalue_reference;
#	endif

				char __val[sizeof(Type)];

				raw_optional() KERBAL_NOEXCEPT
				{
				}

				explicit raw_optional(const Type & src)
				{
					construct(src);
				}

				template <typename Up>
				explicit raw_optional(const Up & src)
				{
					construct(src);
				}

# if __cplusplus >= 201103L

				explicit raw_optional(Type && src)
				{
					construct(std::forward<Type>(src));
				}

				template <typename Up>
				explicit raw_optional(Up && src)
				{
					construct(std::forward<Up>(src));
				}

# endif

				void construct()
				{
					new ((void*) (raw_pointer())) Type();
				}

				template <typename Arg0>
				void construct(const Arg0 & arg0)
				{
					new ((void*) (raw_pointer())) Type(arg0);
				}

				template <typename Arg0, typename Arg1>
				void construct(const Arg0 & arg0, const Arg1& arg1)
				{
					new ((void*) (raw_pointer())) Type(arg0, arg1);
				}

				template <typename Arg0, typename Arg1, typename Arg2>
				void construct(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2)
				{
					new ((void*) (raw_pointer())) Type(arg0, arg1, arg2);
				}

				template <typename Arg0, typename Arg1, typename Arg2, typename Arg3>
				void construct(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2, const Arg3& arg3)
				{
					new ((void*) (raw_pointer())) Type(arg0, arg1, arg2, arg3);
				}

				template <typename Arg0, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
				void construct(const Arg0 & arg0, const Arg1& arg1, const Arg2 & arg2, const Arg3& arg3, const Arg4 & arg4)
				{
					new ((void*) (raw_pointer())) Type(arg0, arg1, arg2, arg3, arg4);
				}

# if __cplusplus >= 201103L

				template <typename ... Args>
				void construct(Args&&... args)
				{
					new ((void*)(raw_pointer())) Type(std::forward<Args>(args)...);
				}

				raw_optional& operator=(raw_optional &&) = delete;
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

# 			if __cplusplus >= 201103L

				rvalue_reference raw_value() && noexcept
				{
					return std::move(*raw_pointer());
				}

				const_rvalue_reference raw_value() const && noexcept
				{
					return std::move(*raw_pointer());
				}

#			endif

				pointer raw_pointer() KERBAL_NOEXCEPT
				{
					return ((Type*) (__val));
				}

				const_pointer raw_pointer() const KERBAL_NOEXCEPT
				{
					return ((Type*) (__val));
				}
			};

	} /* namespace data_struct */

} /* namespace kerbal */


#endif /* INCLUDE_KERBAL_DATA_STRUCT_OPTIONAL_BASE_RAW_OPTIONAL_HPP_ */
