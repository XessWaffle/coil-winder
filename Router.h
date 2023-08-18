#ifndef ROUTER_H
#define ROUTER_H

#define LIM A0

#include <stdint.h>
#include <Stepper.h>


typedef enum RouterState{  
    ROUTER_CALIBRATING, // Used purely during the calibration stage 
    ROUTER_DONE, // Used when router has made it to desired location
    ROUTER_IN_MOTION // Used when router has not reached desired location
} router_state_e;

typedef struct Router
{
    Stepper *router;
    router_state_e router_state;

    uint16_t step_location, desired_location, max_step_location;
    uint16_t speed; //Steps per second
} router_s;

void router_initialize();
void router_iterate();

bool read_limit_switch();

void move_router_to(uint16_t step_location);
void set_router_speed(uint16_t speed);
void recalibrate_router();

router_state_e get_router_state();

uint16_t get_max_step_location();

bool is_router_calibrated();


#endif