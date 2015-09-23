#include "gtest/gtest.h"

#include <amschain.h>
// AMS includes
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif

#include "root.h"

#include "Selections/SelectionLists.hpp"
#include "Data/RootWriter.hpp"
#include "Data/TOF.h"
#include "Data/Tracker.h"
#include "Data/Ecal.h"
#include "Data/SelectionStatus.h"
#include "Data/3DVariables.h"
#include "utils/rootUtils.hpp"


// To use a test fixture, derive a class from testing::Test.
class QueueTest : public testing::Test {
protected:  // You should make the members protected s.t. they can be
    // accessed from sub-classes.

    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the varaibles.
    // Otherwise, this can be skipped.
    virtual void SetUp() {

        ch = new AMSChain;
        ch->Add("/afs/cern.ch/work/b/bcoste/1364285262.00000001.root");

        File = new TFile("test.root", "RECREATE");
        outTree = new TTree("data","data");


        // Initializing RTI
        AMSSetupR::RTI rti;rti.UseLatest(6);
        TkDBc::UseFinal();
        TRMCFFKEY_DEF::ReadFromFile = 0;
        TRFITFFKEY_DEF::ReadFromFile = 0;
        TRFITFFKEY.magtemp = 0;

        // Checking if MC
        ch->GetEvent(0);
        bool isMC = AMSEventR::Head()->nMCEventg() > 0;
        ch->Rewind();
    }

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    //
    virtual void TearDown() {
        File -> Write();
    }


    void loop100Events(void (*AddVariableFunction)(ROOTDataList&,TTree*)){
        ROOTDataList data;
        AddVariableFunction(data, outTree);

        for(int ii=0;ii<100;ii++)
            {
                AMSEventR * ev = ch->GetEvent();
                if(!ev) continue;
                outTree -> Fill();
            }

        EXPECT_GT(outTree->GetEntries(), 0);
    }


    // // Declares the variables your tests want to use.
    AMSChain  * ch;
    TFile * File;
    TTree * outTree;
};

TEST_F(QueueTest,AddProvenanceVariables ) {
    // You can access data in the test fixture here.
    //EXPECT_EQ(0u, q0_.Size());
    loop100Events(AddProvenanceVariables);
}

TEST_F(QueueTest,AddGeoVariables ) {
    // You can access data in the test fixture here.
    //EXPECT_EQ(0u, q0_.Size());
    loop100Events(AddGeoVariables);
}

TEST_F(QueueTest,AddSelectionVariables ) {
    // You can access data in the test fixture here.
    //EXPECT_EQ(0u, q0_.Size());
    loop100Events(AddSelectionVariables);
}

TEST_F(QueueTest,AddECALVariable ) {
    // You can access data in the test fixture here.
    //EXPECT_EQ(0u, q0_.Size());
    loop100Events(AddECALVariable);
}

TEST_F(QueueTest,AddTRDVariables ) {
    // You can access data in the test fixture here.
    //EXPECT_EQ(0u, q0_.Size());
    loop100Events(AddTRDVariables);
}

TEST_F(QueueTest,AddTOFVariables ) {
    // You can access data in the test fixture here.
    //EXPECT_EQ(0u, q0_.Size());
    loop100Events(AddTOFVariables);
}

TEST_F(QueueTest,AddTrackerVariables ) {
    // You can access data in the test fixture here.
    //EXPECT_EQ(0u, q0_.Size());
    loop100Events(AddTrackerVariables);
}

TEST_F(QueueTest,Add3DVariables ) {
    // You can access data in the test fixture here.
    //EXPECT_EQ(0u, q0_.Size());
    loop100Events(Add3DVariables);
}

