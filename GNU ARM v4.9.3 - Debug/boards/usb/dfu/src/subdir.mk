################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../boards/usb/dfu/src/usbd_conf.c \
../boards/usb/dfu/src/usbd_desc.c \
../boards/usb/dfu/src/usbd_dfu_flash.c 

OBJS += \
./boards/usb/dfu/src/usbd_conf.o \
./boards/usb/dfu/src/usbd_desc.o \
./boards/usb/dfu/src/usbd_dfu_flash.o 

C_DEPS += \
./boards/usb/dfu/src/usbd_conf.d \
./boards/usb/dfu/src/usbd_desc.d \
./boards/usb/dfu/src/usbd_dfu_flash.d 


# Each subdirectory must supply rules for building sources it contributes
boards/usb/dfu/src/usbd_conf.o: ../boards/usb/dfu/src/usbd_conf.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DEFM32HG322F64=1' '-DUSE_BAND_868=' '-DDEBUG=1' -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32HG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/SLSTK3400A_EFM32HG/config" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\boards" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\mac" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\peripherals" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\radio" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\system" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\system\crypto" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\src" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"boards/usb/dfu/src/usbd_conf.d" -MT"boards/usb/dfu/src/usbd_conf.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

boards/usb/dfu/src/usbd_desc.o: ../boards/usb/dfu/src/usbd_desc.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DEFM32HG322F64=1' '-DUSE_BAND_868=' '-DDEBUG=1' -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32HG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/SLSTK3400A_EFM32HG/config" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\boards" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\mac" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\peripherals" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\radio" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\system" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\system\crypto" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\src" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"boards/usb/dfu/src/usbd_desc.d" -MT"boards/usb/dfu/src/usbd_desc.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

boards/usb/dfu/src/usbd_dfu_flash.o: ../boards/usb/dfu/src/usbd_dfu_flash.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DEFM32HG322F64=1' '-DUSE_BAND_868=' '-DDEBUG=1' -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32HG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/SLSTK3400A_EFM32HG/config" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\boards" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\mac" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\peripherals" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\radio" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\system" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\system\crypto" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\src" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"boards/usb/dfu/src/usbd_dfu_flash.d" -MT"boards/usb/dfu/src/usbd_dfu_flash.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


