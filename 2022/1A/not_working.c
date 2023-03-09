#if 0
clang -fsanitize=undefined -fsanitize=address -static-libsan -g -O2 -Wall main.c 
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

static inline int64_t calc_land_size(int64_t landID) {
  return (landID & 1LL) ? (landID >> 1LL) + 1LL : landCount + 1LL - (landID >> 1LL);
}

static int compare_by_size(const void* _a, const void* _b) {
  const struct plan_entry* const* a = _a;
  const struct plan_entry* const* b = _b;
  if ((*a)->planSize > (*b)->planSize)
    return 1;
  else if ((*a)->planSize < (*b)->planSize)
    return -1;
  return 0;
}

// In place deduplication
static size_t dedup_plans(struct plan_entry** plans, size_t count) {
  size_t newCount = count;
  struct plan_entry** writeHead = plans;
  struct plan_entry** readHead = plans;
  struct plan_entry** end = plans + count;
  while (readHead < end) {
    if (*readHead != *writeHead) {
      writeHead++;
      *writeHead = *readHead;
    }
    readHead++;
  }
  
  return newCount;
}

int main() {
  if (scanf("%" SCNi64 " %" SCNi64 "", &landCount, &planCount) != 2)
    abort();
  
  struct plan_entry* plans = malloc(sizeof(*plans) * planCount);
  struct plan_entry** planSortedBySize = malloc(sizeof(*planSortedBySize) * planCount);
  if (!plans || !planSortedBySize)
    abort();
  
  int64_t maxLength = 0;
  for (int64_t i = 0; i < planCount; i++) {
    plans[i] = (struct plan_entry) {};
    planSortedBySize[i] = &plans[i];
    scanf("%" SCNi64, &plans[i].planSize);
    
    if (plans[i].planSize > maxLength)
      maxLength = plans[i].planSize;
  }
  qsort(planSortedBySize, planCount, sizeof(*planSortedBySize), compare_by_size);
  size_t deduplicatedPlanCount = dedup_plans(planSortedBySize, planCount);
  
  struct plan_entry toSearch = {};
  const struct plan_entry* const toSearchPtr = &toSearch;
  for (int64_t i = 1; i <= landCount; i++) {
    toSearch.planSize = 0;
    for (int64_t currentLand = i; currentLand <= landCount && currentLand <= maxLength; currentLand++) {
      toSearch.planSize += calc_land_size(currentLand);
      struct plan_entry** result = bsearch(&toSearchPtr, planSortedBySize, deduplicatedPlanCount, sizeof(*planSortedBySize), compare_by_size);
      if (result)
        (*result)->statisfiedCount++;
    }
  }
  
  for (int64_t i = 0; i < planCount; i++) {
    printf("%" PRIi64 "\n", plans[i].statisfiedCount);
  }
  free(planSortedBySize);
  free(plans);
}







