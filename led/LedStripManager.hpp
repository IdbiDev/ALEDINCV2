#pragma once
#include <cstdint>
#include "Utils.hpp"
#include "LedStrip.hpp"

#define MAX_LED_AMOUNT 8

class LedStripManager{
public:
    LedStripManager();
    uint8_t get_next_id();
    void free_id(uint8_t id);
    
    LedStrip led_strips[MAX_LED_AMOUNT];
private:
    bool id_list[MAX_LED_AMOUNT];
};