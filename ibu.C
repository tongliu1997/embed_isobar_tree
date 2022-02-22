#include "embed_species.h"
double ncoll_bins[16]={385,317,232,232,150,150,94,94,56,56,32,32,17,17,9,9};



TH2D* truth_augment(TH1D* spec){
    int nbins=spec->GetNbinsX();
    double xmin=spec->GetXaxis()->GetBinLowEdge(1);
    double xmax=spec->GetXaxis()->GetBinLowEdge(nbins)+spec->GetXaxis()->GetBinWidth(nbins);
    TH2D* augmented=new TH2D(Form("%s_augmented",spec->GetName()),"",nbins,xmin,xmax,nbins,xmin,xmax);
    for(int i=1;i<=nbins;i++){
	double value=spec->GetBinContent(i);
	double error=spec->GetBinError(i);
	for(int j=1;j<=nbins;j++){
	    augmented->SetBinContent(i,j,value);
	    augmented->SetBinError(i,j,error);
	}
    }    
    return augmented;

}


TH2F* resp_reweight(TH2F* resp_mtx,TH1D* spec){
    TH2F* resp_return=(TH2F*)resp_mtx->Clone();
    TH2D* aug_spec=truth_augment(spec);
    resp_return->Multiply(aug_spec);
    delete aug_spec;
    return resp_return;

}



TH1D* spec_unfold(TH1D* raw_spec,TH2F* resp_mtx){
    int nbins=raw_spec->GetNbinsX();
    double xmin=raw_spec->GetXaxis()->GetBinLowEdge(1);
    double xmax=raw_spec->GetXaxis()->GetBinLowEdge(nbins)+raw_spec->GetXaxis()->GetBinWidth(nbins);
    TH1D* unfolded=new TH1D(Form("%s_unfolded",raw_spec->GetName()),"Unfolded spec;p_{T};yield",nbins,xmin,xmax);
//    TH1F* reco_weight_ref=(TH1F*)resp_mtx->ProjectionY();    
    for(int i=1;i<=nbins;i++){
	if(raw_spec->GetBinCenter(i)<0.2)continue;
	TH1D* slice=(TH1D*)resp_mtx->ProjectionX(Form("mtx_%i",i),i,i,"");
	double integral=slice->Integral();
	if(integral==0)continue;
	double weight=1.*raw_spec->GetBinContent(i)/slice->Integral();
	cout<<raw_spec->GetBinCenter(i)<<"\t"<<integral<<"\t"<<raw_spec->GetBinContent(i)<<"\t"<<weight<<endl;
	unfolded->Add(slice,weight);
    }
    return unfolded;
}



void ibu(
const char* data_name="~/raghav_docker/out_root/Ru_output.root",
const int niter=2
){
TH1::SetDefaultSumw2(true);
TH2::SetDefaultSumw2(true);

std::vector<int> centrality={70,60,40,20,10,0};
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

TFile* datafile=new TFile(data_name);
TH2D* htrackpT_cent=(TH2D*)datafile->Get("htrackpT_cent");
TH2D* hntrk_cent=(TH2D*)datafile->Get("hntrk_cent");
TH1D* hpt_diff[nstack];
TH1D* hpt_diff_rebin[nstack];
TH1D* hpt_diff_unfold[nstack];
TH1D* hpt_diff_unfold_rebin[nstack];
TH1D* nev_cent=hntrk_cent->ProjectionY();

TH1D* unfolded_spec[niter+1][nstack];
TH2F* resp_iter[niter+1][nstack];
cout<<"Checkpoint 1"<<endl;
double nevts_diff[nstack],evcoll[nstack];

for(int i=0;i<nstack;i++){
    hpt_diff[i]=(TH1D*)htrackpT_cent->ProjectionX(Form("hpt_diff_%i",i),data_stack_bin[i+1],data_stack_bin[i]-1,"");
    nevts_diff[i]=0;
    evcoll[i]=0;
    for(int j=data_stack_bin[i+1];j<data_stack_bin[i];j++){
	nevts_diff[i]+=nev_cent->GetBinContent(j);
	evcoll[i]+=nev_cent->GetBinContent(j)*ncoll_bins[j-2];
    }
    unfolded_spec[0][i]=(TH1D*)hpt_diff[i]->Clone();


    for(int iter=0;iter<niter;iter++){

  	cout<<iter<<"\t Checkpoint 2"<<endl;
    	resp_iter[iter+1][i]=resp_reweight(resp[i],unfolded_spec[iter][i]); 
    	unfolded_spec[iter+1][i]=spec_unfold(hpt_diff[i],resp_iter[iter+1][i]);   
    }


}

















TCanvas* c4=new TCanvas("c4","",1600,900);

c4->Divide(3,2);


for(int i=0;i<5;i++){
//    cout<<resp[i]->GetNbinsX()<<endl; 
    c4->cd(i+1);

//    resp[i]->GetXaxis()->SetRangeUser(0,20);
    resp[i]->Draw("colz");
}
//c4->Draw();

TCanvas* c0=new TCanvas("c0");
c0->Divide(3,2);
for(int i=0;i<5;i++){
    c0->cd(i+1);
    unfolded_spec[niter][i]->GetXaxis()->SetRangeUser(0,15);
    unfolded_spec[niter][i]->Draw();
    hpt_diff[i]->SetLineColor(kRed);
    hpt_diff[i]->Draw("same");

}
//*/

}
