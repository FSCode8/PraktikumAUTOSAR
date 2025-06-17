#ifndef SIMULATED_CONTROLL_FLOW_H
#define SIMULATED_CONTROLL_FLOW_H

#include <stdint.h>

#include "autosar_simu.h"   

void set_Input_values(int8_t IndicatorLever, int16_t SteeringAngle, uint8_t HazardLightsStatus, uint8_t CarLightsStatus, int16_t Velocity);
ReturnType scheduling_cycle_ZSE(void);
ReturnType scheduling_cycle_LM_Module(void);

#endif