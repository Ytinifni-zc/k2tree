//
// Created by inFinity on 2018/01/19.
//

#ifndef K2TREE_MORTON_H
#define K2TREE_MORTON_H

#include <base.h>
#include <cstdint>
#include <utils/bit_vector.h>
#include <sdsl/bit_vectors.hpp>
#include <memory>
#include <async++.h>
#include <boost/sort/sort.hpp>
#include <utils/time.h>

using namespace libk2tree;
using namespace sdsl;

namespace libk2tree {

    template<uint8_t k1_,
             uint8_t k2_,
             uint8_t k1_levels_,
             uint8_t kL_,
             typename t_lev=bit_vector,
             typename t_leaf=bit_vector,
             typename t_rank=rank_support_v<1>>
    class k2tree_morton {

        static_assert(k1_==2||k1_==4||k1_==8||k1_==16, "k1_ has to be in {2, 4, 8, 16}.");
        static_assert(k2_==2||k2_==4||k2_==8||k2_==16, "k2_ has to be in {2, 4, 8, 16}.");
        static_assert(kL_==2||kL_==4||kL_==8||kL_==16, "kL_ has to be in {2, 4, 8, 16}.");
        static_assert(kL_>=k1_, "t_k_leaves has to be larger than t_k_l_1,  otherwise this could lead to different word sizes and thus to a problem for the k2part approach.");
        static_assert(kL_<=8, "t_k can at most be 8 because of the current dac compression implementation.");

        public:

            k2tree_morton() = default;

            k2tree_morton(uint32_t node_num) : node_num_(node_num) {
                bits_ = static_cast<uint8_t>(std::ceil(std::log(node_num_) / std::log(2)));
                k2_levels_ = bits_ - k1_exp_*k1_levels_ - kL_exp_;
                height_ = k1_levels_ + k2_levels_ + kL_exp_;
                m_k_for_level.resize(height_);
                m_mask_table.resize(height_);
                tree_.resize(height_);
                uint32_t mask;
                for (int i = 0; i < height_; ++i) {
                    if (i < k1_levels_) {
                        m_k_for_level[i] = k1_;
                        mask = 0xffffffff;
                        mask <<= bits_-(i+1)*k1_exp_;
                        mask = mask & (~(mask << k1_exp_));
                        m_mask_table[i] = mask;
                    } else if (i < height_-1) {
                        m_k_for_level[i] = k2_;
                        mask = 0xffffffff;
                        mask <<= bits_-k1_levels_*k1_exp_-(i+1-k1_levels_)*k2_exp_;
                        mask = mask & (~(mask << k2_exp_));
                        m_mask_table[i] = mask;
                    } else {
                        m_k_for_level[i] = kL_;
                        m_mask_table[i] = 0xffffffff >> (32-kL_exp_);
                    }
                }
            }


            /**
             * Convert <u, v> edge pair to Z-order morton number.
             * @param edge The <u, v> pair.
             * @return Morton number.
             */
            uint64_t kv_2_Zorder(const std::pair<uint32_t, uint32_t> &edge) {
                if (edge.first > node_num_ || edge.second > node_num_) {
                    std::cerr << "Node label should less than or equal to number of node." << std::endl;
                    exit(1);
                }
                uint64_t ret = 0;
                for (int i = 0; i < height_; ++i) {
                    uint64_t u_part, v_part;
                    if (i < k1_levels_) {
                        u_part = static_cast<uint64_t>(edge.first & m_mask_table[i]) << (bits_-i*k1_exp_);
                        v_part = static_cast<uint64_t>(edge.second & m_mask_table[i]) << (bits_-(i+1)*k1_exp_);
                    } else if (i < height_ - 1) {
                        u_part = static_cast<uint64_t>(edge.first & m_mask_table[i])
                                    << (bits_-k1_levels_*k1_exp_-(i-k1_levels_)*k2_exp_);
                        v_part = static_cast<uint64_t>(edge.second & m_mask_table[i])
                                    << (bits_-k1_levels_*k1_exp_-(i-k1_levels_+1)*k2_exp_);
                    } else {
                        u_part = static_cast<uint64_t>(edge.first & m_mask_table[i]) << kL_exp_;
                        v_part = static_cast<uint64_t>(edge.second & m_mask_table[i]);
                    }
                    ret |= u_part | v_part;
                }
                return ret;
            }

