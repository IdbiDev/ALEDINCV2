#include "PacketManager.hpp"
#include "pico/stdlib.h"
#include <cstring>

PacketManager::PacketManager() {
    buffer.reserve(256);
}

void PacketManager::read_serial() {
    int c = getchar_timeout_us(0);
    while (c != PICO_ERROR_TIMEOUT) {
        buffer.push_back(static_cast<uint8_t>(c));
        c = getchar_timeout_us(0);
    }
}

bool PacketManager::try_extract_packet(Packet& outPacket) {
    if (buffer.size() < 5)
        return false;

    // Read header
    uint16_t magic = buffer[0] | (buffer[1] << 8);
    if (magic != MAGIC) {
        // Invalid magic, shift buffer
        buffer.erase(buffer.begin());
        return false;
    }

    uint16_t length = buffer[2] | (buffer[3] << 8);

    if (buffer.size() < 4 + length)
        return false; // Not enough data yet

    // Extract packet
    outPacket.id = buffer[4];
    outPacket.data.assign(buffer.begin() + 5, buffer.begin() + 4 + length);

    // Remove packet from buffer
    buffer.erase(buffer.begin(), buffer.begin() + 4 + length);
    return true;
}

bool PacketManager::process(Packet& outPacket) {
    read_serial();
    return try_extract_packet(outPacket);
}

void PacketManager::reset() {
    buffer.clear();
}
