# Copyright (c) 2014-2015 cyrille_favreau@hotmail.com

cmake_minimum_required(VERSION 2.8)

project(ModelViewerService)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake
  ${CMAKE_SOURCE_DIR}/CMake/common)
include(GitExternal)

set(VERSION_MAJOR "0")
set(VERSION_MINOR "1")
set(VERSION_PATCH "0")
set(VERSION_ABI 1)

include(Common)

if(APPLE)
  cmake_policy(SET CMP0042 NEW)
  set(CMAKE_OSX_DEPLOYMENT_TARGET "10.10" CACHE STRING "Deployment target for OSX" FORCE)
  set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
  set(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE STRING "OSX Architectures" FORCE)
endif()

set(MODELVIEWERSERVICE_DESCRIPTION "Simple 3D Model Viewer exposing ZeroEQ event for remote access")

common_package(GLUT REQUIRED SYSTEM)
common_package(OpenGL REQUIRED)
common_package(assimp)
common_package_post()

# ------------------------------------------------------------------------------
# Applications and libraries
# ------------------------------------------------------------------------------

if(APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -framework OpenGL -Wno-narrowing -Wno-deprecated-declarations")
endif()

add_subdirectory(src)
include(PackageConfig)
