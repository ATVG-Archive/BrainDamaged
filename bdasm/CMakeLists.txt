set(CURRENT_TARGET "BDASM")

message(STATUS "\nConfiguring target ${CURRENT_TARGET}...")

CreateTarget(${CURRENT_TARGET} EXECUTABLE bdasm 20)

set(BDASM_INCLUDE_DIR "${CURRENT_TARGET_DIR}/include")
set(BDASM_INCLUDE_DIR "${CURRENT_TARGET_DIR}" PARENT_SCOPE)
message(STATUS "${CURRENT_TARGET} include directory: ${BDASM_INCLUDE_DIR}")

# disable foreach macro
add_definitions(-DQT_NO_FOREACH)

set_target_properties(${CURRENT_TARGET} PROPERTIES PREFIX "")
set_target_properties(${CURRENT_TARGET} PROPERTIES OUTPUT_NAME "bdasm")

target_include_directories(${CURRENT_TARGET}
PRIVATE
    "${BDASM_INCLUDE_DIR}"
)

message(STATUS "Configured target ${CURRENT_TARGET}.\n")