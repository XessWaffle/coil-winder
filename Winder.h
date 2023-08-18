#ifndef WINDER_H
#define WINDER_H

#include <stdint.h>
#include <Stepper.h>


typedef enum WinderState{  
    WINDER_DONE, // Used when winder has made it to desired location
    WINDER_IN_MOTION // Used when winder has not reached desired location
} winder_state_e;

typedef struct Winder
{
    Stepper *winder;
    winder_state_e winder_state;

    uint32_t step_rotation, desired_rotation;
    uint16_t speed;
} winder_s;

void winder_initialize();
void winder_iterate();

void rotate_winder_to(uint32_t step_rotation);
void set_winder_speed(uint16_t speed);

winder_state_e get_winder_state();


#endif