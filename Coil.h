#ifndef COIL_H
#define COIL_H

#include <stdint.h>

typedef struct Coil
{
    uint16_t loops;
    uint8_t wire_gauge;
    float spool_length;

    uint16_t start_step_location, stop_step_location;
} coil_s;


coil_s* create_coil(uint16_t loops, uint8_t wire_gauge, float spool_length);


#endif