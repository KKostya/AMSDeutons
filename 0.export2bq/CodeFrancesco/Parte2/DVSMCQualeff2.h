using namespace std;

TCanvas *c20=new TCanvas("Data vs MC: Likelihood");
TCanvas *c21=new TCanvas("Data vs MC: Distance");

TH2F * EffDistMCvsDP1 = new TH2F("EffDistMCvsDP1","EffDistMCvsDP1",43,0,43,11,0,11);
TH2F * EffDistMCvsDP2 = new TH2F("EffDistMCvsDP2","EffDistMCvsDP2",43,0,43,11,0,11);
TH2F * EffLik2MCvsDP1 = new TH2F("EffLik2MCvsDP1","EffLik2MCvsDP1",43,0,43,11,0,11);
TH2F * EffLik2MCvsDP2 = new TH2F("EffLik2MCvsDP2","EffLik2MCvsDP2",43,0,43,11,0,11);

TSpline3 *DistDVSMC_P;
TSpline3 *LikDVSMC_P;
TGraphErrors *LikDVSMC_P_Graph;
TGraphErrors *DistDVSMC_P_Graph;
TH2F * LikDVSMC_P_graph=new TH2F("LikDVSMC_P_graph","LikDVSMC_P_graph",43,0,43,2,0,2);
TH2F * DistDVSMC_P_graph=new TH2F("DistDVSMC_P_graph","DistDVSMC_P_graph",43,0,43,2,0,2);

void DVSMCQualeff2_Fill(TNtuple *ntupla, int l,int zona){

	int k = ntupla->GetEvent(l);
	if(Beta<=0||R<=0||R<1.2*Rcutoff||Beta>protons->Eval(R)+0.1||Beta<protons->Eval(R)-0.1) return;
	if((R>Rcut[zona]&&zona<10)||(zona==10)) {
		if(EdepL1<EdepL1beta->Eval(Beta)+0.2&&EdepL1>EdepL1beta->Eval(Beta)-0.2){
			for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]) {EffDistMCvsDP2->Fill(K,zona);}
			if(Dist5D_P<6)
				for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]) {EffDistMCvsDP1->Fill(K,zona);}

			if(Dist5D_P<6) {
				for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]) {EffLik2MCvsDP1->Fill(K,zona);}
				if(LDiscriminant>0.7)
					for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]) {EffLik2MCvsDP2->Fill(K,zona);}
			}

		}
	}
}

void DVSMCQualeff2_Copy(TFile * file1){
	EffDistMCvsDP1 = (TH2F *)file1->Get("EffDistMCvsDP1");
	EffDistMCvsDP2 = (TH2F *)file1->Get("EffDistMCvsDP2");
	EffLik2MCvsDP1 = (TH2F *)file1->Get("EffLik2MCvsDP1");
        EffLik2MCvsDP2 = (TH2F *)file1->Get("EffLik2MCvsDP2");
	return;
}


