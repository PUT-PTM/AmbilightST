################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c \
../src/syscalls.c \
../src/system_stm32f4xx.c \
../src/tm_stm32f4_disco.c \
../src/tm_stm32f4_gpio.c \
../src/tm_stm32f4_usb_vcp.c \
../src/usb_bsp.c \
../src/usb_core.c \
../src/usb_dcd.c \
../src/usb_dcd_int.c \
../src/usbd_cdc_core.c \
../src/usbd_cdc_vcp.c \
../src/usbd_core.c \
../src/usbd_desc.c \
../src/usbd_ioreq.c \
../src/usbd_req.c \
../src/usbd_usr.c \
../src/ws2812b.c 

OBJS += \
./src/main.o \
./src/syscalls.o \
./src/system_stm32f4xx.o \
./src/tm_stm32f4_disco.o \
./src/tm_stm32f4_gpio.o \
./src/tm_stm32f4_usb_vcp.o \
./src/usb_bsp.o \
./src/usb_core.o \
./src/usb_dcd.o \
./src/usb_dcd_int.o \
./src/usbd_cdc_core.o \
./src/usbd_cdc_vcp.o \
./src/usbd_core.o \
./src/usbd_desc.o \
./src/usbd_ioreq.o \
./src/usbd_req.o \
./src/usbd_usr.o \
./src/ws2812b.o 

C_DEPS += \
./src/main.d \
./src/syscalls.d \
./src/system_stm32f4xx.d \
./src/tm_stm32f4_disco.d \
./src/tm_stm32f4_gpio.d \
./src/tm_stm32f4_usb_vcp.d \
./src/usb_bsp.d \
./src/usb_core.d \
./src/usb_dcd.d \
./src/usb_dcd_int.d \
./src/usbd_cdc_core.d \
./src/usbd_cdc_vcp.d \
./src/usbd_core.d \
./src/usbd_desc.d \
./src/usbd_ioreq.d \
./src/usbd_req.d \
./src/usbd_usr.d \
./src/ws2812b.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F407VGTx -DSTM32F4DISCOVERY -DSTM32F40XX -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -I"C:/Users/Olga Kryspin/Desktop/Ambi_paczka/AmbilightUSB2/Utilities" -I"C:/Users/Olga Kryspin/Desktop/Ambi_paczka/AmbilightUSB2/StdPeriph_Driver/inc" -I"C:/Users/Olga Kryspin/Desktop/Ambi_paczka/AmbilightUSB2/inc" -I"C:/Users/Olga Kryspin/Desktop/Ambi_paczka/AmbilightUSB2/CMSIS/device" -I"C:/Users/Olga Kryspin/Desktop/Ambi_paczka/AmbilightUSB2/CMSIS/core" -O3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


