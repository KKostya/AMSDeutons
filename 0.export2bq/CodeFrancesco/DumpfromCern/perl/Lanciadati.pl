#/usr/bin/perl
use warnings;
chomp (@rootuple = `ls ../lsfdati|grep tcsh`);


$num_rootuple = scalar(@rootuple);

print $num_rootuple."\n";


for($j=0;$j<$num_rootuple;$j++){

open(OUT,">","/afs/cern.ch/work/f/fdimicco/private/Dimiccoli/Compiled/Lanciadati/LanciaDati$j.tcsh");

print OUT "#!/bin/tcsh

setenv WORKDIR /afs/cern.ch/work/f/fdimicco/private/Dimiccoli/Compiled/

chmod +x \$WORKDIR/lsfdati/lsfDati$j.tcsh

bsub -q 1nd -o \$WORKDIR/lsfdati/lsfDati$j.out \$WORKDIR/lsfdati/lsfDati$j.tcsh >>\$WORKDIR/lsfdati/lsfDati$j.log\n";

close (OUT);
}
