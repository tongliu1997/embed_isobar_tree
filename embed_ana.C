#include "embed_species.h"
void embed_ana(){
TH1::SetDefaultSumw2(true);
TH2::SetDefaultSumw2(true);
int stack_dim=2;
//0 for lumi, 1 for ea, 2 for vz


std::vector<string> keywords={"proton","antiproton","piplus","piminus","kplus","kminus"};
std::vector<string>::iterator it;
TCanvas* c0=new TCanvas();
c0->Print("vz_track_embed_spec_zero_order_mixed.pdf[");
for(it=keywords.begin();it!=keywords.end();it++){
    string key(Form("%s_pt_mixed",it->c_str()));
    TCanvas* ci=embed_species(key,stack_dim,key,key);
    ci->Print("vz_track_embed_spec_zero_order_mixed.pdf");
}

c0->Print("vz_track_embed_spec_zero_order_mixed.pdf]");


}
