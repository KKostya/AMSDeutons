using namespace std;

TCanvas *c11=new TCanvas("Unbias Trigger Efficiency");

TH1F * EffUnbiasMCP1=new TH1F("EffUnbiasMCP1","EffUnbiasMCP1",18,0,18);
TH1F * EffUnbiasMCP2=new TH1F("EffUnbiasMCP2","EffUnbiasMCP2",18,0,18);
TH1F * EffUnbiasMCP1_R=new TH1F("EffUnbiasMCP1_R","EffUnbiasMCP1_R",43,0,43);
TH1F * EffUnbiasMCP2_R=new TH1F("EffUnbiasMCP2_R","EffUnbiasMCP2_R",43,0,43);
TH2F * EffUnbiasMCD1=new TH2F("EffUnbiasMCD1","EffUnbiasMCD1",18,0,18,6,0,6);
TH2F * EffUnbiasMCD2=new TH2F("EffUnbiasMCD2","EffUnbiasMCD2",18,0,18,6,0,6);
TH2F * EffUnbiasMCD1_R=new TH2F("EffUnbiasMCD1_R","EffUnbiasMCD1_R",43,0,43,6,0,6);
TH2F * EffUnbiasMCD2_R=new TH2F("EffUnbiasMCD2_R","EffUnbiasMCD2_R",43,0,43,6,0,6);

TH1F *EffUnbMCP_R_TH1F = new TH1F("EffUnbMCP_R_TH1F","EffUnbMCP_R_TH1F",43,0,43);
TH1F *EffUnbMCP_TH1F = new TH1F("EffUnbMCP_TH1F","EffUnbMCP_TH1F",18,0,18);
TH2F *EffUnbMCD_R_TH2F = new TH2F("EffUnbMCD_R_TH2F","EffUnbMCD_R_TH2F",43,0,43,6,0,6);
TH2F *EffUnbMCD_TH2F = new TH2F("EffUnbMCD_TH2F","EffUnbMCD_TH2F",18,0,18,6,0,6);



void MCUnbiaseff_Fill(TNtuple *ntupla, int l){
		int k = ntupla->GetEvent(l);
		if((Cutmask&187)!=187||Beta_pre<=0||R_pre<=0) return;
		if(EdepTrack<EdepTrackbeta->Eval(Beta_pre)+0.2&&EdepTrack>EdepTrackbeta->Eval(Beta_pre)-0.2){
		if(Massa_gen<1&&Massa_gen>0.5) {
			for(int M=0;M<43;M++) if(fabs(Momento_gen)<bin[M+1]&&fabs(Momento_gen)>bin[M]) {
				EffUnbiasMCP1_R->Fill(M);
				if(Unbias==0) EffUnbiasMCP2_R->Fill(M);
			}	
			for(int m=0;m<18;m++)  if(Beta_gen>Betabins[m]&&Beta_gen<=Betabins[m+1]){
				EffUnbiasMCP1->Fill(m);
				if(Unbias==0) EffUnbiasMCP2->Fill(m);	
			}
		}				 

		if(Massa_gen>1&&Massa_gen<2) {
			for(int M=0;M<43;M++) if(fabs(Momento_gen)<bin[M+1]&&fabs(Momento_gen)>bin[M]) {
				EffUnbiasMCD1_R->Fill(M,(int)(10000*Massa_gen-18570));
				if(Unbias==0) EffUnbiasMCD2_R->Fill(M,(int)(10000*Massa_gen-18570));
			}
			for(int m=0;m<18;m++) if(Beta_gen>Betabins[m]&&Beta_gen<=Betabins[m+1]){
				EffUnbiasMCD1->Fill(m,(int)(10000*Massa_gen-18570));
				if(Unbias==0) EffUnbiasMCD2->Fill(m,(int)(10000*Massa_gen-18570));
			}
		}
		}
	return;
}

