#include "packet/payload.hpp"

void *Payload::get_raw() {
    return raw;
}

void Payload::set_raw(void *raw) {
    this->raw = raw;
}

void Payload::print_header(FILE *out) {
    fprintf(out, "Payload: length: %d\n", n_bytes);
}
uint32_t Payload::header_len() {
    return n_bytes;
}

void Payload::fill_bit_vec(std::vector<int8_t> &to_fill, int8_t fill_with) {
    int32_t zero_byte_width;
    zero_byte_width = max_payload_len - n_bytes;
    /* If no payload fill with max payload bytes */
    if (n_bytes == 0) {
        make_bitstring(max_payload_len, nullptr, to_fill, fill_with);
    }
    /* If payload but payload is smaller than maximum payload length */
    else if (zero_byte_width > 0) {
        make_bitstring(n_bytes, raw, to_fill, fill_with);
        make_bitstring(zero_byte_width, nullptr, to_fill, fill_with);
    }
    /* Payload is larger or as large as maximum payload length, */
    else {
        make_bitstring(max_payload_len, raw, to_fill, fill_with);
    }
}

void Payload::gen_bit_vec_header(std::vector<std::string> &to_fill) {
    std::vector<std::tuple<std::string, uint32_t>> v;

    if (max_payload_len == 0)
        return;

    v.emplace_back("payload_bit", max_payload_len * 8);
    PacketHeader::make_bitstring_header(v, to_fill);
}

/* Specific to Payload */

void Payload::set_info(uint32_t n_bytes, uint32_t max_payload_len) {
    this->n_bytes = n_bytes;
    this->max_payload_len = max_payload_len;
}
