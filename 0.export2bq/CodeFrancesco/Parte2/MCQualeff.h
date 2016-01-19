using namespace std;

TCanvas *c5=new TCanvas("Likelihood Efficiency on Top of Preselections");
TCanvas *c6=new TCanvas("Distance Efficiency on Top of Preselections");

TH1F * EffDistMCP = new TH1F("EffDistMCP","EffDistMCP",43,0,43);
TH1F * EffLikMCP = new TH1F("EffLikMCP","EffLikMCP",43,0,43);
TH1F * EffDistMCP_Beta = new TH1F("EffDistMCP_Beta","EffDistMCP_Beta",18,0,18);
TH1F * EffLikMCP_Beta = new TH1F("EffLikMCP_Beta","EffLikMCP_Beta",18,0,18);
TH2F * EffDistMCD = new TH2F("EffDistMCD","EffDistMCD",43,0,43,6,0,6);
TH2F * EffLikMCD = new TH2F("EffLikMCD","EffLikMCD",43,0,43,6,0,6);
TH2F * EffDistMCD_Beta = new TH2F("EffDistMCD_Beta","EffDistMCD_Beta",18,0,18,6,0,6);
TH2F * EffLikMCD_Beta = new TH2F("EffLikMCD_Beta","EffLikMCD_Beta",18,0,18,6,0,6);


TH1F * EffQualMCP = new TH1F("EffQualMCP","EffQualMCP",43,0,43);
TH1F * EffQualMCP_Beta = new TH1F("EffQualMCP_Beta","EffQualMCP_Beta",18,0,18);
TH2F * EffQualMCD = new TH2F("EffQualMCD","EffQualMCD",43,0,43,6,0,6);
TH2F * EffQualMCD_Beta = new TH2F("EffQualMCD_Beta","EffQualMCD_Beta",18,0,18,6,0,6);

TH1F * EffMCLikP_TH1F = new TH1F("EffMCLikP_TH1F","EffMCLikP_TH1F",43,0,43);
TH2F * EffMCLikD_TH2F = new TH2F("EffMCLikD_TH2F","EffMCLikD_TH2F",43,0,43,6,0,6);
TH1F * EffMCLikP_Beta_TH1F = new TH1F("EffMCLikP_Beta_TH1F","EffMCLikP_Beta_TH1F",18,0,18);
TH2F * EffMCLikD_Beta_TH2F = new TH2F("EffMCLikD_Beta_TH2F","EffMCLikD_Beta_TH2F",18,0,18,6,0,6);

TH1F * EffMCDistP_TH1F = new TH1F("EffMCDistP_TH1F","EffMCDistP_TH1F",43,0,43);
TH2F * EffMCDistD_TH2F = new TH2F("EffMCDistD_TH2F","EffMCDistD_TH2F",43,0,43,6,0,6);
TH1F * EffMCDistP_Beta_TH1F = new TH1F("EffMCDistP_Beta_TH1F","EffMCDistP_Beta_TH1F",18,0,18);
TH2F * EffMCDistD_Beta_TH2F = new TH2F("EffMCDistD_Beta_TH2F","EffMCDistD_Beta_TH2F",18,0,18,6,0,6);

