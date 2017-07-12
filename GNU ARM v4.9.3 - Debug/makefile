################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include system/crypto/subdir.mk
-include system/subdir.mk
-include src/subdir.mk
-include radio/subdir.mk
-include mac/subdir.mk
-include emlib/subdir.mk
-include boards/subdir.mk
-include CMSIS/EFM32HG/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: DRAMCO_LoRA.axf

# Tool invocations
DRAMCO_LoRA.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb -T "DRAMCO_LoRA.ld" -Xlinker --gc-sections -Xlinker -Map="DRAMCO_LoRA.map" --specs=nano.specs -o DRAMCO_LoRA.axf "./system/crypto/aes.o" "./system/crypto/cmac.o" "./system/adc.o" "./system/delay.o" "./system/eeprom.o" "./system/fifo.o" "./system/gpio.o" "./system/gps.o" "./system/i2c.o" "./system/timer.o" "./system/uart.o" "./src/main.o" "./mac/LoRaMac.o" "./mac/LoRaMacCrypto.o" "./emlib/em_system.o" "./boards/adc-board.o" "./boards/board.o" "./boards/eeprom-board.o" "./boards/gpio-board.o" "./boards/gps-board.o" "./boards/i2c-board.o" "./boards/rtc-board.o" "./boards/spi-board.o" "./boards/uart-board.o" "./boards/uart-usb-board.o" "./CMSIS/EFM32HG/startup_efm32hg.o" "./CMSIS/EFM32HG/system_efm32hg.o" "./boards/sx1272-board.o" "./boards/utilities.o" "./emlib/em_cmu.o" "./emlib/em_emu.o" "./emlib/em_gpio.o" "./emlib/em_leuart.o" "./emlib/em_rtc.o" "./emlib/em_usart.o" "./radio/sx1272.o" -lm -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: DRAMCO_LoRA.hex'
	arm-none-eabi-objcopy -O ihex "DRAMCO_LoRA.axf" "DRAMCO_LoRA.hex"
	@echo ' '

	@echo 'Building bin file: DRAMCO_LoRA.bin'
	arm-none-eabi-objcopy -O binary "DRAMCO_LoRA.axf" "DRAMCO_LoRA.bin"
	@echo ' '

	@echo 'Building s37 file: DRAMCO_LoRA.s37'
	arm-none-eabi-objcopy -O srec "DRAMCO_LoRA.axf" "DRAMCO_LoRA.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "DRAMCO_LoRA.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) DRAMCO_LoRA.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
