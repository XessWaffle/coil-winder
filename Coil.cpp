#include "Coil.h"
#include <Arduino.h>

coil_s* create_coil(uint16_t loops, uint8_t wire_gauge, float spool_length)
{
    coil_s* coil = NULL;

    if((coil = (coil_s*) malloc(sizeof(coil_s))) != NULL)
    {
        coil->loops = loops;
        coil->wire_gauge = wire_gauge;
        coil->spool_length = spool_length;
    }

    return coil;
}