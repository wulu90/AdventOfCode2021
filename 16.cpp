#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <string>
#include <vector>

struct packet {
    int version;
    virtual ~packet() = default;
};

struct literal : packet {
    int64_t value;
};

struct op : packet {
    int id;
    std::vector<std::unique_ptr<packet>> subpackets;
};

std::unique_ptr<packet> parse_packet(const std::string& str, size_t start_pos, size_t& packet_len) {
    size_t tmp = start_pos;

    std::string version_str{str[start_pos], str[start_pos + 1], str[start_pos + 2]};
    int version = std::stoi(version_str, nullptr, 2);
    start_pos += 3;
    std::string type_str{str[start_pos], str[start_pos + 1], str[start_pos + 2]};
    int type = std::stoi(type_str, nullptr, 2);
    start_pos += 3;

    if (type == 4) {    // literal value

        literal lt;
        lt.version = version;
        std::string literal_str;
        while (str[start_pos] == '1') {
            start_pos += 1;
            literal_str.push_back(str[start_pos]);
            literal_str.push_back(str[start_pos + 1]);
            literal_str.push_back(str[start_pos + 2]);
            literal_str.push_back(str[start_pos + 3]);
            start_pos += 4;
        }

        // last group
        start_pos += 1;
        literal_str.push_back(str[start_pos]);
        literal_str.push_back(str[start_pos + 1]);
        literal_str.push_back(str[start_pos + 2]);
        literal_str.push_back(str[start_pos + 3]);

        start_pos += 4;

        // size_t tmplen = start_pos - tmp;
        // packet_len = tmplen % 4 == 0 ? tmplen : (tmplen / 4 + 1) * 4;
        packet_len = start_pos - tmp;
        lt.value   = std::stol(literal_str, nullptr, 2);
        return std::make_unique<literal>(lt);
    } else {    // op
        op oppack;
        oppack.version = version;
        oppack.id      = type;
        if (str[start_pos] == '0')    // total length in bits;
        {
            start_pos += 1;
            std::string len_str = str.substr(start_pos, 15);
            start_pos += 15;
            int16_t len = std::stoi(len_str, nullptr, 2);

            size_t sub_packet_lens = 0;
            while (sub_packet_lens < len) {
                size_t p_len;
                oppack.subpackets.push_back(parse_packet(str, start_pos, p_len));
                start_pos += p_len;
                sub_packet_lens += p_len;
            }

            packet_len = 3 + 3 + 1 + 15 + sub_packet_lens;
        } else {    // number of sub-packets immediately contained;
            start_pos += 1;

            std::string num_str = str.substr(start_pos, 11);
            start_pos += 11;
            int16_t num = std::stoi(num_str, nullptr, 2);

            size_t sub_packet_lens = 0;
            for (int16_t i = 0; i < num; i++) {
                size_t p_len;
                oppack.subpackets.push_back(parse_packet(str, start_pos, p_len));
                start_pos += p_len;
                sub_packet_lens += p_len;
            }

            packet_len = 3 + 3 + 1 + 11 + sub_packet_lens;
        }

        return std::make_unique<op>(std::move(oppack));
    }
}

int sum_versions(std::unique_ptr<packet>& p) {
    if (auto a = dynamic_cast<literal*>(p.get())) {
        return a->version;
    } else {
        auto o = dynamic_cast<op*>(p.get());

        return o->version +
               std::accumulate(o->subpackets.begin(), o->subpackets.end(), 0, [](int init, auto&& p) { return init + sum_versions(p); });

        // int r = o->version;
        // for (auto &p : o->subpackets)
        // {
        //     r += sum_versions(p);
        // }
        // return r;
    }
}

int main() {
    std::map<char, std::string> charmap{

        {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"}, {'4', "0100"}, {'5', "0101"},
        {'6', "0110"}, {'7', "0111"}, {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
        {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}

    };

    std::ifstream input("input/input-16");

    char c;
    std::string str;
    while (input >> c) {
        str += charmap[c];
    }

    size_t plen;
    auto pp = parse_packet(str, 0, plen);

    std::cout << sum_versions(pp) << std::endl;
}
