################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/PPLAB1H\ -\ Leonel\ Monges.c \
../src/aviso.c \
../src/cliente.c \
../src/utn.c 

OBJS += \
./src/PPLAB1H\ -\ Leonel\ Monges.o \
./src/aviso.o \
./src/cliente.o \
./src/utn.o 

C_DEPS += \
./src/PPLAB1H\ -\ Leonel\ Monges.d \
./src/aviso.d \
./src/cliente.d \
./src/utn.d 


# Each subdirectory must supply rules for building sources it contributes
src/PPLAB1H\ -\ Leonel\ Monges.o: ../src/PPLAB1H\ -\ Leonel\ Monges.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/PPLAB1H - Leonel Monges.d" -MT"src/PPLAB1H\ -\ Leonel\ Monges.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


