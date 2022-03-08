#include "unfold_funcs.h"
#include "../isobar_hist_process/isobar_hist.h"
void sample_ibu(
const char* data_name="~/raghav_docker/out_root/Ru_output.root",
const int niter=2
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
cout<<"data stack bins ";
for(int i=0;i<=nstack;i++){
    cout<<data_stack_bin[i];
    if(i==nstack)cout<<"\n";
    else cout<<"  ";

}
const string filename="isobar_trk_eff_ptmix_blend.root";
const string key="blended";
species_plots species(filename,key,key,"pt");
const int stack_dim=1;


TH2F** resp=resp_stack(species,stack_dim,embed_stack_bin);
TH1F** match=match_stack(species,stack_dim,embed_stack_bin);



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

//isobar_hist tester("/gpfs/loomis/project/caines/tl543/Isobar_Hist/ru_files_hadd/ru_files_hadd_3.root");

//TH1D** hpt_diff_reverse=tester.stack(data_stack_bin,0,pt);


for(int i=0;i<nstack;i++){
    hpt_diff[i]=(TH1D*)htrackpT_cent->ProjectionX(Form("hpt_diff_%i",i),data_stack_bin[i+1],data_stack_bin[i]-1,"");
    nevts_diff[i]=0;
    evcoll[i]=0;
    for(int j=data_stack_bin[i+1];j<data_stack_bin[i];j++){
	nevts_diff[i]+=nev_cent->GetBinContent(j);
	evcoll[i]+=nev_cent->GetBinContent(j)*ncoll_bins[j-2];
    }

    cout<<data_stack_bin[i]<<"\t"<<data_stack_bin[i+1]<<"\t"<<nevts_diff[i]<<"\t"<<evcoll[i]/nevts_diff[i]<<endl;

    unfolded_spec[0][i]=(TH1D*)hpt_diff[i]->Clone();


    for(int iter=0;iter<niter;iter++){

//  	cout<<iter<<"\t Checkpoint 2"<<endl;
    	resp_iter[iter+1][i]=resp_reweight(resp[i],unfolded_spec[iter][i]); 
    	unfolded_spec[iter+1][i]=spec_unfold(hpt_diff[i],resp_iter[iter+1][i],iter);   
//	cout<<unfolded_spec[iter+1][i]->GetNbinsX()<<"\t"<<match[i]->GetNbinsX()<<endl;
//	unfolded_spec[iter+1][i]->Divide(match[i]);
    }


}



TH1D* unfolded_rebin[niter+1][nstack];
for(int i=0;i<nstack;i++){
    for(int iter=0;iter<=niter;iter++){
	unfolded_rebin[iter][i]=(TH1D*)unfolded_spec[iter][i]->Rebin(nbins,Form("rebin_spec_%i_%i",iter,i),xbins);
	unfolded_rebin[iter][i]->Scale(1./evcoll[i],"width");
	if(iter>0)unfolded_rebin[iter][i]->Divide(match[i]);
    }
}



TH1D* unfold_ratio[niter+1][nstack];
for(int i=0;i<nstack;i++){
    for(int iter=0;iter<=niter;iter++){
	unfold_ratio[iter][i]=(TH1D*)unfolded_rebin[iter][i]->Clone();
	unfold_ratio[iter][i]->Divide(unfolded_rebin[niter][i]);
	
    }



}

TCanvas* c4=new TCanvas("c4","",1600,900);
c4->Divide(3,2);
c4->Divide(3,2);


for(int i=0;i<5;i++){
//    cout<<resp[i]->GetNbinsX()<<endl; 
    c4->cd(i+1);

//    resp[i]->GetXaxis()->SetRangeUser(0,20);
    resp[i]->Draw("colz");
}
//c4->Draw();
gStyle->SetPalette(kValentine);
TCanvas* c0=new TCanvas("c0");
c0->Divide(3,2);
for(int i=0;i<5;i++){
    c0->cd(i+1);
    for(int it=0;it<=niter;it++){
	
    	unfolded_rebin[it][i]->GetXaxis()->SetRangeUser(0,15);
    	unfolded_rebin[it][i]->Draw("same PLC PLM");
    }
//    hpt_diff[i]->SetLineColor(kRed);
//    hpt_diff[i]->Draw("same");

}
TCanvas* c1=new TCanvas("ratio");
c1->Divide(3,2);
for(int i=0;i<nstack;i++){
    c1->cd(i+1);
    for(int iter=0;iter<=niter;iter++){
	unfold_ratio[iter][i]->Draw("same PLC PLM");
    }

}


TCanvas* c2=new TCanvas("rcp");
c2->Draw();
c2->cd();
TH1D* rcp_iter[niter+1];

TLegend* lg=new TLegend();

for(int iter=0;iter<=niter;iter++){
    rcp_iter[iter]=(TH1D*)unfolded_rebin[iter][nstack-1]->Clone();
    rcp_iter[iter]->Divide(unfolded_rebin[iter][0]);
    rcp_iter[iter]->GetXaxis()->SetRangeUser(0,15);
    rcp_iter[iter]->Draw("same PLC PLM");
    lg->AddEntry(rcp_iter[iter],Form("Iteration %i",iter));

}

lg->Draw();

}
