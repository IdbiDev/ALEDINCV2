#pragma once
#include <vector>
#include <cstdint>
#include "Utils.hpp"
#include "ByteBuffer.hpp"

class PacketManager {
public:
    PacketManager();
    bool process(Packet& outPacket); 
    void read_exact(size_t count);
private:
    ByteBuffer buffer;
};