void MCQualeff_Fill(TNtuple *ntupla, int l){
	
	int k = ntupla->GetEvent(l);
	if(Beta<=0||R<=0) return;
	
	if(!(EdepL1<EdepL1beta->Eval(Beta)+0.2&&EdepL1>EdepL1beta->Eval(Beta)-0.2)) return;
	if(Massa_gen<1){
		for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]) {EffQualMCP->Fill(K);}
                for(int m=0;m<18;m++) if(Beta<Betabins[m+1]&&Beta>Betabins[m]) EffQualMCP_Beta->Fill(m);
		
		if(Dist5D_P<6) {
			for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]) {EffDistMCP->Fill(K);}
			for(int m=0;m<18;m++) if(Beta<Betabins[m+1]&&Beta>Betabins[m]) EffDistMCP_Beta->Fill(m);
		}
		if(LDiscriminant>0.7){
			for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]) {EffLikMCP->Fill(K);}
			for(int m=0;m<18;m++) if(Beta<Betabins[m+1]&&Beta>Betabins[m]) EffLikMCP_Beta->Fill(m);
		}
	}
	if(Massa_gen<2&&Massa_gen>1){
                for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]) {EffQualMCD->Fill(K,(int)(10000*Massa_gen-18570));}
                for(int m=0;m<18;m++) if(Beta<Betabins[m+1]&&Beta>Betabins[m]) EffQualMCD_Beta->Fill(m,(int)(10000*Massa_gen-18570));
		
		if(Dist5D<6) {
                        for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]) {EffDistMCD->Fill(K,(int)(10000*Massa_gen-18570));}
                        for(int m=0;m<18;m++) if(Beta<Betabins[m+1]&&Beta>Betabins[m]) EffDistMCD_Beta->Fill(m,(int)(10000*Massa_gen-18570));
                }
                if(LDiscriminant>0.7){
                        for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]) {EffLikMCD->Fill(K,(int)(10000*Massa_gen-18570));}
                        for(int m=0;m<18;m++) if(Beta<Betabins[m+1]&&Beta>Betabins[m]) EffLikMCD_Beta->Fill(m,(int)(10000*Massa_gen-18570));
                }
        }
	
	return;
}


void MCQualeff_Copy(TFile * file1){
	EffQualMCP = (TH1F *)file1->Get("EffQualMCP");
	EffQualMCP_Beta = (TH1F *)file1->Get("EffQualMCP_Beta");
	EffQualMCD = (TH2F *)file1->Get("EffQualMCD");
        EffQualMCD_Beta = (TH2F *)file1->Get("EffQualMCD_Beta");
	EffDistMCP = (TH1F *)file1->Get("EffDistMCP");
	EffLikMCP = (TH1F *)file1->Get("EffLikMCP");
	EffDistMCP_Beta = (TH1F *)file1->Get("EffDistMCP_Beta");
	EffLikMCP_Beta = (TH1F *)file1->Get("EffLikMCP_Beta");
	EffDistMCD = (TH2F *)file1->Get("EffDistMCD");
        EffLikMCD = (TH2F *)file1->Get("EffLikMCD");
        EffDistMCD_Beta = (TH2F *)file1->Get("EffDistMCD_Beta");
        EffLikMCD_Beta = (TH2F *)file1->Get("EffLikMCD_Beta");
	return;
}

