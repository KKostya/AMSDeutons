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
source /afs/cern.ch/user/k/kostams/public/VirtualEnv/ipython/bin/activate
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/afs/cern.ch/user/k/kostams/public/VirtualEnv/install/lib
source ${homeDir}/env.sh
popd


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

#change the eos mounting point

echo "option in job: ${optional}"
for inputFile in ${ROOTUPLES[@]}; do
    echo "${inputFile}" >> ${homeDir}/1.jobStarted.txt
    name=$(basename ${inputFile})

    #change the eos mounting point
    fileNewMountingPoint="$(echo $inputFile | awk -F'eos/' '{printf("'${eosRoot}/'%s",$2)}')"

    ./main -o "${name%.*}".output -f "${fileNewMountingPoint}" ${smearing} ${timingOffset} ${outputFormat}

    copyResult=1

    if (( "${toGoogleCloudStorage}" > 0 )); then
        copyResult=0
        for zippedFile in "${name%.*}".output/*.gz; do
            echo "$(date): gsutil copy started"
            google_cloud_bucket=gs://ams-datasets/test
            if [ "${optional}" == "FullProd" ]; then
                google_cloud_bucket=gs://ams-datasets/ISS.B950.FULL
            fi
            gsutil cp ${zippedFile} ${google_cloud_bucket}
            if (( "$?" != 0 )); then
                echo "$(date): gsutil failed. Retrying..."  
                gsutil cp ${zippedFile} ${google_cloud_bucket}
                if (( "$?" != 0 )); then
                    echo "$(date): gsutil failed twice. Copying the file to EOS instead"  
                    copyResult=1
                else
                    echo "${inputFile}" >> ${homeDir}/2.successGoogleCloudExport.txt
                fi
            else
                echo "${inputFile}" >> ${homeDir}/2.successGoogleCloudExport.txt
            fi
        done
    fi

    if (( "${copyResult}" > 0 )); then
        echo "$(date): output copy started"
        cp -R *.output/ ${eosRoot}/ams/user/${initial}/${USER}/binaryAmsData/${jobName}
        if (( "$?" != 0 )); then
            echo "${inputFile}" >> ${homeDir}/3.failureEOSCopy.txt
        else
            echo "${inputFile}" >> ${homeDir}/4.successEOSCopy.txt
        fi
        echo "$(date): EOS copy done"
    fi

    rm -rf *.output/
    echo "$(date): output rm done"
done


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

echo "Done!"