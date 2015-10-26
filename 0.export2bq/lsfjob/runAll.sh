#!/bin/bash
if [ "$#" -lt 1 ]; then
    echo usage: ./runAll.sh jobName
    exit
fi

export eosRoot=${HOME}/eos
./submitMakeBinaryData.sh ISS.B950_pass6_$1 ${eosRoot}/ams/Data/AMS02/2014/ISS.B950/pass6 
./submitMakeBinaryData.sh protons.B1034_pr.pl1.1200.qgsp_bic_ams_$1 ${eosRoot}/ams/MC/AMS02/2014/protons.B1034/pr.pl1.1200.qgsp_bic_ams