/**
 * @file       equality_comparable_any.hpp
 * @brief      
 * @date       2019-7-14
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ANY_EQUALITY_COMPARABLE_ANY_HPP
#define KERBAL_ANY_EQUALITY_COMPARABLE_ANY_HPP

#include <kerbal/any/any.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/hash/hash.hpp>
#include <kerbal/utility/addressof.hpp>

namespace kerbal
{

	namespace any
	{

		template <typename Tp>
		struct equality_comparable_any_control_block;

		struct equality_comparable_any_control_block_base
		{
			template< class U >
			struct rebind
			{
				typedef equality_comparable_any_control_block<U> other;
			};


#	if __cplusplus < 201103L

			virtual ~equality_comparable_any_control_block_base()
			{
			}

#	else

			virtual ~equality_comparable_any_control_block_base() = default;

#	endif

			virtual equality_comparable_any_control_block_base* clone() const = 0;
			virtual const std::type_info& type() const KERBAL_NOEXCEPT = 0;

#	if __cplusplus >= 201103L

			std::type_index type_index() const noexcept
			{
				return std::type_index(this->type());
			}

#	endif

			virtual std::size_t hash() const = 0;
			virtual bool operator==(const equality_comparable_any_control_block_base & with) const = 0;
			virtual bool operator!=(const equality_comparable_any_control_block_base & with) const = 0;

		};

		template <typename Tp>
		struct equality_comparable_any_control_block: equality_comparable_any_control_block_base
		{
				Tp value;
				
				explicit equality_comparable_any_control_block(const Tp & value) :
						value(value)
				{
				}

#	if __cplusplus >= 201103L

				explicit equality_comparable_any_control_block(Tp && value) :
						value(std::forward<Tp>(value))
				{
				}

				template <typename ... Args>
				explicit equality_comparable_any_control_block(Args && ... args) :
						value(std::forward<Args>(args)...)
				{
				}

#	endif

				virtual equality_comparable_any_control_block_base* clone() const
				{
					return new equality_comparable_any_control_block(this->value);
				}

				virtual const std::type_info& type() const KERBAL_NOEXCEPT
				{
					return typeid(Tp);
				}
				
				virtual std::size_t hash() const
				{
					return kerbal::data_struct::hash<Tp>()(this->value);
				}
				
				virtual bool operator==(const control_block_base & with) const
				{
					this->value == static_cast<const control_block&>(with).value;
				}
				
				virtual bool operator!=(const control_block_base & with) const
				{
					this->value != static_cast<const control_block&>(with).value;
				}

		};

		class equality_comparable_any: public kerbal::any::__any_base<control_block_base>
		{
			public:

				KERBAL_CONSTEXPR equality_comparable_any() KERBAL_NOEXCEPT :
						__any_base()
				{
				}

				template <typename Tp>
				explicit equality_comparable_any(Tp & value) :
						__any_base(value)
				{
				}

				template <typename Tp>
				explicit equality_comparable_any(const Tp & value) :
						__any_base(value)
				{
				}

				equality_comparable_any(const equality_comparable_any & src) :
						__any_base(src)
				{
				}

#	if __cplusplus >= 201103L

				template <typename Tp>
				explicit equality_comparable_any(Tp && value) :
						__any_base(std::forward<Tp>(value))
				{
				}

				equality_comparable_any(equality_comparable_any && src) noexcept :
						__any_base(src)
				{
				}

#	endif

				template <typename Tp>
				equality_comparable_any& operator=(Tp & value)
				{
					this->assign(value);
					return *this;
				}

				template <typename Tp>
				equality_comparable_any& operator=(const Tp & value)
				{
					this->assign(value);
					return *this;
				}

				equality_comparable_any& operator=(const equality_comparable_any & src)
				{
					this->assign(src);
					return *this;
				}

#	if __cplusplus >= 201103L

				equality_comparable_any& operator=(equality_comparable_any && src)
				{
					this->assign(kerbal::compatibility::move(src));
					return *this;
				}

#	endif

				template <typename Tp>
				friend Tp* any_cast(equality_comparable_any * operand) KERBAL_NOEXCEPT;

				template <typename Tp>
				friend const Tp* any_cast(const equality_comparable_any * operand) KERBAL_NOEXCEPT;

		};

		template <typename Tp>
		Tp* any_cast(equality_comparable_any * operand) KERBAL_NOEXCEPT
		{
			return operand->type() != typeid(Tp) ? NULL : kerbal::utility::addressof(operand->__get_control_block_ref<Tp>().value);
		}

		template <typename Tp>
		const Tp* any_cast(const equality_comparable_any * operand) KERBAL_NOEXCEPT
		{
			return operand->type() != typeid(Tp) ? NULL : kerbal::utility::addressof(operand->__get_control_block_ref<Tp>().value);
		}

		template <typename Tp>
		Tp any_cast(equality_comparable_any & operand)
		{
			typedef typename kerbal::type_traits::remove_reference<Tp>::type value_type;
			value_type * ptr_to_value = any_cast<value_type>(kerbal::utility::addressof(operand));
			if (ptr_to_value == NULL) {
				kerbal::equality_comparable_any::bad_any_cast::throw_this_exception();
			}
			return *ptr_to_value;
		}

		template <typename Tp>
		const Tp any_cast(const equality_comparable_any & operand)
		{
			typedef typename kerbal::type_traits::remove_reference<Tp>::type value_type;
			const value_type * ptr_to_value = any_cast<value_type>(kerbal::utility::addressof(operand));
			if (ptr_to_value == NULL) {
				kerbal::equality_comparable_any::bad_any_cast::throw_this_exception();
			}
			return *ptr_to_value;
		}

#	if __cplusplus >= 201103L

		template <typename Tp>
		const Tp any_cast(equality_comparable_any && operand)
		{
			typedef typename kerbal::type_traits::remove_reference<Tp>::type value_type;
			const value_type * ptr_to_value = any_cast<Tp>(kerbal::utility::addressof(operand));
			if (ptr_to_value == NULL) {
				kerbal::equality_comparable_any::bad_any_cast::throw_this_exception();
			}
			return *ptr_to_value;
		}

#	endif

	} // namespace any

} // namespace kerbal

#endif // KERBAL_ANY_EQUALITY_COMPARABLE_ANY_HPP
