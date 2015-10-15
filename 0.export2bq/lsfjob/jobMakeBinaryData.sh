#!/bin/bash -x
if [ "$#" -lt 2 ]; then
    echo usage: ./jobMakeBinaryData.sh jobName jobNumber
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
echo making local eos mounting point ...
/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select -b fuse mount ${eosRoot}
cp ${executable} main
ls -lrt

for inputFile in ${ROOTUPLES[@]}; do
    if [[ "${inputFile}" == *"/eos/"* ]]; then
        #change the eos mounting point
        fileNameNewMountingPoint=`echo $inputFile | awk -F'eos/' '{printf("'${eosRoot}/'%s",$2)}'`
        echo $fileNameNewMountingPoint
        theLocalFile=`basename "$inputFile"`
        cp ${fileNameNewMountingPoint} .
        ./main ${theLocalFile} "${theLocalFile%.*}".output
        rm -f ${theLocalFile}
    else
        ./main ${inputFile} "${inputFile%.*}".output
    fi
done


cp -R *.output* ${eosRoot}/ams/user/${initial}/${USER}/dstTofTiming/${jobName}


#sed -i 's/, return code.*$/, return code: '${code}'/' /afs/cern.ch/user/${initial}/${USER}/deutons/2.counting/mcmc/tofTimings/dst/dstTofTiming/${jobName}/jobList.log

/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select -b fuse umount eos 


