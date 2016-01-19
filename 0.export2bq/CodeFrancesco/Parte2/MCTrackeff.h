using namespace std;

TCanvas *c_7=new TCanvas("Trigger sel. efficiency");
TCanvas *c7=new TCanvas("Tracker rec. efficiency");
TCanvas *c8=new TCanvas("TOF rec. efficiency");

TH1F * EffQTOFMCP1=new TH1F("EffQTOFMCP1","EffQTOFMCP1",18,0,18);
TH1F * EffQTOFMCP2=new TH1F("EffQTOFMCP2","EffQTOFMCP2",18,0,18);
TH1F * EffQTOFMCP1_R=new TH1F("EffQTOFMCP1_R","EffQTOFMCP1_R",43,0,43);
TH1F * EffQTOFMCP2_R=new TH1F("EffQTOFMCP2_R","EffQTOFMCP2_R",43,0,43);
TH2F * EffQTOFMCD1=new TH2F("EffQTOFMCD1","EffQTOFMCD1",18,0,18,6,0,6);
TH2F * EffQTOFMCD2=new TH2F("EffQTOFMCD2","EffQTOFMCD2",18,0,18,6,0,6);
TH2F * EffQTOFMCD1_R=new TH2F("EffQTOFMCD1_R","EffQTOFMCD1_R",43,0,43,6,0,6);
TH2F * EffQTOFMCD2_R=new TH2F("EffQTOFMCD2_R","EffQTOFMCD2_R",43,0,43,6,0,6);

TH1F * EffTriggMCP1=new TH1F("EffTriggMCP1","EffTriggMCP1",18,0,18);
TH1F * EffTriggMCP2=new TH1F("EffTriggMCP2","EffTriggMCP2",18,0,18);
TH1F * EffTriggMCP1_R=new TH1F("EffTriggMCP1_R","EffTriggMCP1_R",43,0,43);
TH1F * EffTriggMCP2_R=new TH1F("EffTriggMCP2_R","EffTriggMCP2_R",43,0,43);
TH2F * EffTriggMCD1=new TH2F("EffTriggMCD1","EffTriggMCD1",18,0,18,6,0,6);
TH2F * EffTriggMCD2=new TH2F("EffTriggMCD2","EffTriggMCD2",18,0,18,6,0,6);
TH2F * EffTriggMCD1_R=new TH2F("EffTriggMCD1_R","EffTriggMCD1_R",43,0,43,6,0,6);
TH2F * EffTriggMCD2_R=new TH2F("EffTriggMCD2_R","EffTriggMCD2_R",43,0,43,6,0,6);

TH1F * EffTrackMCP1=new TH1F("EffTrackMCP1","EffTrackMCP1",18,0,18);
TH1F * EffTrackMCP2=new TH1F("EffTrackMCP2","EffTrackMCP2",18,0,18);
TH1F * EffTrackMCP1_R=new TH1F("EffTrackMCP1_R","EffTrackMCP1_R",43,0,43);
TH1F * EffTrackMCP2_R=new TH1F("EffTrackMCP2_R","EffTrackMCP2_R",43,0,43);
TH2F * EffTrackMCD1=new TH2F("EffTrackMCD1","EffTrackMCD1",18,0,18,6,0,6);
TH2F * EffTrackMCD2=new TH2F("EffTrackMCD2","EffTrackMCD2",18,0,18,6,0,6);
TH2F * EffTrackMCD1_R=new TH2F("EffTrackMCD1_R","EffTrackMCD1_R",43,0,43,6,0,6);
TH2F * EffTrackMCD2_R=new TH2F("EffTrackMCD2_R","EffTrackMCD2_R",43,0,43,6,0,6);

TH1F * EffTOFMCP1=new TH1F("EffTOFMCP1","EffTOFMCP1",18,0,18);
TH1F * EffTOFMCP2=new TH1F("EffTOFMCP2","EffTOFMCP2",18,0,18);
TH1F * EffTOFMCP1_R=new TH1F("EffTOFMCP1_R","EffTOFMCP1_R",43,0,43);
TH1F * EffTOFMCP2_R=new TH1F("EffTOFMCP2_R","EffTOFMCP2_R",43,0,43);
TH2F * EffTOFMCD1=new TH2F("EffTOFMCD1","EffTOFMCD1",18,0,18,6,0,6);
TH2F * EffTOFMCD2=new TH2F("EffTOFMCD2","EffTOFMCD2",18,0,18,6,0,6);
TH2F * EffTOFMCD1_R=new TH2F("EffTOFMCD1_R","EffTOFMCD1_R",43,0,43,6,0,6);
TH2F * EffTOFMCD2_R=new TH2F("EffTOFMCD2_R","EffTOFMCD2_R",43,0,43,6,0,6);

