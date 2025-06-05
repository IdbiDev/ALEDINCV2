#pragma once
#include <cstdint>
#include "Utils.hpp"
#include "ByteBuffer.hpp"
#include <cstddef>
class PacketManager {
public:
    PacketManager();
    bool process(Packet& outPacket); 
    void read_exact(size_t count);
    void send_packet(const Packet& dataPacket);
    void complete();
    void complete_error(const uint8_t errorCode);
private:
    ByteBuffer buffer;
};
