/* Fermat theorm: 
 * Let MODV = 7
 * Multiply: 
 * (22*2)%MODV = (22%MODV)*(1%MODV) = 2*1 = 2
 *
 * Division:
 * (22/2)%MODV = ?
 *
 * We find multiplicative inverse of 2, which is 2^(MODV-2) and change division to multiplication
 * Hence  it transforms (22/2) => 22*2^(MODV-2) => 22*2^5 => 22*32 => 704%MODV = 4
 *
 */
#define MAX_FACT 1000000
typedef unsigned long long ull;
static ull fact[MAX_FACT+1], invfact[MAX_FACT+1];
#define swap(x, y) (x ^= y, y ^= x, x ^= y)
ull
power(ull a, ull b)
{
  if(b==0)
    return 1;
  else if(b==1)
    return a;
  else if(b%2==0)
    return power((a*a)%MOD_VAL,b/2);
  else
    return (power((a*a)%MOD_VAL,b/2)*a)%MOD_VAL;
}

ull inverse(ull x){
  return power(x, MOD_VAL-2);
}
 
void init(){
  fact[0] = invfact[0] = 1;
  for(ull i=1; i<=MAX_FACT; i++) {
    fact[i]= i*fact[i-1]%MOD_VAL;
  }
  invfact[MAX_FACT]=inverse(fact[MAX_FACT]);
  for(ull i=MAX_FACT; i>0; i--) {
    invfact[i-1]=i*invfact[i]%MOD_VAL;
  }
}

ull
nCr(ull n, ull r) {
  return (((fact[n]*invfact[(n-r)])%MOD_VAL)*invfact[r])%MOD_VAL;
}

ull
nPr(ull n, ull r) {
  return (fact[n]*invfact[(n-r)])%MOD_VAL;
}

ull
nPrsa(ull n, ull m) {
  return (((fact[n+m]*invfact[n])%MOD_VAL)*invfact[m])%MOD_VAL;
}
void
print_binary(unsigned int n) {
  int k=16;
  while(k!=0)
  {
    if((n & 0x01) != 0)
      printf("1");
    else
      printf("0");
    k--;
    n >>= 1;
  }
  pn();
}

