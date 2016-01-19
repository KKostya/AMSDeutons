using namespace std;

TCanvas *c18=new TCanvas("Quality Sel. Check");

TH1F * EffQualCheckMCP1 = new TH1F("EffQualCheckMCP1","EffQualCheckMCP1",43,0,43);
TH1F * EffQualCheckMCP2 = new TH1F("EffQualCheckMCP2","EffQualCheckMCP2",43,0,43);

TH1F * EffTOFUCheckMCP1 = new TH1F("EffTOFUCheckMCP1","EffTOFUCheckMCP1",43,0,43);
TH1F * EffTOFUCheckMCP2 = new TH1F("EffTOFUCheckMCP2","EffTOFUCheckMCP2",43,0,43);
TH1F * EffTOFDCheckMCP1 = new TH1F("EffTOFDCheckMCP1","EffTOFDCheckMCP1",43,0,43);
TH1F * EffTOFDCheckMCP2 = new TH1F("EffTOFDCheckMCP2","EffTOFDCheckMCP2",43,0,43);
TH1F * EffTrackCheckMCP1 = new TH1F("EffTrackCheckMCP1","EffTrackCheckMCP1",43,0,43);
TH1F * EffTrackCheckMCP2 = new TH1F("EffTrackCheckMCP2","EffTrackCheckMCP2",43,0,43);

TH1F * EffLikCheckMCP1 = new TH1F("EffLikCheckMCP1","EffTLikkCheckMCP1",43,0,43);
TH1F * EffLikCheckMCP2 = new TH1F("EffLikCheckMCP2","EffLikCheckMCP2",43,0,43);

TH1F * EffQualCheckMCP_TH1F = new TH1F("EffQualCheckMCP_TH1F","EffQualCheckMCP_TH1F",43,0,43);

void MCQualCheck_Fill(TNtuple *ntupla, int l){

	int k = ntupla->GetEvent(l);
	if(Beta<=0||R<=0||Beta>protons->Eval(R)+0.1||Beta<protons->Eval(R)-0.1) return;
	if(Massa_gen<1){
		for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]) {EffQualCheckMCP2->Fill(K);}
		if(Dist5D_P<6&&LDiscriminant>0.7)
			for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]) {EffQualCheckMCP1->Fill(K);}

		if(!(YTOFD>3||YTOFD<-3||YTrack>3||YTrack<-3)||LDiscriminant>0.7){
			for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]) {EffTOFUCheckMCP2->Fill(K);}
			if(Dist5D_P<6)
				for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]) {EffTOFUCheckMCP1->Fill(K);}
		}
		if(!(YTOFU>3||YTOFU<-3||YTrack>3||YTrack<-3)||LDiscriminant>0.7){
			for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]) {EffTOFDCheckMCP2->Fill(K);}
			if(Dist5D_P<6)	
				for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]) {EffTOFDCheckMCP1->Fill(K);}
		}
		if(!(YTOFU>3||YTOFU<-3||YTOFD>3||YTOFD<-3)||LDiscriminant>0.7){
			for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]) {EffTrackCheckMCP2->Fill(K);}
			if(Dist5D_P<6)
				for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]) {EffTrackCheckMCP1->Fill(K);}
		}
		if(Dist5D_P<3){
                        for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]) {EffLikCheckMCP2->Fill(K);}
                        if(LDiscriminant>0.7)
                                for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]) {EffLikCheckMCP1->Fill(K);}
                }
	}
	return;
}

void MCQualCheck_Copy(TFile * file1){
        EffQualCheckMCP1 = (TH1F *)file1->Get("EffQualCheckMCP1");
        EffQualCheckMCP2 = (TH1F *)file1->Get("EffQualCheckMCP2");
	EffTOFUCheckMCP1 = (TH1F *)file1->Get("EffTOFUCheckMCP1");
        EffTOFUCheckMCP2 = (TH1F *)file1->Get("EffTOFUCheckMCP2");
	EffTrackCheckMCP1 = (TH1F *)file1->Get("EffTrackCheckMCP1");
        EffTrackCheckMCP2 = (TH1F *)file1->Get("EffTrackCheckMCP2");
	EffTOFDCheckMCP1 = (TH1F *)file1->Get("EffTOFDCheckMCP1");
        EffTOFDCheckMCP2 = (TH1F *)file1->Get("EffTOFDCheckMCP2");
	EffLikCheckMCP1 = (TH1F *)file1->Get("EffLikCheckMCP1");
        EffLikCheckMCP2 = (TH1F *)file1->Get("EffLikCheckMCP2");
	return;
}

void MCQualCheck(TFile * file1){
        cout<<"**** MC QUALITY SEL. CHECK ****"<<endl;
	float EffQualCheckP[43]={0};
        for(int i=1;i<43;i++) EffQualCheckP[i]=EffQualCheckMCP1->GetBinContent(i+1)/(float)EffQualCheckMCP2->GetBinContent(i+1);
	for(int i=1;i<43;i++) EffQualCheckMCP_TH1F->SetBinContent(i+1,EffQualCheckMCP1->GetBinContent(i+1)/(float)EffQualCheckMCP2->GetBinContent(i+1));
	float EffTOFUCheckP[43]={0};
        for(int i=1;i<43;i++) EffTOFUCheckP[i]=EffTOFUCheckMCP1->GetBinContent(i+1)/(float)EffTOFUCheckMCP2->GetBinContent(i+1);	
	float EffTrackCheckP[43]={0};
        for(int i=1;i<43;i++) EffTrackCheckP[i]=EffTrackCheckMCP1->GetBinContent(i+1)/(float)EffTrackCheckMCP2->GetBinContent(i+1);
	float EffTOFDCheckP[43]={0};
        for(int i=1;i<43;i++) EffTOFDCheckP[i]=EffTOFDCheckMCP1->GetBinContent(i+1)/(float)EffTOFDCheckMCP2->GetBinContent(i+1);	
	float EffLikCheckP[43]={0};
        for(int i=1;i<43;i++) EffLikCheckP[i]=EffLikCheckMCP1->GetBinContent(i+1)/(float)EffLikCheckMCP2->GetBinContent(i+1);
	c18->cd();
        gPad->SetLogx();
        gPad->SetGridx();
        gPad->SetGridy();
        TGraph *EffMCQualCheckP= new TGraph();
        TGraph *EffMCQualCheckCompP= new TGraph();
        int j=0;
        for(int i=1;i<43;i++) {EffMCQualCheckP->SetPoint(j,R_cent[i],EffQualCheckP[i]);j++;}
        for(int i=1;i<43;i++) {EffMCQualCheckCompP->SetPoint(j,R_cent[i],EffLikCheckP[i]*EffTOFUCheckP[i]*EffTrackCheckP[i]*EffTOFDCheckP[i]);j++;}
        EffMCQualCheckP->SetMarkerColor(2);
        EffMCQualCheckP->SetMarkerStyle(8);
        EffMCQualCheckP->SetLineColor(2);
        EffMCQualCheckP->SetLineWidth(2);
        EffMCQualCheckCompP->SetMarkerColor(2);
        EffMCQualCheckCompP->SetMarkerStyle(4);
        EffMCQualCheckCompP->SetLineColor(2);
        EffMCQualCheckCompP->SetLineWidth(2);
        EffMCQualCheckCompP->Draw("ACP");
	EffMCQualCheckP->Draw("CPsame");	
	return;
}	
