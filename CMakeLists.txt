cmake_minimum_required(VERSION 3.20)

project(environment_monitor_core LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)

set(AVR_MCU atmega328p)
set(F_CPU 16000000UL)

set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)
set(CMAKE_ASM_COMPILER avr-g++)

set(CMAKE_OBJCOPY avr-objcopy)
set(CMAKE_SIZE avr-size)

set(CMAKE_C_FLAGS "-mmcu=${AVR_MCU} -DF_CPU=${F_CPU} -Os")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-sized-deallocation")

set(CMAKE_EXE_LINKER_FLAGS "-mmcu=${AVR_MCU} -fno-sized-deallocation")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

#

add_compile_definitions(
    __AVR__
    __AVR_ATmega328P__
)


include_directories(/usr/lib/avr/include)

set(MCU atmega328p)
set(F_CPU 16000000UL)

set(SRC_DIR environment_core_src)
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

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
target_compile_features(firmware PRIVATE cxx_std_20)

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

# Path to LaTeX source folder
set(LATEX_DIR ${CMAKE_CURRENT_SOURCE_DIR}/latex-doc)
set(MAIN_TEX environment_monitor_core.tex)
#set(OUTPUT_PDF ${CMAKE_CURRENT_BINARY_DIR}/nocovka.pdf)

# Custom target to build docs
add_custom_target(docs
	COMMAND ${CMAKE_COMMAND} -E chdir ${LATEX_DIR} lualatex ${MAIN_TEX}
	COMMAND ${CMAKE_COMMAND} -E chdir ${LATEX_DIR} makeglossaries environment_monitor_core
	COMMAND ${CMAKE_COMMAND} -E chdir ${LATEX_DIR} lualatex ${MAIN_TEX}
	COMMAND ${CMAKE_COMMAND} -E chdir ${LATEX_DIR} lualatex ${MAIN_TEX}
	COMMENT "Building PDF documentation with lualatex and makeglossaries"
)
