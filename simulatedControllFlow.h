#ifndef SIMULATED_CONTROLL_FLOW_H
#define SIMULATED_CONTROLL_FLOW_H

#include <stdint.h>

#include "autosar_simu.h"

// Extern variable declarations
extern int8_t IndicatorLever_value; // 0 = neutral, 1 = right-tip, 2 = right-set, -1 = left-tip, -2 = left-set
extern int16_t SteeringAngle_value; // clockwise positive, counterclockwise negative
extern uint8_t HazardLightsStatus_value; // 0 = off, 1 = on
extern uint8_t CarLightsStatus_value; // 0 = off, 1 = on
extern int16_t Velocity_value; // in km/h, positive = forward, negative = backward

extern int8_t MSG_IndicatorLever_value; // 0 = neutral, 1 = right-tip, 2 = right-set, -1 = left-tip, -2 = left-set
extern int16_t MSG_SteeringAngle_value; // clockwise positive, counterclockwise negative
extern uint8_t MSG_HazardLightsStatus_value; // 0 = off, 1 = on
extern uint8_t MSG_CarLightsStatus_value; // 0 = off, 1 = on
extern int16_t MSG_Velocity_value; // in km/h, positive = forward, negative = backward

extern uint8_t MSG_IndicatorLights_value; // 1010 0000 -> Left Indicators on, 0100 0000 -> Right Indicators on, 0000 0000 -> Indicators off, // 1111 0000 -> Hazard Lights on

extern uint8_t MSG_CorneringLightStatus_value; // 0000 1010 -> Left Conering Light on, 0000 0101 -> Right Cornering Light on, 0000 0000 -> Cornering Lights off

extern uint8_t MSG_LM_value; // 0000 0000 -> first four bits are for indicators, next four bits are for cornering lights    

#endif