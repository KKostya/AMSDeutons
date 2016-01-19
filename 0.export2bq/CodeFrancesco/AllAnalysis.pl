#usr/bin/perl


#use warnings;

#system("rm /home/AMS/fdimicco/fdimicco/fdimicco/Risultati/risultati/*");
#$percorso="/home/francesco/PhD/LocalCNAF/";
$percorso="/storage/gpfs_ams/ams/users/fdimicco/";
system("cp  $percorso/Risultati/*/*tot*  $percorso/Risultati/risultati");

chomp (@Rootuple = `ls  $percorso/Risultati/risultati/|grep tot  |  sed s/_tot_P1.root//g`);
$num_Rootuple = scalar(@Rootuple);
open(OUT,">","./Mesi.h");
print $num_Rootuple."\n";

print OUT "int num_mesi = $num_Rootuple;\n";
print OUT "std::string mesi[]{\n";
for($i=0;$i<$num_Rootuple;$i++) {
	print OUT "\"$Rootuple[$i]\",\n";
}
print OUT "};\n";

for($i=0;$i<$num_Rootuple;$i++) {
print "Analyzing ".$Rootuple[$i]."...\n";
system("./Analisi $Rootuple[$i] 2 tot")
}
                










           