            /**
             * Convert <src, dst> edge pair to Z-order morton number.
             * @param src Source node in an edge.
             * @param dst Destination node in an edge.
             * @return Morton number.
             */
            uint64_t kv_2_Zorder(const uint32_t &src, const uint32_t &dst) {
                if (src > node_num_ || dst > node_num_) {
                    std::cerr << "Node label should less than or equal to number of node." << std::endl;
                    exit(1);
                }
                uint64_t ret = 0;
                for (int i = 0; i < height_; ++i) {
                    uint64_t u_part, v_part;
                    if (i < k1_levels_) {
                        u_part = static_cast<uint64_t>(src & m_mask_table[i]) << (bits_-i*k1_exp_);
                        v_part = static_cast<uint64_t>(dst & m_mask_table[i]) << (bits_-(i+1)*k1_exp_);
                    } else if (i < height_ - 1) {
                        u_part = static_cast<uint64_t>(src & m_mask_table[i])
                                    << (bits_-k1_levels_*k1_exp_-(i-k1_levels_)*k2_exp_);
                        v_part = static_cast<uint64_t>(dst & m_mask_table[i])
                                    << (bits_-k1_levels_*k1_exp_-(i-k1_levels_+1)*k2_exp_);
                    } else {
                        u_part = static_cast<uint64_t>(src & m_mask_table[i]) << kL_exp_;
                        v_part = static_cast<uint64_t>(dst & m_mask_table[i]);
                    }
                    ret |= u_part | v_part;
                }
                return ret;
            }

            std::pair<uint32_t, uint32_t> Zorder_2_kv(uint64_t morton_num) {
                ;
            }


            /**
             * Convert edge array to morton number array.
             * @param edge_array The <u, v> pair array.
             * @param is_parallel Indicate whether use paraller for or not.
             * @return Morton number array.
             */
            vector<uint64_t> kv_array_2_Zorder_array(const vector<std::pair<uint32_t, uint32_t>> &edge_array, bool is_parallel=true) {

                vector<uint64_t> morton_numbers(edge_array.size(), 0ull);
                if (is_parallel) {
                    async::parallel_for(async::irange(0ul, edge_array.size()), [&](uint64_t i) {
                        morton_numbers[i] = kv_2_Zorder(edge_array[i]);
                    });
                } else {
                    for (uint64_t i = 0ul; i < edge_array.size(); ++i) {
                        morton_numbers[i] = kv_2_Zorder(edge_array[i]);
                    }
                }

                return morton_numbers;
            }

            /**
             * Convert edge array to morton number array.
             * @param edge_array The {u, v} pair array.
             * @param size Number of edge.
             * @param is_parallel Indicate whether use paraller for or not.
             * @return Morton number array.
             */
            vector<uint64_t> kv_array_2_Zorder_array(int (*edge_array)[2], const uint64_t &size, bool is_parallel=true) {

                vector<uint64_t> morton_numbers(size, 0ull);
                if (is_parallel) {
                    async::parallel_for(async::irange(0ul, size), [&](uint64_t i) {
                        if (edge_array[i][0] != 0 && edge_array[i][1] != 0)
                            morton_numbers[i] = kv_2_Zorder(edge_array[i][0]-1, edge_array[i][1]-1);
                    });
                } else {
                    for (uint64_t i = 0ul; i < size; ++i) {
                        if (edge_array[i][0] != 0 && edge_array[i][1] != 0)
                            morton_numbers[i] = kv_2_Zorder(edge_array[i][0]-1, edge_array[i][1]-1);
                    }
                }

                return morton_numbers;
            }


            /**
             * Convert edge stream to morton number array.
             * @param in The edge stream.
             * @param size Number of edge.
             * @param is_binary Whether the stream is a binary stream.
             * @return Morton number array.
             */
            vector<uint64_t> kv_array_2_Zorder_array(const std::ifstream &in, const uint64_t &size, const bool &is_binary=true) {
                vector<uint64_t> morton_numbers;
                morton_numbers.reserve(size);
                //while (!in.eof()) {
                //    uint32_t u, v;
                //    if (is_binary) {
                //        in.read((char*)&u, sizeof(u));
                //        in.read((char*)&v, sizeof(v));
                //    } else {
                //        in >> u >> v;
                //    }
                //    morton_numbers.emplace_back(std::make_pair<uint32_t, uint32_t>(u, v);
                //}
                return morton_numbers;
            }

