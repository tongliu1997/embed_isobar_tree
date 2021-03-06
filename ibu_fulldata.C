#include "unfold_funcs.h"
#include "../isobar_hist_process/isobar_hist.h"
void ibu_fulldata(
const string system,
float eta_start=-1,
float eta_end=1,
const int niter=2,
const string embed_key="",
std::vector<int> cent_in={0,10,20,40,60,80}
){
int iszr=0;
if(system=="zr")iszr=1;
const char* data_name=(iszr)?"/gpfs/loomis/project/caines/tl543/Isobar_Hist/zr_hadd.root":
"/gpfs/loomis/project/caines/tl543/Isobar_Hist/ru_hadd.root";
//"/home/tl543/embed_isobar_tree/testout_noweight.root";


int etabin_start=2*eta_start+3;
int etabin_end=2*eta_end+2;
TH1::SetDefaultSumw2(true);
TH2::SetDefaultSumw2(true);

//std::vector<int> centrality={70,60,40,20,10,0};
std::vector<int> centrality;
std::vector<int> embed_stack_bin;//Centrality bins used for embbedding data extraction
std::vector<int> data_stack_bin;//Centrality bins used for real data extraction


const int nstack=cent_in.size()-1;
TH1D* ncoll_bin;
TH1D* npart_bin;

ncoll_bin=new TH1D("ncoll","",nstack,-0.5,nstack-0.5);
npart_bin=new TH1D("npart","",nstack,-0.5,nstack-0.5);

for(int i=0;i<=nstack;i++){
    centrality.push_back(cent_in[nstack-i]);
    embed_stack_bin.push_back(17-cent_in[nstack-i]/5);
    data_stack_bin.push_back(cent_in[i]/5);

}
/*cout<<"data stack bins ";
for(int i=0;i<=nstack;i++){
    cout<<data_stack_bin[i];
    if(i==nstack)cout<<"\n";
    else cout<<"  ";
}
*/
const string filename=Form("isobar_trk_eff_ptmix_blend%s.root",embed_key.c_str());
const string key="blended";
species_plots species(filename,key,key,"pt");
const int stack_dim=1;
/*
TH2F** resp=resp_stack(species,stack_dim,embed_stack_bin);//0th order response matrix
TH1F** match=match_stack(species,stack_dim,embed_stack_bin);//Matching efficiency curve
TH1F** match_norebin=match_stack(species,stack_dim,embed_stack_bin,false);//Matching efficiency curve
*/

TH2F** resp=resp_stack_eta_restricted(species,embed_stack_bin,etabin_start-1,etabin_end-1);
TH1F** match=match_stack_eta_restricted(species,embed_stack_bin,etabin_start-1,etabin_end-1,true);
TH1F** match_norebin=match_stack_eta_restricted(species,embed_stack_bin,etabin_start-1,etabin_end-1,false);

TH1D* hpt_diff[nstack];
TH1D* unfolded_spec[niter+1][nstack];
TH2F* resp_iter[niter+1][nstack];
TH1F* trk_eff[niter+1][nstack];

double nevts_diff[nstack],evcoll[nstack],evcoll_err[nstack],evpart[nstack],evpart_err[nstack];

isobar_hist tester(data_name);
//TH1D** hpt_diff_reverse=tester.stack(data_stack_bin,0,0);
TH3D** hpt_diff_reverse=tester.stack_3d(data_stack_bin,0);

for(int i=0;i<nstack;i++){
    hpt_diff[i]=(TH1D*)hpt_diff_reverse[nstack-1-i]->ProjectionX(Form("pt_stack_%i_%i",centrality[i+1],centrality[i]),etabin_start,etabin_end);
    nevts_diff[i]=0;
    evcoll[i]=0;
    evcoll_err[i]=0;
    evpart[i]=0;
    evpart_err[i]=0;
  
    for(int j=data_stack_bin[nstack-1-i];j<data_stack_bin[nstack-i];j++){
	nevts_diff[i]+=tester.nev_bins(j);
	evcoll[i]+=tester.nev_bins(j)*ncoll_bins[iszr][j];
	evcoll_err[i]+=tester.nev_bins(j)*ncoll_err[iszr][j];
	evpart[i]+=tester.nev_bins(j)*npart_bins[iszr][j];
	evpart_err[i]+=tester.nev_bins(j)*npart_err[iszr][j];
    }

    cout<<data_stack_bin[nstack-1-i]<<"\t"<<data_stack_bin[nstack-i]<<"\t"<<nevts_diff[i]<<"\t"<<evpart_err[i]<<endl;
    ncoll_bin->SetBinContent(i+1,evcoll[i]/nevts_diff[i]); 
    ncoll_bin->SetBinError(i+1,evcoll_err[i]/nevts_diff[i]);
    npart_bin->SetBinContent(i+1,evpart[i]/nevts_diff[i]);
    npart_bin->SetBinError(i+1,evpart_err[i]/nevts_diff[i]);

    unfolded_spec[0][i]=(TH1D*)hpt_diff[i]->Clone();
//    resp_iter[0][i]=(TH2F*)resp[i]->Clone();
//	cout<<"***************"<<endl;
//	cout<<"Initialization bin "<<i<<endl;
//	cout<<"***************"<<endl;
    resp_iter[0][i]=outlier_trim(resp[i],false);
    trk_eff[0][i]=tracking_efficiency(resp_iter[0][i],match[i]); 
    for(int iter=0;iter<niter;iter++){
//	cout<<"***************"<<endl;
//	cout<<"Iteration "<<iter<<" bin "<<i<<endl;
//	cout<<"***************"<<endl;

    	resp_iter[iter+1][i]=resp_reweight(resp_iter[0][i],unfolded_spec[iter][i],iter); 
 	trk_eff[iter+1][i]=tracking_efficiency(resp_iter[iter+1][i],match[i]);
	
//    	unfolded_spec[iter+1][i]=spec_unfold(hpt_diff[i],resp_iter[iter+1][i],iter);   
    	unfolded_spec[iter+1][i]=spec_correct(hpt_diff[i],resp_iter[iter+1][i],iter);   
//	unfolded_spec[iter+1][i]->Divide(match[i]);
    }
}
TCanvas* c_debug=new TCanvas();
c_debug->Divide(3,2);


TH1D* unfold_rebin_test[nstack];
TH1D* unfolded_rebin[niter+1][nstack];
for(int i=0;i<nstack;i++){
    for(int iter=0;iter<=niter;iter++){

	if(iter>0)unfolded_spec[iter][i]->Divide(match_norebin[i]);
	unfolded_rebin[iter][i]=(TH1D*)unfolded_spec[iter][i]->Rebin(nbins,Form("rebin_spec_%i_%i",iter,i),xbins);
	
	if(iter==niter){
	    c_debug->cd(i+1);
	    unfolded_spec[iter][i]->DrawClone();
	    unfold_rebin_test[i]=(TH1D*)unfolded_spec[iter][i]->Rebin(nbins,Form("rebin_test_%i_%i",iter,i),xbins);
	    unfold_rebin_test[i]->Scale(0.05,"width");
	    unfold_rebin_test[i]->SetLineColor(kRed);
	    unfold_rebin_test[i]->DrawClone("same");
	}


	unfolded_rebin[iter][i]->Scale(1./(2*(eta_end-eta_start))/nevts_diff[i],"width");
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

for(int i=0;i<nstack;i++){
    c4->cd(i+1);
    int i_iter=niter;
    resp_iter[i_iter][i]->GetXaxis()->SetRangeUser(0,20);
    resp_iter[i_iter][i]->Draw("colz");
}
c4->Draw();
gStyle->SetPalette(kValentine);
TCanvas* c0=new TCanvas("c0","",1600,900);
c0->Divide(3,2);

TH1D* unfold_plot[niter+1][5];
for(int i=0;i<nstack;i++){
    c0->cd(i+1);
    for(int it=0;it<=niter;it++){
	unfold_plot[it][i]=(TH1D*)(unfolded_rebin[it][i]->Clone());
    	unfold_plot[it][i]->GetXaxis()->SetRangeUser(0,20);
    	unfold_plot[it][i]->Divide(unfolded_rebin[niter][i]);
    	unfold_plot[it][i]->Draw("same PLC PLM");
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

//string system=(iszr)?"zr":"ru";
string outname=Form("outhist_%s%s_%i_%i_%ibin.root",system.c_str(),embed_key.c_str(),etabin_start,etabin_end,nstack);
TFile* output=new TFile(outname.c_str(),"recreate");
for(int i=0;i<nstack;i++){
    unfolded_rebin[niter][i]->SetName(Form("%s%s_unfolded_spec_%i_%i",system.c_str(),embed_key.c_str(),centrality[i+1],centrality[i]));
    unfolded_rebin[niter][i]->SetTitle(Form("%s%s_unfolded_spec_%i_%i",system.c_str(),embed_key.c_str(),centrality[i+1],centrality[i]));
    unfolded_rebin[0][i]->SetName(Form("%s%s_raw_spec_%i_%i",system.c_str(),embed_key.c_str(),centrality[i+1],centrality[i]));
    unfolded_rebin[0][i]->SetTitle(Form("%s%s_raw_spec_%i_%i",system.c_str(),embed_key.c_str(),centrality[i+1],centrality[i]));
    unfolded_rebin[niter][i]->Write();
    unfolded_rebin[0][i]->Write();
}
ncoll_bin->SetName(Form("%s%s_ncoll",system.c_str(),embed_key.c_str()));
ncoll_bin->Write();    
npart_bin->SetName(Form("%s%s_npart",system.c_str(),embed_key.c_str()));
npart_bin->Write();
cout<<outname<<" Written!"<<endl;
output->Close();

//*/
}
