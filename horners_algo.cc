
template<typename T> T 
horners_algo(vector<T> &co_eff, T x) {
  //* co_eff[0] represents MSB and co_eff[size-1] represents LSB */
  T ans=0;
  if(co_eff.size() == 0) {
    ans = 0;
  } else if(co_eff.size() == 1) {
    ans = co_eff[0];
  } else {
    ans = co_eff[0]*x + co_eff[1];
    for(int i=2; i<co_eff.size(); i++) {
      ans = (ans)*x + co_eff[i];
    }
  }
  return ans;
}

