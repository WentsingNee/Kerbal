/**
 * @file       huffman_ptr.hpp
 * @brief
 * @date       huffman_ptr.hpp
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COMPRESSION_HUFFMAN_PTR_HPP
#define KERBAL_COMPRESSION_HUFFMAN_PTR_HPP

#include <kerbal/algorithm/heap.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/compatibility/static_assert.hpp>
#include <kerbal/container/static_vector.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/optional/optional.hpp>
#include <kerbal/type_traits/is_same.hpp>

#if __cplusplus < 201103L
#	include <kerbal/algorithm/modifier/fill.hpp>
#endif

#include <cstddef>

#include <kerbal/utility/compressed_pair.hpp>


namespace kerbal
{

	namespace compression
	{

		namespace detail
		{

			struct huffman_tree_node
			{
					const huffman_tree_node * left;
					const huffman_tree_node * right;
					unsigned char value;
					std::size_t weight;

					// construct merged node
					KERBAL_CONSTEXPR
					explicit huffman_tree_node(std::size_t weight) KERBAL_NOEXCEPT :
							left(NULL), right(NULL), value(0), weight(weight)
					{
					}

					// construct leaf node
					KERBAL_CONSTEXPR
					explicit huffman_tree_node(unsigned value, std::size_t weight) KERBAL_NOEXCEPT :
							left(NULL), right(NULL), value(value), weight(weight)
					{
					}

					KERBAL_CONSTEXPR
					bool is_leaf() const
					{
						return this->left == NULL;
					}

			};

			struct huffman_heap_cmp
			{
					bool operator()(const huffman_tree_node * lhs, const huffman_tree_node * rhs) const
					{
						return lhs->weight > rhs->weight;
					}
			};

			struct huffman_alphabet
			{
					std::size_t cnt[256];

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR
					huffman_alphabet() KERBAL_NOEXCEPT :
							cnt{}
					{
					}

#			else

					huffman_alphabet() KERBAL_NOEXCEPT
					{
						kerbal::algorithm::fill(this->cnt, this->cnt + 256, 0);
					}

#			endif

			};

		} // namespace detail


		class huffman_context
		{
			private:
				detail::huffman_alphabet alphabet;

			public:
				template <typename ForwardIterator>
				KERBAL_CONSTEXPR14
				void prepare(ForwardIterator first, ForwardIterator last)
				{
					typedef ForwardIterator iterator;
					typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
					KERBAL_STATIC_ASSERT((kerbal::type_traits::is_same<value_type, unsigned char>::value), "unexpected");
					while (first != last) {
						value_type c = *first;
						++this->alphabet.cnt[c];
						++first;
					}
				}

			private:

/*
				static void tra(const detail::huffman_tree_node * node, char * code_buff, std::size_t code_length = 0)
				{
					if (node == NULL) {
						return;
					}
					if (node->is_leaf()) {
						code_buff[code_length] = '\0';
						printf("value = %d    weight = %d  code = %s\n", node->value, node->weight, code_buff);
						return;
					}
					code_buff[code_length] = '0';
					tra(node->left, code_buff, code_length + 1);
					code_buff[code_length] = '1';
					tra(node->right, code_buff, code_length + 1);
				}
*/

/*
				static void tra2(const detail::huffman_tree_node * node, char * code_buff, std::size_t code_length = 0)
				{
					while (node != NULL) {
						if (node->is_leaf()) {
							code_buff[code_length] = '\0';
							printf("value = %d    weight = %d  code = %s\n", node->value, node->weight, code_buff);
							return;
						}
						code_buff[code_length] = '0';
						tra2(node->left, code_buff, code_length + 1);
						code_buff[code_length] = '1';

						// <=> tra(node->right, code_buff, code_length + 1);
						node = node->right;
						code_length = code_length + 1;
					}
				}
*/

				static void tra3(const detail::huffman_tree_node * node)
				{
					char code_buff[256 + 2];
					std::size_t code_length = 0;

					kerbal::container::static_vector<kerbal::utility::compressed_pair<const detail::huffman_tree_node *, std::size_t>, 256 + 2> st;
					st.emplace_back_unsafe(node, code_length);

					std::size_t sum = 0;

					do {
						node = st.back().first();
						code_length = st.back().second();
						st.pop_back_unsafe();
						code_buff[code_length++] = '1';

						while (!node->is_leaf()) {
							// in huffman coding-tree, if node is non-leaf, node->right is always not NULL
							//tra2(node->right, code_buff, code_length + 1);
							st.emplace_back_unsafe(node->right, code_length);

							// <=> traverse(node->left, code_buff, code_length + 1);
							node = node->left;
							code_buff[code_length++] = '0';
						}
						code_buff[code_length] = '\0';
						printf("value = %5d    weight = %10ld  code = %10s  len = %10zu\n", node->value, node->weight, code_buff + 1, code_length - 1);
						sum += node->weight * (code_length - 1);
					} while (!st.empty());

					printf("%zu\n", sum / 8);
				}

				static
				void build_huffman_table(kerbal::container::static_vector<detail::huffman_tree_node, 256 * 2 - 1> & huffman_tree_nodes)
				{
					using detail::huffman_tree_node;

					const huffman_tree_node * tree_root = &huffman_tree_nodes[0];

					const huffman_tree_node * ptr2nodes[256 * 2 - 1] = {};
					std::size_t ptr2nodes_cnt = 0;
					for (std::size_t i = 0; i < huffman_tree_nodes.size(); ++i) {
						ptr2nodes[ptr2nodes_cnt++] = &huffman_tree_nodes[i];
					}

					using detail::huffman_heap_cmp;
					huffman_heap_cmp heap_cmp;
					kerbal::algorithm::make_heap(ptr2nodes + 0, ptr2nodes + ptr2nodes_cnt, heap_cmp);
					while (ptr2nodes_cnt != 1) {
						kerbal::algorithm::pop_heap(ptr2nodes + 0, ptr2nodes + ptr2nodes_cnt, heap_cmp);
						--ptr2nodes_cnt;
						const huffman_tree_node * a = ptr2nodes[ptr2nodes_cnt];

						kerbal::algorithm::pop_heap(ptr2nodes + 0, ptr2nodes + ptr2nodes_cnt, heap_cmp);
						--ptr2nodes_cnt;
						const huffman_tree_node * b = ptr2nodes[ptr2nodes_cnt];

						huffman_tree_node & merged_node = huffman_tree_nodes.emplace_back_unsafe(a->weight + b->weight);
						tree_root = &merged_node;
						merged_node.left = a;
						merged_node.right = b;
						ptr2nodes[ptr2nodes_cnt++] = &merged_node;
						kerbal::algorithm::push_heap(ptr2nodes + 0, ptr2nodes + ptr2nodes_cnt, heap_cmp);
					}

					tra3(tree_root);

				}

			public:

				template <typename ForwardIterator, typename OutputIterator>
				KERBAL_CONSTEXPR14
				void exp(ForwardIterator first, ForwardIterator last, OutputIterator out)
				{
					using detail::huffman_tree_node;

					kerbal::container::static_vector<huffman_tree_node, 256 * 2 - 1> huffman_tree_nodes;
					for (std::size_t i = 0; i < 256; ++i) {
						std::size_t cnt = this->alphabet.cnt[i];
						if (cnt == 0) {
							continue;
						}
						huffman_tree_nodes.emplace_back_unsafe(static_cast<unsigned char>(i), cnt);
					}

					build_huffman_table(huffman_tree_nodes);

				}

		};

	} // namespace compression

} // namespace kerbal

#endif // KERBAL_COMPRESSION_HUFFMAN_PTR_HPP
