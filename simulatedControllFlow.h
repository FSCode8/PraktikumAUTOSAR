#ifndef SIMULATED_CONTROLL_FLOW_H
#define SIMULATED_CONTROLL_FLOW_H

#include <stdint.h>

#include "autosar_simu.h"   

void set_Input_values(sint8 IndicatorLever, sint16 SteeringAngle, uint8 HazardLightsStatus, uint8 CarLightsStatus, sint16 Velocity);
Std_ReturnType scheduling_cycle_ZSE(void);
Std_ReturnType scheduling_cycle_LM_Module(void);

#endif