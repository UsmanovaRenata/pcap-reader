
#ifndef PACKET_READER_PCAPINFO_H
#define PACKET_READER_PCAPINFO_H
#include <netinet/ip.h>

struct ConnectionInfo{
    in_addr src_ip;
    in_addr dst_ip;
    uint16_t src_port;
    uint16_t dst_port;
    bool operator==(const ConnectionInfo& other) const {
        return src_ip.s_addr == other.src_ip.s_addr &&
               dst_ip.s_addr == other.dst_ip.s_addr &&
               src_port == other.src_port &&
               dst_port == other.dst_port;
    }
};

struct PacketInfo {
    size_t packet_count = 0;
    size_t byte_count = 0;
    PacketInfo& operator+=(const PacketInfo& other) {
        packet_count += other.packet_count;
        byte_count += other.byte_count;
        return *this;
    }
};


namespace std {
    template <>
    struct hash<ConnectionInfo> {
        std::size_t operator()(const ConnectionInfo& info) const {
            return std::hash<uint16_t>()(info.src_ip.s_addr) ^
                   std::hash<uint16_t>()(info.dst_ip.s_addr) ^
                   std::hash<uint16_t>()(info.src_port) ^
                   std::hash<uint16_t>()(info.dst_port);
        }
    };
}

#endif //PACKET_READER_PCAPINFO_H
