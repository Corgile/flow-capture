#ifndef FLOW_CAPTURE_FILE_PARSER_HPP
#define FLOW_CAPTURE_FILE_PARSER_HPP

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <csignal>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "conf.hpp"
#include "packet/superpacket.hpp"
#include "parser/file_writer.hpp"
#include "stats.hpp"

/*
 * File parser abstract class, any input file type that is new must conform to
 * this abstract class definition
 */

class FileParser {
   public:
    virtual ~FileParser()= default;
    virtual void process_file() = 0;
    virtual void format_and_write_header() = 0;
    void print_stats();
    void set_conf(Config c);
    void set_fileWriter(FileWriter *writer);
    SuperPacket *process_packet(void *pkt);
    static void tokenize_line(const std::string& line, std::vector<std::string> &to_fill,
                       char delimiter = ',');

   protected:
    Stats stat;
    Config config;
    FileWriter *fw;
    uint32_t linktype;
    void write_output(SuperPacket *sp);
    // static void signal_handler(int signum);

    std::vector<std::string> custom_output;
    std::vector<int8_t> bitstring_vec;
    std::vector<std::string> fields_vec;

   private:
    std::string output_type;
};

#endif
