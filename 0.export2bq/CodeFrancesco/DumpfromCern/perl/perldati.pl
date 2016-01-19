#/usr/bin/perl


use warnings;
chomp (@rootuple = `more ../../perl/eosISS.B800pass5.txt`);


$num_rootuple = scalar(@rootuple);

print $num_rootuple."\n";

  open(OUT,">","/afs/cern.ch/user/f/fdimicco/Work/Dimiccoli/Compiled/scripsdati/inputs.h");

  print OUT "std::string tipo=\"ISS.B950\";\n";
  print OUT "std::string energia=\"pass6\";\n";
  print OUT "std::string rootpla[]={\n";
  for ($j=0; $j<($num_rootuple/2) ; $j++){
      print OUT  "\"$rootuple[$j]\",\n";
	}
  print OUT "};";	
