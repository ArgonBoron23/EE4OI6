################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/Modules/LED.cpp 

OBJS += \
./Core/Src/Modules/LED.o 

CPP_DEPS += \
./Core/Src/Modules/LED.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Modules/%.o Core/Src/Modules/%.su Core/Src/Modules/%.cyclo: ../Core/Src/Modules/%.cpp Core/Src/Modules/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m33 -std=gnu++14 -DUSE_NUCLEO_64 -DUSE_HAL_DRIVER -DSTM32H503xx -c -I../Core/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/BSP/STM32H5xx_Nucleo -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Modules

clean-Core-2f-Src-2f-Modules:
	-$(RM) ./Core/Src/Modules/LED.cyclo ./Core/Src/Modules/LED.d ./Core/Src/Modules/LED.o ./Core/Src/Modules/LED.su

.PHONY: clean-Core-2f-Src-2f-Modules

