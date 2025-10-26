# BMS Starter (Embedded C, FreeRTOS-ready)

Minimal, production-style scaffold for an EV Battery Management System (BMS). 
Includes RTOS task layout, drivers, configs, and host-sim stubs so you can build on PC first.

## Features
- Task skeletons: measurement, SOC, balancing, diagnostics, CAN, logger, watchdog
- Drivers: LTC6804 (SPI), INA226 (I²C), EEPROM/FRAM, CAN
- Configurable pack layout in `fw/cfg/pack_cfg.h`
- Host simulation mode (`HOST_SIM`) for unit testing without hardware
- CMake project for host builds

## Build (host simulation)
```bash
mkdir -p build && cd build
cmake -DHOST_SIM=ON ..
cmake --build . -j
./bms_host_sim
```

> For target builds (STM32F4), add your toolchain file and HAL sources in `fw/hal/` and update `CMakeLists.txt` accordingly.

## Directory Layout
```
bms-starter/
  fw/
    app/        # app logic (state machine, SOC, balancing, diagnostics)
    drivers/    # ltc6804, ina226, can, eeprom (stubs + interfaces)
    os/         # OS glue, FreeRTOSConfig, task wrappers
    hal/        # board pins, clock, BSP
    cfg/        # pack configuration and limits
    tests/      # host tests and vectors
  tools/        # PC-side utilities (CAN monitor, simulators)
  CMakeLists.txt
  README.md
  LICENSE
```
