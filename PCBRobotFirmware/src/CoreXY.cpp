#include "CoreXY.h"
#include <Arduino.h>
#include "Constants.h"

// Constructor to initialize pins and variables
CoreXY::CoreXY(TMC2209Controller *stepperA, TMC2209Controller *stepperB)
    : m_stepperA(stepperA), m_stepperB(stepperB)
{
}

// Method to move to a specific position in millimeters and perform actions
void CoreXY::moveTo(float x_mm, float y_mm)
{
    Serial.print("Moving to (");
    Serial.print(x_mm);
    Serial.print(" mm, ");
    Serial.print(y_mm);
    Serial.println(" mm)");

    // Convert millimeters to steps
    int32_t x_steps = (int32_t)(y_mm * COREXY::STEPS_PER_MM);
    int32_t y_steps = (int32_t)(x_mm * COREXY::STEPS_PER_MM);

    m_stepperA->setTargetSteps(x_steps + y_steps); // 3000
    m_stepperB->setTargetSteps(x_steps - y_steps); // 1000

    int32_t deltaA = abs(m_stepperA->getCurrentSteps() - m_stepperA->getTargetSteps());
    int32_t deltaB = abs(m_stepperB->getCurrentSteps() - m_stepperB->getTargetSteps());

    Serial.println(deltaA);
    Serial.println(deltaB);


    if (deltaA > deltaB)
    {
        m_stepperA->setMaxSpeed((int)(COREXY::MAX_SPEED_RPM)); // faster one
        m_stepperB->setMaxSpeed((int)(COREXY::MAX_SPEED_RPM * ((1.0*deltaB) / (1.0*deltaA))));
    }
    else if (deltaA < deltaB)
    {
        m_stepperB->setMaxSpeed((int)(COREXY::MAX_SPEED_RPM)); // faster one
        m_stepperA->setMaxSpeed((int)(COREXY::MAX_SPEED_RPM * ((1.0*deltaA) / (1.0*deltaB))));
    }
    // equal
    else
    {
        m_stepperA->setMaxSpeed(static_cast<int>(COREXY::MAX_SPEED_RPM)); // faster one
        m_stepperB->setMaxSpeed(static_cast<int>(COREXY::MAX_SPEED_RPM)); // faster one
    }

    // Wait for 0.3 seconds
    delay(300);

    // Extend the iron (move Z up) and wait for 1 second
}

void CoreXY::periodic()
{

    m_stepperA->run();
    m_stepperB->run();
}

bool CoreXY::isAtTarget()
{
    m_stepperA->run();
    m_stepperB->run();
    return (m_stepperA->isAtTarget() && m_stepperB->isAtTarget());
}
