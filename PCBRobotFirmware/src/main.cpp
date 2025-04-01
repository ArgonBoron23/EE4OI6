#include "devices/TMC2209.h"

// This example will not work on Arduino boards without HardwareSerial ports,
// such as the Uno, Nano, and Mini.
//
// See this reference for more details:
// https://www.arduino.cc/reference/en/language/functions/communication/serial/

HardwareSerial &serial_stream = Serial1;

const long SERIAL_BAUD_RATE = 115200;
const int DELAY = 4000;
const int32_t VELOCITY = 200;
const uint32_t STEP_COUNT = 500;
// current values may need to be reduced to prevent overheating depending on
// specific motor and power supply voltage
const uint8_t RUN_CURRENT_PERCENT = 100;
const uint8_t MICROSTEPS_PER_STEP_EXPONENT_MIN = 0;
const uint8_t MICROSTEPS_PER_STEP_EXPONENT_MAX = 8;
const uint8_t MICROSTEPS_PER_STEP_EXPONENT_INC = 1;
const uint16_t HALF_STEP_DURATION_MICROSECONDS = 2000;
const uint16_t STOP_DURATION = 200;
const uint8_t STEP_PIN_A = 14;
const uint8_t DIRECTION_PIN_A = 15;
const uint8_t STEP_PIN_B = 12;
const uint8_t DIRECTION_PIN_B = 13;
const uint8_t REPLY_DELAY = 80;
const TMC2209::SerialAddress SERIAL_ADDRESS_1 = TMC2209::SERIAL_ADDRESS_1;
const TMC2209::SerialAddress SERIAL_ADDRESS_2 = TMC2209::SERIAL_ADDRESS_2;

uint8_t microsteps_per_step_exponent = MICROSTEPS_PER_STEP_EXPONENT_MIN;

// Instantiate TMC2209
TMC2209 stepper_driver_A, stepper_driver_B;

void setup()
{
  delay(2000);
  Serial.begin(SERIAL_BAUD_RATE);

  stepper_driver_A.setup(serial_stream, SERIAL_BAUD_RATE, SERIAL_ADDRESS_1);

  if (stepper_driver_A.isCommunicating())
  {
    stepper_driver_A.clearDriveError();
    stepper_driver_A.disableVSense();
    stepper_driver_A.setReplyDelay(REPLY_DELAY);

    stepper_driver_A.setMicrostepsPerStepPowerOfTwo(0);
    stepper_driver_A.disableCoolStep();
    stepper_driver_A.disableStealthChop();
    stepper_driver_A.setRunCurrent(RUN_CURRENT_PERCENT);
    stepper_driver_A.setHoldCurrent(10);
    stepper_driver_A.enable();
    stepper_driver_A.setStallGuardThreshold(100);
    stepper_driver_A.getStallGuardResult();
  }

  stepper_driver_B.setup(serial_stream, SERIAL_BAUD_RATE, SERIAL_ADDRESS_2);

  if (stepper_driver_B.isCommunicating())
  {
    stepper_driver_B.clearDriveError();
    stepper_driver_B.disableVSense();

    stepper_driver_B.setReplyDelay(REPLY_DELAY);

    stepper_driver_B.setMicrostepsPerStepPowerOfTwo(0);
    stepper_driver_B.disableCoolStep();
    stepper_driver_B.disableStealthChop();
    stepper_driver_B.setRunCurrent(RUN_CURRENT_PERCENT);
    stepper_driver_B.setHoldCurrent(10);
    stepper_driver_B.enable();
  }

  pinMode(STEP_PIN_A, OUTPUT);
  pinMode(STEP_PIN_B, OUTPUT);

  pinMode(DIRECTION_PIN_A, OUTPUT);
  pinMode(DIRECTION_PIN_B, OUTPUT);

  digitalWrite(DIRECTION_PIN_A, HIGH);
  digitalWrite(DIRECTION_PIN_B, LOW);

  // stepper_driver_A.moveAtVelocity(VELOCITY);
}

void loop()
{
  // One step takes two iterations through the for loop
  for (uint32_t i = 0; i < STEP_COUNT * 2; ++i)
  {
    digitalWrite(STEP_PIN_A, !digitalRead(STEP_PIN_A));
    digitalWrite(STEP_PIN_B, !digitalRead(STEP_PIN_B));

    delayMicroseconds(HALF_STEP_DURATION_MICROSECONDS);
  }
  digitalWrite(DIRECTION_PIN_A, !digitalRead(DIRECTION_PIN_A));
  digitalWrite(DIRECTION_PIN_B, !digitalRead(DIRECTION_PIN_B));


  stepper_driver_A.disable();
  stepper_driver_B.disable();

  delay(STOP_DURATION);

  stepper_driver_A.enable();
  stepper_driver_B.enable();
}
