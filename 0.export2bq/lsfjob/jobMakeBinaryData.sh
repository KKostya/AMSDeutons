#!/bin/bash -x
if [ "$#" -lt 2 ]; then
    echo usage: ./jobMakeBinaryData.sh jobName jobNumber
    exit
fi

smearing=""
if [ "$#" -gt 2 ]; then
    smearing=" -s $3"
fi

klist

homeDir=$(dirname ${executable})

# Make sure sourcing does not change your path
pushd .
source $HOME/.bashrc
popd
source ${homeDir}/env.sh

jobName=$1
jobNumber=$2

mkdir eos
eosRoot=`pwd`/eos
echo "making local eos mounting point ..."
/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select -b fuse mount ${eosRoot}
cp ${executable} main

for lib in ${libs[@]}
do
    cp ${homeDir}/$(basename ${lib}) .
done


LD_LIBRARY_PATH=.:${LD_LIBRARY_PATH}
ls -lrt

for inputFile in ${ROOTUPLES[@]}; do
    #change the eos mounting point
    fileNameNewMountingPoint=`echo $inputFile | awk -F'eos/' '{printf("'${eosRoot}/'%s",$2)}'`
    echo $fileNameNewMountingPoint
    theLocalFile=`basename "$inputFile"`
    cp ${fileNameNewMountingPoint} .
    ./main -o "${theLocalFile%.*}".output -f ${theLocalFile} ${smearing}
    rm -f ${theLocalFile}
    # cd *.output/
    # for binaryFile in *.bin; do
    #     bzip2 ${binaryFile}
    # done
    # cd ..
    cp -R *.output/ ${eosRoot}/ams/user/${initial}/${USER}/binaryAmsData/${jobName}
    rm -rf *.output/
done

/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select -b fuse umount eos 

