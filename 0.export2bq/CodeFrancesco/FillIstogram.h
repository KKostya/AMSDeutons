using namespace std;

void FillIstogram(int INDX,string frac,string mese)

{


	//string percorso="/home/francesco/PhD/LocalCNAF/";
	string percorso="/storage/gpfs_ams/ams/users/fdimicco/";
	TH1F * Esposizione[11];
	string numero[11]={"0","1","2","3","4","5","6","7","8","9","10"};
	string tagli[10]={"Trigger","3of4 TOF","TRD Segments","Rigidity exists","Chi^2 R","Matching TOF","Matching TRD","In TRD Accept.","1 Particle","1 Tr. Track"};
	string nome;
	float DXWind[43];
	for(int i=0;i<11;i++) {
		nome="Esposizione"+numero[i];
		Esposizione[i]= new TH1F(nome.c_str(),nome.c_str(),43,0,43);
	}


	float fraz=1;
	float Q=0;
	float temp=0;
	float Zona=0;
	int UnbiasPre=9;
	float tempi[11]={0};
	float Esposizionegeo[43][11]={{0}};
	double geomag[12]={0,0,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.3};
	float DistTOF,DistTrack,DistTRD=0;
	string nomefile=percorso + "/Risultati/risultati/"+mese+"_"+frac+"_P1.root";
 	TFile *file =TFile::Open(nomefile.c_str());	
	if(!file){
	nomefile=percorso + "/Risultati/"+mese+"/"+mese+"_"+frac+"_P1.root";
	file =TFile::Open(nomefile.c_str());
	}
	TFile *file1;
	TNtuple *ntupla1;
	TNtuple *ntupla0;
	TFile *file2;
        TNtuple *ntupla3;
        TNtuple *ntupla2;
	if(!file) {cout<<"## Histograms file not detected: rebuilding from trigger ##"<<endl; INDX=0;}
	if(INDX!=2){	
	nomefile=percorso+"/Risultati/risultati/RisultatiMC_"+frac+".root";	
	file1 =TFile::Open(nomefile.c_str());
	if(!file1)  {nomefile=percorso + "/Risultati/"+mese+"/RisultatiMC_"+frac+".root";
		    file1 =TFile::Open(nomefile.c_str());}
	ntupla1=(TNtuple*)file1->Get("grandezzesepd");
	ntupla0=(TNtuple*)file1->Get("trig");
	nomefile=percorso+"/Risultati/risultati/RisultatiDATI_"+frac+".root";	
	file2 =TFile::Open(nomefile.c_str());
	if(!file2)  {nomefile=percorso+"/Risultati/"+mese+"/RisultatiDATI_"+frac+".root";
                    file2 =TFile::Open(nomefile.c_str());}
        ntupla3=(TNtuple*)file2->Get("grandezzesepd");
        ntupla2=(TNtuple*)file2->Get("trig");
	
	ntupla0->SetBranchAddress("Momento_gen",&Momento_gen);
	ntupla0->SetBranchAddress("Ev_Num",&Ev_Num);
	ntupla0->SetBranchAddress("Trig_Num",&Trig_Num);	
	ntupla0->SetBranchAddress("R_pre",&R_pre);
	ntupla0->SetBranchAddress("Beta_pre",&Beta_pre);
	ntupla0->SetBranchAddress("Cutmask",&CUTMASK);	
	ntupla0->SetBranchAddress("Massagen",&Massa_gen);
	ntupla0->SetBranchAddress("EdepL1",&EdepL1);	
	ntupla0->SetBranchAddress("EdepTOFU",&EdepTOFU);	
	ntupla0->SetBranchAddress("EdepTOFD",&EdepTOFD);
	ntupla0->SetBranchAddress("EdepTrack",&EdepTrack);
	ntupla0->SetBranchAddress("EdepECAL",&EdepECAL);
	ntupla0->SetBranchAddress("BetaRICH",&BetaRICH);
	ntupla0->SetBranchAddress("Unbias",&Unbias);


	ntupla1->SetBranchAddress("R",&R);
        ntupla1->SetBranchAddress("Beta",&Beta);
        ntupla1->SetBranchAddress("EdepL1",&EdepL1);
        ntupla1->SetBranchAddress("X",&X);
        ntupla1->SetBranchAddress("YTOFU",&YTOFU);
        ntupla1->SetBranchAddress("YTrack",&YTrack);
        ntupla1->SetBranchAddress("YTOFD",&YTOFD);
	ntupla1->SetBranchAddress("Massagen",&Massa_gen);
        ntupla1->SetBranchAddress("LDiscriminant",&LDiscriminant);
        ntupla1->SetBranchAddress("BDT_response",&BDT_response);
        ntupla1->SetBranchAddress("Cutmask",&CUTMASK);
	ntupla1->SetBranchAddress("Dist5D",&Dist5D);
	ntupla1->SetBranchAddress("Dist5D_P",&Dist5D_P);	
	
	ntupla2->SetBranchAddress("Rcutoff",&Rcutoff);
        ntupla2->SetBranchAddress("Ev_Num",&Ev_Num);
        ntupla2->SetBranchAddress("Trig_Num",&Trig_Num);
        ntupla2->SetBranchAddress("R_pre",&R_pre);
        ntupla2->SetBranchAddress("Beta_pre",&Beta_pre);
        ntupla2->SetBranchAddress("Cutmask",&CUTMASK);
        ntupla2->SetBranchAddress("Latitude",&Latitude);
	ntupla2->SetBranchAddress("EdepECAL",&EdepECAL);
	ntupla2->SetBranchAddress("EdepL1",&EdepL1);
        ntupla2->SetBranchAddress("EdepTOFU",&EdepTOFU);
        ntupla2->SetBranchAddress("EdepTOFD",&EdepTOFD);
        ntupla2->SetBranchAddress("EdepTrack",&EdepTrack);
        ntupla2->SetBranchAddress("BetaRICH",&BetaRICH);
        ntupla2->SetBranchAddress("Unbias",&Unbias);


        ntupla3->SetBranchAddress("R",&R);
        ntupla3->SetBranchAddress("Beta",&Beta);
        ntupla3->SetBranchAddress("EdepL1",&EdepL1);
        ntupla3->SetBranchAddress("Rcutoff",&Rcutoff);
	ntupla3->SetBranchAddress("X",&X);
        ntupla3->SetBranchAddress("YTOFU",&YTOFU);
        ntupla3->SetBranchAddress("YTrack",&YTrack);
        ntupla3->SetBranchAddress("YTOFD",&YTOFD);
        ntupla3->SetBranchAddress("Latitude",&Latitude);
	ntupla3->SetBranchAddress("Massagen",&Massa_gen);
        ntupla3->SetBranchAddress("LDiscriminant",&LDiscriminant);
        ntupla3->SetBranchAddress("BDT_response",&BDT_response);
        ntupla3->SetBranchAddress("Cutmask",&CUTMASK);
        ntupla3->SetBranchAddress("Dist5D",&Dist5D);
        ntupla3->SetBranchAddress("Dist5D_P",&Dist5D_P);
	}
	cout<<"*********************** MC READING *********************"<<endl;
	if(INDX==0)
	for(int i=0; i<ntupla0->GetEntries()/fraz;i++) {
		int k = ntupla0->GetEvent(i);
		Cutmask=CUTMASK;
		if(100*(i/(float)(ntupla0->GetEntries()/fraz))>avanzamento) {cout<<avanzamento<<endl;avanzamento=(int)(100*(i/(float)(ntupla0->GetEntries()/fraz)))+1;}
		Beta_gen=(pow(pow(Momento_gen/Massa_gen,2)/(1+pow(Momento_gen/Massa_gen,2)),0.5));
		MCpreseff_Fill(ntupla0,i);
		MCUnbiaseff_Fill(ntupla0,i);
		MCTrackeff_Fill(ntupla0,i);
		MCpreSeleff_Fill(ntupla0,i);
		MigrationMatrix_Fill(ntupla0,i);
		Correlazione_Preselezioni(ntupla0,i);
		DVSMCpreSeleff_Fill(ntupla0,i);
		DVSMCTrackeff_Fill(ntupla0,i);
	}
	if(INDX==0||INDX==1){
	avanzamento=0;
	for(int i=0; i<ntupla1->GetEntries();i++) {
		int k = ntupla1->GetEvent(i);
		Cutmask=CUTMASK;
        	if(100*(i/(float)(ntupla1->GetEntries()))>avanzamento) {cout<<avanzamento<<endl;avanzamento=(int)(100*(i/(float)(ntupla1->GetEntries())))+1;}
		MCQualeff_Fill(ntupla1,i);	
		MCQualCheck_Fill(ntupla1,i);
		MCQualCheck2_Fill(ntupla1,i);
	}
	}
	if(INDX==1||INDX==2){
		 MCpreeff_Copy(file);
		 MCUnbiaseff_Copy(file); 
		 MCTrackeff_Copy(file);
		 MCpreSeleff_Copy(file);
		 MigrationMatrix_Copy(file);
		 Correlazione_Preselezioni(file);
		 DVSMCpreSeleff_Copy(file);
		 DVSMCTrackeff_Copy(file);	
        }
        if(INDX==2){
                 MCQualeff_Copy(file);
		 MCQualCheck_Copy(file);
		 MCQualCheck2_Copy(file);
        }
	
	cout<<"*********************** DATA READING *********************"<<endl;
        if(INDX!=2){
	Tempi = (TH1F *)file2->Get("Tempi");
	esposizionegeo = (TH2F *)file2->Get("esposizionegeo");
	}
	else{
	Tempi = (TH1F *)file->Get("Tempi");
        esposizionegeo = (TH2F *)file->Get("esposizionegeo");
	}
	avanzamento=0;
	if(INDX==0)
	for(int i=0; i<ntupla2->GetEntries()/fraz;i++) {
                int k = ntupla2->GetEvent(i);
		Cutmask=CUTMASK;
		Massa=pow(fabs(pow(fabs(R_pre)*pow((1-pow(Beta_pre,2)),0.5)/Beta_pre,2)),0.5);
	        for(int z=0;z<12;z++){
                        double geo= geomag[z]  ;
                        double geo2=geomag[z+1];
                        if(Latitude>geo && Latitude<geo2) Zona=z;
        	}
		if(100*(i/(float)(ntupla2->GetEntries()/fraz))>avanzamento) {cout<<avanzamento<<endl;avanzamento=(int)(100*(i/(float)(ntupla2->GetEntries()/fraz)))+1;}
                Beta_gen=(pow(pow(Momento_gen/Massa_gen,2)/(1+pow(Momento_gen/Massa_gen,2)),0.5));
        	DATAUnbiaseff_Fill(ntupla2,i);
		DATApreSeleff_Fill(ntupla2,i,Zona);
		DVSMCpreSeleff_D_Fill(ntupla2,i,Zona);
		DVSMCTrackeff_D_Fill(ntupla0,i);		
	}
        if(INDX==0||INDX==1){
        avanzamento=0;
        for(int i=0; i<ntupla3->GetEntries();i++) {
                int k = ntupla3->GetEvent(i);
                Cutmask=CUTMASK;
                for(int z=0;z<12;z++){
                        double geo= geomag[z]  ;
                        double geo2=geomag[z+1];
                        if(Latitude>geo && Latitude<geo2) Zona=z;
                }
		if(100*(i/(float)(ntupla3->GetEntries()))>avanzamento) {cout<<avanzamento<<endl;avanzamento=(int)(100*(i/(float)(ntupla3->GetEntries())))+1;}
		DATAQualeff_Fill(ntupla3,i,Zona);
		DVSMCQualeff2_Fill(ntupla3,i,Zona);
		ProtonFlux_Fill(ntupla3,i,Zona);	
		}
        }
        if(INDX==1||INDX==2){
                 DATAUnbiaseff_Copy(file);
		 DATApreSeleff_Copy(file);
        }
        if(INDX==2){
		DATAQualeff_Copy(file);
		DVSMCQualeff2_Copy(file);
		ProtonFlux_Copy(file);
        }
	
	cout<<"************************ SAVING DATA ************************"<<endl;
	nomefile=percorso+"/Risultati/"+mese+"/"+mese+"_"+frac+"_P1.root";
	TFile *f_out=new TFile(nomefile.c_str(), "RECREATE");
	Tempi->Write();
	esposizionegeo->Write();
	MigrMatrix->Write();
	EffpreselMCP1->Write();
	EffpreselMCP2->Write();
	EffpreselMCP1_R->Write();
	EffpreselMCP2_R->Write();
	EffpreselMCD1->Write();
	EffpreselMCD2->Write();
	EffpreselMCD1_R->Write();
	EffpreselMCD2_R->Write();
	EffUnbiasMCP1->Write();
        EffUnbiasMCP2->Write();
        EffUnbiasMCP1_R->Write();
        EffUnbiasMCP2_R->Write();
        EffUnbiasMCD1->Write();
        EffUnbiasMCD2->Write();
        EffUnbiasMCD1_R->Write();
        EffUnbiasMCD2_R->Write();
	EffpreSelMCP1->Write();
        EffpreSelMCP2->Write();
        EffpreSelMCP1_R->Write();
        EffpreSelMCP2_R->Write();
        EffpreSelMCD1->Write();
        EffpreSelMCD2->Write();
        EffpreSelMCD1_R->Write();
        EffpreSelMCD2_R->Write();
	EffTriggMCP1->Write();
        EffTriggMCP2->Write();
        EffTriggMCP1_R->Write();
        EffTriggMCP2_R->Write();
        EffTriggMCD1->Write();
        EffTriggMCD2->Write();
        EffTriggMCD1_R->Write();
        EffTriggMCD2_R->Write();
	EffQTOFMCP1->Write();
        EffQTOFMCP2->Write();
        EffQTOFMCP1_R->Write();
        EffQTOFMCP2_R->Write();
        EffQTOFMCD1->Write();
        EffQTOFMCD2->Write();
        EffQTOFMCD1_R->Write();
        EffQTOFMCD2_R->Write();
	EffTrackMCP1->Write();
        EffTrackMCP2->Write();
        EffTrackMCP1_R->Write();
        EffTrackMCP2_R->Write();
        EffTrackMCD1->Write();
        EffTrackMCD2->Write();
        EffTrackMCD1_R->Write();
        EffTrackMCD2_R->Write();
	EffTOFMCP1->Write();
        EffTOFMCP2->Write();
        EffTOFMCP1_R->Write();
        EffTOFMCP2_R->Write();
        EffTOFMCD1->Write();
        EffTOFMCD2->Write();
        EffTOFMCD1_R->Write();
        EffTOFMCD2_R->Write();
	EffQualCheckMCP1->Write();
	EffQualCheckMCP2->Write();
	EffTOFUCheckMCP1->Write();
        EffTOFUCheckMCP2->Write();
	EffTrackCheckMCP1->Write();
        EffTrackCheckMCP2->Write();
	EffTOFDCheckMCP1->Write();
        EffTOFDCheckMCP2->Write();
	EffLikCheckMCP1->Write();
        EffLikCheckMCP2->Write();
	EffDistCheckMCP1->Write();
        EffDistCheckMCP2->Write();
        EffLik2CheckMCP1->Write(); 
        EffLik2CheckMCP2->Write();
	EffQualMCP->Write(); 
	EffQualMCP_Beta->Write(); 
	EffQualMCD->Write(); 
	EffQualMCD_Beta->Write();
	EffDistMCP->Write();
	EffDistMCP_Beta->Write();
	EffLikMCP->Write();
	EffLikMCP_Beta->Write();
	EffDistMCD->Write();
	EffDistMCD_Beta->Write();
        EffLikMCD->Write();
        EffLikMCD_Beta->Write();
	EffUnbiasDATA1->Write();
        EffUnbiasDATA2->Write();
        EffUnbiasDATA1_R->Write();
        EffUnbiasDATA2_R->Write();
        EffpreSelDATA1_R ->Write();
        EffpreSelDATA2_R ->Write();
	CorrelazionePreselezioni->Write();
	EffDistDATAP->Write();
        EffLikDATAP->Write();
	EffQualDATAP->Write(); 
	EffpreSelMCvsD1->Write();
	EffpreSelMCvsD2->Write();
	EffpreSelMCvsD1_R->Write();
	EffpreSelMCvsD2_R->Write();
	EffpreSelMCvsD1_D->Write();
        EffpreSelMCvsD2_D->Write();
        EffpreSelMCvsD1_R_D->Write();
        EffpreSelMCvsD2_R_D->Write();
	EffDistMCvsDP1->Write();
        EffDistMCvsDP2->Write();
        EffLik2MCvsDP1->Write();
        EffLik2MCvsDP2->Write();
	ECALvsR_D->Write();
	ECALvsR_MC->Write();
	PCountsgeo->Write();
	PCounts->Write();
	PCountsgeo_prim->Write();
	PCounts_pre->Write();
	PCounts_sel->Write();
	f_out->Write();
	f_out->Close();


	return;
}
