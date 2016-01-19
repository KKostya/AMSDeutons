using namespace std;

TCanvas * c27 = new TCanvas("Rigidity Migration matrix");

TH2F * MigrMatrix = new TH2F("MigrMatrix","MigrMatrix",43,0,43,43,0,43);

void MigrationMatrix_Fill(TNtuple *ntupla, int l){
	int k = ntupla->GetEvent(l);
	if(!(Unbias==0&&((int)Cutmask&187)==187&&Beta_pre>0&&R_pre>0))	return;
	if(Massa_gen<1&&Massa_gen>0.5) {
                for(int M=0;M<43;M++) if(fabs(Momento_gen)<bin[M+1]&&fabs(Momento_gen)>bin[M]){
			for(int l=0;l<43;l++) if(fabs(R_pre)<bin[l+1]&&fabs(R_pre)>bin[l]) MigrMatrix->Fill(l,M);}
	}
	
}

void MigrationMatrix_Copy(TFile * file){
        MigrMatrix= (TH2F*) file->Get("MigrMatrix");
}

void MigrationMatrix(){
	float norm[43]={0};
	for(int M=0;M<43;M++)for(int l=0;l<43;l++) norm[M]+=MigrMatrix->GetBinContent(l+1,M+1);
	for(int M=0;M<43;M++)for(int l=0;l<43;l++) MigrMatrix->SetBinContent(l+1,M+1,MigrMatrix->GetBinContent(l+1,M+1)/norm[M]);
	c27->cd();
	gPad->SetLogz();
	MigrMatrix->GetXaxis()->SetTitle("n.bin (R meas)");
	MigrMatrix->GetYaxis()->SetTitle("n.bin (R gen)");
	MigrMatrix->Draw("col");
}
