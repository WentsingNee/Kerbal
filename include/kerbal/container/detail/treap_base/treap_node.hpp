/**
 * @file       treap_node.hpp
 * @brief
 * @date       2021-06-13
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_TREAP_BASE_TREAP_NODE_HPP
#define KERBAL_CONTAINER_DETAIL_TREAP_BASE_TREAP_NODE_HPP

#include <kerbal/container/detail/treap_base/treap.fwd.hpp>

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/method_overload_tag.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/utility/in_place.hpp>

#include <cstddef>


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename W>
			struct treap_head_node
			{
					typedef treap_node_base<W> treap_node_base;

					treap_node_base * left;

				protected:
					KERBAL_CONSTEXPR
					treap_head_node() KERBAL_NOEXCEPT :
							left(NULL)
					{
					}
			};

			template <typename W>
			struct treap_node_base: public treap_head_node<W>
			{
				private:
					typedef treap_head_node<W> super;
					typedef std::size_t size_type;
					typedef W weight_type;

				private:
					treap_node_base * parent;
					treap_node_base * right;
					size_type size;
					weight_type weight;

				protected:
					KERBAL_CONSTEXPR
					treap_node_base(weight_type weight) KERBAL_NOEXCEPT :
							parent(NULL), right(NULL), size(0), weight(weight)
					{
					}

					template <typename Tp>
					KERBAL_CONSTEXPR14
					treap_node<Tp> & reinterpret_as() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return static_cast<treap_node<Tp> &>(*this);
					}

					template <typename Tp>
					KERBAL_CONSTEXPR14
					const treap_node<Tp> & reinterpret_as() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return static_cast<const treap_node<Tp> &>(*this);
					}

#			if __cplusplus >= 201103L

					template <typename Tp>
					KERBAL_CONSTEXPR14
					treap_node<Tp> && reinterpret_as() && KERBAL_NOEXCEPT
					{
						return static_cast<treap_node<Tp> &&>(*this);
					}

					template <typename Tp>
					KERBAL_CONSTEXPR14
					const treap_node<Tp> && reinterpret_as() const && KERBAL_NOEXCEPT
					{
						return static_cast<const treap_node<Tp> &&>(*this);
					}

#			endif

					KERBAL_CONSTEXPR14
					treap_node_base * inorder_next() const KERBAL_NOEXCEPT
					{
						if (this->right == NULL) {
							const treap_node_base * current = this;
							bst_node_base * parent = current->parent;
							while (current != parent->left) { // warning: head doesn't have right domain!
								// is parent's right son
								current = parent;
								// std::cout << "  *" << current->reinterpret_as<int>().value << std::endl;
								parent = parent->parent;
							}
							// is parent's left son
							return parent;
						} else {
							treap_node_base * current = this->right;
							while (current->left != NULL) {
								current = current->left;
							}
							return current;
						}
					}

					KERBAL_CONSTEXPR14
					treap_node_base * inorder_prev() const KERBAL_NOEXCEPT
					{
						if (this->left == NULL) {
							const treap_node_base * current = this;
							bst_node_base * parent = current->parent;
							while (current == parent->left) { // warning: head doesn't have right domain!
								// is parent's right son
								current = parent;
								parent = parent->parent;
							}
							// is parent's left son
							return parent;
						} else {
							treap_node_base * current = this->left;
							while (current->right != NULL) {
								current = current->right;
							}
							return current;
						}
					}

			};

			template <typename T, typename W>
			struct treap_head_node : public treap_node_base<W>
			{
				public:
					typedef T value_type;

					value_type value;

				public:

#		if __cplusplus >= 201103L

					template <typename ... Args>
					KERBAL_CONSTEXPR
					explicit treap_head_node(weight_type weight, kerbal::utility::in_place_t, Args&& ... args)
										KERBAL_CONDITIONAL_NOEXCEPT(
												(std::is_nothrow_constructible<Tp, Args...>::value)
										)
							: super(weight), value(kerbal::utility::forward<Args>(args)...)
					{
					}

#		else

					explicit treap_head_node(weight_type weight, kerbal::utility::in_place_t)
							: super(weight), value()
					{
					}

					template <typename Arg0>
					explicit treap_head_node(weight_type weight, kerbal::utility::in_place_t, const Arg0 & arg0)
							: super(weight), value(arg0)
					{
					}

					template <typename Arg0, typename Arg1>
					explicit treap_head_node(weight_type weight, kerbal::utility::in_place_t, const Arg0 & arg0, const Arg1 & arg1)
							: super(weight), value(arg0, arg1)
					{
					}

					template <typename Arg0, typename Arg1, typename Arg2>
					explicit treap_head_node(weight_type weight, kerbal::utility::in_place_t, const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2)
							: super(weight), value(arg0, arg1, arg2)
					{
					}

#		endif

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_TREAP_BASE_TREAP_NODE_HPP
