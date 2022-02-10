#include "embed_species.h"
void embed_ana(
const string pt_token="pt_mixed",
const string obs="pt",
int stack_dim=0
){

string which_loop;
if(obs=="phi")which_loop="eff_phi";
else if(obs=="pt")which_loop="random_trk";
else{cout<<"Come again, what do you want?"<<endl;return; }
TH1::SetDefaultSumw2(true);
TH2::SetDefaultSumw2(true);
//0 for lumi, 1 for ea, 2 for vz
gStyle->SetOptStat(0);
gStyle->SetPalette(kValentine);
std::vector<int> stack_bin;
if(stack_dim==0)stack_bin={0,1};
if(stack_dim==1)stack_bin={1,5,9,13,15,17};
if(stack_dim==2) stack_bin={0,1,2,3,4};
int stack_size=stack_bin.size()-1;

//std::vector<string> keywords={"proton","antiproton","piplus","piminus","kplus","kminus"};
std::vector<string> keywords={"proton","piplus","kplus","antiproton","piminus","kminus"};
std::vector<string>::iterator it;
TCanvas* c0=new TCanvas();
c0->Divide(3,2);
int i=1;

TH1F** eff_diff[6];
//c0->Print("vz_phi_embed_spec_zero_order_test.pdf[");
for(it=keywords.begin();it!=keywords.end();it++){
    string key(pt_token==""? *it : Form("%s_%s",it->c_str(),pt_token.c_str()));
    string filename(Form("out-data/hadd_%s_%s.root",which_loop.c_str(),key.c_str()));

    const string inkey(pt_token==""? "" : key);
    c0->cd(i);
    eff_diff[i-1]=embed_stack(filename,stack_dim,stack_bin,inkey,key,obs);
    TLegend* lg;
    if(i==1)lg=new TLegend(0.2,0.2,0.5,0.5);
    for(int j=0;j<stack_size;j++){
	if(obs=="pt") eff_diff[i-1][j]->GetXaxis()->SetRangeUser(0,20);
	eff_diff[i-1][j]->Draw("same PLC PLM");
 	if(i==1)lg->AddEntry(eff_diff[i-1][j]->GetTitle());
    }
    if(i==1)lg->Draw();

//    TPad* ci=embed_species(filename,stack_dim,key,key,obs);
    i++;
//    ci->Draw();
//    ci->Print("vz_phi_embed_spec_zero_order_test.pdf");
}

//c0->Print("vz_phi_embed_spec_zero_order_test.pdf]");


}
