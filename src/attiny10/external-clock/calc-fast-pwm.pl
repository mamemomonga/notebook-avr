#!/usr/bin/env perl
use strict;
use warnings;

sub usage {
	print "USAGE: $0 fosc(MHz) prescale\n";
	print "prescale: 1, 8, 64, 256, 1024\n";
	exit(1);
}

usage() if(!$ARGV[0] || ($ARGV[0] eq ''));
usage() if(!$ARGV[1] || ($ARGV[1] eq ''));

my %psk=(
	'1'    => [0,0,1],
	'8'    => [0,1,0],
	'64'   => [0,1,1],
	'256'  => [1,0,0],
	'1024' => [1,0,1],
);

usage() unless($psk{$ARGV[1]});
my $prescale = $ARGV[1];
my $fclkio = $ARGV[0] * 1000 * 1000;
my $ps=$psk{$prescale};

printf("TCCR0B |= (%d<<CS02)|(%d<<CS01)|(%d<<CS00); // clkio/%d\n",$ps->[0],$ps->[1],$ps->[2],$prescale);

foreach my $ocr0a (0..255) {
	my $fpwm = $fclkio / ($prescale * ($ocr0a+1));
#	next unless($ocr0a % 2 == 0);
#	next if(int($fpwm) != $fpwm);
	my $ocr0b = $ocr0a / 2;
	next if($ocr0b <= 0);
    printf("OCR0A=0x%02x; OCR0B=0x%02x; // %d Hz\n",$ocr0a,$ocr0b,$fpwm);
}

