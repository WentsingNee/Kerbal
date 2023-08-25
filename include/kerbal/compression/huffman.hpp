/**
 * @file       huffman.hpp
 * @brief
 * @date       huffman.hpp
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_COMPRESSION_HUFFMAN_HPP
#define KERBAL_COMPRESSION_HUFFMAN_HPP

#include <kerbal/algorithm/heap.hpp>
#include <kerbal/algorithm/modifier/copy.hpp>
#include <kerbal/algorithm/modifier/iota.hpp>
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
					short left;
					short right;
					unsigned char value;
					std::size_t weight;

					// construct merged node
					KERBAL_CONSTEXPR
					explicit huffman_tree_node(short left, short right, std::size_t weight) KERBAL_NOEXCEPT :
							left(left), right(right), value(0), weight(weight)
					{
					}

					// construct leaf node
					KERBAL_CONSTEXPR
					explicit huffman_tree_node(unsigned value, std::size_t weight) KERBAL_NOEXCEPT :
							left(-1), right(-1), value(value), weight(weight)
					{
					}

					KERBAL_CONSTEXPR
					bool is_leaf() const KERBAL_NOEXCEPT
					{
						return this->left == -1;
					}

			};

			struct huffman_heap_cmp
			{
					const huffman_tree_node * base;

					KERBAL_CONSTEXPR
					explicit huffman_heap_cmp(const huffman_tree_node * base) KERBAL_NOEXCEPT :
							base(base)
					{
					}

					KERBAL_CONSTEXPR
					bool operator()(short lhs, short rhs) const
					{
						return base[lhs].weight > base[rhs].weight;
					}
			};

		} // namespace detail

		class huffman_context;

		class huffman_alphabet
		{
				friend class huffman_context;

			private:
				std::size_t cnt[256];

			public:

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
						++this->cnt[c];
						++first;
					}
				}

		};

		class huffman_context
		{
			private:
				char codes_table[256][256]; // code length never exceeds 256 (contains '\0')

			public:
				KERBAL_CONSTEXPR14
				explicit huffman_context(const huffman_alphabet & alphabet) KERBAL_NOEXCEPT
#		if __cplusplus >= 201103L
					: codes_table{}
#		endif
				{
					this->build_huffman_table(alphabet);
				}

			private:

				KERBAL_CONSTEXPR14
				void traverse_tree_gen_table(const detail::huffman_tree_node * base, short tree_root) KERBAL_NOEXCEPT
				{
					char code_buff[256 + 1] = {}; // code_buff start from index 1, doesn't occur '\0'
					std::size_t code_length = 0;

					kerbal::container::static_vector<kerbal::utility::compressed_pair<short, std::size_t>, 255> st;
					st.emplace_back_unsafe(tree_root, code_length);

					do {
						tree_root = st.back().first();
						code_length = st.back().second();
						st.pop_back_unsafe();
						code_buff[code_length++] = '1';

						while (!base[tree_root].is_leaf()) {
							// in huffman coding-tree, if node is non-leaf, base[node].right is always not NULL
							// <=> traverse(base[node].right, code_buff, code_length + 1);
							st.emplace_back_unsafe(base[tree_root].right, code_length);

							// <=> traverse(base[node].left, code_buff, code_length + 1);
							tree_root = base[tree_root].left;
							code_buff[code_length++] = '0';
						}
						unsigned char value = base[tree_root].value;
						kerbal::algorithm::copy(code_buff + 1, code_buff + code_length, this->codes_table[value]);
						this->codes_table[value][code_length] = '\0';
					} while (!st.empty());
				}

				KERBAL_CONSTEXPR14
				void build_huffman_table(const huffman_alphabet & alphabet) KERBAL_NOEXCEPT
				{
					using detail::huffman_tree_node;

					kerbal::container::static_vector<huffman_tree_node, 256 * 2 - 1> huffman_tree_nodes;
					for (std::size_t i = 0; i < 256; ++i) {
						std::size_t cnt = alphabet.cnt[i];
						if (cnt == 0) {
							continue;
						}
						huffman_tree_nodes.emplace_back_unsafe(static_cast<unsigned char>(i), cnt);
					}

					const huffman_tree_node * base = &huffman_tree_nodes[0];
					short tree_root = -1;
					{
						short ptr2nodes[256 * 2 - 1] = {};
						short ptr2nodes_cnt = static_cast<short>(huffman_tree_nodes.size());
						kerbal::algorithm::iota(ptr2nodes + 0, ptr2nodes + ptr2nodes_cnt, 0);

						using detail::huffman_heap_cmp;
						huffman_heap_cmp heap_cmp(base);
						kerbal::algorithm::make_heap(ptr2nodes + 0, ptr2nodes + ptr2nodes_cnt, heap_cmp);
						while (ptr2nodes_cnt != 1) {
							kerbal::algorithm::pop_heap(ptr2nodes + 0, ptr2nodes + ptr2nodes_cnt, heap_cmp);
							--ptr2nodes_cnt;
							short a = ptr2nodes[ptr2nodes_cnt];

							kerbal::algorithm::pop_heap(ptr2nodes + 0, ptr2nodes + ptr2nodes_cnt, heap_cmp);
							--ptr2nodes_cnt;
							short b = ptr2nodes[ptr2nodes_cnt];

							huffman_tree_nodes.emplace_back_unsafe(a, b, base[a].weight + base[b].weight);
							ptr2nodes[ptr2nodes_cnt++] = static_cast<short>(huffman_tree_nodes.size() - 1);
							kerbal::algorithm::push_heap(ptr2nodes + 0, ptr2nodes + ptr2nodes_cnt, heap_cmp);
						}
						tree_root = ptr2nodes[0];
					}

					traverse_tree_gen_table(base, tree_root);
				}

			public:

				template <typename ForwardIterator, typename OutputIterator>
				KERBAL_CONSTEXPR14
				OutputIterator compress(ForwardIterator first, ForwardIterator last, OutputIterator out) const
				{
					typedef ForwardIterator iterator;
					typedef typename kerbal::iterator::iterator_traits<iterator>::value_type value_type;
					KERBAL_STATIC_ASSERT((kerbal::type_traits::is_same<value_type, unsigned char>::value), "unexpected");

					unsigned char buff = 0;
					short buff_len = 0;
					while (first != last) {
						const char * code = this->codes_table[*first];
						while (*code != '\0') {
							buff = (buff << 1) | (*code - '0');
							++buff_len;
							if (buff_len == 8) {
								*out = buff;
								++out;
								buff_len = 0;
							}
							++code;
						}
						++first;
					}
					if (buff_len != 0) {
						*out = buff;
						++out;
					}
					return out;
				}

		};

	} // namespace compression

} // namespace kerbal

#endif // KERBAL_COMPRESSION_HUFFMAN_HPP
