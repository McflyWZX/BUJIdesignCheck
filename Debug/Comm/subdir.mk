################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Comm/TestUartComm.c 

OBJS += \
./Comm/TestUartComm.o 

C_DEPS += \
./Comm/TestUartComm.d 


# Each subdirectory must supply rules for building sources it contributes
Comm/TestUartComm.o: ../Comm/TestUartComm.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32H750xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Drivers/CMSIS/Include -I"C:/Users/Abner/Documents/Code/BUJIdesignCheck/ToolsCore" -I"C:/Users/Abner/Documents/Code/BUJIdesignCheck/Hardware" -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/STM32H7xx_HAL_Driver/Inc -I"C:/Users/Abner/Documents/Code/BUJIdesignCheck/Ctrl" -I"C:/Users/Abner/Documents/Code/BUJIdesignCheck/Comm" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Comm/TestUartComm.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

