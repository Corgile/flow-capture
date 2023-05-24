#include "packet/header/ipv6_header.hpp"

void *IPv6Header::get_raw() {
    return (void *)this->raw;
}

void IPv6Header::set_raw(void *raw_data) {
    this->raw = (struct ip6_hdr *)raw_data;
}

void IPv6Header::print_header(FILE *out) {
}

uint32_t IPv6Header::header_len() {
    return 40;
}

std::string IPv6Header::get_src_ip() {
    char s[INET6_ADDRSTRLEN];
    inet_ntop(AF_INET6, (void *)&raw->ip6_src, s, INET6_ADDRSTRLEN);

    return {s};
}

std::string IPv6Header::get_dst_ip() {
    char s[INET6_ADDRSTRLEN];
    inet_ntop(AF_INET6, (void *)&raw->ip6_dst, s, INET6_ADDRSTRLEN);

    return {s};
}

void IPv6Header::fill_bit_vec(std::vector<int8_t> &vec, int8_t bit) {
  if (raw == nullptr) {
    make_bitstring(SIZE_IPV6_HEADER_BITSTRING, nullptr, vec, bit);
    return;
  }
  
  make_bitstring(SIZE_IPV6_HEADER_BITSTRING, (void *) raw, vec, bit);
}

void IPv6Header::gen_bit_header(std::vector<std::string> &vec) {
  std::vector<std::tuple<std::string, uint32_t>> v;
  v.emplace_back("ipv6_ver", 4);
  v.emplace_back("ipv6_tc", 8);
  v.emplace_back("ipv6_fl", 20);
  v.emplace_back("ipv6_len", 16);
  v.emplace_back("ipv6_nh", 8);
  v.emplace_back("ipv6_hl", 8);
  v.emplace_back("ipv6_src", 128);
  v.emplace_back("ipv6_dst", 128);
  
  PacketHeader::gen_bit_header(v, vec);
}

/* Header Specific */
uint8_t IPv6Header::get_ip_proto() {
    return raw->ip6_nxt;
}

uint32_t IPv6Header::get_total_len() {
    return ntohs(raw->ip6_plen) + 40;
}
