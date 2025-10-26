#include "diag.h"
#include <float.h>

extern bms_state_t g_bms;

float min_cell_v(void){
  float m = FLT_MAX;
  for(int i=0;i<MAX_CELLS;i++) if(g_bms.cell_v[i] < m) m = g_bms.cell_v[i];
  return m;
}
float max_cell_v(void){
  float m = -FLT_MAX;
  for(int i=0;i<MAX_CELLS;i++) if(g_bms.cell_v[i] > m) m = g_bms.cell_v[i];
  return m;
}
float max_temp_c(void){
  float m = -FLT_MAX;
  for(int i=0;i<MAX_CELLS;i++) if(g_bms.cell_t[i] > m) m = g_bms.cell_t[i];
  return m;
}

void diag_run(void){
  g_bms.faults = 0;
  if (min_cell_v() < UV_LIMIT) g_bms.faults |= FLT_UV;
  if (max_cell_v() > OV_LIMIT) g_bms.faults |= FLT_OV;
  if (max_temp_c() > OT_LIMIT) g_bms.faults |= FLT_OT;
  // TODO: UT, open-wire detection
}
