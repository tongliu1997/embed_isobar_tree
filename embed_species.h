#pragma once

#include <vector>
#include <string>
#include "species_plots.h"


const int nbins=47;
const Double_t xbins[nbins+1]={0,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.,2.1,2.2,2.3,2.4,2.6,2.8,3,3.35,3.8,4.4,5.1,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,25,30};

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
const species_plots &species,
int stack_dim=2,
std::vector<int> stack_bin={0,1,2,3,4}
){

string obs(species.m_obs==pt?"pt":"phi");

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

    if(obs=="pt"){
	eff_diff[ibin]=(TH1F*)reco_diff[ibin]->Rebin(nbins,Form("rebin_%i",ibin),xbins);
	eff_diff[ibin]->Divide((TH1F*)gen_diff[ibin]->Rebin(nbins,Form("gen_rebin_%i",ibin),xbins));
    }
    else{
	eff_diff[ibin]=(TH1F*)reco_diff[ibin]->Clone();
    	eff_diff[ibin]->Divide(gen_diff[ibin]);
    }
    char* hist_name;
    const char* namekey=species.namestr.c_str(); 
    if(stack_dim==0) hist_name=Form("%s track MC eta %.1f to %.1f",namekey, -1.+0.5*stack_bin[ibin],-1.+0.5*stack_bin[ibin+1]);
    if(stack_dim==1) hist_name=Form("%s EA %i%% to %i%%",namekey,(17-stack_bin[ibin+1])*5,(17-stack_bin[ibin])*5 );
    if(stack_dim==2) hist_name=Form("%s vz %i to %i",namekey,stack_bin[ibin]*15-35,stack_bin[ibin+1]*15-35 );

    eff_diff[ibin]->SetTitle(hist_name);
    eff_diff[ibin]->SetName(hist_name);
//    eff_diff[ibin]->GetXaxis()->SetRangeUser(0,20);
    eff_diff[ibin]->SetLineWidth(2);
    eff_diff[ibin]->SetXTitle(obs.c_str());
    eff_diff[ibin]->SetYTitle("Efficiency");
    
//    eff_diff[ibin]->Draw("same");
}

return eff_diff;

}


TH1F** embed_stack(
const string filename="out-data/hadd_random_trk_proton.root",
int stack_dim=2,
std::vector<int> stack_bin={0,1,2,3,4},
string inkey_str="",
string namekey_str="proton",
string obs="pt"
){
cout<<"Inkey is "<<inkey_str<<endl;
cout<<filename<<"\t"<<inkey_str<<"\t"<<namekey_str<<endl;

species_plots species(filename,inkey_str,namekey_str,obs);

return embed_stack(species,stack_dim,stack_bin);

}




TH1F** match_stack(
const species_plots &species,
int stack_dim=2,
std::vector<int> stack_bin={0,1,2,3,4}
){

string obs(species.m_obs==pt?"pt":"phi");
int stack_size=stack_bin.size()-1;
TH1F* gen_diff[stack_size];
TH1F* match_diff[stack_size];
TH1F** eff_diff=(TH1F**)malloc(sizeof(TH1F*)*stack_size);

for(int ibin=0;ibin<stack_size;ibin++){

    int start_dim[3]={stack_bin[ibin],0,0};    
    int si=start_dim[stack_dim];
    int sj=start_dim[(stack_dim+1)%3];
    int sk=start_dim[(stack_dim+2)%3];

    gen_diff[ibin]=(TH1F*)species.gen_mc_pt[si][sj][sk]->Clone();
    gen_diff[ibin]->SetName(Form("gen_diff_%i",ibin));
    match_diff[ibin]=(TH1F*)species.reco_pt[si][sj][sk]->Clone();
    match_diff[ibin]->SetName(Form("match_diff_%i",ibin));

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
		    match_diff[ibin]->Add(species.match_mc_pt[ai][aj][ak]);
		}
	    }
	}
    }

    if(species.m_obs==pt){
	eff_diff[ibin]=(TH1F*)match_diff[ibin]->Rebin(nbins,Form("rebin_%i",ibin),xbins);
	eff_diff[ibin]->Divide((TH1F*)gen_diff[ibin]->Rebin(nbins,Form("gen_rebin_%i",ibin),xbins));
    }
    else{
	eff_diff[ibin]=(TH1F*)match_diff[ibin]->Clone();
    	eff_diff[ibin]->Divide(gen_diff[ibin]);
    }
    char* hist_name;
    const char* namekey=species.namestr.c_str(); 
    if(stack_dim==0) hist_name=Form("%s track MC eta %.1f to %.1f",namekey, -1.+0.5*stack_bin[ibin],-1.+0.5*stack_bin[ibin+1]);
    if(stack_dim==1) hist_name=Form("%s EA %i%% to %i%%",namekey,(17-stack_bin[ibin+1])*5,(17-stack_bin[ibin])*5 );
    if(stack_dim==2) hist_name=Form("%s vz %i to %i",namekey,stack_bin[ibin]*15-35,stack_bin[ibin+1]*15-35 );

    eff_diff[ibin]->SetTitle(hist_name);
    eff_diff[ibin]->SetName(hist_name);
//    eff_diff[ibin]->GetXaxis()->SetRangeUser(0,20);
    eff_diff[ibin]->SetLineWidth(2);
    eff_diff[ibin]->SetXTitle(obs.c_str());
    eff_diff[ibin]->SetYTitle("Efficiency");
    
//    eff_diff[ibin]->Draw("same");
}

return eff_diff;

}




TH1F** match_stack(
const string filename="out-data/hadd_random_trk_proton.root",
int stack_dim=2,
std::vector<int> stack_bin={0,1,2,3,4},
string inkey_str="",
string namekey_str="proton",
string obs="pt"
){
cout<<"Inkey is "<<inkey_str<<endl;
cout<<filename<<"\t"<<inkey_str<<"\t"<<namekey_str<<endl;

species_plots species(filename,inkey_str,namekey_str,obs);

return match_stack(species,stack_dim,stack_bin);

}


TCanvas* embed_species(
const string filename="noembed_random_trk_proton.root",
//string keyword_str="proton",
int stack_dim=2,
string inkey="",
string namekey="proton",
string obs="pt"
){



std::vector<int> stack_bin;
if(stack_dim==0)stack_bin={0,1};
if(stack_dim==1)stack_bin={1,5,9,13,15,17};
if(stack_dim==2) stack_bin={0,1,2,3,4};
int stack_size=stack_bin.size()-1;

//const char* keyword=keyword_str.c_str();
//const char* filename=Form("out-data/hadd_random_trk_%s.root",keyword);
//const char* filename="eff_phi_piplus.root";


TH1F** eff_diff=embed_stack(filename,stack_dim,stack_bin,inkey,namekey,obs);

gStyle->SetOptStat(0);
TCanvas* c1=new TCanvas("c1",filename.c_str(),900,600);
//TPad* c1=new TPad();


gStyle->SetPalette(kValentine);

TLegend* lg=new TLegend(0.2,0.2,0.5,0.5);
c1->cd();
//if(stack_dim==1)c1->Divide(3,2);
//if(stack_dim==2)c1->Divide(2,2);
for(int i=0;i<stack_size;i++){
//    c1->cd(i+1);
    eff_diff[i]->Draw("same PLC PLM");
//    eff_diff[i]->Draw("same");
    lg->AddEntry(eff_diff[i]->GetTitle());

}

lg->Draw();



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
