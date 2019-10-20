/**
 * @file       test_case_vector.hpp
 * @brief      
 * @date       2019-7-28
 * @author     peter
 * @copyright
 *      peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TEST_TEST_CASE_VECTOR_HPP_
#define KERBAL_TEST_TEST_CASE_VECTOR_HPP_

#include <kerbal/compatibility/noexcept.hpp>

#include <cstdio>
#include <cstdlib>
#include <cstddef>

namespace kerbal
{
	namespace test
	{
		struct unit_info
		{
				enum running_result
				{
					test_passed,
					test_failed,
				};

				typedef running_result (*test_unit_type) (int, char*[]);

				const char * case_name;
				test_unit_type case_call_ptr;
				const char * case_description;

				unit_info(const char * case_name, test_unit_type case_call_ptr, const char * case_description) KERBAL_NOEXCEPT :
						case_name(case_name), case_call_ptr(case_call_ptr), case_description(case_description)
				{
				}

#			if __cplusplus >= 201103L
				~unit_info() noexcept = default;
#			else

				~unit_info() KERBAL_NOEXCEPT
				{
				}

#			endif

		};

		struct test_case_vector_default_allocator
		{
//			std::allocator
			protected:
				typedef unit_info _Tp;
			public:
				typedef _Tp        value_type;
				typedef _Tp*       pointer;
				typedef const _Tp* const_pointer;
				typedef _Tp&       reference;
				typedef const _Tp& const_reference;
				typedef size_t     size_type;
				typedef ptrdiff_t  difference_type;

#			if __cplusplus >= 201103L
				constexpr test_case_vector_default_allocator() noexcept = default;
				~test_case_vector_default_allocator() noexcept = default;
#			endif

				// __p is not permitted to be a null pointer.
				void
				deallocate(pointer __p, size_type) KERBAL_NOEXCEPT
				{
#			if __cpp_aligned_new
					if (alignof(value_type) > __STDCPP_DEFAULT_NEW_ALIGNMENT__)
					{
						::operator delete(__p, std::align_val_t(alignof(value_type)));
						return;
					}
#			endif
					::operator delete(__p);
				}

				size_type max_size() const KERBAL_NOEXCEPT
				{
					return size_t(-1) / sizeof(value_type);
				}

#			if __cplusplus >= 201103L

				template <typename... _Args>
				void construct(pointer __p, _Args&&... __args)
				{
					::new((void *)__p) value_type(std::forward<_Args>(__args)...);
				}

#			else
				// _GLIBCXX_RESOLVE_LIB_DEFECTS
				// 402. wrong new expression in [some_] allocator::construct
				void
				construct(pointer __p, const_reference __val)
				{
					::new((void *)__p) value_type(__val);
				}

#			endif

				void destroy(pointer __p)
				{
					__p->~value_type();
				}

		};

		class test_case_vector
		{
			protected:
				typedef unit_info _Tp;
			public:
				typedef _Tp        value_type;
				typedef _Tp*       pointer;
				typedef const _Tp* const_pointer;
				typedef _Tp&       reference;
				typedef const _Tp& const_reference;
				typedef size_t     size_type;
				typedef ptrdiff_t  difference_type;

			private:
				pointer p;
				test_case_vector_default_allocator alloc;

			public:
				test_case_vector() KERBAL_NOEXCEPT :
						p(NULL)
				{
				}


		};

	} /* namespace test */

} /* namespace kerbal */


#endif /* KERBAL_TEST_TEST_CASE_VECTOR_HPP_ */
