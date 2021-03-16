################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Hardware/GPS.c \
../Hardware/JY61P.c \
../Hardware/OV2640.c 

OBJS += \
./Hardware/GPS.o \
./Hardware/JY61P.o \
./Hardware/OV2640.o 

C_DEPS += \
./Hardware/GPS.d \
./Hardware/JY61P.d \
./Hardware/OV2640.d 


# Each subdirectory must supply rules for building sources it contributes
Hardware/GPS.o: ../Hardware/GPS.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32H750xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Drivers/CMSIS/Include -I"C:/Users/Abner/Documents/Code/BUJIdesignCheck/ToolsCore" -I"C:/Users/Abner/Documents/Code/BUJIdesignCheck/Hardware" -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/STM32H7xx_HAL_Driver/Inc -I"C:/Users/Abner/Documents/Code/BUJIdesignCheck/Ctrl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Hardware/GPS.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Hardware/JY61P.o: ../Hardware/JY61P.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32H750xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Drivers/CMSIS/Include -I"C:/Users/Abner/Documents/Code/BUJIdesignCheck/ToolsCore" -I"C:/Users/Abner/Documents/Code/BUJIdesignCheck/Hardware" -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/STM32H7xx_HAL_Driver/Inc -I"C:/Users/Abner/Documents/Code/BUJIdesignCheck/Ctrl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Hardware/JY61P.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Hardware/OV2640.o: ../Hardware/OV2640.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32H750xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Drivers/CMSIS/Include -I"C:/Users/Abner/Documents/Code/BUJIdesignCheck/ToolsCore" -I"C:/Users/Abner/Documents/Code/BUJIdesignCheck/Hardware" -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/STM32H7xx_HAL_Driver/Inc -I"C:/Users/Abner/Documents/Code/BUJIdesignCheck/Ctrl" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Hardware/OV2640.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

