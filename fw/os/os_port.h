#pragma once
#include <stdint.h>

// Minimal OS abstraction so you can swap FreeRTOS later.
void os_init(void);
void os_start_scheduler(void);
void os_task_create(void (*fn)(void*), const char* name, void* arg, int prio);
void os_delay_ms(uint32_t ms);
uint32_t os_millis(void);
