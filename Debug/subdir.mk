################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Raytracer.cpp \
../main.cpp 

OBJS += \
./Raytracer.o \
./main.o 

CPP_DEPS += \
./Raytracer.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/X11/include -I"/Users/pourya/Desktop/Projects/BlobRay" -I/System/Library/Frameworks/OpenGL.framework/Headers -I/Users/pourya/Desktop/Projects/Dependencies/LOKI/include -I/Users/pourya/Desktop/Projects/Dependencies/OPENCL/common/inc -I/Users/pourya/Desktop/Projects/Dependencies/TBB/include -I/Users/pourya/Desktop/Projects/Dependencies/GLUI/src/include -I/Users/pourya/Desktop/Projects/Dependencies/GLEW/include -I/Users/pourya/Desktop/Projects/Dependencies/BOARD/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


