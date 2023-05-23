#ifndef FLOW_CAPTURE_FILE_WRITER_HPP
#define FLOW_CAPTURE_FILE_WRITER_HPP

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <regex>

#include "conf.hpp"
#include "packet/header/ethernet_header.hpp"
#include "packet/header/icmp_header.hpp"
#include "packet/header/ipv4_header.hpp"
#include "packet/header/ipv6_header.hpp"
#include "packet/header/radiotap_header.hpp"
#include "packet/header/tcp_header.hpp"
#include "packet/header/udp_header.hpp"
#include "packet/header/wlan_header.hpp"
#include "packet/payload.hpp"

/*
 * FileWriter takes care of output for all nPrints
 */

class FileWriter {
   public:
    void set_conf(Config c);
    void write_header(std::vector<std::string> header);
    void write_csv_stringvec(std::vector<std::string> &v);
    void write_bitstring_line(std::vector<std::string> &prefix,
                              std::vector<int8_t> &bistring_vec);

    void write_fields_line(std::vector<std::string> &prefix,
                           std::vector<std::string> &fields_vec);
    void write_line(std::string &line);

   private:
    void recursive_mkdir(char *path);
    FILE *fopen_mkdir(char *path);
    Config config;
    std::vector<uint32_t> keep_indexes;
    std::vector<std::string> build_bitstring_header(
        std::vector<std::string> header);
    uint32_t payload_len;
    FILE *outfile = nullptr;
};

#endif
