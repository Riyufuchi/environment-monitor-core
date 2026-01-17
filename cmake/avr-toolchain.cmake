set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)

set(AVR_MCU atmega328p)
set(F_CPU 16000000UL)

set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)
set(CMAKE_ASM_COMPILER avr-gcc)

set(CMAKE_OBJCOPY avr-objcopy)
set(CMAKE_SIZE avr-size)

set(CMAKE_C_FLAGS "-mmcu=${AVR_MCU} -DF_CPU=${F_CPU} -Os")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics")

set(CMAKE_EXE_LINKER_FLAGS "-mmcu=${AVR_MCU}")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