TH1F * EffTriggerMCP_R_TH1F=new TH1F("EffTriggerMCP_R_TH1F","EffTriggerMCP_R_TH1F",43,0,43);
TH1F * EffTriggerMCP_TH1F=new TH1F("EffTriggerMCP_TH1F","EffTriggerMCP_TH1F",18,0,18);
TH2F * EffTriggerMCD_R_TH2F=new TH2F("EffTriggerMCD_R_TH2F","EffTriggerMCD_R_TH2F",43,0,43,6,0,6);
TH2F * EffTriggerMCD_TH2F=new TH2F("EffTriggerMCD_TH2F","EffTriggerMCD_TH2F",18,0,18,6,0,6);

TH1F * EffQTOFerMCP_R_TH1F=new TH1F("EffQTOFerMCP_R_TH1F","EffQTOFerMCP_R_TH1F",43,0,43);
TH1F * EffQTOFerMCP_TH1F=new TH1F("EffQTOFerMCP_TH1F","EffQTOFerMCP_TH1F",18,0,18);
TH2F * EffQTOFerMCD_R_TH2F=new TH2F("EffQTOFerMCD_R_TH2F","EffQTOFerMCD_R_TH2F",43,0,43,6,0,6);
TH2F * EffQTOFerMCD_TH2F=new TH2F("EffQTOFerMCD_TH2F","EffQTOFerMCD_TH2F",18,0,18,6,0,6);

TH1F * EffTrackerMCP_R_TH1F=new TH1F("EffTrackerMCP_R_TH1F","EffTrackerMCP_R_TH1F",43,0,43);
TH1F * EffTrackerMCP_TH1F=new TH1F("EffTrackerMCP_TH1F","EffTrackerMCP_TH1F",18,0,18);
TH2F * EffTrackerMCD_R_TH2F=new TH2F("EffTrackerMCD_R_TH2F","EffTrackerMCD_R_TH2F",43,0,43,6,0,6);
TH2F * EffTrackerMCD_TH2F=new TH2F("EffTrackerMCD_TH2F","EffTrackerMCD_TH2F",18,0,18,6,0,6);

TH1F * EffTOF_MCP_R_TH1F=new TH1F("EffTOFMCP_R_TH1F","EffTOFMCP_R_TH1F",43,0,43);
TH1F * EffTOF_MCP_TH1F=new TH1F("EffTOFMCP_TH1F","EffTOFMCP_TH1F",18,0,18);
TH2F * EffTOF_MCD_R_TH2F=new TH2F("EffTOFMCD_R_TH2F","EffTOFMCD_R_TH2F",43,0,43,6,0,6);
TH2F * EffTOF_MCD_TH2F=new TH2F("EffTOFMCD_TH2F","EffTOFMCD_TH2F",18,0,18,6,0,6);

