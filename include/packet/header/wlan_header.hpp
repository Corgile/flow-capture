#ifndef FLOW_CAPTURE_LAN_HEADER_HPP
#define FLOW_CAPTURE_LAN_HEADER_HPP

#include "common.hpp"
#include "packet/header/packet_header.hpp"

struct wlan_header {
  uint8_t type;
  uint8_t flag;
  uint16_t duration;
  uint8_t rx_addr[6];
  uint8_t tx_addr[6];
};

class WlanHeader : public PacketHeader {
public:
  /* Required Functions */
  void *get_raw() override;
  
  void set_raw(void *raw_data) override;
  
  void print_header(FILE *out) override;
  
  uint32_t header_len() override;
  
  void fill_bit_vec(std::vector<int8_t> &vec, int8_t bit) override;
  
  void gen_bit_header(std::vector<std::string> &to_fill) override;
  
  std::string get_tx_mac();

private:
  struct wlan_header *raw = nullptr;
};

#endif
