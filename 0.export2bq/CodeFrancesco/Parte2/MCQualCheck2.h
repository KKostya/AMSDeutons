using namespace std;

TCanvas *c19=new TCanvas("EdepL1 Quality Sel. Check");

TH1F * EffDistCheckMCP1 = new TH1F("EffDistCheckMCP1","EffDistCheckMCP1",43,0,43);
TH1F * EffDistCheckMCP2 = new TH1F("EffDistCheckMCP2","EffDistCheckMCP2",43,0,43);
TH1F * EffLik2CheckMCP1 = new TH1F("EffLik2CheckMCP1","EffLik2CheckMCP1",43,0,43);
TH1F * EffLik2CheckMCP2 = new TH1F("EffLik2CheckMCP2","EffLik2CheckMCP2",43,0,43);

TH2F * EffLik2CheckMCP_TH1F = new TH2F("EffLik2CheckMCP_TH1F","EffLik2CheckMCP_TH1F",43,0,43,2,0,2);
TH2F * EffDistCheckMCP_TH1F = new TH2F("EffDistCheckMCP_TH1F","EffDistCheckMCP_TH1F",43,0,43,2,0,2);

void MCQualCheck2_Fill(TNtuple *ntupla, int l){

	int k = ntupla->GetEvent(l);
	if(Beta<=0||R<=0||Beta>protons->Eval(R)+0.1||Beta<protons->Eval(R)-0.1) return;
	if(Massa_gen<1){
		if(EdepL1<EdepL1beta->Eval(Beta)+0.2&&EdepL1>EdepL1beta->Eval(Beta)-0.2){
			for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]) {EffDistCheckMCP2->Fill(K);}
			if(Dist5D_P<6)
				for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]) {EffDistCheckMCP1->Fill(K);}

			if(Dist5D_P<6){
				for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]) {EffLik2CheckMCP2->Fill(K);}
				if(LDiscriminant>0.7)
					for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]) {EffLik2CheckMCP1->Fill(K);}
			}
		}
	}
	return;
}

void MCQualCheck2_Copy(TFile * file1){
	EffDistCheckMCP1 = (TH1F *)file1->Get("EffDistCheckMCP1");
	EffDistCheckMCP2 = (TH1F *)file1->Get("EffDistCheckMCP2");
	EffLik2CheckMCP1 = (TH1F *)file1->Get("EffLik2CheckMCP1");
	EffLik2CheckMCP2 = (TH1F *)file1->Get("EffLik2CheckMCP2");
	return;
}

void MCQualCheck2(TFile * file1){
        cout<<"**** EDEP L1 MC QUALITY SEL. CHECK ****"<<endl;
	float EffDistCheckP[43]={0};
        for(int i=1;i<43;i++) EffDistCheckP[i]=EffDistCheckMCP1->GetBinContent(i+1)/(float)EffDistCheckMCP2->GetBinContent(i+1);
	float EffLik2CheckP[43]={0};
        for(int i=1;i<43;i++) EffLik2CheckP[i]=EffLik2CheckMCP1->GetBinContent(i+1)/(float)EffLik2CheckMCP2->GetBinContent(i+1);	
	
	c19->cd();
        gPad->SetLogx();
        gPad->SetGridx();
        gPad->SetGridy();
        TGraph *EffMCQualCheck2P= new TGraph();
        TGraph *EffMCQualCheckComp2P= new TGraph();
        int j=0;
        for(int i=1;i<43;i++) {EffMCQualCheck2P->SetPoint(j,R_cent[i],EffQualCheckMCP_TH1F->GetBinContent(i+1));j++;}
        for(int i=1;i<43;i++) {EffMCQualCheckComp2P->SetPoint(j,R_cent[i],EffLik2CheckP[i]*EffDistCheckP[i]);j++;}
	for(int i=1;i<43;i++) EffLik2CheckMCP_TH1F->SetBinContent(i,1,EffLik2CheckP[i]);
	for(int i=1;i<43;i++) EffLik2CheckMCP_TH1F->SetBinContent(i,2,EffLik2CheckP[i]*pow(EffLik2CheckMCP1->GetBinContent(i+1),0.5)/EffLik2CheckMCP1->GetBinContent(i+1));
	for(int i=1;i<43;i++) EffDistCheckMCP_TH1F->SetBinContent(i,1,EffDistCheckP[i]);
	for(int i=1;i<43;i++) EffDistCheckMCP_TH1F->SetBinContent(i,2,EffDistCheckP[i]*pow(EffDistCheckMCP1->GetBinContent(i+1),0.5)/EffDistCheckMCP1->GetBinContent(i+1));
        EffMCQualCheck2P->SetMarkerColor(2);
        EffMCQualCheck2P->SetMarkerStyle(8);
        EffMCQualCheck2P->SetLineColor(2);
        EffMCQualCheck2P->SetLineWidth(2);
        EffMCQualCheckComp2P->SetMarkerColor(2);
        EffMCQualCheckComp2P->SetMarkerStyle(4);
        EffMCQualCheckComp2P->SetLineColor(2);
        EffMCQualCheckComp2P->SetLineWidth(2);
	EffMCQualCheckComp2P->Draw("ACP");
	EffMCQualCheck2P->Draw("CPsame");	
	return;
}	
