#!/usr/bin/perl
use strict;
use warnings;

my @fcpu=(qw(
	8
	9.6
	7.3728
	10
	11.0592
	14.7456
	16
	20
	));
my @bauds=(qw(
	9600
	38400
	115200
	31250
));

foreach my $fcpu(@fcpu) {
	my $fosc=$fcpu *1000 *1000;
	printf("## FCPU: %d (%f MHz)\n",$fosc,$fcpu);
	print "\n";
	print " Baudrate | U2Xn, UBBR | ERROR \n";
	print "----------|------------|-------\n";

	foreach my $baud(@bauds) {
		foreach my $u2xn (0,1) {
			my $u = getUBBR($fosc, $baud, $u2xn);
			next if $u->{error} >= 0.5;
			# printf("BAUD: %8d \t U2Xn: %d UBBR: 0x%04x \t ERROR: %f %%\n", $baud, $u2xn, $u->{ubbr}, $u->{error});
			printf("%8d | U2Xn: %d UBBR: 0x%04x | ERROR: %f %%\n", $baud, $u2xn, $u->{ubbr}, $u->{error});
		}
	}
	print "\n";
}

sub getUBBR {
	my ($fosc,$baud,$u2xn)=@_;
	my $dbl=$u2xn ? 8 : 16;
	my $ubbr=int(($fosc/($dbl*$baud))-1);
	my @rates;
	foreach($ubbr-1,$ubbr,$ubbr+1) {
		push @rates,[$_,abs($fosc/($dbl*($_+1))-$baud)];
	}
	@rates=sort { $a->[1] > $b->[1] } @rates;
	$ubbr=$rates[0][0];

	my $rbaud=$fosc/($dbl*($ubbr+1));
	my $error=0;
	if($baud < $rbaud) {
		$error=100-($baud/$rbaud)*100;

	} elsif($baud > $rbaud) {
		$error=100-($rbaud/$baud)*100;
	}
	return { ubbr => $ubbr, baud => $baud, error => $error };
}

