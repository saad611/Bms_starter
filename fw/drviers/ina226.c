#include "ina226.h"
#ifdef HOST_SIM
  #include <math.h>
#endif

bool ina226_init(void){ return true; }

bool ina226_read(float *i_a, float *v_v){
#ifdef HOST_SIM
  static float t=0; t+=0.02f;
  if(i_a) *i_a = 5.0f + 1.0f*(0.5f + 0.5f*sin(t));
  if(v_v) *v_v = 370.0f + 5.0f*(0.5f + 0.5f*sin(0.7f*t));
  return true;
#else
  (void)i_a; (void)v_v; return false;
#endif
}
