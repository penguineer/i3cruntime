#pragma once
#include <stdint.h>

// TODO somehow convert this into code following OO-patterns.

enum slave_priority {
  LOW = 0,
  MEDIUM = 1,
  HIGH = 2,
  REALTIME = 3
};

// struct slavelist {
// uint8_t &get_address;
//   
// }


struct slavelistitem {
  uint8_t address;
  uint64_t intcount;
  enum slave_priority priority;
  struct slavelistitem *previous;
  struct slavelistitem *next;
};

uint8_t get_address(struct slavelistitem item);
uint8_t init(struct slavelistitem *item, enum slave_priority priority, uint8_t address);
uint8_t get_priority(struct slavelistitem *item);
uint8_t insert(struct slavelistitem *newitem,struct slavelistitem *previous, struct slavelistitem *next);
