# Compiling the code on lxplus

    ssh lxplus
    
    # Prepare
    eosmount ~/eos
    mkdir temp
    cd temp

    # Clone the repository
    git clone https://github.com/KKostya/AMSDeutons.git
    # git clone git@github.com:KKostya/AMSDeutons.git

    # Compile
    cd AMSDeutons
    source enable
    cd 0.export2bq
    make

    # Run test
    ./bin/dst -o outputFolder -n 10000 -f ${HOME}/eos/ams/Data/AMS02/2014/ISS.B900/std/1439205227.00000001.root

# The full analysis scripts

DEPENDANCE:
_The bigQuery project: git@github.com:wizmer/bigQuery.git. Add it to your PYTHONPATH

USAGE:
1) If the tables 'AMS.cutoffs' and 'AMS.timeInSecInData' need to be recreated, delete them (this can be done at: https://bigquery.cloud.google.com/queries/ams-test-kostya) and then run:
      ./tableManagement/createCutoffTable.sh 
      ./tableManagement/createTimeInSecInDataTable.sh

   The above queries require to process the entire dataset and might be expensive in term of money (I am not so sure)

2) Create the 'param.json' file containing all the parameters required (like binnings, cuts,...):
   Run: python createParamFile.py

3) Run the analysis
   Run: python run.py




