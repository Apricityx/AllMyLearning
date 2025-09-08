int foo(const int n) {
  if (n == 1)
    return n;
  else
    return n * foo(n - 1);
}

int factorial(const int n) { return foo(n); }
