#ifndef COREXY_H
#define COREXY_H

#include <Arduino.h>
#include "Constants.h"
#include <TMC2209Controller.h>

class CoreXY
{
public:
    CoreXY(TMC2209Controller *stepperA, TMC2209Controller *stepperB);

    void moveTo(float x_mm, float y_mm);

    void periodic();

    bool isAtTarget();

private:
    int32_t currentX; // Current X position in steps
    int32_t currentY; // Current Y position in steps

    // CoreXY control steppers
    TMC2209Controller *m_stepperA;
    TMC2209Controller *m_stepperB;
};

#endif // CORE_XY_CONTROL_H