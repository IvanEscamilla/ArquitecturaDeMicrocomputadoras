################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Aplication/main.c" \
"../Sources/Aplication/sa_mtb.c" \

C_SRCS += \
../Sources/Aplication/main.c \
../Sources/Aplication/sa_mtb.c \

S_SRCS += \
../Sources/Aplication/Dispatcher.s \

S_SRCS_QUOTED += \
"../Sources/Aplication/Dispatcher.s" \

S_DEPS_QUOTED += \
"./Sources/Aplication/Dispatcher.d" \

OBJS += \
./Sources/Aplication/Dispatcher.o \
./Sources/Aplication/main.o \
./Sources/Aplication/sa_mtb.o \

C_DEPS += \
./Sources/Aplication/main.d \
./Sources/Aplication/sa_mtb.d \

S_DEPS += \
./Sources/Aplication/Dispatcher.d \

OBJS_QUOTED += \
"./Sources/Aplication/Dispatcher.o" \
"./Sources/Aplication/main.o" \
"./Sources/Aplication/sa_mtb.o" \

C_DEPS_QUOTED += \
"./Sources/Aplication/main.d" \
"./Sources/Aplication/sa_mtb.d" \

OBJS_OS_FORMAT += \
./Sources/Aplication/Dispatcher.o \
./Sources/Aplication/main.o \
./Sources/Aplication/sa_mtb.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Aplication/Dispatcher.o: ../Sources/Aplication/Dispatcher.s
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC Assembler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Aplication/Dispatcher.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Aplication/Dispatcher.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Aplication/main.o: ../Sources/Aplication/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Aplication/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Aplication/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Aplication/sa_mtb.o: ../Sources/Aplication/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Aplication/sa_mtb.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Aplication/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '


