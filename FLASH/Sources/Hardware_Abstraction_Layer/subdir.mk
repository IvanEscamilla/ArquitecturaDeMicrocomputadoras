################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Hardware_Abstraction_Layer/GPIO.c" \
"../Sources/Hardware_Abstraction_Layer/TimerA.c" \

C_SRCS += \
../Sources/Hardware_Abstraction_Layer/GPIO.c \
../Sources/Hardware_Abstraction_Layer/TimerA.c \

OBJS += \
./Sources/Hardware_Abstraction_Layer/GPIO.o \
./Sources/Hardware_Abstraction_Layer/TimerA.o \

C_DEPS += \
./Sources/Hardware_Abstraction_Layer/GPIO.d \
./Sources/Hardware_Abstraction_Layer/TimerA.d \

OBJS_QUOTED += \
"./Sources/Hardware_Abstraction_Layer/GPIO.o" \
"./Sources/Hardware_Abstraction_Layer/TimerA.o" \

C_DEPS_QUOTED += \
"./Sources/Hardware_Abstraction_Layer/GPIO.d" \
"./Sources/Hardware_Abstraction_Layer/TimerA.d" \

OBJS_OS_FORMAT += \
./Sources/Hardware_Abstraction_Layer/GPIO.o \
./Sources/Hardware_Abstraction_Layer/TimerA.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Hardware_Abstraction_Layer/GPIO.o: ../Sources/Hardware_Abstraction_Layer/GPIO.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Hardware_Abstraction_Layer/GPIO.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Hardware_Abstraction_Layer/GPIO.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Hardware_Abstraction_Layer/TimerA.o: ../Sources/Hardware_Abstraction_Layer/TimerA.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Hardware_Abstraction_Layer/TimerA.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Hardware_Abstraction_Layer/TimerA.o"
	@echo 'Finished building: $<'
	@echo ' '


