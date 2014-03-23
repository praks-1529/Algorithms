double 
round_to_2_dec(double &dist) {
  unsigned long long x = (dist * 1000);
  if((x%10) >= 5) {
    dist = 0.01 * ceil(100 * dist);
  } else {
    dist = 0.01 * floor(100 * dist);
  }
  printf("%.2lf\n", dist);
  return dist;
}
