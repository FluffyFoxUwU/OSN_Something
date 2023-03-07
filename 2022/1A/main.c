#if 0
clang -fsanitize=undefined -fsanitize=address -static-libsan  -O2 -Wall main.c 
exec ./a.out
#endif

//This code will be POSIX 2008 compliant
#define _POSIX_C_SOURCE 200809L
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

static uint64_t landCount = 0;
static uint64_t planCount = 0;

struct plan_entry {
  uint64_t planSize;
  uint64_t statisfiedCount;
};

static inline uint64_t calc_land_size(uint64_t landID) {
  return (landID & 1LL) ? (landID >> 1LL) + 1LL : landCount + 1LL - (landID >> 1LL);
}

int main() {
  if (scanf("%" SCNu64 " %" SCNu64 "", &landCount, &planCount) != 2)
    abort();
  
  // printf("Land count: %d\n", landCount);
  // printf("Plan count: %d\n", planCount);
  
  // for (uint64_t i = 1; i <= landCount; i++)
  //   printf("|%d", calc_land_size(i));
  // printf("|\n");
  
  struct plan_entry* plans = malloc(sizeof(*plans) * planCount);
  if (!plans)
   abort();
  
  uint64_t maxLength = 0;
  for (uint64_t i = 0; i < planCount; i++) {
    plans[i] = (struct plan_entry) {};
    scanf("%" SCNu64, &plans[i].planSize);
    
    if (plans[i].planSize > maxLength)
      maxLength = plans[i].planSize;
  }
  
  for (uint64_t i = 1; i <= landCount; i++) {
    uint64_t length = 0;
    for (uint64_t landID = i; length <= maxLength && landID <= landCount; landID++) {
      length += calc_land_size(landID);
      if (length > maxLength)
        break;
      
      for (uint64_t i = 0; i < planCount; i++) {
        if (plans[i].planSize == length) {
          plans[i].statisfiedCount++;
        }
      }
    }
  }
  
  for (uint64_t i = 0; i < planCount; i++) {
    //printf("Hello: plans[%d] = {%d, %d}\n", i, plans[i].planSize, plans[i].statisfiedCount);
    printf("%" PRIu64 "\n", plans[i].statisfiedCount);
  }
  
  free(plans);
}







