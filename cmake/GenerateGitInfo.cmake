execute_process(
    COMMAND "${GIT_EXECUTABLE}" -C "${REPOSITORY_DIR}" log -1 --pretty=format:%H,%d
    RESULT_VARIABLE GIT_RESULT
    OUTPUT_VARIABLE GIT_INFO
    ERROR_VARIABLE GIT_ERROR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(NOT GIT_RESULT EQUAL 0)
    message(FATAL_ERROR "Could not get Git commit information: ${GIT_ERROR}")
endif()

if(GIT_INFO STREQUAL "")
    message(FATAL_ERROR "Git returned empty commit information")
endif()

string(REPLACE [[\]] [[\\]] GIT_INFO "${GIT_INFO}")
string(REPLACE [["]] [[\"]] GIT_INFO "${GIT_INFO}")

set(GIT_INFO_CONTENT
    "#define GIT_INFO_PRESENT\n static const char* GIT_INFO = \"Version Information=[${GIT_INFO}]\\r\\n\";\n"
)

set(WRITE_HEADER TRUE)
if(EXISTS "${OUTPUT_FILE}")
    file(READ "${OUTPUT_FILE}" CURRENT_CONTENT)
    if(CURRENT_CONTENT STREQUAL GIT_INFO_CONTENT)
        set(WRITE_HEADER FALSE)
    endif()
endif()

if(WRITE_HEADER)
    file(WRITE "${OUTPUT_FILE}" "${GIT_INFO_CONTENT}")
endif()
