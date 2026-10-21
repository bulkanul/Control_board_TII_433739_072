execute_process(
    COMMAND "${GIT_EXECUTABLE}" -C "${REPOSITORY_DIR}" rev-parse --short=7 HEAD
    RESULT_VARIABLE GIT_RESULT
    OUTPUT_VARIABLE COMMIT_HASH
    ERROR_VARIABLE GIT_ERROR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(NOT GIT_RESULT EQUAL 0)
    message(FATAL_ERROR "Could not get the current Git commit hash: ${GIT_ERROR}")
endif()

if(NOT COMMIT_HASH MATCHES "^[0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F]$")
    message(FATAL_ERROR "Git returned an invalid 7-character commit hash: ${COMMIT_HASH}")
endif()

set(HEX_FILE "${OUTPUT_DIR}/${PROJECT_NAME}_${COMMIT_HASH}.hex")

execute_process(
    COMMAND "${OBJCOPY}" -O ihex "${ELF_FILE}" "${HEX_FILE}"
    RESULT_VARIABLE OBJCOPY_RESULT
    ERROR_VARIABLE OBJCOPY_ERROR
)

if(NOT OBJCOPY_RESULT EQUAL 0)
    message(FATAL_ERROR "Could not generate ${HEX_FILE}: ${OBJCOPY_ERROR}")
endif()

message(STATUS "Generated ${HEX_FILE}")
