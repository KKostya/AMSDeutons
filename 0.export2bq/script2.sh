for f in /afs/cern.ch/user/k/kostams/eos/ams/Data/AMS02/2014/ISS.B800/pass5/13856*
do
    N=$(basename $f)
    N=${N%root}
    ./selTable -o /data/SelectionTable/${N}cvs $f
done

