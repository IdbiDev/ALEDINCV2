#include "SettingsManager.hpp"
#include "hardware/sync.h"
#include "hardware/flash.h"

void SettingsManager::save(LedStrip* strips, uint8_t count) {
    FlashSaveFormat saveData = {};

    if (count > MAX_STRIPS) count = MAX_STRIPS;

    for (uint8_t i = 0; i < count; ++i) {
        const LedStrip& s = strips[i];
        LedStripSaveData& d = saveData.strips[i];

        d.type = s.type;
        d.pin = s.pin;

        size_t nameLen = strlen(s.name);
        if (nameLen >= MAX_NAME_LEN) nameLen = MAX_NAME_LEN - 1;
        d.name_length = nameLen;
        memcpy(d.name, s.name, nameLen);
        d.name[nameLen] = '\0';

        d.led_count = s.led_count;
        d.animation_id = s.animation_id;
        d.animation_speed = s.animation_speed;
        d.power = s.power;
        d.color[0] = s.color.r;
        d.color[1] = s.color.g;
        d.color[2] = s.color.b;
        d.color[3] = s.color.a;
    }

    uint32_t ints = save_and_disable_interrupts();
    flash_range_erase(FLASH_TARGET_OFFSET, sizeof(FlashSaveFormat));
    flash_range_program(FLASH_TARGET_OFFSET, reinterpret_cast<const uint8_t*>(&saveData), sizeof(FlashSaveFormat));
    restore_interrupts(ints);
}

void SettingsManager::load(LedStrip* strips, uint8_t maxCount) {
    const FlashSaveFormat* saved = reinterpret_cast<const FlashSaveFormat*>(XIP_BASE + FLASH_TARGET_OFFSET);

    for (uint8_t i = 0; i < maxCount; ++i) {
        const LedStripSaveData& d = saved->strips[i];

        // Érvényes adat ellenőrzése
        if (d.type == 0xFF && d.led_count == 0xFFFF) break;

        LedStrip& s = strips[i];
        s.type = d.type;
        s.pin = d.pin;
        strncpy(s.name, d.name, d.name_length);
        s.name[d.name_length] = '\0';
        s.led_count = d.led_count;
        s.animation_id = d.animation_id;
        s.animation_speed = d.animation_speed;
        s.power = d.power;
        s.color = { d.color[0], d.color[1], d.color[2], d.color[3] };
    }
}