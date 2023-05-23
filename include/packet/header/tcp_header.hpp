#ifndef FLOW_CAPTURE_TCP_HEADER_HPP
#define FLOW_CAPTURE_TCP_HEADER_HPP

#include <netinet/tcp.h>

#include "packet_header.hpp"

#define SIZE_TCP_HEADER_BITSTRING 60

class TCPHeader : public PacketHeader {
   public:
    /* Required Functions */
    std::string get_port(bool src);
    void *get_raw() override;
    void set_raw(void *raw_data) override;
    void print_header(FILE *out) override;
    uint32_t header_len() override;
    void fill_bit_vec(std::vector<int8_t> &to_fill, int8_t fill_with) override;
    void gen_bit_vec_header(std::vector<std::string> &to_fill) override;

    /* Header Specific */
   private:
    struct tcphdr *raw = nullptr;
};

#endif
