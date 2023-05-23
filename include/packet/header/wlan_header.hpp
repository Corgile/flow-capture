#ifndef FLOW_CAPTURE_LAN_HEADER_HPP
#define FLOW_CAPTURE_LAN_HEADER_HPP

#include "packet_header.hpp"

// TODO: we only parse the first 10 bytes at this time
#define SIZE_WLAN_HEADER_BITSTRING 10

struct wlan_header {
    uint8_t type;
    uint8_t flag;
    uint16_t duration;
    uint8_t rx_addr[6];
    uint8_t tx_addr[6];
};

class WlanHeader : public PacketHeader {
   public:
    /* Required Functions */
    void *get_raw() override;
    void set_raw(void *raw_data) override;
    void print_header(FILE *out) override;
    uint32_t header_len() override;
    void fill_bit_vec(std::vector<int8_t> &to_fill, int8_t fill_with) override;
    void gen_bit_vec_header(std::vector<std::string> &to_fill) override;

    std::string get_tx_mac();

   private:
    struct wlan_header *raw = nullptr;
};

#endif
