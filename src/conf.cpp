#include "conf.hpp"

Config::Config() {
    this->radiotap = 0;
    this->wlan = 0;
    this->eth = 0;
    this->ipv4 = 0;
    this->ipv6 = 0;
    this->tcp = 0;
    this->udp = 0;
    this->icmp = 0;
    this->payload = 0;
    this->bit = -1;
    this->num_packets = 0;
    this->absolute_timestamps = 0;
    this->relative_timestamps = 0;
    this->pcap = 0;
    this->csv = 0;
    this->stats = 0;
    this->nprint = 0;
    this->verbose = 0;
    this->live_capture = 0;
    this->output_index = 0;
    this->regex = nullptr;
    this->infile = nullptr;
    this->filter = nullptr;
    this->ip_file = nullptr;
    this->outfile = nullptr;
    this->device = nullptr;
}
