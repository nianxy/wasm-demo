#include <string.h>
#include <stdlib.h>

// 返回一个新的字符串，需要通过free释放
const char* string_duplicate(const char* str, int duplicate_times) {
  int len = strlen(str);
  char* result = malloc(len*2 + 1);
  char* pr = result;
  for (int i = 0; i < duplicate_times; ++i) {
    memcpy(pr, str, len);
    pr += len;
  }
  *pr = '\0';
  return result;
}

double plus100(double a) {
  return a + 100;
}

float plus100f(float a) {
  return a + 100;
}

/**
 * format: 0: RGBA
 */
void rgb_to_gray(unsigned char* data, int width, int height, int format) {
  if (format==0) {
    for (int i = 0; i < width * height; ++i) {
      int base = i * 4;
      unsigned char c = (unsigned char) (data[base + 0] * 0.299 + data[base + 1] * 0.587 + data[base + 2] * 0.114);
      data[base + 0] = c;
      data[base + 1] = c;
      data[base + 2] = c;
    }
  }
}
