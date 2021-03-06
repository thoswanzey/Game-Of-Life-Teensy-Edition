cmake_minimum_required(VERSION 3.18.4)

# Set compiler path, include toolchain parameters
set(BAREMETAL_ARM_TOOLCHAIN_PATH /usr/bin)
set(CMAKE_TOOLCHAIN_FILE toolchain.cmake)

project(teensyistic LANGUAGES C CXX ASM)

# Common directories
set(SRC_FILES "${CMAKE_SOURCE_DIR}/src")
set(BUILD_FILES "${CMAKE_SOURCE_DIR}/build")
set(TEENSY_DRIVER_DIR "${CMAKE_SOURCE_DIR}/driver/teensy4")

# Specify our source files
file(GLOB_RECURSE ${CMAKE_PROJECT_NAME}_src
  "${SRC_FILES}/*.cpp"
  "${SRC_FILES}/*.c"
  "${SRC_FILES}/*.S"
  "${TEENSY_DRIVER_DIR}/*.cpp"
  "${TEENSY_DRIVER_DIR}/*.c"
)

include_directories(
    "${TEENSY_DRIVER_DIR}"
    "${SRC_FILES}"
    "${SRC_FILES}/lib/TeensyThreads"
)

# Clean up the hex file we created
set_property(DIRECTORY PROPERTY ADDITIONAL_CLEAN_FILES
  "${BUILD_DIR}/${CMAKE_PROJECT_NAME}.hex"
)

# Compile the elf
add_executable(${CMAKE_PROJECT_NAME}.elf ${${CMAKE_PROJECT_NAME}_src})

# Print executable size
add_custom_command(TARGET ${CMAKE_PROJECT_NAME}.elf
  POST_BUILD
  COMMAND ${CMAKE_SIZE} ARGS ${CMAKE_PROJECT_NAME}.elf
)

# Create the hex file
add_custom_command(TARGET ${CMAKE_PROJECT_NAME}.elf
  POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} ARGS -O ihex -R .eeprom -R .fuse -R .lock -R .signature ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.hex
)

# Upload the hex file to the teensy
add_custom_command(TARGET ${CMAKE_PROJECT_NAME}.elf
  POST_BUILD
  COMMAND ${CMAKE_SOURCE_DIR}/tools/teensy_loader_cli ARGS --mcu=${MCU} -v -w ${CMAKE_PROJECT_NAME}.hex
)
