#!/bin/bash
if [ "$#" -lt 1 ]; then
    echo usage: ./submitMakeBinaryData.sh jobName
    exit
fi

export jobName=$1

# chunkSize=40000000000 # 40GB of data per job
# MAXJOB=1
# queue=8nm

chunkSize=40000000000 # 40GB of data per job
MAXJOB=1000
queue=2nd

export eosRoot=${HOME}/eos
export executable=../bin/dst
export initial="$(echo ${USER} | head -c 1)"
export queue
#files=("${eosRoot}/ams/Data/AMS02/2014/ISS.B950/pass6"/*.root)
files=("${eosRoot}/ams/MC/AMS02/2014/protons.B1033/pr.pl1.10200.qgsp_bic_ams"/*.root)

if [ "$#" -gt 1 ]; then
    echo "New file dir provided : $2" 
    files=("$2"/*.root)
fi

gitStatus=$(git status --porcelain ../dst.cpp ../dst.hpp ../../utils/include/DstAmsBinary.hpp ../../utils/src/DstAmsBinary.cpp ../../utils/include/Loop.hpp ../../utils/src/Loop.cpp ../selections/* ../3DVariables.hpp)
if [ "$gitStatus" != "" ]; then
    echo "These files need to be committed before launching the jobs:"
    echo "${gitStatus}"
    exit
fi

export libs=(../../utils/lib/libRootUtils.so  ../../utils/lib/libGeneralUtils.so ../../utils/lib/libDstAmsBinary.so)


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

for lib in ${libs[@]}
do
    if [[ ! -f "$lib" ]]; then
        echo "lib : ${lib} not found !"
        exit
    fi
    cp ${lib} `pwd`/$jobName/
done

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

cp jobMakeBinaryData.sh ${jobName}

cat << END > $jobName/env.sh
export eosRoot=$eosRoot
export executable=$executable
$(declare -p libs)
END

function splitBySize(){
    if [ "$#" -lt 2 ]; then
        echo usage: ./splitBySize.sh chunkSize listOfFiles
        exit
    fi

    chunkSize=$1

    listOfFiles=("$@")
    listOfFiles=("${listOfFiles[@]:1}")

    size=0
    out=()
    for f in "${listOfFiles[@]}"
    do
        out+=($f)
        ((size+=$(stat   --printf="%s" $f)))
        if (( "${size}" >   "${chunkSize}" )); then
            echo ${out[@]}
            out=()
            size=0
        fi
    done

    if (( "${#out[@]}" != 0 ));then
        echo ${out[@]}
    fi
}

function launchJob(){
    export ROOTUPLES="$@"
    bsubCommand="bsub -q ${queue} k5reauth -R -- $(pwd)/${jobName}/jobMakeBinaryData.sh ${jobName}"
    eval $bsubCommand
    #$(pwd)/${jobName}/jobMakeBinaryData.sh ${jobName}
    echo ${ROOTUPLES}>>${jobName}/inputFileList.log
}
export -f launchJob

splitBySize ${chunkSize} ${files[@]} | head -n ${MAXJOB} | xargs -L 1 -I{} bash -i -c "launchJob {}"


