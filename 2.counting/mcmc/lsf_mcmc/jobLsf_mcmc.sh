#!/bin/bash -x
if [ "$#" -lt 2 ]; then
    echo usage: ./jobElectronSample.sh jobName jobNumber
    exit
fi

initial="$(echo ${USER} | head -c 1)"

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
echo making local eos mounting point ...
/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select -b fuse mount ${eosRoot}

mkdir datasets
mkdir tmp

filesToCopy=('initialConditions.txt' 'mask.csv' 'B_resolution.csv' 'R_resolution.csv')

for f in ${filesToCopy[@]}; do
    cp `dirname ${executable}`/../datasets/${f} datasets/
done

cd tmp
cp ${executable} main
cp ${reader} reader

./main -f mcmcJob_${jobName}_${jobNumber} -n 500000000
./reader mcmcJob_${jobName}_${jobNumber}

cp -R mcmcJob_* ${eosRoot}/ams/user/${initial}/${USER}/lsf_mcmc/${jobName}

#/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select -b fuse umount eos 


