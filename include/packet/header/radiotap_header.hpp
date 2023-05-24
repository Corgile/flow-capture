#ifndef FLOW_CAPTURE_RADIOTAP_HEADER_HPP
#define FLOW_CAPTURE_RADIOTAP_HEADER_HPP

#include "common.hpp"
#include "packet/header/packet_header.hpp"

struct radiotap_header {
  /* all bytes for radiotap_data 	*/
  [[maybe_unused]] uint8_t *radiotap_data;
};

class RadiotapHeader : public PacketHeader {
public:
  /* Required Functions */
  void *get_raw() override;
  
  void set_raw(void *raw_data) override;
  
  void print_header(FILE *out) override;
  
  uint32_t header_len() override;
  
  void fill_bit_vec(std::vector<int8_t> &vec, int8_t bit) override;
  
  void gen_bit_header(std::vector<std::string> &vec) override;

private:
  struct radiotap_header *raw = nullptr;
};

#endif
