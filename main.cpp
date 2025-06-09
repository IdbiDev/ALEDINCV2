#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "connection/PacketManager.hpp"
#include "led/LedStripManager.hpp"
#include "SettingsManager.hpp"


LedStrip ledStrips[MAX_LED_AMOUNT];
int main() {
    stdio_init_all();
    sleep_ms(2000); // allow USB connection to establish
    //printf("Hello world!\n");

    PacketManager packetManager;
    SettingsManager settingsManager;
    Packet packet;
    settingsManager.load(ledStrips,MAX_STRIPS);
    while (true) {
        if(packetManager.process(packet)) {
            if(packet.id == TEST_CONNECTION) {
                if(packet.data.read_uint16() != 0xABCD) {
                    packetManager.complete_error(DRIVER_ERROR_INVALID_TEST_MAGIC);
                    continue;
                }
                packetManager.complete();
                continue;
            }
            //If packed processed then we return READY
            packetManager.complete();
        }
        //sleep_ms(500);
    }
}
