
 
 
setenv AMSBASE /afs/cern.ch/ams/Offline/AMSsoft
setenv AMSSYS linux_slc6_gcc64
setenv ROOTSYS $AMSBASE/$AMSSYS/root_v5.34ams/
setenv CERN $AMSBASE/$AMSSYS/
setenv CERN_LEVEL 2005/
setenv CERN_ROOT $CERN/$CERN_LEVEL
setenv CERNDIR $CERN/$CERN_LEVEL
setenv AMSLIB $CERNDIR
setenv AMSDataDir /cvmfs/ams.cern.ch/Offline/AMSDataDir
setenv PATH $ROOTSYS/bin:$CERN_ROOT/bin:/afs/cern.ch/ams/opt/intel/composer_xe_2011_sp1.9.293/compiler//bin/intel64:$PATH
setenv LD_LIBRARY_PATH $ROOTSYS/lib:/afs/cern.ch/ams/opt/intel/composer_xe_2011_sp1.9.293/compiler//lib/intel64
setenv CLHEP_BASE_DIR $AMSBASE/$AMSSYS/CLHEP
setenv CLHEP_INCLUDE_DIR $AMSBASE/$AMSSYS/CLHEP/include
setenv CLHEP_LIB_DIR $AMSBASE/$AMSSYS/CLHEP/lib
setenv G4INSTALL $AMSBASE/$AMSSYS/geant4_ams
 
 
setenv G4SYSTEM Linux-g++.64
setenv G4USE_STL 1
setenv OGLHOME /usr
setenv G4WORKDIR /tmp
setenv G4LIB $G4INSTALL/lib
setenv G4_NO_VERBOSE 1
 
 
# Environment variables needed to find geant4 data files:
#
# Data for neutron scattering processes,
#    distributed in a separate tar file, then placed under data
setenv NeutronHPCrossSections $AMSBASE/shared/newgeant4/data/G4NDL3.14
#
#  Nuclear Photon evaporation data,
#    distributed with the source files under data
setenv G4LEVELGAMMADATA $AMSBASE/shared/newgeant4/data/PhotonEvaporation2.1
#
# Data for radiative decay hadronic processes under data,
#    distributed in a separate tar file
setenv G4RADIOACTIVEDATA $AMSBASE/shared/newgeant4/data/RadiativeDecay3.3
#
# Data for low energy electromagnetic processes,
#    distributed in a separate tar file, then placed under data
setenv G4LEDATA $AMSBASE/shared/newgeant4/data/G4EMLOW6.19
setenv G4NEUTRONHPDATA $AMSBASE/shared/newgeant4/data/G4NDL3.14
setenv G4ABLADATA $AMSBASE/shared/newgeant4/data/G4ABLA3.0
setenv G4REALSURFACEDATA $AMSBASE/shared/newgeant4/data/RealSurface1.0
setenv G4NEUTRONXSDATA $AMSBASE/shared/newgeant4/data/G4NEUTRONXS1.0
setenv G4PIIDATA $AMSBASE/shared/newgeant4/data/G4PII1.2
#
# Data for elastic scattering processes,
#    distributed in a separate tar file, then placed under data
setenv G4ELASTICDATA $AMSBASE/shared/newgeant4/data/G4ELASTIC1.1
setenv G4DPMJET2_5DATA $AMSBASE/shared/newgeant4/data/DPMJET/GlauberData
 
 
setenv AMSP 1
setenv G4AMS 1
setenv PGTRACK 1
setenv AMSSRC /afs/cern.ch/ams/Offline/vdev/
setenv AMSGeoDir $AMSSRC/display/ams02/
setenv CVS_RSH ssh
setenv AMSWD /afs/cern.ch/ams/Offline/vdev/




setenv AMSLIBso $AMSSRC/lib/linuxx8664gcc5.34/ntuple_slc6_PG.so

setenv AMSICC 1
setenv ECALBDT 1
setenv STAGE_HOST castorpublic
setenv RFIO_USE_CASTOR_V2 YES
setenv STAGE_SVCCLASS amsuser
setenv CASTOR_INSTANCE castorpublic
