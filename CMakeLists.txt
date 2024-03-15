cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)
project(macropad C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CPP_STANDARD 11)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR ARM)

set(FAMILY rp2040)
set(BOARD pico_sdk)
set(TINYUSB_FAMILY_PROJECT_NAME_PREFIX "tinyusb_host_")

add_compile_options(-Wall
                    -Wno-format
                    -Wno-unused-function
                    )


pico_sdk_init()

add_executable(macropad_hid)
target_sources(macropad_hid PUBLIC
        src/main.c
        src/usb_descriptors.c
)

target_include_directories(macropad_hid PUBLIC
        src
)

target_link_libraries(macropad_hid PUBLIC pico_stdlib pico_unique_id tinyusb_device tinyusb_board)

pico_add_extra_outputs(macropad_hid)