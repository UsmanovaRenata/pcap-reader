
#include <iostream>
#include <netinet/ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include "../include/PacketHandler.h"

void PacketHandler::packet_handler(unsigned char *data, const struct pcap_pkthdr *pkthdr, const unsigned char *packet) {
    const struct ether_header *ethernet_header = (struct ether_header *)packet;
    ConnectionInfo info_key{};
    PacketInfo info_val{};
    if (ntohs(ethernet_header->ether_type) == ETHERTYPE_IP) {
        const struct ip *ip_header = (struct ip *)(packet + sizeof(struct ether_header));
        if (ip_header->ip_v == IPVERSION && (ip_header->ip_p == IPPROTO_TCP || ip_header->ip_p == IPPROTO_UDP)) {
            info_key.src_ip = ip_header->ip_src;
            info_key.dst_ip = ip_header->ip_dst;
            if (ip_header->ip_p == IPPROTO_TCP) {
                const struct tcphdr *tcp_header = (struct tcphdr *)(packet + sizeof(struct ether_header) + ip_header->ip_hl * 4);
                info_key.src_port = ntohs(tcp_header->th_sport);
                info_key.dst_port = ntohs(tcp_header->th_dport);
            } else if (ip_header->ip_p == IPPROTO_UDP) {
                const struct udphdr *udp_header = (struct udphdr *)(packet + sizeof(struct ether_header) + ip_header->ip_hl * 4);
                info_key.src_port = ntohs(udp_header->uh_sport);
                info_key.dst_port = ntohs(udp_header->uh_dport);
            }else{
                return;
            }
            std::cout << "...\n";
            info_val.byte_count = pkthdr->len;
            info_val.packet_count = 1;
            info[info_key] += info_val;
        }else{
            return;
        }
    } else{
        return;
    }
}

const std::unordered_map<ConnectionInfo, PacketInfo> &PacketHandler::get_info() const{
    return info;
}
