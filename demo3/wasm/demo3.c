int add(int a, int b) {
  return a+b;
}

int is_neg(int a) {
  return a<0;
}

int abs(int a) {
  if (is_neg(a)) {
    return -a;
  } else {
    return a;
  }
}

int unused() {
  return 0;
}
