#!/bin/bash

echo "YOU ARE ABOUT TO LAUNCH 4000 JOBS"
echo "ARE YOU SURE YOU WANT TO PROCEED ?"
echo "Type yes to continue"
read confirmation

if [ "$confirmation" != "yes" ]; then
    exit
fi

echo ""
echo "Have you checked that everything is up-to-date ?"
echo "Type yes to continue"
read confirmation
if [ "$confirmation" != "yes" ]; then
    exit
fi

python -c "with open('/afs/cern.ch/user/b/bcoste/public/lsfJobs/ISS.B950.all.txt') as f: all={word.strip() for word in f};
with open('/afs/cern.ch/user/b/bcoste/public/lsfJobs/ISS.B950.processed.txt') as f: done={word.strip() for word in f};
with open('ISS.B950.toDo.txt','w') as f:
 for file in all-done: f.write(file+'\n')"

jobName=fullISS.B950_$(date -R | tr ' ,:' '_' | cut -c -25)_${USER}
./submitMakeBinaryData.sh $jobName ISS.B950.toDo.txt FullProd
