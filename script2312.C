{
    
    gROOT->Reset();
    gInterpreter->AddIncludePath(gSystem->ExpandPathName("$AMSSRC/include"));
    gSystem->Load(gSystem->ExpandPathName("$AMSLIBso"));

    string tipo="ISS.B620";
    string energia="pass4";
    string rootpla[5];
    string istogramma="istogramma2312";
    rootpla[0]="1313295844.00204618.root";
    rootpla[1]="1313297255.00000001.root";
    rootpla[2]="1313297255.00928661.root";
}
