#ifndef AUTOSAR_SIMU_H
#define AUTOSAR_SIMU_H

#include <stdint.h>
#include <stddef.h>

typedef enum {
    OK,
    ERROR
} ReturnType;

#include "simulatedControllFlow.h"

// RTE Read functions
ReturnType Rte_Read_IndicatorLever(int8_t* value);
ReturnType Rte_Read_SteeringAngle(int16_t* value);
ReturnType Rte_Read_HazardLightsStatus(uint8_t* value);
ReturnType Rte_Read_CarLightsStatus(uint8_t* value);
ReturnType Rte_Read_Velocity(int16_t* value);

ReturnType Rte_Read_MSG_IndicatorLever(int8_t* value);
ReturnType Rte_Read_MSG_HazardLightsStatus(uint8_t* value);
ReturnType Rte_Read_MSG_SteeringAngle(int16_t* value);
ReturnType Rte_Read_MSG_CarLightsStatus(uint8_t* value);
ReturnType Rte_Read_MSG_Velocity(int16_t* value);

ReturnType Rte_Read_MSG_IndicatorLights(uint8_t* value);

ReturnType Rte_Read_MSG_CornerLightsStatus(uint8_t* value);

ReturnType Rte_Read_MSG_LM(uint8_t* value);

// RTE Write functions
ReturnType Rte_Write_MSG_IndicatorLever(int8_t value);
ReturnType Rte_Write_MSG_SteeringAngle(int16_t value);
ReturnType Rte_Write_MSG_HazardLightsStatus(uint8_t value);
ReturnType Rte_Write_MSG_CarLightsStatus(uint8_t value);
ReturnType Rte_Write_MSG_Velocity(int16_t value);

ReturnType Rte_Write_MSG_CornerLightsStatus(uint8_t value);

ReturnType Rte_Write_MSG_IndicatorLights(uint8_t value);

ReturnType Rte_Write_MSG_LM(uint8_t value);

#endif // AUTOSAR_H


