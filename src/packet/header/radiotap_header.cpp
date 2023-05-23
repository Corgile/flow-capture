#include "packet/header/radiotap_header.hpp"

void *RadiotapHeader::get_raw() {
    return (void *)raw;
}

void RadiotapHeader::set_raw(void *raw) {
    this->raw = (struct radiotap_header *)raw;
}

void RadiotapHeader::print_header(FILE *out) {
    if (raw == nullptr) {
        fprintf(out, "RadiotapHeader: raw data not set\n");
    } else {
        fprintf(out, "RadiotapHeader: %d bytes\n", header_len());
    }
}

uint32_t RadiotapHeader::header_len() {
    return SIZE_RADIOTAP_HEADER_BITSTRING;
}

void RadiotapHeader::fill_bit_vec(std::vector<int8_t> &to_fill,
                                  int8_t fill_with) {
    make_bitstring(SIZE_RADIOTAP_HEADER_BITSTRING, raw, to_fill, fill_with);
}

void RadiotapHeader::gen_bit_vec_header(std::vector<std::string> &to_fill) {
    std::vector<std::tuple<std::string, uint32_t>> v;

    v.push_back(std::make_tuple("radiotap_reversion", 1 * 8));
    v.push_back(std::make_tuple("radiotap_pad0", 1 * 8));
    v.push_back(std::make_tuple("radiotap_len", 2 * 8));
    v.push_back(std::make_tuple("radiotap_present", 12 * 8));
    v.push_back(std::make_tuple("radiotap_mactimestamp", 8 * 8));
    v.push_back(std::make_tuple("radiotap_flags", 1 * 8));
    v.push_back(std::make_tuple("radiotap_rate", 1 * 8));
    v.push_back(std::make_tuple("radiotap_channel", 2 * 8));
    v.push_back(std::make_tuple("radiotap_channelflags", 2 * 8));
    v.push_back(std::make_tuple("radiotap_antennasignal", 1 * 8));
    v.push_back(std::make_tuple("radiotap_pad1", 1 * 8));
    v.push_back(std::make_tuple("radiotap_rxflags", 2 * 8));
    v.push_back(std::make_tuple("radiotap_pad2", 6 * 8));
    v.push_back(std::make_tuple("radiotap_timestamp", 12 * 8));
    v.push_back(std::make_tuple("radiotap_antennas", 4 * 8));

    PacketHeader::make_bitstring_header(v, to_fill);
}