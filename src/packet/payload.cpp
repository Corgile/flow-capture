#include "packet/payload.hpp"

void *Payload::get_raw() {
  return this->raw;
}

void Payload::set_raw(void *raw_data) {
  this->raw = raw_data;
}

void Payload::print_header(FILE *out) {
  fprintf(out, "Payload: length: %d\n", n_bytes);
}

uint32_t Payload::header_len() {
  return n_bytes;
}

void Payload::fill_bit_vec(std::vector<int8_t> &vec, int8_t bit) {
  uint32_t zero_byte_width;
  zero_byte_width = max_payload_len - n_bytes;
  /* If no payload fill with max payload bytes */
  if (n_bytes == 0) {
    make_bitstring(max_payload_len, nullptr, vec, bit);
  }
    /* If payload but payload is smaller than maximum payload length */
  else if (zero_byte_width > 0) {
    make_bitstring(n_bytes, raw, vec, bit);
    make_bitstring(zero_byte_width, nullptr, vec, bit);
  }
    /* Payload is larger or as large as maximum payload length, */
  else {
    make_bitstring(max_payload_len, raw, vec, bit);
  }
}

void Payload::gen_bit_header(std::vector<std::string> &vec) {
  std::vector<std::tuple<std::string, uint32_t>> v;
  
  if (max_payload_len == 0)
    return;
  
  v.emplace_back("payload_bit", max_payload_len * 8);
  PacketHeader::gen_bit_header(v, vec);
}

/** Specific to Payload */
void Payload::set_info(uint32_t _n_bytes, uint32_t _max_payload_len) {
  this->n_bytes = _n_bytes;
  this->max_payload_len = _max_payload_len;
}
