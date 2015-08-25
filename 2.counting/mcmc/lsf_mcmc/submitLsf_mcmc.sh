#!/bin/bash
if [ "$#" -lt 1 ]; then
    echo usage: ./submitLsf_mcmc.sh jobName
    exit
fi

jobName=$1
chunkSize=20
MAXJOB=1
#queue=ams1nd
queue=8nm

initial="$(echo $USER | head -c 1)"

export isEosFolder=1
export eosRoot=/afs/cern.ch/user/${initial}/${USER}/eos
export executable=/afs/cern.ch/user/${initial}/${USER}/deutons/2.counting/mcmc/mcmc
export reader=`dirname ${executable}`/reader
if [[ ! -f "$executable" ]]; then
    echo Executable: ${executable} not found !
    echo Exit !
    exit
fi

if [[ ! -f "$reader" ]]; then
    echo Executable: ${reader} not found !
    echo Exit !
    exit
fi

if [[ -d "/afs/cern.ch/user/${initial}/${USER}/deutons/2.counting/mcmc/lsf_mcmc/$jobName" ]]; then
    echo folder: /afs/cern.ch/user/${initial}/${USER}/deutons/2.counting/mcmc/lsf_mcmc/$jobName exists !
    echo Please, choose another job name
    echo Exit !
    exit
fi
mkdir /afs/cern.ch/user/${initial}/${USER}/deutons/2.counting/mcmc/lsf_mcmc/$jobName


if [[ ${isEosFolder} == "1" ]]; then
    /afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select -b fuse mount $eosRoot

    if [[ ! -d "${eosRoot}/ams/user/${initial}/${USER}/lsf_mcmc" ]]; then
        echo folder: ${eosRoot}/ams/user/${initial}/${USER}/lsf_mcmc does not exist or is not accessible !
        echo Exit !
        exit
    fi

    if [[ -d "${eosRoot}/ams/user/${initial}/${USER}/lsf_mcmc/$jobName" ]]; then
        echo folder: ${eosRoot}/ams/user/${initial}/${USER}/lsf_mcmc/$jobName exists or is not accessible !
        echo Please, choose another job name
        echo Exit !
        exit
    fi
    mkdir ${eosRoot}/ams/user/${initial}/${USER}/lsf_mcmc/$jobName
fi

if [[ ! -f "/afs/cern.ch/user/${initial}/${USER}/deutons/2.counting/mcmc/lsf_mcmc/jobLsf_mcmc.sh" ]]; then
    echo Job file: /afs/cern.ch/user/${initial}/${USER}/deutons/2.counting/mcmc/lsf_mcmc/jobLsf_mcmc.sh does not exist !
    echo Exit !
    exit
fi

cat << END > $jobName/env.sh
export isWorkFolder=$isWorkFolder
export isEosFolder=$isEosFolder
export eosRoot=$eosRoot
export executable=$executable
END

for ((j=0; j < ${MAXJOB}; j+=1)); do

    bsubCommand="bsub -J ${jobName}_${j} -q ${queue} /afs/cern.ch/user/${initial}/${USER}/deutons/2.counting/mcmc/lsf_mcmc/jobLsf_mcmc.sh ${jobName} ${j}"
    $bsubCommand
    echo "${bsubCommand}, return code: ">>/afs/cern.ch/user/${initial}/${USER}/deutons/2.counting/mcmc/lsf_mcmc/${jobName}/jobList.log
    echo ${ROOTUPLES}>>/afs/cern.ch/user/${initial}/${USER}/deutons/2.counting/mcmc/lsf_mcmc/${jobName}/inputFileList.log
done

