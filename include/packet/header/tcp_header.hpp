#ifndef FLOW_CAPTURE_TCP_HEADER_HPP
#define FLOW_CAPTURE_TCP_HEADER_HPP

#include <netinet/tcp.h>

#include "common.hpp"
#include "packet/header/packet_header.hpp"

class TCPHeader : public PacketHeader {
public:
  /* Required Functions */
  std::string get_port(bool src);
  
  void *get_raw() override;
  
  void set_raw(void *raw_data) override;
  
  void print_header(FILE *out) override;
  
  uint32_t header_len() override;
  
  void fill_bit_vec(std::vector<int8_t> &vec, int8_t bit) override;
  
  void gen_bit_header(std::vector<std::string> &vec) override;
  
  /* Header Specific */
private:
  struct tcphdr *raw = nullptr;
};

#endif
