#ifndef COIL_H
#define COIL_H

#include <stdint.h>

typedef struct Coil
{
    uint16_t loops;
    uint8_t wire_gauge;
    float spool_length;
} coil_s;


coil_s* create_coil(uint16_t loops, uint8_t wire_gauge, float spool_length);


#endif