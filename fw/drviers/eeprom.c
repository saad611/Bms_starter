#include "eeprom.h"
#include <string.h>
#ifdef HOST_SIM
  #include <stdlib.h>
  static uint8_t mem[4096];
#endif

bool eeprom_init(void){ return true; }
bool eeprom_write(uint32_t addr, const void* data, uint32_t len){
#ifdef HOST_SIM
  if(addr+len>sizeof(mem)) return false;
  memcpy(&mem[addr], data, len); return true;
#else
  (void)addr;(void)data;(void)len; return false;
#endif
}
bool eeprom_read(uint32_t addr, void* data, uint32_t len){
#ifdef HOST_SIM
  if(addr+len>sizeof(mem)) return false;
  memcpy(data, &mem[addr], len); return true;
#else
  (void)addr;(void)data;(void)len; return false;
#endif
}
