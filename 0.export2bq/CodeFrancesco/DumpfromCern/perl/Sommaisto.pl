#/usr/bin/perl


#use warnings;
chomp (@rootuple = `ls -l ../istogrammidati | grep -v " 63 "| grep -v " 0 " |awk '{print \$9}'`);

$num_rootuple = scalar(@rootuple);

print $num_rootuple."\n";

 open(OUT,">","/afs/cern.ch/work/f/fdimicco/private/Dimiccoli/Compiled/Sommaisto.sh");
  print OUT  "#!/bin/tcsh

hadd -f ./sommadati1.root ";

for ($j=1 ; $j<($num_rootuple) ; $j++)
{
		
	print OUT  " ./istogrammidati/$rootuple[$j] "
}
print OUT "\n";


print $num_rootuple."\n";

