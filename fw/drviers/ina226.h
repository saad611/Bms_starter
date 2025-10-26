#pragma once
#include <stdbool.h>

bool ina226_init(void);
bool ina226_read(float *i_a, float *v_v);
