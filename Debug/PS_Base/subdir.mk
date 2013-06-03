################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../PS_Base/FastAccessToNamedResource.cpp \
../PS_Base/PS_AppConfig.cpp \
../PS_Base/PS_CPU_INFO.cpp \
../PS_Base/PS_ErrorManager.cpp \
../PS_Base/PS_FileDirectory.cpp \
../PS_Base/PS_Logger.cpp \
../PS_Base/PS_String.cpp 

OBJS += \
./PS_Base/FastAccessToNamedResource.o \
./PS_Base/PS_AppConfig.o \
./PS_Base/PS_CPU_INFO.o \
./PS_Base/PS_ErrorManager.o \
./PS_Base/PS_FileDirectory.o \
./PS_Base/PS_Logger.o \
./PS_Base/PS_String.o 

CPP_DEPS += \
./PS_Base/FastAccessToNamedResource.d \
./PS_Base/PS_AppConfig.d \
./PS_Base/PS_CPU_INFO.d \
./PS_Base/PS_ErrorManager.d \
./PS_Base/PS_FileDirectory.d \
./PS_Base/PS_Logger.d \
./PS_Base/PS_String.d 


# Each subdirectory must supply rules for building sources it contributes
PS_Base/%.o: ../PS_Base/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/X11/include -I"/Users/pourya/Desktop/Projects/BlobRay" -I/System/Library/Frameworks/OpenGL.framework/Headers -I/Users/pourya/Desktop/Projects/Dependencies/LOKI/include -I/Users/pourya/Desktop/Projects/Dependencies/OPENCL/common/inc -I/Users/pourya/Desktop/Projects/Dependencies/TBB/include -I/Users/pourya/Desktop/Projects/Dependencies/GLUI/src/include -I/Users/pourya/Desktop/Projects/Dependencies/GLEW/include -I/Users/pourya/Desktop/Projects/Dependencies/BOARD/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


