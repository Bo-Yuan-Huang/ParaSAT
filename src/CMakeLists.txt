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

# ---------------------------------------------------------------------------- #
# TARGET
# archive library 
# ---------------------------------------------------------------------------- #
add_library(${PARASAT_LIB_NAME} 
  ${CMAKE_CURRENT_SOURCE_DIR}/core/Solver.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/utils/Options.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/utils/System.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/simp/SimpSolver.cc
)
add_library(${PROJECT_NAME}::${PARASAT_LIB_NAME} ALIAS ${PARASAT_LIB_NAME})

##
## compile features/options
##
target_compile_features(${PARASAT_LIB_NAME} PUBLIC cxx_std_17)
target_compile_definitions(${PARASAT_LIB_NAME} PRIVATE __STDC_FORMAT_MACROS)
target_compile_definitions(${PARASAT_LIB_NAME} PRIVATE __STDC_LIMIT_MACROS)

set_property(
  TARGET ${PARASAT_LIB_NAME}
  PROPERTY POSITION_INDEPENDENT_CODE ON
)

if(${CMAKE_COMPILER_IS_GNUCXX})
  if(${CMAKE_PROJECT_NAME} MATCHES ${PROJECT_NAME})
    if(${CMAKE_BUILD_TYPE} MATCHES Debug)
      target_compile_options(${PARASAT_LIB_NAME} PUBLIC "-Wall")
    endif()
  endif()
endif()

##
## include paths
##
target_include_directories(${PARASAT_LIB_NAME}
  PUBLIC
  $<INSTALL_INTERFACE:${PARASAT_INCLUDE_INSTALL_DIR}>
  $<BUILD_INTERFACE:${PARASAT_INCLUDE_BUILD_DIR}>
)

# ---------------------------------------------------------------------------- #
# LINK LIBRARIES
# external dependencies
# ---------------------------------------------------------------------------- #
##
## filesystem
##
if(NOT APPLE)
  target_link_libraries(${PARASAT_LIB_NAME} PUBLIC stdc++fs)
endif()

##
## ZLIB
##
find_package(ZLIB REQUIRED)
target_link_libraries(${PARASAT_LIB_NAME} PUBLIC ZLIB::ZLIB)

##
## glog
##
target_link_libraries(${PARASAT_LIB_NAME} PUBLIC glog::glog)

##
## fmt lib
##
target_link_libraries(${PARASAT_LIB_NAME} PUBLIC fmt::fmt)