            void build_from_edge_array(int (*edge_array)[2], const uint64_t &size, bool is_parallel=true) {
                vector<uint64_t> morton_numbers;
                utils::cost([&](){
                    std::cerr << "Convert edges to morton numbers: ";
                    morton_numbers = kv_array_2_Zorder_array(edge_array, size, is_parallel);
                });
                if (munmap(edge_array, size*8) == -1) {
                    perror("munmap failed.");
                    exit(1);
                }
                utils::cost([&](){
                    std::cerr << "Boost block sort: ";
                    boost::sort::block_indirect_sort(morton_numbers.begin(), morton_numbers.end());
                });

                utils::cost([&](){
                    std::cerr << "Build tree: " << std::endl;

                    // Generate level masks. Tested.
                    vector<uint64_t> level_masks(height_);
                    const uint64_t MAX_UINT64 = 0xffffffffffffffffull;
                    level_masks[height_-1] = MAX_UINT64 << (kL_exp_ << 1);
                    for (int level = height_-2; level >= 0; --level) {
                        if (level >= k1_levels_)
                            level_masks[level] = level_masks[level+1] << (k2_exp_ << 1);
                        else
                            level_masks[level] = level_masks[level+1] << (k1_exp_ << 1);
                    }
                    for (auto m: level_masks)
                        std::cerr << std::hex << m << std::dec << std::endl;

                    // TODO Generate level bitmap's size.
                    vector<uint64_t> level_sizes(height_, 1ull); // Bitmap size in each level.
                    //level_sizes.resize(1ull, height_);
                    auto do_mask = [&](uint64_t morton_num) {
                        // Do mask with morton number.
                        // Note that level_codes[0] is useless.
                        vector<uint64_t> lc(height_, 0ull);
                        for (int i = 0; i < height_; ++i) {
                            lc[i] = morton_num & level_masks[i];
                        }
                        return lc;
                    };

                    auto cmp_level_codes = [&](const vector<uint64_t> &lc1, const vector<uint64_t> &lc2) {
                        // Compare level codes generated by last morton number with current level codes.
                        // Add level size in different level.
                        for (int i = 0; i < height_; ++i) {
                            if (lc1[i] != lc2[i])
                                level_sizes[i]++;
                        }
                    };

                    auto level_codes = do_mask(morton_numbers.front());
                    for (auto mn: morton_numbers) {
                        auto cur_lc = do_mask(mn);
                        cmp_level_codes(level_codes, cur_lc);
                        level_codes.swap(cur_lc);
                    }

                    /*
                    // TEST CODE
                    uint64_t inter_node_sum = 0ull;
                    for (auto s: level_sizes) {
                        std::cerr << s << std::endl;
                        inter_node_sum += s;
                    }
                    std::cerr << "Total interal node number: " << inter_node_sum << std::endl;
                    */
                });
            }

        private:

            // Number of node.
            uint32_t node_num_;

            vector<uint8_t> m_k_for_level;
            vector<uint32_t> m_mask_table;

            uint8_t bits_;
            // Height of k2tree
            uint8_t height_;
            // Number of k2 levels.
            uint8_t k2_levels_;
            static constexpr uint8_t k1_exp_ = static_cast<uint8_t>(std::ceil(std::log(k1_) / std::log(2)));
            static constexpr uint8_t k2_exp_ = static_cast<uint8_t>(std::ceil(std::log(k2_) / std::log(2)));
            static constexpr uint8_t kL_exp_ = static_cast<uint8_t>(std::ceil(std::log(kL_) / std::log(2)));

            /**
             * Bitmap of T and L.
             * Size of tree_ equals height_.
             * The last element is L. Others indicate T in each level.
             */
            vector<bit_vector> tree_;
    };


} // end namespace libk2tree

#endif
