################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/argon/STM32Cube/Repository/STM32Cube_FW_H5_V1.3.0/Drivers/BSP/STM32H5xx_Nucleo/stm32h5xx_nucleo.c 

C_DEPS += \
./Drivers/BSP/STM32H5xx_Nucleo/stm32h5xx_nucleo.d 

OBJS += \
./Drivers/BSP/STM32H5xx_Nucleo/stm32h5xx_nucleo.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32H5xx_Nucleo/stm32h5xx_nucleo.o: C:/Users/argon/STM32Cube/Repository/STM32Cube_FW_H5_V1.3.0/Drivers/BSP/STM32H5xx_Nucleo/stm32h5xx_nucleo.c Drivers/BSP/STM32H5xx_Nucleo/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_NUCLEO_64 -DUSE_HAL_DRIVER -DSTM32H503xx -c -I../Core/Inc -IC:/Users/argon/STM32Cube/Repository/STM32Cube_FW_H5_V1.3.0/Drivers/STM32H5xx_HAL_Driver/Inc -IC:/Users/argon/STM32Cube/Repository/STM32Cube_FW_H5_V1.3.0/Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -IC:/Users/argon/STM32Cube/Repository/STM32Cube_FW_H5_V1.3.0/Drivers/BSP/STM32H5xx_Nucleo -IC:/Users/argon/STM32Cube/Repository/STM32Cube_FW_H5_V1.3.0/Drivers/CMSIS/Device/ST/STM32H5xx/Include -IC:/Users/argon/STM32Cube/Repository/STM32Cube_FW_H5_V1.3.0/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM32H5xx_Nucleo

clean-Drivers-2f-BSP-2f-STM32H5xx_Nucleo:
	-$(RM) ./Drivers/BSP/STM32H5xx_Nucleo/stm32h5xx_nucleo.cyclo ./Drivers/BSP/STM32H5xx_Nucleo/stm32h5xx_nucleo.d ./Drivers/BSP/STM32H5xx_Nucleo/stm32h5xx_nucleo.o ./Drivers/BSP/STM32H5xx_Nucleo/stm32h5xx_nucleo.su

.PHONY: clean-Drivers-2f-BSP-2f-STM32H5xx_Nucleo

