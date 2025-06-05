#pragma once
#include <cstdint>
#include "ByteBuffer.hpp"
#pragma pack(push, 1)
struct Color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};
#pragma pack(pop)
#pragma pack(push, 1)
struct Packet {
        uint8_t id;
        ByteBuffer data;
};
#pragma pack(pop)

constexpr uint8_t TEST_CONNECTION = 0;
constexpr uint8_t READY = 1;
constexpr uint8_t UPDATE_LED_STRIP_POWER = 2;
constexpr uint8_t ERROR = 3;
constexpr uint8_t CONTROLLER_REQUEST_SETTINGS = 5;
constexpr uint8_t UPDATE_LED_STRIP_PROPERTIES = 4;
constexpr uint8_t UPDATE_LED_STRIP_FILL_COLOR = 6;
constexpr uint8_t UPDATE_LED_STRIP_PER_LED_COLOR = 8;
constexpr uint8_t HOST_REQUEST_SETTINGS = 10;
constexpr uint8_t HOST_SEND_SETTINGS = 12;
constexpr uint8_t CONTROLLER_SEND_SETTINGS = 7;
constexpr uint8_t CONTROLLER_SEND_DEBUG_MESSAGE = 9;
