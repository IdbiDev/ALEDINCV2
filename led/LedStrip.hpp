#pragma once
#include <vector>
#include <cstdint>
#include "Utils.hpp"
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
    Color color;

    LedStrip();

    void refresh_led_strip();
    bool is_sound_visualize();
    void fill();
    void set_pixel_color(uint16_t pixel,Color color);

    void show_pixels();
}; 