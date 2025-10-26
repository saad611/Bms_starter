#pragma once
#include <stdint.h>

void  soc_init(float soc0);
void  soc_update(float i_a, float dt_s, float pack_t_c);
float soc_get(void);
