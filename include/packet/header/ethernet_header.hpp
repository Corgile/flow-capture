#ifndef FLOW_CAPTURE_ETH_HEADER_HPP
#define FLOW_CAPTURE_ETH_HEADER_HPP

#include <netinet/if_ether.h>

#include "packet_header.hpp"

#define SIZE_ETH_HEADER_BITSTRING 14

class EthHeader : public PacketHeader {
   public:
    /* Required Functions */
    void *get_raw() override;
    void set_raw(void *raw) override;
    void print_header(FILE *out) override;
    uint32_t header_len() override;
    void fill_bit_vec(std::vector<int8_t> &to_fill, int8_t fill_with) override;
    void gen_bit_vec_header(std::vector<std::string> &to_fill) override;

   private:
    struct ether_header *raw = nullptr;
};

#endif
