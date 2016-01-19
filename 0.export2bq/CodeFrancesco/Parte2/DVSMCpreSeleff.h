TCanvas *c17[4];

TH2F * EffpreSelMCvsD1=new TH2F("EffpreSelMCvsD1","EffpreSelMCvsD1",18,0,18,3,0,3);
TH2F * EffpreSelMCvsD2=new TH2F("EffpreSelMCvsD2","EffpreSelMCvsD2",18,0,18,3,0,3);
TH2F * EffpreSelMCvsD1_R=new TH2F("EffpreSelMCvsD1_R","EffpreSelMCvsD1_R",43,0,43,3,0,3);
TH2F * EffpreSelMCvsD2_R=new TH2F("EffpreSelMCvsD2_R","EffpreSelMCvsD2_R",43,0,43,3,0,3);

TH3F * EffpreSelMCvsD1_D=new TH3F("EffpreSelMCvsD1_D","EffpreSelMCvsD1_D",18,0,18,3,0,3,11,0,11);
TH3F * EffpreSelMCvsD2_D=new TH3F("EffpreSelMCvsD2_D","EffpreSelMCvsD2_D",18,0,18,3,0,3,11,0,11);
TH3F * EffpreSelMCvsD1_R_D=new TH3F("EffpreSelMCvsD1_R_D","EffpreSelMCvsD1_R_D",43,0,43,3,0,3,11,0,11);
TH3F * EffpreSelMCvsD2_R_D=new TH3F("EffpreSelMCvsD2_R_D","EffpreSelMCvsD2_R_D",43,0,43,3,0,3,11,0,11);

TH2F * EffPreSelMCvsD_R_TH2F=new TH2F("EffPreSelMCvsD_R_TH2F","EffPreSelMCvsD_R_TH2F",43,0,43,3,0,3);
TH2F * EffPreSelMCvsD_TH2F=new TH2F("EffPreSelMCvsD_TH2F","EffPreSelMCvsD_TH2F",18,0,18,3,0,3);

TGraphErrors *PreDVSMC_P_Graph[3];
TH2F *PreDVSMC_P[3];

void DVSMCpreSeleff_D_Fill(TNtuple *ntupla, int l,int zona){
        int k = ntupla->GetEvent(l);
        if(Unbias!=0||Beta_pre<=0||R_pre<=0||Beta_pre>protons->Eval(R_pre)+0.1||Beta_pre<protons->Eval(R_pre)-0.1) return;
        for(int S=0;S<3;S++){
		if((R_pre>Rcut[zona]&&zona<10)||(zona==10&&R_pre>1.2*Rcutoff)){
                        for(int M=0;M<43;M++) if(fabs(R_pre)<bin[M+1]&&fabs(R_pre)>bin[M]) {
                                //if(EdepL1>0.04&&EdepL1<EdepL1beta->Eval(Beta_pre)+0.2&&EdepL1>EdepL1beta->Eval(Beta_pre)-0.2){
                                if((S!=3&&EdepTOFU<EdepTOFbeta->Eval(Beta_pre)+1&&EdepTOFU>EdepTOFbeta->Eval(Beta_pre)-1)||S==3){
					if(((int)Cutmask&notpassed[S])==notpassed[S]) EffpreSelMCvsD1_R_D->Fill(M,S,zona);
                                	if(((int)Cutmask&passed[S])==passed[S]) EffpreSelMCvsD2_R_D->Fill(M,S,zona);
                                }
                        }
                        for(int m=0;m<18;m++)  if(Beta_pre>Betabins[m]&&Beta_pre<=Betabins[m+1]){
                                //if(EdepL1<EdepL1beta->Eval(Beta_pre)+0.2&&EdepL1>EdepL1beta->Eval(Beta_pre)-0.2){
                                if((S!=3&&EdepTOFU<EdepTOFbeta->Eval(Beta_pre)+1&&EdepTOFU>EdepTOFbeta->Eval(Beta_pre)-1)||S==3){
					if(((int)Cutmask&notpassed[S])==notpassed[S]) EffpreSelMCvsD1_D->Fill(m,S,zona);
                                	if(((int)Cutmask&passed[S])==passed[S]) EffpreSelMCvsD2_D->Fill(m,S,zona);
                                }
                        }
		}
        }
        return;
}


