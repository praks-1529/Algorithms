/* GENERATE Nth fibonacci number. The method1 and method2 are O(N), where as method3 is O(logn) since it optimizes on number of multiplications needed to get M^n */
#include<iostream>
using namespace std;

int 
matr_mult(int F[2][2], int M[2][2]) {
   int m00 = F[0][0]*M[0][0] + F[0][1]*M[1][0]; 
   int m01 = F[0][0]*M[0][1] + F[0][1]*M[1][1]; 
   int m10 = F[1][0]*M[0][0] + F[1][1]*M[1][0]; 
   int m11 = F[1][0]*M[0][1] + F[1][1]*M[1][1]; 
   F[0][0] = m00;
   F[0][1] = m01;
   F[1][0] = m10;
   F[1][1] = m11;
}

void 
power(int F[2][2], int n) {
  int M[2][2] = { {1,1}, {1, 0} }; 
  while(n--) {
    matr_mult(F, M);
  }
}

void 
power_opt(int F[2][2], int n) {
  int M[2][2] = { {1,1}, {1, 0} }; 
  if(n==1 || n==0) {
    return;
  } else {
    power_opt(F, n/2);
    matr_mult(F, F);
    if(n%2) {
      matr_mult(F, M);
    }
  }
}

int method2(int n) {
  if(n==1 || n == 2 || n == 3) {
    if(n==1) {
      return 0;
    } else if(n==2) {
      return 1;
    } else {
      return 1;
    }
  } else {
    n -= 3;
    int F[2][2] = { {1,1}, {1, 0} }; 
    power(F, n);
    return F[0][0];
  }
}

int method3(int n) {
  if(n==1 || n == 2 || n == 3) {
    if(n==1) {
      return 0;
    } else if(n==2) {
      return 1;
    } else {
      return 1;
    }
  } else {
    n -= 2;
    int F[2][2] = { {1,1}, {1, 0} }; 
    power_opt(F, n);
    return F[0][0];
  }
}

int method1(int n) {
  int a, b, c;
  a = 0; 
  b = 1;
  if(n==1 || n == 2) {
    if(n==1) {
      return 0;
    } else {
      return 1;
    }
  } else {
    int orig_n = n;
    n -= 2;
    while(n--) {
      c = a+b;
      a = b;
      b = c;
    }
    return c;
  }
}

int main() {
  int n; cin >> n;
  cout << method1(n) << ":" << method2(n) << ":" << method3(n);
}
