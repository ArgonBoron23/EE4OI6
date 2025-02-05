#include "TMC2209.h";

#include <stdio.h>

#ifdef __cplusplus
extern "C"
#endif
{
#include "stm32h5xx_hal.h"
#include "stm32h5xx_nucleo.h"
}

TMC2209::TMC2209()
{
}

void TMC2209::initDriver()
{
    currentPosSteps = 0;
    BSP_LED_Init(LED_GREEN);
}

void TMC2209::setTargetSteps(__int32_t targetSteps)
{
    targetPosSteps = targetSteps;
    BSP_LED_Toggle(LED_GREEN);
    HAL_Delay(500);
    
}
