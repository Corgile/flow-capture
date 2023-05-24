#include "packet/header/packet_header.hpp"

void PacketHeader::ascii_encode(unsigned char *ptr, uint32_t num_bytes,
                                std::vector<std::string> &vec) {
  uint32_t i;
  char *s, *t;
  
  s = new char[num_bytes * 2 + 1];
  
  t = s;
  for (i = 0; i < num_bytes; i++) {
    sprintf(t, "%c", (ptr[i]));
    t++;
  }
  vec.emplace_back(s);
  delete s;
}

void PacketHeader::make_bitstring(uint32_t num_bytes, void *ptr,
                                  std::vector<int8_t> &vec,
                                  int8_t bit) {
  
  if (ptr == nullptr) {
    for (uint32_t i = 0; i < num_bytes * 8; i++)
      vec.push_back(bit);
    return;
  }
  
  auto byte = (uint8_t *) ptr;
  for (uint32_t i = 0; i < num_bytes; i++) {
    for (int32_t j = 7; j >= 0; j--) {
      auto _bit = (byte[i] >> j) & 0x01;
      vec.push_back(int8_t(_bit));
    }
  }
}

void PacketHeader::gen_bit_header(
    const std::vector<std::tuple<std::string, uint32_t>> &v,
    std::vector<std::string> &field) {
  std::vector<std::tuple<std::string, uint32_t>>::const_iterator vit;
  for (vit = v.begin(); vit != v.end(); vit++) {
    for (uint32_t i = 0; i < std::get<1>(*vit); i++) {
      field.push_back(std::get<0>(*vit) + "_" + std::to_string(i));
    }
  }
}