void MCQualeff(TFile * file1){
	cout<<"**** MC QUALITY SEL. EFFICIENCIES ****"<<endl;		

	float EffLikP[43]={0};
	for(int i=1;i<43;i++) EffLikP[i]=EffLikMCP->GetBinContent(i+1)/(float)EffQualMCP->GetBinContent(i+1);
	float EffLikD[43][6]={{0}};
	for(int i=1;i<43;i++) for(int h=0;h<6;h++) if(EffQualMCD->GetBinContent(i+1,h+1)>0&&EffLikMCD->GetBinContent(i+1,h+1)<EffQualMCD->GetBinContent(i+1,h+1))
		EffLikD[i][h]=EffLikMCD->GetBinContent(i+1,h+1)/(float)EffQualMCD->GetBinContent(i+1,h+1);

	float EffDistP[43]={0};
	for(int i=1;i<43;i++) EffDistP[i]=EffDistMCP->GetBinContent(i+1)/(float)EffQualMCP->GetBinContent(i+1);
	float EffDistD[43][6]={{0}};
	for(int i=1;i<43;i++) for(int h=0;h<6;h++) if(EffQualMCD->GetBinContent(i+1,h+1)>0&&EffDistMCD->GetBinContent(i+1,h+1)<EffQualMCD->GetBinContent(i+1,h+1)) 
		EffDistD[i][h]=EffDistMCD->GetBinContent(i+1,h+1)/(float)EffQualMCD->GetBinContent(i+1,h+1);

	float EffLikP_Beta[18]={0};
	for(int i=0;i<17;i++) if(EffQualMCP_Beta->GetBinContent(i+1)>0) if(EffLikMCP_Beta->GetBinContent(i+1)<EffQualMCP_Beta->GetBinContent(i+1))
		EffLikP_Beta[i]=EffLikMCP_Beta->GetBinContent(i+1)/(float)EffQualMCP_Beta->GetBinContent(i+1);
	float EffLikD_Beta[18][6]={{0}};
	for(int i=0;i<17;i++) for(int h=0;h<6;h++) 
		if(EffQualMCD_Beta->GetBinContent(i+1,h+1)>0) if(EffLikMCD_Beta->GetBinContent(i+1,h+1)<EffQualMCD_Beta->GetBinContent(i+1,h+1))
			EffLikD_Beta[i][h]=EffLikMCD_Beta->GetBinContent(i+1,h+1)/(float)EffQualMCD_Beta->GetBinContent(i+1,h+1);	

	float EffDistP_Beta[18]={0};
	for(int i=0;i<17;i++) if(EffQualMCP_Beta->GetBinContent(i+1)>0) if(EffDistMCP_Beta->GetBinContent(i+1)<EffQualMCP_Beta->GetBinContent(i+1))
		EffDistP_Beta[i]=EffDistMCP_Beta->GetBinContent(i+1)/(float)EffQualMCP_Beta->GetBinContent(i+1);
	float EffDistD_Beta[18][6]={{0}};
	for(int i=0;i<17;i++) for(int h=0;h<6;h++) 
		if(EffQualMCD_Beta->GetBinContent(i+1,h+1)>0) if(EffDistMCD_Beta->GetBinContent(i+1,h+1)<EffQualMCD_Beta->GetBinContent(i+1,h+1))
			EffDistD_Beta[i][h]=EffDistMCD_Beta->GetBinContent(i+1,h+1)/(float)EffQualMCD_Beta->GetBinContent(i+1,h+1);	


	
	c5->Divide(2,1);
	c5->cd(1);
	string MCLegend[7]={"protons.B800","d.pl1.0_520_GG_Blic","d.pl1.0_520_GG_BlicDPMJet","d.pl1.0_520_GG_QMD","d.pl1.0_520_Shen_Blic","d.pl1.0_520_Shen_BlicDPMJet","d.pl1.0_520_Shen_QMD"};
	gPad->SetLogx();
        gPad->SetGridx();
        gPad->SetGridy();
	TGraph *EffMCLikP= new TGraph();
	TGraph *EffMCLikD[6];
	int j=0;
	for(int i=1;i<43;i++) {EffMCLikP->SetPoint(j,R_cent[i],EffLikP[i]);j++;}	
	for(int i=1;i<43;i++) EffMCLikP_TH1F->SetBinContent(i+1,EffLikP[i]);
	EffMCLikP->SetMarkerColor(2);
        EffMCLikP->SetMarkerStyle(8);
        EffMCLikP->SetLineColor(2);
        EffMCLikP->SetLineWidth(2);
        EffMCLikP->SetTitle("Likelihood Efficiency MC on top of Pres. (R bins)");
        EffMCLikP->GetXaxis()->SetTitle("R [GV]");
        EffMCLikP->GetYaxis()->SetTitle("Efficiency");
        EffMCLikP->GetXaxis()->SetTitleSize(0.045);
        EffMCLikP->GetYaxis()->SetTitleSize(0.045);
	{
                EffMCLikP->Draw("ACP");
                TLegend* leg =new TLegend(0.4, 0.7,0.95,0.95);
                leg->AddEntry(EffMCLikP,MCLegend[0].c_str(), "ep");

                for(int h=0;h<6;h++){
                        EffMCLikD[h]= new TGraph();
                        EffMCLikD[h]->SetTitle(MCLegend[h+1].c_str());
                        for(int i=1;i<43;i++) EffMCLikD[h]->SetPoint(i,R_cent[i],EffLikD[i][h]);
			for(int i=1;i<43;i++) EffMCLikD_TH2F->SetBinContent(i+1,h+1,EffLikD[i][h]);
			leg->AddEntry(EffMCLikD[h],MCLegend[h+1].c_str(), "ep");
                        EffMCLikD[h]->SetMarkerColor(4);
                        EffMCLikD[h]->SetMarkerStyle(h+3);
                        EffMCLikD[h]->SetMarkerSize(2);
                        EffMCLikD[h]->SetLineColor(4);
                        EffMCLikD[h]->SetLineWidth(1);
                        EffMCLikD[h]->Draw("Psame");
                        leg->Draw();
                } 
        }

	c5->cd(2);
        gPad->SetLogx();
        gPad->SetGridx();
        gPad->SetGridy();
        TGraph *EffMCLikP_Beta= new TGraph();
	TGraph *EffMCLikD_Beta[6];
        j=0;
        for(int i=0;i<17;i++) {EffMCLikP_Beta->SetPoint(j,Ekincent[i],EffLikP_Beta[i]);j++;}
	for(int i=0;i<17;i++) EffMCLikP_Beta_TH1F->SetBinContent(i+1,EffLikP_Beta[i]);
        EffMCLikP_Beta->SetMarkerColor(2);
        EffMCLikP_Beta->SetMarkerStyle(8);
        EffMCLikP_Beta->SetLineColor(2);
        EffMCLikP_Beta->SetLineWidth(2);
        EffMCLikP_Beta->SetTitle("Likelihood Efficiency MC on top of Pres. (Beta bins)");
        EffMCLikP_Beta->GetXaxis()->SetTitle("Kin. En.  [GeV/nucl.]");
        EffMCLikP_Beta->GetYaxis()->SetTitle("Efficiency");
        EffMCLikP_Beta->GetXaxis()->SetTitleSize(0.045);
        EffMCLikP_Beta->GetYaxis()->SetTitleSize(0.045);
	{
                EffMCLikP_Beta->Draw("ACP");
                TLegend* leg =new TLegend(0.4, 0.7,0.95,0.95);
                leg->AddEntry(EffMCLikP_Beta,MCLegend[0].c_str(), "ep");

                for(int h=0;h<6;h++){
                        EffMCLikD_Beta[h]= new TGraph();
                        EffMCLikD_Beta[h]->SetTitle(MCLegend[h+1].c_str());
                        for(int i=1;i<17;i++) EffMCLikD_Beta[h]->SetPoint(i,Ekincent[i],EffLikD_Beta[i][h]);
			for(int i=1;i<17;i++) EffMCLikD_Beta_TH2F->SetBinContent(i+1,h+1,EffLikD_Beta[i][h]);
                        leg->AddEntry(EffMCLikD_Beta[h],MCLegend[h+1].c_str(), "ep");
                        EffMCLikD_Beta[h]->SetMarkerColor(4);
                        EffMCLikD_Beta[h]->SetMarkerStyle(h+3);
                        EffMCLikD_Beta[h]->SetMarkerSize(2);
                        EffMCLikD_Beta[h]->SetLineColor(4);
                        EffMCLikD_Beta[h]->SetLineWidth(1);
                        EffMCLikD_Beta[h]->Draw("Psame");
                        leg->Draw();
                }
        }
	
	c6->Divide(2,1);
        c6->cd(1);
        gPad->SetLogx();
        gPad->SetGridx();
        gPad->SetGridy();
        TGraph *EffMCDistP= new TGraph();
	TGraph *EffMCDistD[6];
        j=0;
        for(int i=1;i<43;i++) {EffMCDistP->SetPoint(j,R_cent[i],EffDistP[i]);j++;}
	for(int i=1;i<43;i++) EffMCDistP_TH1F->SetBinContent(i+1,EffDistP[i]);
        EffMCDistP->SetMarkerColor(2);
        EffMCDistP->SetMarkerStyle(8);
        EffMCDistP->SetLineColor(2);
        EffMCDistP->SetLineWidth(2);
        EffMCDistP->SetTitle("Distance Efficiency MC on top of Pres. (R bins)");
        EffMCDistP->GetXaxis()->SetTitle("R [GV]");
        EffMCDistP->GetYaxis()->SetTitle("Efficiency");
        EffMCDistP->GetXaxis()->SetTitleSize(0.045);
        EffMCDistP->GetYaxis()->SetTitleSize(0.045);
	{
                EffMCDistP->Draw("ACP");
                TLegend* leg =new TLegend(0.4, 0.7,0.95,0.95);
                leg->AddEntry(EffMCDistP,MCLegend[0].c_str(), "ep");

                for(int h=0;h<6;h++){
                        EffMCDistD[h]= new TGraph();
                        EffMCDistD[h]->SetTitle(MCLegend[h+1].c_str());
                        for(int i=1;i<43;i++) EffMCDistD[h]->SetPoint(i,R_cent[i],EffDistD[i][h]);
                        for(int i=1;i<43;i++) EffMCDistD_TH2F->SetBinContent(i+1,h+1,EffDistD[i][h]);
			leg->AddEntry(EffMCDistD[h],MCLegend[h+1].c_str(), "ep");
                        EffMCDistD[h]->SetMarkerColor(4);
                        EffMCDistD[h]->SetMarkerStyle(h+3);
                        EffMCDistD[h]->SetMarkerSize(2);
                        EffMCDistD[h]->SetLineColor(4);
                        EffMCDistD[h]->SetLineWidth(1);
                        EffMCDistD[h]->Draw("Psame");
                        leg->Draw();
                }
        }

        c6->cd(2);
        gPad->SetLogx();
        gPad->SetGridx();
        gPad->SetGridy();
        TGraph *EffMCDistP_Beta= new TGraph();
        TGraph *EffMCDistD_Beta[6];
	j=0;
        for(int i=0;i<17;i++) {EffMCDistP_Beta->SetPoint(j,Ekincent[i],EffDistP_Beta[i]);j++;}
        for(int i=0;i<17;i++) EffMCDistP_Beta_TH1F->SetBinContent(j+1,EffDistP_Beta[i]);
	EffMCDistP_Beta->SetMarkerColor(2);
        EffMCDistP_Beta->SetMarkerStyle(8);
        EffMCDistP_Beta->SetLineColor(2);
        EffMCDistP_Beta->SetLineWidth(2);
        EffMCDistP_Beta->SetTitle("Distance Efficiency MC on top of Pres. (Beta bins)");
        EffMCDistP_Beta->GetXaxis()->SetTitle("Kin. En.  [GeV/nucl.]");
        EffMCDistP_Beta->GetYaxis()->SetTitle("Efficiency");
        EffMCDistP_Beta->GetXaxis()->SetTitleSize(0.045);
        EffMCDistP_Beta->GetYaxis()->SetTitleSize(0.045);
	{
                EffMCDistP_Beta->Draw("ACP");
                TLegend* leg =new TLegend(0.4, 0.7,0.95,0.95);
                leg->AddEntry(EffMCDistP_Beta,MCLegend[0].c_str(), "ep");

                for(int h=0;h<6;h++){
                        EffMCDistD_Beta[h]= new TGraph();
                        EffMCDistD_Beta[h]->SetTitle(MCLegend[h+1].c_str());
                        for(int i=1;i<17;i++) EffMCDistD_Beta[h]->SetPoint(i,Ekincent[i],EffDistD[i][h]);
			for(int i=1;i<17;i++) EffMCDistD_Beta_TH2F->SetBinContent(i+1,h+1,EffDistD[i][h]);
                        leg->AddEntry(EffMCDistD_Beta[h],MCLegend[h+1].c_str(), "ep");
                        EffMCDistD_Beta[h]->SetMarkerColor(4);
                        EffMCDistD_Beta[h]->SetMarkerStyle(h+3);
                        EffMCDistD_Beta[h]->SetMarkerSize(2);
                        EffMCDistD_Beta[h]->SetLineColor(4);
                        EffMCDistD_Beta[h]->SetLineWidth(1);
                        EffMCDistD_Beta[h]->Draw("Psame");
                        leg->Draw();
                }
        }

}


