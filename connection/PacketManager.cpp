#include "PacketManager.hpp"
#include "pico/stdlib.h"
#include <cstring>
#include <stdio.h>

PacketManager::PacketManager() {
    buffer = ByteBuffer();
}
void PacketManager::read_exact(size_t count) {
    while (count > 0) {
        int c = getchar_timeout_us(1000); // vár max 1ms-ot
        if (c != PICO_ERROR_TIMEOUT) {
            //buffer.write_uint8(static_cast<uint8_t>(c));
            count--;
        }
    }
}
bool PacketManager::process(Packet& outPacket) {

    read_exact(4);
    if(buffer.read_uint16() != 0xABCD){//magic Number
        return false;
    }
    uint16_t payloadSize = buffer.read_uint16();
    read_exact(payloadSize);//payload size
    outPacket.id = buffer.read_uint8();
    outPacket.data = buffer.read_bytes(payloadSize - 1);
    buffer.clear();
    return true;
}

void PacketManager::send_packet(const Packet& dataPacket) {
    ByteBuffer newBuffer; //wtf is this cpp

    uint16_t payloadLength = dataPacket.data.data_size() + 1;  // +1 for the packet ID

    newBuffer.write_uint16(0xABCD);                              // Packet header
    newBuffer.write_uint16(payloadLength);                       // Payload size
    newBuffer.write_uint8(dataPacket.id);                        // Packet type
    newBuffer.write_bytes(dataPacket.data.data(), dataPacket.data.data_size()); // Payload
    fwrite(newBuffer.data(), 1, newBuffer.data_size(), stdout);  
}
void PacketManager::complete() {
    Packet packet;
    packet.id = READY;
    packet.data.write_uint8(READY);
    send_packet(packet);
    packet.data.clear();
    
}
void PacketManager::complete_error(const uint8_t errorCode){
    Packet packet;
    packet.id = ERROR;
    packet.data.write_uint8(errorCode);
    send_packet(packet);
    packet.data.clear();
}