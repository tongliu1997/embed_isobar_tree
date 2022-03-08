#include "embed_species.h"
void match_vs_reco(){
TH1::SetDefaultSumw2(true);
TH2::SetDefaultSumw2(true);

const string filename="isobar_trk_eff_ptmix_blend.root";

const string key="blended";
species_plots species(filename,key,key,"pt");
species.mc_cutoff(15);
cout<<"Cutoff done."<<endl;
int stack_dim=1;
//0 for lumi, 1 for ea, 2 for vz
vector<int> stack_bin={1,5,9,13,15,17};

TH1F** match=match_stack(species,stack_dim,stack_bin);
TH1F** reco=embed_stack(species,stack_dim,stack_bin);

TCanvas* c4=new TCanvas("c4");
c4->Divide(3,2);

for(int i=0;i<5;i++){
  c4->cd(i+1);
  reco[i]->GetXaxis()->SetRangeUser(0,20);
  reco[i]->Draw();
  match[i]->SetLineColor(kRed);
  match[i]->Draw("same");
}

}
