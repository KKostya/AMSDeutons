eosm
#for f in $(seq 382 438)
for f in 044 045 046 047 048 049 050 051 052 053 054 055 382 415 438
do
	FILES=$(ls $AFSHOME/eos/ams/MC/AMS02/2014/protons.B1042/pr.pl1.0510/93956${f}*.root | tr "\n" ",")
	~/AMSDeutons/0.export2bq/bin/dst -f $FILES -s -0.87 -z 10 -o pB1045.$f.out
done
