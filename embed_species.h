#include <vector>
#include <string>
#include "species_plots.h"
int find_ibin(int j,std::vector<int> bins){
int ibin=-1;
//cout<<j<<"\t"<<bins[0]<<endl;

while(j>bins[ibin+1]){
    ibin++;
    if(ibin >= bins.size())return -2;
}
return ibin;

}

TH1F** embed_stack(
const char* filename="out-data/hadd_random_trk_proton.root",
int stack_dim=2,
std::vector<int> stack_bin={0,1,2,3,4},
string inkey_str="",
string namekey_str="proton"
){
cout<<"Inkey is "<<inkey_str<<endl;
species_plots species(filename,inkey_str,namekey_str);

int stack_size=stack_bin.size()-1;
TH1F* gen_diff[stack_size];
TH1F* reco_diff[stack_size];
TH1F** eff_diff=(TH1F**)malloc(sizeof(TH1F*)*stack_size);



for(int ibin=0;ibin<stack_size;ibin++){

    int start_dim[3]={stack_bin[ibin],0,0};    
    int si=start_dim[stack_dim];
    int sj=start_dim[(stack_dim+1)%3];
    int sk=start_dim[(stack_dim+2)%3];



    gen_diff[ibin]=(TH1F*)species.gen_mc_pt[si][sj][sk]->Clone();
    gen_diff[ibin]->SetName(Form("gen_diff_%i",ibin));
    reco_diff[ibin]=(TH1F*)species.reco_pt[si][sj][sk]->Clone();
    reco_diff[ibin]->SetName(Form("reco_diff_%i",ibin));


    int bin_size[3]={species.lumi_bins,species.ea_bins,species.vz_bins};
    int ibins=bin_size[stack_dim],jbins=bin_size[(stack_dim+1)%3],kbins=bin_size[(stack_dim+2)%3];
    

    for(int j=0;j<jbins;j++){
	for(int k=0;k<kbins;k++){
	    for(int i=stack_bin[ibin];i<stack_bin[ibin+1];i++){
		if(!(i==stack_bin[ibin] && j==0 && k==0)) {
		    int rot_pos[3]={i,j,k};
		    int ai=rot_pos[(3-stack_dim)%3];
		    int aj=rot_pos[(4-stack_dim)%3];
		    int ak=rot_pos[(5-stack_dim)%3];
		    gen_diff[ibin]->Add(species.gen_mc_pt[ai][aj][ak]);
		    reco_diff[ibin]->Add(species.reco_pt[ai][aj][ak]);
		}
	    }
	}

    }
    eff_diff[ibin]=(TH1F*)gen_diff[ibin]->Clone();
    eff_diff[ibin]=(TH1F*)reco_diff[ibin]->Clone();
    eff_diff[ibin]->Divide(gen_diff[ibin]);
    char* hist_name;
    const char* namekey=namekey_str.c_str(); 
    if(stack_dim==0) hist_name=Form("%s Lumi diff: only one fxxking bin!",namekey);
    if(stack_dim==1) hist_name=Form("%s EA %i%% to %i%%",namekey,(17-stack_bin[ibin+1])*5,(17-stack_bin[ibin])*5 );
    if(stack_dim==2) hist_name=Form("%s vz %i to %i",namekey,stack_bin[ibin]*15-35,stack_bin[ibin+1]*15-35 );

    eff_diff[ibin]->SetTitle(hist_name);
    eff_diff[ibin]->SetName(hist_name);
    eff_diff[ibin]->GetXaxis()->SetRangeUser(0,20);
    eff_diff[ibin]->SetLineWidth(2);
    

}
return eff_diff;

}

TCanvas* embed_species(
//const char* inputname="noembed_random_trk_proton.root"
string keyword_str="proton",
int stack_dim=2,
string inkey="",
string namekey="proton"
){

std::vector<int> stack_bin;
if(stack_dim==0)stack_bin={0,1};
if(stack_dim==1)stack_bin={1,5,9,13,15,17};
if(stack_dim==2) stack_bin={0,1,2,3,4};
int stack_size=stack_bin.size()-1;

const char* keyword=keyword_str.c_str();
//const char* filename=Form("out-data/hadd_random_trk_%s.root",keyword);
const char* filename="isobar_trk_eff_ptmix_blend.root";


TH1F** eff_diff=embed_stack(filename,stack_dim,stack_bin,inkey,namekey);

gStyle->SetOptStat(0);
TCanvas* c1=new TCanvas("","",900,600);
if(stack_dim==1)c1->Divide(3,2);
if(stack_dim==2)c1->Divide(2,2);
for(int i=0;i<stack_size;i++){
    c1->cd(i+1);
    eff_diff[i]->Draw();
}
return c1;


//c1->SaveAs(Form("%s_lowpt_eff_zero_order.pdf",keyword));
/*TFile* output=new TFile(Form("efficiency_plots/trk_efficiencies_%s.root",keyword),"recreate");
output->cd();
for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
	for(int k=0;k<4;k++){
	    pt_efficiency[i][j][k]->Write();
	}
    }
}

output->Close();
*/
}
