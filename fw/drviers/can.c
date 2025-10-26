#include "can.h"
#include <stdio.h>

void can_init(void){}

void can_tx_status(const bms_state_t* s){
#ifdef HOST_SIM
  printf("[CAN] SOC=%.1f%% V=%.1fV I=%.1fA minV=%.3f maxV=%.3f faults=0x%08X\n",
    s->soc*100.0f, s->pack_v, s->pack_i,
    99.0f, 101.0f, s->faults);
#else
  // TODO: Pack DBC and send via CAN
  (void)s;
#endif
}
