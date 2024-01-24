
#ifndef PACKET_READER_PACKETHANDLER_H
#define PACKET_READER_PACKETHANDLER_H
#include <pcap.h>
#include <unordered_map>
#include "PcapInfo.h"

class PacketHandler {
public:
    PacketHandler() : info() {};
    void packet_handler(unsigned char *data, const struct pcap_pkthdr *pkthdr, const unsigned char *packet);
    const std::unordered_map<ConnectionInfo, PacketInfo>& get_info() const;
private:
    std::unordered_map<ConnectionInfo, PacketInfo> info;
};


#endif //PACKET_READER_PACKETHANDLER_H
