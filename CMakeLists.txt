cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
if(WIN32 OR WIN64)
	add_definitions(-DWINDOWS)
elseif(UNIX)
	add_definitions(-DLINUX)
elseif(APPLE)
	add_definitions(-DOSX)
endif()
project(commons)
set(CMAKE_CXX_STANDARD 17)
add_library(${PROJECT_NAME} STATIC
		src/commons/serialization.hh
		src/buffer.cc src/commons/buffer.hh
		src/events.cc src/commons/events.hh
		src/misc.cc src/commons/misc.hh
		src/stringtools.cc src/commons/stringtools.hh
		src/fileio.cc src/commons/fileio.hh
		src/logger.cc src/commons/logger.hh
		src/scheduling.cc src/commons/scheduling.hh
		src/threadpool.cc src/commons/threadpool.hh
		
		src/commons/math/compound.hh
		src/commons/math/general.hh
		src/commons/math/glmconversion.hh
		src/commons/math/interpolation.hh
		src/commons/math/mat3.hh
		src/commons/math/mat4.hh
		src/commons/math/quaternion.hh
		src/commons/math/shapes.hh
		src/commons/math/util.hh
		src/commons/math/vec2.hh
		src/commons/math/vec3.hh
		src/commons/math/vec4.hh)
