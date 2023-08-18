#include "Winder.h"
#include "Constants.h"
#include <Arduino.h>

winder_s glbl_winder;

void winder_initialize()
{
    glbl_winder.winder = new Stepper(STEPS_PER_REVOLUTION, 2, 4, 0, 5);
    glbl_winder.winder->setSpeed(MAX_SPEED);
    glbl_winder.winder_state = WINDER_DONE;
    glbl_winder.step_rotation = 0;
    glbl_winder.desired_rotation = 0;
    glbl_winder.speed = 1;
}

void winder_iterate()
{
    static uint32_t step_timer = 0;

    if(millis() - step_timer > 1000/glbl_winder.speed)
    {
        switch(glbl_winder.winder_state)
        {
            case WINDER_DONE:
                break;
            
            case WINDER_IN_MOTION:
                if(glbl_winder.desired_rotation == glbl_winder.step_rotation)
                {
                    glbl_winder.winder_state = WINDER_DONE;
                }

                uint8_t step_dir = glbl_winder.desired_rotation - glbl_winder.step_rotation > 0 ? 1 : -1;
                glbl_winder.winder->step(step_dir);
                glbl_winder.step_rotation += step_dir;

                break;
        }
        
        step_timer = millis();
    }
}

void rotate_winder_to(uint32_t step_rotation)
{
    glbl_winder.desired_rotation = step_rotation;
    glbl_winder.winder_state = WINDER_IN_MOTION;
}

void set_winder_speed(uint16_t speed)
{
    glbl_winder.speed = speed;
}

winder_state_e get_winder_state()
{
    return glbl_winder.winder_state;
}