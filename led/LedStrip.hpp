#pragma once
#include <cstdint>
#include "Utils.hpp"
#include "hardware/dma.h"
#include "hardware/pio.h"
//#include <string>

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

    uint8_t* brightness_levels;
    uint32_t* dimmer_buffer;

    
/*  brightness_levels = nullptr;
    dimmer_buffer = nullptr;
    dma_channel = -1;
    pio = nullptr;
    sm = -1;  */


    PIO pio;
    uint sm;
    int dma_channel = -1;

    LedStrip();
    ~LedStrip();

    void configure(uint8_t id, uint8_t type, uint8_t pin, char* name, uint16_t led_count, uint8_t animation, uint8_t animation_speed, bool pwr, Color base_color);
    void re_init();
    void fill(Color color);
    void set_pixel_color(uint16_t pixel,Color color);
    void show(bool force);
private:
    void allocate();
    void release();
}; 