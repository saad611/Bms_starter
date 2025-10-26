#include <stdio.h>
#include <string.h>

#include "fw/cfg/pack_cfg.h"
#include "hal/board.h"
#include "os/os_port.h"
#include "drivers/ltc6804.h"
#include "drivers/ina226.h"
#include "drivers/eeprom.h"
#include "drivers/can.h"
#include "app/soc.h"
#include "app/balance.h"
#include "app/state_machine.h"

bms_state_t g_bms;

static void task_meas(void* arg){
  (void)arg;
  static uint32_t last=0;
  if(os_millis() - last < 10) return; last = os_millis();

  ltc6804_read_volt(g_bms.cell_v, MAX_CELLS);
  ltc6804_read_temp(g_bms.cell_t, MAX_CELLS);
  ina226_read(&g_bms.pack_i, &g_bms.pack_v);
}

static void task_soc(void* arg){
  (void)arg;
  static uint32_t last=0; uint32_t now=os_millis();
  float dt = (now-last)/1000.0f; if(dt < 0.02f) return; last=now;
  soc_update(g_bms.pack_i, dt, 30.0f);
  g_bms.soc = soc_get();
}

static void task_balance(void* arg){
  (void)arg;
  static uint32_t last=0;
  if(os_millis() - last < 100) return; last=os_millis();
  balance_apply(g_bms.cell_v, MAX_CELLS, BAL_TARGET_V);
}

static void task_diag(void* arg){
  (void)arg;
  static uint32_t last=0;
  if(os_millis() - last < 10) return; last=os_millis();
  sm_update();
}

static void task_can(void* arg){
  (void)arg;
  static uint32_t last=0;
  if(os_millis() - last < 100) return; last=os_millis();
  can_tx_status(&g_bms);
}

int main(void){
  board_init();
  os_init();

  memset(&g_bms, 0, sizeof(g_bms));
  ltc6804_init();
  ina226_init();
  eeprom_init();
  can_init();
  soc_init(0.8f);

  os_task_create(task_meas,    "meas",    0, 1);
  os_task_create(task_soc,     "soc",     0, 1);
  os_task_create(task_balance, "balance", 0, 1);
  os_task_create(task_diag,    "diag",    0, 1);
  os_task_create(task_can,     "can",     0, 1);

  printf("BMS host simulation starting...\n");
  os_start_scheduler();
  return 0;
}
