#include <stdio.h>
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;
typedef unsigned long long ull;

void
prime_gen(ull limit, vector<ull> &result) {
  /* THIS METHOD USES SIEVE OF ATKINs ALGO */
  /* Flag to indicate whether prime or not */
  bool *flag = new bool[limit+1];
  memset(flag, 0, (limit+1)*sizeof(bool));
  result.clear();
  result.push_back(2); 
  result.push_back(3); 
  ull root = ceil(sqrt(limit));
  ull n;
  for(ull x=0; x <=root; x++) {
    for(ull y=0; y<=root; y++) {
      n = 4*x*x + y*y;
      if((n <= limit) && (( n%12 == 1) || (n%12 == 5))) {
        // Flip the flag. The reason for flipping is, we are basically interseted in 
        // finding if 4x^2 + y^2 = n has odd number of solutions. So if after flipping
        // the flag[n] "k" times, if flag[n] is true, that means k(i.e no of soln) is odd 
        // else it is even
        flag[n] ^= true;
      }
      n = 3*x*x + y*y;
      if((n <= limit) && (n%12 == 7)) {
        flag[n] ^= true;
      }
      if(x > y) {
        n = 3*x*x - y*y;
        if((n <= limit) && (n%12 == 11)) {
          flag[n] ^= true;
        }
      }
    }
  }
  // Eliminate all the composite by seiving
  for(ull n=5; n <= root; n++) {
    if(flag[n] == true) {
      // We found a prime
      ull square=n*n;
      int multiple_factor=1;
      while((multiple_factor*square) <= limit) {
        flag[(multiple_factor*square)] = false;
        multiple_factor++;
      }
    }
  }
  // Now all the numbers that are marked true are prime
  for(ull n=5; n<= limit; n++) {
    if(flag[n] == true) {
      result.push_back(n);
    }
  }
}

int main() {
  ull limit = 10e+8;
  vector<ull> result;
  prime_gen(limit, result);
  vector<ull>::iterator it;
  cout << result.size() << "prime numbers were found" << endl;
  //for(it=result.begin(); it!= result.end(); it++) {
    //cout << *it << endl;
  //}
}
