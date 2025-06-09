#include "LedStripManager.hpp"

uint8_t LedStripManager::get_next_id(){
    for (uint8_t i = 0; i < MAX_LED_AMOUNT; i++)
    {
        if(id_list[i] == false){
            id_list[i] = true;
            return i;
        }
    }
    return -1;
}


void LedStripManager::free_id(uint8_t id){
    id_list[id] = false;
}

LedStripManager::LedStripManager() {
    for (uint8_t i = 0; i < MAX_LED_AMOUNT; i++)
    {
            id_list[i] = false;
    }
}