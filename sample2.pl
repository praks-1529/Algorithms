#!/usr/bin/perl
use strict;
my $N = 50000;
my $K = 50000;
print "$N $K\n";
while($N--) {
  my $c = &generate_number(1000000);
  print "$c\n";
}

while($K--) {
  my $f = &generate_number(50000);
  my $t = &generate_number(50000);
  if($f > $t) {
    print "$t $f\n"
  } else {
    if($f == $t) {
      $t++;
    }
    print "$f $t\n"
  }
}

sub generate_number {
  my($range) = $_[0];
  my $random_num = rand($range);
  my $random_int = sprintf("%d", $random_num);
  if($random_int == 0) {
    $random_int = &generate_number($range);
  } else {
    return $random_int;
  }
}
