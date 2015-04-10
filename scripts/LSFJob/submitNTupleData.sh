#!/bin/bash
if [ "$#" -lt 1 ]; then
    echo usage: ./submitNTupleData.sh jobName
    exit
fi

jobName=$1
chunkSize=1
MAXJOB=4000
queue=1nd
export isEosFolder=1
export eosRoot=${HOME}/eos
export initial=`echo $HOME | awk -F'/' '{print $5}'`
export executable=../../ntupleData
files=("${HOME}/eos/ams/Data/AMS02/2014/ISS.B950/pass6"/*)

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

if [[ ${isEosFolder} == "1" ]]; then
    /afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select -b fuse mount $eosRoot

    if [[ ! -d "${eosRoot}/ams/user/${initial}/${USER}/NTupleData" ]]; then
        echo folder: ${eosRoot}/ams/user/${initial}/${USER}/NTupleData does not exist or is not accessible !
        echo Exit !
        exit
    fi

    if [[ -d "${eosRoot}/ams/user/${initial}/${USER}/NTupleData/$jobName" ]]; then
        echo folder: ${eosRoot}/ams/user/${initial}/${USER}/NTupleData/$jobName exists or is not accessible !
        echo Please, choose another job name
        echo Exit !
        exit
    fi
    mkdir ${eosRoot}/ams/user/${initial}/${USER}/NTupleData//$jobName
fi

if [[ ! -f "jobNTupleData.sh" ]]; then
    echo "Job file: jobNTupleData.sh does not exist !"
    echo Exit !
    exit
fi

cat << END > $jobName/env.sh
export isWorkFolder=$isWorkFolder
export isEosFolder=$isEosFolder
export eosRoot=$eosRoot
export executable=$executable
END

for ((i=0; i < ${#files[@]}; i+=chunkSize)); do
    export ROOTUPLES="${files[@]:i:chunkSize}"
    j=$((i/chunkSize))
    if (( j >= MAXJOB )); then
	break
    fi    

    bsubCommand="bsub -J ${jobName}_${j} -q ${queue} jobNTupleData.sh ${jobName} ${j}"
    $bsubCommand
    echo "${bsubCommand}, return code: ">>${jobName}/jobList.log
    echo ${ROOTUPLES}>>${jobName}/inputFileList.log

    if [ "$j" -gt 0 ]; then
    	wrapUpCondition="$wrapUpCondition &&"
    fi
    wrapUpCondition="$wrapUpCondition ended(${jobName}_$j)"
done

echo $wrapUpCondition
bsub -o ${jobName}/wrapup.out -q $queue -w "$wrapUpCondition" rerunBadJobs.sh ${jobName}

