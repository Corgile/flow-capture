#ifndef FLOW_CAPTURE_COMMON_HPP
#define FLOW_CAPTURE_COMMON_HPP

#define SIZE_UDP_HEADER_BITSTRING 8
#define SIZE_ETH_HEADER_BITSTRING 14
#define SIZE_ICMP_HEADER_BITSTRING 8
#define SIZE_IPV4_HEADER_BITSTRING 60
#define SIZE_IPV4_HEADER_BITSTRING 60
#define SIZE_IPV6_HEADER_BITSTRING 40
#define SIZE_TCP_HEADER_BITSTRING 60
#define SIZE_RADIOTAP_HEADER_BITSTRING 56

// TODO: we only parse the first 10 bytes at this time
#define SIZE_WLAN_HEADER_BITSTRING 10

using callback_data_t = unsigned char *;

using raw_data_t = const void *;

using header_ip_t = const struct iphdr *;
using header_eth_t = const struct ether_header *;
using header_tcp_t = const struct tcphdr *;
using header_udp_t = const struct udphdr *;
using header_ipv6_t = const struct ip6_hdr *;
using header_icmp_t = const struct icmphdr *;
using header_radio_t = const struct radiotap_header *;
using header_vlan_t = const struct vlan_hdr { uint32_t vlan_flag; } *;

using packet_ip_t = const struct ip *;
using packet_icmp_t = const struct icmp *;

#endif // FLOW_CAPTURE_COMMON_HPP
