#include "PacketManager.hpp"
#include "pico/stdlib.h"
#include <cstring>


PacketManager::PacketManager() {
    buffer = ByteBuffer();
}
void PacketManager::read_exact(size_t count) {
    while (count > 0) {
        int c = getchar_timeout_us(1000); // vár max 1ms-ot
        if (c != PICO_ERROR_TIMEOUT) {
            buffer.write_uint8(static_cast<uint8_t>(c));
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
