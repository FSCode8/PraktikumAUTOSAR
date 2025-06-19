#ifndef AUTOSAR_SIMU_H
#define AUTOSAR_SIMU_H

#include <stdint.h>
#include <stddef.h>

typedef enum {
    E_OK,
    E_NOT_OK
} Std_ReturnType;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;
typedef int8_t sint8;
typedef int16_t sint16;
typedef int32_t sint32;
typedef int64_t sint64;

typedef uint8_t Pwm_ChannelType;

// RTE Read functions
Std_ReturnType Rte_Read_IndicatorLever(int8_t* value);
Std_ReturnType Rte_Read_SteeringAngle(int16_t* value);
Std_ReturnType Rte_Read_HazardLightsStatus(uint8_t* value);
Std_ReturnType Rte_Read_CarLightsStatus(uint8_t* value);
Std_ReturnType Rte_Read_Velocity(int16_t* value);

Std_ReturnType Rte_Read_MSG_IndicatorLever(int8_t* value);
Std_ReturnType Rte_Read_MSG_HazardLightsStatus(uint8_t* value);
Std_ReturnType Rte_Read_MSG_SteeringAngle(int16_t* value);
Std_ReturnType Rte_Read_MSG_CarLightsStatus(uint8_t* value);
Std_ReturnType Rte_Read_MSG_Velocity(int16_t* value);

Std_ReturnType Rte_Read_MSG_IndicatorLights(uint8_t* value);

Std_ReturnType Rte_Read_MSG_CornerLightsStatus(uint8_t* value);

Std_ReturnType Rte_Read_MSG_LM(uint8_t* value);

// RTE Write functions
Std_ReturnType Rte_Write_MSG_IndicatorLever(int8_t value);
Std_ReturnType Rte_Write_MSG_SteeringAngle(int16_t value);
Std_ReturnType Rte_Write_MSG_HazardLightsStatus(uint8_t value);
Std_ReturnType Rte_Write_MSG_CarLightsStatus(uint8_t value);
Std_ReturnType Rte_Write_MSG_Velocity(int16_t value);

Std_ReturnType Rte_Write_MSG_CornerLightsStatus(uint8_t value);

Std_ReturnType Rte_Write_MSG_IndicatorLights(uint8_t value);

Std_ReturnType Rte_Write_MSG_LM(uint8_t value);

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

extern uint8_t MSG_CorneringLightStatus_value; // 0000 1000 -> Left Cornering Light on, 0000 0100 -> Right Cornering Light on, 0000 0000 -> Cornering Lights off // only front light modules have cornering lights

extern uint8_t MSG_LM_value; // 0000 0000 -> first four bits are for indicators, next four bits are for cornering lights 

#endif // AUTOSAR_H
