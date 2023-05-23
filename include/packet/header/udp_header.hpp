#ifndef FLOW_CAPTURE_UDP_HEADER_HPP
#define FLOW_CAPTURE_UDP_HEADER_HPP

#include <netinet/udp.h>

#include "packet_header.hpp"

#define SIZE_UDP_HEADER_BITSTRING 8

class UDPHeader : public PacketHeader {
   public:
    /* Required Functions */
    void *get_raw() override;
    void set_raw(void *raw) override;
    void print_header(FILE *out) override;
    uint32_t header_len() override;
    std::string get_port(bool src);
    void fill_bit_vec(std::vector<int8_t> &to_fill, int8_t fill_with) override;
    void gen_bit_vec_header(std::vector<std::string> &to_fill) override;
    /* Header Specific */
   private:
    struct udphdr *raw = nullptr;
};

#endif
