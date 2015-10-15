#!/bin/bash
if [ "$#" -lt 1 ]; then
    echo usage: ./submitMakeBinaryData.sh jobName
    exit
fi

jobName=$1
chunkSize=20
MAXJOB=1000
queue=1nd
export eosRoot=${HOME}/eos
export executable=../bin/dst
export initial="$(echo ${USER} | head -c 1)"

files=("${eosRoot}/ams/Data/AMS02/2014/ISS.B950/pass6"/*)
#files=("${eosRoot}/ams/MC/AMS02/2014/protons.B1034/pr.pl1.1200.qgsp_bic_ams"/*)

if [[ ! -f "$executable" ]]; then
    echo Executable: ${executable} not found !
    echo Exit !
    exit
fi

if [[ -d "$jobName" ]]; then
    echo folder: $jobName exists !
    echo Please, choose another job name
    echo Exit !
    exit
fi

mkdir $jobName
cp ${executable} $jobName/`basename ${executable}`
executable=`pwd`/$jobName/`basename ${executable}`

/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select -b fuse mount $eosRoot
if [[ ! -d "${eosRoot}/ams/user/${initial}/${USER}/binaryAmsData" ]]; then
    mkdir ${eosRoot}/ams/user/${initial}/${USER}/binaryAmsData
fi

if [[ ! -d "${eosRoot}/ams/user/${initial}/${USER}/binaryAmsData" ]]; then
    echo folder: ${eosRoot}/ams/user/${initial}/${USER}/binaryAmsData does not exist or is not accessible !
    echo Exit !
    exit
fi

if [[ -d "${eosRoot}/ams/user/${initial}/${USER}/binaryAmsData/$jobName" ]]; then
    echo folder: ${eosRoot}/ams/user/${initial}/${USER}/binaryAmsData/$jobName exists or is not accessible !
    echo Please, choose another job name
    echo Exit !
    exit
fi
mkdir ${eosRoot}/ams/user/${initial}/${USER}/binaryAmsData/$jobName

if [[ ! -f "jobMakeBinaryData.sh" ]]; then
    echo Job file: jobMakeBinaryData.sh does not exist !
    echo Exit !
    exit
fi

cat << END > $jobName/env.sh
export eosRoot=$eosRoot
export executable=$executable
END

for ((i=0; i < ${#files[@]}; i+=chunkSize)); do
    export ROOTUPLES="${files[@]:i:chunkSize}"
    j=$((i/chunkSize))
    if (( j >= MAXJOB )); then
	break
    fi    

    bsubCommand="bsub -J ${jobName}_${j} -q ${queue} $(pwd)/jobMakeBinaryData.sh ${jobName} ${j}"
    $bsubCommand
    echo ${ROOTUPLES}>>${jobName}/inputFileList.log
done

