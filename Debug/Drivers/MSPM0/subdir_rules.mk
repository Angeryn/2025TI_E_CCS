################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Drivers/MSPM0/%.o: ../Drivers/MSPM0/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/29555/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/BSP/MPU6050" -I"C:/Users/29555/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/BSP/MPU6050/DMP" -I"C:/Users/29555/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/CONTROL" -I"C:/Users/29555/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/HARDWARE" -I"C:/Users/29555/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/Drivers" -I"C:/Users/29555/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang" -I"C:/Users/29555/workspace_ccstheia/empty_LP_MSPM0G3507_nortos_ticlang/Debug" -I"C:/ti/mspm0_sdk_2_01_00_03/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_01_00_03/source" -gdwarf-3 -MMD -MP -MF"Drivers/MSPM0/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


