# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_NO_FLASH 1)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(ALEDINCV2 C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/connection/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/led/*.cpp
)

add_executable(ALEDINCV2
    ${SOURCES}
)

pico_set_program_name(ALEDINCV2 "ALEDINCV2")
pico_set_program_version(ALEDINCV2 "0.1")

# Generate PIO header
pico_generate_pio_header(ALEDINCV2 ${CMAKE_CURRENT_LIST_DIR}/blink.pio)

pico_generate_pio_header(ALEDINCV2 ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(ALEDINCV2 0)
pico_enable_stdio_usb(ALEDINCV2 1)

# Add the standard library to the build
target_link_libraries(ALEDINCV2
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(ALEDINCV2 PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(ALEDINCV2 
        hardware_dma
        hardware_pio
        pico_cyw43_arch_none
        )
target_compile_options(ALEDINCV2 PRIVATE -fno-exceptions -fno-rtti -fno-threadsafe-statics)
target_link_options(ALEDINCV2 PRIVATE -nostartfiles -Wl,--undefined=__dso_handle)

#pico_add_extra_outputs(ALEDINCV2)
#pico_add_binary(ALEDINCV2)
#file(GLOB_RECURSE ALL_SOURCES CONFIGURE_DEPENDS
#    ${CMAKE_SOURCE_DIR}/*.cpp
#)
#target_sources(ALEDINCV2 PRIVATE ${ALL_SOURCES})
