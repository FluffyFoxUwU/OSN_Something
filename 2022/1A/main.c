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

static int64_t landCount = 0;
static int64_t planCount = 0;

struct plan_entry {
  int64_t planSize;
  int64_t statisfiedCount;
};

int64_t calc_land_size(int64_t landID) {
  return (landID & 1) ? (landID >> 1) + 1 : landCount + 1 - (landID >> 1);
}

bool is_usable(int64_t startLand, int64_t size) {
  int64_t totalSize = 0;
  for (int64_t i = startLand; totalSize < size && i <= landCount; i++)
    totalSize += calc_land_size(i);
  return totalSize == size;
}

int main() {
  if (scanf("%" SCNi64 " %" SCNi64 "", &landCount, &planCount) != 2)
    abort();
  
  // printf("Land count: %d\n", landCount);
  // printf("Plan count: %d\n", planCount);
  
  // for (int64_t i = 1; i <= landCount; i++)
  //   printf("|%d", calc_land_size(i));
  // printf("|\n");
  
  struct plan_entry* plans = malloc(sizeof(*plans) * planCount);
  if (!plans)
    abort();
  
  for (int64_t i = 0; i < planCount; i++) {
    plans[i] = (struct plan_entry) {};
    scanf("%" SCNi64, &plans[i].planSize);
  }
  
  for (int64_t i = 1; i <= landCount; i++) {
    for (int64_t j = 0; j < planCount; j++) {
      struct plan_entry* entry = &plans[j];
      if (is_usable(i, entry->planSize))
        entry->statisfiedCount++;
    }
  }
  
  for (int64_t i = 0; i < planCount; i++) {
    //printf("Hello: plans[%d] = {%d, %d}\n", i, plans[i].planSize, plans[i].statisfiedCount);
    printf("%" PRIi64 "\n", plans[i].statisfiedCount);
  }
  free(plans);
}







