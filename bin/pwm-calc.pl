#!/usr/bin/env perl
use strict;
use warnings;

sub usage {
	print "USAGE: $0 fosc(MHz) prescale\n";
	exit(1);
}

usage() if(!$ARGV[0] || ($ARGV[0] eq ''));
usage() if(!$ARGV[1] || ($ARGV[1] eq ''));

my $fosc = $ARGV[0] * 1000 * 1000;
my $prescale = $ARGV[1];

foreach my $ocrb (1..255) {
  if($fosc % ($prescale * $ocrb) == 0) {
    printf("OCRBx: 0x%02x, Interval Freq: %d Hz\n",$ocrb, ($fosc / $ocrb / $prescale));
  }
}

