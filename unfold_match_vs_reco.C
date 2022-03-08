#include "unfold_funcs.h"
void unfold_match_vs_reco(
const char* data_name="~/raghav_docker/out_root/Ru_output.root"
){
TH1::SetDefaultSumw2(true);
TH2::SetDefaultSumw2(true);


std::vector<int> centrality={80,60,40,20,10,0};
std::vector<int> embed_stack_bin;
std::vector<int> data_stack_bin;


const int nstack=centrality.size()-1;
for(int i=0;i<=nstack;i++){
    embed_stack_bin.push_back(17-centrality[i]/5);
    data_stack_bin.push_back(19-embed_stack_bin[i]);

}


const string filename="isobar_trk_eff_ptmix_blend.root";
const string key="blended";
species_plots species(filename,key,key,"pt");
const int stack_dim=1;


TH2F** resp=resp_stack(species,stack_dim,embed_stack_bin);
TH1F** match=match_stack(species,stack_dim,embed_stack_bin);
TH2F* resp_wt[nstack];

TFile* datafile=new TFile(data_name);
TH2D* htrackpT_cent=(TH2D*)datafile->Get("htrackpT_cent");
TH2D* hntrk_cent=(TH2D*)datafile->Get("hntrk_cent");
TH1D* nev_cent=hntrk_cent->ProjectionY();

TH1D* reco_rebin[nstack];
TH1D* match_rebin[nstack];

TH1D* hpt_diff[nstack];
TH1D* hpt_rebin[nstack];
double nevts_diff[nstack],evcoll[nstack];

gStyle->SetOptStat(0);
TCanvas* c1=new TCanvas("c1","",1600,900);

c1->Divide(3,2);
for(int i=0;i<nstack;i++){
    hpt_diff[i]=(TH1D*)htrackpT_cent->ProjectionX(Form("hpt_diff_%i",i),data_stack_bin[i+1],data_stack_bin[i]-1,"");
    nevts_diff[i]=0;
    evcoll[i]=0;
    for(int j=data_stack_bin[i+1];j<data_stack_bin[i];j++){
	nevts_diff[i]+=nev_cent->GetBinContent(j);
	evcoll[i]+=nev_cent->GetBinContent(j)*ncoll_bins[j-2];
    }
    
    resp_wt[i]=resp_reweight(resp[i],hpt_diff[i]);
//    resp_wt[i]=(TH2F*)resp[i]->Clone();

    reco_rebin[i]=(TH1D*)resp_wt[i]->ProjectionY()->Rebin(nbins,Form("reco_rebin_%i",i),xbins);
    reco_rebin[i]->Scale(1./evcoll[i],"width");

//    match_rebin[i]=(TH1D*)resp_wt[i]->ProjectionX()->Rebin(nbins,Form("match_rebin_%i",i),xbins);
    match_rebin[i]=(TH1D*)resp_wt[i]->ProjectionX()->Rebin(nbins,Form("match_rebin_%i",i),xbins);
    match_rebin[i]->Scale(1./evcoll[i],"width");
//    reco_rebin[i]->Divide(match_rebin[i]);
    hpt_rebin[i]=(TH1D*)hpt_diff[i]->Rebin(nbins,Form("spec_rebin_%i",i),xbins);
    hpt_rebin[i]->Scale(1./evcoll[i],"width");
    hpt_rebin[i]->SetLineColor(kRed);
    c1->cd(i+1);
//    reco_rebin[i]->Draw();
//    match_rebin[i]->Divide(hpt_rebin[i]);
    reco_rebin[i]->Divide(match_rebin[i]);
    reco_rebin[i]->Multiply(match[i]);



    reco_rebin[i]->GetXaxis()->SetRangeUser(0,15);
//    hpt_rebin[i]->Draw("same");
    reco_rebin[i]->Draw();

    match[i]->SetLineColor(kRed);
    match[i]->Draw("same");


}



}
