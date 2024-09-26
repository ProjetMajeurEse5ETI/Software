################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Sequenceur_Driver/Seq_Half_Bridge.c 

OBJS += \
./Core/Sequenceur_Driver/Seq_Half_Bridge.o 

C_DEPS += \
./Core/Sequenceur_Driver/Seq_Half_Bridge.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Sequenceur_Driver/%.o: ../Core/Sequenceur_Driver/%.c Core/Sequenceur_Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xC -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Sequenceur_Driver

clean-Core-2f-Sequenceur_Driver:
	-$(RM) ./Core/Sequenceur_Driver/Seq_Half_Bridge.d ./Core/Sequenceur_Driver/Seq_Half_Bridge.o

.PHONY: clean-Core-2f-Sequenceur_Driver

