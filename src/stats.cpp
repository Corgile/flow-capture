#include "stats.hpp"

#define ull static_cast<unsigned long long>
#define ratio(x, y) (100.0 * (double(x) / ull(y)))

void Stats::print_stats() const {
  fprintf(stderr, "General Statistics\n");
  fprintf(stderr, "  Packets processed: %10llu\n", ull(processed));
  fprintf(stderr, "  Packets skipped:   %10llu (%.2f%%)\n", ull(skipped), ratio(skipped, processed));
  fprintf(stderr, "  Packets parsed:    %10llu (%.2f%%)\n", ull(n_parsed), ratio(n_parsed, processed));
  fprintf(stderr, "Network Layer Statistics (of packets parsed)\n");
  fprintf(stderr, "  IPv4:              %10llu (%.2f%%)\n", ull(ipv4), ratio(ipv4, n_parsed));
  fprintf(stderr, "  IPv6:              %10llu (%.2f%%)\n", ull(ipv6), ratio(ipv6, n_parsed));
  fprintf(stderr, "Transport Layer Statistics (of packets parsed)\n");
  fprintf(stderr, "  TCP:               %10llu (%.2f%%)\n", ull(tcp), ratio(tcp, n_parsed));
  fprintf(stderr, "  UDP:               %10llu (%.2f%%)\n", ull(udp), ratio(udp, n_parsed));
  fprintf(stderr, "  ICMP:              %10llu (%.2f%%)\n", ull(icmp), ratio(icmp, n_parsed));
}

void Stats::update(bool parsed, uint8_t network_layer, uint8_t transport_layer) {
  processed++;
  if (!parsed) {
    skipped++;
    return;
  }
  this->n_parsed++;
  ipv4 += network_layer == 4;
  ipv6 += network_layer == 6;
  tcp += transport_layer == IPPROTO_TCP;
  udp += transport_layer == IPPROTO_UDP;
  icmp += transport_layer == IPPROTO_ICMP;
}

uint64_t Stats::get_packets_processed() const {
  return processed;
}
