#ifndef Constants_h
#define Constants_h

#include <Arduino.h>
#include "devices/TMC2209.h";

// Driver in slot A1
// Schematic - motor 3
namespace MOTOR_A
{
    constexpr uint8_t PIN_STEP = 3,
                      PIN_DIR = 2;

    constexpr TMC2209::SerialAddress UART_ADDR = TMC2209::SERIAL_ADDRESS_2;

}

// Driver in slot A4
// Schematic - motor 2
namespace MOTOR_B
{
    constexpr uint8_t PIN_STEP = 9,
                      PIN_DIR = 8;

    constexpr TMC2209::SerialAddress UART_ADDR = TMC2209::SERIAL_ADDRESS_0;

}

// Driver in slot A3
// Schematic - motor 1
namespace MOTOR_Z
{
    constexpr uint8_t PIN_STEP = 7,
                      PIN_DIR = 6;

    constexpr TMC2209::SerialAddress UART_ADDR = TMC2209::SERIAL_ADDRESS_3;

}

// Driver in slot A2
// Schematic - motor 4
namespace MOTOR_E
{
    constexpr uint8_t PIN_STEP = 5,
                      PIN_DIR = 4;

    constexpr TMC2209::SerialAddress UART_ADDR = TMC2209::SERIAL_ADDRESS_1;
}

namespace COREXY
{
    uint16_t MAX_X_MM = 459,
             MAX_Y_MM = 296;
    float STEPS_PER_MM = 5.0;
}

namespace Z_AXIS
{
    float STEPS_PER_MM = 37.5;
    uint8_t PIN_LIMIT_SWITCH = 22;
}

namespace SOLDER_SPOOL_GUN{
    float STEPS_PER_MM = 45.0; // 7 mm PD roller on 50:10 gear ratio
    uint8_t PIN_BEAM_BREAK = 21;
    
}

#endif