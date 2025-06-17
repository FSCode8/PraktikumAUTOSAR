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
 * In the main application, they are defined in simulatedControllFlow.c.
 *  
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

// Test helper
uint8_t compare_ExternInternVariables()
{
    // returns 1 if same, returns 0 if different
    if(IndicatorLever_value != MSG_IndicatorLever_value) return 0;
    if(SteeringAngle_value != MSG_SteeringAngle_value) return 0;
    if(HazardLightsStatus_value != MSG_HazardLightsStatus_value) return 0;
    if(CarLightsStatus_value != MSG_CarLightsStatus_value) return 0;
    if(Velocity_value != MSG_Velocity_value) return 0;

    return 1;
}

// --- Your Test Functions ---
// A test suite for the ZSE ECU
void test_ZSE_modules() 
{
    uint8_t correct_execution;

    test_suite_start("ZSE ECU module Tests");

    // Test 1 input controller
    set_Input_values(1, 1, 1, 1, 1); // messages from the 4 other ECUs
    
    correct_execution = Input_Controller_runnable();
    if (correct_execution==0) // everything correct
    {
        ASSERT_TRUE(compare_ExternInternVariables(), "Input Controller Test 1");
    }
    else // something wrong
    {
       ASSERT_TRUE(0, "Execution Input Controller Test 1"); 
    }

    // Test 2 input controller
    set_Input_values(1, 1, 1, 1, 1); // messages from the 4 other ECUs
    
    correct_execution = Input_Controller_runnable();
    if (correct_execution==0) // everything correct
    {
        ASSERT_TRUE(compare_ExternInternVariables(), "Input Controller Test 2");
    }
    else // something wrong
    {
       ASSERT_TRUE(0, "Execution Input Controller Test 2"); 
    }

    // Test 3 input controller
    set_Input_values(0, -2, 1, 1, -10); // messages from the 4 other ECUs
    
    correct_execution = Input_Controller_runnable();
    if (correct_execution==0) // everything correct
    {
        ASSERT_TRUE(compare_ExternInternVariables(), "Input Controller Test 3");
    }
    else // something wrong
    {
       ASSERT_TRUE(0, "Execution Input Controller Test 3"); 
    }
   
    /*
    set_Input_values(0, -70, 1, 1, 10);
    Input_Controller_runnable();

    // Test 1 Indicator Light Logic
    correct_execution = Indicator_Light_Logic_runnable();
    if (correct_execution==0) // everything correct
    {
        ASSERT_UINT8_EQ(0xF0, MSG_IndicatorLights_value, "Indicator Light Logic - Hazard Light with Cornering Light left");
    }
    else // something wrong
    {
       ASSERT_TRUE(0, "Execution Indicator Light Logic Test 1"); 
    }

    // Test 1 Cornering Light Logic
    correct_execution = Cornering_Light_Logic_runnable();
    if (correct_execution==0) // everything correct
    {
        ASSERT_UINT8_EQ(0x08, MSG_CorneringLightStatus_value, "Cornering Light Logic - Hazard Light with Cornering Light left");
    }
    else // something wrong
    {
       ASSERT_TRUE(0, "Execution Cornering Light Logic Test 1"); 
    }

    // Test 1 message Controller
    correct_execution = Message_Controller_runnable();
    if (correct_execution==0) // everything correct
    {
        ASSERT_UINT8_EQ(0xF8, MSG_LM_value, "Message Controller - Hazard Light with Cornering Light left");
    }
    else // something wrong
    {
       ASSERT_TRUE(0, "Execution Message Controller Test 1"); 
    }
    */
}

void test_ZSE_full() 
{
    test_suite_start("full ZSE ECU Tests");

    MSG_IndicatorLights_value = 0;
    MSG_CorneringLightStatus_value = 0;
    MSG_LM_value = 0;

    set_Input_values(0, 0, 1, 0, 0); // messages from the 4 other ECUs - Hazard Light

    uint8_t correct_execution_ZSE = 0;
    uint8_t correct_execution_LM = 0;
    for (size_t i = 0; i < 202; i++)
    {
        /*-------------------------------------------------------------------*/
        correct_execution_ZSE = scheduling_cycle_ZSE(); // Execution ZSE cycle
        if(correct_execution_ZSE) break;

        // Assert output
        if(i==0) ASSERT_UINT8_EQ(0xF0, MSG_LM_value, "ZSE Hazard Light 1"); 
        if(i==100) ASSERT_UINT8_EQ(0xF0, MSG_LM_value, "ZSE Hazard Light 2"); 
        if(i==101) ASSERT_UINT8_EQ(0xF8, MSG_LM_value, "ZSE Hazard Light with Cornering Light left"); 

        
        /*-------------------------------------------------------------------*/
        correct_execution_LM = scheduling_cycle_LM_Module(); // Execution LM cycle
        if(correct_execution_LM) break;

        // Assert changes output
        //if(i==101) ASSERT_EQ(1, debug_cornering_light_status, "LM Hazard Light with Cornering Light left"); 

        /*-------------------------------------------------------------------*/
        correct_execution_LM = scheduling_cycle_LM_Module(); // Execution LM cycle
        //if(correct_execution_LM) break;

        // Assert changes output
        //if(i==0) ASSERT_EQ(1, debug_indicator_status, "LM Hazard Light 1");
        //if(i==100) ASSERT_EQ(1, debug_indicator_status, "LM Hazard Light 2"); 
        

        /*---------------- Change Inputs ------------------------------------------*/ 
        if(i==100) set_Input_values(0, -70, 1, 1, 10);
        
    }

    ASSERT_TRUE(correct_execution_ZSE==0, "Correct Execution ZSE"); 
    ASSERT_TRUE(correct_execution_LM==0, "Correct Execution LM");
    
}

void test_LM()
{
    test_suite_start("LM ECU Tests");

}


// The main function for the test executable
int main() {
    printf("Running AUTOSAR Simulation Unit Tests\n");
    printf("======================================\n");

    // Run all the test suites
    test_ZSE_modules(); // Test the SWCs of the ZSE
    test_ZSE_full();
    test_LM();

    // Show summary and return a status code
    test_summary();
    return get_test_result();
}