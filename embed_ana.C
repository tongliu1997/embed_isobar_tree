#include "embed_species.h"
void embed_ana(
const string which_loop="random_trk",
const string pt_token="pt_mixed"

){
TH1::SetDefaultSumw2(true);
TH2::SetDefaultSumw2(true);
int stack_dim=2;
//0 for lumi, 1 for ea, 2 for vz


std::vector<string> keywords={"proton","antiproton","piplus","piminus","kplus","kminus"};
std::vector<string>::iterator it;
TCanvas* c0=new TCanvas();
c0->Print("vz_track_embed_spec_zero_order_test.pdf[");
for(it=keywords.begin();it!=keywords.end();it++){
    string key(pt_token==""? *it : Form("%s_%s",it->c_str(),pt_token.c_str()));
    string filename(Form("out-data/hadd_%s_%s.root",which_loop.c_str(),key.c_str()));
    TCanvas* ci=embed_species(filename,stack_dim,key,key,"pt");
    ci->Draw();
    ci->Print("vz_track_embed_spec_zero_order_test.pdf");
}

c0->Print("vz_track_embed_spec_zero_order_test.pdf]");


}
