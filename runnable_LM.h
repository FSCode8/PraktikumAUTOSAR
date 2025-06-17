#ifndef LM_H
#define LM_H

#include <stdint.h>

#include "autosar_simu.h"

// Runnable
ReturnType LM_Controller_runnable(void);

extern uint8_t debug_LEDs_statuses [7];
extern uint8_t debug_indicator_status;
extern uint8_t debug_cornering_light_status;

#endif