#include "unfold_funcs.h"
#include "../isobar_hist_process/isobar_hist.h"
void ibu_fulldata(
const char* data_name="/gpfs/loomis/project/caines/tl543/Isobar_Hist/zr_hadd.root",
//const char* data_name="/gpfs/loomis/project/caines/tl543/Isobar_Hist/ru_files_hadd/ru_hadd_1.root",
int iszr=1,
const int niter=2
){
TH1::SetDefaultSumw2(true);
TH2::SetDefaultSumw2(true);

std::vector<int> centrality={80,60,40,20,10,0};
std::vector<int> embed_stack_bin;//Centrality bins used for embbedding data extraction
std::vector<int> data_stack_bin;//Centrality bins used for real data extraction


const int nstack=centrality.size()-1;
for(int i=0;i<=nstack;i++){
    embed_stack_bin.push_back(17-centrality[i]/5);
    data_stack_bin.push_back(centrality[nstack-i]/5);

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

TH2F** resp=resp_stack(species,stack_dim,embed_stack_bin);//0th order response matrix
TH1F** match=match_stack(species,stack_dim,embed_stack_bin);//Matching efficiency curve
TH1F** match_norebin=match_stack(species,stack_dim,embed_stack_bin,false);//Matching efficiency curve

TH1D* hpt_diff[nstack];
TH1D* unfolded_spec[niter+1][nstack];
TH2F* resp_iter[niter+1][nstack];
TH1F* trk_eff[niter+1][nstack];

double nevts_diff[nstack],evcoll[nstack];

isobar_hist tester(data_name);
TH1D** hpt_diff_reverse=tester.stack(data_stack_bin,0,pt);

for(int i=0;i<nstack;i++){
    hpt_diff[i]=hpt_diff_reverse[nstack-1-i];
    nevts_diff[i]=0;
    evcoll[i]=0;
    for(int j=data_stack_bin[nstack-1-i];j<data_stack_bin[nstack-i];j++){
	nevts_diff[i]+=tester.nev_bins(j);
	evcoll[i]+=tester.nev_bins(j)*ncoll_bins[iszr][j];
    }

    cout<<data_stack_bin[nstack-1-i]<<"\t"<<data_stack_bin[nstack-i]<<"\t"<<nevts_diff[i]<<"\t"<<evcoll[i]/nevts_diff[i]<<endl;
    unfolded_spec[0][i]=(TH1D*)hpt_diff[i]->Clone();
//    resp_iter[0][i]=(TH2F*)resp[i]->Clone();
    resp_iter[0][i]=outlier_trim(resp[i]);
    trk_eff[0][i]=tracking_efficiency(resp_iter[0][i],match_norebin[i]); 
    for(int iter=0;iter<niter;iter++){
    	resp_iter[iter+1][i]=resp_reweight(resp[i],unfolded_spec[iter][i],iter); 
 	trk_eff[iter+1][i]=tracking_efficiency(resp_iter[iter+1][i],match_norebin[i]);
	
//    	unfolded_spec[iter+1][i]=spec_unfold(hpt_diff[i],resp_iter[iter+1][i],iter);   
    	unfolded_spec[iter+1][i]=spec_correct(hpt_diff[i],resp_iter[iter+1][i],iter);   
//	cout<<unfolded_spec[iter+1][i]->GetNbinsX()<<"\t"<<match[i]->GetNbinsX()<<endl;
//	unfolded_spec[iter+1][i]->Divide(match[i]);
    }
}

TH1D* unfolded_rebin[niter+1][nstack];
for(int i=0;i<nstack;i++){
    for(int iter=0;iter<=niter;iter++){

	if(iter>0)unfolded_spec[iter][i]->Divide(match_norebin[i]);
	unfolded_rebin[iter][i]=(TH1D*)unfolded_spec[iter][i]->Rebin(nbins,Form("rebin_spec_%i_%i",iter,i),xbins);
//	unfolded_rebin[iter][i]=(TH1D*)unfolded_spec[iter][i]->Clone();
//	unfolded_rebin[iter][i]->SetName(Form("spec_unfold_rebin_%i_%i"));
	unfolded_rebin[iter][i]->Scale(1./evcoll[i],"width");
//	if(iter>0)
//	    unfolded_rebin[iter][i]->Divide(match[i]);
    }
}

TH1D* unfold_ratio[niter+1][nstack];
for(int i=0;i<nstack;i++){
    for(int iter=0;iter<=niter;iter++){
	unfold_ratio[iter][i]=(TH1D*)unfolded_rebin[iter][i]->Clone();
	unfold_ratio[iter][i]->Divide(unfolded_rebin[niter][i]);
    }
}
/*
TCanvas* c4=new TCanvas("c4","",1600,900);
c4->Divide(3,2);

for(int i=0;i<5;i++){
//    cout<<resp[i]->GetNbinsX()<<endl; 
    c4->cd(i+1);

//    resp[i]->GetXaxis()->SetRangeUser(0,20);
    resp[i]->Draw("colz");
}
*/
//c4->Draw();
gStyle->SetPalette(kValentine);
TCanvas* c0=new TCanvas("c0","",1600,900);
c0->Divide(3,2);
for(int i=0;i<5;i++){
    c0->cd(i+1);
    for(int it=0;it<=niter;it++){
    	unfolded_rebin[it][i]->GetXaxis()->SetRangeUser(0,15);
    	unfolded_rebin[it][i]->Draw("same PLC PLM");
    }
}
TCanvas* c1=new TCanvas("ratio");
c1->Divide(3,2);
//int i=nstack-1;
gStyle->SetOptStat(0);
for(int i=0;i<nstack;i++){
    c1->cd(i+1);
    match[i]->GetXaxis()->SetRangeUser(0,20);
//    match[i]->GetYaxis()->SetRangeUser(0,20);
//    match[i]->Draw("PLC PLM"); 
    for(int iter=2;iter<=niter;iter++){
//	unfold_ratio[iter][i]->Draw("same PLC PLM");
	
	trk_eff[iter][i]->Draw("same PLC PLM");

//  	resp_iter[0][i]->Draw("colz");
    }
}


TCanvas* c2=new TCanvas("rcp");
c2->Draw();
c2->cd();
TH1D* rcp_iter[niter+1];

TLegend* lg=new TLegend();

TH1D* rcp_offset=(TH1D*)unfolded_rebin[0][0]->Clone();
for(int i=1;i<=rcp_offset->GetNbinsX();i++){
    rcp_offset->SetBinContent(i,-0.1);
    rcp_offset->SetBinError(i,0);
    
}





for(int iter=0;iter<=niter;iter++){
    rcp_iter[iter]=(TH1D*)unfolded_rebin[iter][nstack-1]->Clone();
    rcp_iter[iter]->Divide(unfolded_rebin[iter][0]);
//    if(iter)rcp_iter[iter]->Add(rcp_offset,1.*iter);
    rcp_iter[iter]->GetXaxis()->SetRangeUser(0,20);

    rcp_iter[iter]->SetLineWidth(2);
    rcp_iter[iter]->Draw("same PLC PLM");
//    lg->AddEntry(rcp_iter[iter],iter?Form("Iteration %i -%.1f",iter,0.1*iter):"Iteration 0");
    lg->AddEntry(rcp_iter[iter],iter?Form("Iteration %i",iter):"Raw");

}

lg->Draw();

string outname=(iszr)?"outhist_zr.root":"outhist_ru.root";
TFile* output=new TFile(outname.c_str(),"recreate");
string system=(iszr)?"zr":"ru";
for(int i=0;i<nstack;i++){
    unfolded_rebin[niter][i]->SetName(Form("%s_unfolded_spec_%i_%i",system.c_str(),centrality[i+1],centrality[i]));
    unfolded_rebin[niter][i]->SetTitle(Form("%s_unfolded_spec_%i_%i",system.c_str(),centrality[i+1],centrality[i]));
    unfolded_rebin[0][i]->SetName(Form("%s_raw_spec_%i_%i",system.c_str(),centrality[i+1],centrality[i]));
    unfolded_rebin[0][i]->SetTitle(Form("%s_raw_spec_%i_%i",system.c_str(),centrality[i+1],centrality[i]));
    unfolded_rebin[niter][i]->Write();
    unfolded_rebin[0][i]->Write();
}
output->Close();
}
