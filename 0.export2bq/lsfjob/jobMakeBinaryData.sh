#!/bin/bash -x
if [ "$#" -lt 1 ]; then
    echo usage: ./jobMakeBinaryData.sh jobName
    exit
fi

smearing=""
timingOffset=""
if [ "$#" -gt 1 ]; then
    smearing=" -s $2 "
fi

if [ "$#" -gt 2 ]; then
    timingOffset=" -z $3 "
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

if (( "${toGoogleCloudStorage:=0}" > 0 )); then
    outputFormat=" -m zip "
fi

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

echo "rootuple vanilla :  ${ROOTUPLES[@]}"
echo "${ROOTUPLES[@]}" >> ${homeDir}/jobStarted.txt

#change the eos mounting point

name=$(basename $(echo ${ROOTUPLES[@]} | awk '{print $1}'))

filesNewMountingPoint=()
for inputFile in ${ROOTUPLES[@]}; do
    #change the eos mounting point
    filesNewMountingPoint+=" $(echo $inputFile | awk -F'eos/' '{printf("'${eosRoot}/'%s",$2)}')"
done


./main -o "${name%.*}".output -f "${filesNewMountingPoint[@]}" ${smearing} ${timingOffset} ${outputFormat}

copyResult=1

if (( "${toGoogleCloudStorage}" > 0 )); then
    copyResult=0

    pushd .
    source /afs/cern.ch/user/k/kostams/public/VirtualEnv/env.sh
    popd
    for zippedFile in "${name%.*}".output/*.gz; do
        gsutil cp ${zippedFile} gs://ams-datasets/fat.ISSB950
        if (( "$?" != 0 )); then
          echo "gsutil failed. Copying the files to EOS instead"  
          copyResult=1
        else
            echo "${ROOTUPLES[@]}" >> ${homeDir}/successGoogleCloudExport.txt
        fi
    done
fi

if (( "${copyResult}" > 0 )); then
    echo "output copy started at : $(date)"
    cp -R *.output/ ${eosRoot}/ams/user/${initial}/${USER}/binaryAmsData/${jobName}
    echo "output copy done at : $(date)"
    echo "${ROOTUPLES[@]}" >> ${homeDir}/successEOSCopy.txt
fi

rm -rf *.output/
echo "output rm done at : $(date)"

#echo "${${homeDir}
/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select -b fuse umount eos 

# for inputFile in ${ROOTUPLES[@]}; do
#     #change the eos mounting point
#     fileNameNewMountingPoint=`echo $inputFile | awk -F'eos/' '{printf("'${eosRoot}/'%s",$2)}'`
#     echo $fileNameNewMountingPoint
#     theLocalFile=`basename "$inputFile"`
#     echo "input copy started at : $(date)"
#     cp ${fileNameNewMountingPoint} .
#     echo "copy done at : $(date)"
#     ./main -o "${theLocalFile%.*}".output -f ${theLocalFile} ${smearing} ${timingOffset}
#     rm -f ${theLocalFile}
#     echo "output copy started at : $(date)"
#     cp -R *.output/ ${eosRoot}/ams/user/${initial}/${USER}/binaryAmsData/${jobName}
#     echo "output copy done at : $(date)"
#     rm -rf *.output/
#     echo "output rm done at : $(date)"
# done
