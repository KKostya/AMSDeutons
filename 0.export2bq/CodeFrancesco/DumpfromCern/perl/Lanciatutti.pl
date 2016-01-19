#/usr/bin/perl
##
use warnings;
open(OUT,">","/afs/cern.ch/work/f/fdimicco/private/Dimiccoli/Compiled/Lanciadati/Lanciatutti.sh");
for($j=1000;$j<7000;$j++){
print OUT "tcsh LanciaDati$j.tcsh\n"
}

