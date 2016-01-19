using namespace std;

TCanvas *c10 =new TCanvas("Cascade Pres. Eff.");

void MCpreCheck(){

	cout<<"**** MC P Eff. CHECK ****"<<endl;
	float EffPreCompP[43][8]={{0}};
	for(int i=1;i<43;i++) EffPreCompP[i][0]=EffTriggerMCP_R_TH1F->GetBinContent(i+1);
	for(int i=1;i<43;i++) EffPreCompP[i][1]=EffPreCompP[i][0]*EffTOF_MCP_R_TH1F->GetBinContent(i+1);
	for(int i=1;i<43;i++) EffPreCompP[i][2]=EffPreCompP[i][1]*1;//*EffQTOFerMCP_R_TH1F->GetBinContent(i+1);
	for(int i=1;i<43;i++) EffPreCompP[i][3]=EffPreCompP[i][2]*EffTrackerMCP_R_TH1F->GetBinContent(i+1);
	for(int i=1;i<43;i++) EffPreCompP[i][4]=EffPreCompP[i][3]*EffPreSelMCP_R_TH2F->GetBinContent(i+1,3);
	for(int i=1;i<43;i++) EffPreCompP[i][5]=EffPreCompP[i][4]*EffPreSelMCP_R_TH2F->GetBinContent(i+1,2);
	for(int i=1;i<43;i++) EffPreCompP[i][6]=EffPreCompP[i][5]*EffPreSelMCP_R_TH2F->GetBinContent(i+1,1);
	for(int i=1;i<43;i++)EffPreCompP[i][7]=EffPreCompP[i][6]*EffUnbMCP_R_TH1F->GetBinContent(i+1);	

	c10->cd();
        gPad->SetLogx();
        gPad->SetGridx();
        gPad->SetGridy();
        string MCLegend[8]={"3/4 TOF Activity","Beta from 3/4 cluster","TOF Charge","Track Exists","Only 1 Track","ChisquareY<5","TOF-Track Matching","Unbias==0"};
        TGraph * EffPreCompMCP_R[8]; 
	for(int h=0;h<8;h++) EffPreCompMCP_R[h]= new TGraph();
        TGraph * EffPreFullMCP_R = new TGraph();
	for(int h=0;h<8;h++){
	EffPreCompMCP_R[h]->SetTitle(MCLegend[h].c_str());
        for(int i=0;i<43;i++) EffPreCompMCP_R[h]->SetPoint(i,R_cent[i],EffPreCompP[i][h]);
        }
	for(int i=0;i<43;i++) EffPreFullMCP_R->SetPoint(i,R_cent[i],EffPreMCP_R_TH1F->GetBinContent(i+1));
	//TGraph * EffTrackerMCD_R[6];
      	for(int h=0;h<8;h++){
	EffPreCompMCP_R[h]->SetMarkerColor(h);
	EffPreFullMCP_R->SetMarkerColor(2);
        EffPreCompMCP_R[h]->SetMarkerStyle(8);
        EffPreFullMCP_R->SetMarkerStyle(4);
	EffPreCompMCP_R[h]->SetLineColor(h);
        EffPreCompMCP_R[h]->SetLineWidth(2);
	EffPreFullMCP_R->SetLineColor(2);
        EffPreFullMCP_R->SetLineWidth(2);
        EffPreFullMCP_R->GetXaxis()->SetTitle("R [GV]");
        EffPreFullMCP_R->GetYaxis()->SetTitle("Pres. Efficiency");
	EffPreFullMCP_R->GetYaxis()->SetRangeUser(0,1.1);
        EffPreFullMCP_R->GetXaxis()->SetTitleSize(0.045);
        EffPreFullMCP_R->GetYaxis()->SetTitleSize(0.045);
        }
	{
                EffPreFullMCP_R->Draw("ACP");
		TLegend* leg =new TLegend(0.4, 0.7,0.95,0.95);
                leg->AddEntry(EffPreFullMCP_R,"Full Set Cuts", "ep");
		for(int h=0;h<8;h++){
			EffPreCompMCP_R[h]->Draw("CPsame");
			leg->AddEntry(EffPreCompMCP_R[h],MCLegend[h].c_str(), "ep");
        	}
		leg->Draw("same");
	}

}
