#include "os_port.h"
#include "hal/board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef HOST_SIM

typedef struct task_node {
  void (*fn)(void*);
  void* arg;
  const char* name;
  int prio;
  struct task_node* next;
} task_node_t;

static task_node_t* g_tasks = NULL;
static uint64_t t0_ms = 0;

static uint64_t now_ms(){
  struct timespec ts; clock_gettime(CLOCK_MONOTONIC, &ts);
  return (uint64_t)ts.tv_sec*1000 + ts.tv_nsec/1000000;
}

void os_init(void){
  t0_ms = now_ms();
}

void os_start_scheduler(void){
  // Cooperative round-robin simulation
  while(1){
    for(task_node_t* t = g_tasks; t; t = t->next){
      t->fn(t->arg);
    }
  }
}

void os_task_create(void (*fn)(void*), const char* name, void* arg, int prio){
  task_node_t* n = (task_node_t*)calloc(1, sizeof(task_node_t));
  n->fn = fn; n->arg = arg; n->name=name; n->prio=prio;
  n->next = g_tasks; g_tasks = n;
}

void os_delay_ms(uint32_t ms){
  board_delay_ms((int)ms);
}

uint32_t os_millis(void){
  return (uint32_t)(now_ms() - t0_ms);
}

#else
// TODO: Map to FreeRTOS primitives on target
void os_init(void){}
void os_start_scheduler(void){}
void os_task_create(void (*fn)(void*), const char* name, void* arg, int prio){ (void)fn;(void)name;(void)arg;(void)prio; }
void os_delay_ms(uint32_t ms){ (void)ms; }
uint32_t os_millis(void){ return 0; }
#endif
