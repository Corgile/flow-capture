#include "packet/header/ipv4_header.hpp"


void *IPv4Header::get_raw() {
  return (void *) this->raw;
}

void IPv4Header::set_raw(void *raw_data) {
  this->raw = (struct ip *) raw_data;
}

void IPv4Header::print_header(FILE *out) {
  if (raw == nullptr) {
    fprintf(out, "IPv4Header: raw data not set\n");
  } else {
    fprintf(out, "IPv4Header: src_ip: %s, dst_ip: %s\n",
            inet_ntoa(raw->ip_src), inet_ntoa(raw->ip_dst));
  }
}

uint32_t IPv4Header::header_len() {
  return raw->ip_hl * 4;
}

void IPv4Header::fill_bit_vec(std::vector<int8_t> &vec, int8_t bit) {
  uint32_t ip_header_byte_size, zero_byte_width;
  
  if (raw == nullptr) {
    make_bitstring(SIZE_IPV4_HEADER_BITSTRING, nullptr, vec, bit);
    return;
  }
  
  ip_header_byte_size = raw->ip_hl * 4;
  zero_byte_width = SIZE_IPV4_HEADER_BITSTRING - ip_header_byte_size;
  
  make_bitstring(ip_header_byte_size, (void *) raw, vec, bit);
  make_bitstring(zero_byte_width, nullptr, vec, bit);
}

void IPv4Header::gen_bit_header(std::vector<std::string> &vec) {
  std::vector<std::tuple<std::string, uint32_t>> v;
  v.emplace_back("ipv4_ver", 4);
  v.emplace_back("ipv4_hl", 4);
  v.emplace_back("ipv4_tos", 8);
  v.emplace_back("ipv4_tl", 16);
  v.emplace_back("ipv4_id", 16);
  v.emplace_back("ipv4_rbit", 1);
  v.emplace_back("ipv4_dfbit", 1);
  v.emplace_back("ipv4_mfbit", 1);
  v.emplace_back("ipv4_foff", 13);
  v.emplace_back("ipv4_ttl", 8);
  v.emplace_back("ipv4_proto", 8);
  v.emplace_back("ipv4_cksum", 16);
  v.emplace_back("ipv4_src", 32);
  v.emplace_back("ipv4_dst", 32);
  v.emplace_back("ipv4_opt", 320);
  
  PacketHeader::gen_bit_header(v, vec);
}

/* Header Specific */

std::string IPv4Header::get_src_ip() {
  return inet_ntoa(raw->ip_src);
}

std::string IPv4Header::get_dst_ip() {
  return inet_ntoa(raw->ip_dst);
}

uint8_t IPv4Header::get_ip_proto() {
  return raw->ip_p;
}

uint16_t IPv4Header::get_total_len() {
  return ntohs(raw->ip_len);
}