void MCTrackeff_Fill(TNtuple *ntupla, int l){
	int k = ntupla->GetEvent(l);
	if(Massa_gen<1&&Massa_gen>0.5) {
		for(int M=0;M<43;M++) if(fabs(Momento_gen)<bin[M+1]&&fabs(Momento_gen)>bin[M]) {
			EffTriggMCP1_R->Fill(M);
			if(((int)Cutmask&1)==1) EffTriggMCP2_R->Fill(M);
			if(((int)Cutmask&1)==1) EffTOFMCP1_R->Fill(M);
			if(((int)Cutmask&3)==3&&Beta_pre>0) EffTOFMCP2_R->Fill(M);
			if(EdepL1<EdepL1beta->Eval(Beta_pre)+0.2&&EdepL1>EdepL1beta->Eval(Beta_pre)-0.2&&((int)Cutmask&3)==3&&Beta_pre>0){
				EffQTOFMCP1_R->Fill(M);
				if(EdepTOFU<EdepTOFbeta->Eval(Beta_pre)+1&&EdepTOFU>EdepTOFbeta->Eval(Beta_pre)-1) EffQTOFMCP2_R->Fill(M);
			}
		}
		//if(EdepTOFU<EdepTOFbeta->Eval(Beta_pre)+1&&EdepTOFU>EdepTOFbeta->Eval(Beta_pre)-1&&((int)Cutmask&3)==3&&Beta_pre>0){
		 if(EdepL1<EdepL1beta->Eval(Beta_pre)+0.2&&EdepL1>EdepL1beta->Eval(Beta_pre)-0.2&&((int)Cutmask&3)==3&&Beta_pre>0){
			for(int M=0;M<43;M++) if(fabs(Momento_gen)<bin[M+1]&&fabs(Momento_gen)>bin[M])	
				EffTrackMCP1_R->Fill(M);
			for(int M=0;M<43;M++) if(fabs(R_pre)<bin[M+1]&&fabs(R_pre)>bin[M])
				if(((int)Cutmask&11)==11&&R_pre>0) EffTrackMCP2_R->Fill(M);
		}

		for(int m=0;m<18;m++)  if(Beta_gen>Betabins[m]&&Beta_gen<=Betabins[m+1]){
			EffTriggMCP1->Fill(m);
			if(((int)Cutmask&1)==1) EffTriggMCP2->Fill(m);
			if(((int)Cutmask&1)==1) EffTOFMCP1->Fill(m);
			if(((int)Cutmask&3)==3&&Beta_pre>0) EffTOFMCP2->Fill(m);
			if(EdepL1<EdepL1beta->Eval(Beta_pre)+0.2&&EdepL1>EdepL1beta->Eval(Beta_pre)-0.2&&((int)Cutmask&3)==3&&Beta_pre>0){
				EffQTOFMCP1->Fill(m);
				if(EdepTOFU<EdepTOFbeta->Eval(Beta_pre)+1&&EdepTOFU>EdepTOFbeta->Eval(Beta_pre)-1) EffQTOFMCP2->Fill(m);
			}

			if(EdepTOFU<EdepTOFbeta->Eval(Beta_pre)+1&&EdepTOFU>EdepTOFbeta->Eval(Beta_pre)-1&&((int)Cutmask&3)==3&&Beta_pre>0){ 
				EffTrackMCP1->Fill(m);
				if(((int)Cutmask&11)==11&&R_pre>0) EffTrackMCP2->Fill(m);
			}
		}
	}

	if(Massa_gen>1&&Massa_gen<2) {
		for(int M=0;M<43;M++) if(fabs(Momento_gen)<bin[M+1]&&fabs(Momento_gen)>bin[M]) {
			EffTriggMCD1_R->Fill(M,(int)(10000*Massa_gen-18570));
			if(((int)Cutmask&1)==1) EffTriggMCD2_R->Fill(M,(int)(10000*Massa_gen-18570));
			if(((int)Cutmask&1)==1) EffTOFMCD1_R->Fill(M,(int)(10000*Massa_gen-18570));
			if(((int)Cutmask&3)==3&&Beta_pre>0) EffTOFMCD2_R->Fill(M,(int)(10000*Massa_gen-18570));
			if(EdepL1<EdepL1beta->Eval(Beta_pre)+0.2&&EdepL1>EdepL1beta->Eval(Beta_pre)-0.2&&((int)Cutmask&3)==3&&Beta_pre>0){
				EffQTOFMCD1_R->Fill(M,(int)(10000*Massa_gen-18570));
				if(EdepTOFU<EdepTOFbeta->Eval(Beta_pre)+1&&EdepTOFU>EdepTOFbeta->Eval(Beta_pre)-1) EffQTOFMCD2_R->Fill(M,(int)(10000*Massa_gen-18570));
			}
		}
		if(EdepTOFU<EdepTOFbeta->Eval(Beta_pre)+1&&EdepTOFU>EdepTOFbeta->Eval(Beta_pre)-1&&((int)Cutmask&3)==3&&Beta_pre>0){
			for(int M=0;M<43;M++) if(fabs(Momento_gen)<bin[M+1]&&fabs(Momento_gen)>bin[M])	
				EffTrackMCD1_R->Fill(M,(int)(10000*Massa_gen-18570));
			for(int M=0;M<43;M++) if(fabs(R_pre)<bin[M+1]&&fabs(R_pre)>bin[M])	
				if(((int)Cutmask&11)==11&&R_pre>0) EffTrackMCD2_R->Fill(M,(int)(10000*Massa_gen-18570));
		}

		for(int m=0;m<18;m++) if(Beta_gen>Betabins[m]&&Beta_gen<=Betabins[m+1]){
			EffTriggMCD1->Fill(m,(int)(10000*Massa_gen-18570));
			if(((int)Cutmask&1)==1) EffTriggMCD2->Fill(m,(int)(10000*Massa_gen-18570));
			if(((int)Cutmask&1)==1) EffTOFMCD1->Fill(m,(int)(10000*Massa_gen-18570));
			if(((int)Cutmask&3)==3&&Beta_pre>0) EffTOFMCD2->Fill(m,(int)(10000*Massa_gen-18570));
			if(EdepL1<EdepL1beta->Eval(Beta_pre)+0.2&&EdepL1>EdepL1beta->Eval(Beta_pre)-0.2&&((int)Cutmask&3)==3&&Beta_pre>0){
				EffQTOFMCD1->Fill(m,(int)(10000*Massa_gen-18570));
				if(EdepTOFU<EdepTOFbeta->Eval(Beta_pre)+1&&EdepTOFU>EdepTOFbeta->Eval(Beta_pre)-1) EffQTOFMCD2->Fill(m,(int)(10000*Massa_gen-18570));
			}

			if(EdepTOFU<EdepTOFbeta->Eval(Beta_pre)+1&&EdepTOFU>EdepTOFbeta->Eval(Beta_pre)-1&&((int)Cutmask&3)==3&&Beta_pre>0){
				EffTrackMCD1->Fill(m,(int)(10000*Massa_gen-18570));
				if(((int)Cutmask&11)==11&&R_pre>0) EffTrackMCD2->Fill(m,(int)(10000*Massa_gen-18570));
			}
		}
	}

	return; 
}

