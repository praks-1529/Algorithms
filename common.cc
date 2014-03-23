#include <iostream>
using namespace std;

typedef int ull;
void
swap(ull &x, ull &y) {
  //x = x + y - ( y = x );
  x ^= y; y ^= x; x ^= y;
}

int
count_bits(ull i) {
   i = ((i & 0xAAAAAAAA) >>  1) + (i & 0x55555555);
   i = ((i & 0xCCCCCCCC) >>  2) + (i & 0x33333333);
   i = ((i & 0xF0F0F0F0) >>  4) + (i & 0x0F0F0F0F);
   i = ((i & 0xFF00FF00) >>  8) + (i & 0x00FF00FF);
   i = ((i & 0xFFFF0000) >> 16) + (i & 0x0000FFFF);
   return (int)i;
}

ull 
gcd(ull a, ull b) {
  if(!( a && b)) {
    if(!a) {
      return b;
    } else {
      return a;
    }
  }
  if(b > a) {
    /* Swap a and b */
    ull temp = a;
    a = b;
    b = temp;
  } 
  while(a%b) {
    ull temp = a%b;
    a = b;
    b = temp;
  }
  return b;
}

ull lcm(ull a, ull b) {
  return ((a*b)/gcd(a, b));
}

int main() {
  int i=10;
  int j = 15;
  cout << count_bits(i) << " " << count_bits(j) << endl;
  cout << i << " " << j << endl;
  swap(i, j);
  cout << i << " " << j << endl;
}
