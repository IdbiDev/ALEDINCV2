#pragma once

#include "led/LedStrip.hpp"
#include "hardware/flash.h"
#include "pico/stdlib.h"

#define FLASH_TARGET_OFFSET (256 * 1024) // 256KB offset

class SettingsManager {
public:
    static void save(LedStrip* strips, uint8_t count);
    static void load(LedStrip* strips, uint8_t maxCount);
};
