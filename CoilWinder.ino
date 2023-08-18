#include "Router.h"
#include "Winder.h"

void setup() {
  router_initialize();
  winder_initialize();
  rotate_winder_to(5000);
  set_winder_speed(800);
}

void loop() {
  router_iterate();
  winder_iterate();
}