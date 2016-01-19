using namespace std;

TCanvas *c14[4];

float Rcut[11]={18,18,16,14,12,10,8,6,4,2,1};
TH3F * EffpreSelDATA1_R=new TH3F("EffpreSelDATA1_R","EffpreSelDATA1_R",43,0,43,3,0,3,11,0,11);
TH3F * EffpreSelDATA2_R=new TH3F("EffpreSelDATA2_R","EffpreSelDATA2_R",43,0,43,3,0,3,11,0,11);

TF1 * CorrLAT_pre[3];
TH2F *CorrLATpre_spl[3];
TGraphErrors *CorrLATpre_Spl[3];

void DATApreSeleff_Fill(TNtuple *ntupla, int l,int zona){
	int k = ntupla->GetEvent(l);
	if(Unbias!=0||Beta_pre<=0||R_pre<=0||Beta_pre>protons->Eval(R_pre)+0.1||Beta_pre<protons->Eval(R_pre)-0.1) return;
	for(int S=0;S<3;S++){
			for(int M=0;M<43;M++) if(fabs(R_pre)<bin[M+1]&&fabs(R_pre)>bin[M]&&R_pre>Rcut[zona]) {
				//if(EdepL1<EdepL1beta->Eval(Beta_pre)+0.2&&EdepL1>EdepL1beta->Eval(Beta_pre)-0.2){
				if((S!=3&&EdepTOFU<EdepTOFbeta->Eval(Beta_pre)+1&&EdepTOFU>EdepTOFbeta->Eval(Beta_pre)-1)||S==3){
					if(((int)Cutmask&notpassed[S])==notpassed[S]) EffpreSelDATA1_R->Fill(M,S,zona);
					if(((int)Cutmask&passed[S])==passed[S]) EffpreSelDATA2_R->Fill(M,S,zona);
				}
			}	
	}
	return;
}

void DATApreSeleff_Copy(TFile * file){
        EffpreSelDATA1_R =(TH3F*) file->Get("EffpreSelDATA1_R");
        EffpreSelDATA2_R =(TH3F*) file->Get("EffpreSelDATA2_R");
	return;	
}

