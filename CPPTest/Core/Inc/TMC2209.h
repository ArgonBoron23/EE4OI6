#ifndef INC_TMC2209_h
#define INC_TMC2209_h



/* Includes ------------------------------------------------------------------*/
#include "stm32h5xx_hal.h"
#include "stm32h5xx_nucleo.h"
#include <stdio.h>


class TMC2209{

protected:
    __int32_t currentPosSteps;
    __int32_t targetPosSteps;

    __uint16_t stepMode;


public:
    TMC2209();

    void initDriver();

    void setTargetSteps(__int32_t targetSteps);


};
#ifdef __cplusplus

#endif

#endif