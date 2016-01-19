using namespace std;

TCanvas *c28= new TCanvas("R vs ECAL E.dep.");
TH2F * ECALvsR_D=new TH2F("ECALvsR_D","ECALvsR_D",1000,0,100,1000,0,100);
TH2F * ECALvsR_MC=new TH2F("ECALvsR_MC","ECALvsR_MC",1000,0,100,1000,0,100);

void DVSMCTrackeff_D_Fill(TNtuple *ntupla, int l){
        int k = ntupla->GetEvent(l);
        if(Unbias!=0||Beta_pre<=0) return;
		if(R_pre>1.2*Rcutoff){
			if(EdepTOFU<EdepTOFbeta->Eval(Beta_pre)+1&&EdepTOFU>EdepTOFbeta->Eval(Beta_pre)-1&&((int)Cutmask&3)==3)
			ECALvsR_D->Fill(R_pre,EdepECAL);
		}
        return;
}


void DVSMCTrackeff_Fill(TNtuple *ntupla, int l){
	int k = ntupla->GetEvent(l);
        if(Unbias!=0||Beta_pre<=0) return;
                if(Massa_gen<1&&Massa_gen>0.5){
                        if(EdepTOFU<EdepTOFbeta->Eval(Beta_pre)+1&&EdepTOFU>EdepTOFbeta->Eval(Beta_pre)-1&&((int)Cutmask&3)==3)
                        ECALvsR_MC->Fill(R_pre,EdepECAL);
                }
        return;

}


void DVSMCTrackeff_Copy(TFile * file){
        ECALvsR_D =(TH2F*) file->Get("ECALvsR_D");
	ECALvsR_MC =(TH2F*) file->Get("ECALvsR_MC");
        return;
}

void DVSMCTrackeff(TFile * file){
	c28->Divide(1,2);
	c28->cd(1);
	gPad->SetLogx();
	gPad->SetLogy();
	gPad->SetLogz();
	ECALvsR_MC->SetTitle("Protons MC");
	ECALvsR_MC->GetXaxis()->SetTitle("R [GV]");
	ECALvsR_MC->GetYaxis()->SetTitle("ECAL E.dep.");
	ECALvsR_MC->Draw("col");
	c28->cd(2);
        gPad->SetLogx();
        gPad->SetLogy();
	gPad->SetLogz();
        ECALvsR_D->SetTitle("DATA");
        ECALvsR_D->GetXaxis()->SetTitle("R [GV]");
        ECALvsR_D->GetYaxis()->SetTitle("ECAL E.dep.");
        ECALvsR_D->Draw("col");
}
