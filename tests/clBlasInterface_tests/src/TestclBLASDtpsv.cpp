#include <iostream>
#include "HPL_clBLAS.h"

#define N 5

int check(bool is_ok)
{
  if(is_ok) {
    std::cout << "Test is PASSED. \n";
    return 0;
  } else {
    std::cout << "Test is FAILED. \n";
    return -1;
  }
}

bool tol(double a, double b)
{
    return abs(a - b) < 0.0001;
}

int test1()
{
  HPL::Array<double, 1> A((N*N+N)/2);
  HPL::Array<double, 1> x(N);

  for(int i = 0; i < (N*N+N)/2; i++) {
    A(i) = i + 1;
  }

  for(int i = 0; i < N; i++) {
     x(i) = 1 << i + 1;
  }

  HPL_clblasSetup();

  try { clblasDtpsv(clblasUpper, A, x); } catch (HPL::HPLException& e) { std::cout << e.what();  if(e.getErrCode() == -33) std::cout << "The test device probably does not support double precision\n"; }

  HPL_clblasTeardown();

  return check((tol(x(0), -1.78667f)) && (tol(x(1),  -0.42667f)) && (tol(x(2),  -0.58667f)) &&
               (tol(x(3),  -1.06667f)) && (tol(x(4), 2.13333f)));
}

int test2()
{
  HPL::Array<double, 1> A((N * N + N) / 2);
  HPL::Array<double, 1> x(N);

  for(int i = 0; i < (N*N+N)/2; i++) {
    A(i) = i + 1;
  }

  for(int i = 0; i < N; i++) {
     x(i) = 1 << i + 1;
  }

  HPL_clblasSetup();

  try { clblasDtpsv(clblasLower, A, x); } catch (HPL::HPLException& e) { std::cout << e.what();  if(e.getErrCode() == -33) std::cout << "The test device probably does not support double precision\n"; }

  HPL_clblasTeardown();

  return check(tol(x(0), 2.f) && tol(x(1), 0.f) && tol(x(2),  0.f) && tol(x(3), 0.2f) && tol(x(4), 0.48f));
}

int main()
{
    test1();
    test2();
}
