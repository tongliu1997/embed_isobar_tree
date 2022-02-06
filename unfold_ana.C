#include "embed_species.h"

double ncoll_bins[16]={385,317,232,232,150,150,94,94,56,56,32,32,17,17,9,9};


void unfold_ana(){
TH1::SetDefaultSumw2(true);
TH2::SetDefaultSumw2(true);

const char* embed_name="isobar_trk_eff_ptmix_blend.root";
const char* keyword="blended";
int stack_dim=1;
//0 for lumi, 1 for ea, 2 for vz

std::vector<int> centrality={70,60,40,20,10,0};

std::vector<int> embed_stack_bin;
//={1,5,9,13,15,17};


std::vector<int> data_stack_bin;
const int nstack=centrality.size();
for(int i=0;i<nstack;i++){
    embed_stack_bin.push_back(17-centrality[i]/5);
    data_stack_bin.push_back(19-embed_stack_bin[i]);

}
//18 14 10 6 4 2


TH1F** eff_stacked=embed_stack(embed_name,stack_dim,embed_stack_bin,keyword,keyword);

const char* data_name="../raghav_docker/out_root/Ru_output.root";
TFile* datafile=new TFile(data_name);
TH2D* htrackpT_cent=(TH2D*)datafile->Get("htrackpT_cent");
TH2D* hntrk_cent=(TH2D*)datafile->Get("hntrk_cent");

const int nbins=29;
Double_t xbins[nbins+1]={0,0.2,0.4,0.6,0.8,1,1.2,1.4,1.6,1.8,2.,2.2,2.4,2.6,2.8,3,3.4,3.8,4.4,5,6,7,8,9,10,12,15,18,25,30};
TH1D* hpt_diff[nstack-1];
TH1D* hpt_diff_rebin[nstack-1];
TH1D* hpt_diff_unfold[nstack-1];
TH1D* hpt_diff_unfold_rebin[nstack-1];
TH1D* nev_cent=hntrk_cent->ProjectionY();
double nevts_diff[nstack-1],evcoll[nstack-1];
for(int i=0;i<nstack-1;i++){
//    htrackpT_cent->GetXaxis()->SetRangeUser(0,18);
    hpt_diff[i]=(TH1D*)htrackpT_cent->ProjectionX(Form("hpt_diff_%i",i),data_stack_bin[i+1],data_stack_bin[i]-1,"");
    nevts_diff[nstack-1]=0;
    evcoll[nstack-1]=0;
    for(int j=data_stack_bin[i+1];j<data_stack_bin[i];j++){
	nevts_diff[i]+=nev_cent->GetBinContent(j);
	evcoll[i]+=nev_cent->GetBinContent(j)*ncoll_bins[j-2];	
    }
    hpt_diff[i]->Rebin(4);
    hpt_diff_rebin[i]=(TH1D*)hpt_diff[i]->Rebin(nbins,Form("hpt_diff_rebin_%i",i),xbins);
//    hpt_diff_rebin[i]=(TH1D*)hpt_diff[i]->Clone();
//    hpt_diff[i]->GetXaxis()->SetRange(1,25);
    hpt_diff_rebin[i]->Scale(1.0/evcoll[i],"width");

//    hpt_diff[i]->Divide(eff_stacked[i]);

    hpt_diff_unfold[i]=(TH1D*)hpt_diff[i]->Clone();
    hpt_diff_unfold[i]->SetName(Form("hpt_diff_unfold_%i",i));
//    hpt_diff_unfold[i]->GetXaxis()->SetRangeUser(0,5);
    hpt_diff_unfold[i]->Divide(eff_stacked[i]);
    cout<<hpt_diff_unfold[i]->GetNbinsX()<<"\t"<<eff_stacked[i]->GetNbinsX()<<endl;
    hpt_diff_unfold_rebin[i]=(TH1D*)hpt_diff_unfold[i]->Rebin(nbins,Form("hpt_diff_unfold_rebin_%i",i),xbins);
//    hpt_diff_unfold_rebin[i]=(TH1D*)hpt_diff_unfold[i]->Clone();
    hpt_diff_unfold_rebin[i]->Scale(1.0/evcoll[i],"width");
}

TCanvas* c1=new TCanvas();
c1->Draw();
c1->cd();
c1->SetLogy();
gStyle->SetPalette(kCMYK);
for(int i=0;i<nstack-1;i++){
    hpt_diff_unfold_rebin[i]->Draw("same PLC PLM");
//     eff_stacked[i]->Draw("same PLC PLM");
}

TLegend *lg=new TLegend();
for(int i=0;i<nstack-1;i++){
    lg->AddEntry(hpt_diff_unfold_rebin[i],Form("%i%%_%i%%",centrality[i+1],centrality[i]));

}
lg->Draw();
cout<<evcoll[nstack-2]/nevts_diff[nstack-2]<<"\t"<<evcoll[0]/nevts_diff[0]<<endl;


TCanvas* c2=new TCanvas();
c2->Draw();
c2->cd();
TH1D* hpt_ratio=(TH1D*)hpt_diff_rebin[nstack-2]->Clone();
hpt_ratio->SetName("ratio");
hpt_ratio->SetYTitle("R_{CP}");
hpt_ratio->Divide(hpt_diff_rebin[0]);
hpt_ratio->Draw();

TH1D* hpt_unfold_ratio=(TH1D*)hpt_diff_unfold_rebin[nstack-2]->Clone();
hpt_unfold_ratio->SetName("unfolded ratio");
hpt_unfold_ratio->Divide(hpt_diff_unfold_rebin[0]);
hpt_unfold_ratio->SetLineColor(kRed);
hpt_unfold_ratio->Draw("same");
TLegend *lg1=new TLegend();
lg1->AddEntry(hpt_ratio,"Raw");
lg1->AddEntry(hpt_unfold_ratio,"Unfolded");
lg1->Draw();

}
