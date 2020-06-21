#!/usr/bin/env perl
use strict;
use warnings;

my %twps=(
	# TWPS1, TWPS0
	1  => [0,0],
	4  => [0,1],
	16 => [1,0],
	64 => [1,1],
);

my $f_cpu=16000000;
my $prescaler=1;

printf("TWSR = (%d<<TWPS1)|(%d<<TWPS0); // prescaler: %d\n",@{$twps{$prescaler}},$prescaler);
foreach my $twbr(0..255) {
	my $f_scl=$f_cpu/((2*$twbr*$prescaler)+16);

	# 小数点を含まない周波数
	next unless(int($f_scl) == $f_scl);

	printf("TWBR=0x%02x; // F_SCL: %.2f kHz\n",$twbr,$f_scl/1000);
}

