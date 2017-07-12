################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c 

OBJS += \
./src/main.o 

C_DEPS += \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/main.o: ../src/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DEFM32HG322F64=1' '-DUSE_BAND_868=' '-DDEBUG=1' -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32HG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/SLSTK3400A_EFM32HG/config" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\boards" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\mac" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\peripherals" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\radio" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\system" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\system\crypto" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\src" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"src/main.d" -MT"src/main.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


