#/usr/bin/perl
#

use warnings;
chomp (@rootuple = `more ../../perl/eosISS.B800pass5.txt`);


$num_rootuple = scalar(@rootuple);

print $num_rootuple."\n";

$n=0;#$num_rootuple/2;
$m=0;
for($j=0;$j<$num_rootuple/6;$j++)
{
$m=$n+3*$j;
open(OUT,">","/afs/cern.ch/work/f/fdimicco/private/Dimiccoli/Compiled/lsfdati/lsfDati$j.tcsh");

print OUT "#!/bin/tcsh

setenv WORKDIR /afs/cern.ch/work/f/fdimicco/private/Dimiccoli/Compiled
setenv WORKSPACE Risultati/ams/user/f/fdimicco
source \$WORKDIR/amsvar.sh

\$WORKDIR/exe/maindatatree $j >> \$WORKDIR/logs/$rootuple[$m].log\n
scp -o ProxyCommand=\"ssh fdimicco\@bastion.cnaf.infn.it nc %h %p\" \$WORKDIR/\$WORKSPACE/istogrammidati/$rootuple[$m]  fdimicco\@ui02-ams:/home/AMS/fdimicco/fdimicco/MAIN/istogrammidati/

scp -o ProxyCommand=\"ssh fdimicco\@bastion.cnaf.infn.it nc %h %p\" \$WORKDIR/logs/$rootuple[$m].log  fdimicco\@ui02-ams:/home/AMS/fdimicco/fdimicco/MAIN/istogrammidati/

mv \$WORKDIR/\$WORKSPACE/istogrammidati/$rootuple[$m] \$WORKDIR/\$WORKSPACE/istogrammidati_Completi/
mv \$WORKDIR/logs/$rootuple[$m].log \$WORKDIR/logcompleti;
";

close (OUT);

}


