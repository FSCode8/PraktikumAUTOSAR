#include "my_test.h"      // Your testing framework
#include "autosar_simu.h" // Includes RTE function prototypes and externs

// Include headers for the runnables you want to test
#include "simulatedControllFlow.h"
#include "runnable_Input_Controller.h"
#include "runnable_Indicator_Logic.h"
#include "runnable_Cornering_Light_Logic.h"
#include "runnable_Message_Controller.h"
#include "runnable_LM.h"

/*
 * =================================================================
 * MOCK GLOBAL STATE FOR TESTING
 *
 * These variables are defined here to satisfy the linker for the
 * test build. In the main application, they are defined in
*  simulatedControllFlow.c.
 * =================================================================
 */
// Variables inside the ZSE ECU
int8_t MSG_IndicatorLever_value = 0;
int16_t MSG_SteeringAngle_value = 0;
uint8_t MSG_HazardLightsStatus_value = 0;
uint8_t MSG_CarLightsStatus_value = 0;
int16_t MSG_Velocity_value = 0;

uint8_t MSG_IndicatorLights_value = 0;

uint8_t MSG_CorneringLightStatus_value = 0;

uint8_t MSG_LM_value = 0;

// Variables from extern
int8_t IndicatorLever_value = 0;
int16_t SteeringAngle_value = 0;
uint8_t HazardLightsStatus_value = 0;
uint8_t CarLightsStatus_value = 0;
int16_t Velocity_value = 0;


// --- Your Test Functions ---
// A test suite for the ZSE ECU
void test_ZSE() {
    test_suite_start("ZSE ECU Tests");

    // Assuming calculate_light_level is a function in runnable_LM.c
    ASSERT_EQ(0, set_Input_values(0, 0, 0, 0, 0), "set Input values");
    ASSERT_EQ(0, scheduling_cycle_ZSE(), "Run scheduling cycle for ZSE");
    ASSERT_EQ(0, MSG_LM_value, "LM value should be 0");
}


// The main function for the test executable
int main() {
    printf("Running AUTOSAR Simulation Unit Tests\n");
    printf("======================================\n");

    // Run all your test suites
    test_ZSE(); // Test the Light Module (LM)
    // ... call other test suites

    // Show summary and return a status code
    test_summary();
    return get_test_result();
}