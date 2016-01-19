TCanvas *c13=new TCanvas("Correlazione Selezioni");
TH2F * CorrelazionePreselezioni = new TH2F("CorrelazionePreselezioni","CorrelazionePreselezioni",11,0,11,11,0,11);
int Norm[11]={0};

void Correlazione_Preselezioni(TNtuple *ntupla, int l){
	int k = ntupla->GetEvent(l);
	for(int S=0;S<10;S++){
		if((((int)Cutmask>>S)&1)==1){
			for(int F=0;F<10;F++) if((((int)Cutmask>>F)&1)==1) CorrelazionePreselezioni->Fill(S,F);
			if(Unbias==0)  CorrelazionePreselezioni->Fill(S,10);
		}		
		if((((int)Cutmask>>S)&1)==1) Norm[S]++;
	}
	if(Unbias==0){
		for(int F=0;F<10;F++) if((((int)Cutmask>>F)&1)==1) CorrelazionePreselezioni->Fill(10,F);
		if(Unbias==0) {CorrelazionePreselezioni->Fill(10,10);Norm[10]++;}
	}
}

void Correlazione_Preselezioni_Copy(TFile * file){
	CorrelazionePreselezioni = (TH2F*) file->Get("CorrelazionePreselezioni");
	return;
}

void Correlazione_Preselezioni(TFile * file){
	for(int S=0;S<11;S++)
		for(int F=0;F<11;F++) if(Norm[S]>0) CorrelazionePreselezioni->SetBinContent(S+1,F+1,CorrelazionePreselezioni->GetBinContent(S+1,F+1)/(float)Norm[S]);
	c13->cd();
	CorrelazionePreselezioni->Draw("col");
}
