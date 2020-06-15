# ==============================================================================
# MIT License
#
# Copyright (c) 2020 Princeton University
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# ==============================================================================

cmake_minimum_required(VERSION 3.14.0)

# ---------------------------------------------------------------------------- #
# PROJECT
# name version language
# ---------------------------------------------------------------------------- #
project(paraSat VERSION     0.1
                LANGUAGES   CXX
)

# ---------------------------------------------------------------------------- #
# OPTION
# build configuration
# ---------------------------------------------------------------------------- #
include(CMakeDependentOption)

cmake_dependent_option(PARASAT_BUILD_TEST "Build unit tests."                 ON
  "PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME" OFF)

# ---------------------------------------------------------------------------- #
# VARARIABLE
# alias and configurations
# ---------------------------------------------------------------------------- #
set(PARASAT_TARGET_NAME ${PROJECT_NAME}) 
set(PARASAT_INCLUDE_INSTALL_DIR "include")
set(PARASAT_INCLUDE_BUILD_DIR "${PROJECT_SOURCE_DIR}/include")
set(PARASAT_TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")

if(${BUILD_SHARED_LIBS})
  set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
  set(CMAKE_MACOSX_RPATH TRUE)
endif()

# ---------------------------------------------------------------------------- #
# External dependencies
# ---------------------------------------------------------------------------- #
##
## make sure that custom modules can be found.
##
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

##
## third-party packages
##
include(FetchContent)

# glog::glog
FetchContent_Declare(
  glog
  GIT_REPOSITORY https://github.com/google/glog.git
  GIT_TAG        v0.4.0
)

# fmt::fmt
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG        6.2.1
)

# BFG::Lyra
FetchContent_Declare(
  lyra
  GIT_REPOSITORY https://github.com/bfgroup/Lyra.git
  GIT_TAG        1.4
)

# populate external packages
FetchContent_MakeAvailable(glog fmt lyra)

# ---------------------------------------------------------------------------- #
# TARGET
# library target
# ---------------------------------------------------------------------------- #
set(PARASAT_LIB_NAME ${PARASAT_TARGET_NAME}Core)
add_subdirectory(src)

# ---------------------------------------------------------------------------- #
# TARGET
# executable target
# ---------------------------------------------------------------------------- #
set(PARASAT_EXE_NAME ${PARASAT_TARGET_NAME})
add_subdirectory(app)

# ---------------------------------------------------------------------------- #
# INSTALL
# project and library
# ---------------------------------------------------------------------------- #
##
## install targets
##
install(
  TARGETS ${PARASAT_EXE_NAME} ${PARASAT_LIB_NAME}
  EXPORT  ${PARASAT_TARGETS_EXPORT_NAME}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION ${PARASAT_INCLUDE_INSTALL_DIR}
)

##
## include directory
##
configure_file(
  ${PROJECT_SOURCE_DIR}/src/config.h.in
  ${PROJECT_SOURCE_DIR}/include/parasat/config.h
  @ONLY
)

# ---------------------------------------------------------------------------- #
# UNINSTALL
# uninstall files listed in install_manifest.txt
# ---------------------------------------------------------------------------- #
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake"
    IMMEDIATE @ONLY
  )

  add_custom_target(uninstall
    COMMAND 
      ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_uninstall.cmake
  )

endif()

# ---------------------------------------------------------------------------- #
# Unit tests
# ---------------------------------------------------------------------------- #
if(${PARASAT_BUILD_TEST})
  enable_testing()
  add_subdirectory(test)
endif()

