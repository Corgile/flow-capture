#ifndef FLOW_CAPTURE_SUPERPACKET_HPP
#define FLOW_CAPTURE_SUPERPACKET_HPP

#include <arpa/inet.h>
#include <pcap.h>

#include <tuple>

#include "common.hpp"
#include "conf.hpp"
#include "packet/header/ethernet_header.hpp"
#include "packet/header/icmp_header.hpp"
#include "packet/header/ipv4_header.hpp"
#include "packet/header/ipv6_header.hpp"
#include "packet/header/radiotap_header.hpp"
#include "packet/header/tcp_header.hpp"
#include "packet/header/udp_header.hpp"
#include "packet/header/wlan_header.hpp"
#include "payload.hpp"

class SuperPacket {
public:
  SuperPacket(void *pkt, uint32_t max_payload_len, uint32_t link_type);

  std::string get_port(bool src);

  std::string get_ip_address(bool src);

  std::string get_tx_mac_address();

  void print_packet(FILE *out);

  [[nodiscard]] bool check_parseable() const { return parseable; };

  std::tuple<uint8_t, uint8_t> get_packet_type();

  void fill_bit_vec(Config *c, std::vector<int8_t> &vec);

  std::string get_index(Config *c);

private:
  bool process_v4(void *pkt);

  bool process_v6(void *pkt);

  bool parseable;
  uint32_t max_payload_len;
  RadiotapHeader radiotap_header;
  WlanHeader wlan_header;
  EthHeader ethernet_header;
  IPv4Header ipv4_header;
  IPv6Header ipv6_header;
  TCPHeader tcp_header;
  UDPHeader udp_header;
  ICMPHeader icmp_header;
  Payload payload;
};

#endif
