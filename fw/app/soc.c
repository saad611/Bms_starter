#include "soc.h"
#include "fw/cfg/pack_cfg.h"

static float g_soc = 0.5f;
static float q_ah  = 0.0f;

static float clampf(float x, float a, float b){ return x<a?a:(x>b?b:x); }

void soc_init(float soc0){
  g_soc = clampf(soc0, 0.0f, 1.0f);
  q_ah = (1.0f - g_soc) * PACK_CAP_AH;
}

static float ocv_lookup_to_soc(float ocv_v, float temp_c){
  (void)temp_c;
  // toy LUT: 3.3V -> 0.0, 3.7V -> 0.5, 4.2V -> 1.0
  if(ocv_v <= 3.3f) return 0.0f;
  if(ocv_v >= 4.2f) return 1.0f;
  return (ocv_v - 3.3f) / (4.2f - 3.3f);
}

void soc_update(float i_a, float dt_s, float temp_c){
  q_ah += (i_a * dt_s) / 3600.0f; // discharge positive current
  float soc_cc  = clampf(1.0f - q_ah / PACK_CAP_AH, 0.0f, 1.0f);
  float ocv     = 3.7f + 0.1f*(soc_cc-0.5f); // toy OCV
  float soc_ocv = ocv_lookup_to_soc(ocv, temp_c);
  const float alpha = 0.98f;
  g_soc = alpha*soc_cc + (1.0f-alpha)*soc_ocv;
}

float soc_get(void){ return g_soc; }