void MCTrackeff_Copy(TFile * file){
	EffTriggMCP1= (TH1F*) file->Get("EffTriggMCP1");
        EffTriggMCD1= (TH2F*) file->Get("EffTriggMCD1");
        EffTriggMCP2= (TH1F*) file->Get("EffTriggMCP2");
        EffTriggMCD2= (TH2F*) file->Get("EffTriggMCD2");
        EffTriggMCP1_R =(TH1F*) file->Get("EffTriggMCP1_R");
        EffTriggMCD1_R =(TH2F*) file->Get("EffTriggMCD1_R");
        EffTriggMCP2_R =(TH1F*) file->Get("EffTriggMCP2_R");
        EffTriggMCD2_R =(TH2F*) file->Get("EffTriggMCD2_R");
        EffQTOFMCP1= (TH1F*) file->Get("EffQTOFMCP1");
        EffQTOFMCD1= (TH2F*) file->Get("EffQTOFMCD1");
        EffQTOFMCP2= (TH1F*) file->Get("EffQTOFMCP2");
        EffQTOFMCD2= (TH2F*) file->Get("EffQTOFMCD2");
        EffQTOFMCP1_R =(TH1F*) file->Get("EffQTOFMCP1_R");
        EffQTOFMCD1_R =(TH2F*) file->Get("EffQTOFMCD1_R");
        EffQTOFMCP2_R =(TH1F*) file->Get("EffQTOFMCP2_R");
        EffQTOFMCD2_R =(TH2F*) file->Get("EffQTOFMCD2_R");
	EffTrackMCP1= (TH1F*) file->Get("EffTrackMCP1");
	EffTrackMCD1= (TH2F*) file->Get("EffTrackMCD1"); 
	EffTrackMCP2= (TH1F*) file->Get("EffTrackMCP2");
	EffTrackMCD2= (TH2F*) file->Get("EffTrackMCD2");
	EffTrackMCP1_R =(TH1F*) file->Get("EffTrackMCP1_R");
	EffTrackMCD1_R =(TH2F*) file->Get("EffTrackMCD1_R");
	EffTrackMCP2_R =(TH1F*) file->Get("EffTrackMCP2_R");
	EffTrackMCD2_R =(TH2F*) file->Get("EffTrackMCD2_R");
	EffTOFMCP1= (TH1F*) file->Get("EffTOFMCP1");
	EffTOFMCD1= (TH2F*) file->Get("EffTOFMCD1");
	EffTOFMCP2= (TH1F*) file->Get("EffTOFMCP2");
	EffTOFMCD2= (TH2F*) file->Get("EffTOFMCD2");
	EffTOFMCP1_R =(TH1F*) file->Get("EffTOFMCP1_R");
	EffTOFMCD1_R =(TH2F*) file->Get("EffTOFMCD1_R");
	EffTOFMCP2_R =(TH1F*) file->Get("EffTOFMCP2_R");
	EffTOFMCD2_R =(TH2F*) file->Get("EffTOFMCD2_R");

	return; 
}

