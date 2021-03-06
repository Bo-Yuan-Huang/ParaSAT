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
##
## To keep cache clean
##
mark_as_advanced(
  BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
  gmock_build_tests gtest_build_samples gtest_build_tests
  gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)

##
## Keep IDEs that support folders clean
##
set_target_properties(gtest PROPERTIES FOLDER extern)
set_target_properties(gtest_main PROPERTIES FOLDER extern)
set_target_properties(gmock PROPERTIES FOLDER extern)
set_target_properties(gmock_main PROPERTIES FOLDER extern)

##
## Macro for adding new test
##
macro(package_add_test TESTNAME)
  add_executable(${TESTNAME} ${ARGN})
  target_link_libraries(${TESTNAME} gtest gmock gtest_main)
  add_test(${TESTNAME} ${TESTNAME})
  set_target_properties(${TESTNAME} PROPERTIES FOLDER test)
endmacro()

# ---------------------------------------------------------------------------- #
# External dependencies
# ---------------------------------------------------------------------------- #
# nlohmann_json::nlohmann_json
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG        v3.8.0
)

set(JSON_BuildTests OFF CACHE INTERNAL "")

FetchContent_MakeAvailable(json)

# ---------------------------------------------------------------------------- #
# TARGET
# unit tests 
# ---------------------------------------------------------------------------- #
set(PARASAT_TEST_MAIN sanity_check)

package_add_test(${PARASAT_TEST_MAIN} 
  main.cc
  t_sc18_main.cc
  t_sc18_rand.cc
)

set(PARASAT_TEST_SRC_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/data/config.h.in
  ${CMAKE_CURRENT_SOURCE_DIR}/config.h
  IMMEDIATE @ONLY
)

target_link_libraries(${PARASAT_TEST_MAIN} ${PARASAT_LIB_NAME})
target_link_libraries(${PARASAT_TEST_MAIN} nlohmann_json::nlohmann_json)

add_custom_target(run
  COMMAND "${CMAKE_CURRENT_BINARY_DIR}/${PARASAT_TEST_MAIN}"
)

add_custom_target(hard
  COMMAND "${CMAKE_CURRENT_BINARY_DIR}/${PARASAT_TEST_MAIN}" --gtest_also_run_disabled_tests
)

