#/usr/bin/perl

chomp (@rootuple1 = `more ../../perl/eosMC.B800pass5_P.txt`);
chomp (@rootuple2 = `more ../../perl/eosMC.B800pass5_D1.txt`);
chomp (@rootuple3 = `more ../../perl/eosMC.B800pass5_D2.txt`);
chomp (@rootuple4 = `more ../../perl/eosMC.B800pass5_D3.txt`);
chomp (@rootuple5 = `more ../../perl/eosMC.B800pass5_D4.txt`);
chomp (@rootuple6 = `more ../../perl/eosMC.B800pass5_D5.txt`);
chomp (@rootuple7 = `more ../../perl/eosMC.B800pass5_D6.txt`);
chomp (@rootuple8 = `more ../../perl/eosMC.B800pass5_He.txt`);

$num_rootuple1 = scalar(@rootuple1);
$num_rootuple2 = scalar(@rootuple2);
$num_rootuple3 = scalar(@rootuple3);
$num_rootuple4 = scalar(@rootuple4);
$num_rootuple5 = scalar(@rootuple5);
$num_rootuple6 = scalar(@rootuple6);
$num_rootuple7 = scalar(@rootuple7);
$num_rootuple8 = scalar(@rootuple8);


print "ntuple Protoni ".$num_rootuple1."\n";
print "ntuple Deutoni1 ".$num_rootuple2."\n";
print "ntuple Deutoni2 ".$num_rootuple3."\n";
print "ntuple Deutoni3 ".$num_rootuple4."\n";
print "ntuple Deutoni4 ".$num_rootuple5."\n";
print "ntuple Deutoni5 ".$num_rootuple6."\n";
print "ntuple Deutoni6 ".$num_rootuple7."\n";
print "ntuple Elio ".$num_rootuple8."\n";


$num_rootpletot=$num_rootuple1+$num_rootuple2+$num_rootuple3+$num_rootuple4+$num_rootuple5+$num_rootuple6+$num_rootuple7+$num_rootuple8;

##d.pl1.0_520_GG_Blic
##d.pl1.0_520_GG_BlicDPMJet
##d.pl1.0_520_GG_QMD
##d.pl1.0_520_Shen_Blic
##d.pl1.0_520_Shen_BlicDPMJet
#d.pl1.0_520_Shen_QMD

 open(OUT,">","/afs/cern.ch/user/f/fdimicco/Work/Dimiccoli/Compiled/scripsMC/inputs.h");
    print OUT "int numroottot=".$num_rootpletot.";\n";

    print OUT "std::string tipo2=\"d.B1030\";\n";
      print OUT "std::string energia2=\"d.pl1.0_520_GG_Blic\";\n";
        print OUT "int numroot2=".$num_rootuple2.";\n";
	print OUT "std::string rootpla2[]={\n";
          for ($j=0 ; $j<$num_rootuple2 ; $j++){
                print OUT  "\"$rootuple2[$j]\",\n";
                        }
                          print OUT "};";
    
	print OUT "std::string tipo3=\"d.B1030\";\n";
      print OUT "std::string energia3=\"d.pl1.0_520_GG_BlicDPMJet\";\n";
        print OUT "int numroot3=".$num_rootuple3.";\n";
	print OUT "std::string rootpla3[]={\n";
          for ($j=0 ; $j<$num_rootuple3 ; $j++){
                print OUT  "\"$rootuple3[$j]\",\n";
                        }
                          print OUT "};";
    print OUT "std::string tipo4=\"d.B1030\";\n";
      print OUT "std::string energia4=\"d.pl1.0_520_GG_QMD\";\n";
        print OUT "int numroot4=".$num_rootuple4.";\n";
	print OUT "std::string rootpla4[]={\n";
          for ($j=0 ; $j<$num_rootuple4 ; $j++){
                print OUT  "\"$rootuple4[$j]\",\n";
                        }
                          print OUT "};";
    
   print OUT "std::string tipo5=\"d.B1030\";\n";
      print OUT "std::string energia5=\"d.pl1.0_520_Shen_Blic\";\n";
         print OUT "int numroot5=".$num_rootuple5.";\n";
	print OUT "std::string rootpla5[]={\n";
          for ($j=0 ; $j<$num_rootuple5 ; $j++){
                print OUT  "\"$rootuple5[$j]\",\n";
                        }
                          print OUT "};";
    
   print OUT "std::string tipo6=\"d.B1030\";\n";
      print OUT "std::string energia6=\"d.pl1.0_520_Shen_BlicDPMJet\";\n";
        print OUT "int numroot6=".$num_rootuple6.";\n";
	print OUT "std::string rootpla6[]={\n";
          for ($j=0 ; $j<$num_rootuple6 ; $j++){
                print OUT  "\"$rootuple6[$j]\",\n";
                        }
                          print OUT "};";
    
    print OUT "std::string tipo7=\"d.B1030\";\n";
      print OUT "std::string energia7=\"d.pl1.0_520_Shen_QMD\";\n";
        print OUT "int numroot7=".$num_rootuple7.";\n";
	print OUT "std::string rootpla7[]={\n";
          for ($j=0 ; $j<$num_rootuple7 ; $j++){
                print OUT  "\"$rootuple7[$j]\",\n";
                        }
			 print OUT "};";
	
       print OUT "std::string tipo1=\"protons.B800\";\n";
      print OUT "std::string energia1=\"pr.pl1.0_5200\";\n";
        print OUT "int numroot1=".$num_rootuple1.";\n";
        print OUT "std::string rootpla1[]={\n";
          for ($j=0 ; $j<$num_rootuple1 ; $j++){
                print OUT  "\"$rootuple1[$j]\",\n";
                        }
                          print OUT "};";

	print OUT "std::string tipo8=\"he.B800\";\n";
      print OUT "std::string energia8=\"he.pl1.1400\";\n";
        print OUT "int numroot8=".$num_rootuple8.";\n";
        print OUT "std::string rootpla8[]={\n";
          for ($j=0 ; $j<$num_rootuple8 ; $j++){
                print OUT  "\"$rootuple8[$j]\",\n";
                        }
                         print OUT "};";                     
