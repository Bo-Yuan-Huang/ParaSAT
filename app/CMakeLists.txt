# ---------------------------------------------------------------------------- #
# TARGET
# executable
# ---------------------------------------------------------------------------- #
add_executable(${PARASAT_EXE_NAME} 
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cc
)

# ---------------------------------------------------------------------------- #
# LINK LIBRARIES
# external dependencies
# ---------------------------------------------------------------------------- #
##
## paraSatCore
##
target_link_libraries(${PARASAT_EXE_NAME} PUBLIC ${PARASAT_LIB_NAME})

