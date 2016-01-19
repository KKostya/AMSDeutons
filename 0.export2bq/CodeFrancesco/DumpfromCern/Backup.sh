#!/bin/bash

export WORKDIR=/afs/cern.ch/work/f/fdimicco/private/Dimiccoli/Compiled;

rm -r $WORKDIR/BackupCERN;
mkdir $WORKDIR/BackupCERN;

cp $WORKDIR/*.C $WORKDIR/BackupCERN;
cp -r $WORKDIR/o $WORKDIR/BackupCERN;
cp $WORKDIR/*.sh $WORKDIR/BackupCERN;
cp -r $WORKDIR/perl $WORKDIR/BackupCERN;

tar cvf $WORKDIR/BackupCERN.tar $WORKDIR/BackupCERN/
