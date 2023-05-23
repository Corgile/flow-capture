#ifndef FLOW_CAPTURE_IPv4_HEADER_HPP
#define FLOW_CAPTURE_IPv4_HEADER_HPP

#include <netinet/ip.h>

#include "packet/header/packet_header.hpp"

#define SIZE_IPV4_HEADER_BITSTRING 60

class IPv4Header : public PacketHeader {
   public:
    /* Required Functions */
    void *get_raw() override;
    void set_raw(void *raw) override;
    void print_header(FILE *out) override;
    uint32_t header_len() override;
    void fill_bit_vec(std::vector<int8_t> &to_fill, int8_t fill_with) override;
    void gen_bit_vec_header(std::vector<std::string> &to_fill) override;

    /* Header Specific */
    std::string get_src_ip();
    std::string get_dst_ip();
    uint8_t get_ip_proto();
    uint16_t get_total_len();

   private:
    struct ip *raw = nullptr;
};

#endif
