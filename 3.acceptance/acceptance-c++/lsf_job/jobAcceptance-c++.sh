#!/bin/bash -x
if [ "$#" -lt 2 ]; then
    echo usage: ./jobElectronSample.sh jobName jobNumber
    exit
fi


k5reauth -R
klist

# Make sure sourcing does not change your path
curPATH=`pwd`
source $HOME/.bashrc
cd $curPATH

jobName=$1
jobNumber=$2

mkdir eos
eosRoot=`pwd`/eos
echo "making local eos mounting point ..."
/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select -b fuse mount ${eosRoot}

cp /afs/cern.ch/user/b/bcoste/utils/lib/libGeneralUtils.so /afs/cern.ch/user/b/bcoste/utils/lib/libRootUtils .
cp ${executable} main
ls -lrt

for inputFile in ${ROOTUPLES[@]}; do
    #change the eos mounting point
    fileNameNewMountingPoint=`echo $inputFile | awk -F'eos/' '{printf("'${eosRoot}/'%s",$2)}'`
    echo $fileNameNewMountingPoint
    theLocalFile=`basename "$inputFile"`
    cp ${fileNameNewMountingPoint} .
    ./main ${theLocalFile}
    mv ana_${theLocalFile} /afs/cern.ch/work/b/bcoste/acceptance-c++/$jobName/
    rm -f ${theLocalFile}
done



/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select -b fuse umount eos 


