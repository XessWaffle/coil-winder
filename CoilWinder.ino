#include "Constants.h"

#include "Router.h"
#include "Winder.h"

#include "CoilUtilities.h"

coil_s *coil;

void setup() {
  router_initialize();
  winder_initialize();
  set_winder_speed(MAX_STEPS_PER_SECOND);

  coil = create_coil(200, 26, 20);

}

void loop() {

  static bool winder_prepping = false, winder_ready = false, coil_done = false;
  if(get_router_state() == ROUTER_DONE && !coil_done)
  {
    if(get_winder_state() == WINDER_DONE && winder_ready)
    {
      winder_prepping = false;
      winder_ready = false;
      coil_done = true;
    }

    if(winder_ready)
    {
      static bool towardsStop = true;
      set_router_speed(calculate_router_speed(coil));
      move_router_to(towardsStop ? coil->stop_step_location : coil->start_step_location);
      towardsStop = !towardsStop;
    }
    else if(winder_prepping)
    {
      rotate_winder_to(calculate_winder_step_rotations(coil));
      winder_ready = true;
    } 
    else if(is_router_calibrated())
    {
      coil->start_step_location = get_max_step_location();
      coil->stop_step_location = get_max_step_location() - convert_mm_to_steps(coil->spool_length);
      move_router_to(coil->start_step_location);
      winder_prepping = true;
    }
  }
  router_iterate();
  winder_iterate();
}