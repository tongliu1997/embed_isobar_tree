#include "embed_species.h"
void add_debug(){
TH1::SetDefaultSumw2(true);
TH2::SetDefaultSumw2(true);
//0 for lumi, 1 for ea, 2 for vz


/*TH1F* lowpt_plots=*embed_stack("out-data/hadd_random_trk_piplus.root",0,{0,1},"","piplus");
TCanvas* c1=new TCanvas();
c1->cd();
lowpt_plots->Draw();

TH1F* highpt_plots=*embed_stack("out-data/hadd_random_trk_piplus_highpt.root",0,{0,1},"","piplus_highpt");
TCanvas* c3=new TCanvas();
c3->cd();
highpt_plots->SetLineColor(kRed);
highpt_plots->Draw();

TCanvas* c2=embed_species("piplus_pt_mixed",stack_dim,"blended","blended");
c2->Draw();
*/


//TH1F* blended_plots=*embed_stack("out-data/hadd_random_trk_piplus_highpt.root",0,{0,1},"","piplus_highpt");
//TH1F** blended_plots=embed_stack("isobar_trk_eff_ptmix_blend.root",1,{0,1,2,3,4},"blended","blended");
//TCanvas* c4=embed_species("out-data/hadd_eff_phi_piplus_pt_mixed.root",1,"piplus_pt_mixed","piplus_pt_mixed","phi");
//std::vector<int> bin={0,1,2,3,4};
//TH1F** plots=embed_stack("out-data/hadd_eff_phi_piplus.root",2,bin,"","","phi");

const string filename="isobar_trk_eff_ptmix_blend.root";
const string key="blended";
species_plots species(filename,key,key,"pt");
const int stack_dim=1;
vector<int> stack_bin={1,5,9,13,15,17};


TH2F** devs=dev_stack(species,stack_dim,stack_bin);
TCanvas* c4=new TCanvas("c4");
c4->Divide(3,2);
for(int i=0;i<5;i++){
    c4->cd(i+1);
    c4->SetLogz();
    devs[i]->GetXaxis()->SetRangeUser(0,20);
    devs[i]->Draw("colz");
}
//c4->Draw();

}
