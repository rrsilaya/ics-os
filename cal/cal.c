#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "cal.h"

int main() {
  for (int i = 1; i <= 12; i++) {
    cal(i, 2017);
    printf("\n");
  }
  return 0;
}