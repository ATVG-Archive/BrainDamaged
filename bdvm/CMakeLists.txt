set(CURRENT_TARGET "BDVM")
set(OUTPUT_NAME bdvm)

message(STATUS "\nConfiguring target ${CURRENT_TARGET}...")

CreateTarget(${CURRENT_TARGET} EXECUTABLE bdvm 20)

set(BDVM_INCLUDE_DIR "${CURRENT_TARGET_DIR}/include")
set(BDVM_INCLUDE_DIR "${CURRENT_TARGET_DIR}" PARENT_SCOPE)
message(STATUS "${CURRENT_TARGET} include directory: ${BDVM_INCLUDE_DIR}")

# disable foreach macro
add_definitions(-DQT_NO_FOREACH)

set_target_properties(${CURRENT_TARGET} PROPERTIES PREFIX "")
set_target_properties(${CURRENT_TARGET} PROPERTIES OUTPUT_NAME "${OUTPUT_NAME}")

target_link_libraries(${CURRENT_TARGET}
PRIVATE
    fmt
    cxxopts
    libbdvm_interface
)

target_include_directories(${CURRENT_TARGET}
PRIVATE
    "${BDVM_INCLUDE_DIR}"
)

message(STATUS "Configured target ${CURRENT_TARGET}.\n")