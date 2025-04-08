#include "TMC2209Controller.h"

TMC2209Controller::TMC2209Controller(TMC2209 *TMC2209Ptr, float stepAngle, uint8_t pinDir, uint8_t pinStep) : m_TMC2209(TMC2209Ptr)
{
    currentSteps = 0;
    targetSteps = 0;

    fullStepAngleDegrees = stepAngle;

    directionPin = pinDir;
    stepPin = pinStep;

    baseDirPinState = false;
    currentDirPinState = baseDirPinState;
    
}

void TMC2209Controller::init()
{
    targetSteps = 0;  // Reference
    currentSteps = 0; // Output
    isInverted = false;
    speedRPM = 100;
    lastStepTimeInMicros = micros();
    atTarget = false;
    steppedLastLoop = false;

    stepPeriodRemainder = 0;

    pinMode(directionPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    delay(4);

}

int32_t TMC2209Controller::getCurrentSteps()
{
    return (int32_t)(currentSteps / microsteps);
}

int32_t TMC2209Controller::getTargetSteps()
{
    return (int32_t)(targetSteps / microsteps);
}

void TMC2209Controller::setCurrentSteps(int32_t resetCurrentSteps)
{
    currentSteps = resetCurrentSteps;
}

void TMC2209Controller::setTargetSteps(int32_t stepsTarget)
{
    microsteps = m_TMC2209->getMicrostepsPerStep();

    targetSteps = (int32_t)(stepsTarget * microsteps);
    delayMicroseconds(200);

    stepPeriodRemainder = 0;

    stepPeriodMicros = ((fullStepAngleDegrees / speedRPM) / 360 / microsteps * 60000000);
    
}

void TMC2209Controller::setMaxSpeed(unsigned int newSpeedRPM)
{
    speedRPM = newSpeedRPM;

    // Update the target since this method calcs speed
    setTargetSteps(getTargetSteps());
    
}

void TMC2209Controller::run()
{
  // If current is not at target
  if (targetSteps != currentSteps)
  {

      atTarget = false;

      // Check if it is time to make another step
      if ((int)(micros() - lastStepTimeInMicros + moveProcessingInMicros) >= stepPeriodMicros) // 8 us
      {

          if (currentSteps > targetSteps) // going in reverse, 4us
          {
              // Check if the currrent direction is the same as the base. It should not be for going in reverse
              if (currentDirPinState == baseDirPinState)
              {
                  // Then invert it
                  currentDirPinState = !baseDirPinState;
                  digitalWrite(directionPin, currentDirPinState); // Temporarily flip direction, 4 us
                  delay(40);                         // settling
              }

              // Make a step
              digitalWrite(stepPin, HIGH);             // 4us
              delayMicroseconds(stepHighTimeInMicros); // variable us
              digitalWrite(stepPin, LOW);              // 4us
              delayMicroseconds(stepHighTimeInMicros); // variable us

              currentSteps--; // decrement current steps, 0us
          }
          else // going forward
          {

              // Check if the currrent direction is not the same as the base. It should be for going forward
              if (currentDirPinState != baseDirPinState)
              {
                  // Then invert it
                  currentDirPinState = baseDirPinState;
                  digitalWrite(directionPin, currentDirPinState); // Temporarily flip direction, 4 us
                  delayMicroseconds(120);                         // settling
              }

              // Make a step
              digitalWrite(stepPin, HIGH);
              delayMicroseconds(stepHighTimeInMicros);
              digitalWrite(stepPin, LOW);
              delayMicroseconds(stepHighTimeInMicros);

              currentSteps++; // Increment current steps, 0 us
          }

          // Note the time the step finished

          steppedLastLoop = true;

          lastStepTimeInMicros = micros(); // 8us
      }
      else
      {
          steppedLastLoop = false;
          stepPeriodRemainder = 0;
      }
  }
  else
  {
      atTarget = true;
  }
}

void TMC2209Controller::setInverted(bool invert){
    baseDirPinState = invert;
    isInverted = invert;
}

bool TMC2209Controller::getInverted()
{
    return isInverted;
}

bool TMC2209Controller::isAtTarget()
{
    return atTarget;
}

bool TMC2209Controller::steppedLastRun()
{
    return steppedLastLoop;
}

float TMC2209Controller::getStepAngle()
{
    return fullStepAngleDegrees;
}
