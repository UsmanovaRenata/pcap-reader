
#include "../include/PcapManager.h"
#include <iostream>
#include <fstream>

PcapManager::PcapManager() {
    packetHandler = new PacketHandler();
    handle = nullptr;
}

void PcapManager::start_packet_capture(){

    char errbuf[PCAP_ERRBUF_SIZE];
    char *dev = pcap_lookupdev(errbuf);
    if (dev == nullptr) {
        std::cerr << "Error finding network device: " << errbuf << std::endl;
        return;
    }

    std::cout << "Using network device: " << dev << std::endl;

    handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (handle == nullptr) {
        std::cerr << "Error opening device " << dev << ": " << errbuf << std::endl;
        return;
    }
    pcap_loop(handle, 100, packet_handler_static, reinterpret_cast<unsigned char*>(packetHandler));

}

void PcapManager::close_device() const {
    pcap_close(handle);
    std::cout << "Device was closed" << std::endl;
}

PcapManager::~PcapManager() {
    delete packetHandler;
}

void PcapManager::packet_handler_static(unsigned char *data, const struct pcap_pkthdr *pkthdr, const unsigned char *packet) {
    auto* newPacketHandler = reinterpret_cast<PacketHandler*>(data);
    newPacketHandler->packet_handler(data, pkthdr, packet);
}

void PcapManager::save_to_file(const char *fileName) const{

    std::ofstream csv_file(fileName);
    auto info = packetHandler->get_info();
    if (!csv_file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }
    csv_file << "Source IP,Destination IP,Source Port,Destination Port,Packet Count,Byte Count" << std::endl;
    for (const auto& entry : info) {
        const ConnectionInfo& info_key = entry.first;
        const PacketInfo& info_val = entry.second;
        csv_file << inet_ntoa(info_key.src_ip) << ","
                 << inet_ntoa(info_key.dst_ip) << ","
                 << info_key.src_port << ","
                 << info_key.dst_port << ","
                 << info_val.packet_count << ","
                 << info_val.byte_count << std::endl;
    }

    csv_file.close();

}






