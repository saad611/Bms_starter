#include "balance.h"
#include <stdbool.h>
#include <stdio.h>

static void drv_bal_set(size_t idx, bool on){
#ifdef HOST_SIM
  printf("  [BAL] cell%02u -> %s\n", (unsigned)idx, on? "ON":"OFF");
#else
  (void)idx; (void)on; // TODO: GPIO to MOSFET driver
#endif
}

void balance_apply(const float *cv, size_t n, float target){
  const float TH = 0.01f; // 10 mV hysteresis
  for (size_t i=0;i<n;i++) {
    bool on = (cv[i] > target + TH);
    drv_bal_set(i, on);
  }
}
