#include <TMC2209.h>
#include <TMC2209Controller.h>
#include "Constants.h"
#include "CoreXY.h"

// This example will not work on Arduino boards without HardwareSerial ports,
// such as the Uno, Nano, and Mini.
//
// See this reference for more details:
// https://www.arduino.cc/reference/en/language/functions/communication/serial/

HardwareSerial &serial_stream = Serial1;

const long SERIAL_BAUD_RATE = 115200;
const int DELAY = 4000;
const int32_t VELOCITY = 200;
const uint32_t STEP_COUNT = 200;
// current values may need to be reduced to prevent overheating depending on
// specific motor and power supply voltage
const uint8_t RUN_CURRENT_PERCENT = 50;
const uint8_t MICROSTEPS_PER_STEP_EXPONENT_MIN = 0;
const uint8_t MICROSTEPS_PER_STEP_EXPONENT_MAX = 8;
const uint8_t MICROSTEPS_PER_STEP_EXPONENT_INC = 1;
const uint16_t HALF_STEP_DURATION_MICROSECONDS = 500;
const uint16_t STOP_DURATION = 200;

const uint8_t REPLY_DELAY = 40;

uint8_t microsteps_per_step_exponent = MICROSTEPS_PER_STEP_EXPONENT_MIN;

// Instantiate TMC2209
TMC2209 stepperDriverA, stepperDriverB, stepperDriverZ, stepperDriverE;

TMC2209Controller
    stepperA(&stepperDriverA, 1.8, MOTOR_A::PIN_DIR, MOTOR_A::PIN_STEP),
    stepperB(&stepperDriverB, 1.8, MOTOR_B::PIN_DIR, MOTOR_B::PIN_STEP),
    stepperE(&stepperDriverE, 1.8, MOTOR_E::PIN_DIR, MOTOR_E::PIN_STEP),
    stepperZ(&stepperDriverZ, 1.8, MOTOR_Z::PIN_DIR, MOTOR_Z::PIN_STEP);

// CoreXY motion system
CoreXY m_CoreXY(&stepperA, &stepperB);


void setup()
{

  delay(2000);
  Serial.begin(SERIAL_BAUD_RATE);

  stepperA.m_TMC2209->setup(serial_stream, SERIAL_BAUD_RATE, MOTOR_A::UART_ADDR);
  delay(10);
  if (stepperA.m_TMC2209->isCommunicating())
  {
    delay(10);
    stepperA.m_TMC2209->clearDriveError();
    delay(10);
    stepperA.m_TMC2209->disableVSense();
    delay(10);
    stepperA.m_TMC2209->setReplyDelay(REPLY_DELAY);
    delay(10);
    stepperA.m_TMC2209->setMicrostepsPerStepPowerOfTwo(0);
    delay(10);
    stepperA.m_TMC2209->disableCoolStep();
    delay(10);
    stepperA.m_TMC2209->disableStealthChop();
    delay(10);
    stepperA.m_TMC2209->setRunCurrent(RUN_CURRENT_PERCENT);
    delay(10);
    stepperA.m_TMC2209->setHoldCurrent(10);
    delay(10);
    stepperA.m_TMC2209->enable();
    delay(10);
  }

  stepperB.m_TMC2209->setup(serial_stream, SERIAL_BAUD_RATE, MOTOR_B::UART_ADDR);
  delay(10);
  if (stepperB.m_TMC2209->isCommunicating())
  {
    stepperB.m_TMC2209->clearDriveError();
    delay(10);
    stepperB.m_TMC2209->disableVSense();
    delay(10);

    stepperB.m_TMC2209->setReplyDelay(REPLY_DELAY);
    delay(10);

    stepperB.m_TMC2209->setMicrostepsPerStepPowerOfTwo(0);
    delay(10);

    stepperB.m_TMC2209->disableCoolStep();
    delay(10);

    stepperB.m_TMC2209->disableStealthChop();
    delay(10);

    stepperB.m_TMC2209->setRunCurrent(RUN_CURRENT_PERCENT);
    delay(10);

    stepperB.m_TMC2209->setHoldCurrent(10);
    delay(10);

    stepperB.m_TMC2209->enable();
    delay(10);
  }

  stepperE.m_TMC2209->setup(serial_stream, SERIAL_BAUD_RATE, MOTOR_E::UART_ADDR);
  delay(10);
  if (stepperE.m_TMC2209->isCommunicating())
  {
    delay(10);
    stepperE.m_TMC2209->clearDriveError();
    delay(10);
    stepperE.m_TMC2209->disableVSense();
    delay(10);
    stepperE.m_TMC2209->setReplyDelay(REPLY_DELAY);
    delay(10);
    stepperE.m_TMC2209->setMicrostepsPerStepPowerOfTwo(0);
    delay(10);
    stepperE.m_TMC2209->disableCoolStep();
    delay(10);
    stepperE.m_TMC2209->disableStealthChop();
    delay(10);
    stepperE.m_TMC2209->setRunCurrent(RUN_CURRENT_PERCENT);
    delay(10);
    stepperE.m_TMC2209->setHoldCurrent(10);
    delay(10);
    stepperE.m_TMC2209->enable();
    delay(10);
  }

  stepperZ.m_TMC2209->setup(serial_stream, SERIAL_BAUD_RATE, MOTOR_Z::UART_ADDR);
  delay(10);
  if (stepperZ.m_TMC2209->isCommunicating())
  {
    delay(10);
    stepperZ.m_TMC2209->clearDriveError();
    delay(10);
    stepperZ.m_TMC2209->disableVSense();
    delay(10);
    stepperZ.m_TMC2209->setReplyDelay(REPLY_DELAY);
    delay(10);
    stepperZ.m_TMC2209->setMicrostepsPerStepPowerOfTwo(0);
    delay(10);
    stepperZ.m_TMC2209->disableCoolStep();
    delay(10);
    stepperZ.m_TMC2209->disableStealthChop();
    delay(10);
    stepperZ.m_TMC2209->setRunCurrent(RUN_CURRENT_PERCENT);
    delay(10);
    stepperZ.m_TMC2209->setHoldCurrent(10);
    delay(10);
    stepperZ.m_TMC2209->enableAutomaticGradientAdaptation();
    delay(10);
    stepperZ.m_TMC2209->enable();
    delay(10);
  }

  stepperA.init();
  stepperB.init();
  stepperZ.init();
  stepperE.init();

  stepperA.setInverted(MOTOR_A::IS_INVERTED);
  stepperB.setInverted(MOTOR_B::IS_INVERTED);
  stepperE.setInverted(MOTOR_E::IS_INVERTED);
  stepperZ.setInverted(MOTOR_Z::IS_INVERTED);

  stepperA.setMaxSpeed(150);
  stepperB.setMaxSpeed(150);
  stepperZ.setMaxSpeed(150);
  stepperE.setMaxSpeed(100);
}

