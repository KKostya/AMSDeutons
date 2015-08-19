#!/bin/bash -x
if [ "$#" -lt 2 ]; then
    echo usage: ./jobElectronSample.sh jobName jobNumber
    exit
fi

# Make sure sourcing does not change your path
curPATH=`pwd`
source $HOME/.bashrc
cd $curPATH

jobName=$1
jobNumber=$2

UUID=$(cat /proc/sys/kernel/random/uuid) # Generate a unique folder name

mkdir $UUID
cd $UUID

#mount eos

echo reading eosdir
/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select -b fuse mount ${eosRoot}

cp ${executable} main
ls -lrt

for inputFile in ${ROOTUPLES[@]}; do
    filename=`basename "$inputFile"`
    filenameNoExt="${filename%.*}"
    cp $inputFile . 
    ./main $filename -b -o ntupleData_"${filenameNoExt}".root
    rm -f $filename
done
cp -R *.root ${eosRoot}/ams/user/${initial}/${USER}/NTupleData/${jobName}


