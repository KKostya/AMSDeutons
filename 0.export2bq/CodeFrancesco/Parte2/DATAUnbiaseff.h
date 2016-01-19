using namespace std;

TCanvas *c12=new TCanvas("DATA: Unb. Trigger Efficiency");

TH1F * EffUnbiasDATA1=new TH1F("EffUnbiasDATA1","EffUnbiasDATA1",18,0,18);
TH1F * EffUnbiasDATA2=new TH1F("EffUnbiasDATA2","EffUnbiasDATA2",18,0,18);
TH1F * EffUnbiasDATA1_R=new TH1F("EffUnbiasDATA1_R","EffUnbiasDATA1_R",43,0,43);
TH1F * EffUnbiasDATA2_R=new TH1F("EffUnbiasDATA2_R","EffUnbiasDATA2_R",43,0,43);

TH1F *EffUnbDATA_R_TH1F = new TH1F("EffUnbDATA_R_TH1F","EffUnbDATA_R_TH1F",43,0,43);
TH1F *EffUnbDATA_TH1F = new TH1F("EffUnbDATA_TH1F","EffUnbDATA_TH1F",18,0,18);
                                    

void DATAUnbiaseff_Fill(TNtuple *ntupla, int l){
	int k = ntupla->GetEvent(l);
	if(((int)Cutmask&187)!=187||R_pre<=0||Beta_pre<=0||R_pre<1.2*Rcutoff) return;

	for(int M=0;M<43;M++) if(fabs(R_pre)<bin[M+1]&&fabs(R_pre)>bin[M]) {
		if(EdepTrack<EdepTrackbeta->Eval(Beta_pre)+0.2&&EdepTrack>EdepTrackbeta->Eval(Beta_pre)-0.2){
			EffUnbiasDATA2_R->Fill(M);
			if(Unbias==1) EffUnbiasDATA1_R->Fill(M);
		}
	}	
	for(int m=0;m<18;m++)  if(Beta_pre>Betabins[m]&&Beta_pre<=Betabins[m+1]){
		if(EdepTrack<EdepTrackbeta->Eval(Beta_pre)+0.2&&EdepTrack>EdepTrackbeta->Eval(Beta_pre)-0.2){
			EffUnbiasDATA2->Fill(m);
			if(Unbias==1) EffUnbiasDATA1->Fill(m);	
		}
	}

	return;
}

void DATAUnbiaseff_Copy(TFile * file){
        EffUnbiasDATA1= (TH1F*) file->Get("EffUnbiasDATA1");
        EffUnbiasDATA2= (TH1F*) file->Get("EffUnbiasDATA2");
        EffUnbiasDATA1_R =(TH1F*) file->Get("EffUnbiasDATA1_R");
        EffUnbiasDATA2_R =(TH1F*) file->Get("EffUnbiasDATA2_R");
                                                       	
	return;	
}

void DATAUnbiaseff(TFile * file1){

	cout<<"************************************************* DATA Unbias TRIGG. EFFICIENCy **********************************************************************"<<endl;
	c12->Divide(2,1);
        float EffUnbiasDATA[18]={0};
        for(int i=0;i<17;i++) if(EffUnbiasDATA1->GetBinContent(i+1)>0) 
                EffUnbiasDATA[i]=EffUnbiasDATA2->GetBinContent(i+1)/(EffUnbiasDATA2->GetBinContent(i+1)+100*(float)EffUnbiasDATA1->GetBinContent(i+1));
	float EffUnbiasDATA_R[43]={0};
        for(int i=1;i<43;i++) EffUnbiasDATA_R[i]=EffUnbiasDATA2_R->GetBinContent(i+1)/(EffUnbiasDATA2_R->GetBinContent(i+1)+100*(float)EffUnbiasDATA1_R->GetBinContent(i+1));

	 c12->cd(1);
        gPad->SetLogx();
        gPad->SetGridx();
        gPad->SetGridy();
        string MCLegend[2]={"protons","deutons"};
        TGraph * EffUnbDATA_R = new TGraph();
        EffUnbDATA_R->SetTitle(MCLegend[0].c_str());
        for(int i=0;i<43;i++) EffUnbDATA_R->SetPoint(i,R_cent[i],EffUnbiasDATA_R[i]);
        for(int i=0;i<43;i++) EffUnbDATA_R_TH1F->SetBinContent(i+1,EffUnbiasDATA_R[i]);
        TGraph * EffUnbMCD_R[6];
        EffUnbDATA_R->SetMarkerColor(2);
        EffUnbDATA_R->SetMarkerStyle(8);
        EffUnbDATA_R->SetLineColor(2);
        EffUnbDATA_R->SetLineWidth(2);
        EffUnbDATA_R->SetTitle("Preselections Efficiency MC (R bins)");
        EffUnbDATA_R->GetXaxis()->SetTitle("R [GV]");
        EffUnbDATA_R->GetYaxis()->SetTitle("Pres. Efficiency");
        EffUnbDATA_R->GetXaxis()->SetTitleSize(0.045);
        EffUnbDATA_R->GetYaxis()->SetTitleSize(0.045);
        {
                EffUnbDATA_R->Draw("ACP");
                TLegend* leg =new TLegend(0.4, 0.7,0.95,0.95);
                leg->AddEntry(EffUnbDATA_R,MCLegend[0].c_str(), "ep");

        }

        c12->cd(2);
        gPad->SetLogx();
        gPad->SetGridx();
        gPad->SetGridy();
        TGraph * EffUnbDATA = new TGraph();
        for(int i=0;i<17;i++) EffUnbDATA->SetPoint(i,Ekincent[i],EffUnbiasDATA[i]);
        for(int i=0;i<17;i++) EffUnbDATA_TH1F->SetBinContent(i+1,EffUnbiasDATA[i]);
        TGraph * EffUnbMCD[6];
        EffUnbDATA->SetMarkerColor(2);
        EffUnbDATA->SetMarkerStyle(8);
        EffUnbDATA->SetLineColor(2);
        EffUnbDATA->SetLineWidth(2);
        EffUnbDATA->SetTitle("Preselections Efficiency MC (Beta bins)");
        EffUnbDATA->GetXaxis()->SetTitle("Kin. En. / nucl. [GeV/nucl.]");
        EffUnbDATA->GetYaxis()->SetTitle("Pres. Efficiency");
        EffUnbDATA->GetXaxis()->SetTitleSize(0.045);
        EffUnbDATA->GetYaxis()->SetTitleSize(0.045);
        {
                EffUnbDATA->Draw("ACP");
                TLegend* leg =new TLegend(0.4, 0.7,0.95,0.95);
                leg->AddEntry(EffUnbDATA,MCLegend[0].c_str(), "ep");

        }


	
}
