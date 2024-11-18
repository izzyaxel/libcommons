cmake_minimum_required(VERSION 3.29 FATAL_ERROR)

set(ARCH "x86_64")
set(CMAKE_CXX_STANDARD 23)
cmake_policy(SET CMP0100 NEW)

#Base flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wformat-security -Wno-unused -Wno-array-bounds -Wno-stringop-overflow")

if(CMAKE_BUILD_TYPE MATCHES Release OR CMAKE_BUILD_TYPE MATCHES MinSizeRel OR CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
  set(REL_BUILD "true")
endif()

#Platform-specific flags
if(WIN32 OR WIN64)
  add_definitions(-DWINDOWS)
  if(${REL_BUILD} MATCHES "true")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIE")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--high-entropy-va -Wl,--dynamicbase -Wl,--nxcompat")
  endif()
elseif(UNIX)
  add_definitions(-DLINUX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
  if(${REL_BUILD} MATCHES "true")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIE")
  endif()
elseif(APPLE)
  add_definitions(-DOSX)
endif()

if(${REL_BUILD} MATCHES "true")
  set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")
  add_definitions(-DRELEASE)
elseif(CMAKE_BUILD_TYPE MATCHES Debug)
  set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -O0")
  add_definitions(-DDEBUG)
endif()

project(commons)
set(CMAKE_CXX_STANDARD 23)
set(SRC
    src/commons/export.hh

    src/commons/events.hh
    src/commons/serialization.hh
    
    src/buffer.cc
    src/commons/buffer.hh
    src/misc.cc
    src/commons/misc.hh
    src/stringtools.cc
    src/commons/stringtools.hh
    src/fileio.cc
    src/commons/fileio.hh
    src/logger.cc
    src/commons/logger.hh
    src/scheduling.cc
    src/commons/scheduling.hh
    src/threadpool.cc
    src/commons/threadpool.hh
    src/dataBuffer.cc
    src/commons/dataBuffer.hh
    src/random.cc
    src/commons/random.hh

    src/commons/math/general.hh
    src/commons/math/util.hh
    src/commons/math/glmconversion.hh
    src/commons/math/interpolation.hh
    src/commons/math/compound.hh
    src/commons/math/vec2.hh
    src/commons/math/vec3.hh
    src/commons/math/vec4.hh
    src/commons/math/circle.hh
    src/commons/math/aabb2D.hh
    src/commons/math/aabb3D.hh
    src/commons/math/mat3.hh
    src/commons/math/mat4.hh
    src/commons/math/quaternion.hh
    src/commons/math/linesegment2D.hh)

add_definitions(-DSTATICBUILD)
add_library(${PROJECT_NAME} STATIC ${SRC})
