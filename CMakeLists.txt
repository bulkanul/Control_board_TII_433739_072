cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME Control_board_TII_433739_072)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

find_package(Git REQUIRED)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/admin_mode.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/commands_handler.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/hardware.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/leds.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/params_func.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/server.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/tools.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/user_mode.c
    ${CMAKE_CURRENT_SOURCE_DIR}/board_prj_driver_lib/drivers/HPLD_1000.c
    ${CMAKE_CURRENT_SOURCE_DIR}/board_prj_driver_lib/drivers/HPLD_1500.c
    ${CMAKE_CURRENT_SOURCE_DIR}/board_prj_driver_lib/drivers/dac_ad5693_driver.c
    ${CMAKE_CURRENT_SOURCE_DIR}/board_prj_driver_lib/tools/adc_handler.c
    ${CMAKE_CURRENT_SOURCE_DIR}/board_prj_driver_lib/tools/temp_calc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/board_prj_driver_lib/tools/temp_control.c
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Remove wrong libob.a library dependency when using cpp files
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)

target_link_options(${CMAKE_PROJECT_NAME} PRIVATE "LINKER:-u,_printf_float")

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND}
        "-DPROJECT_NAME=$<TARGET_FILE_BASE_NAME:${CMAKE_PROJECT_NAME}>"
        "-DELF_FILE=$<TARGET_FILE:${CMAKE_PROJECT_NAME}>"
        "-DOUTPUT_DIR=$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>"
        "-DGIT_EXECUTABLE=${GIT_EXECUTABLE}"
        "-DREPOSITORY_DIR=${CMAKE_SOURCE_DIR}"
        "-DOBJCOPY=${CMAKE_OBJCOPY}"
        -P "${CMAKE_CURRENT_SOURCE_DIR}/cmake/GenerateHex.cmake"
    COMMENT "Generating project HEX with current commit hash"
    VERBATIM
)
