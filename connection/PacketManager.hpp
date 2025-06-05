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
private:
    ByteBuffer buffer;
};
