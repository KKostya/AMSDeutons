#!/bin/bash
if [ "$#" -lt 1 ]; then
    echo usage: ./submitAcceptance-c++.sh jobName
    exit
fi

jobName=$1
chunkSize=10
MAXJOB=1000
queue=1nh
export isWorkFolder=1
export isEosFolder=0
export eosRoot=/afs/cern.ch/user/b/bcoste/eos
export executable=/afs/cern.ch/user/b/bcoste/deutons/3.acceptance/acceptance-c++/bin/acceptance
#files=("/afs/cern.ch/user/b/bcoste/eos/ams/MC/AMS02/2014/protons.B1034/pr.pl1.1200.qgsp_bic_ams"/*)
#files=("/afs/cern.ch/user/b/bcoste/eos/ams/MC/AMS02/2014/protons.B800/pr.pl1.0_5200/"/*)
files=("/afs/cern.ch/user/b/bcoste/eos/ams/MC/AMS02/2014/d.B1030/d.pl1.0_520_Shen_Blic"/*)
if [[ ! -f "$executable" ]]; then
    echo Executable: ${executable} not found !
    echo Exit !
    exit
fi

if [[ -d "/afs/cern.ch/user/b/bcoste/deutons/3.acceptance/acceptance-c++/lsf_job/$jobName" ]]; then
    echo folder: /afs/cern.ch/user/b/bcoste/deutons/3.acceptance/acceptance-c++/lsf_job/$jobName exists !
    echo Please, choose another job name
    echo Exit !
    exit
fi
mkdir /afs/cern.ch/user/b/bcoste/deutons/3.acceptance/acceptance-c++/lsf_job/$jobName

if [[ ${isWorkFolder} == "1" ]]; then
    if [[ ! -d "/afs/cern.ch/work/b/bcoste/acceptance-c++" ]]; then
        echo folder: /afs/cern.ch/work/b/bcoste/acceptance-c++ does not exist !
        echo Exit !
    fi

    if [[ -d "/afs/cern.ch/work/b/bcoste/acceptance-c++/$jobName" ]]; then
        echo folder: /afs/cern.ch/work/b/bcoste/acceptance-c++/$jobName exists !
        echo Please, choose another job name
        echo Exit !
        exit
    fi
    mkdir /afs/cern.ch/work/b/bcoste/acceptance-c++/$jobName
fi

if [[ ! -f "/afs/cern.ch/user/b/bcoste/deutons/3.acceptance/acceptance-c++/lsf_job/jobAcceptance-c++.sh" ]]; then
    echo Job file: /afs/cern.ch/user/b/bcoste/deutons/3.acceptance/acceptance-c++/lsf_job/jobAcceptance-c++.sh does not exist !
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

    bsubCommand="bsub -J ${jobName}_${j} -q ${queue} /afs/cern.ch/user/b/bcoste/deutons/3.acceptance/acceptance-c++/lsf_job/jobAcceptance-c++.sh ${jobName} ${j}"
    $bsubCommand
    #/afs/cern.ch/user/b/bcoste/deutons/3.acceptance/acceptance-c++/lsf_job/jobAcceptance-c++.sh ${jobName} ${j}
    echo "${bsubCommand}, return code: ">>/afs/cern.ch/user/b/bcoste/deutons/3.acceptance/acceptance-c++/lsf_job/${jobName}/jobList.log
    echo ${ROOTUPLES}>>/afs/cern.ch/user/b/bcoste/deutons/3.acceptance/acceptance-c++/lsf_job/${jobName}/inputFileList.log
done


