set(CURRENT_TARGET "libbdvm")
set(OUTPUT_NAME libbdvm)
set(LIB_INTERFACE_NAME libbdvm_interface)

message(STATUS "\nConfiguring target ${CURRENT_TARGET}...")

CreateTarget(${CURRENT_TARGET} SHARED ${OUTPUT_NAME} 20)

set(LIBBDVM_INCLUDE_DIR "${CURRENT_TARGET_DIR}/include")
set(LIBBDVM_INCLUDE_DIR "${CURRENT_TARGET_DIR}" PARENT_SCOPE)
message(STATUS "${CURRENT_TARGET} include directory: ${LIBBDVM_INCLUDE_DIR}")

# disable foreach macro
add_definitions(-DQT_NO_FOREACH)

set_target_properties(${CURRENT_TARGET} PROPERTIES PREFIX "")
set_target_properties(${CURRENT_TARGET} PROPERTIES OUTPUT_NAME "${OUTPUT_NAME}")

target_include_directories(${CURRENT_TARGET}
PRIVATE
    "${LIBBDVM_INCLUDE_DIR}"
)

add_library(${LIB_INTERFACE_NAME} INTERFACE)
target_link_libraries(${LIB_INTERFACE_NAME} INTERFACE ${CURRENT_TARGET} ${OUTPUT_NAME})
target_include_directories(${LIB_INTERFACE_NAME} INTERFACE "${LIBBDVM_INCLUDE_DIR}")

message(STATUS "Configured target ${CURRENT_TARGET}.\n")