void DATApreSeleff(TFile * file1){

	string tagli[3]={"Matching TOF","Chi^2 R","1 Tr. Track"};
        string nome;

	cout<<"************************************************* MC PRESELECTIONS EFFICIENCIES **********************************************************************"<<endl;
	float EffpreSelDATA_R[43][3][11];
	for(int i=1;i<43;i++) for(int h=0;h<6;h++) for(int l=0;l<11;l++) for(int S=0;S<3;S++){
        EffpreSelDATA_R[i][S][l]=0;
	}
	TGraphErrors * Eff_preSelLAT[3][11];
	for(int S=0;S<3;S++){
		nome="Latitude Efficiency: "+tagli[S];
		c14[S]=new TCanvas(nome.c_str());
		c14[S]->Divide(2,1);
		for(int l=0;l<11;l++)
		for(int i=1;i<43;i++) if(EffpreSelDATA1_R->GetBinContent(i+1,S+1,l+1)>0) 
			EffpreSelDATA_R[i][S][l]=EffpreSelDATA2_R->GetBinContent(i+1,S+1,l+1)/(float)EffpreSelDATA1_R->GetBinContent(i+1,S+1,l+1);
		c14[S]->cd(1);
		gPad->SetLogx();
		gPad->SetGridx();
		gPad->SetGridy();
		for(int l=0;l<11;l++){
			Eff_preSelLAT[S][l]=new TGraphErrors();
			int point=0;
			for(int i=1;i<43;i++)
				if(EffpreSelDATA_R[i][S][l]>0){ 
				Eff_preSelLAT[S][l]->SetPoint(point,R_cent[i],EffpreSelDATA_R[i][S][l]);
				Eff_preSelLAT[S][l]->SetPointError(point,0,pow(EffpreSelDATA2_R->GetBinContent(i+1,S+1,l+1),0.5)/EffpreSelDATA2_R->GetBinContent(i+1,S+1,l+1)*EffpreSelDATA_R[i][S][l]);
				point++;	
			}
		}
		Eff_preSelLAT[S][10]->SetMarkerColor(1);
		Eff_preSelLAT[S][10]->SetLineColor(1);
		Eff_preSelLAT[S][10]->SetMarkerStyle(8);
		Eff_preSelLAT[S][10]->GetXaxis()->SetTitle("R [GV]");
        	Eff_preSelLAT[S][10]->GetYaxis()->SetTitle("Efficiency");
		Eff_preSelLAT[S][10]->GetYaxis()->SetRangeUser(0.1,1);
		Eff_preSelLAT[S][10]->Draw("AP");
		for(int l=0;l<10;l++){
		Eff_preSelLAT[S][l]->SetMarkerColor(l);
		Eff_preSelLAT[S][l]->SetLineColor(l);
                Eff_preSelLAT[S][l]->SetMarkerStyle(8);
		Eff_preSelLAT[S][l]->Draw("Psame");
		}
	}

	cout<<"************************************************************ LAT. Eff. CORRECTION ************************************************************"<<endl;

	double Tau_D[3][11]={{0}};
	double Tau_D_err[3][11]={{0}};
	float HEeff1[3][11]={{0}};
	float HEeff2[3][11]={{0}};
	float HEeff[3][11]={{0}};

	for(int S=0;S<3;S++){
		for(int i=1;i<11;i++)
			for(int j=30;j<43;j++) {
				HEeff1[S][i]+=EffpreSelDATA1_R->GetBinContent(j+1,S+1,i+1);
				HEeff2[S][i]+=EffpreSelDATA2_R->GetBinContent(j+1,S+1,i+1);}
	}
	for(int S=0;S<3;S++)
		for(int i=1;i<11;i++){HEeff[S][i]=HEeff2[S][i]/HEeff1[S][i];}

	for(int S=0;S<3;S++)
		for(int i=1;i<11;i++) {
					Tau_D[S][i]=(HEeff[S][1])/HEeff[S][i];
					Tau_D_err[S][i]=pow(HEeff1[S][i],0.5)/HEeff1[S][i]*Tau_D[S][i];
					}
	TGraphErrors *CorrLATpre[3];
	for(int S=0;S<3;S++){
	c14[S]->cd(2);
	gPad->SetGridy();
	gPad->SetGridx();
	nome="Latitude Efficiency: "+tagli[S];
	nome=nome+": Fit";
	CorrLAT_pre[S]=new TF1(nome.c_str(),"pol3");
	CorrLATpre[S]=new TGraphErrors();
	CorrLATpre[S]->SetTitle("Latitude Efficiency Corr.");
	CorrLATpre[S]->GetXaxis()->SetTitle("Latitude");
	CorrLATpre[S]->GetYaxis()->SetTitle("Eff. Corr. Factor");
	CorrLATpre[S]->SetMarkerStyle(8);
	for(int i=1;i<11;i++) {
			CorrLATpre[S]->SetPoint(i-1,geomagC[i],Tau_D[S][i]);
			CorrLATpre[S]->SetPointError(i-1,0,Tau_D_err[S][i]);	
		}
	CorrLATpre[S]->Fit(nome.c_str());
	CorrLATpre[S]->Draw("AP");	

	nome="CorrLATpre_spl"+tagli[S];
        CorrLATpre_spl[S]=new TH2F(nome.c_str(),nome.c_str(),11,0,11,2,0,2);
	for(int i=0;i<11;i++) CorrLATpre_spl[S]->SetBinContent(i+1,1,CorrLAT_pre[S]->Eval(geomagC[i]));
	for(int i=0;i<11;i++) CorrLATpre_spl[S]->SetBinContent(i+1,2,Tau_D_err[S][i]);
	CorrLATpre_Spl[S]=new TGraphErrors(tagli[S].c_str());
	CorrLATpre_Spl[S]->SetName(tagli[S].c_str());
	int j=0;
	for(int i=1;i<11;i++) { CorrLATpre_Spl[S]->SetPoint(j,geomagC[i],CorrLAT_pre[S]->Eval(geomagC[i]));
				CorrLATpre_Spl[S]->SetPointError(j,0,Tau_D_err[S][i]);
				j++;
				}
	CorrLATpre_Spl[S]->SetLineColor(2);
	CorrLATpre_Spl[S]->SetMarkerColor(2);
	CorrLATpre_Spl[S]->SetFillColor(2);
	CorrLATpre_Spl[S]->SetFillStyle(3001);
	CorrLATpre_Spl[S]->SetLineWidth(2);
	CorrLATpre_Spl[S]->Draw("L4same");	

	}
}

