################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/stm32f4_discovery.c \
../Utilities/stm32f4_discovery_lis302dl.c 

OBJS += \
./Utilities/stm32f4_discovery.o \
./Utilities/stm32f4_discovery_lis302dl.o 

C_DEPS += \
./Utilities/stm32f4_discovery.d \
./Utilities/stm32f4_discovery_lis302dl.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/%.o: ../Utilities/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F407VGTx -DSTM32F4DISCOVERY -DSTM32F40XX -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -I"C:/Users/Olga Kryspin/Desktop/Ambi_paczka/AmbilightUSB2/Utilities" -I"C:/Users/Olga Kryspin/Desktop/Ambi_paczka/AmbilightUSB2/StdPeriph_Driver/inc" -I"C:/Users/Olga Kryspin/Desktop/Ambi_paczka/AmbilightUSB2/inc" -I"C:/Users/Olga Kryspin/Desktop/Ambi_paczka/AmbilightUSB2/CMSIS/device" -I"C:/Users/Olga Kryspin/Desktop/Ambi_paczka/AmbilightUSB2/CMSIS/core" -O3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


