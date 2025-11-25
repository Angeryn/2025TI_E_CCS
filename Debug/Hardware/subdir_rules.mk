################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Hardware/%.o: ../Hardware/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/30253/workspace_ccstheia/222-3.Motor.OLED.encoder.huidu - 2/BSP/MPU6050" -I"C:/Users/30253/workspace_ccstheia/222-3.Motor.OLED.encoder.huidu - 2/BSP/MPU6050/DMP" -I"C:/Users/30253/workspace_ccstheia/222-3.Motor.OLED.encoder.huidu - 2/CONTROL" -I"C:/Users/30253/workspace_ccstheia/222-3.Motor.OLED.encoder.huidu - 2/HARDWARE" -I"C:/Users/30253/workspace_ccstheia/222-3.Motor.OLED.encoder.huidu - 2/Drivers" -I"C:/Users/30253/workspace_ccstheia/222-3.Motor.OLED.encoder.huidu - 2" -I"C:/Users/30253/workspace_ccstheia/222-3.Motor.OLED.encoder.huidu - 2/Debug" -I"C:/ti/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_01_00_03/source" -gdwarf-3 -MMD -MP -MF"Hardware/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