void MCUnbiaseff_Copy(TFile * file){
	EffUnbiasMCP1= (TH1F*) file->Get("EffUnbiasMCP1");
        EffUnbiasMCD1= (TH2F*) file->Get("EffUnbiasMCD1");
        EffUnbiasMCP2= (TH1F*) file->Get("EffUnbiasMCP2");
        EffUnbiasMCD2= (TH2F*) file->Get("EffUnbiasMCD2");
        EffUnbiasMCP1_R =(TH1F*) file->Get("EffUnbiasMCP1_R");
        EffUnbiasMCD1_R =(TH2F*) file->Get("EffUnbiasMCD1_R");
        EffUnbiasMCP2_R =(TH1F*) file->Get("EffUnbiasMCP2_R");
        EffUnbiasMCD2_R =(TH2F*) file->Get("EffUnbiasMCD2_R");
                                                               	
	return;	
}

void MCUnbiaseff(TFile * file1){

	string nome;
	Tempi = (TH1F *)file1->Get("Tempi");

	cout<<"**** MC Unbias TRIGGER EFF. ****"<<endl;
	c11->Divide(2,1);
        float EffUnbiasMCP[18]={0};
        for(int i=0;i<17;i++) if(EffUnbiasMCP1->GetBinContent(i+1)>0) if(EffUnbiasMCP2->GetBinContent(i+1)<EffUnbiasMCP1->GetBinContent(i+1))
                EffUnbiasMCP[i]=EffUnbiasMCP2->GetBinContent(i+1)/(float)EffUnbiasMCP1->GetBinContent(i+1);
        float EffUnbiasMCD[18][6]={{0}};
        for(int i=0;i<17;i++) for(int h=0;h<6;h++) if(EffUnbiasMCD2->GetBinContent(i+1,h+1)<EffUnbiasMCD1->GetBinContent(i+1,h+1))
                EffUnbiasMCD[i][h]=EffUnbiasMCD2->GetBinContent(i+1,h+1)/(float)EffUnbiasMCD1->GetBinContent(i+1,h+1);

        float EffUnbiasMCP_R[43]={0};
        for(int i=1;i<43;i++) EffUnbiasMCP_R[i]=EffUnbiasMCP2_R->GetBinContent(i+1)/(float)EffUnbiasMCP1_R->GetBinContent(i+1);
        float EffUnbiasMCD_R[43][6]={{0}};
        for(int i=4;i<43;i++) for(int h=0;h<6;h++) if(EffUnbiasMCD1_R->GetBinContent(i+1,h+1)>EffUnbiasMCD2_R->GetBinContent(i+1,h+1))
                EffUnbiasMCD_R[i][h]=EffUnbiasMCD2_R->GetBinContent(i+1,h+1)/(float)EffUnbiasMCD1_R->GetBinContent(i+1,h+1);


	c11->cd(1);
        gPad->SetLogx();
        gPad->SetGridx();
        gPad->SetGridy();
        string MCLegend[7]={"protons.B800","d.pl1.0_520_GG_Blic","d.pl1.0_520_GG_BlicDPMJet","d.pl1.0_520_GG_QMD","d.pl1.0_520_Shen_Blic","d.pl1.0_520_Shen_BlicDPMJet","d.pl1.0_520_Shen_QMD"};
        TGraph * EffUnbMCP_R = new TGraph();
        EffUnbMCP_R->SetTitle(MCLegend[0].c_str());
        for(int i=0;i<43;i++) EffUnbMCP_R->SetPoint(i,R_cent[i],EffUnbiasMCP_R[i]);
        for(int i=0;i<43;i++) EffUnbMCP_R_TH1F->SetBinContent(i+1,EffUnbiasMCP_R[i]);
        TGraph * EffUnbMCD_R[6];
        EffUnbMCP_R->SetMarkerColor(2);
        EffUnbMCP_R->SetMarkerStyle(8);
        EffUnbMCP_R->SetLineColor(2);
        EffUnbMCP_R->SetLineWidth(2);
        EffUnbMCP_R->SetTitle("Preselections Efficiency MC (R bins)");
        EffUnbMCP_R->GetXaxis()->SetTitle("R [GV]");
        EffUnbMCP_R->GetYaxis()->SetTitle("Pres. Efficiency");
        EffUnbMCP_R->GetXaxis()->SetTitleSize(0.045);
        EffUnbMCP_R->GetYaxis()->SetTitleSize(0.045);
        {
                EffUnbMCP_R->Draw("ACP");
                TLegend* leg =new TLegend(0.4, 0.7,0.95,0.95);
                leg->AddEntry(EffUnbMCP_R,MCLegend[0].c_str(), "ep");

                for(int h=0;h<6;h++){
                        EffUnbMCD_R[h]= new TGraph();
                        EffUnbMCD_R[h]->SetTitle(MCLegend[h+1].c_str());
                        for(int i=1;i<43;i++) EffUnbMCD_R[h]->SetPoint(i,R_cent[i],EffUnbiasMCD_R[i][h]);
                        for(int i=1;i<43;i++) EffUnbMCD_R_TH2F->SetBinContent(i+1,h+1,EffUnbiasMCD_R[i][h]);
                        leg->AddEntry(EffUnbMCD_R[h],MCLegend[h+1].c_str(), "ep");
                        EffUnbMCD_R[h]->SetMarkerColor(4);
                        EffUnbMCD_R[h]->SetMarkerStyle(h+3);
                        EffUnbMCD_R[h]->SetMarkerSize(2);
                        EffUnbMCD_R[h]->SetLineColor(4);
                        EffUnbMCD_R[h]->SetLineWidth(2);
                        EffUnbMCD_R[h]->Draw("Psame");
                        leg->Draw();
                }
        }

        c11->cd(2);
        gPad->SetLogx();
        gPad->SetGridx();
        gPad->SetGridy();
        TGraph * EffUnbMCP = new TGraph();
        for(int i=0;i<17;i++) EffUnbMCP->SetPoint(i,Ekincent[i],EffUnbiasMCP[i]);
        for(int i=0;i<17;i++) EffUnbMCP_TH1F->SetBinContent(i+1,EffUnbiasMCP[i]);
        TGraph * EffUnbMCD[6];
        EffUnbMCP->SetMarkerColor(2);
        EffUnbMCP->SetMarkerStyle(8);
        EffUnbMCP->SetLineColor(2);
        EffUnbMCP->SetLineWidth(2);
        EffUnbMCP->SetTitle("Preselections Efficiency MC (Beta bins)");
        EffUnbMCP->GetXaxis()->SetTitle("Kin. En. / nucl. [GeV/nucl.]");
        EffUnbMCP->GetYaxis()->SetTitle("Pres. Efficiency");
        EffUnbMCP->GetXaxis()->SetTitleSize(0.045);
        EffUnbMCP->GetYaxis()->SetTitleSize(0.045);
        {
                EffUnbMCP->Draw("ACP");
                TLegend* leg =new TLegend(0.4, 0.7,0.95,0.95);
                leg->AddEntry(EffUnbMCP,MCLegend[0].c_str(), "ep");

                for(int h=0;h<6;h++){
                        EffUnbMCD[h]= new TGraph();
                        for(int i=0;i<17;i++) EffUnbMCD[h]->SetPoint(i,Ekincent[i],EffUnbiasMCD[i][h]);
                        for(int i=0;i<17;i++) EffUnbMCD_TH2F->SetBinContent(i+1,h+1,EffUnbiasMCD[i][h]);
                        EffUnbMCD[h]->SetMarkerColor(4);
                        EffUnbMCD[h]->SetMarkerStyle(h+3);
                        leg->AddEntry(EffUnbMCD[h],MCLegend[h+1].c_str(), "ep");
                        EffUnbMCD[h]->SetMarkerSize(2);
                        EffUnbMCD[h]->SetLineColor(4);
                        EffUnbMCD[h]->SetLineWidth(2);
                        EffUnbMCD[h]->Draw("Psame");
                        leg->Draw();
                }
        }

}
