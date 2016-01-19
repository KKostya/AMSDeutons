TCanvas * c26 = new TCanvas("Latitude pile-up correction");

TH2F * PCountsgeo = new TH2F("PCountsgeo","PCountsgeo",43,0,43,11,0,11);
TH2F * PCountsgeo_prim = new TH2F("PCountsgeo_prim","PCountsgeo_prim",43,0,43,11,0,11);

TH2F * CorrLAT_totM1= new TH2F("CorrLAT_totM1","CorrLAT_totM1",43,0,43,2,0,2);
TH2F * CorrLAT_totM2= new TH2F("CorrLAT_totM2","CorrLAT_totM2",43,0,43,2,0,2);

TH2F * CorrLAT_preM2= new TH2F("CorrLAT_preM2","CorrLAT_preM2",43,0,43,2,0,2);

TH2F * CorrLAT_tot_spl= new TH2F("CorrLAT_tot_spl","CorrLAT_tot_spl",11,0,11,2,0,2);
TH2F * CorrLAT_pre_spl= new TH2F("CorrLAT_pre_spl","CorrLAT_pre_spl",11,0,11,2,0,2);

void CorrLAT(TFile * file1){
	cout<<"******* LAT CORRECTION *************"<<endl;
	float CorrLAT_tot[11]={1,1,1,1,1,1,1,1,1,1,1};
	float CorrLAT_tot_err[11]={0};
	
	float CorrLAT_Pre[11]={1,1,1,1,1,1,1,1,1,1,1};
        float CorrLAT_Pre_err[11]={0};

	for(int m=0;m<11;m++) {
		for(int S=0;S<3;S++) CorrLAT_tot[m]*=CorrLAT_pre[S]->Eval(geomagC[m]);
		for(int S=0;S<3;S++) CorrLAT_Pre[m]*=CorrLAT_pre[S]->Eval(geomagC[m]);
		CorrLAT_tot[m]*=CorrLAT_Lik->Eval(geomagC[m]);
		CorrLAT_tot[m]*=CorrLAT_Dist->Eval(geomagC[m]);
		
		for(int S=0;S<3;S++) CorrLAT_tot_err[m]+=pow(CorrLATpre_spl[S]->GetBinContent(m+1,2)/CorrLATpre_spl[S]->GetBinContent(m+1,1),2);
		for(int S=0;S<3;S++) CorrLAT_Pre_err[m]+=pow(CorrLATpre_spl[S]->GetBinContent(m+1,2)/CorrLATpre_spl[S]->GetBinContent(m+1,1),2);
		CorrLAT_tot_err[m]+=pow(CorrLAT_Lik_spl->GetBinContent(m+1,2)/CorrLAT_Lik_spl->GetBinContent(m+1,1),2);
		CorrLAT_tot_err[m]+=pow(CorrLAT_Dist_spl->GetBinContent(m+1,2)/CorrLAT_Dist_spl->GetBinContent(m+1,1),2);
		CorrLAT_tot_err[m]=pow(CorrLAT_tot_err[m],0.5)*CorrLAT_tot[m];
		CorrLAT_Pre_err[m]=pow(CorrLAT_Pre_err[m],0.5)*CorrLAT_Pre[m];
		}		
	
	/// METODO 1
	float uno,unopre=0;
	float due=0;

	for(int i=0;i<43;i++){
		uno=0;
        	unopre=0;
		due=0;
		for(int m=0;m<11;m++){
				uno+=PCountsgeo_prim->GetBinContent(i+1,m+1)*CorrLAT_tot[m];
				due+=PCountsgeo_prim->GetBinContent(i+1,m+1);
		}
		CorrLAT_totM1->SetBinContent(i+1,1,uno/due);	
	}

	//METODO 2
	float Espos_R[43]={0};	
	float CorrLATtotM2[43]={0};
	float CorrLATpreM2[43]={0};
	float CorrLATtotM2_err[43]={0};
	float CorrLATpreM2_err[43]={0};
	for(int i=0;i<43;i++){
			for(int m=1;m<11;m++) Espos_R[i]+=esposizionegeo->GetBinContent(i,m);
			for(int m=0;m<11;m++) CorrLATtotM2[i]+=CorrLAT_tot[m]*esposizionegeo->GetBinContent(i,m)/Espos_R[i];
			for(int m=0;m<11;m++) CorrLATtotM2_err[i]+=pow(CorrLAT_tot_err[m]*esposizionegeo->GetBinContent(i,m)/Espos_R[i],2); 
			for(int m=0;m<11;m++) CorrLATpreM2[i]+=CorrLAT_Pre[m]*esposizionegeo->GetBinContent(i,m)/Espos_R[i];
			for(int m=0;m<11;m++) CorrLATpreM2_err[i]+=pow(CorrLAT_Pre_err[m]*esposizionegeo->GetBinContent(i,m)/Espos_R[i],2);

		}
	
	for(int i=0;i<43;i++) CorrLATtotM2_err[i]=pow(CorrLATtotM2_err[i],0.5);
	for(int i=0;i<43;i++) CorrLATpreM2_err[i]=pow(CorrLATpreM2_err[i],0.5);
	for(int i=0;i<43;i++) CorrLAT_totM2->SetBinContent(i+1,1,CorrLATtotM2[i]);
	for(int i=0;i<43;i++) CorrLAT_preM2->SetBinContent(i+1,1,CorrLATpreM2[i]);
	for(int i=0;i<43;i++) CorrLAT_totM2->SetBinContent(i+1,2,CorrLATtotM2_err[i]);
        for(int i=0;i<43;i++) CorrLAT_preM2->SetBinContent(i+1,2,CorrLATpreM2_err[i]);
	
	c26->Divide(1,2);
	c26->cd(1);
	gPad->SetGridy();
        gPad->SetGridx();
	TGraphErrors *CorrLAT_tot_Spl=new TGraphErrors();
	for(int m=0;m<11;m++) {
		CorrLAT_tot_spl->SetBinContent(m+1,0,CorrLAT_tot[m]);
		CorrLAT_tot_spl->SetBinContent(m+1,1,CorrLAT_tot_err[m]);
		CorrLAT_tot_Spl->SetPoint(m,geomagC[m],CorrLAT_tot[m]);
		CorrLAT_tot_Spl->SetPointError(m,0,CorrLAT_tot_err[m]);
	}
	CorrLAT_tot_Spl->SetLineColor(1);
	CorrLAT_tot_Spl->SetMarkerColor(1);
	CorrLAT_tot_Spl->SetLineWidth(2);
	CorrLAT_tot_Spl->SetMarkerStyle(8);
	CorrLAT_tot_Spl->SetFillStyle(3002);
	CorrLAT_tot_Spl->GetXaxis()->SetTitle("Latitude");
        CorrLAT_tot_Spl->GetYaxis()->SetTitle("Eff. Corr. Factor");
	CorrLAT_tot_Spl->Draw("APC");
	
	c26->cd(2);
        gPad->SetGridy();
        gPad->SetGridx();
	gPad->SetLogx();
	TGraphErrors *CorrLAT_totM1_Spl=new TGraphErrors();
	for(int i=0;i<43;i++){
		CorrLAT_totM1_Spl->SetPoint(i,R_cent[i],CorrLAT_totM1->GetBinContent(i+1,1));
	}
	CorrLAT_totM1_Spl->SetLineColor(2);
        CorrLAT_totM1_Spl->SetMarkerColor(2);
        CorrLAT_totM1_Spl->SetLineWidth(2);
        CorrLAT_totM1_Spl->SetMarkerStyle(8);
        CorrLAT_totM1_Spl->SetFillStyle(3002);
	CorrLAT_totM1_Spl->GetXaxis()->SetTitle("R [GV]");
        CorrLAT_totM1_Spl->GetYaxis()->SetTitle("Eff. Corr. Factor");
	CorrLAT_totM1_Spl->Draw("APC");
	TGraphErrors *CorrLAT_totM2_Spl=new TGraphErrors();
        for(int i=0;i<43;i++){
                CorrLAT_totM2_Spl->SetPoint(i,R_cent[i],CorrLAT_totM2->GetBinContent(i+1,1));
        }
        CorrLAT_totM2_Spl->SetLineColor(4);
        CorrLAT_totM2_Spl->SetMarkerColor(4);
        CorrLAT_totM2_Spl->SetLineWidth(2);
        CorrLAT_totM2_Spl->SetMarkerStyle(8);
        CorrLAT_totM2_Spl->SetFillStyle(3002);
	CorrLAT_totM2_Spl->Draw("PCsame");
	return;
}
