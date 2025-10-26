#pragma once
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "fw/cfg/pack_cfg.h"

bool ltc6804_init(void);
bool ltc6804_read_volt(float *out_v, size_t n_cells);
bool ltc6804_read_temp(float *out_c, size_t n_cells);
