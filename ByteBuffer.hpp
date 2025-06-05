#pragma once
#include <vector>
#include <cstdint>
#include <cstring>

class ByteBuffer {
public:
    ByteBuffer() : position(0) {
        buffer.reserve(256); // Reserve space to avoid reallocations
    }

    ByteBuffer(const std::vector<uint8_t>& data) : buffer(data), position(0) {
        buffer.reserve(256); // Still allow some growth
    }

    void write_uint8(uint8_t value) {
        buffer.push_back(value);
    }

    void write_uint16(uint16_t value) {
        buffer.push_back(value & 0xFF);
        buffer.push_back((value >> 8) & 0xFF);
    }

    void write_bytes(const std::vector<uint8_t>& data) {
        buffer.insert(buffer.end(), data.begin(), data.end());
    }

    uint8_t read_uint8() {
        ensure_available(1);
        return buffer[position++];
    }

    uint16_t read_uint16() {
        ensure_available(2);
        uint16_t result = buffer[position] | (buffer[position + 1] << 8);
        position += 2;
        return result;
    }

    std::vector<uint8_t> read_bytes(size_t length) {
        ensure_available(length);
        std::vector<uint8_t> result(buffer.begin() + position, buffer.begin() + position + length);
        position += length;
        return result;
    }

    const std::vector<uint8_t>& data() const {
        return buffer;
    }

    void clear() {
        buffer.clear();
        buffer.reserve(256); // Re-reserve after clear
        position = 0;
    }

    size_t size() const {
        return buffer.size();
    }

    size_t remaining() const {
        return buffer.size() - position;
    }

    void reset() {
        position = 0;
    }

private:
    std::vector<uint8_t> buffer;
    size_t position;

    void ensure_available(size_t size) {
        return;
    }
};
