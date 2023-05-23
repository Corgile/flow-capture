#ifndef FLOW_CAPTURE_PCAP_PARSER_HPP
#define FLOW_CAPTURE_PCAP_PARSER_HPP

#if defined(__NetBSD__)
#include <net/if_ether.h>
#else
#include <net/ethernet.h>
#endif

#define LINUX_COOKED_HEADER_SIZE 16

#include <pcap.h>

#include "file_parser.hpp"

/*
 * Parses a PCAP from a written file
 */

class PCAPParser : public FileParser {
   public:
    PCAPParser();
    void process_file() override;
    void format_and_write_header() override;
    static void packet_handler(u_char *user_data,
                               const struct pcap_pkthdr *pkthdr,
                               const u_char *packet);
    int64_t process_timestamp(struct timeval ts);

   private:
    struct timeval mrt{};
    std::vector<std::string> to_fill;

    pcap_t *get_pcap_handle();
    pcap_t *open_live_handle();
    void set_filter(pcap_t *handle, char *filter);
};

#endif
