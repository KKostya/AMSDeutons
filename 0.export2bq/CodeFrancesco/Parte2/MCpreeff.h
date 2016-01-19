using namespace std;

TCanvas *c4=new TCanvas("Preselections Efficiency on Top of Trigger");

TH1F * EffpreselMCP1=new TH1F("EffpreselMCP1","EffpreselMCP1",18,0,18);
TH1F * EffpreselMCP2=new TH1F("EffpreselMCP2","EffpreselMCP2",18,0,18);
TH1F * EffpreselMCP1_R=new TH1F("EffpreselMCP1_R","EffpreselMCP1_R",43,0,43);
TH1F * EffpreselMCP2_R=new TH1F("EffpreselMCP2_R","EffpreselMCP2_R",43,0,43);
TH2F * EffpreselMCD1=new TH2F("EffpreselMCD1","EffpreselMCD1",18,0,18,6,0,6);
TH2F * EffpreselMCD2=new TH2F("EffpreselMCD2","EffpreselMCD2",18,0,18,6,0,6);
TH2F * EffpreselMCD1_R=new TH2F("EffpreselMCD1_R","EffpreselMCD1_R",43,0,43,6,0,6);
TH2F * EffpreselMCD2_R=new TH2F("EffpreselMCD2_R","EffpreselMCD2_R",43,0,43,6,0,6);

TH1F *EffPreMCP_R_TH1F = new TH1F("EffPreMCP_R_TH1F","EffPreMCP_R_TH1F",43,0,43);
TH1F *EffPreMCP_TH1F = new TH1F("EffPreMCP_TH1F","EffPreMCP_TH1F",18,0,18);
TH2F *EffPreMCD_R_TH2F = new TH2F("EffPreMCD_R_TH2F","EffPreMCD_R_TH2F",43,0,43,6,0,6);
TH2F *EffPreMCD_TH2F = new TH2F("EffPreMCD_TH2F","EffPreMCD_TH2F",18,0,18,6,0,6);



void MCpreseff_Fill(TNtuple *ntupla, int l){
	int k = ntupla->GetEvent(l);
	if(Massa_gen<1&&Massa_gen>0.5) {
		for(int M=0;M<43;M++) if(fabs(Momento_gen)<bin[M+1]&&fabs(Momento_gen)>bin[M]) 
			EffpreselMCP1_R->Fill(M);
		if(/*Unbias==0&&*/((int)Cutmask&187)==187&&Beta_pre>0&&R_pre>0) 
			for(int M=0;M<43;M++) if(fabs(R_pre)<bin[M+1]&&fabs(R_pre)>bin[M]) 	
				//if(EdepTOFU<EdepTOFbeta->Eval(Beta_pre)+1&&EdepTOFU>EdepTOFbeta->Eval(Beta_pre)-1) //taglio x valutare efficienza
				EffpreselMCP2_R->Fill(M);

		for(int m=0;m<18;m++)  if(Beta_gen>Betabins[m]&&Beta_gen<=Betabins[m+1]){
			EffpreselMCP1->Fill(m);
			if(/*Unbias==0&&*/((int)Cutmask&187)==187&&Beta_pre>0&&R_pre>0) 
				//if(EdepTOFU<EdepTOFbeta->Eval(Beta_pre)+1&&EdepTOFU>EdepTOFbeta->Eval(Beta_pre)-1)
				EffpreselMCP2->Fill(m);	
		}
	}				 

	if(Massa_gen>1&&Massa_gen<2) {
		for(int M=0;M<43;M++) if(fabs(Momento_gen)<bin[M+1]&&fabs(Momento_gen)>bin[M]) 
			EffpreselMCD1_R->Fill(M,(int)(10000*Massa_gen-18570));
		if(((int)Cutmask&187)==187&&Beta_pre>0&&Unbias==0&&R_pre>0) 
			for(int M=0;M<43;M++) if(fabs(R_pre)<bin[M+1]&&fabs(R_pre)>bin[M])	
				//if(EdepTOFU<EdepTOFbeta->Eval(Beta_pre)+1&&EdepTOFU>EdepTOFbeta->Eval(Beta_pre)-1) //taglio x valutare efficienza
				EffpreselMCD2_R->Fill(M,(int)(10000*Massa_gen-18570));

		for(int m=0;m<18;m++) if(Beta_gen>Betabins[m]&&Beta_gen<=Betabins[m+1]){
			EffpreselMCD1->Fill(m,(int)(10000*Massa_gen-18570));
			if(((int)Cutmask&187)==187&&Beta_pre>0&&Unbias==0&&R_pre>0) 
				//if(EdepTOFU<EdepTOFbeta->Eval(Beta_pre)+1&&EdepTOFU>EdepTOFbeta->Eval(Beta_pre)-1) //taglio x valutare efficienza
				EffpreselMCD2->Fill(m,(int)(10000*Massa_gen-18570));
		}
	}

	return;
}

void MCpreeff_Copy(TFile * file){
	EffpreselMCP1= (TH1F*) file->Get("EffpreselMCP1");
	EffpreselMCD1= (TH2F*) file->Get("EffpreselMCD1");
	EffpreselMCP2= (TH1F*) file->Get("EffpreselMCP2");
	EffpreselMCD2= (TH2F*) file->Get("EffpreselMCD2");
	EffpreselMCP1_R =(TH1F*) file->Get("EffpreselMCP1_R");
	EffpreselMCD1_R =(TH2F*) file->Get("EffpreselMCD1_R");
	EffpreselMCP2_R =(TH1F*) file->Get("EffpreselMCP2_R");
	EffpreselMCD2_R =(TH2F*) file->Get("EffpreselMCD2_R");

	return;	
}

void MCpreeff(TFile * file1){

	string numero[18]={"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17"};
	string tagli[10]={"Trigger","3of4 TOF","TRD Segments","Rigidity exists","Chi^2 R","Matching TOF","Matching TRD","In TRD Accept.","1 Particle","1 Tr. Track"};
	string nome;

	cout<<"**** MC PRESELECTIONS EFFICIENCY (FULL SET) ****"<<endl;
	c4->Divide(2,1);
	float EffpreselMCP[18]={0};
	for(int i=0;i<17;i++) if(EffpreselMCP1->GetBinContent(i+1)>0) if(EffpreselMCP2->GetBinContent(i+1)<EffpreselMCP1->GetBinContent(i+1))
		EffpreselMCP[i]=EffpreselMCP2->GetBinContent(i+1)/(float)EffpreselMCP1->GetBinContent(i+1);
	float EffpreselMCD[18][6]={{0}};
	for(int i=0;i<17;i++) for(int h=0;h<6;h++) if(EffpreselMCD2->GetBinContent(i+1,h+1)<EffpreselMCD1->GetBinContent(i+1,h+1))
		EffpreselMCD[i][h]=EffpreselMCD2->GetBinContent(i+1,h+1)/(float)EffpreselMCD1->GetBinContent(i+1,h+1);

	float EffpreselMCP_R[43]={0};
	for(int i=1;i<43;i++) EffpreselMCP_R[i]=EffpreselMCP2_R->GetBinContent(i+1)/(float)EffpreselMCP1_R->GetBinContent(i+1);
	float EffpreselMCD_R[43][6]={{0}};
	for(int i=4;i<43;i++) for(int h=0;h<6;h++) if(EffpreselMCD1_R->GetBinContent(i+1,h+1)>EffpreselMCD2_R->GetBinContent(i+1,h+1))
		EffpreselMCD_R[i][h]=EffpreselMCD2_R->GetBinContent(i+1,h+1)/(float)EffpreselMCD1_R->GetBinContent(i+1,h+1);

	c4->cd(1);
	gPad->SetLogx();
	gPad->SetGridx();
	gPad->SetGridy();
	string MCLegend[7]={"protons.B800","d.pl1.0_520_GG_Blic","d.pl1.0_520_GG_BlicDPMJet","d.pl1.0_520_GG_QMD","d.pl1.0_520_Shen_Blic","d.pl1.0_520_Shen_BlicDPMJet","d.pl1.0_520_Shen_QMD"};
	TGraph * EffPreMCP_R = new TGraph();
	EffPreMCP_R->SetTitle(MCLegend[0].c_str());
	for(int i=0;i<43;i++) EffPreMCP_R->SetPoint(i,R_cent[i],EffpreselMCP_R[i]);
	for(int i=0;i<43;i++) EffPreMCP_R_TH1F->SetBinContent(i+1,EffpreselMCP_R[i]);
	TGraph * EffPreMCD_R[6];
	EffPreMCP_R->SetMarkerColor(2);
	EffPreMCP_R->SetMarkerStyle(8);
	EffPreMCP_R->SetLineColor(2);
	EffPreMCP_R->SetLineWidth(2);
	EffPreMCP_R->SetTitle("Preselections Efficiency MC (R bins)");
	EffPreMCP_R->GetXaxis()->SetTitle("R [GV]");
	EffPreMCP_R->GetYaxis()->SetTitle("Pres. Efficiency");
	EffPreMCP_R->GetXaxis()->SetTitleSize(0.045);
	EffPreMCP_R->GetYaxis()->SetTitleSize(0.045);
	{
		EffPreMCP_R->Draw("ACP");
		TLegend* leg =new TLegend(0.4, 0.7,0.95,0.95);
		leg->AddEntry(EffPreMCP_R,MCLegend[0].c_str(), "ep");

		for(int h=0;h<6;h++){
			EffPreMCD_R[h]= new TGraph();
			EffPreMCD_R[h]->SetTitle(MCLegend[h+1].c_str());
			for(int i=1;i<43;i++) EffPreMCD_R[h]->SetPoint(i,R_cent[i],EffpreselMCD_R[i][h]);
			for(int i=1;i<43;i++) EffPreMCD_R_TH2F->SetBinContent(i+1,h+1,EffpreselMCD_R[i][h]);
			leg->AddEntry(EffPreMCD_R[h],MCLegend[h+1].c_str(), "ep");
			EffPreMCD_R[h]->SetMarkerColor(4);
			EffPreMCD_R[h]->SetMarkerStyle(h+3);
			EffPreMCD_R[h]->SetMarkerSize(2);
			EffPreMCD_R[h]->SetLineColor(4);
			EffPreMCD_R[h]->SetLineWidth(2);
			EffPreMCD_R[h]->Draw("Psame");
			leg->Draw();
		}
	}

	c4->cd(2);
	gPad->SetLogx();
	gPad->SetGridx();
	gPad->SetGridy();
	TGraph * EffPreMCP = new TGraph();
	for(int i=0;i<17;i++) EffPreMCP->SetPoint(i,Ekincent[i],EffpreselMCP[i]);
	for(int i=0;i<17;i++) EffPreMCP_TH1F->SetBinContent(i+1,EffpreselMCP[i]);
	TGraph * EffPreMCD[6];
	EffPreMCP->SetMarkerColor(2);
	EffPreMCP->SetMarkerStyle(8);
	EffPreMCP->SetLineColor(2);
	EffPreMCP->SetLineWidth(2);
	EffPreMCP->SetTitle("Preselections Efficiency MC (Beta bins)");
	EffPreMCP->GetXaxis()->SetTitle("Kin. En. / nucl. [GeV/nucl.]");
	EffPreMCP->GetYaxis()->SetTitle("Pres. Efficiency");
	EffPreMCP->GetXaxis()->SetTitleSize(0.045);
	EffPreMCP->GetYaxis()->SetTitleSize(0.045);
	{
		EffPreMCP->Draw("ACP");
		TLegend* leg =new TLegend(0.4, 0.7,0.95,0.95);
		leg->AddEntry(EffPreMCP,MCLegend[0].c_str(), "ep");

		for(int h=0;h<6;h++){
			EffPreMCD[h]= new TGraph();
			for(int i=0;i<17;i++) EffPreMCD[h]->SetPoint(i,Ekincent[i],EffpreselMCD[i][h]);
			for(int i=0;i<17;i++) EffPreMCD_TH2F->SetBinContent(i+1,h+1,EffpreselMCD[i][h]);
			EffPreMCD[h]->SetMarkerColor(4);
			EffPreMCD[h]->SetMarkerStyle(h+3);
			leg->AddEntry(EffPreMCD[h],MCLegend[h+1].c_str(), "ep");
			EffPreMCD[h]->SetMarkerSize(2);
			EffPreMCD[h]->SetLineColor(4);
			EffPreMCD[h]->SetLineWidth(2);
			EffPreMCD[h]->Draw("Psame");
			leg->Draw();
		}
	}
}
