#include "Router.h"
#include "Constants.h"
#include <Arduino.h>

router_s glbl_router;

void router_initialize()
{
    glbl_router.router = new Stepper(STEPS_PER_REVOLUTION, 13, 14, 12, 16);
    glbl_router.router->setSpeed(MAX_SPEED);
    glbl_router.router_state = ROUTER_CALIBRATING;
    glbl_router.step_location = 0;
    glbl_router.desired_location = 0;
    glbl_router.max_step_location = 0;
    glbl_router.speed = 600;

}

void router_iterate()
{

    static uint32_t step_timer = 0;

    if(millis() - step_timer > 1000/glbl_router.speed)
    {
        switch(glbl_router.router_state)
        {
            case ROUTER_CALIBRATING:
                static bool forward = false;
                static bool found_negative_edge = false;

                glbl_router.router->step(forward ? 1 : -1);

                if(found_negative_edge)
                {
                    glbl_router.max_step_location++;
                    glbl_router.step_location++;
                }

                if(read_limit_switch())
                {
                    if(found_negative_edge)
                    {
                        glbl_router.router_state = ROUTER_IN_MOTION;
                        glbl_router.desired_location = glbl_router.max_step_location / 2;
                    }
                    found_negative_edge = true;
                    forward = !forward;
                }

                break;
            
            case ROUTER_DONE:
                break;
            
            case ROUTER_IN_MOTION:
                if(glbl_router.desired_location == glbl_router.step_location)
                {
                    glbl_router.router_state = ROUTER_DONE;
                }

                int step_dir = glbl_router.desired_location > glbl_router.step_location ? 1 : -1;
                glbl_router.router->step(step_dir);
                glbl_router.step_location += step_dir;

                // An Edge has been hit, recalibrate
                /*if(read_limit_switch())
                {
                    glbl_router.router->step(-20 * step_dir);
                    recalibrate_router();
                }*/
                break;
        }
        
        step_timer = millis();
    }
}

bool read_limit_switch()
{
    static bool read_prevent = false;
    static uint32_t read_prevent_timer = 0;

    if(millis() - read_prevent_timer > LIM_READ_DELAY)
    {
        read_prevent = false;
    }

    bool limhit = analogRead(LIM) > 100;

    if(limhit && !read_prevent)
    {
        read_prevent = true;
        read_prevent_timer = millis();
        return true;
    }

    return false;
}

void move_router_to(uint16_t step_location)
{
    if(glbl_router.max_step_location != 0 && 
        step_location <= glbl_router.max_step_location)
    {
        glbl_router.desired_location = step_location;
        glbl_router.router_state = ROUTER_IN_MOTION;
    }
}

void set_router_speed(uint16_t speed)
{
    glbl_router.speed = speed;
}

void recalibrate_router()
{
    glbl_router.router_state = ROUTER_CALIBRATING;
}

router_state_e get_router_state()
{
    return glbl_router.router_state;
}
