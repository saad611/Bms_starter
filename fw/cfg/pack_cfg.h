#pragma once
#include <stdint.h>

#define MAX_CELLS       96
#define CELLS_PER_IC    12
#define N_IC            (MAX_CELLS / CELLS_PER_IC)

#define PACK_CAP_AH     80.0f

// Limits (Volts / °C)
#define UV_LIMIT        2.80f
#define OV_LIMIT        4.20f
#define OT_LIMIT        60.0f
#define UT_LIMIT        -20.0f

// Balancing target (V)
#define BAL_TARGET_V    4.10f

typedef struct {
  float cell_v[MAX_CELLS];
  float cell_t[MAX_CELLS];
  float pack_i;    // A
  float pack_v;    // V
  float soc;       // 0..1
  float soh;       // 0..1
  uint32_t faults; // bitfield
} bms_state_t;

enum {
  FLT_NONE = 0,
  FLT_UV   = 1<<0,
  FLT_OV   = 1<<1,
  FLT_OT   = 1<<2,
  FLT_UT   = 1<<3,
  FLT_OPEN = 1<<4,
};

extern bms_state_t g_bms;
