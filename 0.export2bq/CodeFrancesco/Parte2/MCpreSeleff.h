using namespace std;

TCanvas *c9[4];

TH2F * EffpreSelMCP1=new TH2F("EffpreSelMCP1","EffpreSelMCP1",18,0,18,3,0,3);
TH2F * EffpreSelMCP2=new TH2F("EffpreSelMCP2","EffpreSelMCP2",18,0,18,3,0,3);
TH2F * EffpreSelMCP1_R=new TH2F("EffpreSelMCP1_R","EffpreSelMCP1_R",43,0,43,3,0,3);
TH2F * EffpreSelMCP2_R=new TH2F("EffpreSelMCP2_R","EffpreSelMCP2_R",43,0,43,3,0,3);
TH3F * EffpreSelMCD1=new TH3F("EffpreSelMCD1","EffpreSelMCD1",18,0,18,6,0,6,3,0,3);
TH3F * EffpreSelMCD2=new TH3F("EffpreSelMCD2","EffpreSelMCD2",18,0,18,6,0,6,3,0,3);
TH3F * EffpreSelMCD1_R=new TH3F("EffpreSelMCD1_R","EffpreSelMCD1_R",43,0,43,6,0,6,3,0,3);
TH3F * EffpreSelMCD2_R=new TH3F("EffpreSelMCD2_R","EffpreSelMCD2_R",43,0,43,6,0,6,3,0,3);

TH2F * EffPreSelMCP_R_TH2F=new TH2F("EffPreSelMCP_R_TH2F","EffPreSelMCP_R_TH2F",43,0,43,3,0,3);
TH2F * EffPreSelMCP_TH2F=new TH2F("EffPreSelMCP_TH2F","EffPreSelMCP_TH2F",18,0,18,3,0,3);
TH3F * EffPreSelMCD_R_TH3F=new TH3F("EffPreSelMCD_R_TH3F","EffPreSelMCP_R_TH2F",43,0,43,6,0,6,3,0,3);
TH3F * EffPreSelMCD_TH3F=new TH3F("EffPreSelMCD_TH3F","EffPreSelMCD_TH3F",18,0,18,6,0,6,3,0,3);


void MCpreSeleff_Fill(TNtuple *ntupla, int l){
	int k = ntupla->GetEvent(l);
	//if(Beta_pre<=0||R_pre<=0||Beta_pre>protons->Eval(R_pre)+0.1||Beta_pre<protons->Eval(R_pre)-0.1) return;
	for(int S=0;S<3;S++){
		if(Massa_gen<1&&Massa_gen>0.5) {
			for(int M=0;M<43;M++) if(fabs(R_pre)<bin[M+1]&&fabs(R_pre)>bin[M]) {
				//if(EdepL1<EdepL1beta->Eval(Beta_pre)+0.2&&EdepL1>EdepL1beta->Eval(Beta_pre)-0.2){
					if(((int)Cutmask&notpassed[S])==notpassed[S]) EffpreSelMCP1_R->Fill(M,S);
					if(((int)Cutmask&passed[S])==passed[S]) EffpreSelMCP2_R->Fill(M,S);
			}	
			for(int m=0;m<18;m++)  if(Beta_pre>Betabins[m]&&Beta_pre<=Betabins[m+1]){
				//if(EdepL1<EdepL1beta->Eval(Beta_pre)+0.2&&EdepL1>EdepL1beta->Eval(Beta_pre)-0.2){
					if(((int)Cutmask&notpassed[S])==notpassed[S]) EffpreSelMCP1->Fill(m,S);
					if(((int)Cutmask&passed[S])==passed[S]) EffpreSelMCP2->Fill(m,S);	
			}
		}				 

		if(Massa_gen>1&&Massa_gen<2) {
			for(int M=0;M<43;M++) if(fabs(R_pre)<bin[M+1]&&fabs(R_pre)>bin[M]) {
				//if(EdepL1<EdepL1beta->Eval(Beta_pre)+0.2&&EdepL1>EdepL1beta->Eval(Beta_pre)-0.2){
					if(((int)Cutmask&notpassed[S])==notpassed[S]) EffpreSelMCD1_R->Fill(M,(int)(10000*Massa_gen-18570),S);
					if(((int)Cutmask&passed[S])==passed[S]) EffpreSelMCD2_R->Fill(M,(int)(10000*Massa_gen-18570),S);
			}
			for(int m=0;m<18;m++) if(Beta_pre>Betabins[m]&&Beta_pre<=Betabins[m+1]){
				//if(EdepL1<EdepL1beta->Eval(Beta_pre)+0.2&&EdepL1>EdepL1beta->Eval(Beta_pre)-0.2){
					if(((int)Cutmask&notpassed[S])==notpassed[S]) EffpreSelMCD1->Fill(m,(int)(10000*Massa_gen-18570),S);
					if(((int)Cutmask&passed[S])==passed[S]) EffpreSelMCD2->Fill(m,(int)(10000*Massa_gen-18570),S);
			}
		}
	}
	return;
}

void MCpreSeleff_Copy(TFile * file){
	EffpreSelMCP1= (TH2F*) file->Get("EffpreSelMCP1");
	EffpreSelMCD1= (TH3F*) file->Get("EffpreSelMCD1");
        EffpreSelMCP2= (TH2F*) file->Get("EffpreSelMCP2");
        EffpreSelMCD2= (TH3F*) file->Get("EffpreSelMCD2");
        EffpreSelMCP1_R =(TH2F*) file->Get("EffpreSelMCP1_R");
        EffpreSelMCD1_R =(TH3F*) file->Get("EffpreSelMCD1_R");
        EffpreSelMCP2_R =(TH2F*) file->Get("EffpreSelMCP2_R");
        EffpreSelMCD2_R =(TH3F*) file->Get("EffpreSelMCD2_R");
	
	return;	
}

void MCpreSeleff(TFile * file1){

	string numero[18]={"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17"};
	string tagli[3]={"Matching TOF","Chi^2 R","1 Tr. Track"};
	string nome;

	cout<<"**** MC \"GOLDEN\" SEL. EFFICIENCIES ****"<<endl;
	string MCLegend[7]={"protons.B800","d.pl1.0_520_GG_Blic","d.pl1.0_520_GG_BlicDPMJet","d.pl1.0_520_GG_QMD","d.pl1.0_520_Shen_Blic","d.pl1.0_520_Shen_BlicDPMJet","d.pl1.0_520_Shen_QMD"};
	float EffpreSelMCP[18][3];
	float EffpreSelMCD[18][6][3];
	float EffpreSelMCP_R[43][3];
	float EffpreSelMCD_R[43][6][3];	
	for(int i=1;i<43;i++) for(int h=0;h<6;h++) for(int m=0;m<17;m++) for(int S=0;S<3;S++){
        EffpreSelMCP_R[i][S]=0;
        EffpreSelMCD_R[i][h][S]=0; 
	EffpreSelMCP[m][S]=0;
        EffpreSelMCD[m][h][S]=0;
	}
	for(int S=0;S<3;S++){
		nome="Efficiency: "+tagli[S];
		c9[S]=new TCanvas(nome.c_str());
		c9[S]->Divide(2,1);
		
		for(int i=0;i<17;i++) if(EffpreSelMCP1->GetBinContent(i+1,S+1)>0) if(EffpreSelMCP2->GetBinContent(i+1,S+1)<EffpreSelMCP1->GetBinContent(i+1,S+1))
			EffpreSelMCP[i][S]=EffpreSelMCP2->GetBinContent(i+1,S+1)/(float)EffpreSelMCP1->GetBinContent(i+1,S+1);
		for(int i=0;i<17;i++) for(int h=0;h<6;h++) if(EffpreSelMCD2->GetBinContent(i+1,h+1,S+1)<EffpreSelMCD1->GetBinContent(i+1,h+1,S+1))
			EffpreSelMCD[i][h][S]=EffpreSelMCD2->GetBinContent(i+1,h+1,S+1)/(float)EffpreSelMCD1->GetBinContent(i+1,h+1,S+1);
		
		for(int i=1;i<43;i++) EffpreSelMCP_R[i][S]=EffpreSelMCP2_R->GetBinContent(i+1,S+1)/(float)EffpreSelMCP1_R->GetBinContent(i+1,S+1);
		for(int i=4;i<43;i++) for(int h=0;h<6;h++) if(EffpreSelMCD1_R->GetBinContent(i+1,h+1,S+1)>EffpreSelMCD2_R->GetBinContent(i+1,h+1,S+1))
			EffpreSelMCD_R[i][h][S]=EffpreSelMCD2_R->GetBinContent(i+1,h+1,S+1)/(float)EffpreSelMCD1_R->GetBinContent(i+1,h+1,S+1);
		
		c9[S]->cd(1);
		gPad->SetLogx();
		gPad->SetGridx();
		gPad->SetGridy();
		TGraph * EffPreSelMCP_R = new TGraph();
		EffPreSelMCP_R->SetTitle(MCLegend[0].c_str());
		for(int i=0;i<43;i++) EffPreSelMCP_R->SetPoint(i,R_cent[i],EffpreSelMCP_R[i][S]);
		for(int i=0;i<43;i++) EffPreSelMCP_R_TH2F->SetBinContent(i+1,S+1,EffpreSelMCP_R[i][S]);
		TGraph * EffPreSelMCD_R[6][3];
		EffPreSelMCP_R->SetMarkerColor(2);
		EffPreSelMCP_R->SetMarkerStyle(8);
		EffPreSelMCP_R->SetLineColor(2);
		EffPreSelMCP_R->SetLineWidth(2);
		nome="Efficiency: "+tagli[S]+ "MC (R bins)";
		EffPreSelMCP_R->SetTitle(nome.c_str());
		EffPreSelMCP_R->GetXaxis()->SetTitle("R [GV]");
		EffPreSelMCP_R->GetYaxis()->SetTitle("Pres. Efficiency");
		EffPreSelMCP_R->GetXaxis()->SetTitleSize(0.045);
		EffPreSelMCP_R->GetYaxis()->SetTitleSize(0.045);
		{
			EffPreSelMCP_R->Draw("ACP");
			TLegend* leg =new TLegend(0.4, 0.7,0.95,0.95);
			leg->AddEntry(EffPreSelMCP_R,MCLegend[0].c_str(), "ep");

			for(int h=0;h<6;h++){
				EffPreSelMCD_R[h][S]= new TGraph();
				EffPreSelMCD_R[h][S]->SetTitle(MCLegend[h+1].c_str());
				for(int i=1;i<43;i++) EffPreSelMCD_R[h][S]->SetPoint(i,R_cent[i],EffpreSelMCD_R[i][h][S]);
				for(int i=1;i<43;i++) EffPreSelMCD_R_TH3F->SetBinContent(i+1,h+1,S+1,EffpreSelMCD_R[i][h][S]);
				leg->AddEntry(EffPreSelMCD_R[h][S],MCLegend[h+1].c_str(), "ep");
				EffPreSelMCD_R[h][S]->SetMarkerColor(4);
				EffPreSelMCD_R[h][S]->SetMarkerStyle(h+3);
				EffPreSelMCD_R[h][S]->SetMarkerSize(2);
				EffPreSelMCD_R[h][S]->SetLineColor(4);
				EffPreSelMCD_R[h][S]->SetLineWidth(2);
				EffPreSelMCD_R[h][S]->Draw("Psame");
				leg->Draw();
			}
		}

		c9[S]->cd(2);
		gPad->SetLogx();
		gPad->SetGridx();
		gPad->SetGridy();
		TGraph * EffPreSelMCP = new TGraph();
		for(int i=0;i<17;i++) EffPreSelMCP->SetPoint(i,Ekincent[i],EffpreSelMCP[i][S]);
		for(int i=0;i<17;i++) EffPreSelMCP_TH2F->SetBinContent(i+1,S+1,EffpreSelMCP[i][S]);
		TGraph * EffPreSelMCD[6][3];
		EffPreSelMCP->SetMarkerColor(2);
		EffPreSelMCP->SetMarkerStyle(8);
		EffPreSelMCP->SetLineColor(2);
		EffPreSelMCP->SetLineWidth(2);
		EffPreSelMCP->SetTitle("Preselections Efficiency MC (Beta bins)");
		EffPreSelMCP->GetXaxis()->SetTitle("Kin. En. / nucl. [GeV/nucl.]");
		EffPreSelMCP->GetYaxis()->SetTitle("Pres. Efficiency");
		EffPreSelMCP->GetXaxis()->SetTitleSize(0.045);
		EffPreSelMCP->GetYaxis()->SetTitleSize(0.045);
		{
			EffPreSelMCP->Draw("ACP");
			TLegend* leg =new TLegend(0.4, 0.7,0.95,0.95);
			leg->AddEntry(EffPreSelMCP,MCLegend[0].c_str(), "ep");

			for(int h=0;h<6;h++){
				EffPreSelMCD[h][S]= new TGraph();
				for(int i=0;i<17;i++) EffPreSelMCD[h][S]->SetPoint(i,Ekincent[i],EffpreSelMCD[i][h][S]);
				for(int i=0;i<17;i++) EffPreSelMCD_TH3F->SetBinContent(i+1,h+1,S+1,EffpreSelMCD[i][h][S]);
				EffPreSelMCD[h][S]->SetMarkerColor(4);
				EffPreSelMCD[h][S]->SetMarkerStyle(h+3);
				leg->AddEntry(EffPreSelMCD[h][S],MCLegend[h+1].c_str(), "ep");
				EffPreSelMCD[h][S]->SetMarkerSize(2);
				EffPreSelMCD[h][S]->SetLineColor(4);
				EffPreSelMCD[h][S]->SetLineWidth(2);
				EffPreSelMCD[h][S]->Draw("Psame");
				leg->Draw();
			}
		}
	}
}

