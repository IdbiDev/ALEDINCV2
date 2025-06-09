#pragma once
#include <cstdint>

#define MAX_STRIPS 8
#define MAX_NAME_LEN 32

struct LedStripSaveData {
    uint8_t  type;
    uint8_t  pin;
    uint16_t led_count;
    uint8_t  animation_id;
    uint8_t  animation_speed;
    uint8_t  power;
    uint8_t  color[4]; // RGBA
    uint8_t  name_length; // UTF-8 hossz
    char     name[MAX_NAME_LEN];
} __attribute__((packed));

struct FlashSaveFormat {
    LedStripSaveData strips[MAX_STRIPS];
    uint32_t crc32; // Opcionális, később használhatod
} __attribute__((packed));
