#ifndef COIL_UTILITIES_H
#define COIL_UTILITIES_H

#include <stdint.h>
#include "Coil.h"

float convert_steps_to_mm(uint16_t steps);
uint16_t convert_mm_to_steps(float mm);

float calculate_wire_diameter(coil_s* coil);

uint16_t calculate_router_speed(coil_s* coil);

uint32_t calculate_winder_step_rotations(coil_s* coil);

#endif