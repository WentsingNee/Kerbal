/**
 * @file       any.hpp
 * @brief      
 * @date       2019-7-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ANY_ANY_HPP
#define KERBAL_ANY_ANY_HPP

#include <kerbal/any/any_base.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/utility/addressof.hpp>

namespace kerbal
{

	namespace any
	{

		template <typename Tp>
		struct any_control_block;

		struct any_control_block_base
		{
			template< class U >
			struct rebind
			{
				typedef any_control_block<U> other;
			};

#	if __cplusplus < 201103L

			virtual ~any_control_block_base()
			{
			}

#	else

			virtual ~any_control_block_base() = default;

#	endif

			virtual any_control_block_base* clone() const = 0;
			virtual const std::type_info& type() const KERBAL_NOEXCEPT = 0;

#	if __cplusplus >= 201103L

			std::type_index type_index() const noexcept
			{
				return std::type_index(this->type());
			}

#	endif

		};

		template <typename Tp>
		struct any_control_block: any_control_block_base
		{
				Tp value;
				
				explicit any_control_block(const Tp & value) :
						value(value)
				{
				}

#	if __cplusplus >= 201103L

				explicit any_control_block(Tp && value) :
						value(std::forward<Tp>(value))
				{
				}

				template <typename ... Args>
				explicit any_control_block(Args && ... args) :
						value(std::forward<Args>(args)...)
				{
				}

#	endif

				virtual any_control_block_base* clone() const
				{
					return new any_control_block(this->value);
				}

				virtual const std::type_info& type() const KERBAL_NOEXCEPT
				{
					return typeid(Tp);
				}
		};

		class any: public kerbal::any::__any_base<any_control_block_base>
		{
			public:

				KERBAL_CONSTEXPR any() KERBAL_NOEXCEPT :
						__any_base()
				{
				}

				template <typename Tp>
				explicit any(Tp & value) :
						__any_base(value)
				{
				}

				template <typename Tp>
				explicit any(const Tp & value) :
						__any_base(value)
				{
				}

				any(const any & src) :
						__any_base(src)
				{
				}

#	if __cplusplus >= 201103L

				template <typename Tp>
				explicit any(Tp && value) :
						__any_base(std::forward<Tp>(value))
				{
				}

				any(any && src) noexcept :
						__any_base(src)
				{
				}

#	endif

				template <typename Tp>
				any& operator=(Tp & value)
				{
					this->assign(value);
					return *this;
				}

				template <typename Tp>
				any& operator=(const Tp & value)
				{
					this->assign(value);
					return *this;
				}

				any& operator=(const any & src)
				{
					this->assign(src);
					return *this;
				}

#	if __cplusplus >= 201103L

				any& operator=(any && src)
				{
					this->assign(kerbal::compatibility::move(src));
					return *this;
				}

#	endif

				template <typename Tp>
				friend Tp* any_cast(any * operand) KERBAL_NOEXCEPT;

				template <typename Tp>
				friend const Tp* any_cast(const any * operand) KERBAL_NOEXCEPT;

		};

		template <typename Tp>
		Tp* any_cast(any * operand) KERBAL_NOEXCEPT
		{
			return operand->type() != typeid(Tp) ? NULL : kerbal::utility::addressof(operand->__get_control_block_ref<Tp>().value);
		}

		template <typename Tp>
		const Tp* any_cast(const any * operand) KERBAL_NOEXCEPT
		{
			return operand->type() != typeid(Tp) ? NULL : kerbal::utility::addressof(operand->__get_control_block_ref<Tp>().value);
		}

		template <typename Tp>
		Tp any_cast(any & operand)
		{
			typedef typename kerbal::type_traits::remove_reference<Tp>::type value_type;
			value_type * ptr_to_value = any_cast<value_type>(kerbal::utility::addressof(operand));
			if (ptr_to_value == NULL) {
				kerbal::any::bad_any_cast::throw_this_exception();
			}
			return *ptr_to_value;
		}

		template <typename Tp>
		const Tp any_cast(const any & operand)
		{
			typedef typename kerbal::type_traits::remove_reference<Tp>::type value_type;
			const value_type * ptr_to_value = any_cast<value_type>(kerbal::utility::addressof(operand));
			if (ptr_to_value == NULL) {
				kerbal::any::bad_any_cast::throw_this_exception();
			}
			return *ptr_to_value;
		}

#	if __cplusplus >= 201103L

		template <typename Tp>
		const Tp any_cast(any && operand)
		{
			typedef typename kerbal::type_traits::remove_reference<Tp>::type value_type;
			const value_type * ptr_to_value = any_cast<Tp>(kerbal::utility::addressof(operand));
			if (ptr_to_value == NULL) {
				kerbal::any::bad_any_cast::throw_this_exception();
			}
			return *ptr_to_value;
		}

#	endif

	} // namespace any

} // namespace kerbal


#endif // KERBAL_ANY_ANY_HPP
