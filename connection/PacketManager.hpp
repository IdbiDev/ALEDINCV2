#pragma once
#include <vector>
#include <cstdint>

class PacketManager {
public:
    struct Packet {
        uint8_t id;
        std::vector<uint8_t> data;
    };

    PacketManager();

    bool process(Packet& outPacket); 
    void reset();

private:
    std::vector<uint8_t> buffer;
    static constexpr uint16_t MAGIC = 0xABCD;

    void read_serial();
    bool try_extract_packet(Packet& outPacket);
};
