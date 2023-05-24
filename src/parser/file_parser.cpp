#include "parser/file_parser.hpp"

#include <utility>

#define CUSTOM_OUTPUT_RESERVE_SIZE 50
#define BITSTRING_RESERVE_SIZE 10000

void FileParser::set_conf(Config c) {
  this->config = std::move(c);
  
  /* Write header when we set the config */
  format_and_write_header();
  
  /* Reserve vectors and use them the entire time */
  custom_output.reserve(CUSTOM_OUTPUT_RESERVE_SIZE);
  bitstring_vec.reserve(BITSTRING_RESERVE_SIZE);
}

void FileParser::set_fileWriter(FileWriter *writer) {
  this->fw = writer;
}

void FileParser::tokenize_line(const std::string &line,
                               std::vector<std::string> &vec,
                               char delimiter) {
  std::string token;
  std::stringstream ss;
  
  vec.clear();
  ss.str(line);
  while (getline(ss, token, delimiter)) { vec.push_back(token); }
}

SuperPacket *FileParser::process_packet(void *pkt) {
  bool parseable;
  SuperPacket *sp;
  std::string src_ip;
  std::vector<std::string> to_fill;
  std::map<std::string, std::uint32_t>::iterator mit;
  uint8_t network_layer, transport_layer;
  
  to_fill.clear();
  sp = new SuperPacket(pkt, config.payload, linktype);
  parseable = sp->check_parseable();
  if (!parseable) {
    delete sp;
    network_layer = 0;
    transport_layer = 0;
    stat.update(parseable, network_layer, transport_layer);
    return nullptr;
  }
  if (config.verbose)
    sp->print_packet(stderr);
  /* Exit when done */
  if (config.num_packets != 0 &&
      stat.get_packets_processed() >= config.num_packets)
    exit(0);
  std::tie(network_layer, transport_layer) = sp->get_packet_type();
  stat.update(parseable, network_layer, transport_layer);
  
  return sp;
}

void FileParser::write_output(SuperPacket *sp) {
  sp->fill_bit_vec(&config, bitstring_vec);
  fw->write_bitstring_line(custom_output, bitstring_vec);
  bitstring_vec.clear();
  custom_output.clear();
  
  delete sp;
}

void FileParser::print_stats() {
  stat.print_stats();
}