void MCTrackeff(TFile * file1){

	string numero[18]={"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17"};
	string tagli[10]={"Trigger","3of4 TOF","TRD Segments","Rigidity exists","Chi^2 R","Matching TOF","Matching TRD","In TRD Accept.","1 Particle","1 Tr. Track"};
	string nome;
	Tempi = (TH1F *)file1->Get("Tempi");

	cout<<"**** MC BASIC SEL. EFFICIENCIES ****"<<endl;
	float EffQTOFMCP[18]={0};
        for(int i=0;i<17;i++) if(EffQTOFMCP1->GetBinContent(i+1)>0) if(EffQTOFMCP2->GetBinContent(i+1)<EffQTOFMCP1->GetBinContent(i+1))
                EffQTOFMCP[i]=EffQTOFMCP2->GetBinContent(i+1)/(float)EffQTOFMCP1->GetBinContent(i+1);
        float EffQTOFMCD[18][6]={{0}};
        for(int i=0;i<17;i++) for(int h=0;h<6;h++) if(EffQTOFMCD2->GetBinContent(i+1,h+1)<EffQTOFMCD1->GetBinContent(i+1,h+1))
                EffQTOFMCD[i][h]=EffQTOFMCD2->GetBinContent(i+1,h+1)/(float)EffQTOFMCD1->GetBinContent(i+1,h+1);

        float EffQTOFMCP_R[43]={0};
        for(int i=1;i<43;i++) EffQTOFMCP_R[i]=EffQTOFMCP2_R->GetBinContent(i+1)/(float)EffQTOFMCP1_R->GetBinContent(i+1);
        float EffQTOFMCD_R[43][6]={{0}};
        for(int i=4;i<43;i++) for(int h=0;h<6;h++) if(EffQTOFMCD1_R->GetBinContent(i+1,h+1)>EffQTOFMCD2_R->GetBinContent(i+1,h+1))
                EffQTOFMCD_R[i][h]=EffQTOFMCD2_R->GetBinContent(i+1,h+1)/(float)EffQTOFMCD1_R->GetBinContent(i+1,h+1);
                                                                                                                     
	c_7->Divide(2,1);
        float EffTriggMCP[18]={0};
        for(int i=0;i<17;i++) if(EffTriggMCP1->GetBinContent(i+1)>0) if(EffTriggMCP2->GetBinContent(i+1)<EffTriggMCP1->GetBinContent(i+1))
                EffTriggMCP[i]=EffTriggMCP2->GetBinContent(i+1)/(float)EffTriggMCP1->GetBinContent(i+1);
        float EffTriggMCD[18][6]={{0}};
        for(int i=0;i<17;i++) for(int h=0;h<6;h++) if(EffTriggMCD2->GetBinContent(i+1,h+1)<EffTriggMCD1->GetBinContent(i+1,h+1))
                EffTriggMCD[i][h]=EffTriggMCD2->GetBinContent(i+1,h+1)/(float)EffTriggMCD1->GetBinContent(i+1,h+1);

        float EffTriggMCP_R[43]={0};
        for(int i=1;i<43;i++) EffTriggMCP_R[i]=EffTriggMCP2_R->GetBinContent(i+1)/(float)EffTriggMCP1_R->GetBinContent(i+1);
        float EffTriggMCD_R[43][6]={{0}};
        for(int i=4;i<43;i++) for(int h=0;h<6;h++) if(EffTriggMCD1_R->GetBinContent(i+1,h+1)>EffTriggMCD2_R->GetBinContent(i+1,h+1))
                EffTriggMCD_R[i][h]=EffTriggMCD2_R->GetBinContent(i+1,h+1)/(float)EffTriggMCD1_R->GetBinContent(i+1,h+1);
	
	c7->Divide(2,1);
	float EffTrackMCP[18]={0};
	for(int i=0;i<17;i++) if(EffTrackMCP1->GetBinContent(i+1)>0) if(EffTrackMCP2->GetBinContent(i+1)<EffTrackMCP1->GetBinContent(i+1))
		EffTrackMCP[i]=EffTrackMCP2->GetBinContent(i+1)/(float)EffTrackMCP1->GetBinContent(i+1);
	float EffTrackMCD[18][6]={{0}};
	for(int i=0;i<17;i++) for(int h=0;h<6;h++) if(EffTrackMCD2->GetBinContent(i+1,h+1)<EffTrackMCD1->GetBinContent(i+1,h+1))
		EffTrackMCD[i][h]=EffTrackMCD2->GetBinContent(i+1,h+1)/(float)EffTrackMCD1->GetBinContent(i+1,h+1);

	float EffTrackMCP_R[43]={0};
	for(int i=1;i<43;i++) EffTrackMCP_R[i]=EffTrackMCP2_R->GetBinContent(i+1)/(float)EffTrackMCP1_R->GetBinContent(i+1);
	float EffTrackMCD_R[43][6]={{0}};
	for(int i=4;i<43;i++) for(int h=0;h<6;h++) if(EffTrackMCD1_R->GetBinContent(i+1,h+1)>EffTrackMCD2_R->GetBinContent(i+1,h+1))
		EffTrackMCD_R[i][h]=EffTrackMCD2_R->GetBinContent(i+1,h+1)/(float)EffTrackMCD1_R->GetBinContent(i+1,h+1);

	c8->Divide(2,1);
	float EffTOFMCP[18]={0};
	for(int i=0;i<17;i++) if(EffTOFMCP1->GetBinContent(i+1)>0) if(EffTOFMCP2->GetBinContent(i+1)<EffTOFMCP1->GetBinContent(i+1))
		EffTOFMCP[i]=EffTOFMCP2->GetBinContent(i+1)/(float)EffTOFMCP1->GetBinContent(i+1);
	float EffTOFMCD[18][6]={{0}};
	for(int i=0;i<17;i++) for(int h=0;h<6;h++) if(EffTOFMCD2->GetBinContent(i+1,h+1)<EffTOFMCD1->GetBinContent(i+1,h+1))
		EffTOFMCD[i][h]=EffTOFMCD2->GetBinContent(i+1,h+1)/(float)EffTOFMCD1->GetBinContent(i+1,h+1);

	float EffTOFMCP_R[43]={0};
	for(int i=1;i<43;i++) EffTOFMCP_R[i]=EffTOFMCP2_R->GetBinContent(i+1)/(float)EffTOFMCP1_R->GetBinContent(i+1);
	float EffTOFMCD_R[43][6]={{0}};
	for(int i=4;i<43;i++) for(int h=0;h<6;h++) if(EffTOFMCD1_R->GetBinContent(i+1,h+1)>EffTOFMCD2_R->GetBinContent(i+1,h+1))
		EffTOFMCD_R[i][h]=EffTOFMCD2_R->GetBinContent(i+1,h+1)/(float)EffTOFMCD1_R->GetBinContent(i+1,h+1);
	

        for(int i=0;i<43;i++) EffQTOFerMCP_R_TH1F->SetBinContent(i+1,EffQTOFMCP_R[i]);
        for(int h=0;h<6;h++) for(int i=1;i<43;i++) EffQTOFerMCD_R_TH2F->SetBinContent(i+1,h+1,EffQTOFMCD_R[i][h]);
	
	c_7->cd(1);
        gPad->SetLogx();
        gPad->SetGridx();
        gPad->SetGridy();
        string MCLegend[7]={"protons.B800","d.pl1.0_520_GG_Blic","d.pl1.0_520_GG_BlicDPMJet","d.pl1.0_520_GG_QMD","d.pl1.0_520_Shen_Blic","d.pl1.0_520_Shen_BlicDPMJet","d.pl1.0_520_Shen_QMD"};
        TGraph * EffTriggerMCP_R = new TGraph();
        EffTriggerMCP_R->SetTitle(MCLegend[0].c_str());
        for(int i=0;i<43;i++) EffTriggerMCP_R->SetPoint(i,R_cent[i],EffTriggMCP_R[i]);
        for(int i=0;i<43;i++) EffTriggerMCP_R_TH1F->SetBinContent(i+1,EffTriggMCP_R[i]);
        TGraph * EffTriggerMCD_R[6];
        EffTriggerMCP_R->SetMarkerColor(2);
        EffTriggerMCP_R->SetMarkerStyle(8);
        EffTriggerMCP_R->SetLineColor(2);
        EffTriggerMCP_R->SetLineWidth(2);
        EffTriggerMCP_R->SetTitle("Trigger rec. Efficiency MC (R bins)");
        EffTriggerMCP_R->GetXaxis()->SetTitle("R [GV]");
        EffTriggerMCP_R->GetYaxis()->SetTitle("Pres. Efficiency");
        EffTriggerMCP_R->GetXaxis()->SetTitleSize(0.045);
        EffTriggerMCP_R->GetYaxis()->SetTitleSize(0.045);
        {
                EffTriggerMCP_R->Draw("ACP");
                TLegend* leg =new TLegend(0.4, 0.7,0.95,0.95);
                leg->AddEntry(EffTriggerMCP_R,MCLegend[0].c_str(), "ep");

                for(int h=0;h<6;h++){
                        EffTriggerMCD_R[h]= new TGraph();
                        EffTriggerMCD_R[h]->SetTitle(MCLegend[h+1].c_str());
                        for(int i=1;i<43;i++) EffTriggerMCD_R[h]->SetPoint(i,R_cent[i],EffTriggMCD_R[i][h]);
                        for(int i=1;i<43;i++) EffTriggerMCD_R_TH2F->SetBinContent(i+1,h+1,EffTriggMCD_R[i][h]);
                        leg->AddEntry(EffTriggerMCD_R[h],MCLegend[h+1].c_str(), "ep");
                        EffTriggerMCD_R[h]->SetMarkerColor(4);
                        EffTriggerMCD_R[h]->SetMarkerStyle(h+3);
                        EffTriggerMCD_R[h]->SetMarkerSize(2);
                        EffTriggerMCD_R[h]->SetLineColor(4);
                        EffTriggerMCD_R[h]->SetLineWidth(2);
                        EffTriggerMCD_R[h]->Draw("Psame");
                        leg->Draw();
                }
        }
        c_7->cd(2);
        gPad->SetLogx();
        gPad->SetGridx();
        gPad->SetGridy();
        TGraph * EffTriggerMCP = new TGraph();
        for(int i=0;i<17;i++) EffTriggerMCP->SetPoint(i,Ekincent[i],EffTriggMCP[i]);
        for(int i=0;i<17;i++) EffTriggerMCP_TH1F->SetBinContent(i+1,EffTriggMCP[i]);
        TGraph * EffTriggerMCD[6];
        EffTriggerMCP->SetMarkerColor(2);
        EffTriggerMCP->SetMarkerStyle(8);
        EffTriggerMCP->SetLineColor(2);
        EffTriggerMCP->SetLineWidth(2);
        EffTriggerMCP->SetTitle("Trigger rec. Efficiency MC (Beta bins)");
        EffTriggerMCP->GetXaxis()->SetTitle("Kin. En. / nucl. [GeV/nucl.]");
        EffTriggerMCP->GetYaxis()->SetTitle("Trigger rec. Efficiency");
        EffTriggerMCP->GetXaxis()->SetTitleSize(0.045);
        EffTriggerMCP->GetYaxis()->SetTitleSize(0.045);
        {
                EffTriggerMCP->Draw("ACP");
                TLegend* leg =new TLegend(0.4, 0.7,0.95,0.95);
                leg->AddEntry(EffTriggerMCP,MCLegend[0].c_str(), "ep");

                for(int h=0;h<6;h++){
                        EffTriggerMCD[h]= new TGraph();
                        for(int i=0;i<17;i++) EffTriggerMCD[h]->SetPoint(i,Ekincent[i],EffTriggMCD[i][h]);
                        for(int i=0;i<17;i++) EffTriggerMCD_TH2F->SetBinContent(i+1,h+1,EffTriggMCD[i][h]);
                        EffTriggerMCD[h]->SetMarkerColor(4);
                        EffTriggerMCD[h]->SetMarkerStyle(h+3);
                        leg->AddEntry(EffTriggerMCD[h],MCLegend[h+1].c_str(), "ep");
                        EffTriggerMCD[h]->SetMarkerSize(2);
                        EffTriggerMCD[h]->SetLineColor(4);
                        EffTriggerMCD[h]->SetLineWidth(2);
                        EffTriggerMCD[h]->Draw("Psame");
                        leg->Draw();
                }
        }

	c7->cd(1);
	gPad->SetLogx();
	gPad->SetGridx();
	gPad->SetGridy();
	TGraph * EffTrackerMCP_R = new TGraph();
	EffTrackerMCP_R->SetTitle(MCLegend[0].c_str());
	for(int i=0;i<43;i++) EffTrackerMCP_R->SetPoint(i,R_cent[i],EffTrackMCP_R[i]);
	for(int i=0;i<43;i++) EffTrackerMCP_R_TH1F->SetBinContent(i+1,EffTrackMCP_R[i]);
	TGraph * EffTrackerMCD_R[6];
	EffTrackerMCP_R->SetMarkerColor(2);
	EffTrackerMCP_R->SetMarkerStyle(8);
	EffTrackerMCP_R->SetLineColor(2);
	EffTrackerMCP_R->SetLineWidth(2);
	EffTrackerMCP_R->SetTitle("Tracker rec. Efficiency MC (R bins)");
	EffTrackerMCP_R->GetXaxis()->SetTitle("R [GV]");
	EffTrackerMCP_R->GetYaxis()->SetTitle("Pres. Efficiency");
	EffTrackerMCP_R->GetXaxis()->SetTitleSize(0.045);
	EffTrackerMCP_R->GetYaxis()->SetTitleSize(0.045);
	{
		EffTrackerMCP_R->Draw("ACP");
		TLegend* leg =new TLegend(0.4, 0.7,0.95,0.95);
		leg->AddEntry(EffTrackerMCP_R,MCLegend[0].c_str(), "ep");

		for(int h=0;h<6;h++){
			EffTrackerMCD_R[h]= new TGraph();
			EffTrackerMCD_R[h]->SetTitle(MCLegend[h+1].c_str());
			for(int i=1;i<43;i++) EffTrackerMCD_R[h]->SetPoint(i,R_cent[i],EffTrackMCD_R[i][h]);
			for(int i=1;i<43;i++) EffTrackerMCD_R_TH2F->SetBinContent(i+1,h+1,EffTrackMCD_R[i][h]);
			leg->AddEntry(EffTrackerMCD_R[h],MCLegend[h+1].c_str(), "ep");
			EffTrackerMCD_R[h]->SetMarkerColor(4);
			EffTrackerMCD_R[h]->SetMarkerStyle(h+3);
			EffTrackerMCD_R[h]->SetMarkerSize(2);
			EffTrackerMCD_R[h]->SetLineColor(4);
			EffTrackerMCD_R[h]->SetLineWidth(2);
			EffTrackerMCD_R[h]->Draw("Psame");
			leg->Draw();
		}
	}
	c7->cd(2);
	gPad->SetLogx();
	gPad->SetGridx();
	gPad->SetGridy();
	TGraph * EffTrackerMCP = new TGraph();
	for(int i=0;i<17;i++) EffTrackerMCP->SetPoint(i,Ekincent[i],EffTrackMCP[i]);
	for(int i=0;i<17;i++) EffTrackerMCP_TH1F->SetBinContent(i+1,EffTrackMCP[i]);
	TGraph * EffTrackerMCD[6];
	EffTrackerMCP->SetMarkerColor(2);
	EffTrackerMCP->SetMarkerStyle(8);
	EffTrackerMCP->SetLineColor(2);
	EffTrackerMCP->SetLineWidth(2);
	EffTrackerMCP->SetTitle("Tracker rec. Efficiency MC (Beta bins)");
	EffTrackerMCP->GetXaxis()->SetTitle("Kin. En. / nucl. [GeV/nucl.]");
	EffTrackerMCP->GetYaxis()->SetTitle("Tracker rec. Efficiency");
	EffTrackerMCP->GetXaxis()->SetTitleSize(0.045);
	EffTrackerMCP->GetYaxis()->SetTitleSize(0.045);
	{
		EffTrackerMCP->Draw("ACP");
		TLegend* leg =new TLegend(0.4, 0.7,0.95,0.95);
		leg->AddEntry(EffTrackerMCP,MCLegend[0].c_str(), "ep");

		for(int h=0;h<6;h++){
			EffTrackerMCD[h]= new TGraph();
			for(int i=0;i<17;i++) EffTrackerMCD[h]->SetPoint(i,Ekincent[i],EffTrackMCD[i][h]);
			for(int i=0;i<17;i++) EffTrackerMCD_TH2F->SetBinContent(i+1,h+1,EffTrackMCD[i][h]);
			EffTrackerMCD[h]->SetMarkerColor(4);
			EffTrackerMCD[h]->SetMarkerStyle(h+3);
			leg->AddEntry(EffTrackerMCD[h],MCLegend[h+1].c_str(), "ep");
			EffTrackerMCD[h]->SetMarkerSize(2);
			EffTrackerMCD[h]->SetLineColor(4);
			EffTrackerMCD[h]->SetLineWidth(2);
			EffTrackerMCD[h]->Draw("Psame");
			leg->Draw();
		}
	}

	c8->cd(1);
	gPad->SetLogx();
	gPad->SetGridx();
	gPad->SetGridy();
	TGraph * EffTOF_MCP_R = new TGraph();
	EffTOF_MCP_R->SetTitle(MCLegend[0].c_str());
	for(int i=0;i<43;i++) EffTOF_MCP_R->SetPoint(i,R_cent[i],EffTOFMCP_R[i]);
	for(int i=0;i<43;i++) EffTOF_MCP_R_TH1F->SetBinContent(i+1,EffTOFMCP_R[i]);
	TGraph * EffTOF_MCD_R[6];
	EffTOF_MCP_R->SetMarkerColor(2);
	EffTOF_MCP_R->SetMarkerStyle(8);
	EffTOF_MCP_R->SetLineColor(2);
	EffTOF_MCP_R->SetLineWidth(2);
	EffTOF_MCP_R->SetTitle("TOF rec. Efficiency MC (R bins)");
	EffTOF_MCP_R->GetXaxis()->SetTitle("R [GV]");
	EffTOF_MCP_R->GetYaxis()->SetTitle("Pres. Efficiency");
	EffTOF_MCP_R->GetXaxis()->SetTitleSize(0.045);
	EffTOF_MCP_R->GetYaxis()->SetTitleSize(0.045);
	{
		EffTOF_MCP_R->Draw("ACP");
		TLegend* leg =new TLegend(0.4, 0.7,0.95,0.95);
		leg->AddEntry(EffTOF_MCP_R,MCLegend[0].c_str(), "ep");

		for(int h=0;h<6;h++){
			EffTOF_MCD_R[h]= new TGraph();
			EffTOF_MCD_R[h]->SetTitle(MCLegend[h+1].c_str());
			for(int i=1;i<43;i++) EffTOF_MCD_R[h]->SetPoint(i,R_cent[i],EffTOFMCD_R[i][h]);
			for(int i=1;i<43;i++) EffTOF_MCD_R_TH2F->SetBinContent(i+1,h+1,EffTOFMCD_R[i][h]);
			leg->AddEntry(EffTOF_MCD_R[h],MCLegend[h+1].c_str(), "ep");
			EffTOF_MCD_R[h]->SetMarkerColor(4);
			EffTOF_MCD_R[h]->SetMarkerStyle(h+3);
			EffTOF_MCD_R[h]->SetMarkerSize(2);
			EffTOF_MCD_R[h]->SetLineColor(4);
			EffTOF_MCD_R[h]->SetLineWidth(2);
			EffTOF_MCD_R[h]->Draw("Psame");
			leg->Draw();
		}
	}

	c8->cd(2);
	gPad->SetLogx();
	gPad->SetGridx();
	gPad->SetGridy();
	TGraph * EffTOF_MCP = new TGraph();
	for(int i=0;i<17;i++) EffTOF_MCP->SetPoint(i,Ekincent[i],EffTOFMCP[i]);
	for(int i=0;i<17;i++) EffTOF_MCP_TH1F->SetBinContent(i+1,EffTOFMCP[i]);
	TGraph * EffTOF_MCD[6];
	EffTOF_MCP->SetMarkerColor(2);
	EffTOF_MCP->SetMarkerStyle(8);
	EffTOF_MCP->SetLineColor(2);
	EffTOF_MCP->SetLineWidth(2);
	EffTOF_MCP->SetTitle("TOF_ rec. Efficiency MC (Beta bins)");
	EffTOF_MCP->GetXaxis()->SetTitle("Kin. En. / nucl. [GeV/nucl.]");
	EffTOF_MCP->GetYaxis()->SetTitle("TOF_ rec. Efficiency");
	EffTOF_MCP->GetXaxis()->SetTitleSize(0.045);
	EffTOF_MCP->GetYaxis()->SetTitleSize(0.045);
	{
		EffTOF_MCP->Draw("ACP");
		TLegend* leg =new TLegend(0.4, 0.7,0.95,0.95);
		leg->AddEntry(EffTOF_MCP,MCLegend[0].c_str(), "ep");

		for(int h=0;h<6;h++){
			EffTOF_MCD[h]= new TGraph();
			for(int i=0;i<17;i++) EffTOF_MCD[h]->SetPoint(i,Ekincent[i],EffTOFMCD[i][h]);
			for(int i=0;i<17;i++) EffTOF_MCD_TH2F->SetBinContent(i+1,h+2,EffTOFMCD[i][h]);
			EffTOF_MCD[h]->SetMarkerColor(4);
			EffTOF_MCD[h]->SetMarkerStyle(h+3);
			leg->AddEntry(EffTOF_MCD[h],MCLegend[h+1].c_str(), "ep");
			EffTOF_MCD[h]->SetMarkerSize(2);
			EffTOF_MCD[h]->SetLineColor(4);
			EffTOF_MCD[h]->SetLineWidth(2);
			EffTOF_MCD[h]->Draw("Psame");
			leg->Draw();
		}
	}


}
