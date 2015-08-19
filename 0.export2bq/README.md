    source amsvar.sh.lxplus
    make ntupleData

    ./ntupleData -n 10000 -o test.root ~/eos/ams/Data/AMS02/2014/ISS.B800/pass5/1388159992.00000001.root
