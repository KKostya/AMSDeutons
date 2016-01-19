using namespace std;

TCanvas *c15=new TCanvas("Latitude Likelihood Efficiency");
TCanvas *c16=new TCanvas("Latitude Distance Efficiency");

TH2F * EffDistDATAP = new TH2F("EffDistDATAP","EffDistDATAP",43,0,43,11,0,11);
TH2F * EffLikDATAP = new TH2F("EffLikDATAP","EffLikDATAP",43,0,43,11,0,11);

TH2F * EffQualDATAP = new TH2F("EffQualDATAP","EffQualDATAP",43,0,43,11,0,11);

TF1 * CorrLAT_Lik;
TF1 * CorrLAT_Dist;

TH2F *CorrLAT_Lik_spl;
TGraphErrors *CorrLAT_Lik_Spl;

TH2F *CorrLAT_Dist_spl;
TGraphErrors *CorrLAT_Dist_Spl;


void DATAQualeff_Fill(TNtuple *ntupla, int l,int zona){

	int k = ntupla->GetEvent(l);
	if(Beta<=0||R<=0) return;
	if(!(EdepL1<EdepL1beta->Eval(Beta)+0.2&&EdepL1>EdepL1beta->Eval(Beta)-0.2)) return;
	for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]&&R>Rcut[zona]) {EffQualDATAP->Fill(K,zona);}

	if(Dist5D_P<6) {
		for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]&&R>Rcut[zona]) {EffDistDATAP->Fill(K,zona);}
	}
	if(Dist5D_P<6&&LDiscriminant>0.7){
		for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]&&R>Rcut[zona]) {EffLikDATAP->Fill(K,zona);}
	}

	return;
}


void DATAQualeff_Copy(TFile * file1){
	EffQualDATAP = (TH2F *)file1->Get("EffQualDATAP");
	EffDistDATAP = (TH2F *)file1->Get("EffDistDATAP");
	EffLikDATAP = (TH2F *)file1->Get("EffLikDATAP");
	return;
}


