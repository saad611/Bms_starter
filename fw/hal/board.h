#pragma once

// Pin mappings, clocks, peripherals.
// Fill in for target (STM32F4xx). For HOST_SIM these are no-ops.

void board_init(void);
void board_delay_ms(int ms);

#ifdef HOST_SIM
  #include <time.h>
  #include <stdio.h>
  static inline void board_init(void) {}
  static inline void board_delay_ms(int ms){
    struct timespec ts = { ms/1000, (ms%1000)*1000000L };
    nanosleep(&ts, 0);
  }
#endif
