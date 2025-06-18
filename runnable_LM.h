#ifndef LM_H
#define LM_H

#include <stdint.h>

#include "autosar_simu.h"

// Runnable
Std_ReturnType LM_Controller_runnable(void);

extern uint8 debug_LEDs_statuses [7];
extern uint8 debug_indicator_status;
extern uint8 debug_cornering_light_status;

#endif