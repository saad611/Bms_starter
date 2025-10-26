#pragma once
#include "fw/cfg/pack_cfg.h"

void can_init(void);
void can_tx_status(const bms_state_t* s);
