#pragma once
#include <cstdint>
#include <cstring>

class ByteBuffer {
public:
    static constexpr size_t FIXED_CAPACITY = 256;

    ByteBuffer()
        : buffer(small), capacity(FIXED_CAPACITY), size(0), position(0), usingHeap(false) {}

    ~ByteBuffer() {
        release_heap();
    }

    // === Write ===
    void write_uint8(uint8_t value) {
        ensure_capacity(size + 1);
        buffer[size++] = value;
    }

    void write_uint16(uint16_t value) {
        ensure_capacity(size + 2);
        buffer[size++] = value & 0xFF;
        buffer[size++] = (value >> 8) & 0xFF;
    }

    void write_bytes(const uint8_t* data, size_t length) {
        ensure_capacity(size + length);
        std::memcpy(buffer + size, data, length);
        size += length;
    }

    // === Read ===
    uint8_t read_uint8() {
        return (position < size) ? buffer[position++] : 0;
    }

    uint16_t read_uint16() {
        uint16_t lo = read_uint8();
        uint16_t hi = read_uint8();
        return lo | (hi << 8);
    }

    void read_bytes(uint8_t* dest, size_t length) {
        if (position + length <= size) {
            std::memcpy(dest, buffer + position, length);
            position += length;
        }
    }
    ByteBuffer read_bytes(size_t length) {
        ByteBuffer out;
        if (position + length <= size) {
            out.write_bytes(buffer + position, length);
            position += length;
        }
        return out;
    }

    // === Buffer Management ===
    const uint8_t* data() const { return buffer; }
    size_t data_size() const { return size; }
    size_t remaining() const { return size - position; }

    void reset() { position = 0; }

    void clear() {
        std::memset(buffer, 0, capacity);
        size = 0;
        position = 0;

        if (usingHeap) {
            release_heap();
            buffer = small;
            capacity = FIXED_CAPACITY;
            usingHeap = false;
        }
    }

private:
    uint8_t small[FIXED_CAPACITY];
    uint8_t* buffer;
    size_t capacity;
    size_t size;
    size_t position;
    bool usingHeap;

    void ensure_capacity(size_t new_cap) {
        if (new_cap <= capacity) return;

        size_t new_capacity = (new_cap * 3) / 2;
        uint8_t* new_buffer = new uint8_t[new_capacity];
        std::memcpy(new_buffer, buffer, size);

        if (usingHeap) delete[] buffer;
        buffer = new_buffer;
        capacity = new_capacity;
        usingHeap = true;
    }

    void release_heap() {
        if (usingHeap && buffer) {
            delete[] buffer;
            buffer = nullptr;
        }
    }
};
