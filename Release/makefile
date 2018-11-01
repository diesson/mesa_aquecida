################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include lib/subdir.mk
-include display/subdir.mk
-include control/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Mesa_aquecida.lss \

FLASH_IMAGE += \
Mesa_aquecida.hex \

EEPROM_IMAGE += \
Mesa_aquecida.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Mesa_aquecida.elf secondary-outputs

# Tool invocations
Mesa_aquecida.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Mesa_aquecida.map -mmcu=atmega328p -o "Mesa_aquecida.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Mesa_aquecida.lss: Mesa_aquecida.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Mesa_aquecida.elf  >"Mesa_aquecida.lss"
	@echo 'Finished building: $@'
	@echo ' '

Mesa_aquecida.hex: Mesa_aquecida.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Mesa_aquecida.elf  "Mesa_aquecida.hex"
	@echo 'Finished building: $@'
	@echo ' '

Mesa_aquecida.eep: Mesa_aquecida.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Mesa_aquecida.elf  "Mesa_aquecida.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Mesa_aquecida.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p Mesa_aquecida.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Mesa_aquecida.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
