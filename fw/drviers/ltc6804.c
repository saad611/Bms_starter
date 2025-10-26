#include "ltc6804.h"
#include <string.h>

#ifdef HOST_SIM
  #include <math.h>
  static float sim_t = 0.0f;
#endif

bool ltc6804_init(void){
  return true;
}

bool ltc6804_read_volt(float *out_v, size_t n){
#ifdef HOST_SIM
  sim_t += 0.01f;
  for(size_t i=0;i<n;i++){
    float ripple = 0.03f * sinf(sim_t + (float)i*0.1f);
    out_v[i] = 3.9f + ripple; // simulate around 3.9V
  }
  return true;
#else
  // TODO: SPI transactions, PEC checks
  (void)out_v; (void)n;
  return false;
#endif
}

bool ltc6804_read_temp(float *out_c, size_t n){
#ifdef HOST_SIM
  for(size_t i=0;i<n;i++) out_c[i] = 28.0f + (i%3)*1.0f;
  return true;
#else
  (void)out_c; (void)n;
  return false;
#endif
}
