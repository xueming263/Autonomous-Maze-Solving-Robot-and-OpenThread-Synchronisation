cmake_minimum_required(VERSION 3.13)
if (DEFINED ENV{PICO_SDK_PATH})
  include("$ENV{PICO_SDK_PATH}/pico_sdk_init.cmake")
else ()
  include("../pico-sdk/pico_sdk_init.cmake")
endif()
project(project C CXX ASM)
add_compile_options(-Wall -Wextra)

pico_sdk_init()

add_subdirectory(../pololu_3pi_2040_robot pololu_3pi_2040_robot)

# add executable target files
add_executable(maze-project
    main.c
    turn.c
    sensors.c
    multi_display.c
    follow_segment.c
    maze_solve.c
    path.c
    uart_rx.c
    leds.c
)

# add the path of headers used in project
target_include_directories(maze-project PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)

# the PICO SDK libraries
target_link_libraries(maze-project
    pololu_3pi_2040_robot
    pico_stdlib
    hardware_pwm
    hardware_adc
    hardware_i2c
    hardware_spi
    hardware_pio
)

# Enable USB and UART debug interfaces
pico_enable_stdio_usb(maze-project 1)
pico_enable_stdio_uart(maze-project 1)

# Added generation of additional executable 
# file formats (such as .uf2 files)
pico_add_extra_outputs(maze-project)