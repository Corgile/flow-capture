#ifndef FLOW_CAPTURE_IPv4_HEADER_HPP
#define FLOW_CAPTURE_IPv4_HEADER_HPP

#include <netinet/ip.h>

#include "common.hpp"
#include "packet/header/packet_header.hpp"

class IPv4Header : public PacketHeader {
public:
  /* Required Functions */
  void *get_raw() override;
  
  void set_raw(void *raw_data) override;
  
  void print_header(FILE *out) override;
  
  uint32_t header_len() override;
  
  void fill_bit_vec(std::vector<int8_t> &vec, int8_t bit) override;
  
  void gen_bit_header(std::vector<std::string> &vec) override;
  
  /* Header Specific */
  std::string get_src_ip();
  
  std::string get_dst_ip();
  
  uint8_t get_ip_proto();
  
  uint16_t get_total_len();

private:
  struct ip *raw = nullptr;
};

#endif
