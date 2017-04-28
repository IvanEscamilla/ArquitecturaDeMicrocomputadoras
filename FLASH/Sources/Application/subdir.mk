################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Application/main.c" \
"../Sources/Application/sa_mtb.c" \

C_SRCS += \
../Sources/Application/main.c \
../Sources/Application/sa_mtb.c \

S_SRCS += \
../Sources/Application/Dispatcher.s \

S_SRCS_QUOTED += \
"../Sources/Application/Dispatcher.s" \

S_DEPS_QUOTED += \
"./Sources/Application/Dispatcher.d" \

OBJS += \
./Sources/Application/Dispatcher.o \
./Sources/Application/main.o \
./Sources/Application/sa_mtb.o \

C_DEPS += \
./Sources/Application/main.d \
./Sources/Application/sa_mtb.d \

S_DEPS += \
./Sources/Application/Dispatcher.d \

OBJS_QUOTED += \
"./Sources/Application/Dispatcher.o" \
"./Sources/Application/main.o" \
"./Sources/Application/sa_mtb.o" \

C_DEPS_QUOTED += \
"./Sources/Application/main.d" \
"./Sources/Application/sa_mtb.d" \

OBJS_OS_FORMAT += \
./Sources/Application/Dispatcher.o \
./Sources/Application/main.o \
./Sources/Application/sa_mtb.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Application/Dispatcher.o: ../Sources/Application/Dispatcher.s
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ARM Ltd Windows GCC Assembler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Application/Dispatcher.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Application/Dispatcher.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Application/main.o: ../Sources/Application/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Application/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Application/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Application/sa_mtb.o: ../Sources/Application/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Application/sa_mtb.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Application/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '


