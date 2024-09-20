//* Lab 0 - C Programming Refresher | Part 2 - Using the Static and Const Keywords

// TASK: Demonstrate a proper use case for the static and const keywords
/**
 * ? Static and Const Information
 * Static global variables can only be accessed by functions within this file which guards against variable name conflicts and unintended value changes if the document is imported to another program
 * Variables that should not be changed (and there is the available space in memory for it) should be declared as const and should be named in SCREAMING_SNAKE_CASE to denote their constant nature,
 * otherwise, global constants and magic numbers can generally be defined by the preprocessor using #define
 * Const also better informs the compiler how it should treat the variable, allowing it to perform its own optimization on its implementation
 */

//? Programs, such as main.c and static_const.c, are separated so that all functions are implemented when compiled together, but not treated as one compilation unit
//? This is necessary for the static keyword to properly limit the scope of variables and functions defined in src.c

#include "static_const.h"
#include <stdio.h>

int main() {
  //! printf("Score: %d\n", local_score); // This will throw an undeclared error as local_score is static to static_const.c
  //! check_score(); // This will throw an implicit declaration of function error as check_score() is static to static_const.c
  //! printf("Local: %d\n", POINTS_TO_WIN); // This will throw an undeclared error as POINTS_TO_WIN is being referenced out of scope
  
  // These will all run properly because increment_score() is in the included static_const.h file and is defined in static_const.c which is compiled with main.c
  // Even though local_score is static to static_const.c, it can still be viewed and manipulated within the public function increment_score()
  printf("Score: %d\n", increment_score());
  printf("Score: %d\n", increment_score());
  printf("Score: %d\n", increment_score());
  printf("Score: %d\n", increment_score());
}
