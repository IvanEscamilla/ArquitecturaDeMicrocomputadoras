################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Service_Layer/StandarLibrary.c" \
"../Sources/Service_Layer/Task.c" \

C_SRCS += \
../Sources/Service_Layer/StandarLibrary.c \
../Sources/Service_Layer/Task.c \

OBJS += \
./Sources/Service_Layer/StandarLibrary.o \
./Sources/Service_Layer/Task.o \

C_DEPS += \
./Sources/Service_Layer/StandarLibrary.d \
./Sources/Service_Layer/Task.d \

OBJS_QUOTED += \
"./Sources/Service_Layer/StandarLibrary.o" \
"./Sources/Service_Layer/Task.o" \

C_DEPS_QUOTED += \
"./Sources/Service_Layer/StandarLibrary.d" \
"./Sources/Service_Layer/Task.d" \

OBJS_OS_FORMAT += \
./Sources/Service_Layer/StandarLibrary.o \
./Sources/Service_Layer/Task.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Service_Layer/StandarLibrary.o: ../Sources/Service_Layer/StandarLibrary.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Service_Layer/StandarLibrary.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Service_Layer/StandarLibrary.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Service_Layer/Task.o: ../Sources/Service_Layer/Task.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Service_Layer/Task.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Service_Layer/Task.o"
	@echo 'Finished building: $<'
	@echo ' '


