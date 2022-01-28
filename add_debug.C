#include "embed_species.h"
void add_debug(){
TH1::SetDefaultSumw2(true);
TH2::SetDefaultSumw2(true);
int stack_dim=1;
//0 for lumi, 1 for ea, 2 for vz


TH1F* lowpt_plots=*embed_stack("out-data/hadd_random_trk_piplus.root",0,{0,1},"","piplus");
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


}