void DATAQualeff(TFile * file1){
	cout<<"********************************************************** DATA QUALITY SEL. EFFICIENCIES ************************************************************"<<endl;		
	c15->Divide(2,1);
	c16->Divide(2,1);
	float EffLikDATA[43][11]={{0}};
	for(int l=0;l<11;l++)
		for(int i=1;i<43;i++) 
			if(EffQualDATAP->GetBinContent(i+1,l+1)>0)
				EffLikDATA[i][l]=EffLikDATAP->GetBinContent(i+1,l+1)/(float)EffDistDATAP->GetBinContent(i+1,l+1);

	float EffDistDATA[43][11]={0};
	for(int l=0;l<11;l++)
		for(int i=1;i<43;i++) 
			if(EffQualDATAP->GetBinContent(i+1,l+1)>0)
				EffDistDATA[i][l]=EffDistDATAP->GetBinContent(i+1,l+1)/(float)EffQualDATAP->GetBinContent(i+1,l+1);
	
	cout<<"************************************************************ LAT. Eff. CORRECTION ************************************************************"<<endl;

        double Tau_DLik[11]={0};
        double Tau_DLik_err[11]={0};
        float HELikeff1[11]={0};
        float HELikeff2[11]={0};
        float HELikeff[11]={0};
	double Tau_DDist[11]={0};
        double Tau_DDist_err[11]={0};
        float HEDisteff1[11]={0};
        float HEDisteff2[11]={0};
        float HEDisteff[11]={0};

                for(int i=1;i<11;i++)
                        for(int j=30;j<43;j++) {
                                HEDisteff1[i]+=EffDistDATAP->GetBinContent(j+1,i+1);
				HEDisteff2[i]+=EffQualDATAP->GetBinContent(j+1,i+1);
				HELikeff1[i]+=EffLikDATAP->GetBinContent(j+1,i+1);
                                HELikeff2[i]+=EffDistDATAP->GetBinContent(j+1,i+1);
				}
                for(int i=1;i<11;i++){
					HELikeff[i]=HELikeff1[i]/HELikeff2[i];
					HEDisteff[i]=HEDisteff1[i]/HEDisteff2[i];	
				}

                for(int i=1;i<11;i++) {
					Tau_DLik[i]=(HELikeff[1])/HELikeff[i];
                                        Tau_DLik_err[i]=pow(HELikeff1[i],0.5)/HELikeff1[i]*Tau_DLik[i];
					Tau_DDist[i]=(HEDisteff[1])/HEDisteff[i];
                                        Tau_DDist_err[i]=pow(HEDisteff1[i],0.5)/HEDisteff1[i]*Tau_DDist[i];
                                        }
	
	c15->cd(1);
	gPad->SetLogx();
	gPad->SetGridx();
	gPad->SetGridy();
	TGraphErrors *EffDATALikP[11];
	for(int l=0;l<11;l++){
		EffDATALikP[l]=new TGraphErrors();
		int j=0;
		for(int i=1;i<43;i++) if(EffLikDATA[i][l]>0){
			EffDATALikP[l]->SetPoint(j,R_cent[i],EffLikDATA[i][l]);
			EffDATALikP[l]->SetPointError(j,0,pow(EffLikDATAP->GetBinContent(i+1,l+1),0.5)/EffLikDATAP->GetBinContent(i+1,l+1)*EffLikDATA[i][l]);
			j++;
		}	
	}
	cout<<endl;
	EffDATALikP[10]->SetMarkerColor(1);
	EffDATALikP[10]->SetMarkerStyle(8);
	EffDATALikP[10]->SetLineColor(1);
	EffDATALikP[10]->SetTitle("Likelihood Latitude Efficiency ");
	EffDATALikP[10]->GetXaxis()->SetTitle("R [GV]");
	EffDATALikP[10]->GetYaxis()->SetTitle("Efficiency");
	EffDATALikP[10]->GetXaxis()->SetTitleSize(0.045);
	EffDATALikP[10]->GetYaxis()->SetTitleSize(0.045);
	EffDATALikP[10]->Draw("AP");
	for(int l=0;l<10;l++){
		EffDATALikP[l]->SetMarkerColor(l);
		EffDATALikP[l]->SetMarkerStyle(8);	
		EffDATALikP[l]->SetLineColor(l);
		EffDATALikP[l]->Draw("Psame");
	}
	
	TGraphErrors *CorrLATLik;
        c15->cd(2);
        gPad->SetGridy();
        gPad->SetGridx();
        CorrLAT_Lik=new TF1("Likelihood Lat. Corr.","pol3");
        CorrLATLik=new TGraphErrors();
        CorrLATLik->SetTitle("Latitude Efficiency Corr.");
        CorrLATLik->GetXaxis()->SetTitle("Latitude");
        CorrLATLik->GetYaxis()->SetTitle("Eff. Corr. Factor");
        CorrLATLik->GetYaxis()->SetRangeUser(0.96,1.04);
	CorrLATLik->SetMarkerStyle(8);
        for(int i=1;i<11;i++) {
                        CorrLATLik->SetPoint(i-1,geomagC[i],Tau_DLik[i]);
                        CorrLATLik->SetPointError(i-1,0,Tau_DLik_err[i]);
                }
        CorrLATLik->Fit("Likelihood Lat. Corr.");
        CorrLATLik->Draw("AP");
	string nome="CorrLAT_Lik_spl";
        CorrLAT_Lik_spl=new TH2F(nome.c_str(),nome.c_str(),11,0,11,2,0,2);
        for(int i=0;i<11;i++) CorrLAT_Lik_spl->SetBinContent(i+1,1,CorrLAT_Lik->Eval(geomagC[i]));
        for(int i=0;i<11;i++) CorrLAT_Lik_spl->SetBinContent(i+1,2,Tau_DLik_err[i]);
	CorrLAT_Lik_Spl=new TGraphErrors("CorrLAT_Lik_Spl");
        CorrLAT_Lik_Spl->SetName("CorrLAT_Lik_Spl");
	for(int i=0;i<10;i++) {CorrLAT_Lik_Spl->SetPoint(i,geomagC[i+1],CorrLAT_Lik->Eval(geomagC[i+1]));
                                CorrLAT_Lik_Spl->SetPointError(i,0,Tau_DLik_err[i+1]);
                                }
        CorrLAT_Lik_Spl->SetLineColor(2);
        CorrLAT_Lik_Spl->SetMarkerColor(2);
        CorrLAT_Lik_Spl->SetFillColor(2);
        CorrLAT_Lik_Spl->SetFillStyle(3001);
        CorrLAT_Lik_Spl->SetLineWidth(2);
        CorrLAT_Lik_Spl->Draw("4same");


	c16->cd(1);
	gPad->SetLogx();
	gPad->SetGridx();
	gPad->SetGridy();
	TGraphErrors *EffDATADistP[11];
	for(int l=0;l<11;l++){
		EffDATADistP[l]=new TGraphErrors();
		int j=0;
		for(int i=1;i<43;i++) if(EffDistDATA[i][l]>0){
			EffDATADistP[l]->SetPoint(j,R_cent[i],EffDistDATA[i][l]);
			EffDATADistP[l]->SetPointError(j,0,pow(EffDistDATAP->GetBinContent(i+1,l+1),0.5)/EffDistDATAP->GetBinContent(i+1,l+1)*EffDistDATA[i][l]);
			j++;
		}
	}
	EffDATADistP[10]->SetMarkerColor(1);
	EffDATADistP[10]->SetMarkerStyle(8);
	EffDATADistP[10]->SetLineColor(1);
	EffDATADistP[10]->SetTitle("Distance Latitude Efficiency ");
	EffDATADistP[10]->GetXaxis()->SetTitle("R [GV]");
	EffDATADistP[10]->GetYaxis()->SetTitle("Efficiency");
	EffDATADistP[10]->GetXaxis()->SetTitleSize(0.045);
	EffDATADistP[10]->GetYaxis()->SetTitleSize(0.045);
	EffDATADistP[10]->Draw("AP");
	for(int l=0;l<10;l++){
		EffDATADistP[l]->SetMarkerColor(l); 
		EffDATADistP[l]->SetMarkerStyle(8);
		EffDATADistP[l]->SetLineColor(l);
		EffDATADistP[l]->Draw("Psame");
	}
	TGraphErrors *CorrLATDist;
        c16->cd(2);
        gPad->SetGridy();
        gPad->SetGridx();
        CorrLAT_Dist=new TF1("Distance Lat. Corr.","pol4");
        CorrLATDist=new TGraphErrors();
        CorrLATDist->SetTitle("Latitude Efficiency Corr.");
        CorrLATDist->GetXaxis()->SetTitle("Latitude");
        CorrLATDist->GetYaxis()->SetTitle("Eff. Corr. Factor");
	CorrLATDist->GetYaxis()->SetRangeUser(0.96,1.04);
        CorrLATDist->SetMarkerStyle(8);
        for(int i=1;i<11;i++) {
                        CorrLATDist->SetPoint(i-1,geomagC[i],Tau_DDist[i]);
                        CorrLATDist->SetPointError(i-1,0,Tau_DDist_err[i]);
                }
        CorrLATDist->Fit("Distance Lat. Corr.");
        CorrLATDist->Draw("AP");
	nome="CorrLAT_Dist_spl";
        CorrLAT_Dist_spl=new TH2F(nome.c_str(),nome.c_str(),11,0,11,2,0,2);
        for(int i=0;i<11;i++) CorrLAT_Dist_spl->SetBinContent(i+1,1,CorrLAT_Dist->Eval(geomagC[i]));
	for(int i=0;i<11;i++) CorrLAT_Dist_spl->SetBinContent(i+1,2,Tau_DDist_err[i]);	
	CorrLAT_Dist_Spl=new TGraphErrors("CorrLAT_Dist_Spl");
        CorrLAT_Dist_Spl->SetName("CorrLAT_Dist_Spl");
	for(int i=0;i<10;i++) {CorrLAT_Dist_Spl->SetPoint(i,geomagC[i+1],CorrLAT_Dist->Eval(geomagC[i+1]));
                                CorrLAT_Dist_Spl->SetPointError(i,0,Tau_DDist_err[i+1]);
                                }
        CorrLAT_Dist_Spl->SetLineColor(2);
        CorrLAT_Dist_Spl->SetMarkerColor(2);
        CorrLAT_Dist_Spl->SetFillColor(2);
        CorrLAT_Dist_Spl->SetFillStyle(3001);
        CorrLAT_Dist_Spl->SetLineWidth(2);
        CorrLAT_Dist_Spl->Draw("4same");

}


