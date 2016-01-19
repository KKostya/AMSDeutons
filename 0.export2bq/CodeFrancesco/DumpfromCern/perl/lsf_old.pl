#/usr/bin/perl
##


use warnings;

for($j=0;$j<2000;$j++)
{
open(OUT,">","/afs/cern.ch/work/f/fdimicco/private/Dimiccoli/Compiled/lsf/lsfMC$j.tcsh");

print OUT "#!/bin/tcsh

setenv WORKDIR /afs/cern.ch/work/f/fdimicco/private/Dimiccoli/Compiled
setenv WORKSPACE Risultati/ams/user/f/fdimicco
source \$WORKDIR/amsvar.sh

\$WORKDIR/exe/mainMCtree $j >> \$WORKDIR/logsMC/$j.log\n
scp -o ProxyCommand=\"ssh fdimicco\@bastion.cnaf.infn.it nc %h %p\" \$WORKDIR/istogrammiMC/$j.root  fdimicco\@ui02-ams:/home/AMS/fdimicco/fdimicco/MAIN/istogrammiMC/

scp -o ProxyCommand=\"ssh fdimicco\@bastion.cnaf.infn.it nc %h %p\" \$WORKDIR/logsMC/$j.log  fdimicco\@ui02-ams:/home/AMS/fdimicco/fdimicco/MAIN/istogrammiMC/

rm \$WORKDIR/istogrammiMC/$j.root; 
mv \$WORKDIR/logsMC/$j.log \$WORKDIR/logcompletiMC;


";

close (OUT);

}


