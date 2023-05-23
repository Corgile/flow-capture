#ifndef FLOW_CAPTURE_RADIOTAP_HEADER_HPP
#define FLOW_CAPTURE_RADIOTAP_HEADER_HPP

#include "packet_header.hpp"

#define SIZE_RADIOTAP_HEADER_BITSTRING 56

struct radiotap_header {
    uint8_t *radiotap_data; /* all bytes for radiotap_data 	*/
};

class RadiotapHeader : public PacketHeader {
   public:
    /* Required Functions */
    void *get_raw() override;
    void set_raw(void *raw) override;
    void print_header(FILE *out) override;
    uint32_t header_len() override;
    void fill_bit_vec(std::vector<int8_t> &to_fill, int8_t fill_with) override;
    void gen_bit_vec_header(std::vector<std::string> &to_fill) override;

   private:
    struct radiotap_header *raw = nullptr;
};

#endif
