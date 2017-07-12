################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../peripherals/gpio-ioe.c \
../peripherals/mag3110.c \
../peripherals/mma8451.c \
../peripherals/mpl3115.c \
../peripherals/pam7q.c \
../peripherals/selector.c \
../peripherals/sx1509.c \
../peripherals/sx9500.c 

OBJS += \
./peripherals/gpio-ioe.o \
./peripherals/mag3110.o \
./peripherals/mma8451.o \
./peripherals/mpl3115.o \
./peripherals/pam7q.o \
./peripherals/selector.o \
./peripherals/sx1509.o \
./peripherals/sx9500.o 

C_DEPS += \
./peripherals/gpio-ioe.d \
./peripherals/mag3110.d \
./peripherals/mma8451.d \
./peripherals/mpl3115.d \
./peripherals/pam7q.d \
./peripherals/selector.d \
./peripherals/sx1509.d \
./peripherals/sx9500.d 


# Each subdirectory must supply rules for building sources it contributes
peripherals/gpio-ioe.o: ../peripherals/gpio-ioe.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DEFM32HG322F64=1' '-DUSE_BAND_868=' '-DDEBUG=1' -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32HG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/SLSTK3400A_EFM32HG/config" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\boards" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\mac" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\peripherals" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\radio" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\system" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\src" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"peripherals/gpio-ioe.d" -MT"peripherals/gpio-ioe.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

peripherals/mag3110.o: ../peripherals/mag3110.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DEFM32HG322F64=1' '-DUSE_BAND_868=' '-DDEBUG=1' -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32HG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/SLSTK3400A_EFM32HG/config" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\boards" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\mac" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\peripherals" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\radio" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\system" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\src" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"peripherals/mag3110.d" -MT"peripherals/mag3110.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

peripherals/mma8451.o: ../peripherals/mma8451.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DEFM32HG322F64=1' '-DUSE_BAND_868=' '-DDEBUG=1' -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32HG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/SLSTK3400A_EFM32HG/config" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\boards" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\mac" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\peripherals" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\radio" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\system" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\src" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"peripherals/mma8451.d" -MT"peripherals/mma8451.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

peripherals/mpl3115.o: ../peripherals/mpl3115.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DEFM32HG322F64=1' '-DUSE_BAND_868=' '-DDEBUG=1' -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32HG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/SLSTK3400A_EFM32HG/config" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\boards" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\mac" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\peripherals" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\radio" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\system" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\src" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"peripherals/mpl3115.d" -MT"peripherals/mpl3115.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

peripherals/pam7q.o: ../peripherals/pam7q.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DEFM32HG322F64=1' '-DUSE_BAND_868=' '-DDEBUG=1' -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32HG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/SLSTK3400A_EFM32HG/config" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\boards" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\mac" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\peripherals" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\radio" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\system" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\src" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"peripherals/pam7q.d" -MT"peripherals/pam7q.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

peripherals/selector.o: ../peripherals/selector.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DEFM32HG322F64=1' '-DUSE_BAND_868=' '-DDEBUG=1' -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32HG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/SLSTK3400A_EFM32HG/config" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\boards" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\mac" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\peripherals" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\radio" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\system" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\src" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"peripherals/selector.d" -MT"peripherals/selector.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

peripherals/sx1509.o: ../peripherals/sx1509.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DEFM32HG322F64=1' '-DUSE_BAND_868=' '-DDEBUG=1' -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32HG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/SLSTK3400A_EFM32HG/config" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\boards" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\mac" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\peripherals" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\radio" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\system" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\src" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"peripherals/sx1509.d" -MT"peripherals/sx1509.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

peripherals/sx9500.o: ../peripherals/sx9500.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 '-DEFM32HG322F64=1' '-DUSE_BAND_868=' '-DDEBUG=1' -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32HG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/SLSTK3400A_EFM32HG/config" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\boards" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\mac" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\peripherals" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\radio" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\system" -I"C:\Users\geoffrey.ottoy\SimplicityStudio\v4_workspace\DRAMCO_LoRA\src" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"peripherals/sx9500.d" -MT"peripherals/sx9500.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


