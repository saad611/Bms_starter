#pragma once
#include <stdint.h>
#include <stdbool.h>

bool eeprom_init(void);
bool eeprom_write(uint32_t addr, const void* data, uint32_t len);
bool eeprom_read (uint32_t addr, void* data, uint32_t len);
