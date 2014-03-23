#!/usr/bin/perl
use strict;
my $T = 1;
#print "$T\n";
while($T--) {
  my $N = 50000;
  my $K = 50000;
  print "$N $K\n";
  while($K--) {
    my $c = &generate_number(3);
    my $i = &generate_number($N);
    my $j = &generate_number($N);
    if($c==1) {
      print "S $i";
    } elsif($c == 2) {
      print "Q $i $j";
    }
    print "\n";
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
