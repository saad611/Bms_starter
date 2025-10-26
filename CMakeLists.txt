cmake_minimum_required(VERSION 3.15)
project(bms C)

option(HOST_SIM "Build for host simulation" OFF)

if(HOST_SIM)
  add_compile_definitions(HOST_SIM=1)
endif()

set(CMAKE_C_STANDARD 11)

add_executable(bms_host_sim
  fw/app/bms_main.c
  fw/app/state_machine.c
  fw/app/balance.c
  fw/app/soc.c
  fw/app/diag.c
  fw/drivers/ltc6804.c
  fw/drivers/ina226.c
  fw/drivers/can.c
  fw/drivers/eeprom.c
  fw/os/os_port.c
)

target_include_directories(bms_host_sim PRIVATE
  fw
  fw/app
  fw/drivers
  fw/os
  fw/hal
  fw/cfg
)
