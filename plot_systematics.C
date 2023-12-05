#include "../pp_reference/hist_pp.h"
#include "out_hist.h"

const int nrebin=32;
const Double_t rebin_edge[nrebin+1]={0.4,0.5,0.6,0.7,0.8,0.9,1,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.,2.1,2.2,2.3,2.4,2.6,2.8,3,3.35,3.8,4.4,5.1,6,7,8,9,10};

double rebin_center[nrebin];

int colors[20]={418,879,600,1,632,3,9,20,30,40,810,397,434,844,618,624,797,38,46,43};
int markers[20]={20,21,22,47,29,33,34,37,39,43,45,46,23,48,49,33,34,2,3,5};

void plot_systematics(
const string system="zr",
const string nominal_name="outhist_zr_2_3.root",
const string iter_name="outhist_zr_2_3_1iter.root",
const string pion_name="outhist_zr_pion_2_3.root",
const string smear_name="outhist_zr_smear_2_3.root",
const string out_name="systematics_zr_2_3.root",
std::vector<int> bins={0,10,20,40,60,80}
//unfold_spec[i] is centrality bin[i] to bin[i+1]
){

    for(int i=0;i<nrebin;i++) rebin_center[i]=0.5*(rebin_edge[i]+rebin_edge[i+1]);
    gStyle->SetOptStat(0);
    out_hist* vari[3];
    vari[0]=new out_hist(iter_name,bins,system,"");
    vari[0]->set_name("_1iter");
    vari[1]=new out_hist(pion_name,bins,system,"_pion");
    vari[2]=new out_hist(smear_name,bins,system,"_smear");

    string err_names[3]={"_sys_1iter","_sys_pion","_sys_smear"};
    string err_label[4]={"1st iter (#times 5)","pk#pi weighting","p_{T} smearing","Total error"};
    const int ncent=bins.size()-1;
    cout<<ncent<<endl;
    TCanvas* c_err=new TCanvas("errors","",800,800);
    TPad* can_err[ncent];
    out_hist* clean_plots=new out_hist(nominal_name,bins,system,"");
    clean_plots->set_name("_no_error");
    clean_plots->clear_error();
//    out_hist nominal_plots(nominal_name);
    out_hist* nominal_plots[3];
    for(int i=0;i<3;i++){
	nominal_plots[i]=new out_hist(nominal_name,bins,system,"");
	nominal_plots[i]->set_name(err_names[i].c_str());	
    	nominal_plots[i]->clear_error();
    	nominal_plots[i]->add_error(vari[i]);

    }

    TH1D* hist_errs[ncent][3];
    TGraph* hist_sys[ncent][3];
    TH1D* dummy_plot=new TH1D("pAu_raa_dummy","",nrebin,rebin_edge);
    dummy_plot->GetYaxis()->SetTitleSize(0.08);
    dummy_plot->GetYaxis()->SetTitleOffset(0.5);
    dummy_plot->GetXaxis()->SetTitleSize(0.06);
    dummy_plot->GetXaxis()->SetTitleOffset(0.9);
    dummy_plot->GetYaxis()->SetRangeUser(-0.3,4.3);
    c_err->Draw();

    TLatex tag;
    tag.SetTextAlign(23);
    tag.SetNDC();
    TGraph* hist_total_sys[ncent];
    for(int ic=0;ic<ncent;ic++){
      c_err->cd();
      float top_edge=0.05;
      float top=(ic==ncent-1)?1:top_edge+(1-top_edge*2)/ncent*(ic+1);
      float bottom=(ic==0)?0:top_edge+(1-top_edge*2)/ncent*(ic);
      can_err[ic]=new TPad(Form("pad_%i",ic),"",0,bottom,1,top);
      can_err[ic]->SetTickx();
      if(ic!=0) can_err[ic]->SetBottomMargin(0);
      else can_err[ic]->SetBottomMargin(top_edge/(top_edge+(1-top_edge*2)/ncent));
      if(ic!=ncent-1) can_err[ic]->SetTopMargin(0);
      else can_err[ic]->SetTopMargin(top_edge/(top_edge+(1-top_edge*2)/ncent));
      can_err[ic]->Draw();
      can_err[ic]->cd();

      dummy_plot->GetYaxis()->SetTitle("");
      dummy_plot->GetYaxis()->SetNdivisions(203);
      dummy_plot->GetYaxis()->SetLabelSize((ic==0 || ic==ncent-1)?0.1:0.12);
      dummy_plot->GetXaxis()->SetLabelSize(0.12);
      dummy_plot->DrawClone();
      double total_err[nrebin]={0}; 
      for(int i=0;i<3;i++){
	string myname=nominal_plots[i]->unfold_spec[ic]->GetName();
	hist_errs[ic][i]=(TH1D*)nominal_plots[i]->unfold_spec[ic]->Clone();
	hist_errs[ic][i]->Divide(clean_plots->unfold_spec[ic]);

	double err[nrebin];
    	for(int ibin=1;ibin<=nrebin;ibin++){
	    int scale=(i==0)?5:1;
	    err[ibin]=hist_errs[ic][i]->GetBinError(ibin+3)*100*scale;
	    total_err[ibin]+=pow(err[ibin],2);
//	    hist_sys[ic][i]->SetBinContent(ibin,0);

	}
	hist_sys[ic][i]=new TGraph(nrebin,rebin_center,err);
	hist_sys[ic][i]->SetLineColor(colors[i]);
	hist_sys[ic][i]->SetMarkerColor(colors[i]);
	hist_sys[ic][i]->SetMarkerStyle(markers[i]);
	hist_sys[ic][i]->SetMarkerSize(1);
	hist_sys[ic][i]->SetLineWidth(2);
	hist_sys[ic][i]->Draw("samepl");
     }
     for(int ibin=1;ibin<=nrebin;ibin++) total_err[ibin]=sqrt(total_err[ibin]);
     hist_total_sys[ic]=new TGraph(nrebin,rebin_center,total_err);
     hist_total_sys[ic]->SetLineColor(50);
     hist_total_sys[ic]->SetMarkerColor(50);
     hist_total_sys[ic]->SetMarkerStyle(34);
     hist_total_sys[ic]->SetMarkerSize(1);
     hist_total_sys[ic]->SetLineWidth(2);
     hist_total_sys[ic]->Draw("samepl");
     tag.SetTextSize((ic==0 || ic==ncent-1)?0.13:.15);
     tag.DrawLatex(0.35,ic==ncent-1?.7:0.9,Form("%i%%-%i%%",bins[ic],bins[ic+1]));

   if(ic==3){
     TLegend* lg=new TLegend(0.65,0.7,0.9,0.9);
     lg->AddEntry(hist_total_sys[ic],err_label[ic].c_str());
    lg->SetBorderSize(0);
    lg->Draw();

   }
   if(ic<3){
    TLegend* lg=new TLegend(0.65,0.75,0.9,0.9);
    lg->AddEntry(hist_sys[ic][ic],err_label[ic].c_str());
    lg->SetBorderSize(0);
    lg->Draw();
   }
   }
   c_err->SaveAs(Form("sys_%s.pdf",system.c_str())); 
}
