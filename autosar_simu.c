#include "autosar_simu.h"

// Read functions
ReturnType Rte_Read_IndicatorLever(int8_t* value)
{
    if (value == NULL) return 1;  // error code
    *value = IndicatorLever_value;
    return 0;  // success
}
ReturnType Rte_Read_SteeringAngle(int16_t* value)
{
    if (value == NULL) return 1;  // error code
    *value = SteeringAngle_value;
    return 0;  // success
}
ReturnType Rte_Read_HazardLightsStatus(uint8_t* value)
{
    if (value == NULL) return 1;  // error code
    *value = HazardLightsStatus_value;
    return 0;  // success
}
ReturnType Rte_Read_CarLightsStatus(uint8_t* value)
{
    if (value == NULL) return 1;  // error code
    *value = CarLightsStatus_value;
    return 0;  // success
}
ReturnType Rte_Read_Velocity(int16_t* value)
{
    if (value == NULL) return 1;  // error code
    *value = Velocity_value;
    return 0;  // success
}

// ----- // Read functions for MSG_ variables
ReturnType Rte_Read_MSG_HazardLightsStatus(uint8_t* value)
{
    // Simulate reading the value from RTE
    if (value == NULL) return 1;  // error code
    *value = MSG_HazardLightsStatus_value; // Assume MSG_HazardLightsStatus_value is defined globally
    return OK;
}
ReturnType Rte_Read_MSG_IndicatorLever(int8_t* value)
{
    // Simulate reading the value from RTE
    if (value == NULL) return 1;  // error code
    *value = MSG_IndicatorLever_value; // Assume MSG_IndicatorLever_value is defined globally
    return OK;
}
ReturnType Rte_Read_MSG_Velocity(int16_t* value)    
{
    // Simulate reading the value from RTE
    if (value == NULL) return 1;  // error code
    *value = MSG_Velocity_value; // Assume MSG_Velocity_value is defined globally
    return OK;
}
ReturnType Rte_Read_MSG_SteeringAngle(int16_t* value)
{
    // Simulate reading the value from RTE
    if (value == NULL) return 1;  // error code
    *value = MSG_SteeringAngle_value; // Assume MSG_SteeringAngle_value is defined globally
    return OK;
}
ReturnType Rte_Read_MSG_CarLightsStatus(uint8_t* value)
{
    // Simulate reading the value from RTE
    if (value == NULL) return 1;  // error code
    *value = MSG_CarLightsStatus_value; // Assume MSG_CarLightsStatus_value is defined globally
    return OK;
}

ReturnType Rte_Read_MSG_IndicatorLights(uint8_t* value)
{
    // Simulate reading the value from RTE
    if (value == NULL) return 1;  // error code
    *value = MSG_IndicatorLights_value; // Assume MSG_IndicatorLights_value is defined globally
    return OK;
}

ReturnType Rte_Read_MSG_CornerLightsStatus(uint8_t* value)
{
    // Simulate reading the value from RTE
    if (value == NULL) return 1;  // error code
    *value = MSG_CorneringLightStatus_value; // Assume MSG_CorneringLightStatus_value is defined globally
    return OK;
}

ReturnType Rte_Read_MSG_LM(uint8_t* value)
{
    // Simulate reading the value from RTE
    if (value == NULL) return 1;  // error code
    *value = MSG_LM_value; // Assume MSG_LM_value is defined globally
    return OK;
}

// ----------------------------------------------------------------------------------------------- //
// Write functions

ReturnType Rte_Write_MSG_IndicatorLever(int8_t value)
{
    MSG_IndicatorLever_value = value;
    return 0;  // success
}
ReturnType Rte_Write_MSG_HazardLightsStatus(uint8_t value)
{
    MSG_HazardLightsStatus_value = value;
    return 0;  // success
}
ReturnType Rte_Write_MSG_Velocity(int16_t value)
{
    MSG_Velocity_value = value;
    return 0;  // success
}
ReturnType Rte_Write_MSG_SteeringAngle(int16_t value)
{
    MSG_SteeringAngle_value = value;
    return 0;  // success
}
ReturnType Rte_Write_MSG_CarLightsStatus(uint8_t value)
{
    MSG_CarLightsStatus_value = value;
    return 0;  // success
}

ReturnType Rte_Write_MSG_IndicatorLights(uint8_t value)
{
    MSG_IndicatorLights_value = value; // Assume MSG_IndicatorLights_value is defined globally
    return OK;
}

ReturnType Rte_Write_MSG_CornerLightsStatus(uint8_t value)
{
    // Simulate writing the value to RTE
    MSG_CorneringLightStatus_value = value; // Assume MSG_CorneringLightStatus_value is defined globally
    return OK;
}

ReturnType Rte_Write_MSG_LM(uint8_t value)
{
    // Simulate writing the value to RTE
    MSG_LM_value = value; // Assume MSG_LM_value is defined globally
    return OK;
}