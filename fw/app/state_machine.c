#include "state_machine.h"
#include "fw/cfg/pack_cfg.h"
#include "diag.h"

static bms_mode_t mode = ST_IDLE;
extern bms_state_t g_bms;

void sm_update(void){
  diag_run();
  if(g_bms.faults) { mode = ST_FAULT; return; }
  // naive mode inference
  if (g_bms.pack_i > 0.5f) mode = ST_DIS;
  else if (g_bms.pack_i < -0.5f) mode = ST_CHG;
  else mode = ST_IDLE;
}

bms_mode_t sm_get(void){ return mode; }
