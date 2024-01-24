cmake_minimum_required(VERSION 3.22)
project(packet_reader)

set(CMAKE_CXX_STANDARD 17)

add_executable(packet_reader main.cpp
        include/PcapManager.h
        src/PcapManager.cpp
        include/PcapInfo.h
        src/PacketHandler.cpp
        include/PacketHandler.h)

find_library(PCAP_LIBRARY pcap)

target_link_libraries(packet_reader ${PCAP_LIBRARY})
