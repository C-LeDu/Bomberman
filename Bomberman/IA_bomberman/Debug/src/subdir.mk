################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/IA_bomberman.cpp 

OBJS += \
./src/IA_bomberman.o 

CPP_DEPS += \
./src/IA_bomberman.d 


# Each subdirectory must supply rules for building sources it contributes
src/IA_bomberman.o: ../src/IA_bomberman.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/IA_bomberman.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


