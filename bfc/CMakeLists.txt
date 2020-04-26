set(CURRENT_TARGET "BFC")

message(STATUS "\nConfiguring target ${CURRENT_TARGET}...")

CreateTarget(${CURRENT_TARGET} EXECUTABLE bfc 20)

set(BFC_INCLUDE_DIR "${CURRENT_TARGET_DIR}/include")
set(BFC_INCLUDE_DIR "${CURRENT_TARGET_DIR}" PARENT_SCOPE)
message(STATUS "${CURRENT_TARGET} include directory: ${BFC_INCLUDE_DIR}")

# disable foreach macro
add_definitions(-DQT_NO_FOREACH)

set_target_properties(${CURRENT_TARGET} PROPERTIES PREFIX "")
set_target_properties(${CURRENT_TARGET} PROPERTIES OUTPUT_NAME "bfc")

target_include_directories(${CURRENT_TARGET}
PRIVATE
    "${BFC_INCLUDE_DIR}"
)

message(STATUS "Configured target ${CURRENT_TARGET}.\n")