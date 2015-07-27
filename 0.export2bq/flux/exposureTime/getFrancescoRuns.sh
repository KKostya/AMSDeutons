#!/bin/bash
dir=/afs/cern.ch/user/b/bcoste/eos/ams/Data/AMS02/2011B/ISS.B620/pass4/

francescoFiles=(`cat francescoRunList.txt  | grep -v log`)
nFrancescoFiles=${#francescoFiles[@]}
echo $nFrancescoFiles
                                 
amsFiles=(`cat amsFilesB620Pass4.txt`)

iFrancescoFile=0
iAMSFile=0

rm -f francescoRunAtCern.txt
while (( iFrancescoFile < nFrancescoFiles )); do
#while (( iFrancescoFile < 1 )); do
    echo ${francescoFiles[iFrancescoFile]}
    
    while (( 1 )); do
        if [[ "${amsFiles[${iAMSFile}]}" == *"${francescoFiles[${iFrancescoFile}]}" ]]; then
            echo ${amsFiles[$iAMSFile]} >> francescoRunAtCern.txt
            ((iAMSFile++))
            echo ${amsFiles[$iAMSFile]} >> francescoRunAtCern.txt
            ((iAMSFile++))
            echo ${amsFiles[$iAMSFile]} >> francescoRunAtCern.txt
            break
        fi

        ((iAMSFile++))
    done
    ((iFrancescoFile++))
done

