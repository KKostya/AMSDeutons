using namespace std;

TCanvas * c23 = new TCanvas("Protons Flux: Geo. Zones");
TCanvas * c24 = new TCanvas("Primary Protons Flux");
TCanvas * c25 = new TCanvas("Protons Flux: Pre vs Qual");


TH3F * PFluxgeo = new TH3F("PFluxgeo","PFluxgeo",43,0,43,11,0,11,2,0,2);
TH2F * PFlux = new TH2F("PFlux","PFlux",43,0,43,2,0,2);
TH2F * PFluxpre = new TH2F("PFluxpre","PFluxpre",43,0,43,2,0,2);
TH2F * PFluxsel = new TH2F("PFluxsel","PFluxsel",43,0,43,2,0,2);

TH1F * PCounts = new TH1F("PCounts","PCounts",43,0,43);
TH1F * PCounts_pre = new TH1F("PCounts_pre","PCounts_pre",43,0,43);
TH1F * PCounts_sel = new TH1F("PCounts_sel","PCounts_sel",43,0,43);
string numero[11]={"0","1","2","3","4","5","6","7","8","9","10"};
TGraphErrors * P_Fluxgeo[11];
TGraphErrors * P_Flux;
TGraphErrors * P_Flux_pre;
float potenza=2.7;
//string percorso="/home/francesco/PhD/LocalCNAF/";
string percorso="/storage/gpfs_ams/ams/users/fdimicco/";
void ProtonFlux_Fill(TNtuple *ntupla, int l,int zona){
        int k = ntupla->GetEvent(l);
        if(Beta<=0||R<=0) return;
        if(Dist5D_P<6&&LDiscriminant>0.7){
                for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]) {PCountsgeo->Fill(K,zona);}
                for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]) if(R>1.2*Rcutoff) {PCountsgeo_prim->Fill(K,zona);}
		if(R>1.2*Rcutoff) for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]) {PCounts->Fill(K);}
        }
	if(!(EdepL1<EdepL1beta->Eval(Beta)+0.2&&EdepL1>EdepL1beta->Eval(Beta)-0.2)) return;
	if(Beta>protons->Eval(R)+0.1||Beta<protons->Eval(R)-0.1) return;
	for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]&&R>1.2*Rcutoff) {
			PCounts_pre->Fill(K);
        		if(Dist5D_P<6&&LDiscriminant>0.7) PCounts_sel->Fill(K);
			}
			
	return;
}

void ProtonFlux_Copy(TFile * file1){
        PCountsgeo = (TH2F *)file1->Get("PCountsgeo");
        PCountsgeo_prim = (TH2F *)file1->Get("PCountsgeo_prim");
	PCounts = (TH1F *)file1->Get("PCounts");
	PCounts_pre = (TH1F *)file1->Get("PCounts_pre");
	PCounts_sel = (TH1F *)file1->Get("PCounts_sel");
}

