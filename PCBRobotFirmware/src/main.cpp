#include "devices/TMC2209.h"

// This example will not work on Arduino boards without HardwareSerial ports,
// such as the Uno, Nano, and Mini.
//
// See this reference for more details:
// https://www.arduino.cc/reference/en/language/functions/communication/serial/

HardwareSerial & serial_stream = Serial1;

const long SERIAL_BAUD_RATE = 115200;
const int DELAY = 4000;
const int32_t VELOCITY = 200;
const uint32_t STEP_COUNT = 1000;
// current values may need to be reduced to prevent overheating depending on
// specific motor and power supply voltage
const uint8_t RUN_CURRENT_PERCENT = 50;
const uint8_t MICROSTEPS_PER_STEP_EXPONENT_MIN = 0;
const uint8_t MICROSTEPS_PER_STEP_EXPONENT_MAX = 8;
const uint8_t MICROSTEPS_PER_STEP_EXPONENT_INC = 1;
const uint16_t HALF_STEP_DURATION_MICROSECONDS = 400;
const uint16_t STOP_DURATION = 1000;
const uint8_t STEP_PIN = 14;
const uint8_t DIRECTION_PIN = 15;
const TMC2209::SerialAddress SERIAL_ADDRESS_1 = TMC2209::SERIAL_ADDRESS_1;


uint8_t microsteps_per_step_exponent = MICROSTEPS_PER_STEP_EXPONENT_MIN;


// Instantiate TMC2209
TMC2209 stepper_driver;


void setup()
{
  delay(2000);
  Serial.begin(SERIAL_BAUD_RATE);

  stepper_driver.setup(serial_stream, SERIAL_BAUD_RATE, SERIAL_ADDRESS_1);
  stepper_driver.setMicrostepsPerStepPowerOfTwo(0);
  stepper_driver.disableCoolStep();
  stepper_driver.disableStealthChop();
  stepper_driver.setRunCurrent(RUN_CURRENT_PERCENT);
  stepper_driver.setHoldCurrent(10);
  stepper_driver.enable();

  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIRECTION_PIN, OUTPUT);
  //stepper_driver.moveAtVelocity(VELOCITY);
}


void loop()
{
  // One step takes two iterations through the for loop
  for (uint32_t i=0; i<STEP_COUNT*2; ++i)
  {
    digitalWrite(STEP_PIN, !digitalRead(STEP_PIN));
    delayMicroseconds(HALF_STEP_DURATION_MICROSECONDS);
  }
  digitalWrite(DIRECTION_PIN, !digitalRead(DIRECTION_PIN));
  stepper_driver.disable();
  delay(STOP_DURATION);
  stepper_driver.enable();
}