void loop()
{

  m_CoreXY.moveTo(0, 0);

  do
  {
    m_CoreXY.periodic();

  } while (!m_CoreXY.isAtTarget());

  delay(1000);



  m_CoreXY.moveTo(67, 9);

  do
  {
    m_CoreXY.periodic();

  
  } while (!m_CoreXY.isAtTarget());
  delay(1000);


  stepperZ.setTargetSteps(250);

  do
  {
    stepperZ.run();

  
  } while (!stepperZ.isAtTarget());

  delay(1000);

  // Solder
  m_CoreXY.moveTo(67, 9-1);

  do
  {
    m_CoreXY.periodic();

  
  } while (!m_CoreXY.isAtTarget());



  // Dispense solder


  stepperE.setTargetSteps(610);

  do
  {
    stepperE.run();

  
  } while (!stepperE.isAtTarget());

  delay(2000);


  // Dispense solder
  stepperE.setTargetSteps(200);

  do
  {
    stepperE.run();

  
  } while (!stepperE.isAtTarget());

  delay(500);



  // Retract iron

  delay(1000);

  stepperZ.setTargetSteps(0);

  do
  {
    stepperZ.run();

  
  } while (!stepperZ.isAtTarget());

  


  // NEXT PIN
  m_CoreXY.moveTo(64.5, 9);

  do
  {
    m_CoreXY.periodic();

  
  } while (!m_CoreXY.isAtTarget());
  delay(1000);


  stepperZ.setTargetSteps(250);

  do
  {
    stepperZ.run();

  
  } while (!stepperZ.isAtTarget());

  delay(1000);

  // Solder
  m_CoreXY.moveTo(64.5, 9-1);

  do
  {
    m_CoreXY.periodic();

  
  } while (!m_CoreXY.isAtTarget());



  // Dispense solder


  stepperE.setTargetSteps(610);

  do
  {
    stepperE.run();

  
  } while (!stepperE.isAtTarget());

  delay(2000);


  // Dispense solder
  stepperE.setTargetSteps(200);

  do
  {
    stepperE.run();

  
  } while (!stepperE.isAtTarget());

  delay(500);



  // Retract iron

  delay(1000);

  stepperZ.setTargetSteps(0);

  do
  {
    stepperZ.run();

  
  } while (!stepperZ.isAtTarget());

  /// END
 

  delay(500);

  m_CoreXY.moveTo(0, 0);

  do
  {
    m_CoreXY.periodic();

  } while (!m_CoreXY.isAtTarget());

  delay(1000);


  

  while(1){

  }

}
