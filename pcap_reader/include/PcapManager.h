
#ifndef PACKET_READER_PCAPMANAGER_H
#define PACKET_READER_PCAPMANAGER_H

#include "PacketHandler.h"

class PcapManager {
public:
    PcapManager();
    void start_packet_capture();
    void close_device() const ;
    void save_to_file(const char* fileName) const;
    ~PcapManager();
private:
    static void packet_handler_static(unsigned char *data, const struct pcap_pkthdr *pkthdr, const unsigned char *packet);
    PacketHandler *packetHandler;
    pcap_t* handle;
};





#endif //PACKET_READER_PCAPMANAGER_H
