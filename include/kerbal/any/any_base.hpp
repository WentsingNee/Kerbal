/**
 * @file       any_base.hpp
 * @brief      
 * @date       2019-7-24
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ANY_ANY_BASE_HPP
#define KERBAL_ANY_ANY_BASE_HPP

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/any/bad_any_cast.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/decay.hpp>
#include <kerbal/type_traits/reference_deduction.hpp>

#include <cstddef>
#include <typeinfo>
#include <utility>

#if __cplusplus >= 201103L
#	include <memory>
#	include <typeindex>
#endif

namespace kerbal
{

	namespace any
	{

		template <typename ControlBlockBaseType>
		class __any_base
		{
			protected:

				typedef ControlBlockBaseType control_block_base;

				template <typename Tp>
				struct control_block
				{
						typedef typename control_block_base::template rebind<Tp>::other type;
				};

				control_block_base *p;

				control_block_base& __get_control_block_base_ref()
				{
					return static_cast<control_block_base&>(*this->p);
				}

				const control_block_base& __get_control_block_base_ref() const
				{
					return static_cast<const control_block_base&>(*this->p);
				}
				
				template <typename Tp>
				typename control_block<Tp>::type&
				__get_control_block_ref()
				{
					return static_cast<typename control_block<Tp>::type&>(this->__get_control_block_base_ref());
				}

				template <typename Tp>
				const typename control_block<Tp>::type&
				__get_control_block_ref() const
				{
					return static_cast<const typename control_block<Tp>::type&>(this->__get_control_block_base_ref());
				}

				template <typename Tp>
				static control_block_base* __create_control_block(Tp & value)
				{
					typedef typename kerbal::type_traits::decay<Tp>::type value_type;
					return static_cast<control_block_base*>(new typename control_block<value_type>::type(value));
				}

				template <typename Tp>
				static control_block_base* __create_control_block(const Tp & value)
				{
					typedef typename kerbal::type_traits::decay<const Tp>::type value_type;
					return static_cast<control_block_base*>(new typename control_block<value_type>::type(value));
				}

#	if __cplusplus >= 201103L

				template <typename Tp>
				static control_block_base* __create_control_block(Tp && value)
				{
					using value_type = typename kerbal::type_traits::decay<Tp>::type; // TODO
					return static_cast<control_block_base*>(new typename control_block<Tp>::type(std::forward<Tp>(value)));
				}

				template <typename Tp, typename ... Args>
				static control_block_base* __create_control_block(Args&& ... args)
				{
					using value_type = typename kerbal::type_traits::decay<Tp>::type; // TODO
					return static_cast<control_block_base*>(new typename control_block<Tp>::type(std::forward<Args>(args)...));
				}

#	endif

			public:

				KERBAL_CONSTEXPR __any_base() KERBAL_NOEXCEPT :
						p(NULL)
				{
				}

				template <typename Tp>
				explicit __any_base(Tp & value) :
						p(__create_control_block(value))
				{
				}

				template <typename Tp>
				explicit __any_base(const Tp & value) :
						p(__create_control_block(value))
				{
				}

				__any_base(const __any_base & src) :
						p(src.has_value() ? src.__get_control_block_base_ref().clone() : NULL)
				{
				}

#	if __cplusplus >= 201103L

				template <typename Tp>
				explicit __any_base(Tp && value) :
						p(__create_control_block(std::forward<Tp>(value)))
				{
				}

				__any_base(__any_base && src) noexcept :
						p(src.p)
				{
					src.p = nullptr;
				}

#	endif

				~__any_base()
				{
					this->reset();
				}

				template <typename Tp>
				void assign(Tp & value)
				{
					typedef typename kerbal::type_traits::decay<Tp>::type value_type;
					if (this->type() == typeid(value_type)) {
						//this->type() couldn't be void because Tp can't be void type
						this->__get_control_block_ref<value_type>().value = value;
					} else {
						this->reset();
						this->p = __create_control_block(value);
					}
				}

				template <typename Tp>
				void assign(const Tp & value)
				{
					typedef typename kerbal::type_traits::decay<const Tp>::type value_type;
					if (this->type() == typeid(value_type)) {
						//this->type() couldn't be void because Tp can't be void type
						this->__get_control_block_ref<value_type>().value = value;
					} else {
						this->reset();
						this->p = __create_control_block(value);
					}
				}

				void assign(const __any_base & src)
				{
					this->reset();
					if (src.has_value()) {
						this->p = src.__get_control_block_base_ref().clone();
					}
				}

#	if __cplusplus >= 201103L

				template <typename Tp>
				void assign(Tp && value)
				{
					typedef typename kerbal::type_traits::decay<Tp>::type value_type;
					this->emplace<value_type>(std::forward<Tp>(value));
				}

				void assign(__any_base && src)
				{
					this->reset();
					this->p = src.p;
					src.p = nullptr;
				}

			protected:

				__any_base& operator=(const __any_base & src)
				{
					this->assign(src);
					return *this;
				}

#	if __cplusplus >= 201103L

				__any_base& operator=(__any_base && src)
				{
					this->assign(kerbal::compatibility::move(src));
					return *this;
				}

#	endif

			public:

				template <typename Tp, typename ... Args>
				typename kerbal::type_traits::decay<Tp>::type&
				emplace(Args&& ... args)
				{
					this->reset();
					typedef typename kerbal::type_traits::decay<Tp>::type value_type;
					this->p = __create_control_block<value_type>(std::forward<Args>(args)...);
					return this->__get_control_block_ref<value_type>().value;
				}

#	endif

				void reset()
				{
					delete this->p;
					this->p = NULL;
				}

				KERBAL_CONSTEXPR bool has_value() const KERBAL_NOEXCEPT
				{
					return this->p != NULL;
				}

				const std::type_info& type() const KERBAL_NOEXCEPT
				{
					return this->has_value() ? this->__get_control_block_base_ref().type() : typeid(void);
				}

#	if __cplusplus >= 201103L

				std::type_index type_index() const KERBAL_NOEXCEPT
				{
					return std::type_index(this->type());
				}

#	endif

				void swap(__any_base & with) KERBAL_NOEXCEPT
				{
					kerbal::algorithm::swap(this->p, with.p);
				}
				
		};

	} // namespace any

} // namespace kerbal


#endif // KERBAL_ANY_ANY_BASE_HPP
