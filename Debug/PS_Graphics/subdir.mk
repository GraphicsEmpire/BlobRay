################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../PS_Graphics/AffineWidgets.cpp \
../PS_Graphics/AssetManager.cpp \
../PS_Graphics/CLMeshBuffer.cpp \
../PS_Graphics/GroundMatrix.cpp \
../PS_Graphics/MeshRenderer.cpp \
../PS_Graphics/OclRayTracer.cpp \
../PS_Graphics/PS_ArcBallCamera.cpp \
../PS_Graphics/PS_Box.cpp \
../PS_Graphics/PS_ComputeDevice.cpp \
../PS_Graphics/PS_DebugUtils.cpp \
../PS_Graphics/PS_GLFuncs.cpp \
../PS_Graphics/PS_GLMeshBuffer.cpp \
../PS_Graphics/PS_GLSurface.cpp \
../PS_Graphics/PS_Matrix.cpp \
../PS_Graphics/PS_Mesh.cpp \
../PS_Graphics/PS_MeshRender.cpp \
../PS_Graphics/PS_OclScan.cpp \
../PS_Graphics/PS_Particles.cpp \
../PS_Graphics/PS_Pixmap.cpp \
../PS_Graphics/PS_Quaternion.cpp \
../PS_Graphics/PS_ShaderGLSL.cpp \
../PS_Graphics/PS_SketchConfig.cpp \
../PS_Graphics/Polygon.cpp \
../PS_Graphics/SceneBox.cpp \
../PS_Graphics/SceneGraph.cpp \
../PS_Graphics/ShaderManager.cpp \
../PS_Graphics/ThinPlateSpline.cpp \
../PS_Graphics/lodepng.cpp \
../PS_Graphics/testLib.cpp 

OBJS += \
./PS_Graphics/AffineWidgets.o \
./PS_Graphics/AssetManager.o \
./PS_Graphics/CLMeshBuffer.o \
./PS_Graphics/GroundMatrix.o \
./PS_Graphics/MeshRenderer.o \
./PS_Graphics/OclRayTracer.o \
./PS_Graphics/PS_ArcBallCamera.o \
./PS_Graphics/PS_Box.o \
./PS_Graphics/PS_ComputeDevice.o \
./PS_Graphics/PS_DebugUtils.o \
./PS_Graphics/PS_GLFuncs.o \
./PS_Graphics/PS_GLMeshBuffer.o \
./PS_Graphics/PS_GLSurface.o \
./PS_Graphics/PS_Matrix.o \
./PS_Graphics/PS_Mesh.o \
./PS_Graphics/PS_MeshRender.o \
./PS_Graphics/PS_OclScan.o \
./PS_Graphics/PS_Particles.o \
./PS_Graphics/PS_Pixmap.o \
./PS_Graphics/PS_Quaternion.o \
./PS_Graphics/PS_ShaderGLSL.o \
./PS_Graphics/PS_SketchConfig.o \
./PS_Graphics/Polygon.o \
./PS_Graphics/SceneBox.o \
./PS_Graphics/SceneGraph.o \
./PS_Graphics/ShaderManager.o \
./PS_Graphics/ThinPlateSpline.o \
./PS_Graphics/lodepng.o \
./PS_Graphics/testLib.o 

CPP_DEPS += \
./PS_Graphics/AffineWidgets.d \
./PS_Graphics/AssetManager.d \
./PS_Graphics/CLMeshBuffer.d \
./PS_Graphics/GroundMatrix.d \
./PS_Graphics/MeshRenderer.d \
./PS_Graphics/OclRayTracer.d \
./PS_Graphics/PS_ArcBallCamera.d \
./PS_Graphics/PS_Box.d \
./PS_Graphics/PS_ComputeDevice.d \
./PS_Graphics/PS_DebugUtils.d \
./PS_Graphics/PS_GLFuncs.d \
./PS_Graphics/PS_GLMeshBuffer.d \
./PS_Graphics/PS_GLSurface.d \
./PS_Graphics/PS_Matrix.d \
./PS_Graphics/PS_Mesh.d \
./PS_Graphics/PS_MeshRender.d \
./PS_Graphics/PS_OclScan.d \
./PS_Graphics/PS_Particles.d \
./PS_Graphics/PS_Pixmap.d \
./PS_Graphics/PS_Quaternion.d \
./PS_Graphics/PS_ShaderGLSL.d \
./PS_Graphics/PS_SketchConfig.d \
./PS_Graphics/Polygon.d \
./PS_Graphics/SceneBox.d \
./PS_Graphics/SceneGraph.d \
./PS_Graphics/ShaderManager.d \
./PS_Graphics/ThinPlateSpline.d \
./PS_Graphics/lodepng.d \
./PS_Graphics/testLib.d 


# Each subdirectory must supply rules for building sources it contributes
PS_Graphics/%.o: ../PS_Graphics/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/X11/include -I"/Users/pourya/Desktop/Projects/BlobRay" -I/System/Library/Frameworks/OpenGL.framework/Headers -I/Users/pourya/Desktop/Projects/Dependencies/LOKI/include -I/Users/pourya/Desktop/Projects/Dependencies/OPENCL/common/inc -I/Users/pourya/Desktop/Projects/Dependencies/TBB/include -I/Users/pourya/Desktop/Projects/Dependencies/GLUI/src/include -I/Users/pourya/Desktop/Projects/Dependencies/GLEW/include -I/Users/pourya/Desktop/Projects/Dependencies/BOARD/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


