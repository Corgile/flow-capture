#include "packet/header/icmp_header.hpp"

/* Required Functions */
void *ICMPHeader::get_raw() {
    return (void *)this->raw;
}

void ICMPHeader::set_raw(void *raw_data) {
    this->raw = (struct icmp *)raw_data;
}

void ICMPHeader::print_header(FILE *out) {
  if (raw == nullptr) {
    fprintf(out, "ICMPHeader:: raw data not set\n");
  } else {
    fprintf(out, "icmp: type: %u, code: %u\n", raw->icmp_type,
            raw->icmp_code);
  }
}

void ICMPHeader::fill_bit_vec(std::vector<int8_t> &vec, int8_t bit) {
  if (raw == nullptr) {
    make_bitstring(SIZE_ICMP_HEADER_BITSTRING, nullptr, vec, bit);
    return;
  }
  make_bitstring(SIZE_ICMP_HEADER_BITSTRING, (void *) raw, vec, bit);
}

void ICMPHeader::gen_bit_header(std::vector<std::string> &vec) {
  std::vector<std::tuple<std::string, uint32_t>> v;
  v.emplace_back("icmp_type", 8);
  v.emplace_back("icmp_code", 8);
  v.emplace_back("icmp_cksum", 16);
  v.emplace_back("icmp_roh", 32);
  
  PacketHeader::gen_bit_header(v, vec);
}