void DVSMCQualeff2(TFile * file1){
	cout<<"************************************************************ MC QUALITY SEL. EFFICIENCIES ************************************************************"<<endl;		
	float EffLik2MCvsDP[43][11]={{0}};
	for(int l=0;l<11;l++)
	for(int i=1;i<43;i++) if(EffLik2MCvsDP2->GetBinContent(i+1,l+1)>100&&EffLik2MCvsDP1->GetBinContent(i+1,l+1)>100)
		EffLik2MCvsDP[i][l]=EffLik2MCvsDP2->GetBinContent(i+1,l+1)/(float)EffLik2MCvsDP1->GetBinContent(i+1,l+1)*CorrLAT_Lik->Eval(geomagC[l]);

	float EffDistMCvsDP[43][11]={{0}};
	for(int l=0;l<11;l++)
	for(int i=1;i<43;i++) if(EffDistMCvsDP2->GetBinContent(i+1,l+1)>100&&EffDistMCvsDP1->GetBinContent(i+1,l+1)>100)
		EffDistMCvsDP[i][l]=EffDistMCvsDP1->GetBinContent(i+1,l+1)/(float)EffDistMCvsDP2->GetBinContent(i+1,l+1)*CorrLAT_Dist->Eval(geomagC[l]);
	
	//WEIGHTED MEAN over LAT
	float EffDistMCvsDP_mean[43]={0};
	float EffLik2MCvsDP_mean[43]={0};
	float EffDistMCvsDP_meanerr[43]={0};
        float EffLik2MCvsDP_meanerr[43]={0};
	TGraphErrors * EffDistMCvsDP_Mean=new TGraphErrors();
	TGraphErrors * EffLik2MCvsDP_Mean=new TGraphErrors();
	float denom=0;
	for(int i=1;i<43;i++) {
		for(int l=0;l<11;l++) {
			if(EffLik2MCvsDP2->GetBinContent(i+1,l+1)>100&&EffLik2MCvsDP1->GetBinContent(i+1,l+1)>100){
				denom=pow(EffLik2MCvsDP1->GetBinContent(i+1,l+1),0.5)/EffLik2MCvsDP1->GetBinContent(i+1,l+1)*EffLik2MCvsDP[i][l]/EffLik2CheckMCP_TH1F->GetBinContent(i+1,1);
				EffLik2MCvsDP_mean[i]+=(EffLik2MCvsDP[i][l]/EffLik2CheckMCP_TH1F->GetBinContent(i+1,1))/pow(denom,2);
				EffLik2MCvsDP_meanerr[i]+=1/pow(denom,2);
			}
		}
		EffLik2MCvsDP_mean[i]=EffLik2MCvsDP_mean[i]/EffLik2MCvsDP_meanerr[i];
		EffLik2MCvsDP_meanerr[i]=pow(1/EffLik2MCvsDP_meanerr[i],0.5);
		EffLik2MCvsDP_Mean->SetPoint(i,R_cent[i],EffLik2MCvsDP_mean[i]);
		EffLik2MCvsDP_Mean->SetPointError(i,0,EffLik2MCvsDP_meanerr[i]);
	}
	
	denom=0;
        for(int i=1;i<43;i++) {
                for(int l=0;l<11;l++) {
                        if(EffDistMCvsDP2->GetBinContent(i+1,l+1)>100&&EffDistMCvsDP1->GetBinContent(i+1,l+1)>100){
                                denom=pow(EffDistMCvsDP1->GetBinContent(i+1,l+1),0.5)/EffDistMCvsDP1->GetBinContent(i+1,l+1)*EffDistMCvsDP[i][l]/EffDistCheckMCP_TH1F->GetBinContent(i+1,1);
                                EffDistMCvsDP_mean[i]+=(EffDistMCvsDP[i][l]/EffDistCheckMCP_TH1F->GetBinContent(i+1,1))/pow(denom,2);
                                EffDistMCvsDP_meanerr[i]+=1/pow(denom,2);
                        }
                }
                EffDistMCvsDP_mean[i]=EffDistMCvsDP_mean[i]/EffDistMCvsDP_meanerr[i];
                EffDistMCvsDP_meanerr[i]=pow(1/EffDistMCvsDP_meanerr[i],0.5);
                EffDistMCvsDP_Mean->SetPoint(i,R_cent[i],EffDistMCvsDP_mean[i]);
                EffDistMCvsDP_Mean->SetPointError(i,0,EffDistMCvsDP_meanerr[i]);
        }
	//SMOOTHING & FIT
	double ratioL_smooth[43]={0};
	double ratioD_smooth[43]={0};

	for(int j=1;j<43;j++){
		ratioL_smooth[j]=EffLik2MCvsDP_mean[j];
		ratioD_smooth[j]=EffDistMCvsDP_mean[j];
	}
	ratioL_smooth[0]=ratioL_smooth[1];
	ratioD_smooth[0]=ratioD_smooth[1];
	
        TGraphErrors *EffMCvsDLikP_MC=new TGraphErrors();
        int j=0;
        for(int i=1;i<43;i++) if(EffLik2CheckMCP_TH1F->GetBinContent(i+1,1)>0)
                {EffMCvsDLikP_MC->SetPoint(j,R_cent[i],EffLik2CheckMCP_TH1F->GetBinContent(i+1,1)/EffLik2CheckMCP_TH1F->GetBinContent(i+1,1));j++;}
	
        TGraphErrors *EffMCvsDDistP_MC= new TGraphErrors();
        j=0;
        for(int i=1;i<43;i++) if(EffDistCheckMCP_TH1F->GetBinContent(i+1,1)>0)
                {EffMCvsDDistP_MC->SetPoint(j,R_cent[i],EffDistCheckMCP_TH1F->GetBinContent(i+1,1)/EffDistCheckMCP_TH1F->GetBinContent(i+1,1));j++;}

	TF1 *polL=new TF1("polL","pol2");
	TF1 *polD=new TF1("polD","pol2");
	
	EffLik2MCvsDP_Mean->Fit("polL","","",8,70);
	EffDistMCvsDP_Mean->Fit("polD","","",8,70);

	for(int j=3;j<43;j++){
		if(R_cent[j]<8){
		ratioL_smooth[j]=(ratioL_smooth[j]+ratioL_smooth[j-1]+ratioL_smooth[j+1])/3;
		ratioD_smooth[j]=(ratioD_smooth[j]+ratioD_smooth[j-1]+ratioD_smooth[j+1])/3;
		}
		else{
		ratioL_smooth[j]=polL->Eval(R_cent[j]);
		ratioD_smooth[j]=polD->Eval(R_cent[j]);
		}
	}
	
	///////////
	

	c20->cd();
	gPad->SetLogx();
        gPad->SetGridx();
        gPad->SetGridy();
	//LikDVSMC_P = new TSpline3("LikDVSMC_P",EffMCvsDLikP);
	LikDVSMC_P = new TSpline3("LikDVSMC_P",R_cent,ratioL_smooth,40); 
	LikDVSMC_P->SetLineColor(4);
	LikDVSMC_P_Graph=new TGraphErrors();
	LikDVSMC_P_Graph->SetName("LikDVSMC_P_Graph");
	j=0;
	for(int i=1;i<43;i++) {
		if(EffLik2CheckMCP_TH1F->GetBinContent(i+1,1)>0){
		LikDVSMC_P_Graph->SetPoint(j,R_cent[i],ratioL_smooth[i]);
		LikDVSMC_P_graph->SetBinContent(i+1,1,ratioL_smooth[i]);
		LikDVSMC_P_Graph->SetPointError(j,0,EffLik2MCvsDP_meanerr[i]);
		LikDVSMC_P_graph->SetBinContent(i+1,2,EffLik2MCvsDP_meanerr[i]);
	j++;
	}
	}
	LikDVSMC_P_Graph->SetLineColor(4);
	LikDVSMC_P_Graph->SetFillColor(4);
	LikDVSMC_P_Graph->SetFillStyle(3001);
        LikDVSMC_P_Graph->SetLineWidth(4);
	EffLik2MCvsDP_Mean->SetMarkerColor(2);
        EffLik2MCvsDP_Mean->SetMarkerStyle(4);
        EffLik2MCvsDP_Mean->SetLineColor(2);
        EffLik2MCvsDP_Mean->SetLineWidth(2);
        EffMCvsDLikP_MC->SetMarkerColor(2);
        EffMCvsDLikP_MC->SetMarkerStyle(8);
        EffMCvsDLikP_MC->SetLineColor(2);
        EffMCvsDLikP_MC->SetLineWidth(2);
	EffLik2MCvsDP_Mean->SetTitle("Likelihood Efficiency DATA/MC");
        EffLik2MCvsDP_Mean->GetXaxis()->SetTitle("R [GV]");
        EffLik2MCvsDP_Mean->GetYaxis()->SetTitle("Efficiency");
        EffLik2MCvsDP_Mean->GetXaxis()->SetTitleSize(0.045);
        EffLik2MCvsDP_Mean->GetYaxis()->SetTitleSize(0.045);
	EffLik2MCvsDP_Mean->GetYaxis()->SetRangeUser(0.7,1.4);
	{
                EffLik2MCvsDP_Mean->Draw("AP");
		EffMCvsDLikP_MC->Draw("CPsame");
                LikDVSMC_P_Graph->Draw("L4same");
		TLegend* leg =new TLegend(0.4, 0.7,0.95,0.95);
                //leg->AddEntry(EffMCLikP,MCLegend[0].c_str(), "ep");

        }

	c21->cd();
        gPad->SetLogx();
        gPad->SetGridx();
        gPad->SetGridy();
	//DistDVSMC_P = new TSpline3("DistDVSMC_P",EffMCvsDDistP);
	DistDVSMC_P =new TSpline3("DistDVSMC_P",R_cent,ratioD_smooth,40);
	DistDVSMC_P->SetLineColor(4);
	DistDVSMC_P_Graph=new TGraphErrors();
        DistDVSMC_P_Graph->SetName("DistDVSMC_P_Graph");
	j=0;
        for(int i=1;i<43;i++) {
                if(EffDistCheckMCP_TH1F->GetBinContent(i+1,1)>0){
                DistDVSMC_P_Graph->SetPoint(j,R_cent[i],ratioD_smooth[i]);
               	DistDVSMC_P_graph->SetBinContent(i+1,1,ratioD_smooth[i]);
		DistDVSMC_P_Graph->SetPointError(j,0,EffDistMCvsDP_meanerr[i]);
        	DistDVSMC_P_graph->SetBinContent(i+1,2,EffDistMCvsDP_meanerr[i]);
	j++;
        }
        }
        DistDVSMC_P_Graph->SetLineColor(4);
        DistDVSMC_P_Graph->SetFillColor(4);
        DistDVSMC_P_Graph->SetFillStyle(3001);
        DistDVSMC_P_Graph->SetLineWidth(4);
	EffDistMCvsDP_Mean->SetMarkerColor(2);
        EffDistMCvsDP_Mean->SetMarkerStyle(4);
        EffDistMCvsDP_Mean->SetLineColor(2);
        EffDistMCvsDP_Mean->SetLineWidth(2);
	EffMCvsDDistP_MC->SetMarkerColor(2);
        EffMCvsDDistP_MC->SetMarkerStyle(8);
        EffMCvsDDistP_MC->SetLineColor(2);
        EffMCvsDDistP_MC->SetLineWidth(2);
        EffDistMCvsDP_Mean->SetTitle("Distance Efficiency DATA/MC");
        EffDistMCvsDP_Mean->GetXaxis()->SetTitle("R [GV]");
        EffDistMCvsDP_Mean->GetYaxis()->SetTitle("Efficiency");
        EffDistMCvsDP_Mean->GetXaxis()->SetTitleSize(0.045);
        EffDistMCvsDP_Mean->GetYaxis()->SetTitleSize(0.045);
	EffDistMCvsDP_Mean->GetYaxis()->SetRangeUser(0.7,1.4);
        {
                EffDistMCvsDP_Mean->Draw(/*"AP4"*/"AP");
		EffMCvsDDistP_MC->Draw("CPsame");
                DistDVSMC_P_Graph->Draw("L4same");
		TLegend* leg =new TLegend(0.4, 0.7,0.95,0.95);
                //leg->AddEntry(EffMCDistP,MCLegend[0].c_str(), "ep");

        }	


}

