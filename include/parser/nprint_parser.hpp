#ifndef FLOW_CAPTURE_NPRINT_PARSER_HPP
#define FLOW_CAPTURE_NPRINT_PARSER_HPP

#include <netinet/ip.h>
#include <pcap.h>

#include <tuple>

#include "packet/superpacket.hpp"
#include "parser/file_parser.hpp"

/*
 * NprintParser is used to transform any nPrint back to a PCAP
 */

class NprintParser : public FileParser {
   public:
    void process_file() override;
    void format_and_write_header() override;

   private:
    std::string clean_line(std::string &line);
    uint8_t *transform_bitstring(std::string &bits);
    std::tuple<void *, uint64_t> parse_packet(std::string &bits);
};

#endif
