#include "embed_species.h"
void dev_ana(){
TH1::SetDefaultSumw2(true);
TH2::SetDefaultSumw2(true);

const string filename="isobar_trk_eff_ptmix_blend.root";
const string key="blended";
species_plots species(filename,key,key,"pt");
const int stack_dim=1;
vector<int> stack_bin={1,5,9,13,15,17};


TH2F** devs=dev_stack(species,stack_dim,stack_bin);
TCanvas* c4=new TCanvas("c4");
TH1F* disect[5][10];
c4->Divide(3,2);


gStyle->SetPalette(kValentine);
for(int i=0;i<5;i++){
    cout<<devs[i]->GetNbinsX()<<endl; 
    c4->cd(i+1);
    for(int j=0;j<10;j++){
    	disect[i][j]=(TH1F*)devs[i]->ProjectionY(Form("dev_proj_%i_%i",i,j),40*j+1,40*(j+1),"");
	disect[i][j]->GetXaxis()->SetRangeUser(-0.3,0.3);
	disect[i][j]->Draw("same PLC PLM");
    }

//    c4->SetLogz();
//    devs[i]->GetXaxis()->SetRangeUser(0,20);
//    devs[i]->Draw("colz");
}
//c4->Draw();

TCanvas* c0=new TCanvas("c0");
c0->Divide(3,2);
for(int i=0;i<5;i++){
    c0->cd(i+1);
    TProfile* pf=devs[i]->ProfileX(Form("dev_prof_%i",i),1,-1,"s");

    pf->Rebin(20);
    pf->GetXaxis()->SetRangeUser(0,20);
    pf->Draw();
}


}
