#include <stdlib.h>

int factorial(int n) {
  int result = 1;
  for (int i = 1; i <= n; i++) {
    result *= i;
  }
  return result;
}

int invalid_access() {
  int *a = malloc(10*sizeof(int));
  a[10] = 100; // Invalid access, but can not be detected
  a = 0;
  *a = 1; // invalid access, can be detected
  return 0;
}

int memory_leak() {
  int *a = malloc(10*sizeof(int));
  return 0; // memory leak, can not be detected
}
