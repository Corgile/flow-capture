#ifndef FLOW_CAPTURE_ETH_HEADER_HPP
#define FLOW_CAPTURE_ETH_HEADER_HPP

#include <netinet/if_ether.h>

#include "common.hpp"
#include "packet/header/packet_header.hpp"

#define SIZE_ETH_HEADER_BITSTRING 14

class EthHeader : public PacketHeader {
public:
  /* Required Functions */
  void *get_raw() override;
  
  void set_raw(void *raw_data) override;
  
  void print_header(FILE *out) override;
  
  uint32_t header_len() override;
  
  void fill_bit_vec(std::vector<int8_t> &vec, int8_t bit) override;
  
  void gen_bit_header(std::vector<std::string> &vec) override;

private:
  struct ether_header *raw = nullptr;
};

#endif
