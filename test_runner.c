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
    set_Input_values(0, 0, 0, 0, 0); // messages from the 4 other ECUs
    
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
   
    
    set_Input_values(-1, -20, 0, 1, 10);
    Input_Controller_runnable();

    // Test 1 Indicator Light Logic
    correct_execution = Indicator_Light_Logic_runnable();
    if (correct_execution==0) // everything correct
    {
        ASSERT_UINT8_EQ(0xA0, MSG_IndicatorLights_value, "Indicator Light Logic - Left Tipped");
    }
    else // something wrong
    {
       ASSERT_TRUE(0, "Execution Indicator Light Logic Test 1"); 
    }

    // Test 1 Cornering Light Logic
    correct_execution = Cornering_Light_Logic_runnable();
    if (correct_execution==0) // everything correct
    {
        ASSERT_UINT8_EQ(0x08, MSG_CorneringLightStatus_value, "Cornering Light Logic - Cornering Light left");
    }
    else // something wrong
    {
       ASSERT_TRUE(0, "Execution Cornering Light Logic Test 1"); 
    }

    // Test 1 message Controller
    correct_execution = Message_Controller_runnable();
    if (correct_execution==0) // everything correct
    {
        ASSERT_UINT8_EQ(0xA8, MSG_LM_value, "Message Controller - Hazard Light with Cornering Light left");
    }
    else // something wrong
    {
       ASSERT_TRUE(0, "Execution Message Controller Test 1"); 
    }


    flag_position = 1; // Set the flag position to front left
    flag_special_equipment = 0; // Set the flag for special equipment to basic

    // Test 1 LM Module
    correct_execution = LM_Controller_runnable();
    if (correct_execution==0) // everything correct
    {
        ASSERT_EQ(1, debug_cornering_light_status, "LM Module Test 1 - Cornering Light Status");
        ASSERT_EQ(1, debug_indicator_status, "LM Module Test 1 - Indicator Status");
    }
    else // something wrong
    {
       ASSERT_TRUE(0, "Execution LM Module Test 1"); 
    }

    // Test 2 LM Module
    correct_execution = LM_Controller_runnable();
    if (correct_execution==0) // everything correct
    {
        ASSERT_EQ(1, debug_cornering_light_status, "LM Module Test 2 - Cornering Light Status");
        ASSERT_EQ(1, debug_indicator_status, "LM Module Test 2 - Indicator Status");
    }
    else // something wrong
    {
       ASSERT_TRUE(0, "Execution LM Module Test 1"); 
    }
}

void test_ZSE_full() 
{
    test_suite_start("full ZSE ECU Tests");

    // Variables set in module tests 
    // (because of state dependecies they have to be the starting values)
    MSG_IndicatorLights_value = 0xA0;
    MSG_CorneringLightStatus_value = 0x08;
    MSG_LM_value = 0xA8;
    set_Input_values(-1, -20, 0, 1, 10); // messages from the 4 other ECUs - Hazard Light

    // Run the ECU cycles
    uint8_t correct_execution_ZSE = 0;
    uint8_t correct_execution_LM = 0;
    uint8_t next_assertion = 0; // helper variable for tests

    for (size_t i = 0; i < 10002; i++)
    {
        /*---------------- START CYCLE ----------------------------------------*/
        correct_execution_ZSE = scheduling_cycle_ZSE(); // Execution ZSE cycle
        if(correct_execution_ZSE) break;

        correct_execution_LM = scheduling_cycle_LM_Module(); // Execution LM cycle
        if(correct_execution_LM) break;

        correct_execution_LM = scheduling_cycle_LM_Module(); // Execution LM cycle
        if(correct_execution_LM) break;

        /*---------------- Change Inputs ------------------------------------------*/ 
        if(i==50) set_Input_values(0, 20, 0, 1, 10); // steering angle at <= 20°; indicator lever neutral
        if(i==60) set_Input_values(0, -21, 0, 1, 71); // Velocity greater than 70
        if(i==70) set_Input_values(0, -15, 0, 1, 10); // steering angle at <= -15; indicator lever neutral
        if(i==398) set_Input_values(-1, 0, 0, 1, 10); // transition to LS2
        if(i==499) set_Input_values(-2, 0, 0, 1, 10); // set to LS2
        if(i==502) set_Input_values(-1, 0, 0, 1, 10); // transition to neutral
        if(i==604) set_Input_values(0, 0, 0, 1, 10); // set to neutral
        if(i==800) set_Input_values(-1, 0, 0, 1, 10); // set to LS1
        if(i==801) set_Input_values(-1, 0, 1, 1, 10); // set Hazard Light on and left indicator lever tipped
        if(i==950) set_Input_values(-1, 0, 0, 1, 10); // set to LS1

        /* ---------------- TESTS -----------------------------------*/
        if(i==0) ASSERT_EQ(1, debug_cornering_light_status, "[#20] Cornering Light left with Blinker left - Steering left");
        if(i==51) ASSERT_EQ(1, debug_cornering_light_status, "[#21] Cornering Light left with Blinker left - Steering right <= 20°");
        if(i==61) ASSERT_EQ(0, debug_cornering_light_status, "[#22] Cornering off at Velocity > 70");
        if(i==71) ASSERT_EQ(0, debug_cornering_light_status, "[#23] Cornering off at steering angle at <= -15");
        
        if(i==1) if(MSG_LM_value!=0xA8) next_assertion = 1; // both front and rear left indicator lights on
        if(i==50) if(debug_indicator_status!=0) next_assertion = 2; 
        if(i==100) if(debug_indicator_status!=1) next_assertion = 3; // 2
        if(i==150) if(debug_indicator_status!=0) next_assertion = 4; 
        if(i==200) if(debug_indicator_status!=1) next_assertion = 5; // 3
        if(i==250) if(debug_indicator_status!=0) next_assertion = 6; 
        if(i==300) if(debug_indicator_status!=0) next_assertion = 7; // exacly 3 periods
        if(i==300) ASSERT_EQ(0, next_assertion, "#[01 #09 #16 #19] Indicator Light Left ");
        
        if(i==300) next_assertion = 0; // reset for next tests
        if(i==400) if(MSG_LM_value!=0xA8) next_assertion = 1; // both front and rear left indicator lights on
        if(i==400) if(debug_indicator_status!=1) next_assertion = 2; // 1
        if(i==450) if(debug_indicator_status!=0) next_assertion = 3;
        if(i==500) ASSERT_EQ(0, next_assertion, "[#03] Indicator Light Left");

        if(i==600) next_assertion = 0; // reset for next tests
        if(i==600) if(debug_indicator_status!=1) next_assertion = 1; // 1
        if(i==650) if(debug_indicator_status!=0) next_assertion = 2;
        if(i==800) if(debug_indicator_status!=0) next_assertion = 3; // 3
        if(i==800) ASSERT_EQ(0, next_assertion, "[#05 #15] Indicator Light Left LS2->LS1->Neutral");

        if(i==800) next_assertion = 0; // reset for next tests
        if(i==801) if(debug_indicator_status!=1) next_assertion = 1; // 1
        if(i==851) if(debug_indicator_status!=0) next_assertion = 2;
        if(i==901) if(MSG_LM_value!=0xF8) next_assertion = 3; // Hazard Light on
        if(i==901) if(debug_indicator_status!=1) next_assertion = 4; // 3
        if(i==1001) if(MSG_LM_value!=0xA8) next_assertion = 5; // Hazard Light on
        if(i==1001) ASSERT_EQ(0, next_assertion, "[#07 #08 #14] Hazard Light with Blinker left");
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