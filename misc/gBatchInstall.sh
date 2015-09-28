# System:
# Description:	Ubuntu 14.04.3 LTS
# Release:	14.04
# Codename:	trusty

# compiler:
# g++ (Ubuntu 4.8.4-2ubuntu1~14.04) 4.8.4

# git gbatch repo hash:
# 1f87cffcdfbb28bf877b45b46824cfa802642aef

sudo apt-get install git unzip build-essential libx11-dev cmake libxml2-dev libgmp3-dev m4 libffi-dev libzmq3-dev 
sudo apt-get install libssl-dev libxpm-dev libxft-dev libxext-dev libjpeg8-dev python2.7

# XROOTD
git clone https://github.com/xrootd/xrootd.git
cd xrootd
git checkout b2ee72584fbc5ef6873bbac445b4b620b5bca71e
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/opt/xrootd -DENABLE_PERL=FALSE
make
sudo make install
cd ../..

# ROOT
wget https://root.cern.ch/download/root_v5.34.32.source.tar.gz
tar -xzvf root_v5.34.32.source.tar.gz
cd root
sed -i '5015 a \   decver=400000000' configure #Make a fake xrootd version number corresponding to version 4
./configure --all
make
ROOTPATH=`pwd`
source bin/thisroot.sh
cd ..

# GBATCH
echo "Password is the standard password associated with user: AMSWWW"
GIT_SSL_NO_VERIFY=true git clone https://amswww@stash.physik.rwth-aachen.de/scm/gbatch/ams.git 

cd ams/install
cat<<AMSVAR>amsvar_bash.gcc64
#!/bin/bash
if [ -z "\${Offline}" ]; then
    echo "Please export the env var Offline first:"
    echo "Suggestions:"
    echo "export Offline=/cvmfs/ams.cern.ch/Offline"
    echo "or if you can't access cvmfs:"
    echo "export Offline=/afs/cern.ch/exp/ams/Offline"
    exit 1
fi  
export ROOTSYS=${ROOTPATH}
export PATH=${ROOTSYS}/bin:${PATH}
export LD_LIBRARY_PATH=$ROOTSYS/lib:${LD_LIBRARY_PATH}
export CVSROOT=$Offline/CVS
#export CVSROOT=:ext:`whoami`@ams.cern.ch:/cvsroot
export CVS_RSH=ssh
export ProductionRunsDir=/s0dat0/Data/Deframing
export AMSDataDir=$Offline/AMSDataDir
export AMSDataDirRW=$Offline/AMSDataDirRW
export EDITOR= emacs
export CVSEDITOR= emacs
export RunsDir=$Offline/RunsDir
export AMSDataNtuplesDir=$Offline/ntuples
export AMSMCNtuplesDir=$Offline/amsmcntuplesdir
export ProductionLogDirLocal=$Offline/logs.local
export RunsSummaryFile=$Offline/runs_STS91.log
export SlowRateDataDir=$Offline/SlowRateDataDir
export AMSGeoDir=$Offline/vdev/display/
export amsed=$Offline/vdev/exe/linuxx8664gcc/amsed
export amsedc=$Offline/vdev/exe/linuxx8664gcc/amsedc
export amsedPG=$Offline/vdev/exe/linuxx8664gcc/amsedPG
export amsedcPG=$Offline/vdev/exe/linuxx8664gcc/amsedcPG
export offmon=$Offline/vdev/exe/linux/offmon      
export offmonc=$Offline/vdev/exe/linux/offmonc      
export AMSDynAlignment=$AMSDataDirRW/ExtAlig/AlignmentFiles/
export AMSICC=1
export AMSP=1
export XROOTD=/opt/xrootd/
export PATH=${XROOTD}/bin:$PATH
export LD_LIBRARY_PATH=${XROOTD}/lib64:${AMSWD}/lib/linuxx8664gcc5.34:${LD_LIBRARY_PATH}
export NORFIOD=1
export NOCASTOR=1
export SLC6system=1
export PGTRACK=1
AMSVAR

source amsvar_bash.gcc64
make lib
cd ../../

# # ACSoft
# GIT_SSL_NO_VERIFY=true git clone https://amswww@stash.physik.rwth-aachen.de/scm/acsoft/ams-acsoft.git
# GIT_SSL_NO_VERIFY=true git checkout release/7.0.1.0
# mkdir build
# cd build
# cmake .. && make -j

# # ACSoft Event Display
# GIT_SSL_NO_VERIFY=true git clone https://amswww@stash.physik.rwth-aachen.de/scm/acsofted/ams-acsofted.git
# mkdir build
# cd build
# cmake .. && make -j 
