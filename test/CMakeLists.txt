# ---------------------------------------------------------------------------- #
# External dependency
# ---------------------------------------------------------------------------- #
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.10.0
)

FetchContent_MakeAvailable(googletest)

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
# TARGET
# unit tests 
# ---------------------------------------------------------------------------- #
set(PARASAT_TEST_MAIN sanity_check)

package_add_test(${PARASAT_TEST_MAIN} 
  main.cc
  run_satcomp_bench.cc
)

set(PARASAT_TEST_SRC_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/data/config.h.in
  ${CMAKE_CURRENT_SOURCE_DIR}/config.h
  IMMEDIATE @ONLY
)

target_link_libraries(${PARASAT_TEST_MAIN} ${PARASAT_LIB_NAME})

add_custom_target(run
  COMMAND "${CMAKE_CURRENT_BINARY_DIR}/${PARASAT_TEST_MAIN}"
)

