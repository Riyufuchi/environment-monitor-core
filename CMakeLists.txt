cmake_minimum_required(VERSION 3.20)

project(environment_monitor_core LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_definitions(
    __AVR__
    __AVR_ATmega328P__
)


include_directories(/usr/lib/avr/include)

set(MCU atmega328p)
set(F_CPU 16000000UL)

set(SRC_DIR environment_core)
set(BUILD_DIR ${CMAKE_BINARY_DIR})

file(GLOB_RECURSE C_SOURCES
    ${SRC_DIR}/*.c
)

file(GLOB_RECURSE CPP_SOURCES
    ${SRC_DIR}/*.cpp
)

add_executable(firmware
    ${C_SOURCES}
    ${CPP_SOURCES}
)

target_compile_features(firmware PRIVATE cxx_std_17)

target_compile_options(firmware PRIVATE
    -Wall
    -Os
)

target_link_options(firmware PRIVATE
    -mmcu=${MCU}
)

add_custom_command(
    TARGET firmware POST_BUILD
    COMMAND avr-objcopy -O ihex -R .eeprom
            firmware firmware.hex
    COMMENT "Generating HEX file"
)

add_custom_target(flash
    COMMAND avrdude -p ${MCU} -c arduino -P /dev/ttyACM0 -b 115200
            -D -U flash:w:firmware.hex:i
    DEPENDS firmware
    COMMENT "Flashing firmware"
)

add_custom_target(size
    COMMAND avr-size firmware
)
