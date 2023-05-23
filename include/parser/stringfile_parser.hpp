

#ifndef FLOW_CAPTURE_STRINGFILE_PARSER_HPP
#define FLOW_CAPTURE_STRINGFILE_PARSER_HPP

#include "parser/file_parser.hpp"

/*
 * StringFileParser parses hex encoded packets in a CSV.For example, the
 * output of a zmap scan
 */

class StringFileParser : public FileParser {
   public:
    void process_file() override;
    void format_and_write_header() override;

   private:
    uint32_t num_cols;
    static int hex_value(char hex_digit);
    void format_custom_output(std::vector<std::string> &tokens);
    static std::string hex_to_string(std::string input);
};

#endif
