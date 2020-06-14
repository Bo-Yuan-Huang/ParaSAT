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
  # add_subdirectory(test)
endif()

