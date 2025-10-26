#pragma once
typedef enum { ST_IDLE, ST_CHG, ST_DIS, ST_FAULT } bms_mode_t;
void sm_update(void);
bms_mode_t sm_get(void);
