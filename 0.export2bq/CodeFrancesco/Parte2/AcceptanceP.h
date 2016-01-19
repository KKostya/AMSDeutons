using namespace std;

TCanvas * c22 = new TCanvas("Protons Acceptance");

TH2F * AcceptPzone = new TH2F("AcceptPzone","AcceptPzone",43,0,43,11,0,11);
TH2F * AcceptPzone_pre = new TH2F("AcceptPzone_pre","AcceptPzone_pre",43,0,43,11,0,11);

void AcceptanceP(TFile * file1){

	float AcceptgeoP[43]={0};
	float AcceptSelMCP[43]={0};
	float AcceptSelP[43][11]={0};
	float AcceptpreP[43][11]={0};	

	float eventiprova=0;
	for(int i=1;i<43;i++) eventiprova+=EffTriggMCP1_R->GetBinContent(i+1);
	float triggerbin=(pow(0.0308232619,-1))*eventiprova/43;
	for(int i=0;i<43;i++) 
		AcceptgeoP[i]=EffTriggerMCP_R_TH1F->GetBinContent(i+1)*EffTOF_MCP_R_TH1F->GetBinContent(i+1)*EffTriggMCP1_R->GetBinContent(i+1)/triggerbin*47.78;
	for(int j=0;j<11;j++) 
		for(int i=0;i<43;i++)	{
			//AcceptSelP[i][j]=AcceptgeoP[i]*EffTrackerMCP_R_TH1F->GetBinContent(i+1);
			//for(int S=0;S<3;S++) AcceptSelP[i][j]*=EffPreSelMCP_R_TH2F->GetBinContent(i+1,S+1);
			AcceptSelP[i][j]=EffPreMCP_R_TH1F->GetBinContent(i+1)*EffTriggMCP1_R->GetBinContent(i+1)/triggerbin*47.78;
			AcceptSelP[i][j]=AcceptSelP[i][j]*EffUnbDATA_R_TH1F->GetBinContent(i+1);
			AcceptpreP[i][j]=AcceptSelP[i][j];
			AcceptSelP[i][j]*=EffLik2CheckMCP_TH1F->GetBinContent(i+1,1)*EffDistCheckMCP_TH1F->GetBinContent(i+1,1);
			AcceptSelMCP[i]=AcceptSelP[i][j];
			// Data-driven corrections
			//latitude
			for(int S=0;S<3;S++) AcceptSelP[i][j]/=CorrLAT_pre[S]->Eval(geomagC[j]);
			for(int S=0;S<3;S++) AcceptpreP[i][j]/=CorrLAT_pre[S]->Eval(geomagC[j]);
			AcceptSelP[i][j]/=CorrLAT_Lik->Eval(geomagC[j])*CorrLAT_Dist->Eval(geomagC[j]);
			//DvsMC
			for(int S=0;S<3;S++) AcceptSelP[i][j]*=PreDVSMC_P[S]->GetBinContent(i+1,1);
			for(int S=0;S<3;S++) AcceptpreP[i][j]*=PreDVSMC_P[S]->GetBinContent(i+1,1);		
			AcceptSelP[i][j]*=DistDVSMC_P->Eval(R_cent[i])*LikDVSMC_P->Eval(R_cent[i]);	
			}	
	c22->cd();
	gPad->SetLogx();
        gPad->SetGridx();
        gPad->SetGridy();
	TGraphErrors * AccgeoP= new TGraphErrors();
	TGraphErrors * AccSelMCP= new TGraphErrors();
	TGraphErrors * AccSelP[11];
	TGraphErrors * AccpreP[11];
	for(int i=0;i<43;i++) AccgeoP->SetPoint(i,R_cent[i],AcceptgeoP[i]);	
	for(int i=0;i<43;i++) AccSelMCP->SetPoint(i,R_cent[i],AcceptSelMCP[i]);
	
	for(int j=0;j<11;j++) for(int i=0;i<43;i++) AcceptPzone->SetBinContent(i+1,j+1,AcceptSelP[i][j]);
	for(int j=0;j<11;j++) for(int i=0;i<43;i++) AcceptPzone_pre->SetBinContent(i+1,j+1,AcceptpreP[i][j]);

	for(int j=0;j<11;j++) {
		AccSelP[j]=new TGraphErrors();
		for(int i=0;i<43;i++) AccSelP[j]->SetPoint(i,R_cent[i],AcceptSelP[i][j]);
		AccSelP[j]->SetMarkerStyle(8);
        	AccSelP[j]->SetMarkerColor(j-1);
        	AccSelP[j]->SetLineColor(j-1);
        	AccSelP[j]->SetLineWidth(2);
	}
	for(int j=0;j<11;j++) {
                AccpreP[j]=new TGraphErrors();
                for(int i=0;i<43;i++) AccpreP[j]->SetPoint(i,R_cent[i],AcceptpreP[i][j]);
                AccpreP[j]->SetMarkerStyle(8);
                AccpreP[j]->SetMarkerColor(j-1);
                AccpreP[j]->SetLineColor(j-1);
                AccpreP[j]->SetLineWidth(2);
        }

	AccgeoP->SetMarkerStyle(8);
	AccgeoP->SetMarkerColor(2);
	AccgeoP->SetLineColor(2);
	AccgeoP->SetLineWidth(2);
	AccSelMCP->SetMarkerStyle(8);
        AccSelMCP->SetMarkerColor(1);
        AccSelMCP->SetLineColor(1);
        AccSelMCP->SetLineWidth(3);
	AccgeoP->SetTitle("Protons Acceptance");
        AccgeoP->GetXaxis()->SetTitle("R [GV]");
        AccgeoP->GetYaxis()->SetTitle("Acceptance [m^2 sr]");
        AccgeoP->GetXaxis()->SetTitleSize(0.045);
        AccgeoP->GetYaxis()->SetTitleSize(0.045);
	AccgeoP->Draw("AC");
	for(int j=0;j<11;j++) AccSelP[j]->Draw("PCsame");
	for(int j=0;j<11;j++) AccpreP[j]->Draw("PCsame");
	AccSelMCP->Draw("Csame");
}

