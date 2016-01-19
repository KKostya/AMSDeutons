#/usr/bin/perl
##
#

for($j=0;$j<10000;$j++){
print $j."\n" ;

open(OUT,">","/afs/cern.ch/work/f/fdimicco/private/Dimiccoli/Compiled/Lancia/LanciaMC$j.tcsh");

print OUT "#!/bin/tcsh

setenv WORKDIR /afs/cern.ch/work/f/fdimicco/private/Dimiccoli/Compiled/

chmod +x \$WORKDIR/lsf/lsfMC$j.tcsh

bsub -q 1nd -o \$WORKDIR/lsf/lsfMC$j.out -e \$WORKDIR/err/lsfMC$j.err \$WORKDIR/lsf/lsfMC$j.tcsh >>\$WORKDIR/lsf/lsfMC$j.log\n";

close (OUT);
}