void DVSMCpreSeleff_Fill(TNtuple *ntupla, int l){
        int k = ntupla->GetEvent(l);
        if(Unbias!=0||Beta_pre<=0||R_pre<=0||Beta_pre>protons->Eval(R_pre)+0.1||Beta_pre<protons->Eval(R_pre)-0.1) return;
        for(int S=0;S<3;S++){
                if(Massa_gen<1&&Massa_gen>0.5) {
                        for(int M=0;M<43;M++) if(fabs(R_pre)<bin[M+1]&&fabs(R_pre)>bin[M]) {
                              // if(EdepL1>0.04&&EdepL1<EdepL1beta->Eval(Beta_pre)+0.2&&EdepL1>EdepL1beta->Eval(Beta_pre)-0.2){
                             if((S!=3&&EdepTOFU<EdepTOFbeta->Eval(Beta_pre)+1&&EdepTOFU>EdepTOFbeta->Eval(Beta_pre)-1)||S==3){
				if(((int)Cutmask&notpassed[S])==notpassed[S]) EffpreSelMCvsD1_R->Fill(M,S);
                                if(((int)Cutmask&passed[S])==passed[S]) EffpreSelMCvsD2_R->Fill(M,S);
                                }
                        }
                        for(int m=0;m<18;m++)  if(Beta_pre>Betabins[m]&&Beta_pre<=Betabins[m+1]){
                             // if(EdepL1<EdepL1beta->Eval(Beta_pre)+0.2&&EdepL1>EdepL1beta->Eval(Beta_pre)-0.2){
                             if((S!=3&&EdepTOFU<EdepTOFbeta->Eval(Beta_pre)+1&&EdepTOFU>EdepTOFbeta->Eval(Beta_pre)-1)||S==3){
				if(((int)Cutmask&notpassed[S])==notpassed[S]) EffpreSelMCvsD1->Fill(m,S);
                                if(((int)Cutmask&passed[S])==passed[S]) EffpreSelMCvsD2->Fill(m,S);
                                }
                        }
                }

        }
        return;
}


void DVSMCpreSeleff_Copy(TFile * file){
        EffpreSelMCvsD1= (TH2F*) file->Get("EffpreSelMCvsD1");
        EffpreSelMCvsD2= (TH2F*) file->Get("EffpreSelMCvsD2");
        EffpreSelMCvsD1_R =(TH2F*) file->Get("EffpreSelMCvsD1_R");
        EffpreSelMCvsD2_R =(TH2F*) file->Get("EffpreSelMCvsD2_R");
	EffpreSelMCvsD1_D= (TH3F*) file->Get("EffpreSelMCvsD1_D");
        EffpreSelMCvsD2_D= (TH3F*) file->Get("EffpreSelMCvsD2_D");
        EffpreSelMCvsD1_R_D =(TH3F*) file->Get("EffpreSelMCvsD1_R_D");
        EffpreSelMCvsD2_R_D =(TH3F*) file->Get("EffpreSelMCvsD2_R_D");

        return;
}

