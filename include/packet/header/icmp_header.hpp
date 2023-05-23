#ifndef FLOW_CAPTURE_ICMP_HEADER_HPP
#define FLOW_CAPTURE_ICMP_HEADER_HPP

#include <netinet/ip.h>
#include <netinet/ip_icmp.h>

#include "packet/header/packet_header.hpp"

#define SIZE_ICMP_HEADER_BITSTRING 8

/*
 * We consider the ICMP header to always be 8 bytes, with the rest of the data
 * being part of the payload. Some consider it "ICMP data", it simplifies things
 * for us if its just abstracted as a payload
 */

class ICMPHeader : public PacketHeader {
   public:
    /* Required Functions */
    void *get_raw() override;
    void set_raw(void *raw_data) override;
    void print_header(FILE *out) override;
    uint32_t header_len() override { return 8; };
    void fill_bit_vec(std::vector<int8_t> &to_fill, int8_t fill_with) override;
    void gen_bit_vec_header(std::vector<std::string> &to_fill) override;

   private:
    struct icmp *raw = nullptr;
};

#endif
