#include "parser/file_writer.hpp"

#include <utility>

void FileWriter::set_conf(const Config& c) {
    this->config = c;
    if (c.outfile == nullptr) {
        this->outfile = stdout;
    } else {
        if (std::string(c.outfile).find('/') == std::string::npos) {
            this->outfile = fopen(c.outfile, "w");
        } else {
            this->outfile = fopen_mkdir(c.outfile);
        }
    }
}

void FileWriter::recursive_mkdir(char *path) {
    char *sep;

    sep = strrchr(path, '/');
    if (sep != nullptr) {
        *sep = 0;
        if (strcmp(path, "") != 0)
            recursive_mkdir(path);
        *sep = '/';
    }
    if (mkdir(path, 0777) && errno != EEXIST) {
        fprintf(stderr, "error while trying to create '%s'\n", path);
    }
}

FILE *FileWriter::fopen_mkdir(char *path) {
    char *sep, *path0;

    sep = strrchr(path, '/');
    if (sep) {
        path0 = strdup(path);
        path0[sep - path] = 0;
        recursive_mkdir(path0);
        free(path0);
    }
    return fopen(path, "w");
}

void FileWriter::write_header(std::vector<std::string> header) {
    if (outfile == nullptr) {
        fprintf(stderr, "FileWriter output configuration not set\n");
        exit(2);
    }

    std::vector<std::string> compressed_header;

    compressed_header = build_bitstring_header(std::move(header));
    write_csv_bit_vec(compressed_header);
}

std::vector<std::string> FileWriter::build_bitstring_header(
    std::vector<std::string> header) {
    uint32_t i, prefix_len;
    Payload p;
    RadiotapHeader r;
    WlanHeader w;
    EthHeader e;
    IPv4Header v4;
    IPv6Header v6;
    TCPHeader tcp;
    UDPHeader udp;
    ICMPHeader icmp;
    std::vector<std::string> compressed_header;

    prefix_len = header.size();
    /* Need to inform the payload of the max len */
    p.set_info(0, config.payload);

    if (config.radiotap == 1)
        r.gen_bit_vec_header(header);
    if (config.wlan == 1)
        w.gen_bit_vec_header(header);
    if (config.eth == 1)
        e.gen_bit_vec_header(header);
    if (config.ipv4 == 1)
        v4.gen_bit_vec_header(header);
    if (config.ipv6 == 1)
        v6.gen_bit_vec_header(header);
    if (config.tcp == 1)
        tcp.gen_bit_vec_header(header);
    if (config.udp == 1)
        udp.gen_bit_vec_header(header);
    if (config.icmp == 1)
        icmp.gen_bit_vec_header(header);
    if (config.payload != 0)
        p.gen_bit_vec_header(header);

    for (i = 0; i < prefix_len; i++)
        compressed_header.push_back(header[i]);

    if (config.regex != nullptr) {
        std::regex str_regex(config.regex);
        for (i = prefix_len; i < header.size(); i++) {
            if (!regex_match(header[i], str_regex)) {
                keep_indexes.push_back(i - prefix_len);
                compressed_header.push_back(header[i]);
            }
        }
    } else {
        for (i = prefix_len; i < header.size(); i++) {
            keep_indexes.push_back(i - prefix_len);
            compressed_header.push_back(header[i]);
        }
    }

    return compressed_header;
}

void FileWriter::write_csv_bit_vec(std::vector<std::string> &v) {
    uint32_t i;

    for (i = 0; i < v.size(); i++) {
        fprintf(outfile, "%s", v[i].c_str());
        if (i != v.size() - 1)
            fprintf(outfile, ",");
    }
    fprintf(outfile, "\n");
}

void FileWriter::write_bitstring_line(std::vector<std::string> &prefix,
                                      std::vector<int8_t> &bitstring_vec) {
    uint32_t i;

    for (i = 0; i < prefix.size(); i++) {
        if (keep_indexes.empty()) {
            fprintf(outfile, "%s", prefix[i].c_str());
        } else {
            fprintf(outfile, "%s,", prefix[i].c_str());
        }
    }

    for (i = 0; i < keep_indexes.size(); i++) {
        fprintf(outfile, "%d", bitstring_vec[keep_indexes[i]]);
        if (i != keep_indexes.size() - 1)
            fprintf(outfile, ",");
    }
    fprintf(outfile, "\n");
}