void DVSMCpreSeleff(TFile * file){
	string numero[18]={"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17"};
        string tagli[3]={"Matching TOF","Chi^2 R","1 Tr. Track"};
        string nome;

	cout<<"************************************************* DATA vs MC PRESELECTIONS EFFICIENCIES **********************************************************************"<<endl;
        string MCLegend[7]={"protons.B800","d.pl1.0_520_GG_Blic","d.pl1.0_520_GG_BlicDPMJet","d.pl1.0_520_GG_QMD","d.pl1.0_520_Shen_Blic","d.pl1.0_520_Shen_BlicDPMJet","d.pl1.0_520_Shen_QMD"};
        float EffpreSelMCvsD[18][3];
        float EffpreSelMCvsD_R[43][3];
	float EffpreSelMCvsD_D[18][3][11];
	float EffpreSelMCvsD_R_D[43][3][11];
        float EffpreSelMCvsD_R_mean[43][3];
	float EffpreSelMCvsD_R_meanerr[43][3];
	double ratio_smooth[43][3]={0};
	TF1 * Polpre[3];
	for(int i=1;i<43;i++) for(int h=0;h<6;h++) for(int m=0;m<17;m++) for(int S=0;S<3;S++) for(int l=0;l<11;l++){
        EffpreSelMCvsD_R[i][S]=0;
        EffpreSelMCvsD[m][S]=0;
	EffpreSelMCvsD_R_mean[i][S]=0;
	EffpreSelMCvsD_R_meanerr[i][S]=0;
	EffpreSelMCvsD_R_D[i][S][l]=0;
	ratio_smooth[i][S]=0;
        }
        for(int S=0;S<3;S++){
                nome="Data vs MC: "+tagli[S];
                c17[S]=new TCanvas(nome.c_str());

                for(int i=0;i<17;i++) if(EffpreSelMCvsD1->GetBinContent(i+1,S+1)>0) if(EffpreSelMCvsD2->GetBinContent(i+1,S+1)<EffpreSelMCvsD1->GetBinContent(i+1,S+1))
                        EffpreSelMCvsD[i][S]=EffpreSelMCvsD2->GetBinContent(i+1,S+1)/(float)EffpreSelMCvsD1->GetBinContent(i+1,S+1);

                for(int i=1;i<43;i++) EffpreSelMCvsD_R[i][S]=EffpreSelMCvsD2_R->GetBinContent(i+1,S+1)/(float)EffpreSelMCvsD1_R->GetBinContent(i+1,S+1);

		for(int l=0;l<11;l++)
		for(int i=0;i<17;i++) if(EffpreSelMCvsD1_D->GetBinContent(i+1,S+1,l+1)>0) if(EffpreSelMCvsD2_D->GetBinContent(i+1,S+1,l+1)<EffpreSelMCvsD1_D->GetBinContent(i+1,S+1,l+1))
                        EffpreSelMCvsD_D[i][S][l]=EffpreSelMCvsD2_D->GetBinContent(i+1,S+1,l+1)/(float)EffpreSelMCvsD1_D->GetBinContent(i+1,S+1,l+1)*CorrLAT_pre[S]->Eval(geomagC[l]);

                for(int l=0;l<11;l++)
		for(int i=1;i<43;i++) if(EffpreSelMCvsD2_R_D->GetBinContent(i+1,S+1,l+1)>100&&EffpreSelMCvsD1_R_D->GetBinContent(i+1,S+1,l+1)>100)
		EffpreSelMCvsD_R_D[i][S][l]=EffpreSelMCvsD2_R_D->GetBinContent(i+1,S+1,l+1)/(float)EffpreSelMCvsD1_R_D->GetBinContent(i+1,S+1,l+1)*CorrLAT_pre[S]->Eval(geomagC[l]);


		TGraphErrors * EffPreSelMCvsD_R = new TGraphErrors();
		EffPreSelMCvsD_R->SetTitle(MCLegend[0].c_str());
		for(int i=0;i<43;i++) {EffPreSelMCvsD_R->SetPoint(i,R_cent[i],EffpreSelMCvsD_R[i][S]/EffpreSelMCvsD_R[i][S]);
                                EffPreSelMCvsD_R->SetPointError(i,0,pow(EffpreSelMCvsD1_R->GetBinContent(i+1,S+1),0.5)/EffpreSelMCvsD1_R->GetBinContent(i+1,S+1)*EffpreSelMCvsD_R[i][S]);}
		
		//WEIGHTED MEAN over LAT
		TGraphErrors * EffPreSelMCvsD_R_Mean=new TGraphErrors();
		float denom=0;
		for(int i=1;i<43;i++) {
			for(int l=0;l<11;l++) {
					if(EffpreSelMCvsD2_R_D->GetBinContent(i+1,S+1,l+1)>100&&EffpreSelMCvsD1_R_D->GetBinContent(i+1,S+1,l+1)>100){
						denom=pow(EffpreSelMCvsD1_R_D->GetBinContent(i+1,S+1,l+1),0.5)/EffpreSelMCvsD1_R_D->GetBinContent(i+1,S+1,l+1)*EffpreSelMCvsD_R_D[i][S][l]/EffpreSelMCvsD_R[i][S];
						EffpreSelMCvsD_R_mean[i][S]+=(EffpreSelMCvsD_R_D[i][S][l]/EffpreSelMCvsD_R[i][S])/pow(denom,2);
						EffpreSelMCvsD_R_meanerr[i][S]+=1/pow(denom,2);
						}
					}
			EffpreSelMCvsD_R_mean[i][S]=EffpreSelMCvsD_R_mean[i][S]/EffpreSelMCvsD_R_meanerr[i][S];
			EffpreSelMCvsD_R_meanerr[i][S]=pow(1/EffpreSelMCvsD_R_meanerr[i][S],0.5);
			EffPreSelMCvsD_R_Mean->SetPoint(i,R_cent[i],EffpreSelMCvsD_R_mean[i][S]);
			EffPreSelMCvsD_R_Mean->SetPointError(i,0,EffpreSelMCvsD_R_meanerr[i][S]);
		}
		 //SMOOTHING & FIT
		for(int j=1;j<43;j++){
			ratio_smooth[j][S]=EffpreSelMCvsD_R_mean[j][S];
		}
		ratio_smooth[0][S]=ratio_smooth[1][S];
		nome="Polpre"+tagli[S];
		Polpre[S]=new TF1(nome.c_str(),"pol2");
		EffPreSelMCvsD_R_Mean->Fit(nome.c_str(),"","",8,100);

		for(int j=3;j<43;j++){
			if(R_cent[j]<8){
				ratio_smooth[j][S]=(ratio_smooth[j][S]+ratio_smooth[j-1][S]+ratio_smooth[j+1][S])/3;
			}
			else{
				ratio_smooth[j][S]=Polpre[S]->Eval(R_cent[j]);
			}
		}

		///////////////////////
		c17[S]->cd();
		gPad->SetLogx();
		gPad->SetGridx();
		gPad->SetGridy();
		nome="DvsMC: " + tagli[S]+"_Graph";
		PreDVSMC_P_Graph[S]=new TGraphErrors();
		PreDVSMC_P_Graph[S]->SetName(nome.c_str());
		nome="DvsMC: " + tagli[S];	
		PreDVSMC_P[S]=new TH2F(nome.c_str(),nome.c_str(),43,0,43,2,0,2);
		int j=0;
		for(int i=1;i<43;i++) {
			if(1>0){
				PreDVSMC_P_Graph[S]->SetPoint(j,R_cent[i],ratio_smooth[i][S]); 
				PreDVSMC_P[S]->SetBinContent(j+1,1,ratio_smooth[i][S]);
				PreDVSMC_P_Graph[S]->SetPointError(j,0,EffpreSelMCvsD_R_meanerr[i][S]);
				PreDVSMC_P[S]->SetBinContent(j+1,2,EffpreSelMCvsD_R_meanerr[i][S]);
				j++;
			}
		}
		PreDVSMC_P_Graph[S]->SetLineColor(4);
		PreDVSMC_P_Graph[S]->SetFillColor(4);
		PreDVSMC_P_Graph[S]->SetFillStyle(3001);
		PreDVSMC_P_Graph[S]->SetLineWidth(4);
		EffPreSelMCvsD_R->SetMarkerColor(2);
		EffPreSelMCvsD_R->SetMarkerStyle(8);
		EffPreSelMCvsD_R->SetLineColor(2);
		EffPreSelMCvsD_R->SetLineWidth(1);
		EffPreSelMCvsD_R_Mean->SetMarkerColor(2);
                EffPreSelMCvsD_R_Mean->SetMarkerStyle(4);
                EffPreSelMCvsD_R_Mean->SetLineColor(2);
                EffPreSelMCvsD_R_Mean->SetLineWidth(1);
		nome="Efficiency: "+tagli[S]+ "MC (R bins)";
                EffPreSelMCvsD_R->SetTitle(nome.c_str());
                EffPreSelMCvsD_R->GetXaxis()->SetTitle("R [GV]");
                EffPreSelMCvsD_R->GetYaxis()->SetTitle("Pres. Efficiency");
                EffPreSelMCvsD_R->GetXaxis()->SetTitleSize(0.045);
                EffPreSelMCvsD_R->GetYaxis()->SetTitleSize(0.045);
		EffPreSelMCvsD_R->GetYaxis()->SetRangeUser(0.7,1.4);
                {
                        EffPreSelMCvsD_R->Draw("AP");
			EffPreSelMCvsD_R_Mean->Draw("Psame");
                        PreDVSMC_P_Graph[S]->Draw("L4same");
			TLegend* leg =new TLegend(0.4, 0.7,0.95,0.95);
                        leg->AddEntry(EffPreSelMCvsD_R,MCLegend[0].c_str(), "ep");

                }

	}
}
