################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Hardware_Independent_Layer/LCD.c" \
"../Sources/Hardware_Independent_Layer/TimeBaseGen.c" \

C_SRCS += \
../Sources/Hardware_Independent_Layer/LCD.c \
../Sources/Hardware_Independent_Layer/TimeBaseGen.c \

OBJS += \
./Sources/Hardware_Independent_Layer/LCD.o \
./Sources/Hardware_Independent_Layer/TimeBaseGen.o \

C_DEPS += \
./Sources/Hardware_Independent_Layer/LCD.d \
./Sources/Hardware_Independent_Layer/TimeBaseGen.d \

OBJS_QUOTED += \
"./Sources/Hardware_Independent_Layer/LCD.o" \
"./Sources/Hardware_Independent_Layer/TimeBaseGen.o" \

C_DEPS_QUOTED += \
"./Sources/Hardware_Independent_Layer/LCD.d" \
"./Sources/Hardware_Independent_Layer/TimeBaseGen.d" \

OBJS_OS_FORMAT += \
./Sources/Hardware_Independent_Layer/LCD.o \
./Sources/Hardware_Independent_Layer/TimeBaseGen.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Hardware_Independent_Layer/LCD.o: ../Sources/Hardware_Independent_Layer/LCD.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Hardware_Independent_Layer/LCD.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Hardware_Independent_Layer/LCD.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Hardware_Independent_Layer/TimeBaseGen.o: ../Sources/Hardware_Independent_Layer/TimeBaseGen.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Hardware_Independent_Layer/TimeBaseGen.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Hardware_Independent_Layer/TimeBaseGen.o"
	@echo 'Finished building: $<'
	@echo ' '


