#pragma once
#include <vector>
#include <cstdint>

class LedStrip{
public:
    uint8_t type;
    uint8_t id;
    uint8_t pin;
    char* name;
    uint16_t led_count;
    uint8_t animation_id;
    uint8_t animation_speed;
    bool power;
    uint8_t color[4];

    LedStrip();
}; 