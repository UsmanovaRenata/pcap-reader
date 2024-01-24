#include "include/PcapManager.h"

int main() {
    PcapManager pcapManager;
    pcapManager.start_packet_capture();
    pcapManager.close_device();
    pcapManager.save_to_file("../../first_program.csv");
    return 0;
}
