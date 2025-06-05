#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "connection/PacketManager.hpp"
//#include "blink.pio.h" // Or ws2812.pio
/*
void blink_pin_forever(PIO pio, uint sm, uint offset, uint pin, uint freq) {
    blink_program_init(pio, sm, offset, pin);
    pio_sm_set_enabled(pio, sm, true);
    pio->txf[sm] = (125000000 / (2 * freq)) - 3;
}*/

int main() {
    stdio_init_all();
    sleep_ms(2000); // allow USB connection to establish
    printf("Hello world!\n");

    PacketManager packetManager;
    Packet packet;
    while (true) {
        if(packetManager.process(packet)){
            switch (packet.id)
            {
                case TEST_CONNECTION:
                    
                    break;
                
                default:
                    break;
            }
        }
        //sleep_ms(500);
    }
}
