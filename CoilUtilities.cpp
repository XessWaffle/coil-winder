#include "CoilUtilities.h"
#include "Constants.h"
#include "Router.h"
#include <Arduino.h>


float convert_steps_to_mm(uint16_t steps);
{
    return (float) steps / get_max_step_location() * DISTANCE;
}

uint16_t convert_mm_to_steps(float mm);
{
    return (uint16_t) (mm / DISTANCE * get_max_step_location());
}

float calculate_wire_diameter(coil_s* coil)
{
    return 0.005 * pow(92,(36 - coil->wire_gauge)/39.0) * 25.4;
}

uint16_t calculate_router_speed(coil_s* coil)
{
    float diameter = calculate_wire_diameter(coil); // 1 rotation : wire_diameter mm;
    uint16_t steps = convert_mm_to_steps(diameter); // STEPS_PER_REVOLUTION : steps

    return (float) steps/STEPS_PER_REVOLUTION * MAX_STEPS_PER_SECOND;
}