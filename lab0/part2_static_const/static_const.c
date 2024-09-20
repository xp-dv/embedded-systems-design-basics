//* Lab 0 - C Programming Refresher | Part 2 - Using the Static and Const Keywords

#include "static_const.h"
#include <stdio.h>
#include <stdbool.h>

static int local_score = 0; // Cannot be seen by main.c

static bool check_score(void) { // Cannot be seen by main.c
  const int POINTS_TO_WIN = 3; // Declared as const to prevent value changes and optimize implementation by compiler
  if (local_score >= POINTS_TO_WIN) {
    return true;
  }
  else {
    return false;
  }
}

int increment_score(void) { // Public function declared in static_const.h and defined in static_const.c
  if (check_score()) {
    printf("Winner!\n");
  }
  else {
    local_score++;
  }

  return local_score;
}
