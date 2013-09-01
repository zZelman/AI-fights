################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/1\ Main.cpp \
../src/CAI.cpp \
../src/CGame.cpp \
../src/CGenerator.cpp \
../src/CGenerator_AI.cpp \
../src/CGenerator_Room.cpp \
../src/CMap.cpp \
../src/CMusic.cpp \
../src/CPhysics.cpp \
../src/CResourceDirectories.cpp \
../src/CRoom.cpp \
../src/CRoom_1x1.cpp \
../src/CRoom_1x2.cpp \
../src/CRoom_2x1.cpp \
../src/CRoom_2x2.cpp \
../src/CSprite.cpp \
../src/CTimer.cpp \
../src/CUpdatable.cpp \
../src/CWindow.cpp \
../src/Math2D.cpp \
../src/stdafx.cpp 

OBJS += \
./src/1\ Main.o \
./src/CAI.o \
./src/CGame.o \
./src/CGenerator.o \
./src/CGenerator_AI.o \
./src/CGenerator_Room.o \
./src/CMap.o \
./src/CMusic.o \
./src/CPhysics.o \
./src/CResourceDirectories.o \
./src/CRoom.o \
./src/CRoom_1x1.o \
./src/CRoom_1x2.o \
./src/CRoom_2x1.o \
./src/CRoom_2x2.o \
./src/CSprite.o \
./src/CTimer.o \
./src/CUpdatable.o \
./src/CWindow.o \
./src/Math2D.o \
./src/stdafx.o 

CPP_DEPS += \
./src/1\ Main.d \
./src/CAI.d \
./src/CGame.d \
./src/CGenerator.d \
./src/CGenerator_AI.d \
./src/CGenerator_Room.d \
./src/CMap.d \
./src/CMusic.d \
./src/CPhysics.d \
./src/CResourceDirectories.d \
./src/CRoom.d \
./src/CRoom_1x1.d \
./src/CRoom_1x2.d \
./src/CRoom_2x1.d \
./src/CRoom_2x2.d \
./src/CSprite.d \
./src/CTimer.d \
./src/CUpdatable.d \
./src/CWindow.d \
./src/Math2D.d \
./src/stdafx.d 


# Each subdirectory must supply rules for building sources it contributes
src/1\ Main.o: ../src/1\ Main.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/1 Main.d" -MT"src/1\ Main.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


