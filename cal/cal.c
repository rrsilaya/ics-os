#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cal.h"

int main() {
  // for (int i = 1; i <= 12; i++) {
  //   printf("[Month %i]\n", i);
  //   cal(i, 2017);
  //   printf("\n");
  // }
  cal(12, 2019);
  cal(1, 2020);
  cal(2, 2020);
  return 0;
}