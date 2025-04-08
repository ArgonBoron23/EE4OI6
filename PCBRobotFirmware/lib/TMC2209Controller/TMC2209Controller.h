#ifndef TMC2209Controller_H
#define TMC2209Controller_H

#include <TMC2209.h>

class TMC2209Controller
{

private:
    int32_t currentSteps, targetSteps;
    uint8_t directionPin, stepPin;
    uint16_t microsteps;
    uint16_t speedRPM;

    bool isInverted, currentDir;
    bool baseDirPinState, currentDirPinState;
    bool atTarget, steppedLastLoop;
    float fullStepAngleDegrees;

    uint32_t stepPeriodMicros;
    int32_t stepPeriodRemainder;
    unsigned long lastStepTimeInMicros;

     // Overhead time to process a coming move command
     const unsigned long moveProcessingInMicros = 0;

     // Time the step pin needs to be high to make a step
     const unsigned int stepHighTimeInMicros = 4;



public:
    TMC2209Controller(TMC2209 *TMC2209Ptr, float stepAngle,
                      uint8_t pinDir, uint8_t pinStep);

    TMC2209 *m_TMC2209;

    void init();

    int32_t getCurrentSteps();
    int32_t getTargetSteps();

    void setCurrentSteps(int32_t resetCurrentSteps);
    void setTargetSteps(int32_t targetSteps);

    void setMaxSpeed(unsigned int newSpeedRPM);

    void run();

    void setInverted(bool invert);

    bool getInverted();

    bool isAtTarget();

    bool steppedLastRun();

    float getStepAngle();


};

#endif