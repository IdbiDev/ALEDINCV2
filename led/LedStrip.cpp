#include "LedStrip.hpp"


void LedStrip::allocate() {
    dma_channel = dma_claim_unused_channel(true);
        if (id >= 8) {
        // Érvénytelen ID esetén default érték (pio0, sm0)
        pio = pio0;
        sm = 0;
        return;
    }

    pio = (id < 4) ? pio0 : pio1;
    sm = id % 4;

    brightness_levels = new uint8_t[led_count];
    dimmer_buffer = new uint32_t[led_count];
    for (int i = 0; i < led_count; ++i) {
        brightness_levels[i] = 127;
        dimmer_buffer[i] = 0;
    }
}
LedStrip::~LedStrip() {
    release();
}

void LedStrip::release() {
    delete[] brightness_levels;
    delete[] dimmer_buffer;
    brightness_levels = nullptr;
    dimmer_buffer = nullptr;
    dma_channel = -1;
    pio = nullptr;
    sm = -1;
}

void LedStrip::show(bool force) {
    if (!power && !force) return;

    // Ellenőrizzük, hogy van-e DMA csatorna
    if (dma_channel < 0) return;

    // Konfiguráljuk a DMA csatornát
    dma_channel_config cfg = dma_channel_get_default_config(dma_channel);
    channel_config_set_transfer_data_size(&cfg, DMA_SIZE_32);
    channel_config_set_read_increment(&cfg, true);
    channel_config_set_write_increment(&cfg, false);

    // DMA DREQ PIO-hoz
    channel_config_set_dreq(&cfg, pio_get_dreq(pio, sm, true)); // jobb mint DREQ_PIO0_TX0

    // Elindítjuk az adatátvitelt a dimmer_buffer-ből a PIO FIFO-ba
    dma_channel_configure(
        dma_channel,
        &cfg,
        &pio->txf[sm],        // PIO TX FIFO címe
        dimmer_buffer,        // LED adat buffer
        led_count,            // 32 bites szavak száma
        true                  // Induljon azonnal
    );
}
void LedStrip::set_pixel_color(uint16_t pixel, Color c) {
    if (pixel >= led_count) return;
    brightness_levels[pixel] = c.a;
    int r = (c.r * c.a) / 255;
    int g = (c.g * c.a) / 255;
    int b = (c.b * c.a) / 255;

    if (type == LED_TYPE_GRB) {
        dimmer_buffer[pixel] = (g << 16) | (r << 8) | b;
    } else { 
        dimmer_buffer[pixel] = (r << 16) | (g << 8) | b;
    }
}

void LedStrip::fill(Color c) {
    for (int i = 0; i < led_count; ++i)
        set_pixel_color(i, c);
}
void LedStrip::configure(uint8_t id, uint8_t type, uint8_t pin, std::string name, uint16_t led_count, uint8_t animation, uint8_t animation_speed, bool pwr, Color base_color){
    LedStrip::id = id;
    LedStrip::pin = pin;
    LedStrip::name = name;
    LedStrip::led_count = led_count;
    LedStrip::type = type;
    LedStrip::animation_id = animation;
    LedStrip::animation_speed = animation_speed;
    LedStrip::power = pwr;
    LedStrip::color = base_color;
    allocate();
}