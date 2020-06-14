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
set(PARASAT_TARGET_NAME                ${PROJECT_NAME}) 
set(PARASAT_CONFIG_INSTALL_DIR         "lib/cmake/${PROJECT_NAME}" CACHE INTERNAL "")
set(PARASAT_INCLUDE_INSTALL_DIR        "include")
set(PARASAT_INCLUDE_BUILD_DIR          "${PROJECT_SOURCE_DIR}/include")
set(PARASAT_TARGETS_EXPORT_NAME        "${PROJECT_NAME}Targets")
set(PARASAT_CMAKE_CONFIG_TEMPLATE      "cmake/config.cmake.in")
set(PARASAT_CMAKE_CONFIG_DIR           "${CMAKE_CURRENT_BINARY_DIR}")
set(PARASAT_CMAKE_PROJECT_TARGETS_FILE "${PROJECT_NAME}Targets.cmake")

set(PARASAT_CMAKE_VERSION_CONFIG_FILE  
  "${PARASAT_CMAKE_CONFIG_DIR}/${PROJECT_NAME}ConfigVersion.cmake")

set(PARASAT_CMAKE_PROJECT_CONFIG_FILE  
  "${PARASAT_CMAKE_CONFIG_DIR}/${PROJECT_NAME}Config.cmake")

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
# add_subdirectory(extern)

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
  TARGETS ${PARASAT_LIB_NAME}
  EXPORT  ${PARASAT_TARGETS_EXPORT_NAME}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION ${PARASAT_INCLUDE_INSTALL_DIR}
)

##
## check if c++17 filesystem is available
##
# CHECK_INCLUDE_FILE_CXX(filesystem FS_INCLUDE)

##
## include directory
##
configure_file(
  ${PROJECT_SOURCE_DIR}/src/config.h.in
  ${PROJECT_SOURCE_DIR}/include/parasat/config.h
  @ONLY
)

install(
  DIRECTORY ${PARASAT_INCLUDE_BUILD_DIR}/parasat
  DESTINATION ${PARASAT_INCLUDE_INSTALL_DIR}
)

##
## forward version for find_package
##
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${PARASAT_CMAKE_VERSION_CONFIG_FILE} 
  VERSION ${PACAGE_VERSION}
  COMPATIBILITY AnyNewerVersion
)

##
## cmake config
##
configure_file(
  ${PARASAT_CMAKE_CONFIG_TEMPLATE}
  ${PARASAT_CMAKE_PROJECT_CONFIG_FILE}
  @ONLY
)

install(
  FILES ${PARASAT_CMAKE_PROJECT_CONFIG_FILE} ${PARASAT_CMAKE_VERSION_CONFIG_FILE}
  DESTINATION ${PARASAT_CONFIG_INSTALL_DIR}
)

##
## project export
##
install(
  EXPORT ${PARASAT_TARGETS_EXPORT_NAME}
  DESTINATION ${PARASAT_CONFIG_INSTALL_DIR}
  NAMESPACE ${PROJECT_NAME}::
  FILE ${PARASAT_CMAKE_PROJECT_TARGETS_FILE}
)

export(
  TARGETS ${PARASAT_LIB_NAME}
  NAMESPACE ${PROJECT_NAME}::
  FILE ${PARASAT_CMAKE_PROJECT_TARGETS_FILE}
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