void ProtonFlux(TFile * file1){
	Tempi = (TH1F *)file1->Get("Tempi");
	cout<<"*************** Protons Fluxes Calculation ******************"<<endl;	
	float AcceptLAT[43]={0};
	float AcceptLAT_pre[43]={0};
	float Espos_R[43]={0};
	float errore=0;
	

	for(int j=1;j<43;j++)
			AcceptLAT[j]=(AcceptPzone->GetBinContent(j+1,1));

	for(int j=1;j<43;j++)
		for(int i=1;i<11;i++)
			AcceptLAT_pre[j]=(AcceptPzone_pre->GetBinContent(j+1,1));


	for(int j=1;j<43;j++)
		for(int i=1;i<11;i++) Espos_R[j]+=esposizionegeo->GetBinContent(j,i);

	for(int j=1;j<43;j++){
		AcceptLAT[j]=AcceptLAT[j]/CorrLAT_totM2->GetBinContent(j+1,1);
		AcceptLAT_pre[j]=AcceptLAT_pre[j]/CorrLAT_preM2->GetBinContent(j+1,1);
	}

	for(int l =0;l<11;l++)	
		for(int i=0;i<43;i++) 
			if(AcceptPzone->GetBinContent(i+1,l+1)>0&&Tempi->GetBinContent(l)>0){
		      PFluxgeo->SetBinContent(i+1,l+1,0,PCountsgeo->GetBinContent(i+1,l+1)/(AcceptPzone->GetBinContent(i+1,l+1)*Tempi->GetBinContent(l)*deltaencinprot[i]));
		      //err stat
		       errore=pow(pow(PCountsgeo->GetBinContent(i+1,l+1),0.5)/PCountsgeo->GetBinContent(i+1,l+1),2);
		      //err lat corr
		       errore=errore+CorrLAT_tot_spl->GetBinContent(l+1,2);
			//err D vs MC
			for(int S=0;S<3;S++) errore=errore+pow(PreDVSMC_P[S]->GetBinContent(i+1,2)/PreDVSMC_P[S]->GetBinContent(i+1,1),2);
			errore=errore+pow(LikDVSMC_P_graph->GetBinContent(i+1,2)/LikDVSMC_P_graph->GetBinContent(i+1,1),2);
			
			errore=pow(errore,0.5);
			PFluxgeo->SetBinContent(i+1,l+1,1,errore*PFluxgeo->GetBinContent(i+1,l+1,0));
			}
	for(int i=0;i<43;i++)
		if(AcceptLAT[i]>0&&Espos_R[i]>0){
			PFlux->SetBinContent(i+1,1,PCounts->GetBinContent(i+1)/(AcceptLAT[i]*Espos_R[i]*deltaencinprot[i]));
			errore=0;
			//err stat
			errore=pow(pow(PCounts->GetBinContent(i+1),0.5)/PCounts->GetBinContent(i+1),2);		
			//err lat corr
			errore=errore+pow(CorrLAT_preM2->GetBinContent(i+1,2)/CorrLAT_preM2->GetBinContent(i+1,1),2);
			//err D vs MC
			for(int S=0;S<3;S++) errore=errore+pow(PreDVSMC_P[S]->GetBinContent(i+1,2)/PreDVSMC_P[S]->GetBinContent(i+1,1),2);
                        errore=errore+pow(LikDVSMC_P_graph->GetBinContent(i+1,2)/LikDVSMC_P_graph->GetBinContent(i+1,1),2);
			errore=errore+pow(0.01,2);
			//err sist somma
			errore=pow(errore,0.5);
			PFlux->SetBinContent(i+1,2,errore*PFlux->GetBinContent(i+1,1));
			}	
	
	for(int i=0;i<43;i++)
		if(AcceptLAT_pre[i]>0){
			PFluxpre->SetBinContent(i+1,1,PCounts_pre->GetBinContent(i+1)/(AcceptLAT_pre[i]*Espos_R[i]*deltaencinprot[i]));
			errore=0;
			//err stat
			errore=pow(pow(PCounts_pre->GetBinContent(i+1),0.5)/PCounts_pre->GetBinContent(i+1),2);		
			//err lat corr
			errore=errore+pow(CorrLAT_preM2->GetBinContent(i+1,2)/CorrLAT_preM2->GetBinContent(i+1,1),2);
			//err D vs MC
			for(int S=0;S<3;S++) errore=errore+pow(PreDVSMC_P[S]->GetBinContent(i+1,2)/PreDVSMC_P[S]->GetBinContent(i+1,1),2);
                        errore=errore+pow(LikDVSMC_P_graph->GetBinContent(i+1,2)/LikDVSMC_P_graph->GetBinContent(i+1,1),2);
			//err sist somma
			errore=errore+pow(0.01,2);
			errore=pow(errore,0.5);
			PFluxpre->SetBinContent(i+1,2,errore*PFluxpre->GetBinContent(i+1,1));
			
			}
	
	for(int i=0;i<43;i++)
		if(AcceptLAT[i]>0){
			PFluxsel->SetBinContent(i+1,1,PCounts_sel->GetBinContent(i+1)/(AcceptLAT[i]*Espos_R[i]*deltaencinprot[i]));
			errore=0;
                        errore=pow(pow(PCounts_sel->GetBinContent(i+1),0.5)/PCounts_sel->GetBinContent(i+1),2);
			//err lat corr
			errore=errore+pow(CorrLAT_totM2->GetBinContent(i+1,2)/CorrLAT_totM2->GetBinContent(i+1,1),2);
			//err D vs MC
			for(int S=0;S<3;S++) errore=errore+pow(PreDVSMC_P[S]->GetBinContent(i+1,2)/PreDVSMC_P[S]->GetBinContent(i+1,1),2);	
			errore=errore+pow(0.01,2);
			//err sist somma
			errore=pow(errore,0.5);
			PFluxsel->SetBinContent(i+1,2,errore*PFluxsel->GetBinContent(i+1,1));
			}


	c23->cd();
	gPad->SetLogx();
	gPad->SetLogy();
	gPad->SetGridx();
	gPad->SetGridy();
	string nome;
	for(int j=0;j<11;j++) {
		nome="Protons Flux: Geo. Zone "+numero[j];
		P_Fluxgeo[j]=new TGraphErrors();
		P_Fluxgeo[j]->SetName(nome.c_str());
		for(int i=0;i<43;i++){
				      P_Fluxgeo[j]->SetPoint(i,encinprot[i],PFluxgeo->GetBinContent(i+1,j+1,0)*pow(encinprot[i],potenza));
				      P_Fluxgeo[j]->SetPointError(i,0,PFluxgeo->GetBinContent(i+1,j+1,1)*pow(encinprot[i],potenza));
					}	
		P_Fluxgeo[j]->SetMarkerStyle(8);
		P_Fluxgeo[j]->SetMarkerColor(j-1);
		P_Fluxgeo[j]->SetLineColor(j-1);
		P_Fluxgeo[j]->SetLineWidth(2);
	}
	P_Fluxgeo[10]->SetTitle("Protons Flux: Geo. Zones");
	P_Fluxgeo[10]->GetXaxis()->SetTitle("R [GV]");
	P_Fluxgeo[10]->GetYaxis()->SetTitle("Flux [(m^2 sr GeV/nucl.)^-1]");
	P_Fluxgeo[10]->GetXaxis()->SetTitleSize(0.045);
	P_Fluxgeo[10]->GetYaxis()->SetTitleSize(0.045);
	P_Fluxgeo[10]->GetYaxis()->SetRangeUser(1e-2,1e4);
	P_Fluxgeo[10]->Draw("AP");
	for(int j=0;j<11;j++) P_Fluxgeo[j]->Draw("Psame");

	c24->cd();
	gPad->SetLogx();
	gPad->SetLogy();
	gPad->SetGridx();
	gPad->SetGridy();
	P_Flux=new TGraphErrors();
	for(int i=0;i<43;i++) {P_Flux->SetPoint(i,encinprot[i],PFlux->GetBinContent(i+1,1)*pow(encinprot[i],potenza));
			       P_Flux->SetPointError(i,0,PFlux->GetBinContent(i+1,2)*pow(encinprot[i],potenza));	
	}
	P_Flux->SetName("Protons Primary Flux");
	P_Flux->SetMarkerStyle(8);
	P_Flux->SetMarkerColor(2);
	P_Flux->SetTitle("Primary Protons Flux");
	P_Flux->GetXaxis()->SetTitle("R [GV]");
	P_Flux->GetYaxis()->SetTitle("Flux [(m^2 sr GeV/nucl.)^-1]");
	P_Flux->GetXaxis()->SetTitleSize(0.045);
	P_Flux->GetYaxis()->SetTitleSize(0.045);
	P_Flux->GetYaxis()->SetRangeUser(1e-2,1e4);
	P_Flux->Draw("AP");
	P_Fluxgeo[10]->Draw("Psame");
	TGraph* galprop3P=new TGraph();
	TGraph* galprop3P2=new TGraph();
	float x,y=0;
	int j=0;
	{
		string nomefile=percorso+"/CodesforAnalysis/Galprop/Trotta2011/Def/new_P200.txt";
		ifstream fp(nomefile.c_str());
		while (!fp.eof()){
			fp>>x>>y;
			if(x/1e3>0.05&&x/1e3<=100)
				galprop3P->SetPoint(j,x/1e3,y*1e7*pow(x/1e3,potenza));
			j++;
		}
	}

	j=0;
	{
		string nomefile=percorso+"/CodesforAnalysis/Galprop/Trotta2011/Def/new_P1250.txt";
		ifstream fp(nomefile.c_str());
		while (!fp.eof()){
			fp>>x>>y;
			if(x/1e3>0.05&&x/1e3<=100)
				galprop3P2->SetPoint(j,x/1e3,y*1e7*pow(x/1e3,potenza));
			j++;
		}
	}

	galprop3P->Draw("sameC");
	galprop3P2->Draw("sameC");

	c25->cd();
        gPad->SetLogx();
        gPad->SetGridx();
        gPad->SetGridy();
	TGraphErrors * P_Fluxpre=new TGraphErrors();
	TGraphErrors * P_Flux_=new TGraphErrors();
	P_Flux_pre=new TGraphErrors();
	P_Flux_pre->SetName("Protons Primary Flux (only pres.)");
	int p=0;
	for(int i=1;i<43;i++) if(PFluxpre->GetBinContent(i+1,1)>0&&PFluxsel->GetBinContent(i+1,1)>0) {
		P_Flux_->SetPoint(p,R_cent[i],PFluxpre->GetBinContent(i+1,1)/PFluxpre->GetBinContent(i+1,1));
		P_Flux_pre->SetPoint(p,R_cent[i],PFluxpre->GetBinContent(i+1,1));
		P_Flux_->SetPointError(p,0,(PFluxpre->GetBinContent(i+1,2)+PFluxsel->GetBinContent(i+1,2))/PFluxpre->GetBinContent(i+1,1));
		p++;}
	p=0;
	for(int i=1;i<43;i++) if(PFluxpre->GetBinContent(i+1,1)>0&&PFluxsel->GetBinContent(i+1,1)>0) {
			P_Fluxpre->SetPoint(p,R_cent[i],PFluxsel->GetBinContent(i+1,1)/PFluxpre->GetBinContent(i+1,1));
			p++;}
	P_Fluxpre->SetMarkerStyle(8);
        P_Fluxpre->SetMarkerColor(2);
	P_Flux_->SetMarkerStyle(4);
	P_Flux_->SetFillStyle(3002);
	P_Flux_->SetFillColor(4);
        P_Flux_->SetMarkerColor(2);
	P_Fluxpre->SetTitle("Primary Protons Flux");
        P_Fluxpre->GetXaxis()->SetTitle("R [GV]");
        P_Fluxpre->GetYaxis()->SetTitle("Flux [(m^2 sr GeV/nucl.)^-1]");
        P_Fluxpre->GetXaxis()->SetTitleSize(0.045);
        P_Fluxpre->GetYaxis()->SetTitleSize(0.045);
        P_Fluxpre->GetYaxis()->SetRangeUser(0.8,1.2);
	P_Fluxpre->Draw("AP");
	P_Flux_->Draw("P4same");	
}

